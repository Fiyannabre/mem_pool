#include <stdlib.h>
#include <stdint.h>

#include "mem_pool.h"

#define PAGE_SIZE 4096

//初始化内存池，size为每一块的大小
void mem_pool_init(mem_pool_t* m, int size){
    if(!m) return;
    if(size < 16) size = 16;

    m->mem = (char*) malloc(PAGE_SIZE);
    if(!m->mem) return;
    m->free_ptr = m->mem;
    m->free_count = PAGE_SIZE / size;

    int i = 0;
    char *ptr =  m->free_ptr;
    //将前8个字节作为next指针
    for(;i < m->free_count;i++){
        *(char **)ptr = ptr + size;
        ptr += size;
    }
    *(char **)ptr = NULL;

}

//销毁
void mem_pool_dest(mem_pool_t *m){
    //避免重复释放
    if(!m || m->free_count == 0) return;

    free(m->mem);
}

//分配
void* mem_pool_alloc(mem_pool_t *m){
    if(!m || m->free_count == 0) return NULL;

    //allocate
    void *ptr = m->free_ptr;

    //pop
    m->free_count--;
    m->free_ptr = *(char **)ptr;

    return ptr;
}

//释放
void mem_pool_free(mem_pool_t *m, void *ptr){
    //push
    *(char **)ptr = m->free_ptr;
    m->free_ptr = (char *)ptr;
    m->free_count++;
}


//size 每块内存大小
void pool_uf_init(mem_pool_uf* m, int size){
    if(!m) return;

    void* addr  = malloc(size);
    m->max_size = size;
    mem_node* node = (mem_node*)addr;

    node->free_ptr = (char*)addr + sizeof(*node);
    node->end = (char*)addr + size;
    node->next = NULL;

    m->first = node;
    m->current = node;
}

void pool_uf_dest(mem_pool_uf* m){
    if (!m) return;

    while(!m->first){
        void *addr = m->first;
        mem_node *node = (mem_node*)addr;

        m->first = node->next;
    }
}

void* pool_uf_alloc(mem_pool_uf *m, int size){
    void *cur_addr = m->current;
    mem_node *node = (mem_node*)cur_addr;

    while(node){
        //如果当前块空闲够
        if(size < (node->end - node->free_ptr)){
            char *ptr = node->free_ptr;
            node->free_ptr += size;

            return ptr;
        }

        node = node->next;
    }

    void *addr = malloc(m->max_size);
    node = (mem_node*)addr;

    node->free_ptr = (char*)addr + sizeof(mem_node);
    node->end = (char*)addr + m->max_size;

    node->next = m->current;
    m->current = node;

    char* ptr = node->free_ptr;
    node->free_ptr += size;

    return ptr;
    
}

void pool_uf_delete(mem_pool_uf * m){
    m = NULL;
}
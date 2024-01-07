#ifndef _MEM_POOL_HEAD
#define _MEM_POOL_HEAD

#ifdef __cplusplus
extern "C"
{
#endif


typedef struct mem_pool_s{
    int block_size;
    int free_count;

    char *free_ptr;
    char *mem;
}mem_pool_t;

//初始化
void mem_pool_init(mem_pool_t *, int);
//销毁
void mem_pool_dest(mem_pool_t *);
//分配
void* mem_pool_alloc(mem_pool_t *);
//释放
void mem_pool_free(mem_pool_t *, void*);

//每块前用一小块内存作为node
typedef struct mem_node_s{
    //开始位置
    unsigned char *free_ptr;
    //
    unsigned char *end;

    struct mem_node_s *next;
}mem_node;

//
typedef struct mem_pool_d{
    mem_node *first;
    mem_node *current;

    int max_size;
}mem_pool_uf;

void pool_uf_init(mem_pool_uf* m, int);
void pool_uf_dest(mem_pool_uf* m);
void* pool_uf_alloc(mem_pool_uf *m, int size);
void pool_uf_delete(mem_pool_uf *);

#ifdef __cplusplus
}
#endif

#endif
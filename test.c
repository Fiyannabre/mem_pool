#include <stdio.h>

#define SAME_SIZE 0

#include "mem_pool.h"

int main(){

#if SAME_SIZE
    mem_pool_t m;
    mem_pool_init(&m, 32);

    void *p1 = mem_pool_alloc(&m);
    printf("mem 1 address : %p\n", p1);

    void *p2 = mem_pool_alloc(&m);
    printf("mem 2 address : %p\n", p2);

    void *p3 = mem_pool_alloc(&m);
    printf("mem 3 address : %p\n", p3);

    mem_pool_free(&m, p2);

    void *p4 = mem_pool_alloc(&m);
    printf("mem 4 address : %p\n", p4);

#else

    mem_pool_uf m;

    pool_uf_init(&m, 4096);

    void *p1 = pool_uf_alloc(&m, 16);
    printf("mem 1 address : %p\n", p1);

    void *p2 = pool_uf_alloc(&m, 32);
    printf("mem 2 address : %p\n", p2);

    void *p3 = pool_uf_alloc(&m, 64);
    printf("mem 3 address : %p\n", p3);

    void *p4 = pool_uf_alloc(&m, 128);
    printf("mem 4 address : %p\n", p4);

    void *p5 = pool_uf_alloc(&m, 256);
    printf("mem 5 address : %p\n", p5);

    pool_uf_delete(&m);
#endif

    return 0;
}
#define _GNU_SOURCE
#include <stdio.h>
#include <dlfcn.h>
#include <stdlib.h>

static void * (*sys_malloc)(size_t) = NULL; 

static void link()
{
    if (!sys_malloc)
    {
        sys_malloc = dlsym(RTLD_NEXT, "malloc");
        if (!sys_malloc)
        {
            fprintf(stderr, "error while finding malloc symbols\n");
        }
    }
}

void brme()
{
    
}

void * malloc(size_t n)
{
    link();
    char * ths = getenv("MALLOC_BRK_TH");
    if (ths && n > atoi(ths))
        brme();  
    return sys_malloc(n);
}

#include <windows.h>

// sHELL wrapper for malloc free, calloc, realloc

void *s_malloc(size_t size);

void s_free(void *ptr);

void *s_calloc(size_t num, size_t size);

void *s_realloc(void *ptr, size_t size);

typedef void *t_malloc(size_t size);
typedef void t_free(void *ptr);
typedef void *t_calloc(size_t num, size_t size);
typedef void *t_realloc(void *ptr, size_t size);

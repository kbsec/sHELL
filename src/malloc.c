#include "malloc.h"

// sHELL wrapper for malloc free, calloc, realloc 


void* s_malloc(size_t size){
  return HeapAlloc(GetProcessHeap(), 0, size);
}
void s_free(void* ptr){
  if(ptr != NULL){
    HeapFree(GetProcessHeap(), 0, ptr);
  }
}

void* s_calloc(size_t num, size_t size){
  return HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, num * size);
}

void* s_realloc(void* ptr, size_t size){
  if( ptr == NULL){
    return HeapAlloc(GetProcessHeap(), 0, size);
  }
  return HeapReAlloc(GetProcessHeap(), 0, ptr, size);
}


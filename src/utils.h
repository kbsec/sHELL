#ifndef S_UTILS

#define S_UTILS
#include <windows.h>

size_t strlen(const char *str);
size_t wstrlen(const wchar_t *s);
int strcmp(const char *s1, const char *s2);

char *strcpy(char *dest, const char *src);
unsigned long djb2Hash(unsigned char *str);

void stripnewline(char *x);

void *memset(void *_Dst, int _Val, size_t _Size);

// typedefs for functions
typedef size_t t_strlen(const char *str);
typedef size_t t_wstrlen(const wchar_t *s);
typedef int t_strcmp(const char *s1, const char *s2);

typedef char *t_strcpy(char *dest, const char *src);
typedef unsigned long t_djb2Hash(unsigned char *str);

typedef void t_stripnewline(char *x);

typedef void *t_memset(void *_Dst, int _Val, size_t _Size);
#endif // ! S_UTILS

#include <windows.h>

size_t strlen(const char *str) {
  const char *s;
  for (s = str; *s; ++s)
    ;
  return (s - str);
}

size_t wstrlen(const wchar_t *s) {
  const wchar_t *end = s;
  while (*end != L'\0') {
    ++end;
  }
  return (size_t)(end - s); // Number of wchar_t elements, not bytes
}

int strcmp(const char *s1, const char *s2) {
  while (*s1 && (*s1 == *s2)) {
    s1++;
    s2++;
  }
  return *(const unsigned char *)s1 - *(const unsigned char *)s2;
}

unsigned long djb2Hash(unsigned char *str) {
  unsigned long hash = 5381;
  int c;

  while ((c = *str++))
    hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
  return hash;
}

char *strcpy(char *dest, const char *src) {
  char *saved = dest;
  while (*src) {
    *dest++ = *src++;
  }
  *dest = '\0';
  return saved;
}

void stripnewline(char *x) {
  size_t stLen = strlen(x);
  if (x[stLen - 1] == '\n') {
    x[stLen - 1] = '\0';
  }
}

void *memset(void *_Dst, int _Val, size_t _Size) {
  // Cast the pointer to an unsigned char pointer
  unsigned char *dst = (unsigned char *)_Dst;

  // Fill the memory block with the specified value
  while (_Size--) {
    *dst++ = (unsigned char)_Val;
  }

  // Return the original pointer
  return _Dst;
}

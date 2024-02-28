#include <stdio.h>

unsigned long djb2Hash(unsigned char *str) {
  unsigned long hash = 5381;
  int c;

  while (c = *str++)
    hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
  return hash;
}

int main(int argc, char **argv) {
  for (int i = 1; i < argc; i++) {
    unsigned int hash = djb2Hash(argv[i]);
    if (hash == 0) {
      printf("WARNING: %s-->%d. Name it something else\n", argv[i], hash);
    }
    printf("#define OPCODE_%s %lu\n", argv[i], hash);
  }
}

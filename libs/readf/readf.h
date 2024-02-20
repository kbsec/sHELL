/*
 * This is an example of a module that can be used by other modules
 * */
#include "../include/sHELL.h"
#include "winnt.h"
#include <windows.h>

typedef struct CommandOut_readf {
  LARGE_INTEGER qwFileSize;
  LPVOID lpBuffer;
} CommandOut_readf;

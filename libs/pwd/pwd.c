#include "../include/sHELL.h"
#include "errhandlingapi.h"
#include "minwindef.h"
#include <windows.h>

const char Name[] = "pwd";
const char Help[] = "Print the shell's current working directory.\n"
                    "Usage:\n"
                    "    pwd C:\\vagrant";

InternalAPI *core = NULL;

LPVOID lpOut = NULL;
__declspec(dllexport) VOID CommandCleanup() {
  if (lpOut) {
    core->free(lpOut);
    lpOut = NULL;
  }
}

// Initialization code
__declspec(dllexport) BOOL CommandInit(InternalAPI *lpCore) {
  core = lpCore;
  return TRUE;
}

// Exported function - Name
__declspec(dllexport) const char *CommandNameA() { return Name; }

// Exported function - Help
__declspec(dllexport) const char *CommandHelpA() { return Help; }

// Exported function - Run
__declspec(dllexport) LPVOID CommandRunA(int argc, char **argv) {
  // Allocate a buffer for the current working directory path
  DWORD bufferSize = MAX_PATH;
  char *cwd = (char *)core->malloc(bufferSize);
  if (cwd == NULL) {
    core->wprintf(L"Failed to allocate memory for CWD.\n");
    return 1; // Error code for memory allocation failure
  }
  // // your answer here
  return lpOut; // Success
}

// Entrypoint for the DLL
BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
  switch (fdwReason) {
  case DLL_PROCESS_ATTACH:
    break;
  case DLL_PROCESS_DETACH:
    break;
  case DLL_THREAD_ATTACH:
  case DLL_THREAD_DETACH:
    break;
  }
  return TRUE; // Successful
}

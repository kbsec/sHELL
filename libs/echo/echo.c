#include "../include/sHELL.h"
#include <windows.h>

const char Name[] = "echo";
const char Help[] = "echo a string back to the terminal. Example:"
                    ">>>echo asdf"
                    ">>>asdf";

LPVOID lpOut = NULL;
__declspec(dllexport) VOID CommandCleanup() {
  if (lpOut) {
    core->free(lpOut);
    lpOut = NULL;
  }
}

void *lazy_print(char *szArg) {
  HANDLE stdOut = GetStdHandle(STD_OUTPUT_HANDLE);

  WriteFile(stdOut, szArg, lstrlenA(szArg), NULL, NULL);
}

InternalAPI *core = NULL;
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
  // Example implementation: print arguments and return count
  if (argc != 2) {
    lazy_print("argc != 2.");
    for (int i = 0; i < argc; i++) {
      core->wprintf(L"%S\n", argv[i]);
      /*
       *///lazy_print(argv[i]);
      // lazy_print("\n");
    }
    return NULL;
  }
  lazy_print(argv[1]);
  return (LPVOID)1;
}

// Optional: Entry point for DLL
BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
  switch (fdwReason) {
  case DLL_PROCESS_ATTACH:
    // Code to run when the DLL is loaded
    break;
  case DLL_PROCESS_DETACH:
    // Code to run when the DLL is unloaded
    break;
  case DLL_THREAD_ATTACH:
    // Code to run when a thread is created during DLL's existence
    break;
  case DLL_THREAD_DETACH:
    // Code to run when a thread ends normally
    break;
  }
  return TRUE; // Successful
}

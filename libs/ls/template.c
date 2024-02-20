
#include "../include/sHELL.h"
#include <windows.h>

const char Name[] = "template";
const char Help[] = "Starter template to demonstrate libraries. this just "
                    "prints a message Example:"
                    ">>>template "
                    ">>>I am so modular";

InternalAPI *core = NULL;

// initialization code
__declspec(dllexport) BOOL CommandInit(InternalAPI *lpCore) { core = lpCore; }

// Exported function - Name
__declspec(dllexport) const char *CommandName() { return Name; }

// Exported function - Help
__declspec(dllexport) const char *CommandHelp() { return Help; }

// Exported function - Run
__declspec(dllexport) int CommandRun(int argc, char **argv) {
  // Example implementation: print arguments and return count
  core->wprintf(L"I am so modular!\n");
  return 0;
}

// Entrypoint for the DLL
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

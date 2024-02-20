#include "../include/sHELL.h"

#include <windows.h>

const char Name[] = "clear";
const char Help[] = "clear the screen";

LPVOID lpOut = NULL;
__declspec(dllexport) VOID CommandCleanup() {
  if (lpOut) {
    core->free(lpOut);
    lpOut = NULL;
  }
}

void clearConsole() {
  HANDLE hConsole;
  COORD coordScreen = {0, 0}; // Home for the cursor
  DWORD cCharsWritten;
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  DWORD dwConSize;

  // Get the output console handle
  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

  // Get the number of character cells in the current buffer
  if (!GetConsoleScreenBufferInfo(hConsole, &csbi)) {
    return;
  }

  dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

  // Fill the entire screen with blanks
  if (!FillConsoleOutputCharacter(
          hConsole,          // Handle to console screen buffer
          (TCHAR)' ',        // Character to write to the buffer
          dwConSize,         // Number of cells to write
          coordScreen,       // Coordinates of first cell
          &cCharsWritten)) { // Receive number of characters written
    return;
  }

  // Put the cursor at its home coordinates
  SetConsoleCursorPosition(hConsole, coordScreen);
}

InternalAPI *core = NULL;
__declspec(dllexport) BOOL CommandInit(InternalAPI *lpCore) { core = lpCore; }

// Exported function - Name
__declspec(dllexport) const char *WINAPI CommandNameA() { return Name; }

// Exported function - Help
__declspec(dllexport) const char *WINAPI CommandHelpA() { return Help; }

// Exported function - Run
__declspec(dllexport) int WINAPI CommandRunA(int argc, char **argv) {
  clearConsole();
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

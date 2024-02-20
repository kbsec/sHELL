#include <windows.h>

typedef LPSTR *WINAPI fnCommandLineToArgvA(LPSTR lpCmdline, int *numargs);
LPSTR *WINAPI CommandLineToArgvA(LPSTR lpCmdline, int *numargs);

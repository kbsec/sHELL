#include <windows.h>

#define DEBUG
#include "api.h"
#include "cmdparse.h"
#include "fgets.h"
#include "minwindef.h"
#include "opcode.h"
#include "twindefs.h"
#include "utils.h"

BOOL InitializeCore() {
  // set wprintf
  HMODULE hKernelBase = GetModuleHandleA("kernelbase.dll");
  core = (InternalAPI *)s_malloc(sizeof(InternalAPI));
  memset(core, 0, sizeof(InternalAPI));

  core->wprintf = (t_wprintf *)GetProcAddress(hKernelBase, "wprintf");
  wprintf = core->wprintf;
  if (wprintf == NULL) {
    return FALSE;
  }

  HMODULE hNtDLL = GetModuleHandleA("ntdll.dll");
  if (hNtDLL == NULL) {
    wprintf(L"Failed to find ntdll.dll %d\n", GetLastError());
    return FALSE;
  }
  core->sprintf = (t_sprintf *)GetProcAddress(hNtDLL, "sprintf");
  if (core->sprintf == NULL) {
    wprintf(L"Failed to find ntdll!vsprintf %d\n", GetLastError());
    return FALSE;
  }
  debug_wprintf(L"Setting Core functions ...\n");
  sprintf = core->sprintf;
  core->WriteStdOut = WriteStdOut;
  core->WriteStdOutLarge = WriteStdOutLarge;
  core->CommandLineToArgvA = CommandLineToArgvA;
  // memory managment
  core->free = s_free;
  core->malloc = s_malloc;
  core->calloc = s_calloc;
  core->realloc = s_realloc;

  core->strcmp = strcmp;
  core->strlen = strlen;
  core->memset = memset;
  core->wstrlen = wstrlen;

  // WinAPI
  core->hKernel32 = GetModuleHandleW(L"kernek32.dll");
  core->hGetProcAddress =
      (_GetProcAddress *)GetProcAddress(core->hKernel32, "GetProcAddress");

  // hash function
  core->djb2hash = djb2Hash;
  core->gaCommandsA = gaCommandsA;
  core->gModuleCount = &gModuleCount;
  core->ResolveCommandDependnecies = ResolveCommandDependencies;

  hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
  hStdIn = GetStdHandle(STD_INPUT_HANDLE);

  debug_wprintf(L"[+] Initializing sHELL\n");
  return TRUE;
}

BOOL LoadModulesFromCommandline() {
  int argc = 0;
  char **argv = NULL;
  char *lpCmd = GetCommandLineA();
  debug_wprintf(L"Commandline: %S\n", lpCmd);
  argv = CommandLineToArgvA(lpCmd, &argc);
  for (int i = 1; i < argc; i++) {
    debug_wprintf(L"[+] Adding Command %S\n", argv[i]);
    DWORD dwResult = AddModuleA(argv[i]);
    if (!dwResult) {
      wprintf(L"Failed to load %S: %d\n", argv[i], dwResult);
      return FALSE;
    }
    debug_wprintf(L"Adding module %S:%d\n", argv[i], dwResult);
  }
  debug_wprintf(L"%S %S %S\n", gszName, gszRun, gszHelp);
  s_free(argv);
  return TRUE;
}

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                     LPSTR lpCmdLine, int nCmdShow) {
  // Resolve wprintf()
  if (InitializeCore() != TRUE) {
    return -1;
  }
  debug_wprintf(L"[+] Initialied Core Functionality\n");
  // load all modules passed in via commandline
  if (LoadModulesFromCommandline() != TRUE) {
    return -1;
  }

  char buffer[1025];
  int argc = 0;
  char **argv = NULL;
  debug_wprintf(L"modcount %d \n", gModuleCount);
  while (1) {
    wprintf(L"\n>>>");
    s_fgets(hStdIn, buffer, 1024);
    debug_wprintf(L"INPUT: %S\n", buffer);
    stripnewline(buffer);
    argv = CommandLineToArgvA(buffer, &argc);
    for (int i = 0; i < argc; i++) {
      debug_wprintf(L"%d %S=%lu %d \n", i, argv[i],
                    djb2Hash((unsigned char *)argv[i]), strlen(argv[i]));
    }
    if (argc > 0) {
      stripnewline(argv[0]);
      unsigned int hash = djb2Hash((unsigned char *)argv[0]);
      for (int i = 0; i < gModuleCount; i++) {
        if (gaCommandsA[i].hash == hash) {
          debug_wprintf(L"Running %S\n", gaCommandsA[i].fnName());
          gaCommandsA[i].fnRun(argc, argv);
          debug_wprintf(L"Cleaning up...\n");
          gaCommandsA[i].fnCleanup();
          goto DONE_COMMAND;
        }
      }
      wprintf(L"Unknown command\n");
    }
  DONE_COMMAND:
    s_free(argv);
    argc = 0;
  }
  ExitProcess(0);
  return 0;
}

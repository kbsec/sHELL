#include "api.h"
#include "errhandlingapi.h"
#include "winnt.h"

HANDLE hStdOut;
HANDLE hStdErr;
HANDLE hStdIn;

const char gszName[] = "CommandNameA";
const char gszHelp[] = "CommandHelpA";
const char gszRun[] = "CommandRunA";
const char gszCleanup[] = "CommandCleanup";
const char gszInit[] = "CommandInit";

size_t gModuleCount = 0;
CommandA gaCommandsA[MAX_MODULE_SIZE] = {{0}};

// Internal API for sHELL
InternalAPI *core = NULL;
t_wprintf *wprintf = NULL; // core->wprintf;
t_sprintf *sprintf = NULL;

BOOL WINAPI AddModuleA(char *lpszFilePath) {
  debug_wprintf(L"Entering AddModuleA\n");
  HMODULE hModule = LoadLibraryA(lpszFilePath);
  if (hModule == NULL) {
    wprintf(L"Failed to load %S", lpszFilePath);
    return FALSE;
  }

  debug_wprintf(L"[+] Library %S found %p\n", lpszFilePath, (void *)hModule);
  ZeroMemory(&gaCommandsA[gModuleCount], sizeof(CommandA));

  gaCommandsA[gModuleCount].hModule = hModule;
  // @TODO Lock array

  FARPROC lpF = NULL;
  lpF = GetProcAddress(hModule, gszName);
  if (lpF == NULL) {
    wprintf(L"Missing Function %S!%S: %d\n", lpszFilePath, gszName,
            GetLastError());
    goto cleanup;
  }
  gaCommandsA[gModuleCount].fnName = (fnCommandNameA *)lpF;
  lpF = GetProcAddress(hModule, gszHelp);
  if (lpF == NULL) {
    wprintf(L"Missing Function %S\n", gszHelp);
    goto cleanup;
  }

  gaCommandsA[gModuleCount].fnHelp = (fnCommandHelpA *)lpF;
  // Run
  lpF = GetProcAddress(hModule, gszRun);
  if (lpF == NULL) {
    wprintf(L"Missing Function %S\n", gszRun);
    goto cleanup;
  }

  gaCommandsA[gModuleCount].fnRun = (fnCommandRunA *)lpF;

  lpF = GetProcAddress(hModule, gszCleanup);
  if (lpF == NULL) {
    wprintf(L"Missing Function %S\n", gszCleanup);
    goto cleanup;
  }

  gaCommandsA[gModuleCount].fnCleanup = (fnCommandCleanup *)lpF;
  lpF = GetProcAddress(hModule, gszInit);
  if (lpF == NULL) {
    wprintf(L"Missing Function %S\n", gszRun);
    goto cleanup;
  }

  gaCommandsA[gModuleCount].fnInit = (fnCommandInit *)lpF;
  debug_wprintf(L"Initializing Core for %S\n", lpszFilePath);
  // Initialize Core API
  gaCommandsA[gModuleCount].fnInit(core);

  gaCommandsA[gModuleCount].hash =
      djb2Hash((unsigned char *)gaCommandsA[gModuleCount].fnName());

  wprintf(L"[!] Added New Module: %S: %lu\n",
          gaCommandsA[gModuleCount].fnName(), gaCommandsA[gModuleCount].hash);
  gModuleCount++;
  return TRUE;
cleanup:
  if (hModule) {
    FreeLibrary(hModule);
  }
  debug_wprintf(L"Failure!\n");
  return FALSE;
}

BOOL ResolveCommandDependencies(CommandDependency deps[]) {
  // deps is a null terminated array
  // O(n^2) dummy resolver
  debug_wprintf(L"[+] Resolving Dependencies...\n");
  for (int i = 0; deps[i].hash + deps[i].lpCmd != 0; i++) {
    // dumb linear search for cmd
    for (int j = 0; j < gModuleCount; j++) {
      if (gaCommandsA[j].hash == deps[i].hash) {
        deps[i].lpCmd = &(gaCommandsA[j]);
        break;
      }

      if (deps[i].lpCmd == NULL) {
        wprintf(L"Dependency error: %lu\n", deps[i].hash);
        return FALSE;
      }
    }
  }
  return TRUE;
}

BOOL WriteStdOut(char *data, DWORD dwSize) {
  BOOL result = WriteFile(hStdOut, // Handle to the output device
                          data,    // Buffer to write from
                          dwSize,  // Number of bytes to write
                          NULL,    // Number of bytes that were written
                          NULL     // Not using overlapped I/O
  );
  return result;
}

// provides a (somewhat silly) example of
BOOL WriteStdOutLarge(char *data, ULONGLONG qp) {
  ULONGLONG qwWritten = 0;
  const DWORD dwChunkSize = 1 << 6;
  DWORD dwToWrite = 0;
  DWORD dwWritten = 0;
  while (qp - qwWritten > 0) {
    dwToWrite = min(dwChunkSize, (qp - dwWritten));
    if (!WriteFile(hStdOut, (data + qwWritten), dwToWrite, &dwWritten, NULL)) {
      wprintf(L"\n**** ERROR *** Write terminated early: %d\n", GetLastError());
      return FALSE;
    }
    qwWritten += dwWritten;
  }
  return TRUE;
}

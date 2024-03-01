#ifndef COMMAND_TABLE

#define COMMAND_TABLE
#include "cmdparse.h"
#include "errhandlingapi.h"
#include "malloc.h"
#include "minwindef.h"
#include "twindefs.h"
#include "utils.h"
#include <stdarg.h>
#include <windows.h>

typedef int t_wprintf(const wchar_t *format, ...);
typedef int t_sprintf(char *str, const char *format, ...);

typedef const char *fnCommandNameA();
typedef const char *fnCommandHelpA();
typedef LPVOID fnCommandRunA(int argc, char **argv);
typedef VOID fnCommandCleanup();
typedef LPVOID fnCommandInit(VOID *lpCore);
typedef BOOL fnWriteStdOut(char *data, DWORD dwSize);
typedef BOOL fnWriteStdOutLarge(char *data, ULONGLONG qp);

typedef struct CommandA {
  fnCommandNameA *fnName;
  fnCommandHelpA *fnHelp;
  fnCommandInit *fnInit;
  fnCommandRunA *fnRun;
  fnCommandCleanup *fnCleanup;
  unsigned int hash;
  HMODULE hModule;
} CommandA;

typedef struct CommandDependency {
  unsigned int hash;
  CommandA *lpCmd;
} CommandDependency;

#define DECLARE_DEP(hash)                                                      \
  { hash, NULL }

typedef BOOL fnResolveCommandDependencies(CommandDependency deps[]);

BOOL WriteStdOut(char *data, DWORD dwSize);

BOOL WriteStdOutLarge(char *data, ULONGLONG qp);
BOOL ResolveCommandDependencies(CommandDependency deps[]);

typedef struct InternalAPI {
  fnResolveCommandDependencies *ResolveCommandDependnecies;
  // Print
  t_wprintf *wprintf;
  t_sprintf *sprintf;
  fnWriteStdOut *WriteStdOut;
  fnWriteStdOutLarge *WriteStdOutLarge;
  fnCommandLineToArgvA *CommandLineToArgvA;
  // Memory
  t_malloc *malloc;
  t_free *free;
  t_calloc *calloc;
  t_realloc *realloc;
  // Utils

  t_strlen *strlen;
  t_wstrlen *wstrlen;
  t_strcmp *strcmp;

  t_strcpy *strcpy;
  t_djb2Hash *djb2hash;

  t_stripnewline *stripnewline;

  t_memset *memset;
  HMODULE hKernel32;
  _GetProcAddress *hGetProcAddress;
  CommandA *gaCommandsA;
  size_t *gModuleCount;

} InternalAPI;

extern InternalAPI *core;
extern t_wprintf *wprintf;
extern t_sprintf *sprintf;

#define DEBUG
#ifdef DEBUG
#define debug_WriteStdOut(in, size)                                            \
  core->wprintf(L"DEBUG: %S:%d: ", __FILE__, __LINE__);                        \
  WriteStdOut(in, size)
#define debug_wprintf(...)                                                     \
  core->wprintf(L"DEBUG: %S:%d: ", __FILE__, __LINE__);                        \
  core->wprintf(__VA_ARGS__)
#else
#define debug_wprintf(...)
#define debug_WriteStdOut(in, size)
#endif

extern const char gszName[];
extern const char gszHelp[];
extern const char gszRun[];
extern const char gszCleanup[];
extern const char gszInit[];

extern HANDLE hStdOut;
extern HANDLE hStdErr;
extern HANDLE hStdIn;

#define MAX_MODULE_SIZE 256

BOOL WINAPI AddModuleA(char *lpszFilePath);

extern CommandA gaCommandsA[MAX_MODULE_SIZE];

extern size_t gModuleCount;
#endif

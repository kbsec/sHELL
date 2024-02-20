
#include "libloaderapi.h"
#include <stdio.h>
#include <windows.h>

typedef int CommandRunner(int argc, char **argv);
typedef const char *CommandNameA();
typedef const char *CommandHelpA();

int main() {
  int argc = 1;
  char *argv[] = {"clear"};
  HMODULE hModule = LoadLibraryA("clear.dll");
  printf("[+] Loaded the Library\n");
  CommandRunner *cr = (CommandRunner *)GetProcAddress(hModule, "CommandRun");
  CommandHelpA *cn = (CommandHelpA *)*GetProcAddress(hModule, "CommandName");

  printf("Running tests\n");
  cr(0, NULL);
  cr(argc, argv);
  printf("Make sure the screen is cleared!\n");
  printf("%s\n", cn());
  return 0;
}

#include <windows.h>
#include <stdio.h>


typedef int CommandRunner(int argc, char** argv);

int main(){
  int argc  = 2;
  char *argv[] = {"echo", "this is a test!\n"};
  HMODULE hModule = LoadLibraryA("echo.dll");
  printf("[+] Loaded the Library\n");
  CommandRunner* cr = (CommandRunner*) GetProcAddress(hModule, "CommandRun");
  printf("Running tests\n");
  cr(0, NULL);
  cr(argc, argv);
  return 0;

}

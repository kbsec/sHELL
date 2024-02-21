# sHELL
a hellish way to  build a simple shell. 
course work for CY4973 Introductions to Windows Malware

## Basics
This is a teaching shell used to help students incramentally build out functionality for their final project 


### Format
The main shell will use a trusted path on startup to store all DLLs. Each DLL must have the following functions implemented

```c


char* Name(); // returns a pointer to a null terminated string containing the modules name  
char* Help(); // retrurns a pointer to a null terminated string containing a help message 
DWORD Run(DWORD argc, CHAR** argv); // Primary entry point for the module. this runs the command and outputs a DWORD


```

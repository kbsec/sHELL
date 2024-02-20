
CC=x86_64-w64-mingw32-gcc

.PHONY: clean dist 

all: clear.dll test.exe 

clear.dll:
	$(CC) -shared -nostdlib -ffreestanding   clear.c  -e DllMain  -fPIE -lkernel32 -o clear.dll


dist: clear.dll 
	cp clear.dll ../../dist/

test.exe:
	$(CC) test.c -static -o test.exe

clean:
	-rm *.exe 
	-rm *.dll 

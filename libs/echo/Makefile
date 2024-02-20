CC=x86_64-w64-mingw32-gcc

.PHONY: clean 

all: echo.dll test.exe dist 

echo.dll:
	$(CC) -shared -nostdlib -ffreestanding  -s echo.c  -e DllMain  -fPIC -lkernel32 -o echo.dll

test.exe:
	$(CC) test.c -static -o test.exe

dist: echo.dll 
	cp echo.dll ../../dist/

clean:
	-rm *.exe 
	-rm *.dll 

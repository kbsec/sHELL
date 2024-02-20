CC=x86_64-w64-mingw32-gcc 

LDFLAGS=-s -nostdlib -ffreestanding  -mstackrealign -e WinMain -fPIC -lkernel32 -Wall 

.PHONY: clean dist 

main:
	$(CC) $(LDFLAGS) utils.c  malloc.c   cmdparse.c fgets.c api.c main.c   -lkernel32 -o main.exe

dist: main
	cp main.exe ../dist/

clean:
	rm *.exe

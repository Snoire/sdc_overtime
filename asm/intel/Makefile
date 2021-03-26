all : hello helloc

# "Hello World!"
hello : hello.o
	ld hello.o -o hello

hello.o : hello.asm
	nasm -f elf64 -o hello.o hello.asm

helloc : hello.c
	cc hello.c -o helloc

clean :
	rm -f *.o hello helloc

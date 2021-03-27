all : hello helloc input

# "Hello World!"
hello : hello.o
	ld hello.o -o hello

hello.o : hello.asm
	nasm -f elf64 -o hello.o hello.asm

helloc : hello.c
	cc hello.c -o helloc

# Getting User Input
input : input.o
	ld $< -o $@

input.o : input.asm
	nasm -f elf64 -o $@ $<

clean :
	rm -f *.o hello helloc input

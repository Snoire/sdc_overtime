all : c83
.PHONY : all

c83 : main.o hello.o
	cc main.o hello.o -o c83

main.o : main.c
	cc -c main.c

clean :
	rm -rf *.o

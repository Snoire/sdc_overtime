all : c74
.PHONY : all

c74 : main.o
	cc -o c74 main.o
main.o : main.c
	cc -c main.c

clean :
	-rm -f *.o *~ cscope* c74

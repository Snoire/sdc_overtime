all : c47
.PHONY : all

c47 : main.o
	cc -o c47 main.o
main.o : main.c
	cc -c main.c

clean :
	-rm -f *.o *~ cscope* c47

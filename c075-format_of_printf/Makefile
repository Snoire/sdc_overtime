all : c75 printf2
.PHONY : all

c75 : main.o
	cc -o c75 main.o
main.o : main.c
	cc -c main.c

clean :
	-rm -f *.o *~ cscope* c75 printf2

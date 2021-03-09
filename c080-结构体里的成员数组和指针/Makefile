all : c80
.PHONY : all

c80 : main.o
	cc -o c80 main.o
main.o : main.c
	cc -c main.c

clean :
	-rm -f *.o *~ cscope* c80

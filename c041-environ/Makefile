all : c41
.PHONY : all

c41 : main.o
	cc -o c41 main.o
main.o : main.c
	cc -c main.c

clean :
	-rm -f *.o *~ cscope* c41

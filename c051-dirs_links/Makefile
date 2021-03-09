all : c51
.PHONY : all

c51 : main.o
	cc -o c51 main.o
main.o : main.c
	cc -c main.c

clean :
	-rm -f *.o *~ cscope* c51

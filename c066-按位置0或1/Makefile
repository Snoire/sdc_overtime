all : c66
.PHONY : all

c66 : main.o
	cc -o c66 main.o
main.o : main.c
	cc -c main.c

clean :
	-rm -f *.o *~ cscope* c66

all : c38
.PHONY : all

c38 : main.o
	cc -o c38 main.o
main.o : main.c
	cc -c main.c

clean :
	-rm -f *.o *~ cscope* c38

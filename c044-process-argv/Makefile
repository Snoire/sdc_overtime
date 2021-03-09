all : c44
.PHONY : all

c44 : main.o
	cc -o c44 main.o
main.o : main.c
	cc -c main.c

clean :
	-rm -f *.o *~ cscope* c44

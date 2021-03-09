all : c18
.PHONY : all

c18 : main.o
	cc -o c18 main.o
main.o : main.c
	cc -c main.c

clean :
	-rm -f *.o *~ cscope* c18

all : c54
.PHONY : all

c54 : main.o
	cc -o c54 main.o
main.o : main.c
	cc -c main.c

clean :
	-rm -f *.o *~ cscope* c54

all : c31
.PHONY : all

c31 : linkedList.o
	cc -o c31 linkedList.o -Wall
linkedList.o : linkedList.c
	cc -c linkedList.c -Wall

clean :
	-rm -f *.o *~ cscope* c31

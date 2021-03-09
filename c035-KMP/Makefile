all : c35
.PHONY : all clean

c35 : main.o kmp.o getStr.o
	cc -o c35 main.o kmp.o getStr.o
main.o : main.c
	cc -g -c main.c -Wall
kmp.o : kmp.c
	cc -g -c kmp.c -Wall
getStr.o : getStr.c
	cc -g -c getStr.c -Wall

clean :
	rm *.o c35

clean :
	-rm -f *.o *~ cscope* c35

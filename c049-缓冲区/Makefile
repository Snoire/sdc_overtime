all : c49 feof
.PHONY : all

c49 : main.o
	cc -o c49 main.o
main.o : main.c
	cc -c main.c

clean :
	-rm -f *.o *~ cscope* c49 feof

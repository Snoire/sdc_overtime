all : c14
.PHONY : all

c14 : main.o
	cc -o c14 main.o
main.o : main.c
	cc -c main.c

.PHONY : clean
clean :
	rm -f *.o c14

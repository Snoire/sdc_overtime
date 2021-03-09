all : c71
.PHONY : all

c71 : main.o
	cc -o c71 main.o
main.o : main.c
	cc -c main.c

clean:
	rm -rf *.o a.out c71


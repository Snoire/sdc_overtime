.PHONY : all

all : clean test

test : main.o pri.o
	cc main.o pri.o -o test

clean :
	rm -rf test *.o

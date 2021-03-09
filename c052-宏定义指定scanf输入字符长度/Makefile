.PHONY : all
OBJS = c52 test
all : $(OBJS)

c52 : main.o
	cc -o c52 main.o
main.o : main.c
	cc -c main.c

clean :
	-rm -f *.o *~ cscope* $(OBJS)

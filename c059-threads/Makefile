.PHONY : all
CFLAGS=-pthread

OBJS = c59 thread_cleanup pthread_sigmask
all : $(OBJS)

c59 : main.o
	cc -o c59 main.o -pthread
main.o : main.c
	cc -c main.c

clean :
	-rm -f *.o *~ cscope* $(OBJS)

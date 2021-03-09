.PHONY : all clean
OBJS = c58 child_status
all : $(OBJS)

c58 : main.c

child_status : child_status.o print_wait_status.o
child_status.o : print_wait_status.h

clean :
	-rm -rf *.out *.o $(OBJS)

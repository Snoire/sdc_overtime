.PHONY : all
CFLAGS = -Wall -g

OBJS := c27
OBJS += $(filter-out main,$(patsubst %.c,%,$(wildcard *.c)))

all: $(OBJS)

c27 : main.o
	cc -o c27 main.o
main.o : main.c
	cc -c main.c

clean :
	-rm -f *.o *~ cscope* $(OBJS)

.PHONY : all clean
OBJS := c8
OBJS += $(filter-out main,$(patsubst %.c,%,$(wildcard *.c)))

all: $(OBJS)

c8 : main.o
	cc -o c8 main.o
main.o : main.c
	cc -c main.c

clean :
	-rm -f *.o *~ cscope* $(OBJS)

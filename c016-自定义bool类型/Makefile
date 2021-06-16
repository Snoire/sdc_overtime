.PHONY : all clean
CFLAGS = -Wall -Werror -g

OBJS := c16
OBJS += $(filter-out main,$(patsubst %.c,%,$(wildcard *.c)))

all: $(OBJS)

c16 : main.c
	cc main.c -o c16

clean :
	-rm -f *.o *~ cscope* $(OBJS)

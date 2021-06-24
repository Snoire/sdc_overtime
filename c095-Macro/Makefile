# https://segmentfault.com/a/1190000004200708
.PHONY : all

OBJS = $(patsubst %.c,%,$(wildcard *.c))
CFLAGS = -Wall -Wextra -g

all : $(OBJS)

clean :
	-rm -f *.o *~ *.out $(OBJS)

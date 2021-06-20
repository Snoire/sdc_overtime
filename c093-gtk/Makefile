.PHONY : all
OBJS = $(patsubst %.c,%,$(wildcard *.c))
CFLAGS = -Wall -g

all : $(OBJS)

clean :
	-rm -f *.o *~ *.out $(OBJS)

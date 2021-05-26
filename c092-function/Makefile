.PHONY : all
OBJS = $(patsubst %.c,%,$(wildcard *.c))
CFLAGS = -Wall -g -lm

all : $(OBJS)

clean :
	-rm -f *.o *~ cscope* *.txt $(OBJS)

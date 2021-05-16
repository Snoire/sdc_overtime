.PHONY : all
OBJS = $(patsubst %.c,%,$(wildcard *.c))
CFLAGS = -Wall -g -pthread

all : $(OBJS)

clean :
	-rm -f *.o *~ cscope* *.txt $(OBJS)

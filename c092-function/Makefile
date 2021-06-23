.PHONY : all
OBJS = $(patsubst %.c,%,$(wildcard *.c))
CFLAGS = -Wall -Wextra #-Werror
LDLIBS = -lm

all : $(OBJS)

clean :
	-rm -f *.o *~ *.out $(OBJS)

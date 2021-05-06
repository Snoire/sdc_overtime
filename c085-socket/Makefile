.PHONY : all
OBJS = $(patsubst %.c,%,$(wildcard *.c))
CFLAGS = -Wall -Werror

all : $(OBJS)

clean :
	-rm -f *.o *~ cscope* *.socket $(OBJS)

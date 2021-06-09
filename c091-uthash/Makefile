.PHONY : all
OBJS = $(patsubst %.c,%,$(wildcard *.c))
# https://github.com/troydhanson/uthash
CFLAGS = -Wall -g -I./uthash/include

all : $(OBJS)

clean :
	-rm -f *.o *~ cscope* *.txt $(OBJS)

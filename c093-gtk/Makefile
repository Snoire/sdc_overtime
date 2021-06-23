.PHONY : all
CFLAGS = -Wall -g
CFLAGS += $(shell pkg-config --cflags gtk4)
CFLAGS += $(shell pkg-config --libs gtk4)

OBJS = $(patsubst %.c,%,$(wildcard *.c))

all : $(OBJS)

clean :
	-rm -f *.o *~ *.out $(OBJS)

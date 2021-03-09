.PHONY : all echo clean

OBJS := c63
OBJS += $(filter-out main,$(patsubst %.c,%,$(wildcard *.c)))

CFLAGS = -Wall

all: $(OBJS)

c63 : main.c
	cc main.c -o c63

echo :
	@echo $(OBJS)

clean :
	-rm -f $(OBJS) *~ *.o

.PHONY : all echo clean

OBJS := c55
OBJS += $(filter-out main,$(patsubst %.c,%,$(wildcard *.c)))

CFLAGS = -Wall

all: $(OBJS)

c55 : main.c
	cc main.c -o c55

echo :
	@echo $(OBJS)

clean :
	-rm -f $(OBJS) *~ *.o

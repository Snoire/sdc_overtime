.PHONY : all echo clean

OBJS := c68
OBJS += $(filter-out main,$(patsubst %.c,%,$(wildcard *.c)))

CFLAGS = -Wall

all: $(OBJS)

c68 : main.c
	cc main.c -o c68

echo :
	@echo $(OBJS)

clean :
	-rm -f $(OBJS) *~ *.o

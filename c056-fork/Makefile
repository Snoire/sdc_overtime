.PHONY : all echo clean

OBJS := c56
OBJS += $(filter-out main,$(patsubst %.c,%,$(wildcard *.c)))

CFLAGS = -Wall

all: $(OBJS)

c56 : main.c
	cc main.c -o c56

echo :
	@echo $(OBJS)

clean :
	-rm -f $(OBJS) *~ *.o

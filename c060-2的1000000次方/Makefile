.PHONY : all echo clean

OBJS := c60
OBJS += $(filter-out main,$(patsubst %.c,%,$(wildcard *.c)))

CFLAGS = -Wall

all: $(OBJS)

c60 : main.c
	cc main.c -o c60

echo :
	@echo $(OBJS)

clean :
	-rm -f $(OBJS) *~ *.o

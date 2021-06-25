.PHONY : all
CFLAGS = -Wall -g
CFLAGS += $(shell pkg-config --cflags gtk4)
CFLAGS += $(shell pkg-config --libs gtk4)

OBJS = $(patsubst %.c,%,$(wildcard *.c))
VALA_OBJS = $(patsubst %.vala,vala_%,$(wildcard *.vala))

all : $(OBJS) $(VALA_OBJS)

vala_% : VALAFLAGS = --pkg gtk4
vala_% : %.vala
	valac $(VALAFLAGS) $^ -o $@

echo :
	echo $(VALA_OBJS)
clean :
	-rm -f *.o *~ *.out $(OBJS) $(VALA_OBJS)

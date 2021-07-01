.PHONY : all

OBJS = $(patsubst %.c,%,$(wildcard *.c))
VALA_OBJS = $(patsubst %.vala,vala_%,$(wildcard *.vala))

all : $(OBJS) $(VALA_OBJS)

vala_% : %.vala
	valac $(VALAFLAGS) $^ -o $@

clean :
	-rm -f *.o *~ *.out $(OBJS) $(VALA_OBJS)

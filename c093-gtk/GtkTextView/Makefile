.PHONY : all

CEXES = $(patsubst %.c,%,$(wildcard *.c))
VALAEXES = $(patsubst %.vala,vala_%,$(wildcard *.vala))

all : $(CEXES) $(VALAEXES)

$(CEXES) : %:%.c
	cc $^ -o $@ $(CFLAGS) $(LDFLAGS)

vala_% : %.vala
	valac $(VALAFLAGS) $^ -o $@

clean :
	-rm -f *.o *~ *.out $(CEXES) $(VALAEXES)

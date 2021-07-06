.PHONY : all

CEXES = $(patsubst %.c,%,$(wildcard tfe?.c))
VALAEXES = $(patsubst %.vala,vala_%,$(wildcard tfe?.vala))

all : $(CEXES) $(VALAEXES) tfe3_r vala_tfe3_r

$(CEXES) : %:%.c
	cc $^ -o $@ $(CFLAGS) $(LDFLAGS)

tfe3_r : tfe3_r.c resources.c
	cc $< -o $@ $(CFLAGS) $(LDFLAGS)

resources.c : tfe3.gresource.xml
	glib-compile-resources $< --target=$@ --generate-source

vala_% : %.vala
	valac $(VALAFLAGS) $^ -o $@

vala_tfe3_r : tfe3_r.vala resources.c
	valac --pkg gtk4 --gresources=tfe3.gresource.xml resources.c $< -o $@

clean :
	-rm -f *.o *~ *.out $(CEXES) $(VALAEXES) tfe3_r vala_tfe3_r resources.c

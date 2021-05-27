.PHONY : all echo clean

OBJS := c63
OBJS += $(filter-out main,$(patsubst %.c,%,$(wildcard *.c)))

CFLAGS = -Wall
CFLAGS += -I../../play/uthash/include

all: $(OBJS)

c63 : main.c
	cc main.c -o c63

unlink : unlink.c unlink.txt
	cc unlink.c -o unlink
unlink.txt :
	touch unlink.txt

rename : rename.c rename.old
	cc rename.c -o rename
rename.old :
	echo "file: rename.old" > rename.old

echo :
	@echo $(OBJS)

clean :
	-rm -f $(OBJS) *~ *.o unlink.txt rename.old rename.new

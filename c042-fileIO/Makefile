OBJS = c42 readfromtty_block ioctl tee open
.PHONY : all
all : $(OBJS)

c42 : main.o
	cc -o c42 main.o
	chmod 000 filetest1
main.o : main.c
	cc -c main.c

readfromtty_block : readfromtty_block.o
readfromtty_block.o : readfromtty_block.c

ioctl : ioctl.o
ioctl.o : ioctl.c

tee : tee.o
tee.o : tee.c

open : open.o
open.o : open.c
clean :
	-rm -f *.o *~ cscope* $(OBJS)
	chmod 644 filetest1

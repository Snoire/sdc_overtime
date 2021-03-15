.PHONY : all clean
#OBJS = write read fprintf
OBJS += $(patsubst %.c,%,$(wildcard *.c))
all : $(OBJS)

write : write.o
	cc -o $@ write.o
write.o : write.c
	cc -c write.c

read : read.o
	cc -o $@ $^
read.o : read.c
	cc -c read.c

fprintf : fprintf.o
	cc -o $@ $^
fprintf.o : fprintf.c
	cc -c $^

clean :
	rm -f *.o $(OBJS) rewind.txt write2.txt

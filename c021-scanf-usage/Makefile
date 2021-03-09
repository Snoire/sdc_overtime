.PHONY : all

OBJS = c21 formatstr
all : $(OBJS)

c21 : main.o
	cc -o c21 main.o
main.o : main.c
	cc -c main.c

formatstr : formatstr.o
formatstr.o : formatstr.c

clean :
	-rm -f *.o *~ cscope* $(OBJS)

.PHONY : all
OBJS = c53 read_lastline
all : $(OBJS)

c53 : main.o
	cc -o c53 main.o
main.o : main.c
	cc -c main.c

read_lastline : read_lastline.o
read_lastline.o : read_lastline.c

clean :
	rm -rf *.o *.out $(OBJS)

.PHONY : all
OBJS = c45 datatype_conversion
all : $(OBJS)

c45 : main.o
	cc -o c45 main.o -lcrypt
	-sudo chown root:shadow c45
	sudo chmod 4755 c45
main.o : main.c
	cc -c main.c

clean :
	-rm -f *.o *~ cscope* c45 $(OBJS)

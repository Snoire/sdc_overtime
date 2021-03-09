.PHONY : all
OBJS = get_log_id get_last_line_id
all : $(OBJS)

c65 : main.o
	cc -o c65 main.o
main.o : main.c
	cc -c main.c

clean :
	-rm -f *.o *~ cscope* $(OBJS)

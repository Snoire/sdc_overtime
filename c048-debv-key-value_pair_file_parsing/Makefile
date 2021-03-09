OBJS = c48 sample strstr
.PHONY : all
all : $(OBJS)

c48 : main.o
	cc -o c48 main.o
main.o : main.c
	cc -c main.c

sample : sample.o
sample.o : sample.c

strstr : strstr.o
strstr.o : strstr.c
clean :
	-rm -f *.o *~ cscope* $(OBJS)

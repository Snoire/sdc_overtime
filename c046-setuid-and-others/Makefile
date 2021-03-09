all : root
.PHONY : all

c46 : main.o
	cc -o c46 main.o
main.o : main.c
	cc -c main.c

root : c46
	sudo chown root:root c46
	sudo chmod u+s c46

len : c46
	sudo chown len:len c46
	sudo chmod u+s c46


clean :
	-rm -f *.o *~ cscope* c46

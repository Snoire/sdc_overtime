targets = exit hello0 hello1

all : $(targets)

exit : exit.o
	ld exit.o -o exit
exit.o : exit.s
	as exit.s -o exit.o

hello0 : hello0.o
	ld hello0.o -o hello0
hello0.o : hello0.s
	as hello0.s -o hello0.o

hello1 : hello1.o
	ld $< -o $@
hello1.o : hello1.s
	as $< -o $@



clean :
	rm -f *.o $(targets)

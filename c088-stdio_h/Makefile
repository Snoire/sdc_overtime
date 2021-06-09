.PHONY : all
CFLAGS = -Wall -g

stdio.txt : stdio.h
	/bin/grep -n "extern" $< > $@

stdio.h : stdio.c
	gcc -E $< -o $@

clean :
	-rm -f *.o *~ cscope* *.txt stdio.h

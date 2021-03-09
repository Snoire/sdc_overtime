compile_start_time := $(shell date +%s)
CFLAGS = -I./include -Wall -Werror

objs := user/main.o
objs += user/day_of_week.o
objs += user/day_in_month.o
objs += user/get_current_time.o


all : overtime
.PHONY : all clean cscope install gdb

overtime : $(objs)
	cc $^ -o $@

user/main.o : include/day_of_week.h include/day_in_month.h include/get_current_time.h

#user/main.o : user/main.c
#	cc -c $^ -o $@ $(CFLAGS)
#user/day_of_week.o: user/day_of_week.c
#	cc -c $^ -o $@
#user/day_in_month.o: user/day_in_month.c
#	cc -c $^ -o $@
#user/get_current_time.o: user/get_current_time.c
#	cc -c $^ -o $@

cscope :
	cscope -Rbq

gdb : all
	cc -o user/main.o -c -g user/main.c $(CFLAGS)

install : all
	sudo install -c overtime /usr/local/bin
	sudo install -c overtime.1 /usr/local/man/man1

clean :
	@echo 'clean up redundant files..'
	@rm -f cscope.* overtime *.o *.i *.s
	@cd user; rm -f *.o
	@echo 'Done.'
    


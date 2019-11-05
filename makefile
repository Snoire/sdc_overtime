compile_start_time := $(shell date +%s)
CFLAGS = -I./include

objs := user/main.o
objs += user/dayOfWeek.o
objs += user/daysInaMonth.o
objs += user/getCurrentTime.o


all : overtime
.PHONY : all clean cscope install

overtime : $(objs)
	cc -o $@ $^
user/main.o : user/main.c
	cc -c $^ -o $@ $(CFLAGS)
user/dayOfWeek.o: user/dayOfWeek.c
	cc -c $^ -o $@
user/daysInaMonth.o: user/daysInaMonth.c
	cc -c $^ -o $@
user/getCurrentTime.o: user/getCurrentTime.c
	cc -c $^ -o $@

cscope :
	cscope -Rbq

install : all
	install -c overtime /usr/local/bin/overtime

clean :
	@echo 'clean up redundant files..'
	@rm -f cscope.* overtime *.o *.i *.s
	@cd user; rm -f *.o
	@echo 'Done.'
    


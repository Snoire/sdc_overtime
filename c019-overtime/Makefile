compile_start_time := $(shell date +%s)
#CFLAGS = -I./include -Wall -Werror
CFLAGS = -I./include -Wall -g

#objs := user/main.o
objs += user/day_of_week.o
objs += user/day_in_month.o
objs += user/get_current_time.o


#all : overtime
all : ot otd
.PHONY : all clean install

#overtime : $(objs)
#	cc $^ -o $@
ot : $(objs) user/ot.o
	cc $^ -o $@
otd : $(objs) user/otd.o
	cc $^ -o $@

#user/main.o : include/day_of_week.h include/day_in_month.h include/get_current_time.h
user/ot.o : include/day_of_week.h include/day_in_month.h include/get_current_time.h
user/otd.o : include/day_of_week.h include/day_in_month.h include/get_current_time.h
#user/ot.o : user/ot.c
#	cc -c $^ -o $@ $(CFLAGS)
#user/otd.o : user/otd.c
#	cc -c $^ -o $@ $(CFLAGS)


#user/main.o : user/main.c
#	cc -c $^ -o $@ $(CFLAGS)
#user/day_of_week.o: user/day_of_week.c
#	cc -c $^ -o $@
#user/day_in_month.o: user/day_in_month.c
#	cc -c $^ -o $@
#user/get_current_time.o: user/get_current_time.c
#	cc -c $^ -o $@


install : all
	sudo install -c ot /usr/local/bin
	sudo install -c otd /usr/local/bin
	sudo install -c overtime.1 /usr/local/man/man1

clean :
	@echo 'clean up redundant files..'
	@rm -f ot otd cscope.* overtime *.socket *.o *.i *.s
	@cd user; rm -f *.o
	@echo 'Done.'

.PHONY : all clean cscope

compile_start_time := $(shell date +%s)
maino := mainDir/main.o
file1 := cFile1Dir/cFile1.o
file2 := cFile2Dir/cFile2.o
file3 := cFile3Dir/cFile3.o

mainc := $(maino:.o=.c)
file1c := $(file1:.o=.c)
file2c := $(file2:.o=.c)
file3c := $(file3:.o=.c)

objects := $(maino) $(file1) $(file2) $(file3)
sources := $(objects:.o=.c)

all : c1

#################################################################################

c1 : $(objects)
	cc -o c1 $(objects)
	@echo
	@echo "Compile end at `date` " 
	@echo "Duration "`expr \`date +%s\` - $(compile_start_time)`" seconds" 

$(maino) : $(mainc)
	cd mainDir; cc -c main.c -I ../hFileDir/

$(file1) : $(file1c)
	cd cFile1Dir; cc -c cFile1.c

$(file2) : $(file2c)
	cd cFile2Dir; cc -c cFile2.c

$(file3) : $(file3c)
	cd cFile3Dir; cc -c cFile3.c

#################################################################################

cscope :
##	cd mainDir; cscope -Rbq -I ../hFileDir  ##这个不行，不知道为啥
	cscope -Rbq

clean :
	@echo 'clean up redundant files..'
	@rm -f cscope.* c1 *.o *.i *.s
	@cd mainDir; rm -f *.o *.i *.s
	@cd cFile1Dir; rm -f *.o *.i *.s
	@cd cFile2Dir; rm -f *.o *.i *.s
	@cd cFile3Dir; rm -f *.o *.i *.s
	@cd hFileDir; rm -f *.o *.i *.s
	@echo 'Done.'


compile_start_time := $(shell date +%s)

all :
	make c1
	@echo
	make cscope
	@echo
	@echo "compile end at `date` " 
	@echo "duration "`expr \`date +%s\` - $(compile_start_time)`" seconds" 
	@echo
.PHONY : all

#################################################################################

c1 : mainDir/main.o cFileDir/cFile1.o cFileDir/cFile2.o cFileDir/cFile3.o
	cc -o c1 mainDir/main.o cFileDir/cFile1.o cFileDir/cFile2.o cFileDir/cFile3.o

mainDir/main.o : mainDir/main.c
	cd mainDir; cc -c main.c -I ../hFileDir/

cFileDir/cFile1.o : cFileDir/cFile1.c
	cd cFileDir; cc -c cFile1.c

cFileDir/cFile2.o : cFileDir/cFile2.c
	cd cFileDir; cc -c cFile2.c

cFileDir/cFile3.o : cFileDir/cFile3.c
	cd cFileDir; cc -c cFile3.c

#################################################################################

.PHONY : cscope
cscope :
	cd mainDir; cscope -Rbq -I ../hFileDir

.PHONY : clean
clean :
	@echo 'clean up redundant files..'
	@rm -f cscope.* c1 *.o *.i *.s
	@cd mainDir; rm -f *.o *.i *.s cscope.*
	@cd cFileDir; rm -f *.o *.i *.s
	@cd hFileDir; rm -f *.o *.i *.s
	@echo 'Done.'

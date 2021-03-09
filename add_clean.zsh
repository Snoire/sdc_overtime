#! /bin/zsh
# add clean target in Makefile

echo "==============="
cd $1
pwd
echo "clean :\n\t-rm -f *.o *~ cscope* c${1[3,4]}" >> Makefile

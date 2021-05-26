.PHONY : all clean
a_objects := a.o b.o c.o
1_objects := 1.o 2.o 3.o

a1 := 1
sources := $($(a1)_objects:.o=)

# 输出到系统环境变量，传递给子 make 或 子 shell
export MAKE_VAR = HI
# 系统环境变量可以被覆盖，命令行带进来的变量不行，得用 override
#SCREENDIR = all

echo :
	@echo $(sources)
	@# 继承系统环境变量（用 env 查看）
	@echo 'SCREENDIR = $(SCREENDIR)'
	./echo_var.sh

comma:= ,
empty:=
space:= $(empty) $(empty)
foo:= a b c
bar:= $(subst $(space),$(comma),$(foo))

foo1 := a b c
# 这样写和预期的不一样
bar1:= $(subst $(space),,,$(foo1))

func :
	@echo $(bar)
	@echo $(bar1)

sub :
	make -C sub1 sub

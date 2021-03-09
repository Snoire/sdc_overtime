all : hi
.PHONY : all

hi : main.o compile_dir/hello/libhello.so
	cc -o hi main.o -lhello -L compile_dir/hello -Wl,-rpath-link=compile_dir/world,-rpath=linker_dir/hello
	mv -f compile_dir/hello/libhello.so linker_dir/hello
	mv -f compile_dir/world/libworld.so linker_dir/world
	rm -f *.o

compile_dir/hello/libhello.so : hello.o compile_dir/world/libworld.so
	cc -shared -o libhello.so hello.o -lworld -L compile_dir/world -Wl,-rpath=linker_dir/world
	mv libhello.so compile_dir/hello/

compile_dir/world/libworld.so : world.o
	cc -shared -o libworld.so world.o
	mv libworld.so compile_dir/world/

clean:
	rm -f *.so *.o hi compile_dir/hello/* compile_dir/world/* linker_dir/hello/* linker_dir/world/*


#说明：
#编译时链接库需要分为两类： 直接引用 间接引用
#直接引用 被源码中直接调用的库
#间接引用 被调用库的依赖库
#
#-lxxx 指定具体的库名称，编译时需要显式指定直接引用的库名称
#-L 指定链接库的位置，编译时需要显式指定直接引用的库位置
#-Wl,-rpath-link ，用于编译时指定间接引用的库位置
#如果知道所有间接引用的库文件名称，并且不嫌麻烦，也可以用-lxxx显式指定每一个库（不推荐-lxxx）
#-Wl,-rpath ，有两个作用：
#1. 用于编译时指定间接引用的库位置，作用同-Wl,-rpath-link
#2. 用于运行时指定直接引用库的位置，作用同修改环境变量(LD_LIBRARY_PATH),并且库路径引用优先级高于LD_LIBRARY_PATH
#
#使用建议
#1. 编译命令中使用-Wl,-rpath-link 指定间接引用库位置(编译时)，使用-Wl,-rpath 指定引用库位置（运行时）
#2. -Wl,-rpath-link 在 -Wl,-rpath 前
#
#重要：
#在加载间接引用的库的时候，不会去当前程序的 Library runpath 查找
#也就是说在编译程序时，用 -rpath 指定运行时间接引用的库位置是不行的
#方法：
#1. 运行程序前使用环境变量 LD_LIBRARY_PATH=xxxx 指定库加载路径（间接引用的库在里面）（不推荐）
#LD_LIBRARY_PATH=./lib bin/autoover
#2. 对直接引用的库，设置 rpath 用于查找间接引用的库（可能有多级间接）
#3. 将间接引用的库所在的目录路径添加到 /etc/ld.so.conf 中，并使用 ldconfig 更新下 /etc/ld.so.cache （推荐）
#4. 将间接引用的库，添加到程序的依赖列表里面去
#patchelf --add-needed libproj.so.20 bin/autoover
#5. 库全部放在 /lib 和 /usr/lib 下 （这个也可以）
#
#-path 指定的路径最好用绝对路径
#也可以用相对路径，但是，
#这个相对路径不是相对于生成的库来说（软链接是这样的）
#而是相对于“你”的位置。。
#也就是说，你处于不同的路径，它依赖的库就找不到了。。
#不信你换个路径再执行生成的 hi 程序试试


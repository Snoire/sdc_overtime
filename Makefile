# Makefile to build all programs in all subdirectories
#
# DIRS is a list of all subdirectories containing makefiles
# It should be noted that the brackets contained in the filename should be escaped
#
# using the following method to add subdirectories:
# ar=(*(/))
# print -lr ${(q)ar}

DIRS = asm \
c001-递归解决分鱼问题 \
c002-递归解决年龄问题 \
c003-printf转义 \
c004-二维数组指针 \
c005-\(字符\)数组与指针 \
c006-snprintf \
c007-sprintf_snprintf \
c008-getopt \
c010-字符串与指针与段错误 \
c011-NULL和空字符串的值是否为0 \
c012-前自增后自增 \
c013-copy_from_stdin_to_stdout \
c014-实现more的功能 \
c015-字符串与printf \
c016-自定义bool类型 \
c017-注释版权 \
c018-判断字符串是否为纯数字 \
c019-overtime \
c020-通讯录 \
c021-scanf-usage \
c022-当前时间 \
c023-判断指定日期为周几 \
c024-判断一月有几天 \
c025-文件读写 \
c026-strcpy \
c027-捕获换行-fgets-scanf用法 \
c028-验证字符串是否合法 \
c029-打印彩色字符 \
c030-静态数据区只能初始化一次 \
c031-链表 \
c032-静态链表 \
c033-进制转换器_栈 \
c034-合并字符串_堆 \
c035-KMP \
c036-输入不定长字符串 \
c037-Ctrl+d \
c038-sizeof\(p\) \
c039-strchr解析 \
c040-a=a++ \
c041-environ \
c042-fileIO \
c043-stdarg \
c044-process-argv \
c045-users-groups \
c046-setuid-and-others \
c047-system-limits \
c048-debv-key-value_pair_file_parsing \
c049-缓冲区 \
c050-file-metadata \
c051-dirs_links \
c052-宏定义指定scanf输入字符长度 \
c053-inotify \
c054-结构体的内存分布 \
c055-signal \
c056-fork \
c057-on_exit \
c058-waitpid \
c059-threads \
c060-2的1000000次方 \
c061-进度条 \
c062-sizeof字符串指针 \
c063-test \
c064-函数指针 \
c065-scanf格式字符串中普通字符 \
c066-按位置0或1 \
c068-unsigned_char \
c069-ioctl-if \
c070-clock \
c071-read_last_line \
c072-segmentation_fault \
c073-float_double \
c074-fopen_textmode \
c075-format_of_printf \
c076-fmemopen \
c077-get_ipv6_prefix \
c078-rpath \
c079-ether_aton \
c080-结构体里的成员数组和指针 \
c081-callback_func \
c082-Makefile \
c084-gnu_c \
c085-socket \
c086-mmap \
c087-FIFO \
c088-signal

#c009 \
#c067-两头文件中包含同一个变量定义 \
#c083-link


BUILD_DIRS = ${DIRS}


# Dummy targets for building everything in all subdirectories

all: 	
	@ for dir in ${BUILD_DIRS}; do \
		echo "---------------------------------------------------------"; \
		echo  "\033[;36m                $$dir                \033[;0m"; \
		echo "---------------------------------------------------------"; \
		(cd $${dir}; ${MAKE}) ; \
		if test $$? -ne 0; then break; fi; \
	done

echo: 
	@ for dir in ${BUILD_DIRS}; do echo $${dir}; done

clean: 
	@ for dir in ${BUILD_DIRS}; do \
		(cd $${dir}; ${MAKE} clean) ;\
		if test $$? -ne 0; then ./add_clean.zsh $${dir}; fi; \
	done

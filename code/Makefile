CROSS_COMPILE = # 交叉编译工具头,如：arm-linux-gnueabihf-
#AS      = $(CROSS_COMPILE)as # 把汇编文件生成目标文件
LD      = $(CROSS_COMPILE)ld # 链接器，为前面生成的目标代码分配地址空间，将多个目标文件链接成一个库或者一个可执行文件
CC      = $(CROSS_COMPILE)g++ # 编译器，对 C 源文件进行编译处理，生成汇编文件
#CPP    = $(CC) -E
#AR      = $(CROSS_COMPILE)ar # 打包器，用于库操作，可以通过该工具从一个库中删除或则增加目标代码模块
#NM     = $(CROSS_COMPILE)nm # 查看静态库文件中的符号表

#STRIP       = $(CROSS_COMPILE)strip # 以最终生成的可执行文件或者库文件作为输入，然后消除掉其中的源码
#OBJCOPY  = $(CROSS_COMPILE)objcopy # 复制一个目标文件的内容到另一个文件中，可用于不同源文件之间的格式转换
#OBJDUMP = $(CROSS_COMPILE)objdump # 查看静态库或则动态库的签名方法

# 共享到sub-Makefile
#export AS LD CC CPP AR NM
#export STRIP OBJCOPY OBJDUMP
export CC

# -Wall ： 允许发出 GCC 提供的所有有用的报警信息
# -O2 : “-On”优化等级
# -g : 在可执行程序中包含标准调试信息
# -I : 指定头文件路径（可多个）
CFLAGS := -Wall -O2 -g -lpthread -lmysql 
CFLAGS += -I $(shell pwd)/include

# LDFLAGS是告诉链接器从哪里寻找库文件，这在本Makefile是链接最后应用程序时的链接选项。
#LDFLAGS := /usr/lib/gcc/x86_64-linux-gnu/9/collect2 -plugin /usr/lib/gcc/x86_64-linux-gnu/9/liblto_plugin.so -plugin-opt=/usr/lib/gcc/x86_64-linux-gnu/9/lto-wrapper -plugin-opt=-fresolution=/tmp/ccsLIo7x.res -plugin-opt=-pass-through=-lgcc_s -plugin-opt=-pass-through=-lgcc -plugin-opt=-pass-through=-lc -plugin-opt=-pass-through=-lgcc_s -plugin-opt=-pass-through=-lgcc --build-id --eh-frame-hdr -m elf_x86_64 --hash-style=gnu --as-needed -dynamic-linker /lib64/ld-linux-x86-64.so.2 -pie -z now -z relro /usr/lib/gcc/x86_64-linux-gnu/9/../../../x86_64-linux-gnu/Scrt1.o /usr/lib/gcc/x86_64-linux-gnu/9/../../../x86_64-linux-gnu/crti.o /usr/lib/gcc/x86_64-linux-gnu/9/crtbeginS.o -L/usr/lib/gcc/x86_64-linux-gnu/9 -L/usr/lib/gcc/x86_64-linux-gnu/9/../../../x86_64-linux-gnu -L/usr/lib/gcc/x86_64-linux-gnu/9/../../../../lib -L/lib/x86_64-linux-gnu -L/lib/../lib -L/usr/lib/x86_64-linux-gnu -L/usr/lib/../lib -L/usr/lib/gcc/x86_64-linux-gnu/9/../../.. -lstdc++ -lm -lgcc_s -lgcc -lc -lgcc_s -lgcc

LDFLAGS := 

# 共享到sub-Makefile
export CFLAGS LDFLAGS

# 顶层路径
TOPDIR := $(shell pwd)
export TOPDIR

# 最终目标
TARGET := test

# 本次整个编译需要源 文件 和 目录
# 这里的“obj-y”是自己定义的一个格式，和“STRIP”这些一样，*但是 一般内核会搜集 ”obj-”的变量*
#obj-y += main.o # 需要把当前目录下的 main.c 编进程序里
#obj-y += sub.o # 需要把当前目录下的 sub.c 编进程序里
obj-y += buffer/
obj-y += http/
obj-y += log/
obj-y += MD5/
obj-y += pool/
obj-y += server/
obj-y += timer/
obj-y += main.o
#obj-y += $(patsubst %.c,%.o,$(shell ls *.c))

# 第一个目标
all : start_recursive_build $(TARGET)
	@echo $(TARGET) has been built !
    
# 处理第一个依赖，转到 Makefile.build 执行
start_recursive_build:
	make -C ./ -f $(TOPDIR)/Makefile.build

    
# 处理最终目标，把前期处理得出的 built-in.o 用上
$(TARGET) : built-in.o
	$(CC) -o $(TARGET) built-in.o $(LDFLAGS)
    
# 清理
clean:
	rm -f $(shell find -name "*.o")
	rm -f $(TARGET)
    
# 彻底清理
distclean:
	rm -f $(shell find -name "*.o")
	rm -f $(shell find -name "*.d")
	rm -f $(TARGET)

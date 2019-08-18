# originating https://github.com/TheNetAdmin/Makefile-Templates
# tool marcros

# CC：编译器
CC := gcc
# AR:库链接器
AR := ar
#GCC编译的时候使用的选项*******************************************************************************************************
#1） -c ：指编译，不链接，生成目标文件“.o”。
#2） -S ：只编译，不汇编，生成汇编代码“.S”。
#3） -E ：只进行预编译/预处理，不做其他处理。
#4） -o file：把输出文件输出到file里。
#5） -g ：在可执行程序中包含标准调试信息。
#6） -v ：打印出编译器内部编译各过程的命令行信息和编译器的版本。
#7） -I dir ：在头文件的搜索路径列表中添加dir目录
#8） -L dir ：在库文件的搜索路径列表中添加dir目录
#9） -static ：连接静态库（静态库也可以用动态库链接方式链接）
#10） -llibrary ：连接名为library的库文件（显示指定需要链接的动态库文件）
#-std=c11： c语言标准 c89、c99、c11，c++11、c++14、c++14；
#-fexec-charset=GBK: 指定目标文件的编码格式为GBK（UTF-8）;
#-finput-charset=UTF-8： 指定源文件的编码格式为UTF-8;

#2、gcc告警和出错选项
#1） -ansi ：支持符合ANSI标准的C程序
#2） -pedantic ：允许发出ANSI C标准所列出的全部警告信息
#3） -pedantic-error ：允许发出ANSI C标准所列出的全部错误信息
#4） -w ：关闭所有警告
#5） -Wall ：允许发出gcc提供的所有有用的报警信息
#6） -werror ：把所有的告警信息转化为错误信息，并在告警发生时终止编译过程
#编译的时候使用的选项*******************************************************************************************************
CCFLAG := -Wall -std=c11 -fexec-charset=GBK
DBGFLAG := -g 
CCOBJFLAG := $(CCFLAG) -c

# ar库链接命令的选项和参数*******************************************************************************************************
#操作选项
#d：从库中删除模块。按模块原来的文件名指定要删除的模块。如果使用了任选项v则列出被删除的每个模块。
#m：该操作是在一个库中移动成员。当库中如果有若干模块有相同的符号定义(如函数定义)，则成员的位置顺序很重要。如果没有指定任选项，任何指定的成员将 移到库的最后。也可以使用'a'，'b'，或'I'任选项移动到指定的位置。
#p：显示库中指定的成员到标准输出。如果指定任选项v，则在输出成员的内容前，将显示成员的名字。如果没有指定成员的名字，所有库中的文件将显示出来。
#q：快速追加。增加新模块到库的结尾处。并不检查是否需要替换。'a'，'b'，或'I'任选项对此操作没有影响，模块总是追加的库的结尾处。如果使用了 任选项v则列出每个模块。 这时，库的符号表没有更新，可以用'ar s'或ranlib来更新库的符号表索引。
#r：在库中插入模块(替换)。当插入的模块名已经在库中存在，则替换同名的模块。如果若干模块中有一个模块在库中不存在，ar显示一个错误消息，并不替换 其他同名模块。默认的情况下，新的成员增加在库的结尾处，可以使用其他任选项来改变增加的位置。
#t：显示库的模块表清单。一般只显示模块名。
#x：从库中提取一个成员。如果不指定要提取的模块，则提取库中所有的模块。

#可与操作选项结合使用的任选项：
#a：在库的一个已经存在的成员后面增加一个新的文件。如果使用任选项a，则应该为命令行中membername参数指定一个已经存在的成员名。
#b：在库的一个已经存在的成员前面增加一个新的文件。如果使用任选项b，则应该为命令行中membername参数指定一个已经存在的成员名。
#c：创建一个库。不管库是否存在，都将创建。
#f：在库中截短指定的名字。缺省情况下，文件名的长度是不受限制的，可以使用此参数将文件名截短，以保证与其它系统的兼容。
#i：在库的一个已经存在的成员前面增加一个新的文件。如果使用任选项i，则应该为命令行中membername参数指定一个已经存在的成员名(类似任选项 b)。
#l：暂未使用
#N：与count参数一起使用，在库中有多个相同的文件名时指定提取或输出的个数。
#o：当提取成员时，保留成员的原始数据。如果不指定该任选项，则提取出的模块的时间将标为提取出的时间。
#P：进行文件名匹配时使用全路径名。ar在创建库时不能使用全路径名（这样的库文件不符合POSIX标准），但是有些工具可以。
#s：写入一个目标文件索引到库中，或者更新一个存在的目标文件索引。甚至对于没有任何变化的库也作该动作。对一个库做ar s等同于对该库做ranlib。
#S：不创建目标文件索引，这在创建较大的库时能加快时间。
#u：一般说来，命令ar r...插入所有列出的文件到库中，如果你只想插入列出文件中那些比库中同名文件新的文件，就可以使用该任选项。该任选项只用于r操作选项。
#v：该选项用来显示执行操作选项的附加信息。
#V：显示ar的版本.

#示例
#格式：ar rcs  libxxx.a xx1.o xx2.o
#参数r：在库中插入模块(替换)。当插入的模块名已经在库中存在，则替换同名的模块。如果若干模块中有一个模块在库中不存在，ar显示一个错误消息，并不替换其他同名模块。默认的情况下，新的成员增加在库的结尾处，可以使用其他任选项来改变增加的位置。【1】
#参数c：创建一个库。不管库是否存在，都将创建。
#参数s：创建目标文件索引，这在创建较大的库时能加快时间。（补充：如果不需要创建索引，可改成大写S参数；如果.a文件缺少索引，可以使用ranlib命令添加）

#格式：ar t libxxx.a
#显示库文件中有哪些目标文件，只显示名称。

#格式：ar tv libxxx.a
#显示库文件中有哪些目标文件，显示文件名、时间、大小等详细信息。

#格式：nm -s libxxx.a
#显示库文件中的索引表。

#格式：ranlib libxxx.a
#为库文件创建索引表。
# ar库链接命令的选项和参数*******************************************************************************************************
ARFLAG := -rcs

# path marcros
BIN_PATH := bin
OBJ_PATH := obj
SRC_PATH := src
DBG_PATH := debug
INCLUDE_PATH := ./
LIB_PATH := 

#include marcros
INCLUDE := MyGraph.h
LIB:= 

# compile marcros
TARGET_NAME := libMyGraph.a
DEBUG_NAME  := main.exe
TARGET := $(BIN_PATH)/$(TARGET_NAME)
TARGET_DEBUG := $(DBG_PATH)/$(DEBUG_NAME)
#定义main函数所在的源文件
MAIN_SRC := src/main.c

# src files & obj files
DB_SRC := $(foreach x, $(SRC_PATH), $(wildcard $(addprefix $(x)/*,.c*)))
BIN_SRC := $(filter-out $(MAIN_SRC),$(DB_SRC))
OBJ := $(addprefix $(OBJ_PATH)/, $(addsuffix .o, $(notdir $(basename $(BIN_SRC)))))
OBJ_DEBUG := $(addprefix $(DBG_PATH)/, $(addsuffix .o, $(notdir $(basename $(DB_SRC)))))

# clean files list
DISTCLEAN_LIST := $(OBJ) \
                  $(OBJ_DEBUG)
CLEAN_LIST := $(TARGET) \
			  $(TARGET_DEBUG) \
			  $(DISTCLEAN_LIST)

# default rule
default: all

# non-phony targets
$(TARGET): $(OBJ)
	$(AR) $(ARFLAG) $@ $^ 

#自己在后面添加依赖的头文件
$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c* 
	$(CC) $(CCOBJFLAG) -o $@ $< 

$(DBG_PATH)/%.o: $(SRC_PATH)/%.c* 
	$(CC) $(CCOBJFLAG) $(DBGFLAG) -o $@ $< 

$(TARGET_DEBUG): $(OBJ_DEBUG) 
	$(CC) $(CCFLAG) $(DBGFLAG) $^ -o $@ 

# phony rules
.PHONY: all
all: $(TARGET)

.PHONY: debug
debug: $(TARGET_DEBUG)

.PHONY: clean
clean:
	@echo CLEAN $(CLEAN_LIST)
	@del $(BIN_PATH)\*.a
	@del $(DBG_PATH)\*.exe
	@del $(OBJ_PATH)\*.o
	@del $(DBG_PATH)\*.o


.PHONY: distclean
distclean:
	@echo CLEAN $(CLEAN_LIST)
	@del $(OBJ_PATH)\*.o
	@del $(DBG_PATH)\*.o
	@del $(DBG_PATH)\*.exe
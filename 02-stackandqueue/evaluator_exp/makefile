# originating https://github.com/TheNetAdmin/Makefile-Templates
# tool marcros

# CC：编译器
CC := gcc
#编译的时候使用的选项****************************************
#-c: 只编译不链接
#-Wall： 开启额外警告
#-g: 表示生成调试信息；
#-I （Dictionary：自定义头文件目录）:指定自定义头文件搜索目录；
#-std=c11： c语言标准 c89、c99、c11，c++11、c++14、c++14；
#-fexec-charset=GBK: 指定目标文件的编码格式为GBK（UTF-8）;
#-finput-charset=UTF-8： 指定源文件的编码格式为UTF-8;
CCFLAG := -Wall -std=c11 -fexec-charset=GBK -static-libgcc
DBGFLAG := -g 
CCOBJFLAG := $(CCFLAG) -c
#编译的时候使用的选项****************************************

# path marcros
BIN_PATH := bin
OBJ_PATH := obj
SRC_PATH := src
DBG_PATH := debug
INCLUDE_PATH := ..\..\00-Mylib\include
LIB_PATH := ..\..\00-Mylib\bin
# compile marcros
TARGET_NAME := main
ifeq ($(OS),Windows_NT)
	TARGET_NAME := $(addsuffix .exe,$(TARGET_NAME))
endif
TARGET := $(BIN_PATH)/$(TARGET_NAME)
TARGET_DEBUG := $(DBG_PATH)/$(TARGET_NAME)
#定义main函数所在的源文件
MAIN_SRC := src/main.c
INCLUDE := StackAndQueue.h
LIB := StackAndQueue

# src files & obj files
SRC := $(foreach x, $(SRC_PATH), $(wildcard $(addprefix $(x)/*,.c*)))
OBJ := $(addprefix $(OBJ_PATH)/, $(addsuffix .o, $(notdir $(basename $(SRC)))))
OBJ_DEBUG := $(addprefix $(DBG_PATH)/, $(addsuffix .o, $(notdir $(basename $(SRC)))))

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
	$(CC) $(CCFLAG) -o $@ $^ -L $(LIB_PATH) -l&(LIB)

#自己在后面添加依赖的头文件
$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c* $(INCLUDE_PATH)/$(INCLUDE)
	$(CC) $(CCOBJFLAG) -o $@ $< -I $(INCLUDE_PATH)

$(DBG_PATH)/%.o: $(SRC_PATH)/%.c* $(INCLUDE_PATH)/$(INCLUDE)
	$(CC) $(CCOBJFLAG) $(DBGFLAG) -o $@ $< -I $(INCLUDE_PATH)

$(TARGET_DEBUG): $(OBJ_DEBUG)
	$(CC) $(CCFLAG) $(DBGFLAG) $^ -o $@ -L $(LIB_PATH) -l$(LIB)

# phony rules
.PHONY: all
all: $(TARGET)

.PHONY: debug
debug: $(TARGET_DEBUG)

.PHONY: clean
clean:
	@echo CLEAN $(CLEAN_LIST)
	@del $(BIN_PATH)\*.exe
	@del $(DBG_PATH)\*.exe
	@del $(OBJ_PATH)\*.o
	@del $(DBG_PATH)\*.o


.PHONY: distclean
distclean:
	@echo CLEAN $(CLEAN_LIST)
	@del $(OBJ_PATH)\*.o
	@del $(DBG_PATH)\*.o
	@del $(DBG_PATH)\*.exe
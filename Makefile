# filename: Makefile
# author: H.M.Yang,(hmyang07@gmail.com)
# date: Sun Apr 12 CST 2015
# .
# ├── a.out
# ├── doc
# │   └── README
# ├── inc
# │   └── apue.h
# ├── lib
# │   ├── filetype.c
# │   ├── libapue.a
# │   ├── Makefile.am
# │   ├── Makefile.in
# │   └── myaccess.c
# ├── ls.c
# ├── Makefile
# ├── output
# │   └── ls.o
# └── src
#     ├── chmod.cpp
#     ├── chown.cpp
#     ├── main.cpp
#     ├── readlink_example.cpp
#     ├── rename.cpp
#     ├── symlink.cpp
#     ├── umask.cpp
#     ├── unlinked.cpp
#     └── utime.cpp
# 
# 5 directories, 20 files
# 
# 
EXEC   := a.out

OBJDIR := output
SRCDIR := src
INCDIR := inc
LIBDIR := lib 

LIBS   := apue 

# VPATH := src
vpath %.c $(SRCDIR)
vpath %.h $(INCDIR)

CFLAGS := -Wall -O1 -g
CFLAGS += $(addprefix -I, $(INCDIR)) 

LDFLAFS := $(addprefix -L,$(LIBDIR))
LDFLAFS += $(addprefix -l,$(LIBS))

CC     := gcc
SRC    := $(wildcard *.c) $(wildcard $(SRCDIR)/*.c)
OBJS   := $(patsubst %.c,$(OBJDIR)/%.o,$(notdir $(SRC)))

# ALL:
# 	@echo $(SRC)
# 	@echo $(OBJS)

# vpath <pattern> <directories> # 为符号模式<pattern>的文件指定搜索目录<directories>
# vpath <pattern> # 清除符合模式<pattern>的文件的搜索目录
# vpath # 清除所有已被设置好的文件搜索目录


$(EXEC):$(OBJS)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAFS)
$(OBJDIR)/%.o:$(SRC)
	$(CC) -c -o $@ $< $(CFLAGS) $(LDFLAFS)



.PHONY : clean move
clean:
	rm $(OBJDIR)/*.o $(EXEC)
move:
	find . -maxdepth 1 -type f -name "*.c" | \
		xargs -n1 -i{} mv {} $(SRCDIR)/{}pp 

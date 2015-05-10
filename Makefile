# ####################################################
# Generic makefile
# for compiling and linking C++ projects on Linux 
# Author: George Foot  Modified:Jackie Lee
# ####################################################
#
# Usage:
# $ make 			compile and link the program
# $ make objs 		compile only (no linking, Rarel used)
# $ make clean  	clean the objectives and dependencies
# $ make cleanall 	clean the objectives, dependencies and executable
# $ make rebuild 	rebuild the program. The same as make clean && make all 
# $ make deps 		compile only,generate the dependencies
# $ make info 		check some information and debug
# 
# ### Customising
# #
# # Adjust the following if necessary; EXECUTABLE is the target
# # executable's filename, and LIBS is a list of libraries to link in
# # (e.g. alleg, stdcx, iostr, etc). You can override these on make's
# # command line of course, if you prefer to do it that way.
# #
# #
# 可执行文件名
EXECUTABLE := a.out       		
# 静态库目录
LIBDIR     := 				    
# 静态库文件名
LIBS       :=					
# 头文件目录
INCLUDES   := inc 			    
# 除了当前目录外，其他的源代码文件目录
SRCDIR     := src 			    
# 生成的.o和.d文件输出目录
OBJSDIR    := output 		    
# #
# # # Now alter any implicit rules' variables if you like, e.g.:
#
CC       := g++
CFLAGS   := -g -Wall -O3
CPPFLAGS := $(CFLAGS)
CPPFLAGS += $(addprefix -I,$(INCLUDES))
CPPFLAGS += -MMD
#
# # The next bit checks to see whether rm is in your djgpp bin
# # directory; if not it uses del instead, but this can cause (harmless)
# # `File not found' error messages. If you are not using DOS at all,
# # set the variable to something which will unquestioningly remove
# # files.
#
# ifneq ($(wildcard $(DJDIR)/bin/rm.exe),)
# RM-F := rm -f
# else
# RM-F := del
# endif

RM-F := rm -f


# # You shouldn't need to change anything below this point.
#
# SRCS := $(wildcard *.cc) $(wildcard $(addsuffix /*.cc, $(SRCDIR)))
SRCS := $(wildcard *.cc) 
OBJS := $(patsubst %.cc,%.o,$(SRCS))
DEPS := $(patsubst %.o,%.d,$(OBJS))
MISSING_DEPS := $(filter-out $(wildcard $(DEPS)),$(DEPS))
MISSING_DEPS_SOURCES := $(wildcard $(patsubst %.d,%.cc,$(MISSING_DEPS)))


.PHONY : all deps objs clean cleanall rebuild info

all: $(EXECUTABLE)

deps : $(DEPS)

objs : $(OBJS)

clean :
	@$(RM-F) *.o
	@$(RM-F) *.d
cleanall: clean
	@$(RM-F) $(EXECUTABLE)

rebuild: cleanall all
ifneq ($(MISSING_DEPS),)
$(MISSING_DEPS) :
	@$(RM-F) $(patsubst %.d,%.o,$@)
endif
-include $(DEPS)
$(EXECUTABLE) : $(OBJS)
	$(CC) -o $(EXECUTABLE) $(OBJS) \
		$(addprefix -L,$(LIBDIR)) $(addprefix -l,$(LIBS))

# 隐含规则
# $(EXECUTABLE)依赖于$(OBJS)，但makefile中没有指明$(OBJS)依赖于谁，也没指明命令生成它们；
#
# 这时，make的隐含规则开始起作用；针对$(OBJS)中的每个目标，make自动调用：
#
# $(CC) $(CFLAGS) $(CPPFLAGS) $(TARGET_ARCH) -c $< -o $@ 
#
# 依次生成.o文件和.d文件；
#
# $<表示依赖文件列表的第一个文件名；
#
# $@表示目标文件名；
#
# 之所以会生成.d文件，是由于“-MMD”这一编译选项。为g++加上这一选项后，编译器会生成文件依赖信息，并存放至.d文件中。
#
# 每一个.cpp文件相应地生成一个.d文件和一个.o文件。
info:
	@echo $(SRCS)
	@echo $(OBJS)
	@echo $(DEPS)
	@echo $(MISSING_DEPS)
	@echo $(MISSING_DEPS_SOURCES)

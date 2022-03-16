###### EXEC NAME ######
NAME = ft.out
NAME_STD = std.out
NAME_CATCH = catch.out
NAME_FSANITIZE = fsanitize.out
NAME_EXTREME = ft_extreme.out
NAME_STD_EXTREME = std_extreme.out
EXECS = $(NAME) $(NAME_STD) $(NAME_CATCH) $(NAME_FSANITIZE) $(NAME_EXTREME) $(NAME_STD_EXTREME)

CPP = clang++

###### SANITIZE_FLAG ######
ifeq ($(shell uname),Darwin)
	SANITIZE_FLAG = -O0 -g3 -fsanitize=address
else
	SANITIZE_FLAG = -O0 -g3 -fsanitize=address -fsanitize=leak
endif

###### CFLAG ######
CFLAG = -Wall -Wextra -Werror -pedantic 
#CFLAG += -Wno-unused-variable -Wno-unused-parameter -Wno-unused-function -Wno-unused-local-typedef
ifdef CATCH
	CFLAG += -std=c++17
else
	CFLAG += -std=c++98
endif

# Note: settings related to MODE: 1) CFLAG -D; 2) NAME; 3) SUB_DIR_OBJ and SUB_DIR_DEP;
###### FSANITIZE MODE ######
ifdef FSANITIZE
	CFLAG += $(SANITIZE_FLAG)
	CFLAG += -DFSANITIZE
	NAME = $(NAME_FSANITIZE)
	SUBDIR_OBJ = /obj_fsanitize
	SUBDIR_DEP = /dep_fsanitize
endif

###### CATCH MODE ######
ifdef CATCH
	CFLAG += -DCATCH
	NAME = $(NAME_CATCH)
	SUBDIR_OBJ = /obj_catch
	SUBDIR_DEP = /dep_catch
endif

###### STD MODE ######
ifdef STANDARD
	CFLAG += -DSTANDARD
	NAME = $(NAME_STD)
	SUBDIR_OBJ = /obj_std
	SUBDIR_DEP = /dep_std
endif

###### EXTREME MODE ######
ifdef EXTREME
	CFLAG += -DEXTREME
ifdef STANDARD
	NAME = $(NAME_STD_EXTREME)
	SUBDIR_OBJ = /obj_std_extreme
	SUBDIR_DEP = /dep_std_extreme
else
	NAME = $(NAME_EXTREME)
	SUBDIR_OBJ = /obj_extreme
	SUBDIR_DEP = /dep_extreme
endif
endif

###### DIR & FILES######
DIR_SRC := src
DIR_OBJ := obj$(SUBDIR_OBJ)
DIR_DEP := dep$(SUBDIR_DEP)

ifdef CATCH
	DIR_COMPILE := $(DIR_SRC)
else
	DIR_COMPILE := $(DIR_SRC)/src_project
endif

SRC := $(shell find $(DIR_COMPILE) -type f -name "*.cpp")
OBJ := $(patsubst $(DIR_SRC)/%.cpp,$(DIR_OBJ)/%.o,$(SRC))
DEP := $(patsubst $(DIR_SRC)/%.cpp,$(DIR_DEP)/%.d,$(SRC))

###### compilation ######
all:
	@$(MAKE) $(NAME)

$(NAME): $(OBJ)
	$(CPP) $(CFLAG) -o $@ $^

$(OBJ): $(DIR_OBJ)/%.o: $(DIR_SRC)/%.cpp Makefile
	@mkdir -p $(@D)
	$(CPP) -c -o $@ $< $(CFLAG)
	
$(DIR_DEP)/%.d: $(DIR_SRC)/%.cpp
	@mkdir -p $(@D)
	$(CPP) $< -MM -MF $@ -MT $(DIR_OBJ)/$*.o $(CFLAG)

-include $(DEP)

standard:
	@$(MAKE) all STANDARD=1

fsanitize:
	@$(MAKE) all FSANITIZE=1

catch:
	@$(MAKE) all CATCH=1

extreme:
	@$(MAKE) all EXTREME=1

standard_extreme:
	@$(MAKE) all STANDARD=1 EXTREME=1

###### clean ######
clean:
	rm -rf $(DIR_OBJ) $(DIR_DEP)

fclean: clean
	rm -f $(EXECS) *.log

re: fclean all

.PHONY: all clean fclean re fsanitize standard

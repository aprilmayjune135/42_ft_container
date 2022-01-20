###### EXEC NAME ######
NAME = a.out
NAME_CATCH = catch.out
NAME_FSANITIZE = fsanitize.out
EXECS = $(NAME) $(NAME_CATCH) $(NAME_FSANITIZE)

CPP = clang++

###### SANITIZE_FLAG ######
ifeq ($(shell uname),Darwin)
	SANITIZE_FLAG = -O0 -g3 -fsanitize=address
else
	SANITIZE_FLAG = -O0 -g3 -fsanitize=address -fsanitize=leak
endif

###### CFLAG ######
CFLAG = -Wall -Wextra -Werror -pedantic 
CFLAG += -Wno-unused-variable -Wno-unused-parameter -Wno-unused-function
ifdef CATCH
	CFLAG += -std=c++17 -DCATCH
else
	CFLAG += -std=c++98
endif

###### FSANITIZE MODE ######
ifdef FSANITIZE
	NAME = $(NAME_FSANITIZE)
	CFLAG += $(SANITIZE_FLAG)
	SUBDIR_OBJ = /obj_fsanitize
	SUBDIR_DEP = /dep_fsanitize
endif

###### CATCH MODE ######
ifdef CATCH
	NAME = $(NAME_CATCH)
	SUBDIR_OBJ = /obj_catch
	SUBDIR_DEP = /dep_catch
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
all: $(NAME)

$(NAME): $(OBJ)
	$(CPP) $(CFLAG) -o $@ $^

$(OBJ): $(DIR_OBJ)/%.o: $(DIR_SRC)/%.cpp Makefile
	@mkdir -p $(@D)
	$(CPP) -c -o $@ $< $(CFLAG)
	
$(DIR_DEP)/%.d: $(DIR_SRC)/%.cpp
	@mkdir -p $(@D)
	$(CPP) $< -MM -MF $@ -MT $(DIR_OBJ)/$*.o $(CFLAG)

-include $(DEP)

fsanitize:
	$(MAKE) all FSANITIZE=1

catch:
	$(MAKE) all CATCH=1

###### clean ######
clean:
	rm -rf $(DIR_OBJ) $(DIR_DEP)

fclean: clean
	rm -f $(EXECS)

re: fclean all

.PHONY: all clean fclean re fsanitize

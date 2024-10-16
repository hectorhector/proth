CC = gcc
COMPILER_FLAGS = -Wall

CSRC = proth.c

ifeq ($(debug),1)
   COMPILER_FLAGS += -g
else
   COMPILER_FLAGS += -Werror -O2
endif

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lgmp -lpthread

#OBJ_NAME specifies the name of our exectuable
BIN_NAME = proth

#This is the target that compiles our executable
all : $(CSRC)
	$(CC) $(CSRC) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(BIN_NAME)

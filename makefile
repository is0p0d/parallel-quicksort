# 2023 Jim Moroney
# Look Dr. Rogers it even runs on M1!

uname_p := $(shell uname -p) # run uname to find architecture
$(info uname_p=$(uname_p))

ifeq ($(strip $(uname_p)),arm)
$(info makefile: arm64 detected, changing defaults)
CPP = /opt/homebrew/opt/llvm/bin/clang
CPPFLAGS = -I/opt/homebrew/opt/libomp/include -fopenmp
LDFLAGS = -L/opt/homebrew/opt/libomp/lib
else
$(info makefile: no arm64 detected, preserving defaults)
CPP = /usr/bin/gcc
CPPFLAGS = -lm -fopenmp
LDFLAGS = -lm -fopenmp
# leave defaults
endif

SRC_DIR := src
BIN_DIR := .

EXE := $(BIN_DIR)/quicksort
SRC := $(wildcard $(SRC_DIR)/*.c)
OBJ := $(SRC:$(SRC_DIR)/%.c=$(SRC_DIR)/%.o)
 
.PHONY: all # to prevent make from creating a direction named "all"

debug: CPPFLAGS += -g
debug: $(EXE)

$(EXE):$(OBJ)
	$(CPP) $^ -o $@ $(LDFLAGS)

para_quicksort.o: para_quicksort.c
	$(CPP) -c $(CPPFLAGS) $^



clean:
	$(RM) $(wildcard $(SRC_DIR)/*.o)
	$(RM) quicksort
LWD = $(shell pwd)
OBJ_DIR = $(LWD)/obj
SRC_DIR = $(LWD)/src
DATA_DIR = $(LWD)/data
BIN_DIR = $(LWD)/bin
INCLUDE_DIR = $(LWD)/include
COMMON_DIR = $(LWD)/common
TEST_DIR = $(LWD)/test


CC = g++
CFLAGS = -g -Wall -I$(INCLUDE_DIR)

COMMON_OBJS = 
DFA_SRC = $(SRC_DIR)/DFA.cpp

all: DFA_Simulator

common: $(COMMON_OBJS) $(COMMON_DIR)/include/common.h
	cd $(COMMON_DIR); make ; cd $(LWD)

DFA_Simulator: $(BIN_DIR)/DFA_Simulator

$(BIN_DIR)/DFA_Simulator: $(SRC_DIR)/DFA.cpp $(INCLUDE_DIR)/DFA.h
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(TEST_DIR)/DFA_Simulator.cpp $(DFA_SRC) -o $(BIN_DIR)/DFA_Simulator 

clean:
	rm -f $(BIN_DIR)/* $(OBJ_DIR)/*.o $(OBJ_DIR)/*.s $(OBJ_DIR)/*.i core

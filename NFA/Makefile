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
NFA_SRC = $(SRC_DIR)/NFA.cpp

all: NFA_Simulator

common: $(COMMON_OBJS) $(COMMON_DIR)/include/common.h
	cd $(COMMON_DIR); make ; cd $(LWD)

NFA_Simulator: $(BIN_DIR)/NFA_Simulator

$(BIN_DIR)/NFA_Simulator: $(TEST_DIR)/NFA_Simulator.cpp $(SRC_DIR)/NFA.cpp $(INCLUDE_DIR)/NFA.h
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(TEST_DIR)/NFA_Simulator.cpp $(NFA_SRC) -o $(BIN_DIR)/NFA_Simulator 

clean:
	rm -f $(BIN_DIR)/* $(OBJ_DIR)/*.o $(OBJ_DIR)/*.s $(OBJ_DIR)/*.i core

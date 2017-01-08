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
TM_SRC = $(SRC_DIR)/TM.cpp

all: TM_Simulator

common: $(COMMON_OBJS) $(COMMON_DIR)/include/common.h
	cd $(COMMON_DIR); make ; cd $(LWD)

TM_Simulator: $(BIN_DIR)/TM_Simulator

$(BIN_DIR)/TM_Simulator: $(TEST_DIR)/TM_Simulator.cpp $(SRC_DIR)/TM.cpp $(INCLUDE_DIR)/TM.h
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(TEST_DIR)/TM_Simulator.cpp $(TM_SRC) -o $(BIN_DIR)/TM_Simulator 

clean:
	rm -f $(BIN_DIR)/* $(OBJ_DIR)/*.o $(OBJ_DIR)/*.s $(OBJ_DIR)/*.i core

//
//  NFA.hpp
//  AlgoTests
//
//  Created by Jason Graalum on 12/16/16.
//  Copyright © 2016 Jason Graalum. All rights reserved.
//

#ifndef NFA_H_
#define NFA_H_

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

enum FSM_TYPE
{
	NFA_T,
	NNFA_T
};

class NFA
{
public:
	NFA();
    std::string name;
    int loadNFA(std::string);
    bool runNFA(std::string,unsigned int,int);
    unsigned int getStateIndexbyName(std::string);
    std::string getStateNamebyIndex(unsigned int);
    unsigned int getAlphaIndexbyName(std::string);
    std::string getAlphaNamebyIndex(unsigned int);
    std::vector<std::string> getNextSymbol(std::string);
    unsigned int getStartStateIndex();
    void printNFA();
    void printAlphabet();
    void printStates();
    void printStartState();
    void printAcceptStates();
    void printTransitionFunction();
    std::vector<unsigned int> getNextStates(unsigned int, unsigned int);
    std::vector<unsigned int> getEmptyTransitionStates(unsigned int);
    bool isAcceptedState(unsigned int);
    void setEmptyAlphaIndex(unsigned int);
    unsigned int getEmptyAlphaIndex();
    void setNullStateIndex(unsigned int);
    unsigned int getNullStateIndex();


private:
    FSM_TYPE machine_type; // 0 - NFA, 1 - NNFA
    std::vector<std::string> alphabet;
    unsigned int empty_alpha_index;
    std::vector<std::string> states;
    unsigned int null_state_index;
    std::vector<unsigned int> accept_states; // Indexes to states vector
    unsigned int start_state_index;
    std::vector< std::vector< std::vector<unsigned int> > > transition_table;
};

#endif /* NFA_H_ */


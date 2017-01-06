//
//  DFA.hpp
//  AlgoTests
//
//  Created by Jason Graalum on 12/16/16.
//  Copyright © 2016 Jason Graalum. All rights reserved.
//

#ifndef DFA_H_
#define DFA_H_

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

enum FSM_TYPE
{
	DFA_T,
	NDFA_T
};

class DFA
{
public:
	DFA();
    std::string name;
    int loadDFA(std::string);
    bool runDFA(std::string,unsigned int);
    unsigned int getStateIndexbyName(std::string);
    std::string getStateNamebyIndex(unsigned int);
    unsigned int getAlphaIndexbyName(std::string);
    std::string getAlphaNamebyIndex(unsigned int);
    std::vector<std::string> getNextSymbol(std::string);
    unsigned int getStartStateIndex();
    void printDFA();
    void printAlphabet();
    void printStates();
    void printStartState();
    void printAcceptStates();
    void printTransitionFunction();
    std::vector<unsigned int> getNextStates(unsigned int, unsigned int);
    bool isAcceptedState(unsigned int);

private:
    FSM_TYPE machine_type; // 0 - DFA, 1 - NDFA
    std::vector<std::string> alphabet;
    std::vector<std::string> states;
    std::vector<unsigned int> accept_states; // Indexes to states vector
    unsigned int start_state_index;
    std::vector< std::vector< std::vector<unsigned int> > > transition_table;
};

#endif /* DFA_H_ */


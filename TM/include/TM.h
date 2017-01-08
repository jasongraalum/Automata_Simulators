//
//  TM.hpp
//  AlgoTests
//
//  Created by Jason Graalum on 12/16/16.
//  Copyright © 2016 Jason Graalum. All rights reserved.
//

#ifndef TM_H_
#define TM_H_

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <algorithm>

enum FSM_TYPE
{
	TM_T,
	NTM_T
};

class TM
{
public:
	TM();
    std::string name;
    int loadTM(std::string);
    bool runTM(std::string);
    unsigned int getStateIndexbyName(std::string);
    std::string getStateNamebyIndex(unsigned int);
    unsigned int getAlphaIndexbyName(std::string);
    std::string getAlphaNamebyIndex(unsigned int);
    std::vector<std::string> getNextSymbol(std::string);
    unsigned int getStartStateIndex();
    unsigned int getAcceptStateIndex();
    unsigned int getRejectStateIndex();
    void printTM();
    void printInputAlphabet();
    void printTapeAlphabet();
    void printStates();
    void printStartState();
    void printAcceptState();
    void printRejectState();
    void printTransitionFunction();
    std::string getNextState(unsigned int, unsigned int);
    bool isAcceptedState(unsigned int);
    void setNullStateIndex(unsigned int);
    unsigned int getNullStateIndex();
    void printTape(std::list<std::string>);


private:
    FSM_TYPE machine_type; // 0 - TM, 1 - NTM

    std::vector<std::string> input_alphabet;

    std::vector<std::string> tape_alphabet;

    std::vector<std::string> states;
    unsigned int null_state_index;

    unsigned int start_state_index;
    unsigned int accept_state_index;
    unsigned int reject_state_index;

    std::vector< std::vector<std::string> > transition_table;
};

#endif /* TM_H_ */


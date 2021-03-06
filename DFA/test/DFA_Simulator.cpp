//============================================================================
// Name        : DFA_Simulator.cpp
// Author      : Jason Graalum
// Version     :
// Copyright   : Copyright © 2016 Jason Graalum. All rights reserved.
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "DFA.h"

int main(int argc, const char * argv[]) {

	unsigned int final_state;
	std::string cmd_str = "aabaabaabaabaabaa";
	DFA *dfa = new DFA();
	std::string ifn;
	std::ifstream ifp;

	if (argc > 1)
		ifn = argv[1];
	else {
		std::cout << "Enter DFA filename to load: ";
		std::cin >> ifn;
	}

	dfa->loadDFA(ifn);
	dfa->printDFA();

	std::cout << "Enter the string to run: ";
	std::cin >> cmd_str;

	final_state = dfa->runDFA(cmd_str,dfa->getStartStateIndex());

	std::cout << "Debug" << std::endl;
	if(dfa->isAcceptedState(final_state))
	{
		std::cout << "String " << cmd_str << " accepted by the DFA." << std::endl;
	}
	else
	{
		std::cout << "String " << cmd_str << " NOT accepted by the DFA." << std::endl;
	}
}

//============================================================================
// Name        : TM_Simulator.cpp
// Author      : Jason Graalum
// Version     :
// Copyright   : Copyright © 2016 Jason Graalum. All rights reserved.
// 
//============================================================================

#include "TM.h"

int main(int argc, const char * argv[]) {

	std::string cmd_str = "aabaabaabaabaabaa";
	TM *dfa = new TM();
	std::string ifn;
	std::ifstream ifp;

	if (argc > 1)
		ifn = argv[1];
	else {
		std::cout << "Enter TM filename to load: ";
		std::cin >> ifn;
	}

	dfa->loadTM(ifn);
	dfa->printTM();

	std::cout << "Enter the string to run: ";
	std::cin >> cmd_str;

	if(dfa->runTM(cmd_str))
	{
		std::cout << "String " << cmd_str << " accepted by the TM." << std::endl;
	}
	else
	{
		std::cout << "String " << cmd_str << " NOT accepted by the TM." << std::endl;
	}
}

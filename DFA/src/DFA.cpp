//
//  DFA.cpp
//  AlgoTests
//
//  Created by Jason Graalum on 12/16/16.
//  Copyright © 2016 Jason Graalum. All rights reserved.
//

#include "DFA.h"

DFA::DFA()
{
	machine_type = DFA_T;
	start_state_index = 0;
}

unsigned int DFA::getStartStateIndex()
{
	return(this->start_state_index);
}


std::vector<std::string> DFA::getNextSymbol(std::string cmd_string)
{
	std::vector<std::string> symbol_vec;
    std::string cmd_str = cmd_string;
    std::string::iterator symbol_it;
    std::string symbol = "";
    bool found;
    found = false;

    symbol_it = cmd_string.begin();
    while(!found && symbol_it < cmd_string.end())
	{
		// Build symbol - may be multiple characters
		symbol += *symbol_it;
		std::cout << "Checking for symbol " << *symbol_it << std::endl;

		// Check if symbol(as built) matches a symbol in the DFA
		if(std::find(this->alphabet.begin(), this->alphabet.end(),symbol) != this->alphabet.end())
		{
			std::cout << "Found symbol from alphabet: " << symbol << std::endl;
			found = true;
			symbol_vec.push_back(symbol);
			cmd_string.erase(0,symbol.size());
			symbol_vec.push_back(cmd_string);
		}
		else
		{
			symbol_it++;
		}
	}

	return(symbol_vec);

}
unsigned int DFA::getStateIndexbyName(std::string state)
{
    std::vector<std::string>::iterator iter;
    iter = std::find(this->states.begin(), this->states.end(), state);
    if(iter == this->states.end())
        return(this->states.size()+1);
    else
        return((int) std::distance(this->states.begin(), iter));
}

std::string DFA::getStateNamebyIndex(unsigned int i)
{
    if(i > this->states.size())
        return(NULL);
    else
        return(this->states[i]);
}

unsigned int DFA::getAlphaIndexbyName(std::string alpha)
{
    std::vector<std::string>::iterator iter;
    iter = std::find(this->alphabet.begin(), this->alphabet.end(),alpha);
    if(iter == this->alphabet.end())
        return(this->alphabet.size() + 1);
    else
        return((int) std::distance(this->alphabet.begin(), iter));
}
std::string DFA::getAlphaNamebyIndex(unsigned int i)
{
    if(i > this->alphabet.size())
        return(NULL);
    else
        return(this->alphabet[i]);
}

int DFA::loadDFA(std::string ifn)
{
    std::ifstream ifp(ifn.c_str());
    std::string line;
    std::size_t pos, open_paran, closed_paran, empty_transition;
    std::string s;

    if(!ifp.is_open())

    {
        std::cout << "Unable to open dfa input file: " << ifn << std::endl;
        return(-1);
    }
    else
    {
        std::cout << "Input dfa file " << ifn << " opened successfully." << std::endl;
    }

    // Read Name
    std::getline(ifp,line);

    pos = line.find(" ");
    line.erase(0, pos+1);
    this->name = line;
    std::cout << "DFA Name: " << line << std::endl;

    // Read Alphabet
    std::getline(ifp,line);

    // Remove key word
    pos = line.find(" ");
    line.erase(0, pos+1);

    while((pos = line.find(" ")) != std::string::npos)
    {
        this->alphabet.push_back(line.substr(0,pos));

        line.erase(0,pos+1);
    }
    this->alphabet.push_back(line.substr(0,pos));

    std::cout << "Added " << this->alphabet.size() << " elements to alphabet" << std::endl;
    this->printAlphabet();

    // Read States
    // Remove key word
    std::getline(ifp,line);

    pos = line.find(" ");
    line.erase(0, pos+1);

    while((pos = line.find(" ")) != std::string::npos)
    {
        this->states.push_back(line.substr(0,pos));
        line.erase(0,pos+1);
    }
    this->states.push_back(line.substr(0,pos));

    std::cout << "Added " << this->states.size() << " states" << std::endl;
    this->printStates();

    // Read Start State
    // Remove key word
    std::getline(ifp,line);

    pos = line.find(" ");
    line.erase(0, pos+1);
    this->start_state_index = this->getStateIndexbyName(line);

    std::cout << "Added start state:" << std::endl;
    this->printStartState();

    // Read Accept States
    // Remove key word
    std::getline(ifp,line);
    pos = line.find(" ");
    line.erase(0, pos+1);

    while((pos = line.find(" ")) != std::string::npos)
    {
        this->accept_states.push_back(this->getStateIndexbyName(line.substr(0,pos)));
        line.erase(0,pos+1);
    }
    this->accept_states.push_back(this->getStateIndexbyName(line.substr(0,pos)));

    std::cout << "Added " << this->accept_states.size() << " accept states" << std::endl;
    this->printAcceptStates();

    std::cout << std::endl;

    // Read Transition Table
    // Remove key word - full line
    std::getline(ifp,line);

    for(unsigned int state_index = 0; state_index < this->states.size(); state_index++)
    {
        std::string transition_table_row_str;
        std::getline(ifp,line);
        std::vector< std::vector<unsigned int> > transition_table_row;

        //std::cout << "line = " << line << std::endl;

        for(unsigned int alpha_index = 0; alpha_index < this->alphabet.size(); alpha_index++)
        {
        	std::vector<unsigned int> transition_table_cell;

        	empty_transition = line.find("0");
            open_paran = line.find("(");
            closed_paran = line.find(")");

            if(empty_transition < open_paran) // empty transition
            {
            	transition_table_cell.push_back(0);
            }
            else
            {
            	transition_table_row_str = line.substr(open_paran+1, closed_paran-open_paran-1);
                while((pos = transition_table_row_str.find(" ")) != std::string::npos)
                {
                    transition_table_cell.push_back(getStateIndexbyName(transition_table_row_str.substr(0,pos)));
                    transition_table_row_str.erase(0,pos+1);
                }
                transition_table_cell.push_back(getStateIndexbyName(transition_table_row_str.substr(0,pos)));
            }
            line.erase(open_paran,closed_paran+1);
            transition_table_row.push_back(transition_table_cell);
        }
        this->transition_table.push_back(transition_table_row);

    }

    ifp.close();
    return(0);

}
void DFA::printAlphabet()
{
    std::cout << "Alphabet: ";
    for(std::vector<std::string>::iterator it = this->alphabet.begin(); it != this->alphabet.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;

}

void DFA::printStates()
{
    std::cout << "States: ";
    for(std::vector<std::string>::iterator it = this->states.begin(); it != this->states.end(); ++it)
    	std::cout << *it << " ";
    std::cout << std::endl;

}
void DFA::printStartState()
{
    std::cout << "Start States: " << this->getStateNamebyIndex(this->start_state_index) << std::endl;
}
void DFA::printAcceptStates()
{
    std::cout << "Accept States: ";
    for(std::vector<unsigned int>::iterator it = this->accept_states.begin(); it != this->accept_states.end(); ++it)
       	std::cout << this->getStateNamebyIndex(*it) << " ";
    std::cout << std::endl;
}
void DFA::printTransitionFunction()
{

    std::vector<unsigned int> state_transition;

    std::cout << "       ";
    for(std::vector<std::string>::iterator it = this->alphabet.begin(); it != this->alphabet.end(); ++it)
            std::cout << *it << "  ";
    std::cout << std::endl;

    std::vector<std::string>::iterator state_it;
    std::vector< std::vector< std::vector<unsigned int> > >::iterator table_it;

    for(state_it = this->states.begin(), table_it = this->transition_table.begin(); table_it != this->transition_table.end(); ++state_it, ++table_it)
    {
        std::cout << *state_it << "  ";

    	for(std::vector< std::vector<unsigned int> >::iterator row_it = table_it->begin(); row_it != table_it->end(); ++row_it)
    	{
    		std::cout << "(";
    		for(std::vector<unsigned int>::iterator cell_it = row_it->begin(); cell_it != row_it->end(); ++cell_it)
    		{
    			std::cout << this->getStateNamebyIndex(*cell_it) << ",";
    		}
    		std::cout << ") ";
    	}
    	std::cout << std::endl;
    }
}
void DFA::printDFA()
{
    std::cout << "DFA: " << this->name << std::endl;
    std::cout << "++++++++++++++" << std::endl;
    this->printAlphabet();
    this->printStates();
    this->printStartState();
    this->printAcceptStates();
    this->printTransitionFunction();

}

std::vector<unsigned int> DFA::getNextStates(unsigned int state_index, unsigned int symbol_index)
{
    std::vector<unsigned int> state_vector;
    state_vector = this->transition_table[state_index][symbol_index];
    return(state_vector);
}

bool DFA::runDFA(std::string cmd_string, unsigned int current_state)
{
	std::string symbol;
	std::string new_cmd_string;

	std::vector<std::string> symbol_vec;

	std::vector<unsigned int> next_states;

	// No more symbols in cmd string - check if accept state
	if(cmd_string.size() == 0)
	{
		if(this->isAcceptedState(current_state))
			return(true);
		else
			return(false);
	}

	symbol_vec = this->getNextSymbol(cmd_string);
	symbol = symbol_vec[0];
	new_cmd_string = symbol_vec[1];

	// Symbols left in command string, but no next states == failed path
	next_states = this->getNextStates(current_state,this->getAlphaIndexbyName(symbol));
	if(next_states.size() == 0)
	{
		return(false);
	}

	// Until an accepted path is found, execute runDFA on each next state with symbol
	bool accepted = false;
    std::vector<unsigned int>::iterator state_it;

    state_it = next_states.begin();
	while((accepted == false) && (state_it != next_states.end()))
	{
		if(this->runDFA(new_cmd_string,*state_it))
			accepted = true;
		else
			state_it++;

	}
	return(accepted);

}

bool DFA::isAcceptedState(unsigned int state)
{
	if(std::find(this->accept_states.begin(), this->accept_states.end(), state) != this->accept_states.end() )
	{
		return(1);
	}
	else
	{
		return(0);
	}
}



//
//  NFA.cpp
//  AlgoTests
//
//  Created by Jason Graalum on 12/16/16.
//  Copyright © 2016 Jason Graalum. All rights reserved.
//

#include "NFA.h"

NFA::NFA()
{
    machine_type = NFA_T;
    start_state_index = 0;
}

void NFA::setNullStateIndex(unsigned int i)
{
    this->null_state_index = i;
}

unsigned int NFA::getNullStateIndex()
{
    return(this->null_state_index);
}

void NFA::setEmptyAlphaIndex(unsigned int i)
{
    this->empty_alpha_index = i;
}

unsigned int NFA::getEmptyAlphaIndex()
{
    return(this->empty_alpha_index);
}

unsigned int NFA::getStartStateIndex()
{
    return(this->start_state_index);
}


std::vector<std::string> NFA::getNextSymbol(std::string cmd_string)
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
//        std::cout << "Checking for symbol " << *symbol_it << std::endl;

        // Check if symbol(as built) matches a symbol in the NFA
        if(std::find(this->alphabet.begin(), this->alphabet.end(),symbol) != this->alphabet.end())
        {
//            std::cout << "Found symbol from alphabet: " << symbol << std::endl;
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
unsigned int NFA::getStateIndexbyName(std::string state)
{
    std::vector<std::string>::iterator iter;
    iter = std::find(this->states.begin(), this->states.end(), state);
    if(iter == this->states.end())
        return(this->states.size()+1);
    else
        return((int) std::distance(this->states.begin(), iter));
}

std::string NFA::getStateNamebyIndex(unsigned int i)
{
    if(i == this->getNullStateIndex())
        return("NULL");
    else
        return(this->states[i]);
}

unsigned int NFA::getAlphaIndexbyName(std::string alpha)
{
    std::vector<std::string>::iterator iter;
    iter = std::find(this->alphabet.begin(), this->alphabet.end(),alpha);
    if(iter == this->alphabet.end())
        return(this->alphabet.size() + 1);
    else
        return((int) std::distance(this->alphabet.begin(), iter));
}

std::string NFA::getAlphaNamebyIndex(unsigned int i)
{
    if(i == this->getEmptyAlphaIndex())
        return("empty");
    else
        return(this->alphabet[i]);
}

int NFA::loadNFA(std::string ifn)
{
    std::ifstream ifp(ifn.c_str());
    std::string line;
    std::size_t pos;
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
    std::cout << "NFA Name: " << line << std::endl;

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

    this->setEmptyAlphaIndex(this->alphabet.size());

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

    this->setNullStateIndex(this->states.size());

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

    //
    // Transition table has no column or row headers - only state transitions
    //
    for(unsigned int state_index = 0; state_index < this->states.size(); state_index++)
    {
        std::string transition_table_row_str;
        std::vector< std::vector<unsigned int> > transition_table_row;

        //
        // Get the next line from the input file
        //
        std::getline(ifp,line);

        std::cout << "line = " << line << std::endl;

        //
        // Read the transitions for each symbol in the alphabet 
        // plus the empty-string(hence the + 1 in the loop).
        //
        for(unsigned int alpha_index = 0; alpha_index < this->alphabet.size() + 1; alpha_index++)
        {
            std::size_t open_paran, closed_paran;
            std::vector<unsigned int> transition_table_cell;

            open_paran = line.find("(");
            closed_paran = line.find(")");
            
            // Get the transition string and remove whitespace
            std::string transition_entry = line.substr(open_paran+1,closed_paran-open_paran-1);
            transition_entry.erase(remove_if(transition_entry.begin(), transition_entry.end(), isspace), transition_entry.end());

            std::cout << "entry = " << transition_entry << " size = " << transition_entry.size() << std::endl;

            // If the transition string is now empty, the transition is empty.
            if(transition_entry.size() == 0) // empty transition
            {
                std::cout << "Empty transition" << std::endl;
                transition_table_cell.push_back(this->getNullStateIndex());
            }
            else
            {
                // Use comma for delimiter between states
                while((pos = transition_entry.find(",")) != std::string::npos)
                {
                    std::cout << "Adding " <<  transition_entry.substr(0,pos) << std::endl;
                    transition_table_cell.push_back(getStateIndexbyName(transition_entry.substr(0,pos)));
                    transition_entry.erase(0,pos+1);
                }
                    std::cout << "Adding " <<  transition_entry.substr(0,pos) << std::endl;
                transition_table_cell.push_back(getStateIndexbyName(transition_entry.substr(0,pos)));
            }
            line.erase(open_paran,closed_paran+1);
        std::cout << "line = " << line << std::endl;
            transition_table_row.push_back(transition_table_cell);

        }

        //
        // Add resulting vector into the transition table(vector of vectors)
        //
        this->transition_table.push_back(transition_table_row);

    }

    ifp.close();
    return(0);

}
void NFA::printAlphabet()
{
    std::cout << "Alphabet: ";
    for(std::vector<std::string>::iterator it = this->alphabet.begin(); it != this->alphabet.end(); ++it)
        std::cout << *it << " ";
    std::cout << "empty";
    std::cout << std::endl;

}

void NFA::printStates()
{
    std::cout << "States: ";
    for(std::vector<std::string>::iterator it = this->states.begin(); it != this->states.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;

}
void NFA::printStartState()
{
    std::cout << "Start States: " << this->getStateNamebyIndex(this->start_state_index) << std::endl;
}
void NFA::printAcceptStates()
{
    std::cout << "Accept States: ";
    for(std::vector<unsigned int>::iterator it = this->accept_states.begin(); it != this->accept_states.end(); ++it)
        std::cout << this->getStateNamebyIndex(*it) << " ";
    std::cout << std::endl;
}
void NFA::printTransitionFunction()
{

    std::vector<unsigned int> state_transition;

    std::cout << "       ";
    for(std::vector<std::string>::iterator it = this->alphabet.begin(); it != this->alphabet.end(); ++it)
        std::cout << *it << "  ";
    std::cout << "e" << "  ";
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
void NFA::printNFA()
{
    std::cout << "NFA: " << this->name << std::endl;
    std::cout << "++++++++++++++" << std::endl;
    this->printAlphabet();
    this->printStates();
    this->printStartState();
    this->printAcceptStates();
    this->printTransitionFunction();

}

std::vector<unsigned int> NFA::getEmptyTransitionStates(unsigned int state_index)
{
    std::vector<unsigned int> state_vector;
    unsigned int symbol_index = this->getEmptyAlphaIndex();

    state_vector = this->transition_table[state_index][symbol_index];
//    std::cout << "symbol_index = " << symbol_index << std::endl;
//    std::cout << "state_index = " << state_index << std::endl;
    return(state_vector);
}

std::vector<unsigned int> NFA::getNextStates(unsigned int state_index, unsigned int symbol_index)
{
    std::vector<unsigned int> state_vector;
    state_vector = this->transition_table[state_index][symbol_index];
    return(state_vector);
}

bool NFA::runNFA(std::string cmd_string, unsigned int current_state, int depth)
{
    std::string symbol;
    std::string new_cmd_string;

    std::vector<std::string> symbol_vec;

    std::cout << "***** Starting runNFA at depth " << depth << " with: " << cmd_string << " in state: " << getStateNamebyIndex(current_state) << std::endl;

    bool accepted = false;
    std::vector<unsigned int>::iterator state_it;

    std::vector<unsigned int> next_states;
    std::vector<unsigned int> empty_transition_states;

    //
    // Start advancing any empty transitions from the current state
    // Even if the cmd string is empty, we need to check the empty
    // transitions
    //
    empty_transition_states = this->getEmptyTransitionStates(current_state);

    if(*empty_transition_states.begin() != this->getNullStateIndex())
    {
        std::cout << "Found " << empty_transition_states.size() << " empty transitions in current state" << std::endl;
        state_it = empty_transition_states.begin();
        while((accepted == false) && (state_it != empty_transition_states.end()))
        {
            std::cout << "Empty transition " << *state_it << " at depth " << depth << std::endl;
            if(this->runNFA(cmd_string,*state_it,++depth))
            {
                std::cout << "Accepted" << std::endl;
                accepted = true;
                return(accepted);
            }
            else
                state_it++;
        }
    }

    //
    // If cmd string is empty, only check empty transitions(completed above)
    //
    if(cmd_string.size() == 0)
    {
        std::cout << "Input string is now empty." << std::endl;
        if(this->isAcceptedState(current_state))
        {
            std::cout << "Ended in accept state: " << this->getStateNamebyIndex(current_state) << std::endl;
            return(true);
        }
        else
        {
            std::cout << "Ended in reject state: " << this->getStateNamebyIndex(current_state) << std::endl;
            return(false);
        }
    }

    //
    // Now get the next symbol on the cmd string and continue
    // running runNFA on these symbols in the current state.
    //
    symbol_vec = this->getNextSymbol(cmd_string);
    symbol = symbol_vec[0];
    new_cmd_string = symbol_vec[1];

    //
    // Build next states list from current symbol + current state 
    //
    next_states = this->getNextStates(current_state,this->getAlphaIndexbyName(symbol));

    std::cout << "Check " << next_states.size() << " states at depth " << depth << " with symbol " << symbol << std::endl;
    //
    // Symbols left in command string, but no next states == dead state
    //
    if(*next_states.begin() == this->getNullStateIndex())
    {
        std::cout << "In a state with no next states - rejected dead state." << std::endl;
        return(false);
    }


    //
    // Run the NFA on each state from the transition table
    // Basically a depth-first search of the NFA. If one path comes back
    // in an accept state, stop checking....we only care if at least
    // one path ends in an accept state
    //
    state_it = next_states.begin();
    while((accepted == false) && (state_it != next_states.end()))
    {
        if(this->runNFA(new_cmd_string,*state_it,++depth))
        {
            std::cout << "Accept" << std::endl;
            accepted = true;
            return(accepted);
        }
        else
            state_it++;
    }

    
    std::cout << "Done running NFA and didn't find accepted state" << std::endl;
    return(accepted);

}

bool NFA::isAcceptedState(unsigned int state)
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



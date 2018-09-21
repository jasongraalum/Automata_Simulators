//
//  TM.cpp
//  AlgoTests
//
//  Created by Jason Graalum on 1/7/17.
//  Copyright © 2016 Jason Graalum. All rights reserved.
//

#include "TM.h"

TM::TM()
{
    machine_type = TM_T;
    start_state_index = 0;
}

void TM::setNullStateIndex(unsigned int i)
{
    this->null_state_index = i;
}

unsigned int TM::getNullStateIndex()
{
    return(this->null_state_index);
}

unsigned int TM::getStartStateIndex()
{
    return(this->start_state_index);
}

unsigned int TM::getAcceptStateIndex()
{
    return(this->accept_state_index);
}

unsigned int TM::getRejectStateIndex()
{
    return(this->reject_state_index);
}


std::vector<std::string> TM::getNextSymbol(std::string cmd_string)
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

        // Check if symbol(as built) matches a symbol in the TM
        if(std::find(this->input_alphabet.begin(), this->input_alphabet.end(),symbol) != this->input_alphabet.end())
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
unsigned int TM::getStateIndexbyName(std::string state)
{
    std::vector<std::string>::iterator iter;
    iter = std::find(this->states.begin(), this->states.end(), state);
    if(iter == this->states.end())
        return(this->states.size()+1);
    else
        return((int) std::distance(this->states.begin(), iter));
}

std::string TM::getStateNamebyIndex(unsigned int i)
{
    if(i == this->getNullStateIndex())
        return("NULL");
    else
        return(this->states[i]);
}

unsigned int TM::getAlphaIndexbyName(std::string alpha)
{
    std::cout << "Getting alpha index for \"" << alpha << "\"" << std::endl;
    std::vector<std::string>::iterator iter;
    iter = std::find(this->tape_alphabet.begin(), this->tape_alphabet.end(),alpha);
    return((int) std::distance(this->tape_alphabet.begin(), iter));
}

std::string TM::getAlphaNamebyIndex(unsigned int i)
{
    return(this->tape_alphabet[i]);
}

int TM::loadTM(std::string ifn)
{
    std::ifstream ifp(ifn.c_str());
    std::string line;
    std::size_t pos;
    std::string s;

    if(!ifp.is_open())

    {
        std::cout << "Unable to open TM input file: " << ifn << std::endl;
        return(-1);
    }
    else
    {
        std::cout << "Input TM file " << ifn << " opened successfully." << std::endl;
    }

    // Read Name
    std::getline(ifp,line);

    pos = line.find(" ");
    line.erase(0, pos+1);
    this->name = line;
    std::cout << "TM Name: " << line << std::endl;

    // Read Input Alphabet
    std::getline(ifp,line);

    // Remove key word
    pos = line.find(" ");
    line.erase(0, pos+1);

    while((pos = line.find(" ")) != std::string::npos)
    {
        this->input_alphabet.push_back(line.substr(0,pos));

        line.erase(0,pos+1);
    }
    this->input_alphabet.push_back(line.substr(0,pos));
    std::cout << "Added " << this->input_alphabet.size() << " elements to the input alphabet" << std::endl;

    // Read Tape Alphabet
    std::getline(ifp,line);

    // Remove key word
    pos = line.find(" ");
    line.erase(0, pos+1);

    while((pos = line.find(" ")) != std::string::npos)
    {
        this->tape_alphabet.push_back(line.substr(0,pos));

        line.erase(0,pos+1);
    }
    this->tape_alphabet.push_back(line.substr(0,pos));
    this->tape_alphabet.push_back(" ");

    std::cout << "Added " << this->tape_alphabet.size() << " elements to the tape alphabet" << std::endl;


    this->printInputAlphabet();
    this->printTapeAlphabet();

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

    // Read Accept State
    // Remove key word
    std::getline(ifp,line);

    pos = line.find(" ");
    line.erase(0, pos+1);
    this->accept_state_index = this->getStateIndexbyName(line);

    std::cout << "Added accept state:" << std::endl;
    this->printAcceptState();

    // Read Reject State
    // Remove key word
    std::getline(ifp,line);

    pos = line.find(" ");
    line.erase(0, pos+1);
    this->reject_state_index = this->getStateIndexbyName(line);

    std::cout << "Added reject state:" << std::endl;
    this->printRejectState();

    // Read Transition Table
    // Remove key word - full line
    std::getline(ifp,line);

    //
    // Transition table has no column or row headers - only state transitions
    //
    // Read a line for each state - not including the accept and reject states
    for(unsigned int state_index = 0; state_index < this->states.size()-2; state_index++)
    {
        std::string transition_table_row_str;

        //
        // Get the next line from the input file
        //
        std::getline(ifp,line);

        std::cout << "line = " << line << std::endl;
        std::vector<std::string> transition_table_row;

        //
        // Read the transitions for each symbol in the alphabet 
        //
        for(unsigned int tape_alpha_index = 0; tape_alpha_index < this->tape_alphabet.size(); tape_alpha_index++)
        {
        std::cout << "line = " << line << std::endl;
            std::size_t open_paran, closed_paran;

            open_paran = line.find("(");
            closed_paran = line.find(")");
            
            // Get the transition string
            std::string transition_entry = line.substr(open_paran+1,closed_paran-open_paran-1);

            //std::cout << "entry = " << transition_entry << " size = " << transition_entry.size() << std::endl;

            // If the transition string is empty, the transition is empty.
            if(transition_entry.size() == 0) // empty transition
            {
                std::cout << "Adding NULL to table" << std::endl;
                transition_table_row.push_back("");
            }
            else
            {
                std::cout << "Adding " << transition_entry << " to table" << std::endl;
                transition_table_row.push_back(transition_entry);
            }
            line.erase(0,closed_paran+1);
        std::cout << "line2 = " << line << std::endl;
        }
        this->transition_table.push_back(transition_table_row);

        //
        // Add resulting vector into the transition table(vector of vectors)
        //

    }

    ifp.close();
    return(0);

}

void TM::printInputAlphabet()
{
    std::cout << "Input Alphabet: ";
    for(std::vector<std::string>::iterator it = this->input_alphabet.begin(); it != this->input_alphabet.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;

}

void TM::printTapeAlphabet()
{
    std::cout << "Tape Alphabet: ";
    for(std::vector<std::string>::iterator it = this->tape_alphabet.begin(); it != this->tape_alphabet.end(); ++it)
        std::cout << "(" << *it << ")";
    std::cout << std::endl;
}

void TM::printStates()
{
    std::cout << "States: ";
    for(std::vector<std::string>::iterator it = this->states.begin(); it != this->states.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;

}
void TM::printStartState()
{
    std::cout << "Start States: " << this->getStateNamebyIndex(this->start_state_index) << std::endl;
}

void TM::printAcceptState()
{
    std::cout << "Accept State: " << this->getStateNamebyIndex(this->accept_state_index) << std::endl;
}

void TM::printRejectState()
{
    std::cout << "Reject State: " << this->getStateNamebyIndex(this->reject_state_index) << std::endl;
}

void TM::printTransitionFunction()
{

    std::vector<std::string> state_transition;

    //
    // Print column(tape alphabet) headers
    std::cout << "       ";
    for(std::vector<std::string>::iterator it = this->tape_alphabet.begin(); it != this->tape_alphabet.end(); ++it)
    {
        std::cout << *it << "  ";
    }
    std::cout << std::endl;

    std::vector<std::string>::iterator state_index_it;
    std::vector< std::vector<std::string> >::iterator table_it;

    for(state_index_it = this->states.begin(), table_it = this->transition_table.begin(); table_it != this->transition_table.end(); ++state_index_it, ++table_it)
    {
        //
        // Print row header - state
        //
        std::cout << *state_index_it << "  ";

        for(std::vector<std::string>::iterator row_it = table_it->begin(); row_it != table_it->end(); ++row_it)
        {
            std::cout << "(" << *row_it << ") ";
        }
        std::cout << std::endl;
    }
}
void TM::printTM()
{
    std::cout << "TM: " << this->name << std::endl;
    std::cout << "++++++++++++++" << std::endl;
    this->printInputAlphabet();
    this->printTapeAlphabet();
    this->printStates();
    this->printStartState();
    this->printAcceptState();
    this->printRejectState();
    this->printTransitionFunction();

}

std::string TM::getNextState(unsigned int state_index, unsigned int symbol_index)
{
    std::cout << "Getting next state: " << state_index << "," << symbol_index << std::endl;
    std::string state_vector;
    state_vector = this->transition_table[state_index][symbol_index];
    return(state_vector);
}

void TM::printTape(std::list<std::string> tape)
{
    for(std::list<std::string>::iterator tape_it = tape.begin(); tape_it != tape.end(); ++tape_it)
    {
        if(*tape_it == " ")
            std::cout << "_ ";
        else
            std::cout << *tape_it << " ";
    }
    std::cout << std::endl;
}

bool TM::runTM(std::string cmd_string)
{
    std::string s = cmd_string;
    std::list<std::string> tape;
    std::vector<std::string> next_symbol_vector;
    std::string symbol;
    std::string v, w;

    v = "";
    w = s;

    //
    // Write the command string onto the tape
    //
    while(s.size() > 0)
    {
        next_symbol_vector = getNextSymbol(s);
        symbol = next_symbol_vector[0];
        s = next_symbol_vector[1];
        std::cout << "Symbol = " << symbol << " : Remaining command string = " << s << std::endl;
        tape.push_back(symbol);
    }

    //
    // Setup the TM - current state, and tape position
    //
    unsigned int current_state_index = this->getStartStateIndex();
    unsigned int accept_index = this->getAcceptStateIndex();
    unsigned int reject_index = this->getRejectStateIndex();

    std::string next_state_string;
    std::list<std::string>::iterator tape_position = tape.begin();

    unsigned int symbol_index;
    std::string current_symbol;

    //
    // Variables to track machine action
    //
    std::string write_symbol;
    std::string tape_movement;
    std::string next_state_name;

    do {
        //
        // Get the symbol at the current tape position
        //
        current_symbol = *tape_position;
        symbol_index = this->getAlphaIndexbyName(current_symbol);

        //
        // Based on the current symbol and current state, get next action
        // Decompose the next state string into individual actions:
        //  symbol to write
        //  next state
        //  tape head movement
        //
        next_state_string = this->getNextState(current_state_index, symbol_index);
        if(next_state_string.size() == 0)
        {
            write_symbol = "";
            tape_movement = "";
            next_state_name = this->getStateNamebyIndex(this->getRejectStateIndex());
        }
        else
        {
            std::string s = next_state_string;

            std::size_t first_comma = s.find(",");
            write_symbol = s.substr(0,first_comma);
            write_symbol.erase(write_symbol.begin());
            write_symbol.erase(write_symbol.end()-1);

            s.erase(0,first_comma+1);

            std::size_t second_comma = s.find(",");
            tape_movement = s.substr(0,1);
            s.erase(0,second_comma+1);

            next_state_name = s;
        }

        std::cout << v << next_state_name << w << std::endl;
        std::cout << "Current Symbol = " << current_symbol << std::endl;
        this->printTape(tape);

        std::cout << "Current State(Index) = " << this->getStateNamebyIndex(current_state_index) << "(" << current_state_index << ")" << std::endl;
        std::cout << "Next State String: " << next_state_string << std::endl;
        std::cout << "   Write Symbol: \"" << write_symbol << "\"" << std::endl;
        std::cout << "   Next State: " << next_state_name << std::endl;
        std::cout << "   Tape Move: " << tape_movement << std::endl;

        if(write_symbol.size() > 0)
        {
            std::cout << "Writing \"" << write_symbol << "\" to the tape" << std::endl;
            *tape_position = write_symbol;
        }

        if(tape_movement == "R")
            tape_position++;
        else if(tape_movement == "L")
            tape_position--;

        if(tape_position == tape.end())
        {
            std::cout << "End of tape" << std::endl;
            tape.push_back(" ");
            tape_position--;
            this->printTape(tape);
        }

        current_state_index = this->getStateIndexbyName(next_state_name);
    }
    while((next_state_string.size() > 0) && (current_state_index != accept_index) && (current_state_index != reject_index));


    this->printTape(tape);

    if(current_state_index == accept_index)
        return(true);
    else
        return(false);


}

bool TM::isAcceptedState(unsigned int state)
{
    return(state == this->accept_state_index);
}



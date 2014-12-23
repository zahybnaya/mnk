#include "agent.h"
#include "heuristic.h"
#include <fstream>
#include <exception>
#include <cassert>
#include <algorithm>


/**
 * Thrown when an agent description file is missing a field
 * */
class AgentParamsException: public std::exception {
	public:
		AgentParamsException(std::string f):unknown_field(f){};
		virtual const char* what() const throw()
		{
			return ("malformed agent file on field: " + unknown_field).c_str() ;
		}
	private:
		std::string unknown_field;
};

//TODO: For the demo:
// Create a github repository for this  
// Implement exshistive agent with a depth property 
// Extract out the model fitting algorithm
// Show how easy it is to implement a new agent (online) 
// Extend the number of parameters for an agent 
// Valgrind
// Make agents register themselves
// Add consts, inline, exceptions, errors 
// Avoid segmentaion fault in wrong agents
// Print tree to dot

/**
 * Execute the best play
 * */
zet Agent::play(board& b,bool player){
	std::vector<zet> s = solve(b,player);
	FILE_LOG(logDEBUG)<<"Playing for player "<<((player==BLACK)?"BLACK":"WHITE")<< std::endl;
	assert(b.active_player()==player);
	for (std::vector<zet>::const_iterator i = s.begin(); i != s.end(); ++i) {
		FILE_LOG(logDEBUG)<<"    Move:"<<i->zet_id<< " val:"<<i->val<<std::endl;
	}
	zet r=*std::max_element(s.begin(),s.end(),zet_comparator_t(player));
	FILE_LOG(logDEBUG)<<((player==BLACK)?"BLACK":"WHITE")<<" playes move "<<r.zet_id<<std::endl;
	return r;
}


/**
 * Reads an int property from the table
 * */
int Agent::get_int_property(std::string prop){
	if(m_properties.find(prop)==m_properties.end()){
		throw AgentParamsException(prop);
	}
	return std::stoi(m_properties[prop]);
}

/**
 * Reads a double from the table
 * */
double Agent::get_double_property(std::string prop){
	if(m_properties.find(prop)==m_properties.end()){
		throw AgentParamsException(prop);
	}
	return std::stof(m_properties[prop]);
}

/**
 * Reads a vector TODO
 * */
std::vector<double> Agent::get_array_property(std::string prop){
	if(m_properties.find(prop)==m_properties.end()){
		throw AgentParamsException(prop);
	}
	std::vector<double> v;
	return v;
}

/**
 * Select a random move 
 */
uint64 Agent::select_random_move(std::vector<zet> &moves){
	return moves[rand() % moves.size()].zet_id;
}

const std::string Agent::get_agent_file(){
	return agent_file;

}

void Agent::set_agent_file(std::string af){
	agent_file=af;

}


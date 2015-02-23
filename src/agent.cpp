#include "agent.h"
#include "heuristic.h"
#include <fstream>
#include <exception>
#include <cassert>
#include <algorithm>
#include <random>


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



/**
 *
 * */
void Agent::init(){
	mt19937_64 g;
	g.seed(time(NULL));
	generator.seed(g());
	lapse = std::bernoulli_distribution(get_lapse_rate()); 
}

/**
 * Execute the best play
 * */
zet Agent::play(board& b,bool player){
	this->playing_color = player;
	std::vector<zet> s = solve(b,player);
	FILE_LOG(logDEBUG)<<"Playing for player "<<((player==BLACK)?"BLACK":"WHITE")<< " there are "<< s.size() <<" moves" << std::endl;
	FILE_LOG(logDEBUG)<<" board is :" <<b<<std::endl;
	if(b.active_player()!=player){
		FILE_LOG(logERROR)<<"Player  "<<((player==BLACK)?"BLACK":"WHITE")<< " is not the same as board::active_player()" << std::endl;
	}
	if (lapse(get_generator())){
		return s[std::uniform_int_distribution<int>(0,s.size())(get_generator())];
	}
	zet r;
	std::random_shuffle(s.begin(),s.end());
	if (player == BLACK || !is_negamax()){
		r=*std::min_element(s.begin(),s.end(),compare);
	} else{
		r=*std::max_element(s.begin(),s.end(),compare);
	}
	FILE_LOG(logDEBUG)<<((player==BLACK)?"BLACK":"WHITE")<<" playes move "<<r.zet_id<<std::endl;
	return r;
}


/**
 * Reads an int property from the table
 * */
int Agent::get_int_property(std::string prop) {
	if(m_properties.find(prop)==m_properties.end()){
		throw AgentParamsException(prop);
	}
	return std::stoi(m_properties[prop]);
}

/**
 * Reads a double from the table
 * */
double Agent::get_double_property(std::string prop) {
	if(m_properties.find(prop)==m_properties.end()){
		throw AgentParamsException(prop);
	}
	try{
	return std::stof(m_properties[prop]);
	} catch (std::invalid_argument e){
		FILE_LOG(logERROR)<<" Wrong value for property  "<< prop <<":" << m_properties[prop]<<std::endl;
		exit(-1);
	}
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
	return moves[get_generator()() % moves.size()].zet_id; //TODO: uniform_distribution
}

const std::string Agent::get_agent_file(){
	return agent_file;

}

void Agent::set_agent_file(std::string af){
	agent_file=af;

}

double Agent::get_lapse_rate() {
	return get_double_property("lapse_rate");
}

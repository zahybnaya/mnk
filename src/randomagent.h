#ifndef RANDOM_AGENT_H
#define RANDOM_AGENT_H

#include "agent.h"

class RandomAgent : public Agent {

	public:
		RandomAgent(){};
		zet play(board& b,bool /*player*/); 
		virtual std::string get_name() const { return std::string("RandomAgent");};
		virtual std::vector<zet> solve(board& b,bool player){
			throw std::runtime_error("should not be called");
		};
		virtual bool is_negamax() {return false;};

};
	
#endif

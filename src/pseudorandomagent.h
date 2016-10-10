#ifndef PSEUDORANDOM_AGENT_H
#define PSEUDORANDOM_AGENT_H

#include "agent.h"
#include "pseudorandomplayout.h"


class PseudoRandomAgent : public Agent {

	public:
		PseudoRandomAgent(){};
		zet play(board& b,bool /*player*/); 
		virtual std::string get_name() const { return std::string("PseudoRandomAgent");};
		virtual std::vector<zet> solve(board& b,bool player){
			throw std::runtime_error("should not be called");
		};
		virtual bool is_negamax() {return false;};
	private:
		PseudoRandomPlayout p;
};
	
#endif

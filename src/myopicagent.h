#ifndef MYOPICAGENT_H
#define MYOPICAGENT_H
#include "agent.h"
#include <random>
#include "heuristic.h"

class MyopicAgent: public Agent{
public:
	MyopicAgent(){
	};
	~MyopicAgent(){};
	const std::string get_name(){return "Myopic";}
	std::vector<zet> solve(board& b,bool player);
	
private:
	heuristic h;
	std::bernoulli_distribution lapse;
};


#endif /* end of include guard: MYOPICAGENT_H */

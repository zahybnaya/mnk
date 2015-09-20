#ifndef MYOPICAGENT_H
#define MYOPICAGENT_H
#include "agent.h"
#include <random>
#include "heuristic.h"
#include "heuristicagent.h"

class MyopicAgent: public HeuristicsAgent {
public:
	MyopicAgent(){};
	~MyopicAgent(){};
	std::string get_name()const {return "Myopic";}
	std::vector<zet> solve(board& b,bool player);
private:

};


#endif /* end of include guard: MYOPICAGENT_H */

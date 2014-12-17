#ifndef BFSAGENT_H
#define BFSAGENT_H
#include "uctagent.h"

/**
 * BFS agent is only a UCT agent with no exploration
 * */

class BFSAgent: public UCTAgent{
public:
	BFSAgent(){};
	~BFSAgent(){};
	const std::string get_name(){return "BFS";}
private:
	double get_exploration_constant();
};



#endif /* end of include guard: BFSAGENT_H */


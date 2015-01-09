#ifndef BFSAGENT_H
#define BFSAGENT_H
#include "uctagent.h"
#include "heuristic.h"

/**
 * BFS agent is only a UCT agent with no exploration
 * */

class BFSAgent: public UCTAgent{
public:
	BFSAgent(){};
	~BFSAgent(){};
	const std::string get_name(){return "BFS";}
	double evaulate(Node* lastNode,Node*, uint64);
private:
	heuristic h;
};



#endif /* end of include guard: BFSAGENT_H */


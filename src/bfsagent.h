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
	const double get_D0();
	const double get_K0();
	const double get_gamma();
	const double get_delta();
	const double get_vert_scale();
	const double get_diag_scale();
	const double get_opp_scale();
	bool is_negamax(){return false;};
	heuristic h;
};



#endif /* end of include guard: BFSAGENT_H */


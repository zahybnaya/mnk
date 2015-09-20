#ifndef FIXEDDEPTHTREEAGENT_H
#define FIXEDDEPTHTREEAGENT_H

#include "heuristicagent.h"
#include "treeagent.h"
#include "common.h"
#include "heuristic.h"

class FixedDepthTreeAgent :  public HeuristicsAgent{
public:
	FixedDepthTreeAgent(){};
	~FixedDepthTreeAgent(){};
	std::vector<zet> solve(board& b,bool player);
	void expand_rec(Node* n, int depth);
	virtual std::string get_name() const {return "FixedDepthTreeAgent";}

private:
	int get_depth();
	int get_branching_factor();
};



#endif /* end of include guard: FIXEDDEPTHTREEAGENT_H */


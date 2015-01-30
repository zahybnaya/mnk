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
		void init();
	private:
		double get_D0();
		double get_K0();
		double get_gamma(); 
		double get_delta();
		double get_vert_scale();
		double get_diag_scale();
		double get_opp_scale();
		bool is_negamax(){return false;};
		heuristic h;
};



#endif /* end of include guard: BFSAGENT_H */


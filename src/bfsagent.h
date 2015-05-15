#ifndef BFSAGENT_H
#define BFSAGENT_H
#include "uctagent.h"
#include "heuristic.h"

/**
 * BFS agent is only a UCT agent with no exploration
 * */

class BFSAgent: public TreeAgent{
	public:
		BFSAgent(){};
		~BFSAgent(){};
		void init();
		std::string get_name() const {return "BFS";}
		Node* select_next_node(Node* n);
		void back_propagatate(double new_val, std::vector<Node*> nodes);
		double expand(Node* n);
		//double evaulate(Node* lastNode,Node*, uint64);
		double get_triangle_weight();
		double get_weight(int i);
		double get_K0();
		double get_gamma(); 
		double get_delta();
		double get_vert_scale();
		double get_diag_scale();
		double get_opp_scale();
		bool is_negamax(){return false;};
		void pre_solution();
		void post_solution();
	private:
		heuristic h;
		bernoulli_distribution branching_factor;
};



#endif /* end of include guard: BFSAGENT_H */


#ifndef BFSAGENT_H
#define BFSAGENT_H
#include "uctagent.h"
#include "heuristic.h"

/**
 *
 *
 * */

class BFSAgent: public TreeAgent{
	public:
		BFSAgent(){};
		virtual ~BFSAgent(){};
		void init();
		std::string get_name() const {return "BFS";}
		Node* select_next_node(Node* n);
		void back_propagatate(double new_val, std::vector<Node*> nodes);
		double expand(Node* n);
		double get_K0();
		double get_gamma(); 
		bool is_negamax(){return false;};
		void pre_solution();
		void post_solution();
		/**
		 * How many children to expand
		 * */
		virtual unsigned int get_actual_branching_factor(std::vector<zet>& zets);
	private:
		bernoulli_distribution branching_factor;
};



#endif /* end of include guard: BFSAGENT_H */


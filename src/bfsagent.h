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
		double get_triangle_weight();
		double get_weight(int i);
		double get_K0();
		double get_gamma(); 
		double get_delta();
		double get_vert_scale();
		double get_diag_scale();
		double get_opp_scale();
		double get_act_scale();
		bool is_negamax(){return false;};
		void pre_solution();
		void post_solution();
		/**
		 * How many childrent to expand
		 * */
		virtual unsigned int get_actual_branching_factor(std::vector<zet>& zets);
	private:
		heuristic h;
		bernoulli_distribution branching_factor;
};



#endif /* end of include guard: BFSAGENT_H */


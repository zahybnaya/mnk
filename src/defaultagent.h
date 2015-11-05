#include "bfsagent.h"


/****
 * 
 * This agent changes (1) the stop criteria (2) the prunning method. 
 *
 * It stops the tree-building when either the iterations are done (?) or that the 
 * absolute difference between the two main zets is bigger than threshold. 
 *
 * Prunning (get_actual_branching_factor) maintains only the children with a distnce of less than prune_threshold to
 * the best move
 *
 * */ 
class DefaultAgent: public BFSAgent {

	public:
		DefaultAgent(){};
		virtual ~DefaultAgent(){};

	protected:
		/** 
		 * When exceeding the number of
		 * iterations or threshould
		 * **/
		bool is_stop(Node* n);
		/***
		 * Prunning according to distance from threshold.
		 * */
		unsigned int get_actual_branching_factor(std::vector<zet>& zets);


		std::string get_name() const {return "DEFAULT";}
	private:

		/***
		 * Properties
		 **/
		double get_stop_threshold();
		double get_prune_threshold();
};

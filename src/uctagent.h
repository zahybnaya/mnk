#ifndef UCTAGENT_H
#include "treeagent.h"
#include "randomplayout.h"
#include "heuristic.h"
#include "playoutpolicy.h"

class UCTAgent: public TreeAgent{ 
public:
	UCTAgent();
	~UCTAgent();
	/**
	 * Calculates the uct value of the node
	 * */
	double uct(Node* n, int ttl_visits);
	double expand(Node* n);
	Node* select_next_node(Node* n);
	/**
	 * Set it to random playouts
	 * */
	virtual double evaulate(Node* lastNode, Node* p, uint64 m_id);
	std::string get_name() const;
	/**
	 *  if there are unexpected moves it's not solved
	 **/
	void mark_solved(Node* n);
	void init();

	void pre_solution();
	void post_solution();

private:
	int get_policy_code();
	double get_triangle_weight();
	double get_weight(int i);
	double get_K0();
	double get_gamma(); 
	double get_delta();
	double get_vert_scale();
	double get_diag_scale();
	double get_opp_scale();
	int get_virtual_rollouts();
	/* uct funtions */
	virtual double get_exploration_constant(); 
	PlayoutPolicy* policy;
	bool is_negamax();
	int get_num_of_evals();
	heuristic h;
	bernoulli_distribution branching_factor;
};
#define UCTAGENT_H


#endif /* end of include guard: UCTAGENT_H */


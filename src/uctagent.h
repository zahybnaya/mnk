#ifndef UCTAGENT_H
#include "treeagent.h"
#include "randomplayout.h"

class UCTAgent: public TreeAgent{ 
public:
	UCTAgent();
	~UCTAgent(){};
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
private:
	/* uct funtions */
	virtual double get_exploration_constant(); 
	RandomPlayout policy;
	bool is_negamax();
};
#define UCTAGENT_H


#endif /* end of include guard: UCTAGENT_H */


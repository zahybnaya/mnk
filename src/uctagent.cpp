#include "uctagent.h"
#include <math.h>
#include <assert.h>
#include <algorithm>
#include "randomplayout.h"

/**
 * Constructor 
 * */
UCTAgent::UCTAgent(){
	policy = RandomPlayout();
}

/**
 * Naming of agent
 * */
std::string UCTAgent::get_name() const{
	return std::string("UCT");
}

/**
 * are values stored in a negamax tree
 * */
bool UCTAgent::is_negamax(){
	return true;
}

/**
 * UCT uses a given policy to evaluate new states.
 * */
double UCTAgent::evaulate(Node* lastNode,Node* /* parent*/, uint64 ){
	return policy.eval(lastNode->m_board);
}

/**
 * The uct calculation 
 * */
double UCTAgent::uct(Node* n, int ttl_visits) { 
	double exploration =  sqrt(log(ttl_visits)/n->visits);
	double exploitation = n->val/n->visits;
	bool player_turn = !n->player;
	if ( is_negamax())
		exploitation=(player_turn==BLACK )?exploitation:-exploitation;
	return 
		get_exploration_constant()*exploration + exploitation; 
}

struct uct_comparator_t {
	uct_comparator_t(UCTAgent* a,int ttl): ttl_visits(ttl), a(a){};
	int operator()(std::pair<uint64,Node*> i, std::pair<uint64,Node*> j) {
	       	return a->uct(i.second,ttl_visits)<a->uct(j.second,ttl_visits);
       	}
	int ttl_visits;
	UCTAgent* a;
}; 

/**
 * Returns either a new child node 
 * or an existing child node 
 */
Node* UCTAgent::select_next_node(Node* n){
	assert(!n->solved);
	assert(!n->m_board.is_ended());
	std::vector<zet> moves = unexpanded_moves(n);
	if (!moves.empty()){
		return NULL;
	}
	std::vector<pair<uint64,Node*>> v= get_shuffled_vector(n->children);
	assert(v.size()>0);
	std::pair<uint64,Node*> argmax =
	       	*std::max_element(v.begin(),v.end(),uct_comparator_t(this,n->visits));
	return argmax.second;
}

void UCTAgent::mark_solved(Node* n){
	if (!unexpanded_moves(n).empty()){
		return;
	}
	TreeAgent::mark_solved(n);
}

/**
 * UCT expand
 * */
double UCTAgent::expand(Node* n){
	uint64 move = select_random_unknown_move(n);
	Node* new_node = TreeAgent::connect(move,n);
	return evaulate(new_node, n, move);
}


/**
 *  UCT constant 
 * */
double UCTAgent::get_exploration_constant() {
	return get_double_property("exploration_constant");
}





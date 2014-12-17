#include "uctagent.h"
#include <math.h>
#include <algorithm>

const std::string UCTAgent::get_name(){
	return std::string("UCT");
}

/**
 * The uct calculation as it performed by the agent
 * */
double UCTAgent::uct(Node* n, int ttl_visits) { 
	double exploration =  sqrt(log(ttl_visits)/n->visits);
	double exploitation = n->val/n->visits;
	bool player_turn = !n->player;//n is the child
	exploitation=(player_turn==BLACK)?exploitation:-exploitation;
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
 * TODO: Don't go to solved variations
 */
Node* UCTAgent::select_next_node(Node* n){
	if(n->m_board.is_ended()){
		n->new_node=true;
		return n;
	}
	std::vector<zet> moves = unexpanded_moves(n);
	if (!moves.empty()){
		return expand(select_random_move(moves),n);
	}
	std::pair<uint64,Node*> argmax =
	       	*std::max_element(n->children.begin(),n->children.end(),uct_comparator_t(this,n->visits));
	return argmax.second;
}


/**
 *  UCT constant 
 * */
double UCTAgent::get_exploration_constant() {
	return 0.5;
}





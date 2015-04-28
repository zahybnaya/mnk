#include "uctagent.h"
#include <math.h>
#include <assert.h>
#include <algorithm>
#include "randomplayout.h"

/**
 * Constructor TODO: take this from a properties file
 * */
UCTAgent::UCTAgent(){
	policy = RandomPlayout();
}

/**
 * Naming of agent
 * */
const std::string UCTAgent::get_name(){
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
 * Shuffles a vector from children map
 * */
std::vector<pair<uint64,Node*>> get_shuffled_vector(child_map c){
	std::vector<pair<uint64,Node*>> v;
	assert(c.size()>0);
	std::copy_if(c.begin(), c.end(), std::back_inserter(v),[](const std::pair<uint64,Node*> &p){
			return !p.second->solved;
			});
	std::random_shuffle(v.begin(),v.end());
	return v;
}

/**
 * Returns either a new child node 
 * or an existing child node 
 */
Node* UCTAgent::select_next_node(Node* n){
	assert(!n->solved);
	assert(!n->m_board.is_ended());
	std::vector<zet> moves = unexpanded_moves(n);
	if (!moves.empty()){
		return expand(select_random_move(moves),n);
	}
	std::vector<pair<uint64,Node*>> v= get_shuffled_vector(n->children);
//	if (v.size()==0){
//		std::cout<<"is_solved:"<<n->solved<<"visits:"<<n->visits<<"board:"<<n->m_board.is_ended()<<std::endl;
//		for (child_map::iterator i=n->children.begin() ; i!=n->children.end();++i){
//			std::cout<<"  is_solved:"<<i->second->solved<<"visits:"<<i->second->visits<<"board:"<<i->second->m_board.is_ended()<<std::endl;
//		} 
//		mark_solved(n);
//	}
	assert(v.size()>0);
	std::pair<uint64,Node*> argmax =
	       	*std::max_element(v.begin(),v.end(),uct_comparator_t(this,n->visits));
	return argmax.second;
}


/**
 *  UCT constant 
 * */
double UCTAgent::get_exploration_constant() {
	return get_double_property("exploration_constant");
}





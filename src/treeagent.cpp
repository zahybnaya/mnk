#include "treeagent.h"
#include "heuristic.h"
#include "board.h"
#include <assert.h>
#include <random>
#include <algorithm>

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
 * Returns a list of possible moves and their estimates. 
 */
std::vector<zet> TreeAgent::solve(board& b,bool player){
	this->playing_color = player;
	FILE_LOG(logDEBUG) << "Starting to solve board:{"<< uint64tobinstring(b.pieces[0]) ;
	FILE_LOG(logDEBUG) << ","<< uint64tobinstring(b.pieces[1])<<"}" << std::endl;
	pre_solution();
	this->playing_color=player;
	double gamma = get_iter_gamma();
	std::geometric_distribution<int> iter_dist(gamma);
	int num_iterations= iter_dist(get_generator());
	FILE_LOG(logDEBUG) << " Number of iterations  "<< num_iterations<< std::endl;
	Node* n = create_initial_state(b);
	build_tree(n,num_iterations);	
	std::vector<zet> ret= move_estimates(n);
	delete_tree(n);
	post_solution();
	return ret;
}

/**
 * Creates a new node to represent node and adds it as a child to parent
 */
Node* TreeAgent::connect(uint64 move,Node* parent,double value,int visits){
	assert(parent);
	zet z = zet(move,value,parent->player); 
	board b = parent->m_board+z;
	Node* new_node = new Node(b,!parent->player,value,visits);
	if (new_node->m_board.is_ended()){
		new_node->solved=true;
	}
	parent->children[move]=new_node; 
	FILE_LOG(logDEBUG) << " connecting move:"<<move << " with value:"<< value<< " is_solved:"<<new_node->solved<<std::endl;
	return new_node;
}



/**
 * Creates the initial state 
 * */
Node* TreeAgent::create_initial_state(board b){
	Node* n =new Node(b,b.active_player()); 
	return n ;
}	


/**
 * Iteratively build a tree
 **/
int TreeAgent::build_tree(Node* n,int iterations){ 
	int iterNum=0;
	while (iterNum <= iterations){
		FILE_LOG(logDEBUG) << " Starting iteration "<< iterNum<< std::endl;
		iterate(n);
		iterNum++;
	}
	return 0;
}

/**
 * A single iteraton of building the tree
 * */
void TreeAgent::iterate(Node* n){
	assert(!n->m_board.is_ended());
	if (n->solved){
		FILE_LOG(logDEBUG) << " Node is solved, returning "<< std::endl;
		return;
	}
	std::vector<Node*> nodes = select_variation(n);	
	double new_val = expand(nodes.back());
	//double new_val = evaluate_last_node(nodes);
	back_propagatate(new_val,nodes);
}


/**
 * Returns a variation of the tree starting from the root 
 * and up to the new state node which should be expanded
 */
std::vector<Node*> TreeAgent::select_variation(Node* n){
	FILE_LOG(logDEBUG) << " Selecting variation ";
	std::vector<Node*> ret;
	ret.push_back(n);
	while (n){
		ret.push_back(n);
		n = select_next_node(n); 
	} 
	FILE_LOG(logDEBUG) << " of size "<< ret.size()<<std::endl;
	return ret;
}


/**
 *  Estimates all known estimates from node n
 * */
std::vector<zet> TreeAgent::move_estimates(Node* n){
	std::vector<zet> ret;
	for (child_map::const_iterator i = n->children.begin(); i != n->children.end(); ++i) {
		uint64 move_id=i->first;
		double move_value = (i->second->val)/(i->second->visits);
		bool player = n->player;
		zet z(move_id,move_value,player);
		FILE_LOG(logDEBUG)<<" Move estimate: "<< (i->second->val)<<"/"<<(i->second->visits)<<"="<<move_value<<std::endl;
		ret.push_back(z);
	}
	return ret;
}


void TreeAgent::mark_solved_if_all_children_solved(Node* n){
	if (n->solved){
		return;
	} 
	bool mark_solved=true;
	assert(n->children.size()>0);
	for (child_map::const_iterator i = n->children.begin(); i != n->children.end(); ++i) {
		if( (mark_solved=(mark_solved && i->second->solved))==false){
			return;
		} 
	}
	if (mark_solved){
		n->solved=true;
	}

}

/**
 * Mark node solved 
 * */
void TreeAgent::mark_solved(Node* n){
	mark_solved_if_all_children_solved(n);
}

/**
 * An average back_propagation
 * */
void TreeAgent::back_propagatate(double new_val, std::vector<Node*> nodes){
	for (std::vector<Node*>::const_reverse_iterator i = nodes.rbegin(); i != nodes.rend(); ++i) {
		Node* n = *i;
		n->val+=new_val;
		n->visits++;
		mark_solved(n);
		FILE_LOG(logDEBUG) << "after back-propagating "<< *n << std::endl ;
	}
}


/**
 * Free the tree when done
 **/
void TreeAgent::delete_tree(Node* root){
	for (child_map::iterator i = root->children.begin(); i != root->children.end(); ++i) {
		delete_tree(i->second);
	}
	root->children.clear();
	delete root;
}


/**
 * Returns the list of moves which are not expanded yet
 * */
std::vector<zet> TreeAgent::unexpanded_moves(Node* n){
	vector<zet> moves = enumerate_moves(n->m_board, n->player);
	for (std::vector<zet>::iterator i = moves.begin(); i != moves.end(); ) {
		if (n->children.find(i->zet_id)!= n->children.end()){
			moves.erase(i);
		}else{
			++i;
		}
	}
	return moves;
}

/**
 * Select a random move 
 */
uint64 TreeAgent::select_random_unknown_move(Node* n){
	std::vector<zet> moves=unexpanded_moves(n);
	return moves[rand() % moves.size()].zet_id;
}



/**
 * How many iterations 
 **/
int TreeAgent::get_iterations(){
	return get_int_property("iterations");
}

/**
 * Get the parameter for how many iterations
 * */
double TreeAgent::get_iter_gamma(){
	return get_double_property("gamma");
}


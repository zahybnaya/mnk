#include "treeagent.h"
#include "heuristic.h"
#include "board.h"
#include <assert.h>
#include <random>

/**
 * Returns a list of possible moves and their estimates. 
 */
std::vector<zet> TreeAgent::solve(board& b,bool player){
	FILE_LOG(logDEBUG) << "Starting to solve board:{"<< uint64tobinstring(b.pieces[0]) ;
	FILE_LOG(logDEBUG) << ","<< uint64tobinstring(b.pieces[1])<<"}" << std::endl;
	this->playing_color=player;
	Node* n = create_initial_state(b);
	double gamma = get_iter_gamma();
	std::geometric_distribution<int> iter_dist(gamma);
	int num_iterations= iter_dist(get_generator());
	build_tree(n,num_iterations);	
	std::vector<zet> ret= move_estimates(n);
	delete_tree(n);
	return ret;
}



/**
 * Creates the initial state 
 * */
Node* TreeAgent::create_initial_state(board b){
	Node* n =new Node(b,b.active_player()); 
	n->new_node=false;
	return n ;
}	


/**
 * Iteratively build a tree
 **/
int TreeAgent::build_tree(Node* n,int iterations){ 
	int iterNum=0;
	while (iterNum <= iterations){
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
	if (n->solved) return;
	std::vector<Node*> nodes = select_variation(n);	
	Node* lastNode = nodes.back();
	Node* parent = nodes[nodes.size()-2];
	uint64 move_id = -1;
	for (child_map::const_iterator i = parent->children.begin(); i != parent->children.end(); ++i) {
		if(i->second== lastNode){
			move_id = i->first;
		}
	}
	double new_val = evaulate(lastNode, parent, move_id);
	for(vector<Node*>::iterator i = nodes.begin() ; i!=nodes.end() ; ++i){ assert(!(*i)->new_node); }
	back_propagatate(new_val,nodes);
}


/**
 * Returns a variation of the tree starting from the root 
 * and up to the new state node
 */
std::vector<Node*> TreeAgent::select_variation(Node* n){
	std::vector<Node*> ret;
	ret.push_back(n);
	assert(!n->new_node);
	do{
		n = select_next_node(n); 
		ret.push_back(n);
	} while (!n->new_node);
	n->new_node=false;
	for(vector<Node*>::iterator i = ret.begin() ; i!=ret.end() ; ++i){ assert(!(*i)->new_node); }
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

void TreeAgent::mark_solved(Node* n){
	if (n->solved || n->new_node){
		//std::cout<<" moving-on because n.solved:"<<n->solved<<" and n->new_node:"<< n->new_node<<std::endl;
		return;
	} 
	if (!unexpanded_moves(n).empty()){
		//std::cout<<" moving-on because there are unexpaned_moves"<<std::endl;
		return;
	}
	bool mark_solved=true;
	assert(n->children.size()>0);
	for (child_map::const_iterator i = n->children.begin(); i != n->children.end(); ++i) {
		//std::cout<<" child.solved:  " << i->second->solved ;
		if( (mark_solved=(mark_solved && i->second->solved))==false){
			//std::cout<<" breaking  because of: " << i->second->solved <<" mark_solved:"<<mark_solved ;
			return;
		} 
	}
	if (mark_solved){
		n->solved=true;
		//std::cout<<" assiging solved on n ";
	}
}

/**
 * An average back_propagation
 * */
void TreeAgent::back_propagatate(double new_val, std::vector<Node*> nodes){
	for (std::vector<Node*>::const_reverse_iterator i = nodes.rbegin(); i != nodes.rend(); ++i) {
		Node* n = *i;
		assert(!n->new_node);
		n->val+=new_val;
		n->visits++;
		mark_solved(n);
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
 * Creates a new node to represent node and adds it as a child to parent
 */
Node* TreeAgent::expand(uint64 move,Node* parent){
	zet z = zet(move,0.0,parent->player);
	Node* new_node = new Node(parent->m_board+z,!parent->player);
	if (new_node->m_board.is_ended()){
		new_node->solved=true;
	}
	parent->children[move]=new_node; 
	return new_node;
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


#include "treeagent.h"
#include "heuristic.h"
#include "board.h"
#include <random>

/**
 * Returns a list of possible moves and their estimates. 
 */
std::vector<zet> TreeAgent::solve(board& b,bool player){
	FILE_LOG(logDEBUG) << "Starting to solve board:{"<< uint64tobinstring(b.pieces[0]) ;
	FILE_LOG(logDEBUG) << ","<< uint64tobinstring(b.pieces[1])<<"}" << std::endl;
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
	return new Node(b,b.active_player());
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
 *  Distribution for the number of iterations 
 * */
const DISTRIBUTION get_iteration_distribution(){
	return GEOMETRIC;
}

/**
 *  Parameter for the distribution 
 *  for the number of iterations TODO: Parse as language? e.g. iteration_distribution=G(0.4)/B(0.3)/Beta(0.3,0.4)
 * */
const double get_iteration_distribution_param(){
	return 0;

}


/**
 * Addition to the uct exploitation measurement
 * */
const DISTRIBUTION get_exploitation_noise_distribution(){
	return BERNOULLI;

}

const double get_exploitation_noise_param(){
	return 0;
}


/**
 *
 * A single iteraton of building the tree
 * */
void TreeAgent::iterate(Node* n){
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
	back_propagatate(new_val,nodes);
}


/**
 * Returns a variation of the tree starting from the root 
 * and up to the new state node
 */
std::vector<Node*> TreeAgent::select_variation(Node* n){
	std::vector<Node*> ret;
	ret.push_back(n);
	do{
		n = select_next_node(n); 
		ret.push_back(n);
	} while (!n->new_node);
	n->new_node=false;
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


/**
 * An average back_propagation
 * */
void TreeAgent::back_propagatate(double new_val, std::vector<Node*> nodes){
	for (std::vector<Node*>::const_iterator i = nodes.begin(); i != nodes.end(); ++i) {
		(*i)->val+=new_val;
		(*i)->visits++;
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
const int TreeAgent::get_iterations(){
	return get_int_property("iterations");
}

/**
 *
 * */
const double TreeAgent::get_iter_gamma(){
	return get_double_property("gamma");
}


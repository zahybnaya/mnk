#include "treeagent.h"
#include "heuristic.h"
#include "board.h"
#include "dotexporter.h"
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
			return !p.second->solved && !p.second->playing_color_won;
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
	int num_iterations= iter_dist(get_generator())+1;
	assert(num_iterations>0);
	FILE_LOG(logDEBUG) << " Number of iterations  "<< num_iterations<< std::endl;
	Node* n = create_initial_state(b);
	build_tree(n,num_iterations);	
	std::cout<<this->num_switches<<std::endl; 
	std::vector<zet> ret= move_estimates(n);
	delete_tree(n);
	post_solution();
	return ret;
}

void TreeAgent::pre_solution(){
	this->last_move_searched = -1;
	this->num_switches = 0;
}

/**
 * Creates a new node to represent node and adds it as a child to parent
 */
Node* TreeAgent::connect(uint64 move,Node* parent,double value,int visits){
	assert(parent);
	zet z = zet(move,value,parent->player); 
	Node* new_node = new Node(parent->m_board+z,!parent->player,value,visits);
	if (new_node->m_board.is_ended()){
		new_node->solved=true;
		if ((new_node->player == this->playing_color) && new_node->m_board.player_has_won(new_node->player)){
			new_node->playing_color_won=true;
		}
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


uint64 TreeAgent::get_first_move_id(const std::vector<Node*> &nodes){
	std::vector<Node*>::const_iterator it =  nodes.begin();
	Node* root = *it;
	Node* branch = *(++it);
	FILE_LOG(logDEBUG) << " Root:  "<<root << "  branch:"<<branch<< std::endl;
	for (child_map::const_iterator it = root->children.begin(); it!= root->children.end() ; ++it) {
		FILE_LOG(logDEBUG) << " Checking:  "<<it->second << std::endl;
		if (it->second == branch)
			return it->first;
	}
	throw runtime_error("cannot find child in children map ");
}

/**
 *
 * */
void TreeAgent::count_switches(const std::vector<Node*> &nodes){
	if (nodes.size() <= 1 ) {return ;} 
	uint64 branch_move =  get_first_move_id(nodes);
	if (branch_move == last_move_searched) {
		this->num_switches++; 
		last_move_searched = branch_move;
	}
}


/**
 * A single iteraton of building the tree
 * */
void TreeAgent::iterate(Node* n){
	assert(!n->m_board.is_ended());
	if (n->solved || n->playing_color_won){
		FILE_LOG(logDEBUG) << " Node is solved, returning "<< std::endl;
		return;
	}
	std::vector<Node*> nodes = select_variation(n);	
	count_switches(nodes);
	double new_val = expand(nodes.back());
	back_propagatate(new_val,nodes);
	//todot(n,std::cout);
}


/**
 * Returns a variation of the tree starting from the root 
 * and up to the new state node which should be expanded
 */
std::vector<Node*> TreeAgent::select_variation(Node* n){
	FILE_LOG(logDEBUG) << " Selecting variation ";
	std::vector<Node*> ret;
	while (n){
		ret.push_back(n);
		n = select_next_node(n); 
	} 
	FILE_LOG(logDEBUG) << " variation path size: "<< ret.size()<<std::endl;
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
 * Marks if the playing color had won : either by AND for the negative color or OR for the playing ccolor
 * */
void TreeAgent::mark_playing_color_won(Node* n){
	if(n->children.empty()) 
		return;
	bool use_or = (n->player == this->playing_color);
	bool mark_play = true;
	for (child_map::const_iterator i = n->children.begin(); i != n->children.end(); ++i) {
		if(use_or){
			if (i->second->playing_color_won) break;
			mark_play=false;
		} else if( (mark_play=(mark_play && i->second->playing_color_won))==false){
			return;
		} 
	}
	if (mark_play){
		n->playing_color_won = true;
	}
}

/**
 * A solved node is one that either all children are solved or 
 * that there is a winning variation from it. 
 * */
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
		mark_playing_color_won(n);
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


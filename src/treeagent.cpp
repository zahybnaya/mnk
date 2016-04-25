#include "treeagent.h"
#include "heuristic.h"
#include "board.h"
#include "dotexporter.h"
#include <assert.h>
#include <random>
#include <algorithm>

const double FORCED_WIN_VALUE = 100;
/**
 * Shuffles a vector from children map
 * */
std::vector<pair<uint64,Node*>> get_shuffled_vector(child_map c){
	std::vector<pair<uint64,Node*>> v;
	assert(c.size()>0);
	std::copy_if(c.begin(), c.end(), std::back_inserter(v),[](const std::pair<uint64,Node*> &p){
			return !p.second->solved && !p.second->forced_win && !p.second->forced_loss;
			});
	std::random_shuffle(v.begin(),v.end());
	return v;
}


/**
 * Returns a list of possible moves and their estimates. 
 */
std::vector<zet> TreeAgent::solve(board& b,bool player){
	FILE_LOG(logDEBUG) << "Starting to solve board:{"<< uint64tobinstring(b.pieces[0]) ;
	FILE_LOG(logDEBUG) << ","<< uint64tobinstring(b.pieces[1])<<"}" << std::endl;
	this->playing_color=player;
	double gamma = get_iter_gamma();
	std::geometric_distribution<int> iter_dist(gamma);
	this->max_iterations= iter_dist(get_generator())+1;
	assert(this->max_iterations>0);
	FILE_LOG(logDEBUG) << " Number of iterations  "<< max_iterations<< std::endl;
	Node* n = create_initial_state(b);
	FILE_LOG(logDEBUG) << " Root node  "<< n<< std::endl;
	build_tree(n);	
	std::vector<zet> ret= move_estimates(n);
	//print_time_prediction_metrics(b,n,ret);
	delete_tree(n);
	return ret;
}

double max_val(std::vector<zet> &zets, int player){
	std::sort(zets.begin(), zets.end(),[player](const zet& z1, const zet& z2){ return (player==BLACK)? (z1.val > z2.val):(z2.val > z1.val);  });
	return (zets[0].val);
}

double calc_best_diff(std::vector<zet> &zets, int player, bool nonlinearity){
	std::sort(zets.begin(), zets.end(),[player](const zet& z1, const zet& z2){ return (player==BLACK)? (z1.val > z2.val):(z2.val > z1.val);  });
	assert((player==BLACK)?zets[0].val>=zets[1].val:zets[0].val<=zets[1].val);
	if (zets.size()>2)
		assert((player==BLACK)?zets[1].val>=zets[2].val:zets[1].val<=zets[2].val);
	if(nonlinearity){
		return sigmoid(abs(zets[0].val) - sigmoid(zets[1].val));
	}
	return abs(zets[0].val - zets[1].val);
}


double average_diff(std::vector<zet> &zets, int player){
	double avg_diff=0;
	int diffs = 0;
	std::sort(zets.begin(), zets.end(),[player](const zet& z1, const zet& z2){ return (player==BLACK)? (z1.val > z2.val):(z2.val > z1.val);  });
	for (std::vector<zet>::const_iterator i = zets.begin(); ; ) {
		double v1 = i->val;
		++i;
		if (i==zets.end()) { break;}
		double v2 = i->val;
		avg_diff += abs(v2-v1);
		diffs+=1;
	}
	return avg_diff/diffs;
}

double calc_normalized_best_diff(std::vector<zet> &zets, int player){
	std::sort(zets.begin(), zets.end(),[player](const zet& z1, const zet& z2){ return (player==BLACK)? (z1.val > z2.val):(z2.val > z1.val);  });
	assert((player==BLACK)?zets[0].val>=zets[1].val:zets[0].val<=zets[1].val);
	if (zets.size()>2)
		assert((player==BLACK)?zets[1].val>=zets[2].val:zets[1].val<=zets[2].val);
	return abs(zets[0].val - zets[1].val)/average_diff(zets, player);
}



double calc_entropy(Node *n){
	double entropy=0;
	int sum_visits=0;
	std::for_each(n->children.begin(),n->children.end(),[&](std::pair<uint64,Node*> p){
                        sum_visits += p.second->visits;
			});
	for (child_map::const_iterator it = n->children.begin(); it!= n->children.end() ; ++it) {
		double px=double(it->second->visits)/sum_visits;
		entropy -= px*log(px); 
	}
	return entropy;
}


void TreeAgent::print_time_prediction_metrics(board& b, Node* n,std::vector<zet> &zets ){
	double best_diff = calc_best_diff(zets,this->playing_color);
	double normalized_best_diff = calc_normalized_best_diff(zets,this->playing_color);
	double best_val = max_val(zets,this->playing_color);
	double entropy =  calc_entropy(n);
	double count_evals =0;
	int num_consecutive=this->max_consecutive;
	double num_pieces=0;
	double num_patterns=0;
	int num_nodes = n->visits;
	//black,white,player,best_diff,entropy,tree_switch,count_evals"
	std::cout<<uint64tobinstring(b.pieces[BLACK])<<","<<uint64tobinstring(b.pieces[WHITE])<<","<< this->playing_color <<","<<best_diff<<","<<entropy<<","<<this->num_switches<<","<<count_evals << ","<< best_val <<","<< normalized_best_diff <<","<< num_consecutive<<","<< num_nodes << ","<<num_pieces <<","<< num_patterns  << std::endl; 

}

void TreeAgent::pre_solution(){
	this->last_move_searched = -1;
	this->num_switches = 0;
	this->max_consecutive = 0;
	this->consecutive = 0;
	this->iter_num = 0;
}


bool TreeAgent::is_stop(Node* n){
  return (this->iter_num>this->max_iterations);
}





/**
 * Creates a new node to represent node and adds it as a child to parent
 */
Node* TreeAgent::connect(uint64 move, Node* parent,double value,int visits){
	assert(parent);
	zet z = zet(move,value,parent->player); 
	Node* new_node = new Node(parent->m_board+z,!parent->player,value,visits);
	if (new_node->m_board.is_ended()){
		new_node->solved=true;
		//if ((new_node->player == this->playing_color) && new_node->m_board.player_has_won(new_node->player)){
		if (new_node->m_board.player_has_won(new_node->player)){
			new_node->forced_win=true;
		}
		if (new_node->m_board.player_has_won(!new_node->player)){
			assert(!new_node->forced_win);
			new_node->forced_loss=true;
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
int TreeAgent::build_tree(Node* n){ 
	this->iter_num=0;
	while (!is_stop(n)){
		FILE_LOG(logDEBUG) << " Starting iteration "<< this->iter_num<< std::endl;
		iterate(n);
		this->iter_num++;
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
	if (nodes.size() <= 1 ) {
		FILE_LOG(logDEBUG) << " Variation of size 1 no counting"<< std::endl;
		return;
	} 
	uint64 branch_move = get_first_move_id(nodes);
	if (branch_move != last_move_searched) {
		this->num_switches++; 
		last_move_searched = branch_move;
		this->consecutive = 0;
	} else {
		this->consecutive++;
		this->max_consecutive=(this->consecutive>this->max_consecutive)?this->consecutive:this->max_consecutive;
	}
}


/**
 * A single iteraton of building the tree
 * */
void TreeAgent::iterate(Node* n){
	assert(!n->m_board.is_ended());
	if (n->solved || n->forced_win || n->forced_loss){
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
	FILE_LOG(logDEBUG) << "Selection variation path size: "<< ret.size()<<std::endl;
	return ret;
}


/**
 *  Estimates all known estimates from node n
 * */
std::vector<zet> TreeAgent::move_estimates(Node* n){
	std::vector<zet> ret;
	FILE_LOG(logDEBUG)<<" Move estimates:";
	for (child_map::const_iterator i = n->children.begin(); i != n->children.end(); ++i) {
		uint64 move_id=i->first;
		if(i->second->visits==0) {
			continue;
		}
		double move_value = (i->second->val)/(i->second->visits);
		bool player = n->player;
		zet z(move_id,move_value,player);
		FILE_LOG(logDEBUG)<<move_id<<":"<<move_value<<" ";
		ret.push_back(z);
	}
	FILE_LOG(logDEBUG)<<std::endl;
	return ret;
}


/**
 * if one of the children is forces_loss then node is forced_win. 
 * if all children are forced_win then node is forced_loss
 * */
void TreeAgent::mark_forced_win_loss(Node* n){
	if(n->children.empty()) 
		return;
	n->forced_win=false;
	n->forced_loss=true;
	for (child_map::const_iterator i = n->children.begin(); i != n->children.end(); ++i) {
			if (!i->second->forced_win){
				n->forced_loss = false;
			} 
			if (i->second->forced_loss){
				n->forced_win = true;
				n->val = ((n->player==BLACK)?1:-1)*FORCED_WIN_VALUE * n->visits;
			}
	} 
	if(n->forced_loss){
		n->val = ((n->player==BLACK)?-1:1)*FORCED_WIN_VALUE * n->visits;
	}
	if (n->solved && !n->forced_loss && !n->forced_win){
		//n->val = 0;
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
		if( (mark_solved=(mark_solved && (i->second->solved || i->second->forced_win || i->second->forced_loss)))==false){
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
		FILE_LOG(logDEBUG) << "before back-propagating :"<< n->val <<"/" <<n->visits<< std::endl ;
		n->val+=new_val;
		n->visits++;
		mark_solved(n);
		mark_forced_win_loss(n);
		FILE_LOG(logDEBUG) << "after back-propagating :"<< n->val <<"/" <<n->visits<< std::endl ;
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
 * Get the parameter for how many iterations
 * */
double TreeAgent::get_iter_gamma(){
	return get_double_property("gamma");
}


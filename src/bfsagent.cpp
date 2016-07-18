#include "bfsagent.h"
#include <math.h>
#include <random>
#include <algorithm>
#include <assert.h>
#include <sstream>

/**
 * Initializaion of the heuristic properties
 * */
void BFSAgent::init(){
	HeuristicsAgent::init();
	branching_factor=std::bernoulli_distribution(fmod(get_K0(),1.0));
}

std::string print_children(Node* n){
	std::stringstream ss;
	ss<<" Printing children of node.";
	ss<<((n->player==BLACK)?"BLACK ":"WHITE ");
	ss<<n->val/n->visits<<":";
	for (child_map::const_iterator i = n->children.begin(); i != n->children.end(); ++i) {
		ss<<"{"<< (i->second->val/i->second->visits) << ", forced_win:" <<i->second->forced_win << " forced_loss:" <<i->second->forced_loss << " solved:" << i->second->solved<<"}";
		if(!i->second->forced_win && !i->second->forced_loss && i->second->solved){
			ss<<n->m_board;
		}
	}
	ss<<std::endl;
	return ss.str();
}


unsigned int BFSAgent::get_actual_branching_factor(vector<zet>& zets){
	unsigned int k = int(get_K0()) + branching_factor(get_generator());
	FILE_LOG(logDEBUG) << " selected branching factor of "<<k<<std::endl;
	return k<zets.size()?k:zets.size();
}


/**
 * 
 * */
bool better_for_black(pair<uint64,Node*> n1p, pair<uint64,Node*> n2p) {
	Node* n1 = n1p.second;
	Node* n2 = n2p.second;
	assert(n1->player==n2->player);
	double n1_val = n1->val/n1->visits;
	double n2_val = n2->val/n2->visits;
	// parent is the opposite color
	return  (n1->player == BLACK) ? (n1_val > n2_val):(n1_val < n2_val);
} 

/**
 * The comparator TODO:test this
 * */
bool better(pair<uint64,Node*> n1p, pair<uint64,Node*> n2p) {
	Node* n1 = n1p.second;
	Node* n2 = n2p.second;
	assert(n1->player==n2->player);
	double n1_val = n1->val/n1->visits;
	double n2_val = n2->val/n2->visits;
	return n2_val < n1_val;
} 



void assert_children(std::vector<Node*> nodes){
	Node* prev = NULL;
	Node*	n = NULL;
	for (std::vector<Node*>::const_reverse_iterator i = nodes.rbegin(); i != nodes.rend(); ++i) {
		prev = n;
		n=*i;
		if (prev != NULL){
			bool found_child = false;
			for (child_map::const_iterator ci = n->children.begin(); ci !=n->children.end(); ++ci) {
				if(ci->second==prev){
					found_child = true;
					break;
				}
			}
			assert(found_child);
		}
	}
}

/***
 *
 * */
void print_path(std::vector<Node*> nodes){
	std::stringstream ss; 
	for (std::vector<Node*>::const_reverse_iterator i = nodes.rbegin(); i != nodes.rend(); ++i) {
		Node* n = *i;
		ss<< (n->val/n->visits) <<"," ; 
	}
	FILE_LOG(logDEBUG) << ss.str() << std::endl;
}
/**
 * A minimax back_propagation
 * */
void BFSAgent::back_propagatate(double new_val, std::vector<Node*> nodes){
	assert_children(nodes);
	FILE_LOG(logDEBUG) << " back-propagating begins " <<std::endl;
	print_path(nodes);
	for (std::vector<Node*>::const_reverse_iterator i = nodes.rbegin(); i != nodes.rend(); ++i) {
		Node* n = *i;
		double old_val = (n->val/n->visits);
		FILE_LOG(logDEBUG) << " before back-propagating :"<< n->val <<"/" <<n->visits<<"="<<(n->val/n->visits)<< std::endl ;
		n->visits++;
		if (n->visits==1){
			n->val=new_val*n->visits;
		} else {
			Node* argmax = std::max_element(n->children.begin(),n->children.end(),better_for_black)->second;
			n->val=(argmax->val/argmax->visits)*n->visits;
		}
		mark_solved(n);
		mark_forced_win_loss(n);
		FILE_LOG(logDEBUG) << " after back-propagating :"<< n->val <<"/" <<n->visits<<"="<<(n->val/n->visits)<< std::endl ;
		if ((n->val/n->visits)==old_val){
			//FILE_LOG(logDEBUG) << print_children(n);
			print_path(nodes);
		}
		//assert((n->val/n->visits)!=old_val);
	}
	print_path(nodes);
}

Node* tie_break(std::vector<pair<uint64,Node*>> v, double val){
	std::vector<pair<uint64,Node*>> maxs;
	std::copy_if(v.begin(), v.end(), std::back_inserter(maxs),[val](const std::pair<uint64,Node*> &p){
			return (p.second->val/p.second->visits==val);
			});
	//FILE_LOG(logDEBUG) << " tie-braking amongst "<< maxs.size() <<" candidates with val:" << val<< std::endl;
	std::random_shuffle(maxs.begin(),maxs.end()); //TODO use std::advance
	return maxs.begin()->second;
}

std::string print_v(std::vector<pair<uint64,Node*>> v){
	std::stringstream ss;
	for (std::vector<pair<uint64,Node*>>::const_iterator i = v.begin(); i != v.end(); ++i) {
		ss<<"{"<< (i->second->val/i->second->visits) << "}";
	}
	ss<<std::endl;
	return ss.str();
}


/***
 * Selection policy
 * */
Node* BFSAgent::select_next_node(Node* n) {
	assert(!n->solved);
	assert(!n->m_board.is_ended());
	FILE_LOG(logDEBUG)<< "selecting next node from " <<*n <<" with "<<n->visits<<" visits"<<std::endl;
	if (n->children.empty()){
		FILE_LOG(logDEBUG)<< " empty children - returning null " <<std::endl;
		return NULL;
	}
	std::vector<pair<uint64,Node*>> v= get_shuffled_vector(n->children);
	if(v.size()<=0){
		FILE_LOG(logERROR) << " Empty children vector from node"<<std::endl; 
		for (child_map::const_iterator i = n->children.begin(); i != n->children.end(); ++i) {
			FILE_LOG(logERROR) << " forced_win: " <<i->second->forced_win << " forced_loss: " <<i->second->forced_loss << " solved: " << i->second->solved ;
		}
		FILE_LOG(logERROR)<< "Total of "<< n->children.size() <<" children" <<std::endl;
	}
	assert(v.size()>0);
	std::pair<uint64,Node*> argmax =
		*std::max_element(v.begin(),v.end(),better_for_black);
	Node* ret = tie_break(v, (argmax.second->val/argmax.second->visits));
	return ret;
}

/**
 * Removes features from h for entire tree 
 * 
 * */
void BFSAgent::pre_solution(){
	TreeAgent::pre_solution();
	h.self=get_playing_color();
	h.remove_features();
}

/**
 * restore features after each solution
 * */
void BFSAgent::post_solution(){
	h.restore_features();
}

double value_for_new_node(Node* parent, zet z){
	return (parent->val/parent->visits)+(((parent->player==BLACK)?1:-1)*z.val);
}

/**
 *  Expanding a node
 * */
double BFSAgent::expand(Node* n){
	bool is_root = (n->visits==0);
	if (is_root) {
                n->val=h.evaluate(n->m_board);
                n->visits=1;
        }
	//FILE_LOG(logDEBUG) << "Expending Node "<<*n<<std::endl;
	std::vector<zet> zets;
	h.get_moves(n->m_board,n->player,false,zets);
	double ret_val=0;
	unsigned int actual_branching_factor;
	if (is_root){
		actual_branching_factor =get_actual_branching_factor(zets);
	}else{
		actual_branching_factor = zets.size();
	}
	assert(actual_branching_factor<=zets.size());
	for (unsigned int i=0;i<actual_branching_factor;++i){
		zet z = zets[i];
		if (i==0){ret_val=value_for_new_node(n,z);}
		connect(z.zet_id,n,value_for_new_node(n,z),1);
	}
	//FILE_LOG(logDEBUG) << " expansion returned the value "<<ret_val<<std::endl;
	return ret_val;
}



///**
// * Evaluaties a new node
// **/
//double BFSAgent::evaulate(Node* /*lastNode*/, Node* parent, uint64 move_id){
//	h.self = get_playing_color();
//	std::vector<zet> moves = h.get_moves(parent->m_board/*parent*/,parent->player /*parent*/,false); 
//	for ( std::vector<zet>::const_iterator i = moves.begin(); i != moves.end(); ++i) {
//		if (i->zet_id == move_id){
//			return i->val;
//		}
//	}
//	throw std::runtime_error("Can't evaluate state");
//}
//
double BFSAgent::get_K0() {
	return get_double_property("K0");
}


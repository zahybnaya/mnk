#include "bfsagent.h"
#include <math.h>
#include <random>
#include <algorithm>
#include <assert.h>

/**
 * Initializaion of the heuristic properties
 * */
void BFSAgent::init(){
	Agent::init();
	branching_factor=std::bernoulli_distribution(fmod(get_K0(),1.0));
	h.gamma  = get_gamma();
	h.delta   = get_delta();
	h.vert_scale   = get_vert_scale();
	h.diag_scale   = get_diag_scale();
	h.opp_scale   = get_opp_scale();
	for(int i=0;i<6;i++)
		h.weight[i]=get_weight(i);
	h.weight[16]=get_triangle_weight();
	h.update();
	FILE_LOG(logDEBUG) << "Init an agent with the following properties- " << " D0:" << get_D0() <<" K0:"<< get_K0() <<" h.gamma:"<< get_gamma() << " h.delta:" <<  get_delta() << " h.vert_scale:"<<   get_vert_scale() << " h.diag_scale:"<< get_diag_scale() <<" h.opp_scale: " << get_opp_scale() << " h.weight[0]:"<<get_weight(0) << " lapse_rate" << get_lapse_rate() << std::endl;

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
	return n2_val > n1_val;
} 



/***
 * Selection policy
 * */
Node* BFSAgent::select_next_node(Node* n) {
	assert(!n->solved);
	assert(!n->m_board.is_ended());
	FILE_LOG(logDEBUG)<< "selecting next node from " <<*n <<std::endl;
	if (n->children.empty()){
		FILE_LOG(logDEBUG)<< " empty children - returning null " <<std::endl;
		return NULL;
	}
	std::vector<pair<uint64,Node*>> v= get_shuffled_vector(n->children);
	if(v.size()<=0){
		for ( child_map::const_iterator i = n->children.begin(); i != n->children.end(); ++i) {
			FILE_LOG(logERROR) << *(i->second);
		}
		FILE_LOG(logERROR)<< "Total of "<< n->children.size() <<" children" <<std::endl;
	}
	assert(v.size()>0);
	std::pair<uint64,Node*> argmax =
		*std::max_element(v.begin(),v.end(),better);
	FILE_LOG(logDEBUG) << " returning node "<< *argmax.second<< std::endl;
	return argmax.second;

}

/**
 * Removes features from h for entire tree 
 * 
 * */
void BFSAgent::pre_solution(){
	h.self=get_playing_color();
	h.remove_features();
}

/**
 * restore features after each solution
 * */
void BFSAgent::post_solution(){
	h.restore_features();
}


/**
 * Changes from implementation to another
 * */
double BFSAgent::expand(Node* n){
	int k = int(get_K0()) + branching_factor(get_generator());
	FILE_LOG(logDEBUG) << "Expending Node "<<*n<<std::endl;
	FILE_LOG(logDEBUG) << "selected branching factor of "<<k<<std::endl;
	std::vector<zet> ordered_moves = h.get_moves(n->m_board,n->player,false);
	for (int i=0;i<k;i++){
		zet z = ordered_moves[i];
		connect(z.zet_id,n,z.val,1);
	}
	FILE_LOG(logDEBUG) << " expansion returned the value "<<ordered_moves[0].val<<std::endl;
	return ordered_moves[0].val;
}


/**
 * Evaluaties a new node
 **/
double BFSAgent::evaulate(Node* /*lastNode*/, Node* parent, uint64 move_id){
	h.self = get_playing_color();
	std::vector<zet> moves = h.get_moves(parent->m_board/*parent*/,parent->player /*parent*/,false); 
	for ( std::vector<zet>::const_iterator i = moves.begin(); i != moves.end(); ++i) {
		if (i->zet_id == move_id){
			return i->val;
		}
	}
	throw std::runtime_error("Can't evaluate state");
}

double BFSAgent::get_D0() {
	return get_double_property("D0");
}
double BFSAgent::get_K0() {
	return get_double_property("K0");
}
double BFSAgent::get_gamma() {
	return get_double_property("gamma");
}
double BFSAgent::get_delta() {
	return get_double_property("delta");
}
double BFSAgent::get_vert_scale() {
	return get_double_property("vert_scale");
}
double BFSAgent::get_diag_scale() {
	return get_double_property("diag_scale");
}
double BFSAgent::get_opp_scale() {
	return get_double_property("opp_scale");
}

double BFSAgent::get_triangle_weight(){
	return get_double_property("triangle_weight");
}

double BFSAgent::get_weight(int i){
	std::string t="weights_"+std::to_string(i);
	return get_double_property(t);
}


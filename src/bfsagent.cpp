#include "bfsagent.h"

/**
 * Evaluaties a new node
 **/
double BFSAgent::evaulate(Node* lastNode, Node* parent, uint64 move_id){

	h.remove_features();
	std::vector<zet> moves = h.get_moves(parent->m_board/*parent*/,parent->player /*parent*/,false); 
	for ( std::vector<zet>::const_iterator i = moves.begin(); i != moves.end(); ++i) {
		if (i->zet_id == move_id){
			h.restore_features();
			return i->val;
		}
	}
	
	return -1;
}

const double BFSAgent::get_D0(){
	return get_double_property("D0");
}
const double BFSAgent::get_K0(){
	return get_double_property("K0");
}
const double BFSAgent::get_gamma(){
	return get_double_property("gamma");
}
const double BFSAgent::get_delta(){
	return get_double_property("delta");
}
const double BFSAgent::get_vert_scale(){
	return get_double_property("vert_scale");
}
const double BFSAgent::get_diag_scale(){
	return get_double_property("diag_scale");
}
const double BFSAgent::get_opp_scale(){
	return get_double_property("opp_scale");
}

/**
 *
 * */
void BFSAgent::init():Agent::init(){
	mt19937_64 g;
	g.seed(time(NULL));
	generator.seed(g());
	lapse = std::bernoulli_distribution(get_lapse_rate()); 
	h.D0 = get_D0();
	h.K0 = get_K0();
	h.gamma  = get_gamma();
	h.delta   = get_delta();
	h.vert_scale   = get_vert_scale();
	h.diag_scale   = get_diag_scale();
	h.opp_scale   = get_opp_scale();
}




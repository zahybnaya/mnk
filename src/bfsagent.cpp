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
	h.restore_features();
	return -1;
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
/**
 *
 * */
void BFSAgent::init(){
	Agent::init();
	h.D0 = get_D0();
	h.K0 = get_K0();
	h.gamma  = get_gamma();
	h.delta   = get_delta();
	h.vert_scale   = get_vert_scale();
	h.diag_scale   = get_diag_scale();
	h.opp_scale   = get_opp_scale();
	for(int i=0;i<6;i++)
		h.weight[i]=get_weight(i);
	h.weight[16]=get_triangle_weight();
	h.update();
}




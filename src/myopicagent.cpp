#include "myopicagent.h"
#include "board.h"
#include "heuristic.h"
#include <random> 


std::vector<zet> MyopicAgent::solve(board& b,bool player){
	this->playing_color = player;
	std::vector<zet> moves = h.get_moves(b,player,false); 
	return moves;
}

void MyopicAgent::pre_solution(){
	h.self=get_playing_color();
	h.remove_features();
}

/**
 * restore features after each solution
 * */
void MyopicAgent::post_solution(){
	h.restore_features();
}


double MyopicAgent::get_delta() {
	return get_double_property("delta");
}
double MyopicAgent::get_vert_scale() {
	return get_double_property("vert_scale");
}
double MyopicAgent::get_diag_scale() {
	return get_double_property("diag_scale");
}
double MyopicAgent::get_opp_scale() {
	return get_double_property("opp_scale");
}

double MyopicAgent::get_triangle_weight(){
	return get_double_property("triangle_weight");
}

double MyopicAgent::get_weight(int i){
	std::string t="weights_"+std::to_string(i);
	return get_double_property(t);
}
/**
 * Initializaion of the heuristic properties
 * */
void MyopicAgent::init(){
	Agent::init();
	h.delta   = get_delta();
	h.vert_scale   = get_vert_scale();
	h.diag_scale   = get_diag_scale();
	h.opp_scale   = get_opp_scale();
	for(int i=0;i<6;i++)
		h.weight[i]=get_weight(i);
	h.weight[16]=get_triangle_weight();
	h.update();
	FILE_LOG(logDEBUG) << "Init an agent with the following properties- "  << " h.delta:" <<  get_delta() << " h.vert_scale:"<<   get_vert_scale() << " h.diag_scale:"<< get_diag_scale() <<" h.opp_scale: " << get_opp_scale() << " h.weight[0]:"<<get_weight(0) << " lapse_rate" << get_lapse_rate() << std::endl;

}




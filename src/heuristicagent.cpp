#include "heuristicagent.h"
#include "board.h"
#include "heuristic.h"
#include <random> 


void HeuristicsAgent::pre_solution(){
	FILE_LOG(logDEBUG)<<" pre_solution of myopic. Setting self(playing_color) to "<< get_playing_color()<<std::endl;
	h.remove_features();
}

/**
 * restore features after each solution
 * */
void HeuristicsAgent::post_solution(){
	FILE_LOG(logDEBUG)<<" post-solution of myopic. "<< get_playing_color()<<std::endl;
	h.restore_features();
}


double HeuristicsAgent::get_center_weight() {
	return get_double_property("center_weight");
}


double HeuristicsAgent::get_delta() {
	return get_double_property("delta");
}
double HeuristicsAgent::get_vert_scale() {
	return get_double_property("vert_scale");
}
double HeuristicsAgent::get_diag_scale() {
	return get_double_property("diag_scale");
}
double HeuristicsAgent::get_opp_scale() {
	return get_double_property("opp_scale");
}

double HeuristicsAgent::get_act_scale() {
	return get_double_property("act_scale");
}

double HeuristicsAgent::get_triangle_weight(){
	return get_double_property("triangle_weight");
}

double HeuristicsAgent::get_weight(int i){
	std::string t="weights_"+std::to_string(i);
	return get_double_property(t);
}
/**
 * Initializaion of the heuristic properties
 * */
void HeuristicsAgent::init(){
	Agent::init();
	h.delta   = get_delta();
	h.vert_scale   = get_vert_scale();
	h.diag_scale   = get_diag_scale();
	h.opp_scale   = get_opp_scale();
	h.act_scale   = get_act_scale();
	h.center_weight = get_center_weight();
	for(int i=0;i<5;i++)
		h.weight[i]=get_weight(i);
	h.weight[25]=get_triangle_weight();
	h.update();
	FILE_LOG(logDEBUG) << "Init an agent with the following properties- "  << " h.delta:" <<  get_delta() << " h.vert_scale:"<<   get_vert_scale() << " h.diag_scale:"<< get_diag_scale() <<" h.opp_scale: " << get_opp_scale() << " h.weight[0]:"<<get_weight(0) << " lapse_rate" << get_lapse_rate() << std::endl;

}




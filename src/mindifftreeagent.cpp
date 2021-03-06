#include <assert.h>
#include "mindifftreeagent.h"


double MinDiffTreeAgent::get_stop_threshold(){
	return get_double_property("stop_threshold");
}

double MinDiffTreeAgent::get_abrupt_stop_rate(){
	return get_double_property("abrupt_rate");
}


void MinDiffTreeAgent::pre_solution(){
	BFSAgent::pre_solution();
	this->persistent_ratio_times = 0;
}

void MinDiffTreeAgent::init(){
	BFSAgent::init();
	abrupt_stop = std::bernoulli_distribution(get_abrupt_stop_rate()); 
}

int MinDiffTreeAgent::get_convergence_times(){
	return get_double_property("convergence_times");
}


double MinDiffTreeAgent::get_stop_decrease_rate(){
	return get_double_property("stop_decrease_rate");
}

bool MinDiffTreeAgent::is_stop(Node* n) {
	if (n->forced_win || n->forced_loss || n->solved)
	       	return true;
	std::vector<zet> zets = move_estimates(n);
	if (zets.size()<2) return false;
	double min_diff= calc_best_diff(zets, n->player /* in case of problems, start with the player*/,true);
	int iteration = get_iter_num();
	bool cond= (min_diff > get_stop_threshold() * 1/pow(iteration,get_stop_decrease_rate()));
	return cond;
}


//bool MinDiffTreeAgent::is_stop(Node* n , int iteration , int player) {
//	if (n->forced_win || n->forced_loss || n->solved)
//	       	return true;
//	std::vector<zet> zets = move_estimates(n);
//	if (zets.size()<2) return false;
//	double min_diff= calc_best_diff(zets,  player);
//	double avg_diff= average_diff(zets,  player);
//	assert(avg_diff>0);
//	double ratio = min_diff/avg_diff;
//	if (ratio == this->last_ratio){
//		if(++this->persistent_ratio_times > get_convergence_times()){
//			this->last_ratio = -1;
//			this->persistent_ratio_times = 0;
//			return true;
//		}  
//	}else {
//		this->persistent_ratio_times = 0;
//	} 
//	this->last_ratio = ratio;
//	//FILE_LOG(logDEBUG)<<" Min/Avg Ratio:"<<ratio <<" iteration:" <<iteration<<std::endl;
//	bool cond= (ratio > get_stop_threshold() * 1/pow(iteration,get_stop_decrease_rate()));
//	if(cond){
//	       	//FILE_LOG(logDEBUG)<< " completed " << iteration <<" iterations" <<std::endl;
//	}
//	return cond;
//}
//
//

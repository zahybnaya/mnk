#include "mindifftreeagent.h"

int MinDiffTreeAgent::build_tree(Node* n,int /*iterations*/){
	int iterNum = 0;
       	while (!is_stop(n, iterNum, n->player)){
		iterate(n);
		iterNum++;
	}
	return 0;
}
double MinDiffTreeAgent::get_stop_threshold(){
	return get_double_property("stop_threshold");
}

double MinDiffTreeAgent::get_abrupt_stop_rate(){
	return get_double_property("abrupt_rate");
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

bool MinDiffTreeAgent::is_stop(Node* n , int iteration , int player) {
	std::vector<zet> zets = move_estimates(n);
	if (zets.size()<2) return false;
//	if (abrupt_stop(get_generator())){
//		std::cout<< " ABRUPT* " << iteration <<" iterations" <<std::endl;
//		return true;
//	}
	double min_diff= calc_best_diff(zets,  player);
	double avg_diff= average_diff(zets,  player);
	FILE_LOG(logDEBUG)<<" Min/Avg Ratio:"<<(min_diff/avg_diff)  <<" iteration:" <<iteration<<std::endl;
	bool cond= (min_diff/avg_diff > get_stop_threshold() * 1/pow(iteration,get_stop_decrease_rate()));
	//std::cout<<min_diff/avg_diff << " " << get_stop_threshold() * 1/pow(iteration,get_stop_decrease_rate())<<std::endl;
	if(cond){
	       	FILE_LOG(logDEBUG)<< " completed " << iteration <<" iterations" <<std::endl;
		//std::cout<< " completed " << iteration <<" iterations" <<std::endl;
	}
	return cond;
}



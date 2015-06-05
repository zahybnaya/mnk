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

//
//bool MinDiffTreeAgent::is_stop(Node* n , int iteration , int player) {
//	double k = 100;
//	std::vector<zet> zets = move_estimates(n);
//	if (zets.size()<2) return false;
//	double min_diff= calc_best_diff(zets,  player);
//	double avg_diff= average_diff(zets,  player);
//	double alpha = 1 / (1+exp(-(iteration/double(100))));
//	FILE_LOG(logDEBUG)<<" Min/Avg Ratio:"<<(min_diff/avg_diff) << " 1-alpha:"<< (1-alpha) << " k:"<<k <<" iteration:" <<iteration<<std::endl;
//	bool cond= (min_diff/avg_diff > k*(1-(alpha)));
//	if(cond){
//	       	FILE_LOG(logDEBUG)<< " completed " << iteration <<" iterations" <<std::endl;
//	}
//	return cond;
//
//}
//


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
	bool cond= (min_diff/avg_diff > get_stop_threshold() * 1/pow(iteration,0.1));
	if(cond){
	       	FILE_LOG(logDEBUG)<< " completed " << iteration <<" iterations" <<std::endl;
		std::cout<< " completed " << iteration <<" iterations" <<std::endl;
	}
	return cond;
}



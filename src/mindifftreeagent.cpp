#include "mindifftreeagent.h"

int MinDiffTreeAgent::build_tree(Node* n,int /*iterations*/){
	int iterNum = 0;
       	while (!is_stop(n, iterNum, n->player)){
		iterate(n);
		iterNum++;
	}
	return 0;
}


bool MinDiffTreeAgent::is_stop(Node* n , int iteration , int player) {
	double k = 100;
	std::vector<zet> zets = move_estimates(n);
	if (zets.size()<2) return false;
	double min_diff= calc_best_diff(zets,  player);
	double avg_diff= average_diff(zets,  player);
	double alpha = 1 / (1+exp(-(iteration/double(100))));
	FILE_LOG(logDEBUG)<<" Min/Avg Ratio:"<<(min_diff/avg_diff) << " 1-alpha:"<< (1-alpha) << " k:"<<k <<" iteration:" <<iteration<<std::endl;
	bool cond= (min_diff/avg_diff > k*(1-(alpha)));
	if(cond){
	       	FILE_LOG(logDEBUG)<< " completed " << iteration <<" iterations" <<std::endl;
	}
	return cond;

}



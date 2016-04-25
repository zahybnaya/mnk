#include <algorithm>
#include "consistentmoveagent.h"

void ConsistentMoveAgent::pre_solution(){
	DefaultAgent::pre_solution();
	this->persistent_moves = 0;
	this->current_zet_id = 0;
}


bool ConsistentMoveAgent::is_stop(Node* n){
	if (TreeAgent::is_stop(n))
		return true;
	std::vector<zet> s=move_estimates(n);
	if(s.size()<2){
		FILE_LOG(logDEBUG)<<" IS_STOP: less than two moves so false" <<std::endl;
		return false;}
	zet r;
	if (n->player == BLACK || is_negamax()){
		r=*std::max_element(s.begin(),s.end(),[](const zet& z1, const zet& z2 ){ return z1.val < z2.val;});
	} else{
		r=*std::min_element(s.begin(),s.end(),[](const zet& z1, const zet& z2 ){ return z1.val < z2.val;});
	}
	if(r.zet_id==current_zet_id)
		persistent_moves++;
	else{
		current_zet_id = r.zet_id;
		persistent_moves=0;
	} 
	bool ans=persistent_moves>get_consistent_times();
	FILE_LOG(logDEBUG)<<" IS_STOP: persistent_moves:"<<persistent_moves<<" get_consistent_times():"<<get_consistent_times() <<"So answer is:"<<ans <<std::endl;
	return ans; 
}

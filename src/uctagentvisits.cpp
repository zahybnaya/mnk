#include "uctagentvisits.h"
#include <cassert>
#include <algorithm>
/**
 * Returns a list of possible moves and their estimates. 
 */
std::vector<zet> UCTAgentVisits::solve(board& b,bool player){

	std::vector<zet> ret;
	this->playing_color=player;
	double gamma = get_iter_gamma();
	std::geometric_distribution<int> iter_dist(gamma);
	this->max_iterations= iter_dist(get_generator())+1;
	assert(this->max_iterations>0);
	Node* n = create_initial_state(b);
	build_tree(n);	
	int max_visits= std::max_element(n->children.begin(),n->children.end(),[](const std::pair<uint64,Node*> x1,const std::pair<uint64,Node*> x2){ 
			return x1.second->visits < x2.second->visits;})->second->visits;
	for (auto child : n->children){
		zet z(child.first,0,n->player);
		if(child.second->visits == max_visits){
			z.val = (n->player==BLACK)?100:-100;
		}
		ret.push_back(z);
	}
	delete_tree(n);
	return ret;
}



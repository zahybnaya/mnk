#include <assert.h>
#include "defaultagent.h"

/**
 * Assumes ordered zets
 * */
unsigned int DefaultAgent::get_actual_branching_factor(std::vector<zet>& zets){
  double prune_threshold = get_prune_threshold();
  double best_value = zets.front().val; 
  size_t i=1;
  double oldval=0;
  while ( i < zets.size() && (std::abs(best_value - zets.at(i).val) < prune_threshold)){
      assert(i==1 || oldval > zets.at(i).val);
      oldval = zets.at(i).val;
      i++;
  }
  return i;
}


/***
 * The stop condition
 * */
bool DefaultAgent::is_stop(Node* n){
  if (TreeAgent::is_stop(n))// || n->children.size() <= 1)
    return true;
  std::vector<zet> zets=move_estimates(n);
  if(zets.size() > 2)
	  if(std::abs(zets[0].val - zets[1].val) > get_stop_threshold())
		  return true;
  return false;
}

double DefaultAgent::get_stop_threshold(){
	return get_double_property("stop_threshold");
}

double DefaultAgent::get_prune_threshold(){
	return get_double_property("prune_threshold");
}

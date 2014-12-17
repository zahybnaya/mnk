#include "bfsagent.h"

/**
 * BFS agent is only a UCT agent with no exploration
 * */
double BFSAgent::get_exploration_constant(){
	return 0;
} 


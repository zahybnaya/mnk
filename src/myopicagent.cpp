#include "myopicagent.h"
#include "board.h"
#include "heuristic.h"
#include <random> 


std::vector<zet> MyopicAgent::solve(board& b,bool player){
	std::vector<zet> moves = h.get_moves(b,player,false); 
	return moves;
}



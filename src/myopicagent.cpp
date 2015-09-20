#include "myopicagent.h"
#include "board.h"
#include "heuristic.h"
#include <random> 


std::vector<zet> MyopicAgent::solve(board& b,bool player){
	this->playing_color = player;
	h.self = player;
	FILE_LOG(logDEBUG)<<" evaluating moves using "<< h.Nfeatures <<" features" <<std::endl;
	std::vector<zet> moves = h.get_moves(b,player,false); 
	return moves;
}


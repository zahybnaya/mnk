#include "myopicagent.h"
#include "board.h"
#include "heuristic.h"

std::vector<zet> MyopicAgent::solve(board& b,bool player){
	heuristic h;
	vector<zet> moves = h.enumerate_moves(b, player);
	for (std::vector<zet>::iterator i = moves.begin(); i != moves.end(); ++i) {
		board bnew=b+*i;
		i->val= h.evaluate(bnew);
	}
	return moves;
}

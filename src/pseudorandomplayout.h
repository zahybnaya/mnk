#ifndef PSEUDORANDOMPLAYOUT_H
#define PSEUDORANDOMPLAYOUT_H
#include "randomplayout.h"
#include "board.h"
#include <random>

/**
 * Performs a pseudo-random playout to a final state 
 * and then retrieves {-1.0,1} based on the state of the fianal board
 * */
class PseudoRandomPlayout : public RandomPlayout
{
public:
	~PseudoRandomPlayout(){};
	PseudoRandomPlayout();
	zet select_random_move(board& b);
protected:
	Motif winNextMove;
};

#endif /* end of include guard */

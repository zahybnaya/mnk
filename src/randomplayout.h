#ifndef RANDOMPLAYOUT_H
#define RANDOMPLAYOUT_H
#include "board.h"
#include <random>

/**
 * Performs a random playout to a final state 
 * and then retrieves {-1.0,1} based on the state of the fianal board
 * */
class RandomPlayout
{
public:
	RandomPlayout();
	~RandomPlayout(){};
	double eval(board b);

private:
	double state_value(board& b);
	zet select_random_move(board& b);
	mt19937_64 rng;
};


#endif /* end of include guard: RANDOMPLAYOUT_H */
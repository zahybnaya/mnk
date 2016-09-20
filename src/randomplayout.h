#ifndef RANDOMPLAYOUT_H
#define RANDOMPLAYOUT_H
#include "playoutpolicy.h"
#include <random>

/**
 * Performs a random playout to a final state 
 * and then retrieves {-1.0,1} based on the state of the fianal board
 * */
class RandomPlayout : public PlayoutPolicy
{
public:
	RandomPlayout();
	~RandomPlayout(){};
	virtual double eval(board b);
	virtual zet select_random_move(board& b);
protected:
	double state_value(board& b);
	std::mt19937_64 rng;
};


#endif /* end of include guard: RANDOMPLAYOUT_H */

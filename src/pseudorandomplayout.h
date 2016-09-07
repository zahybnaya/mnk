#ifndef PSEUDORANDOMPLAYOUT_H
#define PSEUDORANDOMPLAYOUT_H
#include "randomplayout.h"
#include "board.h"
#include <random>
#include <map>

/**
 * Performs a pseudo-random playout to a final state 
 * and then retrieves {-1.0,1} based on the state of the fianal board
 * */

typedef struct { int row; int col;} COORD; 

class PseudoRandomPlayout : public RandomPlayout
{
public:
	~PseudoRandomPlayout(){};
	PseudoRandomPlayout();
	zet select_random_move(board& b);
	int proximity(board &b, uint64 m);
private:
	Motif winNextMove;
	std::map<uint64,int> distancesFromCenter;
	std::map<uint64,COORD> getCoord;
	double probPerMove(board& b,uint64 m);
	int distanceFromCenter(uint64 m);
	int proximity(uint64, uint64 );
};

#endif /* end of include guard */

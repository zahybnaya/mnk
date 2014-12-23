#include "heuristic.h"
#include "randomplayout.h"
#include <random>
#include "log.h"

RandomPlayout::RandomPlayout(){
	rng = std::mt19937_64();
	rng.seed(time(NULL));
}

/***
 * Only public function to be called
 * */
double RandomPlayout::eval(board b){
	while(!b.is_ended()){
		zet z= select_random_move(b);
		b=b+z;
	}
	return state_value(b);
}


double RandomPlayout::state_value(board& b){
	if (b.black_has_won()){
		return 1.0;
	}
	if (b.white_has_won()){
		return -1.0;
	}
	return 0;
}

zet RandomPlayout::select_random_move(board& b){
	heuristic h;
	vector<zet> moves = h.enumerate_moves(b, b.active_player());
	return moves[rng() % moves.size()];
}


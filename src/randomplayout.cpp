#include "heuristic.h"
#include "randomplayout.h"
#include <random>
#include "board.h"
#include "log.h"
#include <cassert>

RandomPlayout::RandomPlayout(){
	rng = std::mt19937_64();
	rng.seed(time(NULL));
}

/***
 * The only public function to be called
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
		return 0.0;
	}
	assert(b.is_full());
	return 0.5;
}

zet RandomPlayout::select_random_move(board& b){
	vector<uint64> moves = enumerate_moves_uint64(b);
	return zet(moves[rng() % moves.size()],0,b.active_player());
}


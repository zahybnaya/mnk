#include "myopicpolicyplayout.h" 
#include "board.h"
#include "assert.h"


double MyopicPolicyPlayout::eval(board b){
	while(!b.is_ended()){
		zet z= select_next_move(b);
		b=b+z;
	}
	return state_value(b);

}


double MyopicPolicyPlayout::state_value(board& b){
	if (b.black_has_won()){
		return 1.0;
	}
	if (b.white_has_won()){
		return 0.0;
	}
	return 0.5;
}

zet MyopicPolicyPlayout::select_next_move(board& b){
	vector<zet> moves = h.get_moves(b, b.active_player(),false);
	if (moves.size() > 1){
		assert(moves[0].val >= moves[1].val);
	}
	return moves[0];
}


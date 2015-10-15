#include "myopicpolicyplayout.h" 
#include "board.h"
#include "assert.h"


MyopicPolicyPlayout::MyopicPolicyPlayout(heuristic &h, std::mt19937_64 &generator, double policy_lapse_rate ):h(h), generator(generator){ 
	lapse = new std::bernoulli_distribution(policy_lapse_rate);
};


MyopicPolicyPlayout::~MyopicPolicyPlayout(){
	delete lapse;
}


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
	int player = b.active_player();
	if ((*lapse)(generator)){
		std::vector<zet> s = enumerate_moves(b,player); 
		int rn_n = std::uniform_int_distribution<int>(0,s.size()-1)(generator);
		return s[rn_n];
	}
	vector<zet> moves = h.get_moves(b, player,false);
	if (moves.size() > 1){
		assert(moves[0].val >= moves[1].val);
	}
	return moves[0];
}


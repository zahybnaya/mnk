#include <cassert>
#include  "dummy_agent.h"
#include <random>
#include <exception>
#include "board.h"

DummyAgent::DummyAgent(){
			vector_index_1 = 0;
			vector_index_2 = 0;
			uint64 m1 = 1;
			uint64 m2 = 9;
			uint64 first_move = tilestringtouint64("29");
			uint64 second_move = tilestringtouint64("28");
			for (int i=0;i<2;i++) 
				move_sequence1.push_back(zet(m1,0,true));
			move_sequence1.push_back(zet(first_move,0,true));
			for (int i=0;i<6;i++) 
				move_sequence2.push_back(zet(m2,0,true));
			move_sequence2.push_back(zet(second_move,0,true));
}



//zet DummyAgent::play(board& b,bool player) {
//	if (!player) {
//		assert(vector_index_1<move_sequence1.size());
//		return move_sequence1[vector_index_1++];
//	}
//	assert(vector_index_2<move_sequence2.size());
//	zet z = move_sequence2[vector_index_2++];
//	return z;
//}


inline uint64 tiletouint64(int tile){
  uint64 m=1;
  return m<<=(4*BOARD_WIDTH-tile-1);
}


zet DummyAgent::play(board& b,bool player) {
	discrete_distribution<int> dist{0.00209,0.00065,0,0.21812,0.02814,0.00094,0,0.00063,0.00082,0.0011,0.02488,0.00084,0,0,0,
		0.00079,0.00126,0.00122,0.00063,0.00112,0.2109,0.23721,0,0,0.00175,0.00076,0.00067,0.00115,0.12836,0.01915,0,0.07949,
		0.03082,0.00356,0.00237,0.00058};
  if(player==BLACK && b.pieces[BLACK]==binstringtouint64("000000000000101000000010000000100000")
     && b.pieces[WHITE]==binstringtouint64("001000100000010000000001000000000000"))
	  return zet(tiletouint64(dist(get_generator())),0.0,player);
  throw runtime_error("wrong board");
}


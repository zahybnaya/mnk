#include "randomagent.h"


zet RandomAgent::play(board& b,bool /*player*/) {
	vector<uint64> moves = enumerate_moves_uint64(b);
	return zet(moves[std::uniform_int_distribution<int>(0,moves.size()-1)(get_generator())], 0, b.active_player());
}

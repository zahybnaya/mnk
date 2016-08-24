
#include "pseudorandomagent.h"

zet PseudoRandomAgent::play(board& b,bool /*player*/) {
	return p.select_random_move(b);
}

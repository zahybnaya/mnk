#ifndef PLAYOUTPOLICY_H
#define PLAYOUTPOLICY_H
#include "board.h"

class PlayoutPolicy {
	public:
		PlayoutPolicy(){};
		virtual ~PlayoutPolicy(){};
		virtual double eval(board b) = 0;

};

#endif /* end of include guard: PLAYOUTPOLICY_H */

#ifndef MYOPICPOLICYPLAYOUT_H
#define MYOPICPOLICYPLAYOUT_H
#include "playoutpolicy.h"
#include "heuristic.h"

/***
 *
 * Follows the myopic policy to make the next move. 
 * keeps going until the end and checks who won
 *
 * */

class MyopicPolicyPlayout : public PlayoutPolicy {
	public:
		virtual double eval(board b);
		MyopicPolicyPlayout(heuristic &h):h(h){};
	private:
		double state_value(board& b);
		zet select_next_move(board& b);
		heuristic &h;
};



#endif /* end of include guard: MYOPICPOLICYPLAYOUT_H */

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
		MyopicPolicyPlayout(heuristic &h, std::mt19937_64 &generator, double policy_lapse_rate );
		~MyopicPolicyPlayout();
		virtual double eval(board b);
	private:
		double state_value(board& b);
		zet select_next_move(board& b);
		heuristic &h;
		std::mt19937_64 &generator;
		std::bernoulli_distribution *lapse; 
};



#endif /* end of include guard: MYOPICPOLICYPLAYOUT_H */

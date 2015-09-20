#ifndef HEURISTICSAGENT_H
#define HEURISTICSAGENT_H
#include "agent.h"
#include <random>
#include "heuristic.h"

class HeuristicsAgent: public Agent{
public:
	HeuristicsAgent(){};
	~HeuristicsAgent(){};
	void init();
	void post_solution();
	void pre_solution();
	double get_triangle_weight();
	double get_weight(int i);
	double get_delta();
	double get_vert_scale();
	double get_diag_scale();
	double get_opp_scale();
	heuristic h;
private:
	std::bernoulli_distribution lapse;
	bool is_negamax(){return true;};
};


#endif /* end of include guard: HEURISTICSAGENT_H */

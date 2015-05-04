#ifndef MYOPICAGENT_H
#define MYOPICAGENT_H
#include "agent.h"
#include <random>
#include "heuristic.h"

//TODO: extract the heuristics initiallization
class MyopicAgent: public Agent{
public:
	MyopicAgent(){};
	~MyopicAgent(){};
	void init();
	std::string get_name()const {return "Myopic";}
	std::vector<zet> solve(board& b,bool player);
	double get_triangle_weight();
	double get_weight(int i);
	double get_D0();
	double get_K0();
	double get_gamma(); 
	double get_delta();
	double get_vert_scale();
	double get_diag_scale();
	double get_opp_scale();
	heuristic h;
private:
	std::bernoulli_distribution lapse;
	bool is_negamax(){return false;};
};


#endif /* end of include guard: MYOPICAGENT_H */

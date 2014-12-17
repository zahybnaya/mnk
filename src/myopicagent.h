#ifndef MYOPICAGENT_H
#define MYOPICAGENT_H
#include "agent.h"

class MyopicAgent: public Agent{
public:
	MyopicAgent(){};
	~MyopicAgent(){};
	const std::string get_name(){return "Myopic";}
	std::vector<zet> solve(board& b,bool player);
private:
	/* data */
};


#endif /* end of include guard: MYOPICAGENT_H */

#ifndef UCTAGENTVISITS_H
#define UCTAGENTVISITS_H
#include "uctagent.h"

class UCTAgentVisits: public UCTAgent{
	public :
		virtual std::string get_name() const {
			return std::string("UCT_VISITS");
		
		}
		std::vector<zet> solve(board& b,bool player);
};
#endif

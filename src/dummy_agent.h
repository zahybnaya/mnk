#include "agent.h"
#include <vector>

class DummyAgent: public Agent{
	public:
		DummyAgent();
		~DummyAgent(){};
		zet play(board& b,bool player); 
		std::vector<zet> solve(board& b,bool player){
			return move_sequence1;
		}

		std::string get_name() const  {
			return std::string("DUMMY");
		}
		bool is_negamax(){
			return false;
		}

	private:
		std::vector<zet> move_sequence1;  
		std::vector<zet> move_sequence2;  
		int vector_index_1;
		int vector_index_2;

};


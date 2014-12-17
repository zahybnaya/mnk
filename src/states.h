#ifndef STATES_ITERATOR_H
#define STATES_ITERATOR_H
#include <vector>
#include "board.h"

typedef std::vector<board>::iterator state_it; 
class States{
	public:
		States(){};
		~States(){};
		void read(const char* filename);
		state_it begin(); 
		state_it end(); 
	private:
		std::vector<board> m_states; //TODO make an iterator
};
//TODO: vector of board* is better 
#endif /* end of include guard: STATES_ITERATOR_H */


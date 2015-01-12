#include "bfsagent.h"

/**
 * Evaluaties a new node
 **/
double BFSAgent::evaulate(Node* lastNode, Node* parent, uint64 move_id){

	h.remove_features();
	std::vector<zet> moves = h.get_moves(parent->m_board/*parent*/,parent->player /*parent*/,false); 
	for ( std::vector<zet>::const_iterator i = moves.begin(); i != moves.end(); ++i) {
		if (i->zet_id == move_id){
			h.restore_features();
			return i->val;
		}
	}
	
	return -1;
}




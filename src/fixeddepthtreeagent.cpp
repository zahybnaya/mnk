#include "fixeddepthtreeagent.h"
#include <assert.h>
#include "dotexporter.h"

inline double value_for_new_node1(Node* parent, zet z){
	double r = (parent->val/parent->visits)+(((parent->player==BLACK)?1:-1)*z.val);
	//std::cout<<"Value for new node: parent value:"<<parent->val/parent->visits<<" z.val:"<<z.val<<" z.id:"<<z.zet_id<<" total:"<<r<<std::endl;
	return r;
}

inline bool better_for_black(pair<uint64,Node*> n1p, pair<uint64,Node*> n2p) {
	Node* n1 = n1p.second;
	Node* n2 = n2p.second;
	assert(n1->player==n2->player);
	double n1_val = n1->val/n1->visits;
	double n2_val = n2->val/n2->visits;
	// parent is the opposite color
	return  (n1->player == BLACK) ? (n1_val > n2_val):(n1_val < n2_val);
} 


/**
 * Creates a new node to represent node and adds it as a child to parent
 */
Node* connect(uint64 move, Node* parent,double value,int visits){
	assert(parent);
	zet z = zet(move,value,parent->player); 
	Node* new_node = new Node(parent->m_board+z,!parent->player,value,visits);
	if (new_node->m_board.is_ended()){
		new_node->solved=true;
		if (new_node->m_board.player_has_won(new_node->player)){
			new_node->forced_win=true;
		}
		if (new_node->m_board.player_has_won(!new_node->player)){
			assert(!new_node->forced_win);
			new_node->forced_loss=true;
		}
	} 
 	parent->children[move]=new_node; 
	return new_node;
}




/**
 *  Estimates all known estimates from node n
 * */
std::vector<zet> get_move_estimates(Node* n){
	std::vector<zet> ret;
	for (child_map::const_iterator i = n->children.begin(); i != n->children.end(); ++i) {
		uint64 move_id=i->first;
		if(i->second->visits==0) {
			continue;
		}
		double move_value = (i->second->val)/(i->second->visits);
		bool player = n->player;
		zet z(move_id,move_value,player);
		ret.push_back(z);
	}
	return ret;
}



std::vector<zet> FixedDepthTreeAgent::solve(board& b, bool /*player*/){
	Node* n = new Node(b,b.active_player()); 
	n->val=h.evaluate(n->m_board);
	n->visits=1;
	expand_rec(n,0);
	//todot(n,std::cout);
	return get_move_estimates(n);
}


void FixedDepthTreeAgent::expand_rec(Node* n, int depth){
	if (depth==get_depth() || n->m_board.is_ended())
		return; 
	std::vector<zet> zets;
	h.get_moves(n->m_board,n->player,false,zets);
	for (unsigned int i=0;i<zets.size();++i){
		zet z = zets[i]; 
		expand_rec(connect(z.zet_id,n,value_for_new_node1(n,z),1), depth+1);
	}
	Node* argmax = std::max_element(n->children.begin(),n->children.end(),better_for_black)->second;
	n->val=argmax->val;
	//std::cout<<"n->val ="<<n->val<<std::endl;
}


int FixedDepthTreeAgent::get_depth(){
	return get_int_property("depth");
}


int FixedDepthTreeAgent::get_branching_factor(){
	return get_int_property("branching_factor");
}


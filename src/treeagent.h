#ifndef TREEAGENT_H
#define TREEAGENT_H

#include "agent.h"
typedef struct Node Node;
typedef std::map<uint64,Node*> child_map;

/**
 *  Tree node 
 * */
struct Node {
	Node(board m_board,bool player):m_board(m_board),val(0.0),
		visits(0),player(player),new_node(true){}
	board m_board;
	child_map children; 
	double val;
	int visits;
	bool player;
	bool new_node; //TODO:See if this can be avoided
};

/**
 * Write a node to stream
 */
inline
std::ostream& operator<<(std::ostream& o, Node& n)
{
	o<<"B["<<n.m_board.pieces[BLACK]<<"]W["<<n.m_board.pieces[WHITE]<<"]"<<std::endl;
	return o;
}
/**
 * Part of tree print 
 */
inline void print_node(Node* n, int level){
	std::cout<<std::string(level, ' ')<<"|-"<<*n<<std::endl;
	for (child_map::const_iterator i = n->children.begin(); i != n->children.end(); ++i) {
		Node* c = i->second; 
		print_node(c,level+1);	
	}
}
/**
 * Part of tree print 
 */
inline void print_tree(Node* root){
	print_node(root,0);

}

/**
 *  An agent that builds a tree to 
 *  solve a board
 * */
class TreeAgent: public Agent {

public:
	TreeAgent(){};
	~TreeAgent(){};

	/**
	 * Iterations for the tree
	 * */
	const int get_iterations();


	std::vector<zet> solve(board& b,bool player);
protected:

	/**
	 *  Distribution for the number of iterations 
	 * */
	const DISTRIBUTION get_iteration_distribution();

	/**
	 *  Parameter for the distribution 
	 *  for the number of iterations TODO: Parse as language? e.g. iteration_distribution=G(0.4)/B(0.3)/Beta(0.3,0.4)
	 * */
	const double get_iteration_distribution_param();


	/**
	 * Addition to the uct exploitation measurement
	 * */
	const double get_exploitation_noise_distribution();
	const double get_exploitation_noise_param();

	/**
	 *
	 * */
	const double get_iter_gamma();
	/**
	 * returns the moves which are not 
	 * expanded for a specific node (no node exists)
	 * */
	virtual std::vector<zet> unexpanded_moves(Node* n);
	/**
	 *  Generates a new node by applying move 
	 *  and connecting it to parent
	 * */
	virtual Node* expand(uint64 move,Node* parent);

	/**
	 * Returns a random move from the list of moves  
	 * which does not have a node yet
	 * */
	virtual uint64 select_random_unknown_move(Node* n);

	/**
	 * Create an initial node from board
	 * */
	virtual Node* create_initial_state(board b);

	/**
	 * Assuming a built tree, return the move estimates 
	 * */
	virtual std::vector<zet> move_estimates(Node* n);

	/**
	 * free allocated memory
	 * */
	virtual void delete_tree(Node* root);

	/**
	 * Constructs a tree starting from the root
	 * */
	virtual int build_tree(Node* n,int iterations);

	/**
	 *  Perform a single iteration starting from n
	 * */
	virtual void iterate(Node* n);

	/**
	 * Given an addition node lastNode, return an evaluation
	 **/
	virtual double evaulate(Node* lastNode, Node* parent, uint64 move_id)=0;

	/**
	 * Propagate the new_val through out the nodes variation
	 *
	 **/
	virtual void back_propagatate(double new_val, std::vector<Node*> nodes);


private:
	/**
	 * Select a path starting from the root of the tree that 
	 * ends with a new node
	 * */
	virtual std::vector<Node*> select_variation(Node* root);
	/***
	 * Next node to be selected when on node n in the tree
	 * */
	virtual Node* select_next_node(Node* n) = 0;
};



#endif /* end of include guard: TREEAGENT_H */

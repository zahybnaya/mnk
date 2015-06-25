#ifndef TREEAGENT_H
#define TREEAGENT_H

#include "agent.h"
typedef struct Node Node;
typedef std::map<uint64,Node*> child_map;

double average_diff(std::vector<zet> &zets, int player);
double calc_best_diff(std::vector<zet> &zets, int player);
/**
 *  Tree node 
 * */
struct Node {
	Node(board m_board,bool player,double val=0.0, int visits=0):m_board(m_board),val(val),
		visits(visits),player(player),solved(false), forced_win(false), forced_loss(false){}
	board m_board;
	child_map children; 
	double val;
	int visits;
	bool player;
	bool solved; 
	bool forced_win; 
	bool forced_loss; 
};

/**
 * Write a node to stream
 */
inline
std::ostream& operator<<(std::ostream& o, Node& n)
{
	o<<"SOLVED:"<<n.solved<<" B{"<<n.m_board.pieces[BLACK]<<"}W{"<<n.m_board.pieces[WHITE]<<"}"<<std::endl;
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
 * 
 * */
std::vector<pair<uint64,Node*>> get_shuffled_vector(child_map c);

/**
 *  An agent that builds a tree to 
 *  solve a board
 * */
class TreeAgent: public Agent {

public:
	TreeAgent():last_move_searched(-1){};
	~TreeAgent(){};

	/**
	 * Iterations for the tree
	 * */
	int get_iterations();
	virtual void pre_solution();
	virtual void post_solution(){}

	/**
	 *  returns a vector of estimated moves 
	 * */
	std::vector<zet> solve(board& b,bool player);
protected:
	/**
	 * The gamma parameter for the iteration dist
	 * */
	double get_iter_gamma();
	/**
	 * returns the moves which are not 
	 * expanded for a specific node (no node exists)
	 * */
	virtual std::vector<zet> unexpanded_moves(Node* n);
	/**
	 *  Generates a new node by applying move 
	 *  and connecting it to parent. value and visits are also optional params
	 * */
	virtual Node* connect(uint64 move,Node* parent,double value,int visits);
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
	//virtual double evaulate(Node* lastNode, Node* parent, uint64 move_id);

	/**
	 * Expand a node in the tree
	 * */
	virtual double expand(Node* parent) = 0;


	/**
	 * Propagate the new_val through out the nodes variation
	 **/
	virtual void back_propagatate(double new_val, std::vector<Node*> nodes);
	/**
	 *  marks solved nodes
	 * */
	virtual void mark_solved(Node* n);
	/**
	 *  marks that the playing agent has won from this node
	 * */
	virtual void mark_forced_win_loss(Node* n);

private:
	void print_time_prediction_metrics(board& b, Node* n, std::vector<zet> &zets);
	/**
	 * Select a path starting from the root of the tree that 
	 * ends with a new node
	 * */
	virtual std::vector<Node*> select_variation(Node* root);
	/***
	 * Next node to be selected when on node n in the tree
	 * */
	virtual Node* select_next_node(Node* n) = 0;
	/**
	 * 
	 * */
	void mark_solved_if_all_children_solved(Node* n);
	/**
	 * last branch of the tree that was searched 
	 * */
	uint64 last_move_searched;

	/**
	 *  Counter of the number of switches 
	 * */
	int num_switches;
	int consecutive; 
	int max_consecutive;

	void count_switches(const std::vector<Node*> &nodes);
	uint64 get_first_move_id(const std::vector<Node*> &nodes);
};



#endif /* end of include guard: TREEAGENT_H */

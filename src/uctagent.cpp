#include "uctagent.h"
#include <math.h>
#include <assert.h>
#include <algorithm>
#include "randomplayout.h"
#include "geometricrandom.h"
#include "myopicpolicyplayout.h"

/**
 * Constructor 
 * */
UCTAgent::UCTAgent(){
	policy = NULL;
}

/**
 * Destructor 
 * */
UCTAgent::~UCTAgent(){
	delete(policy);
	policy = NULL;
}


/**
 * Naming of agent
 * */
std::string UCTAgent::get_name() const{
	return std::string("UCT");
}

/**
 * are values stored in a negamax tree
 * */
bool UCTAgent::is_negamax(){
	return false;
}

int UCTAgent::get_policy_code(){
	return get_int_property("policy_code");
}

void UCTAgent::init(){
	Agent::init();
	branching_factor=std::bernoulli_distribution(fmod(get_K0(),1.0));
	h.gamma  = get_gamma();
	h.delta   = get_delta();
	h.vert_scale  = get_vert_scale();
	h.diag_scale  = get_diag_scale();
	h.opp_scale   = get_opp_scale();
	for(int i=0;i<6;i++)
		h.weight[i]=get_weight(i);
	/***
	 * Simplified model
	 * */
	h.weight[4]=h.weight[3];
	h.weight[16]=get_triangle_weight();
	h.update();

	if (policy == NULL)
		switch(get_policy_code()){
			case 0:
				policy = new RandomPlayout();
				break;
			case 1:
				policy = new GeometricRandomPlayout(h);
				break;
			case 2:
				policy = new MyopicPolicyPlayout(h,get_generator(),get_policy_lapse_rate());
				break;
			default:
				throw std::runtime_error("no policy");
		}
	FILE_LOG(logDEBUG) << "Init an agent with the following properties- " <<" K0:"<< get_K0() <<" h.gamma:"<< get_gamma() << " h.delta:" <<  get_delta() << " h.vert_scale:"<<   get_vert_scale() << " h.diag_scale:"<< get_diag_scale() <<" h.opp_scale: " << get_opp_scale() << " h.weight[0]:"<<get_weight(0) << " lapse_rate" << get_lapse_rate() << std::endl;

}


/**
 * UCT uses a given policy to evaluate new states.
 * */
double UCTAgent::evaulate(Node* lastNode,Node* /* parent*/, uint64 ){
	int num_of_evals =  get_num_of_evals();
	double r =0;
	for (int i = 0; i < num_of_evals; i++) {
		r += policy->eval(lastNode->m_board);
	}
	double rval = r/num_of_evals;
	FILE_LOG(logDEBUG)<<"evaluating last node as "<<rval<<" with "<<num_of_evals<<" evaluations"<<std::endl; 
	return rval;
}

/**
 * The uct calculation 
 * */
double UCTAgent::uct(Node* n, int ttl_visits) { 
	double exploration =  sqrt(log(ttl_visits)/n->visits);
	double exploitation = n->val/n->visits;
	bool player_turn = !n->player;
	if ( is_negamax())
		exploitation=(player_turn==BLACK )?exploitation:-exploitation;
	double r = get_exploration_constant()*exploration + exploitation; 
	FILE_LOG(logDEBUG)<<"UCT of Node"<<n<<" "<<r<<std::endl; 
	return r;
		
}

struct uct_comparator_t {
	uct_comparator_t(UCTAgent* a,int ttl): ttl_visits(ttl), a(a){};
	int operator()(std::pair<uint64,Node*> i, std::pair<uint64,Node*> j) {
	       	return a->uct(i.second,ttl_visits)<a->uct(j.second,ttl_visits);
       	}
	int ttl_visits;
	UCTAgent* a;
}; 

/**
 * Returns either a new child node 
 * or an existing child node 
 */
Node* UCTAgent::select_next_node(Node* n){
	assert(!n->solved);
	assert(!n->m_board.is_ended());
	if (n->children.empty()){
		return NULL;
	}
	std::vector<pair<uint64,Node*>> v= get_shuffled_vector(n->children);
	assert(v.size()>0);
	std::pair<uint64,Node*> argmax =
	       	*std::max_element(v.begin(),v.end(),uct_comparator_t(this,n->visits));
	return argmax.second;
}

/**
 * A solved node is one that has all children expanded
 * */
void UCTAgent::mark_solved(Node* n){
	TreeAgent::mark_solved(n);
}


double value_for_new_node_uct(Node* parent, zet z){
	return (parent->val/parent->visits)+(((parent->player==BLACK)?1:-1)*z.val);
}


/**
 * UCT expand
 * */
double UCTAgent::expand(Node* n){
	if (n->visits==0/*root*/) {
                n->val=h.evaluate(n->m_board);
                n->visits=1;
        }
	unsigned int k = int(get_K0()) + branching_factor(get_generator());
	double ret;
	std::vector<zet> zets;
	h.self=get_playing_color();
	h.get_moves(n->m_board,n->player,false,zets);
	unsigned int actual_branching_factor = k<zets.size()?k:zets.size();
	Node* new_node = NULL;
	for (unsigned int i=0;i<actual_branching_factor;++i){
		zet z = zets[i]; 
		uint64 move = z.zet_id;
		new_node = TreeAgent::connect(move,n,0,0);
		double eval = evaulate(new_node, n, move);
		new_node->val=eval;
		new_node->visits=1;
		double zval = value_for_new_node_uct(n,z);
		double normalized_h_value = (1/(1+exp(-zval)));
		assert(normalized_h_value>=0 && normalized_h_value<=1);
		new_node->val+=get_virtual_rollouts()* normalized_h_value;
		new_node->visits+=get_virtual_rollouts();
		if(i==0){
			ret = eval;
		}
	}
	return ret;
}

/**
 * Removes features from h for entire tree 
 * 
 * */
void UCTAgent::pre_solution(){
	TreeAgent::pre_solution();
	h.self=get_playing_color();
	h.remove_features();
}

/**
 * restore features after each solution
 * */
void UCTAgent::post_solution(){
	h.restore_features();
}


/**
 * Number of evaluations of the policy
 * */
int UCTAgent::get_num_of_evals(){
	return get_int_property("num_of_evals");
}

/**
 *  UCT constant 
 * */
double UCTAgent::get_exploration_constant() {
	return get_double_property("exploration_constant");
}

double UCTAgent::get_K0() {
	return get_double_property("K0");
}
double UCTAgent::get_gamma() {
	return get_double_property("gamma");
}
double UCTAgent::get_delta() {
	return get_double_property("delta");
}
double UCTAgent::get_vert_scale() {
	return get_double_property("vert_scale");
}
double UCTAgent::get_diag_scale() {
	return get_double_property("diag_scale");
}
double UCTAgent::get_opp_scale() {
	return get_double_property("opp_scale");
}

double UCTAgent::get_triangle_weight(){
	return get_double_property("triangle_weight");
}

int UCTAgent::get_virtual_rollouts(){
	return get_int_property("virtual_rollouts");
}
double UCTAgent::get_policy_lapse_rate() {
	return get_double_property("policy_lapse_rate");
}
double UCTAgent::get_weight(int i){
	std::string t="weights_"+std::to_string(i);
	return get_double_property(t);
}




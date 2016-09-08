#include "uctagent.h"
#include <math.h>
#include <assert.h>
#include <algorithm>
#include "randomplayout.h"
#include "geometricrandom.h"
#include "myopicpolicyplayout.h"
#include "pseudorandomplayout.h"

//#define UCTDEBUG
/**
 * Constructor 
 * */
UCTAgent::UCTAgent():policy(NULL){
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
/**
 * Assumes ordered zets. Ignore that on the root node.
 * */
unsigned int UCTAgent::get_actual_branching_factor(std::vector<zet>& zets,bool is_root){
  double prune_threshold = get_prune_threshold();
  double best_value = zets.front().val; 
#ifdef UCTDEBUG
  std::cout<<"Expansion: best value:" << best_value << std::endl;
#endif
  size_t i=1;
  double oldval=0;
  while (i < zets.size() && (std::abs(best_value - zets.at(i).val) < prune_threshold)){
      assert(i==1 || oldval > zets.at(i).val);
      oldval = zets.at(i).val;
      i++;
  }
#ifdef UCTDEBUG
  std::cout<<"Expansion: Adding "<< i<<" children with value " << zets.at(i-1).val << std::endl;
#endif
  return i;
}


void UCTAgent::init(){
	FILE_LOG(logDEBUG) << " Init UCTAgent. Init Treeagent first "<<std::endl;
	TreeAgent::init();
	if (policy == NULL){
		FILE_LOG(logDEBUG) << " Getting policy code "<<std::endl;
		int policy_code =get_policy_code(); 
		FILE_LOG(logDEBUG) << " Selecting policy "<<policy_code<<std::endl;
		switch(policy_code){
			case 0:
				policy = new RandomPlayout();
				FILE_LOG(logDEBUG) << " Assigned Random policy for uct "<<std::endl;
				break;
			case 1:
				policy = new GeometricRandomPlayout(h);
				FILE_LOG(logDEBUG) << " Assigned GeoRandom policy for uct "<<std::endl;
				break;
			case 2:
				policy = new MyopicPolicyPlayout(h,get_generator(),get_policy_lapse_rate());
				FILE_LOG(logDEBUG) << " Assigned Myopic policy for uct "<<std::endl;
				break;
			case 3:
				policy = new PseudoRandomPlayout();
				FILE_LOG(logDEBUG) << " Assigned PseudoRandomPlayout policy for uct "<<std::endl;
				break;
			default:
				throw std::runtime_error("no policy");
		}
	}
}


/**
 * UCT uses a given policy to evaluate new states.
 * */
double UCTAgent::evaulate(Node* lastNode,Node* /* parent*/, uint64 ){
	int num_of_evals = std::max(get_num_of_evals(),1);
	double r =0;
	for (int i = 0; i < num_of_evals; i++) {
		r += policy->eval(lastNode->m_board);
	}
	double rval = r/num_of_evals;
	return rval;
}

/**
 * The uct calculation 
 * */
double UCTAgent::uct(Node* n, int ttl_visits) { 
	double exploration =  sqrt(log(ttl_visits)/n->visits);
	double exploitation = n->val/n->visits;
	bool player_turn = !n->player;
	exploitation=(player_turn==BLACK)?exploitation:-exploitation;
	double r = get_exploration_constant()*exploration + exploitation; 
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

void dbg_uct_vals(std::vector<pair<uint64,Node*>> v,UCTAgent* a,int ttl_visits){
	for (auto i:v){
		Node* n =i.second; 
		double exploration =  sqrt(log(ttl_visits)/n->visits);
		double exploitation = n->val/n->visits;
		std::cout<<"SELCTION:Node:"<<n<<" Visits:"<<n->visits <<" TTL_VISITS:"<<ttl_visits<<" Exploration:"<<exploration<<" Exploitation"<<exploitation<<" UCT:"<<a->uct(n,ttl_visits)<<" "<<std::endl;
	}
}

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
#ifdef UCTDEBUG
	dbg_uct_vals(v,this,n->visits);
	std::cout<<"SELECTION: ***Returning selection as:"<<argmax.second<<std::endl;
#endif
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
	bool is_root=false;
	if (n->visits==0/*root*/) {
		is_root=true;
                n->val=h.evaluate(n->m_board);
                n->visits=1;
        }
	double ret;
	std::vector<zet> zets;
	h.self=get_playing_color();
	h.get_moves(n->m_board,n->player,false,zets);
	unsigned int actual_branching_factor = get_actual_branching_factor(zets,is_root); 
	Node* new_node = NULL;
	for (unsigned int i=0;i<actual_branching_factor;++i){
		zet z = zets[i]; 
		uint64 move = z.zet_id;
		new_node = TreeAgent::connect(move,n,0,0);
		double eval = evaulate(new_node, n, move);
		new_node->val=eval;
		new_node->visits=1;
		int vir_rollouts = get_virtual_rollouts();
		if (vir_rollouts >0){
			double zval = value_for_new_node_uct(n,z);
			double normalized_h_value = (1/(1+exp(-zval)));
			assert(normalized_h_value>=0 && normalized_h_value<=1);
			new_node->val+=vir_rollouts* normalized_h_value;
			new_node->visits+=vir_rollouts;
		}
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

double UCTAgent::get_gamma() {
	return get_double_property("gamma");
}
int UCTAgent::get_virtual_rollouts(){
	return get_int_property("virtual_rollouts");
}
double UCTAgent::get_policy_lapse_rate() {
	return get_double_property("policy_lapse_rate");
}
double UCTAgent::get_prune_threshold(){
	return get_double_property("prune_threshold");
}



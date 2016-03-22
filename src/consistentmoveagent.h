
#include "defaultagent.h"

	

/****
 * 
 * This agent changes (1) the stop criteria to stop when there are multiple consistent moves *
 * */ 
class ConsistentMoveAgent: public DefaultAgent {

	public:
		ConsistentMoveAgent(){};
		virtual ~ConsistentMoveAgent(){};
		virtual void pre_solution();
	protected:
		/** 
		 * When exceeding the number of
		 * iterations or threshould
		 * **/
		virtual bool is_stop(Node* n);
		std::string get_name() const {return "CONST_MOVE";}
	private:
		uint64 current_zet_id;
		int persistent_moves;
		inline int get_consistent_times(){
		return get_int_property("consistent_times");}

};
	

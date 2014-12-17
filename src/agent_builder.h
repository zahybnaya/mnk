
/**
 * Get a bunch of parameters and create an agent
 */
#include "common.h"
#include "agent.h"

typedef std::map<std::string, Agent*(*)()> agent_map;

std::pair<std::string,std::string> split_pair(const std::string &s, char delim); 
Agent_params read_agent_params(std::string agent_description_filename);

class Agent_builder {
	public:
		Agent_builder();
		Agent* build(Agent_params p);
	private:
		void register_constructors();
		Agent* create_instance(std::string);
		agent_map agent_constructors;
}; 



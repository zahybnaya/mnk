#include "agent_builder.h"
#include <cassert>
#include "uctagent.h"
#include "myopicagent.h"
#include "fixeddepthtreeagent.h"
#include "bfsagent.h"
#include "dummy_agent.h"
#include "defaultagent.h"
#include "mindifftreeagent.h"

template<typename T> Agent* create_agent() {  return new T; }

Agent_builder::~Agent_builder(){
	
}
Agent_builder::Agent_builder(){
	register_constructors();
}

Agent* Agent_builder::build(Agent_params p){
	Agent* agent= create_instance(p.implementation);
	assert(agent);
	agent->set_properties(p.m_properties);
	agent->set_agent_file(p.agent_file);
	agent->init();
	return agent;
}

/**
 * This is a temporary function that registers any new implementation by codename
 * */
void Agent_builder::register_constructors(){
	agent_constructors["UCT"] = &create_agent<UCTAgent>;
	agent_constructors["MYOPIC"] = &create_agent<MyopicAgent>;
	agent_constructors["BFS"] = &create_agent<BFSAgent>;
	agent_constructors["MIN_DIFF_BFS"] = &create_agent<MinDiffTreeAgent>;
	agent_constructors["DUMMY"] = &create_agent<DummyAgent>;
	agent_constructors["FIXED"] = &create_agent<FixedDepthTreeAgent>;
	agent_constructors["DEFAULT"] = &create_agent<DefaultAgent>;
}

Agent* Agent_builder::create_instance(std::string type){
	if (agent_constructors.find(type)==agent_constructors.end()){
		FILE_LOG(logERROR)<< " Cannot create agent of type "<<type<< std::endl;
		exit(-1);
	}
	Agent *a=agent_constructors[type]();
	return a;
}




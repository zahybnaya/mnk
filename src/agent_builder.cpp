#include "agent_builder.h"
#include <cassert>
#include "uctagent.h"
#include "myopicagent.h"
#include "bfsagent.h"

template<typename T> Agent* create_agent() {  return new T; }


Agent_builder::Agent_builder(){
	register_constructors();
}

Agent* Agent_builder::build(Agent_params p){
	Agent* agent= create_instance(p.implementation);
	assert(agent);
	agent->set_properties(p.m_properties);
	agent->set_agent_file(p.agent_file);
	return agent;
}

void Agent_builder::register_constructors(){
	agent_constructors["UCT"] = &create_agent<UCTAgent>;
	agent_constructors["MYOPIC"] = &create_agent<MyopicAgent>;
	agent_constructors["BFS"] = &create_agent<BFSAgent>;
}

Agent* Agent_builder::create_instance(std::string type){
	if (agent_constructors.find(type)==agent_constructors.end()){
		FILE_LOG(logERROR)<< " Cannot create agent of type "<<type<< std::endl;
		exit(-1);
	}
	Agent *a=agent_constructors[type]();
	return a;
}



std::pair<std::string,std::string> split_pair(const std::string &s, char delim) {
	std::pair<std::string,std::string> p;
	std::stringstream ss(s);
	std::string item;
	std::getline(ss, item, delim);
	p.first=item;
	std::getline(ss, item, delim);
	p.second=item;
	return p;
}

Agent_params read_agent_params(std::string agent_description_filename) {
	FILE_LOG(logDEBUG)<< "Reading agent params from " << agent_description_filename<< std::endl;
	std::ifstream agent_description_file;
	agent_description_file.open(agent_description_filename);
	std::string line;
	Agent_params ag_par;
	while (std::getline(agent_description_file, line))
	{
		if (line.find_first_not_of(' ') == std::string::npos){
			continue;
		}
		if(line.compare(0, 1 , "#") == 0) {
			continue;
		}
		std::pair<std::string,std::string> p= split_pair(line,'=');
		FILE_LOG(logDEBUG) << p.first<<":"<<p.second << std::endl;
		ag_par.m_properties[p.first]=p.second;
	}
	ag_par.implementation = ag_par.m_properties["implementation"];
	ag_par.agent_file = agent_description_filename;
	return ag_par;
}






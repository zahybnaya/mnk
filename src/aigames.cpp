#include "common.h"
#include "agent.h"
#include "agent_builder.h"
#include "states.h"
#include <unistd.h>
#include <fstream>
#include <sstream>

States get_states(Source s) {
	FILE_LOG(logDEBUG)  << "getting states from source file" << std::endl;
	States states;
	states.read(s.state_file.c_str());
	return states;
}



void print_header(std::ostream& o)
{
	o<<"agent_name,agent_file,board,move,value"<<std::endl;
}

void print_agent(std::ostream& o,Agent* a, board b, std::vector<zet> zets){
	for (std::vector<zet>::const_iterator i = zets.begin(); i != zets.end(); ++i) {
		o<<a->get_name()<<","<<a->get_agent_file()<<",{"<<b.pieces[BLACK]<<"," <<b.pieces[WHITE]<<"},"
		       	<<i->zet_id<<","<<i->val<<std::endl;
	}
}


void execute_agent(Agent* a, States s)
{
	FILE_LOG(logDEBUG) << "executing agent "<<a->get_name()<<"..." << std::endl;
	int num_zets;
	for (state_it it = s.begin(); it!=s.end();it++){
		board b = *it;
		std::vector<zet> zets=a->solve(b,true);
		print_header(std::cout);
		print_agent(std::cout,a,b,zets);
	}  
}

int missing_values(){

	std::cout << " Usage: -s <state_file> -a <agent_description_file>"  << std::endl;


}

Source prepeare_source(int argc, const char* argv[]){
	std::string state_file, agent_file;
	bool state_check = false;
	bool agent_check = false;
	for (int i = 0; i < argc; i++) {
		 if (strcmp(argv[i],"-s")==0){
			 state_file = argv[++i];
			 state_check=true;
			 continue;
		 }
		 if (strcmp(argv[i],"-a")==0){
	 		 agent_file = argv[++i];
			 agent_check=true;
			 continue;
		 }
	}
	if (! (state_check && agent_check) ){
		missing_values();
		exit(-1);
	}
	FILE_LOG(logDEBUG) << "state_file:"<<state_file << " agent_file:"<<agent_file << std::endl;
	Source s(state_file, agent_file);
	return s;
}


int main(int argc, const char *argv[])
{
	FILELog::ReportingLevel() = FILELog::FromString("DEBUG");
	FILE_LOG(logDEBUG) << "Initializing aigames"<<std::endl; 
	Source s = prepeare_source(argc,argv);
	States states = get_states(s);
	Agent_params p = read_agent_params(s.agent_description_file); 
	Agent_builder b;
	Agent* agent = b.build(p);
	execute_agent(agent, states);	
	delete agent;

	return 0;
}

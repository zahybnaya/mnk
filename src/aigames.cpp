#include "common.h"
#include "agent.h"
#include "agent_builder.h"
#include "states.h"
#include "data_struct.h"
#include <unistd.h>
#include <fstream>
#include <sstream>
#include <cassert>


States get_states(Source s) {
	FILE_LOG(logDEBUG)  << "getting states from source file" << std::endl;
	States states;
	states.read(s.state_file.c_str());
	return states;
}



void print_header(std::ostream& o)
{
	o<<"index,subject,color,gi,mi,status,bp,wp,response,rt"<<std::endl;

}


void print_agent(bool color,std::ostream& o,Agent* a, board b, zet m, int player_num){
		o<<"0,"<<player_num<<","<<color<<","<<"0,0,playing,"<<uint64tobinstring(b.pieces[BLACK])<<"," <<uint64tobinstring(b.pieces[WHITE])<<","
		       	<<uint64totile(m.zet_id)<<","<<"0"<<std::endl;
}

/**
 * Executes the agen on a data_struct
 * */
void execute_agent_diffs(Agent* a, int player_num, data_struct &dat )
{
	std::vector<unsigned int> boards= dat.select_boards(player_num,ALL);
	FILE_LOG(logDEBUG) << " executing agent "<<a->get_name()<<"..." << std::endl;
	std::cout<<"board,player,zet,value,rt"<<std::endl;
	for (std::vector<unsigned int>::const_iterator it = boards.begin(); it!=boards.end();++it){
		board b = dat.allboards[*it];
		bool color = dat.allmoves[*it].player;
		double rt =  dat.thinking_times[*it];
		std::vector<zet> zets = a->solve(b,color);
		for (std::vector<zet>::const_iterator i = zets.begin(); i != zets.end(); ++i) {
			std::cout<<uint64tobinstring(b.pieces[BLACK])<<"," <<uint64tobinstring(b.pieces[WHITE])<<","<< color <<","<<i->zet_id<<","<<i->val<<std::endl;
		}
	} 
}



/**
 * Executes the agen on a data_struct
 * */
void execute_agent(Agent* a, int player_num, data_struct &dat )
{
	std::vector<unsigned int> boards= dat.select_boards(player_num,ALL);
	FILE_LOG(logDEBUG) << " executing agent "<<a->get_name()<<"..." << std::endl;
	print_header(std::cout);
	for (std::vector<unsigned int>::const_iterator it = boards.begin();  it!=boards.end();++it){
		board b = dat.allboards[*it];
		bool color = dat.allmoves[*it].player;
		zet m=a->play(b,color);
		assert(!b.contains(m.zet_id,m.player));
		assert(!b.contains(m.zet_id,color));
		print_agent(color,std::cout,a,b,m,player_num);
	} 
}


int missing_values(){

	std::cout << " Usage: -s <state_file> -a <agent_description_file>"  << std::endl;
	return -1;


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


/***
 *  This loads the data and for each player, agent performs an action
 * */

int main(int argc, const char *argv[])
{
	FILELog::ReportingLevel() = FILELog::FromString("ERROR");
	FILE_LOG(logDEBUG) << "Initializing aigames"<<std::endl; 
	Source s = prepeare_source(argc,argv);
	data_struct dat; 
        dat.load_file(s.state_file);
	Agent_params p = read_agent_params(s.agent_description_file); 
	Agent_builder b;
	Agent* agent = b.build(p);

	for (std::set<int>::iterator i = dat.distinct_players.begin(); i != dat.distinct_players.end();++i){
		execute_agent_diffs(agent, *i, dat);	
	}
	delete agent;
	return 0;
}

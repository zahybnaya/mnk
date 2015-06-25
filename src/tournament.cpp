#include "common.h"
#include <string.h>
#include <iostream>
#include "states.h"
#include "agent_builder.h"
#include "agent.h"
#include "board.h"
#include <cassert>

struct Match {
	std::string state_file;
	std::string black_agent_file;
	std::string white_agent_file;
	bool show_play;
};

void missing_values(){

	std::cout << "Usage: -s <state_file> -b <black_agent_file> -w <white_agent_file> [-show_play]  " << std::endl;

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
	Source s(state_file, agent_file);
	return s;
}


/**
 * Produce a match from args
 *
 * */
Match prepeare_match(int argc, const char* argv[]){
	std::string state_file, black_agent_file, white_agent_file;
	bool show_play=false;
	bool state_check = false;
	bool b_agent_check = false;
	bool w_agent_check = false;
	for (int i = 0; i < argc; i++) {
		 if (strcmp(argv[i],"-s")==0){
			 state_file = argv[++i];
			 state_check=true;
			 continue;
		 }
		 if (strcmp(argv[i],"-show_play")==0){
	 		 show_play=true;
			 continue;
		 }

		 if (strcmp(argv[i],"-b")==0){
	 		 black_agent_file = argv[++i];
			 b_agent_check=true;
			 continue;
		 }
		 if (strcmp(argv[i],"-w")==0){
	 		 white_agent_file = argv[++i];
			 w_agent_check=true;
			 continue;
		 }
	}
	if (! (state_check && b_agent_check && w_agent_check) ){
		missing_values();
		exit(-1);
	}
	FILE_LOG(logDEBUG) << "State file:"<<state_file << " black agent file:"<<black_agent_file << " white agent file"<< white_agent_file << std::endl;
	Match m;
	m.state_file=state_file;
	m.black_agent_file=black_agent_file;
	m.white_agent_file=white_agent_file;
	m.show_play=show_play;
	return m;
}

/**
 * Print a row in the tournamet
 * */
void print_row(std::ostream& out,board board , Agent* player, zet move){
		out << "{"<<board.pieces[BLACK]<<"," <<board.pieces[WHITE]<<"},"<<player->get_name()<<","<<player->get_agent_file()<<","<<move.zet_id << std::endl;
}


void execute_match(Agent* b_agent, Agent* w_agent, board& board, bool show_play=false){
	int i = board.active_player(), active_player;
	Agent* agents[2];
	assert(BLACK<2 && WHITE <2);
	agents[BLACK] = b_agent;
	agents[WHITE] = w_agent;
	Agent* player;
       	while(!board.is_ended()){
		active_player=(i++)%2;
		FILE_LOG(logDEBUG)<<board;
		if (show_play)
			std::cout << board << std::endl;
		player = agents[active_player];
		player->pre_solution();
		zet move = player->play(board,active_player);
		FILE_LOG(logDEBUG)<<"*Calculating value for the "<< active_player << "player. Move returned with "<< move.player<<std::endl;
		board = board+move;
		assert(board.pieces[active_player] & move.zet_id);
		print_row(std::cout, board,player,move);
		player->post_solution();
	}
	if (show_play)
		std::cout << board << std::endl;
	FILE_LOG(logDEBUG)<<board;
	assert(board.is_ended());
}


void execute_match(Agent* b_agent, Agent* w_agent, States states,bool show_play=false){
	FILE_LOG(logDEBUG) << "Match begins" << std::endl;
	for (state_it it = states.begin(); it!=states.end();it++){
		board b = *it;
		execute_match(b_agent,w_agent,b,show_play);
	} 

}

void print_header(std::ostream& o){
	o<<"board,player,player_file,move"<<std::endl;
}


int main(int argc, const char *argv[])
{
	FILELog::ReportingLevel() = FILELog::FromString("DEBUG");
	Match m = prepeare_match(argc,argv);
	States states; 
	states.read(m.state_file.c_str());
	Agent_params black_agent_params = read_agent_params(m.black_agent_file); 
	Agent_params white_agent_params = read_agent_params(m.white_agent_file); 
	bool show_play=m.show_play;
	Agent_builder b;
	Agent* b_agent = b.build(black_agent_params);
	Agent* w_agent = b.build(white_agent_params);
	FILE_LOG(logDEBUG) << "Initializing tournament between "<<b_agent->get_name()<<" and " << w_agent->get_name()<<std::endl; 
	print_header(std::cout);
	execute_match(b_agent,w_agent,states,show_play);

	delete b_agent;
	delete w_agent;

	return 0;
}

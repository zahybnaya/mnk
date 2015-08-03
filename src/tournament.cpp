#include "common.h"
#include <string.h>
#include <iostream>
#include "data_struct.h"
#include "agent_builder.h"
#include "agent.h"
#include "board.h"
#include <cassert>

struct Match {
	std::string state_file;
	std::string agent1_file;
	std::string agent2_file;
	bool show_play;
	bool verbose;
};

void missing_values(){
	std::cout << "Usage: -s <state_file> -a1 <agent_1_file> -a2 <agent_2_file> [-show_play] -v " << std::endl;
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
	std::string state_file, agent1_file, agent2_file;
	bool show_play=false;
	bool verbose = false;
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
		 if (strcmp(argv[i],"-v")==0){
	 		 verbose=true;
			 continue;
		 }
		 if (strcmp(argv[i],"-a1")==0){
	 		 agent1_file = argv[++i];
			 b_agent_check=true;
			 continue;
		 }
		 if (strcmp(argv[i],"-a2")==0){
	 		 agent2_file = argv[++i];
			 w_agent_check=true;
			 continue;
		 }
	}
	if (! (state_check && b_agent_check && w_agent_check) ){
		missing_values();
		exit(-1);
	}
	FILE_LOG(logDEBUG) << "TOURNAMENT: State file:"<<state_file << " agent file:"<<agent1_file << " agent file"<< agent2_file << std::endl;
	Match m;
	m.state_file=state_file;
	m.agent1_file=agent1_file;
	m.agent2_file=agent2_file;
	m.show_play=show_play;
	m.verbose = verbose;
	return m;
}

/**
 * Print a row in the tournamet
 * */
float game_status(board &board){
	assert(board.is_ended());
	bool black_won = board.black_has_won();
	bool white_won = board.white_has_won();
	assert(!(black_won && white_won));
	float status = 0.5;
	if(black_won){
		status = BLACK;
	} else if (white_won){
		status = WHITE;
	}
	return status;
}



/**
 * Print a row in the tournamet
 * */
inline void print_row(std::ostream& out, board &board , Agent* player, zet move){
		out << "{"<<board.pieces[BLACK]<<"," <<board.pieces[WHITE]<<"},"<<player->get_name()<<","<<player->get_agent_file()<<","<<move.zet_id << std::endl;
}


double execute_match(Agent* agent1, Agent* agent2, board board, bool verbose,  bool show_play=false){
	int playing_color = board.active_player(), active_player=0;
	const int player_1_plays =  playing_color;
	FILE_LOG(logDEBUG)<<" TOURNAMENT:Match starts with (1):"<<agent1->get_name() << " and (2):" << agent2->get_name() <<"  active player is " << playing_color<<std::endl;
	Agent* agents[] = {agent1, agent2};
	Agent* player;
       	while(!board.is_ended()){
		FILE_LOG(logDEBUG)<<board;
		if (show_play)
			std::cout << board << std::endl;
		player = agents[active_player];
		player->pre_solution();
		zet move = player->play(board,playing_color);
		FILE_LOG(logDEBUG)<<"TOURNAMENT: Agent  " <<player->get_name() << " plays " << playing_color<<std::endl;
		board = board+move;
		assert(board.pieces[playing_color] & move.zet_id);
		if (verbose)
			print_row(std::cout, board,player,move);
		player->post_solution();
		playing_color = (playing_color==0)?1:0;
		active_player = (active_player==0)?1:0;
	}
	if (show_play)
		std::cout << board << std::endl;
	assert(board.is_ended());
	float game_stat = game_status(board); 
	FILE_LOG(logDEBUG)<<"TOURNAMENT: Match ended with status " << game_stat<<std::endl;
	if (game_stat==0.5) return 0.5;
	if (game_stat==player_1_plays) return 1;
	else return 0;
}


void execute_match(Agent* agent_1, Agent* agent_2, data_struct &dat, bool verbose, bool show_play=false){
	FILE_LOG(logDEBUG) << "TOURNAMENT:Match begins" << std::endl;
	for ( int i =0 ; i < dat.Nboards ; ++i) {
		board b = dat.allboards[i];
		float p1 = execute_match(agent_1,agent_2,b, verbose , show_play);
		float p2 = execute_match(agent_2,agent_1,b, verbose , show_play);
		FILE_LOG(logDEBUG)<<"TOURNAMENT: p1:"<<p1 <<" and p2:"<<p2 << std::endl;
		float agent_stat = 0;
		if (p1>p2) agent_stat = 1; 
		else if (p1==p2) agent_stat = 0.5;
		FILE_LOG(logDEBUG)<<"TOURNAMENT: p1:"<<p1 <<" and p2:"<<p2 <<" results is " << agent_stat<< std::endl;
		std::cout<<agent_stat<<std::endl;
	} 
}

void print_header(std::ostream& o){
	o<<"board,player,player_file,move"<<std::endl;
}


int main(int argc, const char *argv[])
{
	set_debug(argc,argv);
	Match m = prepeare_match(argc,argv);
	data_struct dat; 
       	dat.load_file(m.state_file);
	Agent_params agent1_params = read_agent_params(m.agent1_file); 
	Agent_params agent2_params = read_agent_params(m.agent2_file); 
	bool show_play=m.show_play;
	Agent_builder b;
	Agent* agent1 = b.build(agent1_params);
	Agent* agent2 = b.build(agent2_params);
	FILE_LOG(logDEBUG) << "TOURNAMENT:Initializing tournament between "<<agent1->get_name()<<" and " << agent2->get_name()<<std::endl; 
	print_header(std::cout);
	execute_match(agent1,agent2,dat, m.verbose,show_play);

	delete agent1;
	delete agent2;

	return 0;
}

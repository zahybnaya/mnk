#include "board.h"
#include "states.h"
#include <fstream>
#include <string.h>
#define BW_DELIM ";"


void States::read(const char* filename){

	std::ifstream state_file;
	state_file.open(filename);
	char cstr_rep[BOARD_WIDTH * 2 * 4+1];
	std::string str_rep;
	if (state_file.is_open()) {
		while (std::getline(state_file,str_rep)) {
			strcpy(cstr_rep,str_rep.c_str());
			char* black_pieces = strtok(cstr_rep,BW_DELIM);
			char* white_pieces = strtok(NULL,BW_DELIM);
			uint64 blackpiecesULL = binstringtouint64(black_pieces);
			uint64 whitepiecesULL = binstringtouint64(white_pieces);
			board b(blackpiecesULL,whitepiecesULL);
			m_states.push_back(b);
		}
	}
	else{
		cerr<<"ERROR: file not found "<<filename<< std::endl;
	}
	state_file.close();

}


std::vector<board>::iterator States::begin(){
	return m_states.begin();
}

std::vector<board>::iterator States::end() {
	return m_states.end();
}



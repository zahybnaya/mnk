#ifndef DATA_STRUCT_H_INCLUDED
#define DATA_STRUCT_H_INCLUDED
#define NO_DATA

#include "board.h"
#include <random>
#include <vector>

#define TEST 1
#define TRAIN 2
#define ALL 0

struct data_struct{
  unsigned int Nplayers; 
  unsigned int Nboards;  
  unsigned int Ntest;
  unsigned int Ntrain;
  vector<string> player_names;
  vector<board> allboards;
  vector<zet> allmoves;
  vector<int> thinking_times;
  vector<int> player_ids;
  vector<int> test;
  vector<int> train;
  data_struct();
  
  int count_distinct_players();
  void add(board, zet, int, int);
  void print(bool);
  void clear();
  void load_board_file(char*);
  void save_board_file(char*);
  void load_file_zeyan(char*);
  void add_names_zeyan(char*);
  void execute_command_zeyan(string*, bool);
  void load_file_gianni(char*);

  void load_file(std::string);
  void load(std::string);
  void add_player(std::string);
  void add_move(std::string move_id, std::string color);
  void add_board(std::string black_pieces,std::string white_pieces, bool is_postmove,std::string move_id, std::string color );
  void add_thinking_time(std::string);
  zet make_zet(std::string move_id, std::string color);



  void add_names_gianni(char*);
  void execute_command_gianni(string*, bool);
  void make_test_and_train(double, mt19937_64);
  void write_to_header(char*);
  double compute_chance();
  vector<unsigned int> select_boards(int,int);
};

inline std::ostream& operator<<(std::ostream& o, data_struct& d){
	o<<"Data struct:"<<std::endl;
	o<<"Nplayers:" << d.Nplayers <<std::endl;
	o<<"Nboards:" << d.Nboards <<std::endl;
	o<<"Ntest:" << d.Ntest <<std::endl;
	o<<"Ntrain:" << d.Ntrain <<std::endl;
	return o;
}


#endif // DATA_STRUCT_H_INCLUDED

#ifndef DATA_STRUCT_H_INCLUDED
#define DATA_STRUCT_H_INCLUDED
//#define NO_DATA

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
  vector<string> player_name;
  vector<board> allboards;
  vector<zet> allmoves;
  vector<int> thinking_time;
  vector<int> player_id;
  vector<int> test;
  vector<int> train;
  data_struct();
  void add(board, zet, int, int);
  void print(bool);
  void clear();
  void load_board_file(char*);
  void save_board_file(char*);
  void load_file_zeyan(char*);
  void add_names_zeyan(char*);
  void execute_command_zeyan(string*, bool);
  void load_file_gianni(char*);
  void add_names_gianni(char*);
  void execute_command_gianni(string*, bool);
  void make_test_and_train(double, mt19937_64);
  void write_to_header(char*);
  double compute_chance();
  vector<unsigned int> select_boards(int,int);
};

#endif // DATA_STRUCT_H_INCLUDED

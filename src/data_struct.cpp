#include "board.h"
#include "data_struct.h"
#include <algorithm>
#include <fstream>
using namespace std;

void data_struct::add(board b, zet m, int t=0, int p=0){
  allboards.push_back(b);
  allmoves.push_back(m);
  thinking_time.push_back(t);
  player_id.push_back(p);
  Nboards++;
}

void data_struct::print(bool pause=false){
  for(unsigned int i=0;i<Nboards;i++){
    allboards[i].write(allmoves[i]);
    if(pause)
      cin.get();
  }
}

void data_struct::clear(){
  allboards.clear();
  allmoves.clear();
  thinking_time.clear();
  player_id.clear();
  train.clear();
  test.clear();
  player_name.clear();
  Nboards=0;
  Nplayers=0;
  Ntrain=0;
  Ntest=0;
}

double data_struct::compute_chance(){
  double L=0.0;
  for(unsigned int i=0;i<Nboards;i++)
    L+=log(4*BOARD_WIDTH-allboards[i].num_pieces());
  return L/Nboards;
}

void data_struct::execute_command_zeyan(string c[5],bool talk=false){
  zet m;
  static bool savemode=false;
  static uint64 t=0;
  static int filenum=0;
  static int gamenum=0;
  static board b;
  int player;
  uint64 tcurr=atoll(c[0].c_str());
  if(c[1]=="start"){
    filenum++;
    if(talk)
       cout<<c[1]<<endl;
  }
  else if (c[1]=="time out" ||
     c[1]=="switch to computer to attack" || c[1]=="show win over" ||
     c[1]=="load new board" || c[1]=="start mode" || c[1]=="game end win" ||
     c[1]=="request draw" || c[1]=="game end draw"){
    if(talk)
       cout<<c[1]<<endl;
    return;
  }
  else if(c[1]=="start exercise"){
    if(talk)
       cout<<c[1]<<endl;
    savemode=false;
  }
  else if(c[1]=="start mode 3"){
    if(talk)
       cout<<c[1]<<endl;
    savemode=true;
  }
  else if(c[1]== "player resets board"){
    b.reset();
    if(talk)
      b.write();
  }
  else if(c[1]=="new hvh"){
    b.reset();
    gamenum++;
    if(talk)
      b.write();
  }
  else if(c[1]=="reset by board"){
    b.reset();
    b.add(c[3],BLACK);
    b.add(c[4],WHITE);
    if(talk)
      b.write();
  }
  else if(c[1]=="0" || c[1]=="1"){
    m=zet(stringstouint64(c[3],c[2]),0.0,c[1]=="0"?BLACK:WHITE);
    player=2*filenum+(c[1]=="0"?0:1);
    if(savemode)
      add(b,m,(tcurr-t)*1000,player);
    b.add(m);
    if(talk)
      b.write();
  }
  else cout<<"Unknown command:\t"<<c[1]<<endl;
  t=tcurr;
}

void data_struct::add_names_zeyan(char* filename){
  string s(filename);
  unsigned int i=s.find('-');
  unsigned int j=s.find('-',i+1);
  unsigned int k=s.find('-',j+1);
  if(k==s.length()){
    player_name.push_back(s.substr(i+1,j-1));
    Nplayers++;
  }
  else {
    player_name.push_back(s.substr(i+1,j-1));
    player_name.push_back(s.substr(j+1,k-1));
    Nplayers+=2;
  }
}

void data_struct::load_file_zeyan(char* filename){
  ifstream input(filename,ios::in);
  add_names_zeyan(filename);
  string line;
  string word[5];
  int index;
  int i;
  while(!input.eof()){
    getline(input,line);
    index=0;
    i=0;
    while(index!=-1){
      index=line.find(',');
      word[i]=line.substr(0,index);
      line=line.substr(index+1);
      i++;
    }
    execute_command_zeyan(word,false);
  }
}

void data_struct::execute_command_gianni(string c[13],bool talk=false){
  static board b;
  static bool drawoffermade=false;
  zet m(tilestringtouint64(c[8]),0.0,(c[2]=="0")?BLACK:WHITE);
  double t=atof(c[9].c_str());
  int player=Nplayers-(c[1]=="0.0"?2:1);
  if(c[0]==""){
    b.reset();
    drawoffermade=false;
  }
  else if(c[5]=="draw offer")
    drawoffermade=true;
  else if(drawoffermade){
    drawoffermade=false;
    if(c[5]=="draw")
      b.reset();
  }
  else {
    if(c[5]=="playing" && c[8]!="36" && b.isempty(m))
      add(b,m,t,player);
    if(c[5]=="win" || c[5]=="draw")
      b.reset();
    else {
      b.pieces[BLACK]=binstringtouint64(c[6]);
      b.pieces[WHITE]=binstringtouint64(c[7]);
    }
  }
}

void data_struct::add_names_gianni(char* filename){
  string s(filename);
  unsigned int namestart=s.find_last_of("/\\");
  unsigned int i=s.find('_',namestart+1);
  unsigned int j=s.find('_',i+1);
  if(j==s.length()){
    player_name.push_back(s.substr(namestart+1,i-namestart-1));
    Nplayers++;
  }
  else {
    player_name.push_back(s.substr(namestart+1,i-namestart-1));
    player_name.push_back(s.substr(i+1,j-i-1));
    Nplayers+=2;
  }
}

void data_struct::load_file_gianni(char* filename){
  ifstream input(filename,ios::in);
  string line;
  string word[10];
  int index;
  int i;
  add_names_gianni(filename);
  getline(input,line);
  while(!input.eof()){
    getline(input,line);
    index=0;
    i=0;
    while(index!=-1){
      index=line.find(',');
      word[i]=line.substr(0,index);
      line=line.substr(index+1);
      i++;
    }
    if(i!=1)
      execute_command_gianni(word,true);
  }
}

void data_struct::load_board_file(char* filename){
  ifstream input(filename,ios::in);
  uint64 pblack,pwhite,m;
  string s;
  while(!input.eof()){
    input>>s;
    input>>pblack>>pwhite;
    input>>m;
    add(board(pblack,pwhite),zet(m,0.0,(s=="Black"?BLACK:WHITE)));
  }
}

void data_struct::save_board_file(char* filename){
  ofstream output2(filename,ios::out);
  board b;
  zet m;
  for(unsigned int i=0;i<Nboards;i++){
    b=allboards[i];
    m=allmoves[i];
    output2<<(m.player==BLACK?"Black\t":"White\t")<<b.pieces[BLACK]<<"\t"<<b.pieces[WHITE]<<"\t"<<m.zet_id<<endl;
  }
}

void data_struct::make_test_and_train(double frac, mt19937_64 engine){
  vector<vector<int>> board_by_player;
  for (int i = 0; i < Nplayers ; i++) {
	  vector<int> v;
  	board_by_player.push_back(v);
  }
  unsigned int n,N,k;
  train.clear();
  test.clear();
  Ntest=Ntrain=0;
  for(unsigned int j=0;j<Nboards;j++)
    board_by_player[player_id[j]].push_back(j);
  for(unsigned int p=0;p<Nplayers;p++){
    N=board_by_player[p].size();
    n=(unsigned int) N*frac;
    for(unsigned int i=0;i<n;i++){
      k=uniform_int_distribution<unsigned int> {i,N-1}(engine);
      test.push_back(board_by_player[p][k]);
      board_by_player[p][k]=board_by_player[p][i];
      Ntest++;
    }
    for(unsigned int i=n;i<N;i++){
      train.push_back(board_by_player[p][i]);
      Ntrain++;
    }
  }
  sort(test.begin(),test.end());
  sort(train.begin(),train.end());
}

vector<unsigned int> data_struct::select_boards(int player, int data_type=ALL){
  vector<unsigned int> boards;
  if(data_type==TEST){
    for(unsigned int i=0;i<Ntest;i++)
      if(player_id[test[i]]==player)
        boards.push_back(test[i]);
  }
  else if(data_type==TRAIN){
    for(unsigned int i=0;i<Ntrain;i++)
      if(player_id[train[i]]==player)
        boards.push_back(train[i]);
  }
  else for(unsigned int i=0;i<Nboards;i++)
    if(player_id[i]==player)
      boards.push_back(i);
  return boards;
}

void data_struct::write_to_header(char* filename){
  ofstream headout(filename,ios::out);
  headout<<"#include \"board.h\"\n"
  <<"#include \"data_struct.h\"\n\n"
  <<"#ifdef NO_DATA\n"
  <<"data_struct::data_struct(): Nplayers(0), Nboards(0), Ntest(0), Ntrain(0){}\n"
  <<"#else\n"
  <<"data_struct::data_struct(): Nplayers("<<Nplayers<<"), Nboards("<<Nboards<<"), Ntest("<<Ntest<<"), Ntrain("<<Ntrain<<"),\n"
  <<"player_name{";
  for(unsigned int i=0;i<Nplayers-1;i++)
    headout<<"\""<<player_name[i]<<"\",\n";
  headout<<"\""<<player_name[Nplayers-1]<<"\"},\n"
  <<"allboards{"<<hex;
  for(unsigned int i=0;i<Nboards-1;i++)
    headout<<"{0x"<<allboards[i].pieces[BLACK]<<"ULL,0x"<<allboards[i].pieces[WHITE]<<"ULL},\n";
  headout<<"{0x"<<allboards[Nboards-1].pieces[BLACK]<<"ULL,0x"<<allboards[Nboards-1].pieces[WHITE]<<"ULL}},\n"
  <<"allmoves{";
  for(unsigned int i=0;i<Nboards-1;i++)
    headout<<"{0x"<<allmoves[i].zet_id<<"ULL,0.0,"<<((allmoves[i].player==BLACK)?"BLACK":"WHITE")<<"},\n";
  headout<<"{0x"<<allmoves[Nboards-1].zet_id<<"ULL,0.0,"<<((allmoves[Nboards-1].player==BLACK)?"BLACK":"WHITE")<<"}},\n"
  <<"thinking_time{"<<dec;
  for(unsigned int i=0;i<Nboards-1;i++)
    headout<<thinking_time[i]<<",\n";
  headout<<thinking_time[Nboards-1]<<"},\n"
  <<"player_id{";
  for(unsigned int i=0;i<Nboards-1;i++)
    headout<<player_id[i]<<",\n";
  headout<<player_id[Nboards-1]<<"},\n"
  <<"test{";
  for(unsigned int i=0;i<Ntest-1;i++)
    headout<<test[i]<<",\n";
  headout<<test[Ntest-1]<<"},\n"
  <<"train{";
  for(unsigned int i=0;i<Ntrain-1;i++)
    headout<<train[i]<<",\n";
  headout<<train[Ntrain-1]<<"}{}\n#endif\n";
  headout.close();
}

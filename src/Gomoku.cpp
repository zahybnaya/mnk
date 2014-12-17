#include "heuristic.h"
#include "board_list.h"
#include "data_struct.h"
//#include "mex.h"

#define WHITE_WINS_GAME -1
#define BLACK_WINS_GAME 1
#define GAME_DRAWN 0
#define UNDETERMINED 2

#include <map>
#include <algorithm>
#include <ctime>
#include <cmath>
#include <string>
#include <thread>
#include <mutex>
using namespace std;

mutex board_list_mutex;

int playgame(heuristic& h1, heuristic& h2){
  zet m;
  board b;
  bool player=BLACK;
  do {
    if(player==BLACK)
      m=h1.makemove(b,player);
    else m=h2.makemove(b,player);
    b.add(m);
    player=!player;
  } while(m.zet_id!=0);
  if(b.white_has_won())
    return WHITE_WINS_GAME;
  if(b.black_has_won())
    return BLACK_WINS_GAME;
  return GAME_DRAWN;
}

void round_robin(heuristic* participant,int Nparticipants,ofstream& output,int firstplayer,int lastplayer){
  int result;
  for(int i=firstplayer;i<lastplayer;i++){
    for(int j=0;j<Nparticipants;j++){
      result=playgame(participant[i],participant[j]);
      output<<result<<"\t"<<flush;
    }
    cout<<i<<endl;
    output<<endl;
  }
}

void worker_thread(heuristic h,data_struct* dat,todolist* board_list){
  int i=-1;
  bool success=false;
  zet m;
  board_list_mutex.lock();
  while(board_list->get_next(i,success)){
    board_list_mutex.unlock();
    m=h.makemove_bfs(dat->allboards[i],dat->allmoves[i].player);
    success=(m.zet_id==dat->allmoves[i].zet_id);
    board_list_mutex.lock();
  }
  board_list_mutex.unlock();
}

void worker_thread_super(superheuristic s,data_struct* dat,todolist* board_list){
  int i=-1;
  bool success=false;
  zet m;
  board_list_mutex.lock();
  while(board_list->get_next(i,success)){
    board_list_mutex.unlock();
    m=s.makemove_bfs(dat->allboards[i],dat->allmoves[i].player);
    success=(m.zet_id==dat->allmoves[i].zet_id);
    board_list_mutex.lock();
  }
  board_list_mutex.unlock();
}

double compute_loglik_threads(heuristic& h,data_struct* dat,todolist* board_list){
  thread t[NTHREADS];
  for(int i=0;i<NTHREADS;i++)
    t[i]=thread(worker_thread,h,dat,board_list);
  for(int i=0;i<NTHREADS;i++)
    t[i].join();
  return board_list->get_Ltot();
}

double compute_loglik_threads_super(superheuristic& s,data_struct* dat,todolist* board_list){
  thread t[NTHREADS];
  for(int i=0;i<NTHREADS;i++)
    t[i]=thread(worker_thread_super,s,dat,board_list);
  for(int i=0;i<NTHREADS;i++)
    t[i].join();
  return board_list->get_Ltot();
}

double compute_loglik(heuristic& h, data_struct& dat, bool talk, int subject,
                      int data_type, char* times_file, char* output_file){
  todolist* board_list;
  double res;
  if(subject==-1){
    if(times_file==NULL)
      board_list=new todolist(dat.Nboards);
    else board_list=new todolist(dat.Nboards,times_file);
  }
  else{
    if(times_file==NULL)
      board_list=new todolist(dat.select_boards(subject,data_type));
    else board_list=new todolist(dat.select_boards(subject,data_type),times_file);
  }
  if(talk){
    if(output_file==NULL)
      board_list->set_cout();
    else board_list->set_output(output_file);
  }
  res=compute_loglik_threads(h,&dat,board_list);
  delete board_list;
  return res;
}

double compute_entropy(superheuristic& s,data_struct& dat,char* filename){
  todolist board_list(dat.Nboards);
  board_list.set_output(filename);
  for(unsigned int i=0;i<dat.Nboards;i++)
    dat.allmoves[i]=s.makemove_bfs(dat.allboards[i],dat.allmoves[i].player);
  return compute_loglik_threads_super(s,&dat,&board_list);
}

double compute_entropy(heuristic& h,data_struct& dat,char* filename){
  todolist board_list(dat.Nboards);
  board_list.set_output(filename);
  for(unsigned int i=0;i<dat.Nboards;i++)
    dat.allmoves[i]=h.makemove_bfs(dat.allboards[i],dat.allmoves[i].player);
  return compute_loglik_threads(h,&dat,&board_list);
}

void set_outputname(char* filename){
  unsigned int i=0;
  do sprintf(filename,"Output/out%u.txt",i),i++;
  while(ifstream(filename));
}

void drawboard(board b,zet m_human,int j, int freq[]){
  char filename[64];
  ofstream out;
  int tile;
  int sumfreq=0;
  int objectnum=1;
  sprintf(filename,"board%i.plt",j);
  out.open(filename,ios::out);
  out<<"reset\n"
     <<"set terminal pngcairo enhanced size 900,400\n"
     <<"set output \"board"<<j<<".png\"\n"
     <<"unset key\n"
     <<"unset xlabel\n"
     <<"unset ylabel\n"
     <<"unset xtics\n"
     <<"unset ytics\n"
     <<"set xrange [0 to "<<BOARD_WIDTH<<"]\n"
     <<"set yrange [0 to 4]\n";
  for(int i=0;i<4*BOARD_WIDTH;i++){
    out<<"set object "<<objectnum<<" rect from "<<i/4<<","<<i%4<<" to "<<i/4+1<<","<<i%4+1<<" fc rgb\"gray\"\n";
    objectnum++;
  }
  for(uint64 m=1;m!=boardend;m<<=1){
    if(m&b.pieces[BLACK]){
      tile=uint64totile(m);
      out<<"set object "<<objectnum<<" circ at "<<tile%BOARD_WIDTH+0.5<<","<<tile/BOARD_WIDTH+0.5
         <<" size 0.4 fs solid 0.8 fc rgb\"black\"\n";
      objectnum++;
    }
    else if(m&b.pieces[WHITE]){
      tile=uint64totile(m);
      out<<"set object "<<objectnum<<" circ at "<<tile%BOARD_WIDTH+0.5<<","<<tile/BOARD_WIDTH+0.5
         <<" size 0.4 fs solid 0.8 fc rgb\"white\"\n";
      objectnum++;
    }
  }
  for(int i=0;i<4*BOARD_WIDTH;i++)
    sumfreq+=freq[i];
  for(int i=0;i<4*BOARD_WIDTH;i++)
    if(freq[i]){
      out<<"set object "<<objectnum<<" rect from "<<i%BOARD_WIDTH<<","<<i/BOARD_WIDTH<<" to "<<i%BOARD_WIDTH+1<<","<<i/BOARD_WIDTH+1
        <<" fc rgb\"red\" fs transparent solid "<<((double) freq[i])/sumfreq<<"\n";
      objectnum++;
    }
  if(m_human.zet_id){
    tile=uint64totile(m_human.zet_id);
    out<<"set object "<<objectnum<<" circ at "<<tile%BOARD_WIDTH+0.5<<","<<tile/BOARD_WIDTH+0.5
       <<" size 0.4 fs transparent empty lw 5 fc rgb\""<<(m_human.player==BLACK?"black":"white")<<"\"\n";
  }
  out<<"plot -1\n";
  out<<flush;
  out.close();
}

void drawboard(board b,uint64 m_black,uint64 m_white,int j, int freq[]){
  char filename[64];
  ofstream out;
  int tile;
  int sumfreq=0;
  int objectnum=1;
  sprintf(filename,"board%i.plt",j);
  out.open(filename,ios::out);
  out<<"reset\n"
     <<"set terminal pngcairo enhanced size 900,400\n"
     <<"set output \"board"<<j<<".png\"\n"
     <<"unset key\n"
     <<"unset xlabel\n"
     <<"unset ylabel\n"
     <<"unset xtics\n"
     <<"unset ytics\n"
     <<"set xrange [0 to "<<BOARD_WIDTH<<"]\n"
     <<"set yrange [0 to 4]\n";
  for(int i=0;i<4*BOARD_WIDTH;i++){
    out<<"set object "<<objectnum<<" rect from "<<i/4<<","<<i%4<<" to "<<i/4+1<<","<<i%4+1<<" fc rgb\"gray\"\n";
    objectnum++;
  }
  for(uint64 m=1;m!=boardend;m<<=1){
    if(m&b.pieces[BLACK]){
      tile=uint64totile(m);
      out<<"set object "<<objectnum<<" circ at "<<tile%BOARD_WIDTH+0.5<<","<<tile/BOARD_WIDTH+0.5
         <<" size 0.4 fs solid 0.9 fc rgb\"black\"\n";
      objectnum++;
    }
    else if(m&b.pieces[WHITE]){
      tile=uint64totile(m);
      out<<"set object "<<objectnum<<" circ at "<<tile%BOARD_WIDTH+0.5<<","<<tile/BOARD_WIDTH+0.5
         <<" size 0.4 fs solid 0.9 fc rgb\"white\"\n";
      objectnum++;
    }
  }
  for(int i=0;i<4*BOARD_WIDTH;i++)
    sumfreq+=freq[i];
  for(int i=0;i<4*BOARD_WIDTH;i++)
    if(freq[i]){
      out<<"set object "<<objectnum<<" rect from "<<i%BOARD_WIDTH<<","<<i/BOARD_WIDTH<<" to "<<i%BOARD_WIDTH+1<<","<<i/BOARD_WIDTH+1
        <<" fc rgb\"red\" fs transparent solid "<<((double) freq[i])/sumfreq<<"\n";
      objectnum++;
    }
  for(uint64 m=1;m!=boardend;m<<=1){
    if(m&m_white){
      tile=uint64totile(m);
      out<<"set object "<<objectnum<<" circ at "<<tile%BOARD_WIDTH+0.5<<","<<tile/BOARD_WIDTH+0.5
         <<" size 0.4 fs solid 0.9 fc rgb\"#ECECEC\"\n";
      objectnum++;
    }
    if(m&m_black){
      tile=uint64totile(m);
      out<<"set object "<<objectnum<<" circ at "<<tile%BOARD_WIDTH+0.5<<","<<tile/BOARD_WIDTH+0.5
         <<" size 0.4 fs solid 0.9 fc rgb\"#595959\"\n";
      objectnum++;
    }
  }
  out<<"plot -1\n";
  out<<flush;
  out.close();
}

#ifdef mex_h
void mexFunction(int nlhs, mxArray *plhs[],int nrhs, const mxArray *prhs[]){
  heuristic h;
  data_struct dat;
  unsigned int seed=unsigned(time(0));
  mt19937_64 global_generator;
  double* playerptr=mxGetPr(prhs[0]);
  int player=((int) (*playerptr+0.5));
  double* paramptr=mxGetPr(prhs[1]);
  global_generator.seed(seed);
  h.seed_generator(global_generator);
  h.get_params_from_matlab(paramptr);
  plhs[0] = mxCreateDoubleScalar(compute_loglik(h,dat,true,player,TEST,"times.txt","Output/out.txt"));
}
#else
int main(int argc, char* argv[]){
  heuristic h;
  superheuristic s;
  data_struct dat;
  unsigned int seed=unsigned(time(0));
  mt19937_64 global_generator;
  char filename[128];
  ofstream output;
  board b;
  zet m;
  cout<<"seed = "<<seed<<endl;
  //sprintf(filename,"loglik_boards%i.txt",subject);
  //output.open(filename,ios::out);
  global_generator.seed(seed);
  for(int i=0;i<dat.Nplayers;i++)
    cout<<dat.player_name[i]<<"\t"<<compute_loglik(h,dat,false,i,ALL,NULL,NULL)<<endl;
  //output.close();
  return 0;
}
#endif

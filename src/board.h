#ifndef BOARD_H_INCLUDED
#define BOARD_H_INCLUDED

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cstdint>
#include <vector>

#define BLACK 0
#define WHITE 1

#define BOARD_WIDTH 9
using namespace std;

#ifndef _WIN64
#define HPC_CLUSTER
#endif

typedef uint64_t uint64;

#if BOARD_WIDTH==11
const uint64 boardend =0x000100000000000ULL;
const uint64 full   =0x0000fffffffffffULL;
const uint64 center =0x00001f03e07c0f8ULL;
const uint64 allbutfirstcol = 0x00000ffdffbff7feULL;

inline bool is_win(uint64 pieces) {
  return (pieces & (pieces>>BOARD_WIDTH) & (pieces>>(2*BOARD_WIDTH)) & (pieces>>(3*BOARD_WIDTH))) ||
         (pieces & (pieces>>(BOARD_WIDTH+1)) & (pieces>>(2*BOARD_WIDTH+2)) & (pieces>>(3*BOARD_WIDTH+3))) ||
         (pieces & (pieces>>(BOARD_WIDTH-1)) & (pieces>>(2*BOARD_WIDTH-2)) & (pieces>>(3*BOARD_WIDTH-3)) & 0x0000000000007f8ULL) ||
         (pieces & (pieces>>1) & (pieces>>2) & (pieces>>3) & 0x00001fe3fc7f8ffULL);
}
#elif BOARD_WIDTH==9
const uint64 boardend =0x000001000000000ULL;
const uint64 full     =0x000000fffffffffULL;
const uint64 center         =0x00000001c0e07038ULL;
const uint64 allbutfirstcol =0x0000000ff7fbfdfeULL;
const uint64 allbutlastcol =0x00000007fbfdfeffULL;
const uint64 allbutfirstrow =0x0000000ffffffe00ULL;
const uint64 allbutlastrow =0x0000000007ffffffULL;

inline bool is_win(uint64 pieces) {
  return (pieces & (pieces>>BOARD_WIDTH) & (pieces>>(2*BOARD_WIDTH)) & (pieces>>(3*BOARD_WIDTH))) ||
         (pieces & (pieces>>(BOARD_WIDTH+1)) & (pieces>>(2*BOARD_WIDTH+2)) & (pieces>>(3*BOARD_WIDTH+3))) ||
         (pieces & (pieces>>(BOARD_WIDTH-1)) & (pieces>>(2*BOARD_WIDTH-2)) & (pieces>>(3*BOARD_WIDTH-3)) & 0x0000000000001f8ULL) ||
         (pieces & (pieces>>1) & (pieces>>2) & (pieces>>3) & 0x0000001f8fc7e3fULL);
}
#endif // BOARD_WIDTH

inline int num_bits(uint64 x){
    const uint64 m1  = 0x5555555555555555ULL; //binary: 0101...
    const uint64 m2  = 0x3333333333333333ULL; //binary: 00110011..
    const uint64 m4  = 0x0f0f0f0f0f0f0f0fULL; //binary:  4 zeros,  4 ones ...
    const uint64 m8  = 0x00ff00ff00ff00ffULL; //binary:  8 zeros,  8 ones ...
    const uint64 m16 = 0x0000ffff0000ffffULL; //binary: 16 zeros, 16 ones ...
    const uint64 m32 = 0x00000000ffffffffULL; //binary: 32 zeros, 32 ones
    x = (x & m1 ) + ((x >>  1) & m1 ); //put count of each  2 bits into those  2 bits
    x = (x & m2 ) + ((x >>  2) & m2 ); //put count of each  4 bits into those  4 bits
    x = (x & m4 ) + ((x >>  4) & m4 ); //put count of each  8 bits into those  8 bits
    x = (x & m8 ) + ((x >>  8) & m8 ); //put count of each 16 bits into those 16 bits
    x = (x & m16) + ((x >> 16) & m16); //put count of each 32 bits into those 32 bits
    x = (x & m32) + ((x >> 32) & m32); //put count of each 64 bits into those 64 bits
    return x;
}

inline bool has_one_bit(uint64 x){
  return  x && !(x & (x-1));
}

inline uint64 rctouint64(int row, int col){
  uint64 temp=1;
  temp <<= (row*BOARD_WIDTH + col);
  return temp;
}

inline uint64 tilestringtouint64(string s){
  uint64 m=1;
  int tile=atoi(s.c_str());
  return m<<=(4*BOARD_WIDTH-tile-1);
}

inline uint64 binstringtouint64(string s){
  return strtoull(s.c_str(),NULL,2);
}

inline uint64 stringstouint64(string sr, string sc){
  return rctouint64(atoi(sr.c_str())-1,atoi(sc.c_str())-1);
}

inline int uint64totile(uint64 m){
  int i=4*BOARD_WIDTH;
  while(m){
    i--;
    m>>=1;
  }
  return i;
}





inline string uint64tobinstring(uint64 m){
  string s(4*BOARD_WIDTH,'0');
  for(int i=4*BOARD_WIDTH-1;i>=0;i--){
    if(m&1)
      s[i]='1';
    m>>=1;
  }
  return s;
}

inline uint64 shift(uint64 m, int row, int col){
  if(row<0)
    for(int i=0;i>row;i--)
      m>>=BOARD_WIDTH;
  else if(row>0)
    for(int i=0;i<row;i++)
      m=(m & allbutlastrow)<<BOARD_WIDTH;
  if(col<0)
    for(int i=0;i>col;i--)
      m=(m & allbutfirstcol)>>1;
  else if(col>0)
    for(int i=0;i<col;i++)
      m=(m & allbutlastcol)<<1;
  return m;
}

inline int rowmax(uint64 m){
  int temp=5;
  while(m){
    m>>=BOARD_WIDTH;
    temp--;
  }
  return temp;
}

inline int rowmin(uint64 m){
  int temp=-4;
  while(m){
    m=(m & allbutlastrow)<<BOARD_WIDTH;
    temp++;
  }
  return temp;
}

inline int colmax(uint64 m){
  int temp=BOARD_WIDTH+1;
  while(m){
    m=(m & allbutfirstcol)>>1;
    temp--;
  }
  return temp;
}

inline int colmin(uint64 m){
  int temp=-BOARD_WIDTH;
  while(m){
    m=(m & allbutlastcol)<<1;
    temp++;
  }
  return temp;
}

inline int rowmax(uint64 m1, uint64 m2){
  int temp=5;
  while(m1 | m2){
    m1>>=BOARD_WIDTH;
    m2>>=BOARD_WIDTH;
    temp--;
  }
  return temp;
}

inline int rowmin(uint64 m1, uint64 m2){
  int temp=-4;
  while(m1 | m2){
    m1=(m1 & allbutlastrow)<<BOARD_WIDTH;
    m2=(m2 & allbutlastrow)<<BOARD_WIDTH;
    temp++;
  }
  return temp;
}

inline int colmax(uint64 m1, uint64 m2){
  int temp=BOARD_WIDTH+1;
  while(m1 | m2){
    m1=(m1 & allbutfirstcol)>>1;
    m2=(m2 & allbutfirstcol)>>1;
    temp--;
  }
  return temp;
}

inline int colmin(uint64 m1, uint64 m2){
  int temp=-BOARD_WIDTH;
  while(m1 | m2){
    m1=(m1 & allbutlastcol)<<1;
    m2=(m2 & allbutlastcol)<<1;
    temp++;
  }
  return temp;
}

inline int rowmax(uint64 m1, uint64 m2, int n){
  int temp=5;
  int total_bits=num_bits(m2);
  while(m1 || num_bits(m2)>total_bits-n){
    m1>>=BOARD_WIDTH;
    m2>>=BOARD_WIDTH;
    temp--;
  }
  return temp;
}

inline int rowmin(uint64 m1, uint64 m2, int n){
  int temp=-4;
  int total_bits=num_bits(m2);
  while(m1 || num_bits(m2)>total_bits-n){
    m1=(m1 & allbutlastrow)<<BOARD_WIDTH;
    m2=(m2 & allbutlastrow)<<BOARD_WIDTH;
    temp++;
  }
  return temp;
}

inline int colmax(uint64 m1, uint64 m2, int n){
  int temp=BOARD_WIDTH+1;
  int total_bits=num_bits(m2);
  while(m1 || num_bits(m2)>total_bits-n){
    m1=(m1 & allbutfirstcol)>>1;
    m2=(m2 & allbutfirstcol)>>1;
    temp--;
  }
  return temp;
}

inline int colmin(uint64 m1, uint64 m2, int n){
  int temp=-BOARD_WIDTH;
  int total_bits=num_bits(m2);
  while(m1 || num_bits(m2)>total_bits-n){
    m1=(m1 & allbutlastcol)<<1;
    m2=(m2 & allbutlastcol)<<1;
    temp++;
  }
  return temp;
}


struct zet{
  uint64 zet_id;
  double val;
  bool player;
  zet(): zet_id(0), val(0.0), player(BLACK){}
  zet(uint64 m,double v,bool p): zet_id(m), val(v), player(p){};
  zet(int row, int col, double v, bool p): zet_id(rctouint64(row,col)), val(v), player(p){}
};

inline bool compare(zet a, zet b){
  return a.val>b.val;
}

/**
 * Comparator structure for zets use this 
 * on a max procedure
 * */
struct zet_comparator_t {
	zet_comparator_t(bool player): player(player){};
	bool operator()(zet z1, zet z2){ 
		if (player==BLACK){
			return z1.val < z2.val;
		}else{
			return z1.val > z2.val;
		}
	};
	bool player;
};


struct board{
  board(): pieces{0,0}{}
  board(uint64 blackpieces, uint64 whitepieces): pieces {blackpieces,whitepieces}{}
  inline void reset(){
    pieces[WHITE]=pieces[BLACK]=0;
  }
  inline bool isempty(zet m){
    return isempty(m.zet_id);
  }
  inline bool isempty(uint64 m){
    return !(m & pieces[BLACK] || m & pieces[WHITE]);
  }
  inline int Nfull(zet m, bool player){
    return Nfull(m.zet_id, player);
  }
  inline int Nfull(uint64 m, bool player){
    return num_bits(m & pieces[player]);
  }
  inline int Nempty(zet m){
    return Nempty(m.zet_id);
  }
  inline int Nempty(uint64 m){
    return num_bits(m & (~pieces[BLACK]) & (~pieces[WHITE]));
  }
  inline bool contains(uint64 m,bool player){
    return !(m & ~pieces[player]);
  }
  inline bool add(int row, int col, bool player){
    return add(rctouint64(row,col),player);
  }
  inline bool add(string c, bool player=BLACK){
    return add(atoll(c.c_str()),player);
  }
  inline bool add(string c1, string c2, bool player=BLACK){
    return add(stringstouint64(c1,c2),player);
  }
  inline bool add(uint64 m, bool player=BLACK){
    if(m & pieces[BLACK] || m & pieces[WHITE])
      return false;
    pieces[player] |= m;
    return true;
  }
  inline bool add(zet m){
    return add(m.zet_id,m.player);
  }
  inline void remove_piece(int row, int col){
    remove_piece(rctouint64(row,col));
  }
  inline void remove_piece(zet m){
    remove_piece(m.zet_id);
  }
  inline void remove_piece(uint64 m){
    pieces[BLACK] &= ~m;
    pieces[WHITE] &= ~m;
  }
  inline bool is_full() {
    return (pieces[BLACK] | pieces[WHITE])==full;
  }

  inline bool is_ended() {
    return is_win(pieces[BLACK])|| is_win(pieces[WHITE]) || is_full() ;
  }
  inline bool black_has_won() {
    return is_win(pieces[BLACK]);
  }

  inline bool white_has_won() {
    return is_win(pieces[WHITE]);
  }
  inline bool player_has_won(bool player) {
    return is_win(pieces[player]);
  }
  inline int num_pieces(){
    return num_bits(pieces[BLACK] | pieces [WHITE]);
  }
  inline void write(zet m){
    write(m.zet_id);
    cout<<m.val<<"\t"<<((m.player==BLACK)?"BLACK":"WHITE")<<endl;
  }
  inline bool active_player(){
    return (num_bits(pieces[BLACK] | pieces[WHITE]))%2;
  }
  inline void write(uint64 m=0,ostream& o=cout ){
    uint64 temp = 1;
    o<<"+";
    for(unsigned int col=0;col<BOARD_WIDTH;col++)
      o<<"-";
    o<<"+"<<endl;
    for(unsigned int row=0;row<4;row++){
      o<<"|";
      for(unsigned int col=0;col<BOARD_WIDTH;col++){
        if (m & temp)
          o<<"#";
        else if(pieces[BLACK] & temp)
          o<<"o";
        else if(pieces[WHITE] & temp)
          o<<"x";
        else o<<" ";
        temp<<= 1;
      }
      o<<"|"<<endl;
    }
    o<<"+";
    for(unsigned int col=0;col<BOARD_WIDTH;col++)
      o<<"-";
    o<<"+"<<endl;
  }
  board operator+ (const zet m){
    board temp(pieces[BLACK],pieces[WHITE]);
    temp.add(m);
    return temp;
  }
  bool operator< (const board& b) const {
    if(pieces[BLACK]<b.pieces[BLACK])
      return true;
    return pieces[WHITE]<b.pieces[WHITE];
  }
  uint64 pieces[2];
}; //END OF BOARD STRUCT

/**
 * Returns a list of possible moves without a value
 */
inline vector<zet> enumerate_moves(board& b, bool player){
  vector<zet> candidate;
  for(uint64 m=1;m!=boardend;m<<=1){
	if(b.isempty(m)){
		candidate.push_back(zet(m,0,player));
	}
  }
  return candidate;
}

/**
 * Returns a list of possible moves without a value
 */
inline vector<uint64> enumerate_moves_uint64(board& b){
  vector<uint64> candidate;
  for(uint64 m=1;m!=boardend;m<<=1){
	if(b.isempty(m)){
		candidate.push_back(m);
	}
  }
  return candidate;
}


/**
 * Returns a list of pieces on the board
 */
inline vector<uint64> enumerate_pieces_uint64(board& b){
  vector<uint64> pieces;
  for(uint64 m=1;m!=boardend;m<<=1){
	if(!b.isempty(m)){
		pieces.push_back(m);
	}
  }
  return pieces;
}



inline std::ostream& operator<<(std::ostream& o, board& b){
    uint64 temp = 1,m=0;
    o<<"+";
    for(unsigned int col=0;col<BOARD_WIDTH;col++)
      o<<"-";
    o<<"+"<<endl;
    for(unsigned int row=0;row<4;row++){
      o<<"|";
      for(unsigned int col=0;col<BOARD_WIDTH;col++){
        if (m & temp)
          o<<"#";
        else if(b.pieces[BLACK] & temp)
          o<<"B";
        else if(b.pieces[WHITE] & temp)
          o<<"W";
        else o<<" ";
        temp<<= 1;
      }
      o<<"|"<<endl;
    }
    o<<"+";
    for(unsigned int col=0;col<BOARD_WIDTH;col++)
      o<<"-";
    o<<"+"<<endl;
    return o;
}

typedef std::pair<uint64,uint64> match_t;
class Motif {
	public:
		Motif(){};
		Motif(std::vector<match_t> matches):matches(matches){};
		inline void add(uint64 match,uint64 freespots){
			matches.push_back(match_t(match,freespots));
		}
		inline void add(uint64 match){
			uint64 freespots = 0;
			matches.push_back(match_t(match,freespots));
		}

		int exists(board &b,int player);
		std::vector<match_t> getMatches(board &b,int player);
	private:
		std::vector<match_t> matches;

};

inline int Motif::exists(board &b, int player){
	int ret=0;
	int opp = (player==WHITE?BLACK:WHITE);
	for(std::vector<match_t>::iterator i = matches.begin() ; i != matches.end(); ++i){
		if(i->second==0){
			int toadd=((b.pieces[player] & (i->first))==(i->first)) ?1:0;  	
			if(toadd){
				ret += 	toadd;
			}
		}else{
			ret += (((b.pieces[player] & (i->first))==(i->first)) && (i->second & (~b.pieces[opp])))?1:0;  	
		} 
	}
	return ret;
}



inline std::vector<match_t> Motif::getMatches(board &b,int player){
	int opp = (player==WHITE?BLACK:WHITE);
	std::vector<match_t> ret;
	for(std::vector<match_t>::iterator i = matches.begin() ; i != matches.end(); ++i){
		if(i->second==0){
			if((b.pieces[player] & (i->first))==(i->first))
				ret.push_back(*i);
		}else{
			if (((b.pieces[player] & (i->first))==(i->first)) && (i->second & (~b.pieces[opp])))
				ret.push_back(*i);
		} 
	}
	return ret;
}

#endif // BOARD_H_INCLUDED

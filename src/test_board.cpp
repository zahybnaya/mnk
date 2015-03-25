#include <iostream>
#include <sstream>
#include "board.h"


int main(int argc, char* argv[]){
	board b;
	std::cout<<b;
	int row=1;
	int col=1;
	uint64 i = rctouint64(row, col);
	int tile=uint64totile(i);
	//std::cout<<"the tile of "<<i<<" is "<<tile<<std::endl;
	//uint64 bintouint64 = binstringtouint64(binstring);
	//uint64 tilefromuint64 = tilestringtouint64(tile);

	std::cout<<"for row:"<<row<<" and col:"<<col<< " the uint64 is "<<i <<" and tile is:"<<tile<<std::endl;  
	//std::cout<<" uint64totile() for "<<i<< " is "<< tile<<std::endl;
	//std::cout<<" uint64tobinstring() for "<<i<< " is "<< binstring<<std::endl;
	std::cout<<"Board with i" <<std::endl;
	zet z(i,0,0);
	b.add(z);
	std::cout<<b;

	std::cout<<"Board with tile" <<std::endl;
	board b2; 
	b2.add(zet(tile,0,0));
	std::cout<<b2;


	std::cout<<"Board from string " <<std::endl;
	std::ostringstream o;
	o << i;
	std::string uint_string =  o.str();
	std::cout<<"this is the string:"<<uint_string<<std::endl;
	board b1;
	zet z1(tilestringtouint64(uint_string),0,0);
	b1.add(z1);
	std::cout<<b1;
	

	std::cout<<"***Board from string " <<std::endl;
	board b4;
	uint64 raw = strtoull(uint_string.c_str(),NULL,0);

	zet z3(raw,0,0);
	b4.add(z3);
	std::cout<<b4;
	


	
}

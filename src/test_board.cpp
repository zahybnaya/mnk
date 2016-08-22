#include <iostream>
#include <sstream>
#include "board.h"
#include "heuristic.h"

//0x0000000000001f8ULL

void print_all_wins(){

	board bt; 
	bt.pieces[WHITE]=binstringtouint64("111100000000000000000000000000000000"); std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("011110000000000000000000000000000000"); std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("001111000000000000000000000000000000"); std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000111100000000000000000000000000000"); std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000011110000000000000000000000000000"); std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000001111000000000000000000000000000"); std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000000000111100000000000000000000000"); std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000000000011110000000000000000000000"); std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000000000001111000000000000000000000"); std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000000000000111100000000000000000000"); std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000000000000011110000000000000000000"); std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000000000000001111000000000000000000"); std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000000000000000000111100000000000000"); std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000000000000000000011110000000000000"); std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000000000000000000001111000000000000"); std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000000000000000000000111100000000000"); std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000000000000000000000011110000000000"); std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000000000000000000000001111000000000"); std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000000000000000000000000000111100000"); std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000000000000000000000000000011110000"); std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000000000000000000000000000001111000"); std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000000000000000000000000000000111100"); std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000000000000000000000000000000011110"); std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000000000000000000000000000000001111"); std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("100000000100000000100000000100000000"); std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("010000000010000000010000000010000000"); std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("001000000001000000001000000001000000"); std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000100000000100000000100000000100000"); std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000010000000010000000010000000010000"); std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000001000000001000000001000000001000"); std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000000100000000100000000100000000100"); std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000000010000000010000000010000000010"); std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000000001000000001000000001000000001"); std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("100000000010000000001000000000100000"); std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("010000000001000000000100000000010000"); std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("001000000000100000000010000000001000"); std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000100000000010000000001000000000100"); std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000010000000001000000000100000000010"); std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000001000000000100000000010000000001"); std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000000001000000010000000100000001000"); std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000000010000000100000001000000010000"); std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000000100000001000000010000000100000"); std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000001000000010000000100000001000000"); std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000010000000100000001000000010000000"); std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000100000001000000010000000100000000"); std::cout<<bt;


}
void print_all_threats(){

	board bt; 
	bt.pieces[WHITE]=binstringtouint64("011100000000000000000000000000000000"); bt.pieces[BLACK]=binstringtouint64("100000000000000000000000000000000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("101100000000000000000000000000000000"); bt.pieces[BLACK]=binstringtouint64("010000000000000000000000000000000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("110100000000000000000000000000000000"); bt.pieces[BLACK]=binstringtouint64("001000000000000000000000000000000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("111000000000000000000000000000000000"); bt.pieces[BLACK]=binstringtouint64("000100000000000000000000000000000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("001110000000000000000000000000000000"); bt.pieces[BLACK]=binstringtouint64("010000000000000000000000000000000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("010110000000000000000000000000000000"); bt.pieces[BLACK]=binstringtouint64("001000000000000000000000000000000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("011010000000000000000000000000000000"); bt.pieces[BLACK]=binstringtouint64("000100000000000000000000000000000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("011100000000000000000000000000000000"); bt.pieces[BLACK]=binstringtouint64("000010000000000000000000000000000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000111000000000000000000000000000000"); bt.pieces[BLACK]=binstringtouint64("001000000000000000000000000000000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("001011000000000000000000000000000000"); bt.pieces[BLACK]=binstringtouint64("000100000000000000000000000000000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("001101000000000000000000000000000000"); bt.pieces[BLACK]=binstringtouint64("000010000000000000000000000000000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("001110000000000000000000000000000000"); bt.pieces[BLACK]=binstringtouint64("000001000000000000000000000000000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000011100000000000000000000000000000"); bt.pieces[BLACK]=binstringtouint64("000100000000000000000000000000000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000101100000000000000000000000000000"); bt.pieces[BLACK]=binstringtouint64("000010000000000000000000000000000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000110100000000000000000000000000000"); bt.pieces[BLACK]=binstringtouint64("000001000000000000000000000000000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000111000000000000000000000000000000"); bt.pieces[BLACK]=binstringtouint64("000000100000000000000000000000000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000001110000000000000000000000000000"); bt.pieces[BLACK]=binstringtouint64("000010000000000000000000000000000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000010110000000000000000000000000000"); bt.pieces[BLACK]=binstringtouint64("000001000000000000000000000000000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000011010000000000000000000000000000"); bt.pieces[BLACK]=binstringtouint64("000000100000000000000000000000000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000011100000000000000000000000000000"); bt.pieces[BLACK]=binstringtouint64("000000010000000000000000000000000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000000111000000000000000000000000000"); bt.pieces[BLACK]=binstringtouint64("000001000000000000000000000000000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000001011000000000000000000000000000"); bt.pieces[BLACK]=binstringtouint64("000000100000000000000000000000000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000001101000000000000000000000000000"); bt.pieces[BLACK]=binstringtouint64("000000010000000000000000000000000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000001110000000000000000000000000000"); bt.pieces[BLACK]=binstringtouint64("000000001000000000000000000000000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000000000011100000000000000000000000"); bt.pieces[BLACK]=binstringtouint64("000000000100000000000000000000000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000000000101100000000000000000000000"); bt.pieces[BLACK]=binstringtouint64("000000000010000000000000000000000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000000000110100000000000000000000000"); bt.pieces[BLACK]=binstringtouint64("000000000001000000000000000000000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000000000111000000000000000000000000"); bt.pieces[BLACK]=binstringtouint64("000000000000100000000000000000000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000000000001110000000000000000000000"); bt.pieces[BLACK]=binstringtouint64("000000000010000000000000000000000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000000000010110000000000000000000000"); bt.pieces[BLACK]=binstringtouint64("000000000001000000000000000000000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000000000011010000000000000000000000"); bt.pieces[BLACK]=binstringtouint64("000000000000100000000000000000000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000000000011100000000000000000000000"); bt.pieces[BLACK]=binstringtouint64("000000000000010000000000000000000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000000000000111000000000000000000000"); bt.pieces[BLACK]=binstringtouint64("000000000001000000000000000000000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000000000001011000000000000000000000"); bt.pieces[BLACK]=binstringtouint64("000000000000100000000000000000000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000000000001101000000000000000000000"); bt.pieces[BLACK]=binstringtouint64("000000000000010000000000000000000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000000000001110000000000000000000000"); bt.pieces[BLACK]=binstringtouint64("000000000000001000000000000000000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000000000000011100000000000000000000"); bt.pieces[BLACK]=binstringtouint64("000000000000100000000000000000000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000000000000101100000000000000000000"); bt.pieces[BLACK]=binstringtouint64("000000000000010000000000000000000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000000000000110100000000000000000000"); bt.pieces[BLACK]=binstringtouint64("000000000000001000000000000000000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000000000000111000000000000000000000"); bt.pieces[BLACK]=binstringtouint64("000000000000000100000000000000000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000000000000001110000000000000000000"); bt.pieces[BLACK]=binstringtouint64("000000000000010000000000000000000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000000000000010110000000000000000000"); bt.pieces[BLACK]=binstringtouint64("000000000000001000000000000000000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000000000000011010000000000000000000"); bt.pieces[BLACK]=binstringtouint64("000000000000000100000000000000000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000000000000011100000000000000000000"); bt.pieces[BLACK]=binstringtouint64("000000000000000010000000000000000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000000000000000111000000000000000000"); bt.pieces[BLACK]=binstringtouint64("000000000000001000000000000000000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000000000000001011000000000000000000"); bt.pieces[BLACK]=binstringtouint64("000000000000000100000000000000000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000000000000001101000000000000000000"); bt.pieces[BLACK]=binstringtouint64("000000000000000010000000000000000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000000000000001110000000000000000000"); bt.pieces[BLACK]=binstringtouint64("000000000000000001000000000000000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000000000000000000011100000000000000"); bt.pieces[BLACK]=binstringtouint64("000000000000000000100000000000000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000000000000000000101100000000000000"); bt.pieces[BLACK]=binstringtouint64("000000000000000000010000000000000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000000000000000000110100000000000000"); bt.pieces[BLACK]=binstringtouint64("000000000000000000001000000000000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000000000000000000111000000000000000"); bt.pieces[BLACK]=binstringtouint64("000000000000000000000100000000000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000000000000000000001110000000000000"); bt.pieces[BLACK]=binstringtouint64("000000000000000000010000000000000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000000000000000000010110000000000000"); bt.pieces[BLACK]=binstringtouint64("000000000000000000001000000000000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000000000000000000011010000000000000"); bt.pieces[BLACK]=binstringtouint64("000000000000000000000100000000000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000000000000000000011100000000000000"); bt.pieces[BLACK]=binstringtouint64("000000000000000000000010000000000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000000000000000000000111000000000000"); bt.pieces[BLACK]=binstringtouint64("000000000000000000001000000000000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000000000000000000001011000000000000"); bt.pieces[BLACK]=binstringtouint64("000000000000000000000100000000000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000000000000000000001101000000000000"); bt.pieces[BLACK]=binstringtouint64("000000000000000000000010000000000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000000000000000000001110000000000000"); bt.pieces[BLACK]=binstringtouint64("000000000000000000000001000000000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000000000000000000000011100000000000"); bt.pieces[BLACK]=binstringtouint64("000000000000000000000100000000000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000000000000000000000101100000000000"); bt.pieces[BLACK]=binstringtouint64("000000000000000000000010000000000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000000000000000000000110100000000000"); bt.pieces[BLACK]=binstringtouint64("000000000000000000000001000000000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000000000000000000000111000000000000"); bt.pieces[BLACK]=binstringtouint64("000000000000000000000000100000000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000000000000000000000001110000000000"); bt.pieces[BLACK]=binstringtouint64("000000000000000000000010000000000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000000000000000000000010110000000000"); bt.pieces[BLACK]=binstringtouint64("000000000000000000000001000000000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000000000000000000000011010000000000"); bt.pieces[BLACK]=binstringtouint64("000000000000000000000000100000000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000000000000000000000011100000000000"); bt.pieces[BLACK]=binstringtouint64("000000000000000000000000010000000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000000000000000000000000111000000000"); bt.pieces[BLACK]=binstringtouint64("000000000000000000000001000000000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000000000000000000000001011000000000"); bt.pieces[BLACK]=binstringtouint64("000000000000000000000000100000000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000000000000000000000001101000000000"); bt.pieces[BLACK]=binstringtouint64("000000000000000000000000010000000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000000000000000000000001110000000000"); bt.pieces[BLACK]=binstringtouint64("000000000000000000000000001000000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000000000000000000000000000011100000"); bt.pieces[BLACK]=binstringtouint64("000000000000000000000000000100000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000000000000000000000000000101100000"); bt.pieces[BLACK]=binstringtouint64("000000000000000000000000000010000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000000000000000000000000000110100000"); bt.pieces[BLACK]=binstringtouint64("000000000000000000000000000001000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000000000000000000000000000111000000"); bt.pieces[BLACK]=binstringtouint64("000000000000000000000000000000100000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000000000000000000000000000001110000"); bt.pieces[BLACK]=binstringtouint64("000000000000000000000000000010000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000000000000000000000000000010110000"); bt.pieces[BLACK]=binstringtouint64("000000000000000000000000000001000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000000000000000000000000000011010000"); bt.pieces[BLACK]=binstringtouint64("000000000000000000000000000000100000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000000000000000000000000000011100000"); bt.pieces[BLACK]=binstringtouint64("000000000000000000000000000000010000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000000000000000000000000000000111000"); bt.pieces[BLACK]=binstringtouint64("000000000000000000000000000001000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000000000000000000000000000001011000"); bt.pieces[BLACK]=binstringtouint64("000000000000000000000000000000100000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000000000000000000000000000001101000"); bt.pieces[BLACK]=binstringtouint64("000000000000000000000000000000010000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000000000000000000000000000001110000"); bt.pieces[BLACK]=binstringtouint64("000000000000000000000000000000001000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000000000000000000000000000000011100"); bt.pieces[BLACK]=binstringtouint64("000000000000000000000000000000100000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000000000000000000000000000000101100"); bt.pieces[BLACK]=binstringtouint64("000000000000000000000000000000010000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000000000000000000000000000000110100"); bt.pieces[BLACK]=binstringtouint64("000000000000000000000000000000001000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000000000000000000000000000000111000"); bt.pieces[BLACK]=binstringtouint64("000000000000000000000000000000000100");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000000000000000000000000000000001110"); bt.pieces[BLACK]=binstringtouint64("000000000000000000000000000000010000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000000000000000000000000000000010110"); bt.pieces[BLACK]=binstringtouint64("000000000000000000000000000000001000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000000000000000000000000000000011010"); bt.pieces[BLACK]=binstringtouint64("000000000000000000000000000000000100");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000000000000000000000000000000011100"); bt.pieces[BLACK]=binstringtouint64("000000000000000000000000000000000010");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000000000000000000000000000000000111"); bt.pieces[BLACK]=binstringtouint64("000000000000000000000000000000001000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000000000000000000000000000000001011"); bt.pieces[BLACK]=binstringtouint64("000000000000000000000000000000000100");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000000000000000000000000000000001101"); bt.pieces[BLACK]=binstringtouint64("000000000000000000000000000000000010");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000000000000000000000000000000001110"); bt.pieces[BLACK]=binstringtouint64("000000000000000000000000000000000001");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000000000100000000100000000100000000"); bt.pieces[BLACK]=binstringtouint64("100000000000000000000000000000000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("100000000000000000100000000100000000"); bt.pieces[BLACK]=binstringtouint64("000000000100000000000000000000000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("100000000100000000000000000100000000"); bt.pieces[BLACK]=binstringtouint64("000000000000000000100000000000000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("100000000100000000100000000000000000"); bt.pieces[BLACK]=binstringtouint64("000000000000000000000000000100000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000000000010000000010000000010000000"); bt.pieces[BLACK]=binstringtouint64("010000000000000000000000000000000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("010000000000000000010000000010000000"); bt.pieces[BLACK]=binstringtouint64("000000000010000000000000000000000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("010000000010000000000000000010000000"); bt.pieces[BLACK]=binstringtouint64("000000000000000000010000000000000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("010000000010000000010000000000000000"); bt.pieces[BLACK]=binstringtouint64("000000000000000000000000000010000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000000000001000000001000000001000000"); bt.pieces[BLACK]=binstringtouint64("001000000000000000000000000000000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("001000000000000000001000000001000000"); bt.pieces[BLACK]=binstringtouint64("000000000001000000000000000000000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("001000000001000000000000000001000000"); bt.pieces[BLACK]=binstringtouint64("000000000000000000001000000000000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("001000000001000000001000000000000000"); bt.pieces[BLACK]=binstringtouint64("000000000000000000000000000001000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000000000000100000000100000000100000"); bt.pieces[BLACK]=binstringtouint64("000100000000000000000000000000000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000100000000000000000100000000100000"); bt.pieces[BLACK]=binstringtouint64("000000000000100000000000000000000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000100000000100000000000000000100000"); bt.pieces[BLACK]=binstringtouint64("000000000000000000000100000000000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000100000000100000000100000000000000"); bt.pieces[BLACK]=binstringtouint64("000000000000000000000000000000100000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000000000000010000000010000000010000"); bt.pieces[BLACK]=binstringtouint64("000010000000000000000000000000000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000010000000000000000010000000010000"); bt.pieces[BLACK]=binstringtouint64("000000000000010000000000000000000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000010000000010000000000000000010000"); bt.pieces[BLACK]=binstringtouint64("000000000000000000000010000000000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000010000000010000000010000000000000"); bt.pieces[BLACK]=binstringtouint64("000000000000000000000000000000010000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000000000000001000000001000000001000"); bt.pieces[BLACK]=binstringtouint64("000001000000000000000000000000000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000001000000000000000001000000001000"); bt.pieces[BLACK]=binstringtouint64("000000000000001000000000000000000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000001000000001000000000000000001000"); bt.pieces[BLACK]=binstringtouint64("000000000000000000000001000000000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000001000000001000000001000000000000"); bt.pieces[BLACK]=binstringtouint64("000000000000000000000000000000001000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000000000000000100000000100000000100"); bt.pieces[BLACK]=binstringtouint64("000000100000000000000000000000000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000000100000000000000000100000000100"); bt.pieces[BLACK]=binstringtouint64("000000000000000100000000000000000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000000100000000100000000000000000100"); bt.pieces[BLACK]=binstringtouint64("000000000000000000000000100000000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000000100000000100000000100000000000"); bt.pieces[BLACK]=binstringtouint64("000000000000000000000000000000000100");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000000000000000010000000010000000010"); bt.pieces[BLACK]=binstringtouint64("000000010000000000000000000000000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000000010000000000000000010000000010"); bt.pieces[BLACK]=binstringtouint64("000000000000000010000000000000000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000000010000000010000000000000000010"); bt.pieces[BLACK]=binstringtouint64("000000000000000000000000010000000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000000010000000010000000010000000000"); bt.pieces[BLACK]=binstringtouint64("000000000000000000000000000000000010");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000000000000000001000000001000000001"); bt.pieces[BLACK]=binstringtouint64("000000001000000000000000000000000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000000001000000000000000001000000001"); bt.pieces[BLACK]=binstringtouint64("000000000000000001000000000000000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000000001000000001000000000000000001"); bt.pieces[BLACK]=binstringtouint64("000000000000000000000000001000000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000000001000000001000000001000000000"); bt.pieces[BLACK]=binstringtouint64("000000000000000000000000000000000001");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000000000010000000001000000000100000"); bt.pieces[BLACK]=binstringtouint64("100000000000000000000000000000000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("100000000000000000001000000000100000"); bt.pieces[BLACK]=binstringtouint64("000000000010000000000000000000000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("100000000010000000000000000000100000"); bt.pieces[BLACK]=binstringtouint64("000000000000000000001000000000000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("100000000010000000001000000000000000"); bt.pieces[BLACK]=binstringtouint64("000000000000000000000000000000100000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000000000001000000000100000000010000"); bt.pieces[BLACK]=binstringtouint64("010000000000000000000000000000000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("010000000000000000000100000000010000"); bt.pieces[BLACK]=binstringtouint64("000000000001000000000000000000000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("010000000001000000000000000000010000"); bt.pieces[BLACK]=binstringtouint64("000000000000000000000100000000000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("010000000001000000000100000000000000"); bt.pieces[BLACK]=binstringtouint64("000000000000000000000000000000010000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000000000000100000000010000000001000"); bt.pieces[BLACK]=binstringtouint64("001000000000000000000000000000000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("001000000000000000000010000000001000"); bt.pieces[BLACK]=binstringtouint64("000000000000100000000000000000000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("001000000000100000000000000000001000"); bt.pieces[BLACK]=binstringtouint64("000000000000000000000010000000000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("001000000000100000000010000000000000"); bt.pieces[BLACK]=binstringtouint64("000000000000000000000000000000001000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000000000000010000000001000000000100"); bt.pieces[BLACK]=binstringtouint64("000100000000000000000000000000000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000100000000000000000001000000000100"); bt.pieces[BLACK]=binstringtouint64("000000000000010000000000000000000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000100000000010000000000000000000100"); bt.pieces[BLACK]=binstringtouint64("000000000000000000000001000000000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000100000000010000000001000000000000"); bt.pieces[BLACK]=binstringtouint64("000000000000000000000000000000000100");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000000000000001000000000100000000010"); bt.pieces[BLACK]=binstringtouint64("000010000000000000000000000000000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000010000000000000000000100000000010"); bt.pieces[BLACK]=binstringtouint64("000000000000001000000000000000000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000010000000001000000000000000000010"); bt.pieces[BLACK]=binstringtouint64("000000000000000000000000100000000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000010000000001000000000100000000000"); bt.pieces[BLACK]=binstringtouint64("000000000000000000000000000000000010");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000000000000000100000000010000000001"); bt.pieces[BLACK]=binstringtouint64("000001000000000000000000000000000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000001000000000000000000010000000001"); bt.pieces[BLACK]=binstringtouint64("000000000000000100000000000000000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000001000000000100000000000000000001"); bt.pieces[BLACK]=binstringtouint64("000000000000000000000000010000000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000001000000000100000000010000000000"); bt.pieces[BLACK]=binstringtouint64("000000000000000000000000000000000001");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000000000000000010000000100000001000"); bt.pieces[BLACK]=binstringtouint64("000000001000000000000000000000000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000000001000000000000000100000001000"); bt.pieces[BLACK]=binstringtouint64("000000000000000010000000000000000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000000001000000010000000000000001000"); bt.pieces[BLACK]=binstringtouint64("000000000000000000000000100000000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000000001000000010000000100000000000"); bt.pieces[BLACK]=binstringtouint64("000000000000000000000000000000001000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000000000000000100000001000000010000"); bt.pieces[BLACK]=binstringtouint64("000000010000000000000000000000000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000000010000000000000001000000010000"); bt.pieces[BLACK]=binstringtouint64("000000000000000100000000000000000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000000010000000100000000000000010000"); bt.pieces[BLACK]=binstringtouint64("000000000000000000000001000000000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000000010000000100000001000000000000"); bt.pieces[BLACK]=binstringtouint64("000000000000000000000000000000010000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000000000000001000000010000000100000"); bt.pieces[BLACK]=binstringtouint64("000000100000000000000000000000000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000000100000000000000010000000100000"); bt.pieces[BLACK]=binstringtouint64("000000000000001000000000000000000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000000100000001000000000000000100000"); bt.pieces[BLACK]=binstringtouint64("000000000000000000000010000000000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000000100000001000000010000000000000"); bt.pieces[BLACK]=binstringtouint64("000000000000000000000000000000100000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000000000000010000000100000001000000"); bt.pieces[BLACK]=binstringtouint64("000001000000000000000000000000000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000001000000000000000100000001000000"); bt.pieces[BLACK]=binstringtouint64("000000000000010000000000000000000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000001000000010000000000000001000000"); bt.pieces[BLACK]=binstringtouint64("000000000000000000000100000000000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000001000000010000000100000000000000"); bt.pieces[BLACK]=binstringtouint64("000000000000000000000000000001000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000000000000100000001000000010000000"); bt.pieces[BLACK]=binstringtouint64("000010000000000000000000000000000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000010000000000000001000000010000000"); bt.pieces[BLACK]=binstringtouint64("000000000000100000000000000000000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000010000000100000000000000010000000"); bt.pieces[BLACK]=binstringtouint64("000000000000000000001000000000000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000010000000100000001000000000000000"); bt.pieces[BLACK]=binstringtouint64("000000000000000000000000000010000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000000000001000000010000000100000000"); bt.pieces[BLACK]=binstringtouint64("000100000000000000000000000000000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000100000000000000010000000100000000"); bt.pieces[BLACK]=binstringtouint64("000000000001000000000000000000000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000100000001000000000000000100000000"); bt.pieces[BLACK]=binstringtouint64("000000000000000000010000000000000000");std::cout<<bt;
	bt.pieces[WHITE]=binstringtouint64("000100000001000000010000000000000000"); bt.pieces[BLACK]=binstringtouint64("000000000000000000000000000100000000");std::cout<<bt;



}

int main(int argc, char* argv[]){
	print_all_threats();
	return 0;

	board bt; 
	Motif specific1; 
	specific1.add(binstringtouint64("110100000000000000000000000000000000"));
	bt.pieces[BLACK]=binstringtouint64("111100000100001001110001000000000000");
	bt.pieces[WHITE]=binstringtouint64("001011010010001000000000000000000001");
	std::cout<<"Should be true:" <<specific1.exists(bt,BLACK)<<std::endl;


	Motif winNextMove; 
	winNextMove.add(binstringtouint64("110100000000000000000000000000000000"),binstringtouint64("001000000000000000000000000000000000"));


	bt.pieces[BLACK]=binstringtouint64("110100000100001001110001000000000000");
	bt.pieces[WHITE]=binstringtouint64("001011010010001000000000000000000001");
	std::cout<<"No empty space. Should be false " <<winNextMove.exists(bt,BLACK)<<std::endl;

	bt.pieces[BLACK]=binstringtouint64("100100000100001001110001000000000000");
	bt.pieces[WHITE]=binstringtouint64("000000010010001000000000000000000001");
	std::cout<<"No pattern. Should be false " <<winNextMove.exists(bt,BLACK)<<std::endl;


	bt.pieces[BLACK]=binstringtouint64("110100000100001001110001000000000000");
	bt.pieces[WHITE]=binstringtouint64("000010110010001000001010000000000001");
	std::cout<<"Should be TRUE" <<winNextMove.exists(bt,BLACK)<<std::endl;

	bt.pieces[BLACK]=binstringtouint64("110100000000000000000000000000000000");
	bt.pieces[WHITE]=binstringtouint64("000000000000000000000000000000000000");
	match_t mm = winNextMove.getMatches(bt,BLACK)[0];
	std::cout<<uint64tobinstring(mm.first)<<","<<uint64tobinstring(mm.second)<<std::endl;

	int mtile = uint64totile(mm.second);
	std::cout<<mtile<<std::endl;
	std::cout<<binstringtouint64("001000000000000000000000000000000000")<<std::endl;
	std::cout<<binstringtouint64("010000000000000000000000000000000000")<<std::endl;
	std::cout<<binstringtouint64("000100000000000000000000000000000000")<<std::endl;
	
	std::cout<<"making move: "<<mtile<<std::endl;
	std::cout<<"board before:" <<bt<<std::endl;
	board bt1=bt+zet(mm.second,BLACK,0);
	std::cout<<"board after:"<<bt1<<std::endl;


	Motif m4diag;
	m4diag.add(binstringtouint64("000000001000000000000000001000000001"),binstringtouint64("000000000000000001000000000000000000"));
	bt.pieces[BLACK]=binstringtouint64("000000000000000000000000000000000000");
	bt.pieces[WHITE]=binstringtouint64("000000001000000000000000001000000001");
	std::cout<<bt<<std::endl;
	bt1=bt+zet(m4diag.getMatches(bt,WHITE)[0].second,WHITE,WHITE);
	std::cout<<bt1<<std::endl;




	Motif m4inarow;
	m4inarow.add(binstringtouint64("111100000000000000000000000000000000"));
	m4inarow.add(binstringtouint64("011110000000000000000000000000000000"));
	m4inarow.add(binstringtouint64("001111000000000000000000000000000000"));
	m4inarow.add(binstringtouint64("000111100000000000000000000000000000"));
	m4inarow.add(binstringtouint64("000011110000000000000000000000000000"));
	m4inarow.add(binstringtouint64("000001111000000000000000000000000000"));
	m4inarow.add(binstringtouint64("000000000111100000000000000000000000"));
	m4inarow.add(binstringtouint64("000000000011110000000000000000000000"));
	m4inarow.add(binstringtouint64("000000000001111000000000000000000000"));
	m4inarow.add(binstringtouint64("000000000000111100000000000000000000"));
	m4inarow.add(binstringtouint64("000000000000011110000000000000000000"));
	m4inarow.add(binstringtouint64("000000000000001111000000000000000000"));
	m4inarow.add(binstringtouint64("000000000000000000111100000000000000"));
	m4inarow.add(binstringtouint64("000000000000000000011110000000000000"));
	m4inarow.add(binstringtouint64("000000000000000000001111000000000000"));
	m4inarow.add(binstringtouint64("000000000000000000000111100000000000"));
	m4inarow.add(binstringtouint64("000000000000000000000011110000000000"));
	m4inarow.add(binstringtouint64("000000000000000000000001111000000000"));
	m4inarow.add(binstringtouint64("000000000000000000000000000111100000"));
	m4inarow.add(binstringtouint64("000000000000000000000000000011110000"));
	m4inarow.add(binstringtouint64("000000000000000000000000000001111000"));
	m4inarow.add(binstringtouint64("000000000000000000000000000000111100"));
	m4inarow.add(binstringtouint64("000000000000000000000000000000011110"));
	m4inarow.add(binstringtouint64("000000000000000000000000000000001111"));
	m4inarow.add(binstringtouint64("100000000100000000100000000100000000"));
	m4inarow.add(binstringtouint64("010000000010000000010000000010000000"));
	m4inarow.add(binstringtouint64("001000000001000000001000000001000000"));
	m4inarow.add(binstringtouint64("000100000000100000000100000000100000"));
	m4inarow.add(binstringtouint64("000010000000010000000010000000010000"));
	m4inarow.add(binstringtouint64("000001000000001000000001000000001000"));
	m4inarow.add(binstringtouint64("000000100000000100000000100000000100"));
	m4inarow.add(binstringtouint64("000000010000000010000000010000000010"));
	m4inarow.add(binstringtouint64("000000001000000001000000001000000001"));

	bt.pieces[BLACK]=binstringtouint64("000000000000000000000000000000000000");
	bt.pieces[WHITE]=binstringtouint64("111100010010001000000000000000000001");


	std::cout<<"Should be true (1):"<<m4inarow.exists(bt,WHITE)<<std::endl;
	std::cout<<"Should be false "<<m4inarow.exists(bt,BLACK)<<std::endl;
	bt.pieces[WHITE]=binstringtouint64("11110000010000000010000000010000000");


	std::cout<<"Should be true (2)"<<m4inarow.exists(bt,WHITE)<<std::endl;
	uint64 first_row = binstringtouint64("111100000000000000000000000000000000");
	std::cout<<"Should be false "<<(bt.pieces[BLACK]&first_row)<<std::endl;
	std::cout<<"Should be true "<<(bt.pieces[WHITE]&first_row)<<std::endl;
	uint64 blank = binstringtouint64("000000000000000000000000000000000000");

	Motif m;
	m.add(first_row,blank);
	std::cout<<"should be true:"<<m.exists(bt,WHITE)<<std::endl;

Motif m1;
	m1.add(first_row);
	std::cout<<"should be true:"<<m.exists(bt,WHITE)<<std::endl;




	std::cout<<"uint64tobinstring(0x0000000000001f8ULL)="<<uint64tobinstring(0x0000000000001f8ULL)<<std::endl;
	std::cout<<"uint64tobinstring(00x00001fe3fc7f8ffULL)="<<uint64tobinstring(0x00001fe3fc7f8ffULL)<<std::endl;


	board b;
	std::cout<<b;
	int row=1;
	int col=1;
	uint64 i = rctouint64(row, col);
	int tile=uint64totile(i);
	std::cout<<"the tile of "<<i<<" is "<<tile<<std::endl;
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

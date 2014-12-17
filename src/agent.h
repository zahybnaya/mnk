#ifndef AGENT_H
#define AGENT_H

#include "common.h"
#include <string.h>
#include <vector>
#include <map>
#include "board.h"

/**
Agent
  |
  |--> TreeAgent
	  |->UCTAgent
	  |->BFSAgent
	  |->ExsustiveAgent
  |->MyopicAgent
**/
class Agent {
	public:
		Agent(){}
		virtual ~Agent(){}
		/**
		 * Retuns the move estimates of all available moves from 
		 * board b and for player 
		 * */
		virtual std::vector<zet> solve(board& b,bool player)=0;
		/**
		 * A string describing this agent
		 * */
		const virtual std::string get_name()=0;
		const std::string get_agent_file();
		/**
		 * Returns the move of the player on this board
		 * */
		zet play(board& b,bool player);
		inline void set_properties(properties p){
			this->m_properties=p;
		}
		void set_agent_file(std::string);
	protected:
		/**
		 * Obtain a list of values
		 * */
		std::vector<double> get_array_property(std::string);

		/**
		 * Obtain the int value of a property
		 * */
		int get_int_property(std::string);
		/**
		 * Obtain the double value of a property
		 * */
		double get_double_property(std::string);
		/**
		 * Returns a random move
		 * */
		uint64 select_random_move(std::vector<zet> &moves);
	private:
		/**
		 * A table to store arbitrary properties 
		 * for that agent
		 * */
		properties m_properties;
		/**
		 * A file from which the agent had built
		 * */
		std::string agent_file;
};


#endif /* end of include guard: AGENT_H */

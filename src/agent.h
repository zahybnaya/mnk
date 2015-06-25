#ifndef AGENT_H
#define AGENT_H

#include "common.h"
#include <string.h>
#include <vector>
#include <map>
#include "board.h"
#include <random>

/**
Agent
  |
  |--> TreeAgent
	  |->UCTAgent
	  |->BFSAgent
	  |->ExshustiveAgent
  |->MyopicAgent
**/
class Agent {
	public:
		Agent(){}
		virtual ~Agent(){}
		
		/**
		 * initializtion after properties are set, etc.
		 * */
		virtual void init();
		/**
		 * Retuns the move estimates of all available moves from 
		 * board b and for player 
		 * */
		virtual std::vector<zet> solve(board& b,bool player)=0;

		/**
		 * Returns the move of the player on this board
		 * */
		virtual zet play(board& b,bool player);
		/**
		 * A string describing this agent
		 * */
		virtual std::string get_name() const =0;
		const std::string get_agent_file();
		inline void set_properties(properties p){
			this->m_properties=p;
		}
		void set_agent_file(std::string);
		/**
		 * lapse_rate is the percentage of times that a random
		 * move is executed
		 * */
		double get_lapse_rate() ;

		/**
		 * What color is this agent playing
		 * */
		inline bool get_playing_color() {return playing_color;}

		/***
		 * Procedure for anything that should be done before 
		 * any solution
		 * */
		virtual void pre_solution(){}

		/***
		 * Procedure for anything that should be done after 
		 * any solution
		 * */
		virtual void post_solution(){}


	protected:

		/**
		 * Obtain a list of values
		 * */
		std::vector<double> get_array_property(std::string);
		/**
		 * Obtain the int value of a property
		 * */
		int get_int_property(std::string) ;
		/**
		 * Obtain the double value of a property
		 * */
		double get_double_property(std::string) ;
		/**
		 * Returns a random move
		 * */
		uint64 select_random_move(std::vector<zet> &moves);

		inline mt19937_64& get_generator() {return generator;}
		/**
		 * probablity to perform a random move
		 * */
		std::bernoulli_distribution lapse;
		/**
		 * Color of agent
		 * */
		bool playing_color;
	private:
		
		/**
		 * are values stored in a negamax tree
		 * */
		virtual bool is_negamax()=0;

		/**
		 * A table to store arbitrary properties 
		 * for that agent
		 * */
		properties m_properties;
		/**
		 * A file from which the agent had built
		 * */
		std::string agent_file;
		/**
		 * Random generator
		 * */
		std::mt19937_64 generator;
		
};


#endif /* end of include guard: AGENT_H */

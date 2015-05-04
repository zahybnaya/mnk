#ifndef COMMON_H
#define COMMON_H
#include <map>
#include <string>
#include <vector>
#include <fstream>
#include "log.h"

typedef uint64_t uint64;
typedef std::map<std::string,std::string> properties;

struct Agent_params {
	std::string agent_file;	
	std::string implementation;	
	properties m_properties;
};

struct Source {
	Source(std::string st, std::string ag):state_file(st),agent_description_file(ag){}
	std::string state_file;
	std::string agent_description_file;
};

enum DISTRIBUTION {GEOMETRIC=0,BERNOULLI=1};


inline std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}


inline std::pair<std::string,std::string> split_pair(const std::string &s, char delim) {
	std::pair<std::string,std::string> p;
	std::stringstream ss(s);
	std::string item;
	std::getline(ss, item, delim);
	p.first=item;
	std::getline(ss, item, delim);
	p.second=item;
	return p;
}

/***
 * Read the agent parameters from a file
 * */
 inline Agent_params read_agent_params(std::string agent_description_filename) {
	FILE_LOG(logDEBUG)<< "Reading agent params from " << agent_description_filename<< std::endl;
	std::ifstream agent_description_file;
	agent_description_file.open(agent_description_filename);
	std::string line;
	Agent_params ag_par;
	while (std::getline(agent_description_file, line))
	{
		if (line.find_first_not_of(' ') == std::string::npos){
			continue;
		}
		if(line.compare(0, 1 , "#") == 0) {
			continue;
		}
		std::pair<std::string,std::string> p= split_pair(line,'=');
		FILE_LOG(logDEBUG) << p.first<<":"<<p.second << std::endl;
		ag_par.m_properties[p.first]=p.second;
	}
	ag_par.implementation = ag_par.m_properties["implementation"];
	ag_par.agent_file = agent_description_filename;
	return ag_par;
}


/**
 * Check if this param is for concretization
 */
inline bool is_concrete_param(std::string val){
	return (val.compare(0, 1 , "?") == 0);
}
/**
 *  Get the right value from the parameter array
 * */
inline std::string assigned_val(std::string val, double* paramptr){
	size_t start_range = val.find("{");
	if (start_range == std::string::npos){
		FILE_LOG(logERROR) << "Wrong format for concerete "<<val<<std::endl;
		exit(-1);
	}
	int ind = std::stoi(val.substr(1,start_range-1));
	double v = paramptr[ind];
	return std::to_string(v);
}

/***
 * Look for the values of ?? and fills it with the relevant data
 * Suggestion: ?<index>{lower,upper}
 * */
inline void concrete(Agent_params& ap,double* paramptr){
	FILE_LOG(logDEBUG) << "starting concrete " << std::endl;
	for (properties::iterator i = ap.m_properties.begin(); i != ap.m_properties.end(); ++i) {
		if(is_concrete_param(i->second)){
			FILE_LOG(logDEBUG) << "need to concrete: ["<<i->first << "] with value:" << i->second<< std::endl; 
			ap.m_properties[i->first]=assigned_val(i->second,paramptr);
			FILE_LOG(logDEBUG) << " concrete-assgined ("<< ap.m_properties[i->first]<<")"<< std::endl;
	       	}
	}
}

#endif /* end of include guard: COMMON_H */


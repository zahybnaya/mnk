#ifndef COMMON_H
#define COMMON_H
#include <map>
#include <string.h>
#include <vector>
#include <fstream>
#include <iostream>
#include <math.h>
#include "log.h"

typedef uint64_t uint64;
typedef std::map<std::string,std::string> properties;
bool is_debug(int argc, const char* argv[]);
double sigmoid(double x);

inline double sigmoid(double x){
	return 1/(1+exp(-x));
}


inline void set_debug(int argc, const char* argv[]){
	if (is_debug(argc, argv)){
		FILELog::ReportingLevel() = FILELog::FromString("DEBUG");
	} else {
		FILELog::ReportingLevel() = FILELog::FromString("ERROR");
	}
}

inline bool is_debug(int argc, const char* argv[]){
	for(int i=0;i<argc;++i){
		if (strcmp(argv[i],"-debug")==0) {
			return	true;
		}
	}
	return false;
}


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
#endif /* end of include guard: COMMON_H */


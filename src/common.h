#ifndef COMMON_H
#define COMMON_H
#include <map>
#include <string>
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


#endif /* end of include guard: COMMON_H */


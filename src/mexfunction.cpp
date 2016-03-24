#include "mex.h"
#include "Gomoku.cpp"
#include <string>
#include <sstream>
#include <cassert>
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
	assert(v);
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

int main(int argc, const char *argv[])
{
	FILELog::ReportingLevel() = FILELog::FromString("ERROR");
	char* agent_file = "../agents/constmoveagent";
	char* data_file  = "../data/37subjects.csvSUB0.csv";
	int player=0; 
	double  params [] = {0.1,0.2,0,1,1,1,1,1,3,4};
	double* paramptr= params;
	data_struct dat = load_data(dat,std::string(data_file)); 
	std::string times_file=dat.get_times_file(data_file);
	Agent_params ap = read_agent_params(std::string(agent_file));
	concrete(ap,paramptr);
	for (properties::iterator i = ap.m_properties.begin(); i != ap.m_properties.end(); ++i) {
		assert(!is_concrete_param(i->second));
	}
	char output[]="Output/out.txt";
	std::cout<<compute_loglik_agent(ap,dat,false,player,/*not-used*/0,times_file,output);
	return 0;
}

void mexFunction(int /*nlhs*/, mxArray *plhs[],int /*nrhs*/, const mxArray *prhs[]){
	FILELog::ReportingLevel() = FILELog::FromString("ERROR");
	//FILELog::ReportingLevel() = FILELog::FromString("DEBUG");
	FILE_LOG(logDEBUG) << " Starting mexFunction" << std::endl;
	double* playerptr=mxGetPr(prhs[0]);
	FILE_LOG(logDEBUG) << "playerptr " << std::endl;
	char* agent_file =mxArrayToString(prhs[1]);
	FILE_LOG(logDEBUG) << "2 " << std::endl;
	char* data_file =mxArrayToString(prhs[2]);
	FILE_LOG(logDEBUG) << "3 " << std::endl;
	double* paramptr=mxGetPr(prhs[3]);
	FILE_LOG(logDEBUG) << "4 " << std::endl;
	int player=((int) (*playerptr)); 
	FILE_LOG(logDEBUG) << "5 " << std::endl;
	//std::ostringstream s,s2; 
	//s << "/home/zb9/mnk/agents/bfsagent" << player;
	//std::string agent_file(agent_file);
	//s2 << "/home/zb9/mnk/data/37subjects.csvSUB" << player << "train.csv";
	//std::string data_file (std::string(data_file)); 
	FILE_LOG(logDEBUG) << "Loading from data file: "<< data_file << std::endl;
	data_struct dat;
        dat = load_data(dat,std::string(data_file)); //TODO: Filter by subject (here it's player)
	FILE_LOG(logDEBUG) << "Getting times file " << std::endl;
	std::string times_file=dat.get_times_file(data_file);
	FILE_LOG(logDEBUG) << "7 " << std::endl;
	Agent_params ap = read_agent_params(std::string(agent_file));
	FILE_LOG(logDEBUG) << " Freeing memory "<<agent_file << std::endl;
	mxFree(agent_file);
	mxFree(data_file);
	FILE_LOG(logDEBUG) << " Starting concrete process for "<<agent_file << std::endl;
	concrete(ap,paramptr);
	for (properties::iterator i = ap.m_properties.begin(); i != ap.m_properties.end(); ++i) {
		assert(!is_concrete_param(i->second));
	}
	char output[]="Output/out.txt";

	FILE_LOG(logDEBUG) << " Calling compute_loglik_agent" << std::endl;
	plhs[0] = mxCreateDoubleScalar(compute_loglik_agent(ap,dat,false,player,/*not-used*/0,times_file,output));
	FILE_LOG(logDEBUG) << " Returning from mexFunction" << std::endl;
}




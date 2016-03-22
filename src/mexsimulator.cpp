#include "Gomoku.cpp"
#include <string>
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
	//FILE_LOG(logDEBUG) << "starting concrete " << std::endl;
	for (properties::iterator i = ap.m_properties.begin(); i != ap.m_properties.end(); ++i) {
		if(is_concrete_param(i->second)){
			//FILE_LOG(logDEBUG) << "need to concrete: ["<<i->first << "] with value:" << i->second<< std::endl; 
			ap.m_properties[i->first]=assigned_val(i->second,paramptr);
			//FILE_LOG(logDEBUG) << " concrete-assgined ("<< ap.m_properties[i->first]<<")"<< std::endl;
	       	}

	}
}



void mexFunction(std::string agent_file, std::string data_file, double* paramptr, int player){
	//FILE_LOG(logDEBUG) << " Starting mexFunction" << std::endl;
	data_struct dat;
       	dat = load_data(dat,data_file); //TODO: Filter by subject (here it's player)
	std::string times_file=dat.get_times_file(data_file);
	Agent_params ap = read_agent_params(agent_file);
	//FILE_LOG(logDEBUG) << " Starting concrete process for "<<agent_file << std::endl;
	concrete(ap,paramptr);
	for (properties::iterator i = ap.m_properties.begin(); i != ap.m_properties.end(); ++i) {
		assert(!is_concrete_param(i->second));
	}
	char output[]="Output/out.txt";
	compute_loglik_agent(ap,dat,true,player,ALL,times_file,output);
}


int get_subject(int argc, const char* argv[]){

	for(int i=0;i<argc;++i){
		if (strcmp(argv[i],"-subject")==0) {
			return	atoi(argv[++i]);
		}
	}
	return -1;
}



int main(int argc, char* argv[]){
	FILELog::ReportingLevel() = FILELog::FromString("ERROR");
	const int iters = 5;
	std::string agent_file(argv[1]); 
	std::string data_file(argv[2]); 

	//std::string agent_file("../agents/bfsagent"); 
	//std::string data_file("../data/37subjects.csvSUB0test.csv"); 
	double params [] = {3,0.01,0.31,0.019,1,2,1,0.042,1,0.2,4.841,2.5,15,1};
	for (int i=0 ; i< iters; ++i ){
		mexFunction(agent_file, data_file, params, 0);
		std::cout<<i<<"/"<<iters<<std::endl;
	}
}






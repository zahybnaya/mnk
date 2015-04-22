#include "mex.h"
#include "Gomoku.cpp"
#include <string>
#include <cassert>
	
void mexFunction(int /*nlhs*/, mxArray *plhs[],int /*nrhs*/, const mxArray *prhs[]){
	FILELog::ReportingLevel() = FILELog::FromString("ERROR");
	FILE_LOG(logDEBUG) << " Starting mexFunction" << std::endl;
	double* playerptr=mxGetPr(prhs[0]);
	//int player=((int) (*playerptr+0.5)); 
	int player=((int) (*playerptr)); 
	char* agent_file =mxArrayToString(prhs[1]);
	char* data_file =mxArrayToString(prhs[2]);
	data_struct dat;
       	dat = load_data(dat,std::string(data_file)); //TODO: Filter by subject (here it's player)
	double* paramptr=mxGetPr(prhs[3]);
	Agent_params ap = read_agent_params(std::string(agent_file));
	FILE_LOG(logDEBUG) << " Starting concrete process for "<<agent_file << std::endl;
	concrete(ap,paramptr);
	for (properties::iterator i = ap.m_properties.begin(); i != ap.m_properties.end(); ++i) {
		assert(!is_concrete_param(i->second));
	}
	char* output="Output/out.txt";
	plhs[0] = mxCreateDoubleScalar(compute_loglik_agent(ap,dat,true,player,ALL,NULL,output));
}




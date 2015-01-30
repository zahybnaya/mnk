#include "mex.h"
#include "Gomoku.cpp"
#include <string>
	
void mexFunction(int nlhs, mxArray *plhs[],int nrhs, const mxArray *prhs[]){
	//heuristic h;
	data_struct dat;
	unsigned int seed=unsigned(time(0));
	mt19937_64 global_generator;
	double* playerptr=mxGetPr(prhs[0]);
	int player=((int) (*playerptr+0.5)); 
	char* agent_file =mxArrayToString(prhs[1]);
	double* paramptr=mxGetPr(prhs[2]);
	global_generator.seed(seed);
	h.seed_generator(global_generator);
	//h.get_params_from_matlab(paramptr);
	Agent_params ap = read_agent_params(std::string(agent_file));
	FILE_LOG(logDEBUG) << " Starting concrete process for "<<agent_file << std::endl;
	concrete(ap,paramptr);
	plhs[0] = mxCreateDoubleScalar(compute_loglik_agent_stub(ap,dat,true,player,TEST,NULL,"Output/out.txt"));
}




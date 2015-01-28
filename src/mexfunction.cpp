#include "mex.h"
#include "Gomoku.cpp"
	
void mexFunction(int nlhs, mxArray *plhs[],int nrhs, const mxArray *prhs[]){
	heuristic h;
	data_struct dat;
	unsigned int seed=unsigned(time(0));
	mt19937_64 global_generator;
	double* playerptr=mxGetPr(prhs[0]);
	int player=((int) (*playerptr+0.5)); double* paramptr=mxGetPr(prhs[1]);
	global_generator.seed(seed);
	h.seed_generator(global_generator);
	h.get_params_from_matlab(paramptr);
	plhs[0] = mxCreateDoubleScalar(compute_loglik(h,dat,true,player,TEST,"times.txt","Output/out.txt"));
}




#include "Gomoku.cpp"

int main(int argc, const char* argv[]){
	FILELog::ReportingLevel() = FILELog::FromString("ERROR");
	Source src=prepeare_source(argc, argv);
	heuristic h;
	superheuristic s;
	data_struct dat; 
       	dat = load_data(dat,src.state_file);
	unsigned int seed=unsigned(time(0));
	mt19937_64 global_generator;
	board b;
	zet m;
	std::cout<<"seed = "<<seed<<std::endl;
	global_generator.seed(seed);
	h.seed_generator(global_generator);
	Agent_params ag = read_agent_params(src.agent_description_file);
	for(unsigned int i=0;i<dat.Nplayers;i++)
		std::cout<<i<<"\t"<<compute_loglik_agent(ag,dat,false,i,ALL,NULL,NULL)<<std::endl;
	return 0;
}



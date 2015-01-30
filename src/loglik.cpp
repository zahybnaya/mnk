#include "Gomoku.cpp"

int main(int argc, const char* argv[]){
	if (argc>1)
		if(strcmp(argv[1],"data")==0){
			return generate_date();
		}
	FILELog::ReportingLevel() = FILELog::FromString("DEBUG");
	Source src=prepeare_source(argc, argv);
	heuristic h;
	superheuristic s;
	data_struct dat;
	unsigned int seed=unsigned(time(0));
	mt19937_64 global_generator;
	char filename[128];
	ofstream output;
	board b;
	zet m;
	cout<<"seed = "<<seed<<endl;
	global_generator.seed(seed);
	h.seed_generator(global_generator);
	Agent_params ag = read_agent_params(src.agent_description_file);
	for(int i=0;i<dat.Nplayers;i++)
		std::cout<<dat.player_name[i]<<"\t"<<compute_loglik_agent(ag,dat,false,i,ALL,NULL,NULL)<<std::endl;
	return 0;
}


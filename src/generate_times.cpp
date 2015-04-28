#include "Gomoku.cpp"

int get_repetitions(int argc, const char* argv[]){

	for(int i=0;i<argc;++i){
		if (strcmp(argv[i],"-rep")==0) {
			return	atoi(argv[++i]);
		}
	}
	return 10;
}



int main(int argc, const char* argv[]){
	FILELog::ReportingLevel() = FILELog::FromString("ERROR");
	Source src=prepeare_source(argc, argv);
	int reps = get_repetitions(argc,argv);
	heuristic h;
	superheuristic s;
	data_struct dat;
       	dat = load_data(dat,src.state_file);
	unsigned int seed=unsigned(time(0));
	mt19937_64 global_generator;
	board b;
	zet m;
	global_generator.seed(seed);
	h.seed_generator(global_generator);
	Agent_params ag = read_agent_params(src.agent_description_file);
	for (int i = 0; i <reps; i++) {
		compute_loglik_agent(ag,dat,true,-1,ALL,NULL,NULL);
	}
	return 0;
}


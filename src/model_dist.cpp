#include "Gomoku.cpp"

int get_times_per_model(int argc, const char* argv[]){
	for(int i=0;i<argc;++i){
		if (strcmp(argv[i],"-N")==0) {
			return	atoi(argv[++i]);
		}
	}
	return -1;
}



int main(int argc, const char *argv[])
{
	set_debug(argc, argv);
	Source src=prepeare_source(argc, argv);
	int times = get_times_per_model(argc,argv);
	data_struct dat; 
       	dat = load_data(dat,src.state_file);
	unsigned int seed=unsigned(time(0));
	std::cout<<"seed = "<<seed<<std::endl;
	mt19937_64 global_generator;
	global_generator.seed(seed);
	Agent_params ag = read_agent_params(src.agent_description_file);
	compute_model_dist(ag,&dat,times);
	return 0;
}

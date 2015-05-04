#include "Gomoku.cpp"


int get_subject(int argc, const char* argv[]){

	for(int i=0;i<argc;++i){
		if (strcmp(argv[i],"-subject")==0) {
			return	atoi(argv[++i]);
		}
	}
	return -1;
}


int main(int argc, const char* argv[]){
	FILELog::ReportingLevel() = FILELog::FromString("ERROR");
	Source src=prepeare_source(argc, argv);
	int subject = get_subject(argc,argv);
	heuristic h;
	superheuristic s;
	data_struct dat; 
       	dat = load_data(dat,src.state_file);
	std::string times_file=dat.get_times_file(src.state_file);
	std::cout<<"times_file:"<<times_file<<std::endl;
	//unsigned int seed=unsigned(time(0));
	unsigned int seed=0;
	std::cout<<"seed = "<<seed<<std::endl;
	mt19937_64 global_generator;
	global_generator.seed(seed);
	h.seed_generator(global_generator);
	Agent_params ag = read_agent_params(src.agent_description_file);
	if(subject!=-1){
		std::cout<<subject<<"\t"<<compute_loglik_agent(ag,dat,false,subject,ALL,times_file,NULL)<<std::endl;
		return 0;
	}
	for (std::set<int>::iterator i = dat.distinct_players.begin(); i != dat.distinct_players.end();++i){
		std::cout<<*i<<"\t"<<compute_loglik_agent(ag,dat,false,*i,ALL,times_file,NULL)<<std::endl;
	}
	return 0;
}



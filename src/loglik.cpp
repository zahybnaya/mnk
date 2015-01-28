#include "Gomoku.cpp"

int main(int argc, const char* argv[]){
	if (argc>1)
		if(strcmp(argv[1],"data")==0){
			return generate_date();
		}
	FILELog::ReportingLevel() = FILELog::FromString("ERROR");
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
	//sprintf(filename,"loglik_boards%i.txt",subject);
	//output.open(filename,ios::out);
	global_generator.seed(seed);
	h.seed_generator(global_generator);
	for(int i=0;i<dat.Nplayers;i++)
		cout<<dat.player_name[i]<<"\t"<<compute_loglik_agent(h,src.agent_description_file,dat,false,i,ALL,NULL,NULL)<<endl;
	//cout<<dat.player_name[i]<<"\t"<<compute_loglik(h,src.agent_description_file,dat,false,i,ALL,NULL,NULL)<<endl;
	//output.close();
	return 0;
}


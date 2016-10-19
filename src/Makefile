
#####
# Build different executables.
#
# states: Runs agents on a list of states
#
# tournament: Runs black vs. white games 
#
# loglik: calculate the loglikelihood
#
# model-fitting: calculates model parameters
#
#####
CCFLAGS=-g -std=c++11 -pthread  -Wall 
#-DNDEBUG
#LDFLAGS=-pg
LDFLAGS=

load-modules:
	module load gcc/4.9.2

states: aigames.cpp pseudorandomplayout.cpp pseudorandomplayout.h  randomplayout.h randomplayout.cpp heuristic.cpp heuristic.h agent_builder.h features.cpp agent.h agent.cpp uctagent.cpp uctagent.h states.cpp agent_builder.h agent_builder.cpp treeagent.h treeagent.cpp myopicagent.h myopicagent.cpp bfsagent.cpp bfsagent.h data_struct.h data_struct.cpp mindifftreeagent.cpp mindifftreeagent.h fixeddepthtreeagent.h fixeddepthtreeagent.cpp heuristicagent.h heuristicagent.cpp
	g++ $(CCFLAGS) aigames.cpp agent.cpp uctagent.cpp pseudorandomplayout.cpp randomplayout.cpp features.cpp  heuristic.cpp myopicagent.cpp bfsagent.cpp treeagent.cpp  agent_builder.cpp states.cpp data_struct.cpp mindifftreeagent.cpp fixeddepthtreeagent.cpp heuristicagent.cpp dummy_agent.cpp geometricrandom.cpp defaultagent.cpp consistentmoveagent.cpp myopicpolicyplayout.cpp -ostates 

tournament: tournament.cpp heuristic.cpp pseudorandomplayout.cpp pseudorandomplayout.h randomplayout.h randomplayout.cpp heuristic.h features.cpp agent_builder.h agent.h agent.cpp uctagent.cpp uctagent.h states.cpp agent_builder.h agent_builder.cpp treeagent.h treeagent.cpp myopicagent.h myopicagent.cpp bfsagent.cpp bfsagent.h
	g++ $(CCFLAGS)  tournament.cpp features.cpp agent.cpp uctagent.cpp heuristic.cpp myopicagent.cpp bfsagent.cpp treeagent.cpp  pseudorandomplayout.cpp randomplayout.cpp agent_builder.cpp states.cpp mindifftreeagent.cpp geometricrandom.cpp data_struct.cpp dummy_agent.cpp -otournament

generate_times: generate_times.cpp Gomoku.cpp board_list.h agent_builder.cpp agent.cpp uctagent.cpp treeagent.cpp features.cpp  data_struct.h data_struct.cpp heuristic.cpp  pseudorandomplayout.cpp pseudorandomplayout.h randomplayout.cpp myopicagent.cpp bfsagent.cpp 
	g++ $(CCFLAGS) generate_times.cpp agent_builder.cpp agent.cpp uctagent.cpp treeagent.cpp features.cpp  data_struct.cpp  heuristic.cpp pseudorandomplayout.cpp randomplayout.cpp myopicagent.cpp bfsagent.cpp -ogenerate_times

model_dist: model_dist.cpp dotexporter.cpp dotexporter.h Gomoku.cpp board_list.h agent_builder.cpp agent.cpp uctagent.cpp heuristicagent.cpp heuristicagent.h treeagent.cpp features.cpp data_struct.h data_struct.cpp heuristic.cpp pseudorandomplayout.cpp pseudorandomplayout.h randomplayout.cpp myopicagent.cpp bfsagent.cpp mindifftreeagent.cpp mindifftreeagent.h geometricrandom.cpp geometricrandom.h playoutpolicy.h myopicpolicyplayout.h myopicpolicyplayout.cpp defaultagent.cpp defaultagent.h consistentmoveagent.h consistentmoveagent.cpp
	g++ $(CCFLAGS) dotexporter.cpp model_dist.cpp heuristicagent.cpp agent_builder.cpp agent.cpp uctagent.cpp treeagent.cpp features.cpp  data_struct.cpp  heuristic.cpp pseudorandomplayout.cpp  randomplayout.cpp myopicagent.cpp bfsagent.cpp mindifftreeagent.cpp geometricrandom.cpp dummy_agent.cpp fixeddepthtreeagent.cpp myopicpolicyplayout.cpp defaultagent.cpp consistentmoveagent.cpp -omodel_dist  $(LDFLAGS)



loglik: uctagentvisits.cpp uctagentvisits.h randomagent.h randomagent.cpp pseudorandomagent.h pseudorandomagent.cpp dotexporter.cpp dotexporter.h loglik.cpp Gomoku.cpp board_list.h agent_builder.cpp agent.cpp uctagent.cpp heuristicagent.cpp heuristicagent.h treeagent.cpp features.cpp data_struct.h data_struct.cpp heuristic.cpp pseudorandomplayout.cpp pseudorandomplayout.h randomplayout.cpp myopicagent.cpp bfsagent.cpp mindifftreeagent.cpp mindifftreeagent.h geometricrandom.cpp geometricrandom.h playoutpolicy.h myopicpolicyplayout.h myopicpolicyplayout.cpp defaultagent.cpp defaultagent.h consistentmoveagent.h consistentmoveagent.cpp
	g++ $(CCFLAGS) uctagentvisits.cpp randomagent.cpp pseudorandomagent.cpp dotexporter.cpp loglik.cpp heuristicagent.cpp agent_builder.cpp agent.cpp uctagent.cpp treeagent.cpp features.cpp  data_struct.cpp  heuristic.cpp  pseudorandomplayout.cpp randomplayout.cpp myopicagent.cpp bfsagent.cpp mindifftreeagent.cpp geometricrandom.cpp dummy_agent.cpp fixeddepthtreeagent.cpp myopicpolicyplayout.cpp defaultagent.cpp consistentmoveagent.cpp -ologlik  $(LDFLAGS)

mexfunction: mexfunction.cpp Gomoku.cpp board_list.h agent_builder.cpp agent.cpp uctagent.cpp treeagent.cpp features.cpp  data_struct.cpp  heuristic.cpp  pseudorandomplayout.cpp pseudorandomplayout.h randomplayout.cpp myopicagent.cpp bfsagent.cpp defaultagent.cpp defaultagent.h
	g++ $(CCFLAGS) mexfunction.cpp agent_builder.cpp agent.cpp uctagent.cpp treeagent.cpp features.cpp  data_struct.cpp  heuristic.cpp pseudorandomplayout.cpp randomplayout.cpp myopicagent.cpp bfsagent.cpp -omexfunction

mexsim:
	g++ $(CCFLAGS) -Wall -Wextra -std=c++11 -O3  -fexpensive-optimizations heuristic.cpp mexfunction.cpp   features.cpp agent.cpp agent_builder.cpp myopicagent.cpp uctagent.cpp treeagent.cpp randomplayout.cpp data_struct.cpp bfsagent.cpp mindifftreeagent.cpp geometricrandom.cpp dummy_agent.cpp fixeddepthtreeagent.cpp myopicpolicyplayout.cpp defaultagent.cpp heuristicagent.cpp consistentmoveagent.cpp -o mexim

modelfitting:
	echo "mex  -f  $$MATLAB_ROOT/bin/mexopts.sh -v -output Gomoku_model CXXFLAGS=\"\\\$$CXXFLAGS -Wall -Wextra -std=c++11 -O3 -fexpensive-optimizations\" heuristic.cpp mexfunction.cpp   features.cpp agent.cpp agent_builder.cpp myopicagent.cpp uctagent.cpp treeagent.cpp pseudorandomplayout.cpp randomplayout.cpp data_struct.cpp bfsagent.cpp mindifftreeagent.cpp geometricrandom.cpp dummy_agent.cpp fixeddepthtreeagent.cpp myopicpolicyplayout.cpp defaultagent.cpp heuristicagent.cpp consistentmoveagent.cpp ; exit" | $$MATLAB_ROOT/bin/matlab -check_malloc -nodisplay


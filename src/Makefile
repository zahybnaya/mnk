
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
FLAGS=-g -std=c++11 -pthread  -Wall

load-modules:
	module load gcc/4.9.2

states: aigames.cpp randomplayout.h randomplayout.cpp heuristic.cpp heuristic.h agent_builder.h features.cpp agent.h agent.cpp uctagent.cpp uctagent.h states.cpp agent_builder.h agent_builder.cpp treeagent.h treeagent.cpp myopicagent.h myopicagent.cpp bfsagent.cpp bfsagent.h data_struct.h data_struct.cpp
	g++ $(FLAGS) aigames.cpp agent.cpp uctagent.cpp randomplayout.cpp features.cpp  heuristic.cpp myopicagent.cpp bfsagent.cpp treeagent.cpp bfs.cpp agent_builder.cpp states.cpp data_struct.cpp -ostates 

tournament: tournament.cpp heuristic.cpp randomplayout.h randomplayout.cpp heuristic.h features.cpp agent_builder.h agent.h agent.cpp uctagent.cpp uctagent.h states.cpp agent_builder.h agent_builder.cpp treeagent.h treeagent.cpp myopicagent.h myopicagent.cpp bfsagent.cpp bfsagent.h
	g++ $(FLAGS)  tournament.cpp features.cpp randomplayout.cpp agent.cpp uctagent.cpp heuristic.cpp myopicagent.cpp bfsagent.cpp treeagent.cpp bfs.cpp randomplayout.cpp agent_builder.cpp states.cpp -otournament


loglik: loglik.cpp Gomoku.cpp board_list.h agent_builder.cpp agent.cpp uctagent.cpp treeagent.cpp features.cpp bfs.cpp data_struct.h data_struct.cpp heuristic.cpp  randomplayout.cpp myopicagent.cpp bfsagent.cpp 
	g++ $(FLAGS) loglik.cpp agent_builder.cpp agent.cpp uctagent.cpp treeagent.cpp features.cpp bfs.cpp data_struct.cpp  heuristic.cpp  randomplayout.cpp myopicagent.cpp bfsagent.cpp -ologlik

mexfunction: mexfunction.cpp Gomoku.cpp board_list.h agent_builder.cpp agent.cpp uctagent.cpp treeagent.cpp features.cpp bfs.cpp data_struct.cpp  heuristic.cpp  randomplayout.cpp myopicagent.cpp bfsagent.cpp 
	g++ $(FLAGS) mexfunction.cpp agent_builder.cpp agent.cpp uctagent.cpp treeagent.cpp features.cpp bfs.cpp data_struct.cpp  heuristic.cpp  randomplayout.cpp myopicagent.cpp bfsagent.cpp -omexfunction


modelfitting:
	echo "mex  -f $$MATLAB_ROOT/bin/mexopts.sh -v -output Gomoku_model CXXFLAGS=\"\\\$$CXXFLAGS -Wall -Wextra -std=c++11 -O3   -fexpensive-optimizations\" heuristic.cpp mexfunction.cpp  bfs.cpp  features.cpp agent.cpp agent_builder.cpp myopicagent.cpp uctagent.cpp treeagent.cpp randomplayout.cpp data_struct.cpp bfsagent.cpp ; exit" | matlab -check_malloc -nodisplay

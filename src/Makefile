
#####
# Build different executables.
#
# states: Runs agents on a list of states
#
# tournament: Runs black vs. white games 
#
# model_fitting: performs fitting 
#
#####

states: aigames.cpp randomplayout.h randomplayout.cpp heuristic.cpp heuristic.h agent_builder.h features.cpp agent.h agent.cpp uctagent.cpp uctagent.h states.cpp agent_builder.h agent_builder.cpp treeagent.h treeagent.cpp myopicagent.h myopicagent.cpp bfsagent.cpp bfsagent.h
	g++ -std=c++11 -pthread aigames.cpp agent.cpp uctagent.cpp randomplayout.cpp features.cpp  heuristic.cpp myopicagent.cpp bfsagent.cpp treeagent.cpp bfs.cpp agent_builder.cpp states.cpp -ostates 

tournament: tournament.cpp heuristic.cpp randomplayout.h randomplayout.cpp heuristic.h features.cpp agent_builder.h agent.h agent.cpp uctagent.cpp uctagent.h states.cpp agent_builder.h agent_builder.cpp treeagent.h treeagent.cpp myopicagent.h myopicagent.cpp bfsagent.cpp bfsagent.h
	g++ -std=c++11 -pthread tournament.cpp features.cpp randomplayout.cpp agent.cpp uctagent.cpp heuristic.cpp myopicagent.cpp bfsagent.cpp treeagent.cpp bfs.cpp agent_builder.cpp states.cpp -otournament


model_fitting: *.cpp
	g++ -std=c++11 -pthread  -O3 Gomoku.cpp features.cpp bfs.cpp data_struct.cpp data.cpp heuristic.cpp  -omodel_fitting



#include "bfsagent.h"


class MinDiffTreeAgent: public BFSAgent {
	public:
		virtual int build_tree(Node* n,int iterations);
		void init();
	private:
		bool is_stop(Node* n, int iteration, int player);
		std::bernoulli_distribution abrupt_stop;
		double get_stop_threshold();
		double get_abrupt_stop_rate();
};

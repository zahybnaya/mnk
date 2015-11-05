#include "bfsagent.h"


class MinDiffTreeAgent: public BFSAgent {
	public:
		void init();
		void pre_solution();
	private:
		int get_convergence_times();
		double get_stop_decrease_rate();
		bool is_stop(Node* n);
		std::bernoulli_distribution abrupt_stop;
		double get_stop_threshold();
		double get_abrupt_stop_rate();
		//double last_ratio;
		int persistent_ratio_times;
};

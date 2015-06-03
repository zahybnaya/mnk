#include "bfsagent.h"


class MinDiffTreeAgent: public BFSAgent {
	public:
		virtual int build_tree(Node* n,int iterations);
	private:
		bool is_stop(Node* n, int iteration, int player);

};

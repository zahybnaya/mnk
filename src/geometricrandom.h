#ifndef GEOMETRICRANDOM_H
#define GEOMETRICRANDOM_H

#include <random>
#include "randomplayout.h"
#include "heuristic.h"


class GeometricRandomPlayout : public RandomPlayout {
	public:
		GeometricRandomPlayout(heuristic &h):h(h){};
		double eval(board b);

	private:
		double state_value(board &b);
		heuristic &h;
};


#endif /* end of include guard: GEOMETRICRANDOM_H */


#include "geometricrandom.h"
#include "heuristic.h"


double GeometricRandomPlayout::eval(board b){
	int steps =1;
	std::uniform_real_distribution<double> unif(0, 1);
	while(!b.is_ended() && unif(rng)<(1.0/steps++) ){
		zet z= select_random_move(b);
		b=b+z;
	}
	return state_value(b);

}

double GeometricRandomPlayout::state_value(board& b){
	if (b.black_has_won()){
		return 1.0;
	}
	if (b.white_has_won()){
		return 0.0;
	}
	if (b.is_ended()){
		return 0.5;
	}
	double hval = h.evaluate(b);
	return (1/(1+exp(-hval)));
}



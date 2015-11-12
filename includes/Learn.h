#ifndef LEARN_H
#define LEARN_H

#include <vector>
#include "Robot.h"
#include "NeuralNetwork.h"

class Learn {
	public:
		Learn() 
		:	r1(0), r2(0)
		{}

		void insert(Robot r);
		NeuralNetwork newBrain(double percentToTake = 0.5);

	private:
		std::vector< Robot > robot_;
		int r1, r2;										// best two robot positions in robot_

		int score(Robot r);
		void bestTwo();
};

#endif

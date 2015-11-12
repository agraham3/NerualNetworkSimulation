#include "Learn.h"
#include "Exceptions.h"
#include "Config.h"

void Learn::insert(Robot r) {
	robot_.push_back(r);
}

int Learn::score(Robot r) {
	int points = 0;
	points += r.score() * POINT_BOOSTER;
	points += r.framesLived();
	return points;
}

void Learn::bestTwo() {
	int pos1 = 0,
			pos2 = 0,
			pts1 = 0,
			pts2 = 0;

	// Find the best two robots
	for (int i = 0; i < robot_.size(); ++i) {
		int points = score(robot_[i]);
		if (points > pts1) {
			// set second best
			pts2 = pts1;
			pos2 = pos1;

			// set best
			pts1 = points;
			pos1 = i;
		}
	}

	// set r1, r2 as the positions in robot_
	// 		where r1 is the best robot and
	//    r2 is the second best robot
	r1 = pos1; 
	r2 = pos2;
}

NeuralNetwork Learn::newBrain(double percentToTake) {
	if (percentToTake > 1)
		throw OverOneHunderedPercent();

	bestTwo();			    // find the best two robots: This sets r1, r2
											// 			where r1 is the best robot stored as a pos in robot_ and
											//  		r2 is the second best robot stored as a pos in robot_
	NeuralNetwork brain1 = robot_[r1].brain(),
								brain2 = robot_[r2].brain();
	NeuralNetwork newBrain = brain2;

	// Make random brains based off: brain1, brain2

	// Half of the best robots brain will be randomly chosen
	std::vector< int > layerPositions;
	int brain1size = brain1.size();
	int a = brain1size * percentToTake;	
	
	// Randomly pick unique layers from brain 1
	int x = 0;
	while (x != a) {
		int n = rand() % brain1size;
		if (!inList(n, layerPositions)) {
			layerPositions.push_back(n);
			++x;
		}
	}

	// Give brain2 a percent "percentToTake" of brain1
	for (int i = 0; i < layerPositions.size(); ++i) {
		newBrain.replace(i, brain1.get_layer(layerPositions[i]));
	}

	return newBrain;
}
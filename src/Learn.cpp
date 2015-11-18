#include "Learn.h"
#include "Exceptions.h"
#include "Config.h"

void Learn::insert(Object* r) {
	if (r->id() != "robot")
		throw NotARobot();

	object_.push_back(r);
}

int Learn::score(int pos) {
	int points = 0;
	points += object_[pos]->score() * POINT_BOOSTER;
	points += object_[pos]->framesLived();
	return points;
}

void Learn::bestTwo() {
	int pos1 = 0,
			pos2 = 0,
			pts1 = 0,
			pts2 = 0;

	// Find the best two robots
	for (int i = 0; i < object_.size(); ++i) {
		int points = score(i);
		if (points > pts1) {
			// set second best
			pts2 = pts1;
			pos2 = pos1;

			// set best
			pts1 = points;
			pos1 = i;
		}
	}

	// set o1, o2 as the positions in object_
	// 		where o1 is the best robot and
	//    o2 is the second best robot
	o1 = pos1; 
	o2 = pos2;
}

NeuralNetwork Learn::newBrain(double percentToTake) {
	if (percentToTake > 1)
		throw OverOneHunderedPercent();

	bestTwo();			    // find the best two robots: This sets o1, o2
											// 			where o1 is the best robot stored as a pos in object_ and
											//  		o2 is the second best robot stored as a pos in object_
	NeuralNetwork brain1 = object_[o1]->brain(),
								brain2 = object_[o2]->brain();
	NeuralNetwork newBrain = NeuralNetwork(brain2);

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
	for (int i = 0; i < layerPositions.size(); ++i)
		newBrain.replace(layerPositions[i], brain1.get_layer(layerPositions[i]));

	return newBrain;
}
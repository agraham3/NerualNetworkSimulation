#include <cstdlib>
#include <algorithm>
#include "Learn.h"
#include "AbstractFactory.h"
#include "Exceptions.h"
#include "Config.h"

void Learn::insert(Object* r) {
	if (r->id() != "robot")
		throw NotARobot();

	object_.push_back(r);
}

int Learn::score(Object* o) {
	int points = 0;
	points += o->score();
	points += o->framesLived();
	return points;
}

NeuralNetwork Learn::newBrain() {
	NeuralNetwork brain = object_[object_.size() - 1]->brain();
	object_.pop_back();
	return brain;
}

NeuralNetwork Learn::bestBrain() {
	int max = -999999;
	for (int i = 0; i < object_.size(); ++i) {
		int s = score(object_[i]);
		if (s <= max)
			continue;

		max = s;
	}

	for (int i = 0; i < object_.size(); ++i) {
		int s = score(object_[i]);
		if (s == max)
			return object_[i]->brain();
	}

	std::cout << "Could not find the brain...\n" << std::endl;
	int r = rand() % object_.size();
	return object_[r]->brain();
}

void Learn::remove(Object* o) {
  object_.erase(std::remove(object_.begin(), object_.end(), o), object_.end());
  delete o;
}

void Learn::run() {
	// remove the two deminstration robots
	object_.pop_back();
	object_.pop_back();

	// throw away half of the brains: (mainly the bad ones)
	// collect the points into a list
	std::deque<int> listPoints;
	for (int i = 0; i < object_.size(); ++i)
		listPoints.push_back(score(object_[i]));

	// sort the list
	std::sort(listPoints.begin(), listPoints.end());
	score_ = listPoints[listPoints.size() - 1];

	// remove the worst half
	std::vector<Object*> o;
	for (int i = 0; i < 50; ++i) {
		int n = listPoints[0];

		// find the robot with this score
		for (int j = 0; j < object_.size(); ++j) {
			if (score(object_[j]) != n)
				continue;

			remove(object_[j]);
  		break;
		}

		listPoints.pop_front();
	}

	// create 50 new brains
	for(int i = 0; i < 50; ++i) {
		NeuralNetwork newBrain = object_[i]->brain();
		newBrain.randomWeightChange();
  	Object * robot = AbstractFactory::createRobot();
  	robot->brain() = newBrain;
		object_.push_back(robot);
	}
}
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
	int pos = rand() % object_.size();
	NeuralNetwork brain = object_[pos]->brain();
	delete object_[pos];
	object_.erase(object_.begin() + pos);
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
	while(object_.size() != 100)
		object_.pop_back();

	// throw away half of the brains: (mainly the bad ones)
	// collect the points into a list
	std::deque<int> listPoints;
	for (int i = 0; i < object_.size(); ++i)
		listPoints.push_back(score(object_[i]));

	// sort the list
	std::sort(listPoints.begin(), listPoints.end());
	scoreH_ = listPoints[listPoints.size() - 1];
	scoreL_ = listPoints[0];

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

	// create 50 new brains: asumes brains are of the same size
	std::deque<Object* > temp = object_;
	while (1) {
		if (temp.size() == 0)
			break;

		int t1 = rand() % temp.size(),
				t2 = rand() % temp.size();
		while (t1 == t2)
			t2 = rand() % temp.size();

		NeuralNetwork brain1 = temp[t1]->brain();
		NeuralNetwork brain2 = temp[t2]->brain();
		NeuralNetwork nb1 = brain1;
		NeuralNetwork nb2 = brain2;
		temp.erase(temp.begin() + t1);
		temp.erase(temp.begin() + t2 - (t2 == 0 ? 0 : 1));

		// create new layers for new brain 1 and 2
		// 		I skip the 1st layer: cutting 1 weight does not make sence
		for (int a = 1; a < brain1.size(); ++a) {									// loop through layers
			std::deque< std::vector<double> > v1;
			std::deque< std::vector<double> > v2;
			for (int b = 0; b < brain1.get_layer(a).size(); ++b) {   // fill two vectors with the nuerons weights from both brains
				v1.push_back(brain1.get_layer(a).get_neuron(b).getWeights());
				v2.push_back(brain2.get_layer(a).get_neuron(b).getWeights());
			}

			// Loop through the nueron's weights: DNA Merging
			int pos = 0;
			while(1) {
				if (v1.size() == 0)
					break;

				std::vector<double> w1;
				std::vector<double> w2;

				// pull out the weights from each brain: then remove them from the list
				int p1 = rand() % v1.size(),
						p2 = rand() % v2.size();
				std::vector<double> wa = v1[p1];
				std::vector<double> wb = v2[p2];
				v1.erase(v1.begin() + p1);
				v2.erase(v2.begin() + p2);

				// DNA part
				int thisOne = 0;
				for(int n = 0; n < wa.size(); ++n) {
					if (n % 5 == 0)
						thisOne = 1 - thisOne;
					if (thisOne) {
						w1.push_back(wa[n]);
						w2.push_back(wb[n]);
					}
					else {
						w1.push_back(wb[n]);
						w2.push_back(wa[n]);
					}
				}

				// assign to neuron
				nb1.get_layer(a).get_neuron(pos).setWeights(w1);
				nb2.get_layer(a).get_neuron(pos).setWeights(w2);

				++pos;
			}
		}

		// create 2 new brains
		Object* robot0 = AbstractFactory::createRobot();
		Object* robot1 = AbstractFactory::createRobot();
		robot0->brain() = nb1;
		robot1->brain() = nb2;
		object_.push_back(robot0);
		object_.push_back(robot1);
	}
}
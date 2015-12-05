#ifndef LEARN_H
#define LEARN_H

#include <vector>
#include "Object.h"
#include "NeuralNetwork.h"

class Learn {
	public:
		Learn() 
		:	o1(0), o2(0), bestScore(0), secondBestScore(0), badBrains_(true)
		{}
		~Learn() {
			clear();	
		}

		void insert(Object* r);
		void clear() { 
			for (int i = 0; i < object_.size(); ++i)
				delete object_[i]; 

			object_.clear();
		}
		int size() { return object_.size(); }

		int getScore() { return bestScore; }
		bool badBrains() { return badBrains_; }
		NeuralNetwork newBrain(double percentToTake = 0.5);

		NeuralNetwork BestBrain() { return bestBrain; }
		NeuralNetwork SecondBestBrain() { return secondBestBrain; }

	private:
		std::vector< Object* > object_;
		int o1, o2;										// best two robot positions in robot_
		int bestScore, secondBestScore;
		NeuralNetwork bestBrain, secondBestBrain;
		bool badBrains_;

		int score(int pos);
		bool bestTwo();
};

#endif

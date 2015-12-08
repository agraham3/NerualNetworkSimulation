#ifndef LEARN_H
#define LEARN_H

#include <deque>
#include "Object.h"
#include "NeuralNetwork.h"

class Learn {
	public:
		Learn()
		: score_(-999999)
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
		void run();
		int score() { return score_; }

		NeuralNetwork bestBrain();

		// return a brain from the pool of brains
		NeuralNetwork newBrain();

	private:
		std::deque< Object* > object_;
		int score_;

		int score(Object*);
		bool bestTwo();
		void remove(Object*);
};

#endif

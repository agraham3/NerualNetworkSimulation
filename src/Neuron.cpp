#include "Neuron.h"

double Neuron::fire() {
	double n = sigmoid(dotProduct(inputs, weights));
  return (n >= 0.5 ? n : 0);
}


void Neuron::insert(const double & x) {
  inputs.push_back(x);
}

void Neuron::insertw(const double & w) {
  weights.push_back(w);
}

void Neuron::clear() {
  inputs.clear();
}

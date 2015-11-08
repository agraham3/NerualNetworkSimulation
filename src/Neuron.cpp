#include "Neuron.h"

double Neuron::fire() {
  return sigmoid(dotProduct(inputs, weights));
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

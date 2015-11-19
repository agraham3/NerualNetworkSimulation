#include "NeuronLayer.h"
#include <iostream>
#include <cstdlib>

void NeuronLayer::insert_neuron(Neuron n){
  neuron.push_back(n);
}

void NeuronLayer::push_layer(const double& v) {
  for (int i = 0; i < neuron.size(); ++i) {
  	neuron[i].insert(v);
  }
}

std::vector< double > NeuronLayer::fire() {
  std::vector< double > values;
  for (int i = 0; i < neuron.size(); ++i) {
  	values.push_back(neuron[i].fire());
  }
  return values;
}

void NeuronLayer::random_weights(int n) {
  for (int i = 0; i < neuron.size(); ++i) {
    for (int ww = 0; ww < n; ++ww) {
      int w = rand() % 41 - 20;       // rand weight: [-20, 20]
      neuron[i].insertw(w);
    }
  } 
}

void NeuronLayer::insert_value(const double & value, const int & pos) {
  neuron[pos].insert(value);
}

void NeuronLayer::clear_layer(){
  for (int i = 0; i < neuron.size(); ++i){
    neuron[i].clear();
  }
}
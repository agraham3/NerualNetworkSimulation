#include <iostream>
#include "NeuralNetwork.h"
#include "Exceptions.h"

void NeuralNetwork::create_layer(const int & n) {
  layer.push_back(NeuronLayer());
  int end = layer.size()-1;
  for (int i = 0; i < n; ++i){
    layer[end].insert_neuron(Neuron());
  }

  if (end != 0)
    layer[end].random_weights(layer[end-1].size());
  else
    layer[end].random_weights(1);
}

void NeuralNetwork::load(const std::vector< double > & input) {
  for (int i = 0; i < input.size(); ++i) {
    layer[0].insert_value(input[i], i);
  }

  int dif = layer[0].size() - input.size();
  if (dif != 0) {
    for (int i = 0; i < dif; ++i) {
      int pos = input.size() + i;
      layer[0].insert_value(0, pos); 
    }
  }
}

std::vector< double > NeuralNetwork::fire() {
  if (layer[0].is_empty()) {
    std::cout << "The Neural Network (layer 0) was not loaded" << std::endl;
    throw NetworkNotLoaded();
  }

  std::vector< double > output;
  for (int i = 0; i < layer.size(); ++i) {
    output = layer[i].fire();              // Fire   the layer
    layer[i].clear_layer();                // Remove values from current layer
    if (i + 1 < layer.size()) {            // Push   values to next layer
      for (int o = 0; o < output.size(); ++o) {
        layer[i+1].push_layer(output[o]);  // Load   next layer
      }
    }
  }

  return output;
}
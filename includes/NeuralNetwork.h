#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H

#include "NeuronLayer.h"

class NeuralNetwork {
  public:
  	NeuralNetwork() {}

    void create_layer(const int &);            // Create a new layer with n neurons
    void load(const std::vector< double > &);  // Load   initial input
    std::vector< double > fire();              // Run    the network
                                               //   The Fire function takes care of:
                                               //     Running the network
                                               //     Cleaning values out of the network 
    std::vector< NeuronLayer > get_layer() {return layer;}
  private:
  	std::vector< NeuronLayer > layer;
};

#endif

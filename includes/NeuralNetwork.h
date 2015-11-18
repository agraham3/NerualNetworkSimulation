#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H

#include "NeuronLayer.h"

class NeuralNetwork {
  public:
  	NeuralNetwork() {}
    NeuralNetwork(const NeuralNetwork& nn)
    : layer(nn.get_layers())
    {}

    void create_layer(const int &);            // Create a new layer with n neurons
    void load(const std::vector< double > &);  // Load   initial input
    std::vector< double > fire();              // Run    the network
                                               //   The Fire function takes care of:
                                               //     Running the network
                                               //     Cleaning values out of the network 

    
    std::vector< NeuronLayer > get_layers() { return layer; }
    std::vector< NeuronLayer > get_layers() const { return layer; }
    NeuronLayer get_layer(int layerPosition) { return layer[layerPosition]; }

    int size() const { return layer.size(); }
    void clear() { layer.clear(); }

    void set(std::vector<NeuronLayer> v) { layer = v; }
    void replace(int layerNumber, NeuronLayer l) { layer[layerNumber] = l; }
    
    void swap(int, int);

  private:
  	std::vector< NeuronLayer > layer;
};

#endif

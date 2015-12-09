#ifndef NEURONLAYER_H
#define NEURONLAYER_H

#include "Neuron.h"
#include "Exceptions.h"

/*
  Note: Make the first layer equal to the number of inputs

  To make the layers fire.
   1) init the first layer
   2) list = layer.fire()
   3) for item in list
   		(next layer).push_layer(item)
   4) repeat 2 and 3 until all layers are done
*/
class NeuronLayer {
  public:
  	NeuronLayer() {}
    NeuronLayer(const NeuronLayer& nl)
    : neuron(nl.neurons())
    {}

    void random_weights(int n);

    void insert_neuron(Neuron);
    void insert_value(const double & value, const int & pos);

  	void push_layer(const double&);
  	std::vector< double > fire();
    void clear_layer();

    // check if the layer is empty
    bool is_empty() { 
      if (neuron.size() == 0)
        throw NoLayerZero();

      return (neuron[0].getInputs().size() == 0);
    }

    int size() { return neuron.size(); }
    void clear() { neuron.clear(); }

    std::vector<Neuron>& neurons() { return neuron; }
    std::vector<Neuron> neurons() const { return neuron; }
    Neuron& get_neuron(int n)       { return neuron[n]; }
    Neuron  get_neuron(int n) const { return neuron[n]; }

  private:
  	std::vector< Neuron > neuron;
};

#endif

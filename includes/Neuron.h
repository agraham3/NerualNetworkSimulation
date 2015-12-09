#ifndef NEURON_H
#define NEURON_H

#include <iostream>
#include <vector>
#include "Functions.h"

class Neuron {
 public:
   Neuron() {}
   Neuron(const Neuron & n)
   : weights(n.getWeights()), inputs(n.getInputs())
   {}

  std::vector< double > getWeights() const { return weights; }
  std::vector< double > getInputs() const { return inputs; }

   // The purpose of this function is to sum up all the
   //   weights * x
   // Note: This is essentially:
   //   weights vector (dot product) x vector
   double fire();

   void insert(const double &);
   void insertw(const double &);
   void clear();

   void setWeight(const double value, const int pos) { weights[pos] = value; }
   void setWeights(std::vector<double> v) { weights = v; }

 private:
  std::vector< double > weights;
  std::vector< double > inputs;
};

inline
std::ostream & operator<<(std::ostream & cout, const Neuron & neuron) {
  cout << "<Neuron " << neuron.getWeights()[0] << '>';
  return cout;
}

#endif

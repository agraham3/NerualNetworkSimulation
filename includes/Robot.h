#ifndef ROBOT_H
#define ROBOT_H

#include "Object.h"
#include "Config.h"
#include "NeuralNetwork.h"
#include "ObjectManager.h"
#include <vector>


// This class consists of a dot "robot and a cirlce "vision"
class Robot : public Object {
 public:
 Robot(double x, double y, double rad,
       double red = 0, double green = 0, double blue = 0)
   : Object(x, y, red, green, blue), r_(rad), 
     vision_size(.4), look_at(PI/2), rotateSpeed(PI/16),
     robotSpeed(.01), bulletSpeed(Vec2f(.05,.05)),
     score_(0), framesLived_(0), energy_(100)
  {
    nn.create_layer(LAYER_ZERO_SIZE);
    nn.create_layer(8);
    nn.create_layer(5);
    nn.create_layer(5);
    nn.create_layer(8);
    nn.create_layer(10);
    nn.create_layer(10);
    nn.create_layer(5);
    nn.create_layer(7);                    // last layer size = number of actions
  }

  bool execute();
  std::vector< Vec2f > radar();

  void draw();

  double radius() { return r_; }
  double visionSize() { return vision_size; }

  int & score() { return score_; }
  int & energy() { return energy_; }

 private:
  double r_, vision_size, look_at, rotateSpeed, robotSpeed;
  Vec2f bulletSpeed;
  int score_, framesLived_, energy_;
  std::vector< double > robotInfo();

  std::string id() { return "robot"; }
  void shoot();
  void rotateLeft();
  void rotateRight();
  void moveUp();
  void moveDown();
  void moveLeft();
  void moveRight();

  NeuralNetwork nn;
  void initNetwork();
  std::vector< double > fireNetwork();
};

#endif

#ifndef ROBOT_H
#define ROBOT_H

#include <vector>
#include "Object.h"
#include "Config.h"
#include "NeuralNetwork.h"
#include "ObjectManager.h"


// This class consists of a dot "robot and a cirlce "vision"
class Robot : public Object {
 public:
 Robot(double x, double y, double rad,
       double red = 0, double green = 0, double blue = 0)
   : Object(x, y, red, green, blue), r_(rad), 
     vision_size(.4), look_at(PI/2), rotateSpeed(PI/16),
     robotSpeed(.01), bulletSpeed(Vec2f(.05,.05)),
     score_(0), framesLived_(0), energy_(ROBOT_ENERGY), numBullets_(NUM_ROBOT_BULLETS)
  {
    initBrain();
  }

  std::string id() { return "robot"; }
  bool execute();
  void handleAction(std::vector<double>);

  std::vector< Vec2f > radar();

  void draw();

  double radius() { return r_; }
  double visionSize() { return vision_size; }

  int& score() { return score_; }
  int& energy() { return energy_; }
  int& framesLived() { return framesLived_; }

  NeuralNetwork& brain() { return nn_; }

 private:
  double r_, vision_size, look_at, rotateSpeed, robotSpeed;
  Vec2f bulletSpeed;
  int score_, framesLived_, energy_, numBullets_;
  std::vector< double > robotInfo();

  void shoot();
  void rotateLeft();
  void rotateRight();
  void moveUp();
  void moveDown();
  void moveLeft();
  void moveRight();

  NeuralNetwork nn_;
  void initNetwork();
  std::vector< double > fireNetwork();
  void initBrain();
};

#endif

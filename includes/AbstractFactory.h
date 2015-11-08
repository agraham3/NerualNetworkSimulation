#ifndef ABSTRACTFACTORY_H
#define ABSTRACTFACTORY_H

#include "Robot.h"
#include "Bullet.h"

class AbstractFactory {
 public:
  AbstractFactory() {}
  
  static Object* createRobot(double x=0, double y=0, double rad = .5, 
                             double red=0, double green=0, double blue=0);
  static Object* createBullet(double x=0, double y=0, 
                              Vec2f d = Vec2f(), Object* whoShotMe = NULL,
                              double rad = .01,
                              double red=0, double green=0, double blue=0);
};

#endif


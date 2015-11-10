#ifndef OBJECT_H
#define OBJECT_H

#include <GL/freeglut.h>
#include <string>
#include "Vec2f.h"

class Object {
 public:
 Object(double x = 0, double y = 0, double red = 0, double green = 0, double blue = 0)
   : pos(Vec2f(x, y)), r(red), g(green), b(blue)
    {}
  
  virtual bool execute() {};
  virtual void draw() {};
  virtual std::string id() {};
  virtual Vec2f & getpos() { return pos; }
  
  virtual double getRed() { return r; }
  virtual double getGreen() { return g; }
  virtual double getBlue() { return b; }

  virtual double radius() {}
  virtual double visionSize() {}

  virtual Object* whoShotMe() {};
  virtual int& score() {};
  virtual int& energy() {};

 private:
  Vec2f pos;
  double r, g, b;
};

#endif

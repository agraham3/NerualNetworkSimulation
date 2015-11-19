#ifndef OBJECT_H
#define OBJECT_H

#include <GL/freeglut.h>
#include <string>
#include <cmath>
#include "Vec2f.h"
#include "NeuralNetwork.h"

class Object {
 public:
   Object(double x = 0, double y = 0, double red = 0, double green = 0, double blue = 0)
     : pos(Vec2f(x, y)), r(red), g(green), b(blue)
     {}
    
    virtual bool execute() {}
    virtual void draw() {}

    virtual std::string id() {}
    virtual Vec2f & getpos() { return pos; }
    virtual double red() { return r; }
    virtual double green() { return g; }
    virtual double blue() { return b; }
    virtual double radius() {}
    virtual int& framesLived() {}

    // robot
    virtual int& score() {}
    virtual int& energy() {}
    virtual double visionSize() {}
    virtual NeuralNetwork& brain() {}

    // bullet
    virtual Object* whoShotMe() {}
    virtual void setWhoShotMe(Object*) {}


 private:
    Vec2f pos;
    double r, g, b;
};

inline
bool circleCollisionCheck(Object* a, Object* b, bool useVision) {
  Vec2f apos = a->getpos();
  Vec2f bpos = b->getpos();

  double dx   = apos.x() - bpos.x(),
         dy   = apos.y() - bpos.y(),
         dist = sqrt(dx*dx + dy*dy);

  if (useVision)
    return (dist < a->visionSize() + b->radius());

  return (dist < (a->radius() + b->radius()));
}

#endif

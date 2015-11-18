#include "AbstractFactory.h"


Object* AbstractFactory::createRobot(double x, double y, double rad,
                                     double red, double green, double blue) {
  return new Robot(x, y, rad, red, green, blue);
}

Object* AbstractFactory::createRobot(Object* o) {
	Vec2f pos = o->getpos();
	Robot * r = new Robot(pos.x(), pos.y(), o->red(), o->green(), o->blue());
	r->brain() = o->brain();
	r->score() = o->score();
	r->framesLived() = o->framesLived();
	return r;
}

Object* AbstractFactory::createBullet(double x, double y, 
                                      Vec2f d, Object* whoShotMe,
                                      double rad,
                                      double red, double green, double blue) {
  return new Bullet(x, y, d, whoShotMe, rad, red, green, blue);
}
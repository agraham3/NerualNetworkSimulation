#include "Bullet.h"
#include "Functions.h"
#include "ObjectManager.h"

bool Bullet::execute() {
  bool moved = move();
  if (!moved)
    return false;

  return true;
}

void Bullet::setdir(Vec2f d) {
  dir = d;
}

bool Bullet::move(){
  Object::getpos() += dir;

  Vec2f pos = Object::getpos();
  if (!withinArena(pos))
    return false;

  return true;
}

void Bullet::draw() {
  Vec2f pos = Object::getpos();
  double x = pos.x(), y = pos.y();
  double r = Object::red(), g = Object::green(), b = Object::blue();
  glColor3f(r, g, b);
  regular_polygon(x, y, r_, 30, GL_TRIANGLE_FAN);            // draw bullet
  glColor3f(0,0,0);
}
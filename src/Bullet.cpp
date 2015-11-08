#include "Bullet.h"
#include "Functions.h"
#include "ObjectManager.h"

void Bullet::execute() {
  move();
}

void Bullet::setdir(Vec2f d) {
  dir = d;
}

void Bullet::move(){
  Object::getpos() += dir;

  Vec2f pos = Object::getpos();
  if (!withinArena(pos)) {
    ObjectManager * manager = ObjectManager::getInstance();
    manager->remove(this);
  }
}

void Bullet::draw() {
  Vec2f pos = Object::getpos();
  double x = pos.x(), y = pos.y();
  double r = Object::getRed(), g = Object::getGreen(), b = Object::getBlue();
  glColor3f(r, g, b);
  regular_polygon(x, y, r_, 30, GL_TRIANGLE_FAN);            // draw bullet
  glColor3f(0,0,0);
}
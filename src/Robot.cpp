#include "Robot.h"
#include "Functions.h"
#include "AbstractFactory.h"
#include <cmath>
#include <cstdlib>
#include "Config.h"

std::vector< double > Robot::robotInfo() {
  Vec2f pos = Object::getpos();

  std::vector< double > info;
  info.push_back(pos.x());
  info.push_back(pos.y());
  info.push_back(framesLived_);
  info.push_back(score_);
  info.push_back(energy_);

  // push x, y from radar
  std::vector< Vec2f > list = radar();
  int numrad = list.size();
  if (numrad > NUM_RADAR_CAN_SEE)
    numrad = NUM_RADAR_CAN_SEE;
  for(int i = 0; i < numrad; ++i) {
    info.push_back(list[i].x()); 
    info.push_back(list[i].y());
  }
  return info;
}

bool Robot::execute() {
  nn_.load(robotInfo());
  std::vector< double > output = nn_.fire();
  int pos = 0;
  double max = 0;
  for (int i = 0; i < output.size(); ++i) {
    double val = output[i];
    if (val >= 0.5 && val > max) {
      max = val;
      pos = i;
    }
  }

  if (max != 0) {
    switch (pos) {
      case 0: moveUp();      break;
      case 1: moveDown();    break;
      case 2: moveLeft();    break;
      case 3: moveRight();   break;
      case 4: rotateLeft();  break;
      case 5: rotateRight(); break;
      case 6: shoot();       break;
    }
  }

  framesLived_ += 1;
  energy_ -= 1;
  if (energy_ < 0) {
    return false;
  }
  
  return true;
}

std::vector< Vec2f > Robot::radar() {
  std::vector< Vec2f > v;
  ObjectManager * manager = ObjectManager::getInstance();
  std::vector< Object* > list = manager->getList();
  if (list.size() == 0)
    return v;

  for(int i = 0; i < list.size(); ++i) {
    if (list[i] != this) {
      // check to see if object is within radar
      if (list[i]->id() == "bullet")
        if (list[i]->whoShotMe() == this)
          continue;

      bool useVisionRadius = true;
      bool within = circleCollisionCheck(this, list[i], useVisionRadius);
      if (within) {
        Vec2f pos = list[i]->getpos();
        v.push_back(pos);
      }
    }
  }
  
  return v;
}

void Robot::shoot() {
  ObjectManager * manager = ObjectManager::getInstance();

  // get robots position
  Vec2f pos = Object::getpos();
  double x = pos.x(), y = pos.y();
  double a = x, b = y;

  // a,b -> look position
  cartesian(a, b, vision_size, look_at);

  // unit vector * speed vector
  Vec2f dir(a - x, b - y);
  double mag = sqrt(pow(dir.x(),2) + pow(dir.y(),2));
  dir /= Vec2f(mag, mag);
  dir *= bulletSpeed;

  // create bullet
  manager->insert(AbstractFactory::createBullet(x, y, dir, this));
}

void Robot::rotateLeft() {
  look_at -= rotateSpeed;
}

void Robot::rotateRight() {
  look_at += rotateSpeed;
}

void Robot::moveUp() {
  Vec2f pos = Object::getpos();
  Vec2f newpos = pos + Vec2f(pos.x(), robotSpeed);
  if (withinArena(newpos))
    Object::getpos().y() += robotSpeed;
}

void Robot::moveDown() {
  Vec2f pos = Object::getpos();
  Vec2f newpos = pos - Vec2f(pos.x(), robotSpeed);
  if (withinArena(newpos))
    Object::getpos().y() -= robotSpeed;
}

void Robot::moveLeft() {
  Vec2f pos = Object::getpos();
  Vec2f newpos = pos - Vec2f(robotSpeed, pos.y());
  if (withinArena(newpos))
    Object::getpos().x() -= robotSpeed;
}

void Robot::moveRight() {
  Vec2f pos = Object::getpos();
  Vec2f newpos = pos + Vec2f(robotSpeed, pos.y());
  if (withinArena(newpos))
    Object::getpos().x() += robotSpeed;
}

void Robot::draw() {
  Vec2f pos = Object::getpos();
  double x = pos.x(), y = pos.y();
  double r = Object::getRed(), g = Object::getGreen(), b = Object::getBlue();
  glColor3f(r, g, b);
  regular_polygon(x, y, r_, 30, GL_TRIANGLE_FAN);           // draw robot
  regular_polygon(x, y, vision_size, 30, GL_LINE_LOOP);  // draw vision ring
  glBegin(GL_LINES); {                                   // draw vision line
    glVertex2f(x, y);
    Vec2f sight(x, y);
    cartesian(sight.x(), sight.y(), vision_size, look_at);
    glVertex2f(sight.x(), sight.y());
  }
  glEnd();
  glColor3f(0,0,0);
}

void Robot::initBrain() {
  nn_.create_layer(LAYER_ZERO_SIZE);
  nn_.create_layer(8);
  nn_.create_layer(5);
  nn_.create_layer(5);
  nn_.create_layer(8);
  nn_.create_layer(10);
  nn_.create_layer(10);
  nn_.create_layer(5);
  nn_.create_layer(7);                    // last layer: size = number of actions
}

void Robot::setBrain(NeuralNetwork nn) {
  nn_.clear();
  nn_.set(nn.get_layers());
}

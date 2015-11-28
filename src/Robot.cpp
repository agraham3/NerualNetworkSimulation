#include <cmath>
#include <cstdlib>
#include "Robot.h"
#include "Functions.h"
#include "AbstractFactory.h"
#include "Config.h"

std::vector< double > Robot::robotInfo() {
  Vec2f pos = Object::getpos();

  std::vector< double > info;
  info.push_back(pos.x());
  info.push_back(pos.y());
  info.push_back(look_at);
  info.push_back(framesLived_);
  info.push_back(score_);
  info.push_back(energy_);
  info.push_back(numBullets_);

  // push x, y from radar
  std::vector< Object* > list = radar();
  int numrad = list.size();
  if (numrad > NUM_RADAR_CAN_SEE)
    numrad = NUM_RADAR_CAN_SEE;
  for(int i = 0; i < numrad; ++i) {
    Vec2f pos = list[i]->getpos();
    info.push_back(pos.x()); 
    info.push_back(pos.y());

    info.push_back(list[i]->radius());

    Vec2f speed = list[i]->speed();
    info.push_back(speed.x());
    info.push_back(speed.y());
  }

  return info;
}

bool Robot::handleAction(std::vector<double> act) {
  // Movement
  bool moved = false, moved1 = false;
  if (act[0] >= 0.5 && act[0] >= act[1])
    moved = moveUp();
  else if (act[1] > 0.5)
    moved = moveDown();
  if (act[2] >= 0.5 && act[2] >= act[3])
    moved1 = moveLeft();
  else if (act[3] >= 0.5)
    moved1 = moveRight();

  if (moved || moved1)
    score_ -= 100;

  if ((act[0] >= 0.5 || act[1] >= 0.5 ||
      act[2] >= 0.5 || act[3] >= 0.5) && !moved && !moved1)
    return true;

  // Rotation
  if (act[4] >= 0.5 && act[4] >= act[5])
    rotateLeft();
  else if (act[5] >= 0.5)
    rotateRight();

  // shoot
  if (act[6] >= 0.5) {
    shoot();    
    energy_ -= 5;
  }

  return false;
}

bool Robot::execute() {
  nn_.load(robotInfo());
  std::vector< double > output = nn_.fire();
  bool hitWall = handleAction(output);

  if (hitWall) {
    score_ -= 100;
    return false;
  }

  framesLived_ += 1;
  energy_ -= 1;
  if (energy_ < 0)
    return false;
  
  return true;
}

std::vector< Object* > Robot::radar() {
  std::vector< Object* > v;
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
        v.push_back(list[i]);
        score_ += 1;                  // give points for having objects within the radar
      }
    }
  }
  
  return v;
}

void Robot::shoot() {
  if (numBullets_ == 0)
    return;

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
  ObjectManager * manager = ObjectManager::getInstance();
  manager->insert(AbstractFactory::createBullet(x, y, dir, this));    
  --numBullets_;


  // give the robot points for shooting
  // while a robot is in vision
  bool robotFound = false;
  std::vector<Object* > v = radar();
  for (int i = 0; i < v.size(); ++i) {
    if (v[i]->id() == "robot") {
      score_ += 60;
      robotFound = true;
    }
  }

  if (!robotFound)
    score_ -= 60;
}

void Robot::rotateLeft() {
  look_at -= rotateSpeed;
}

void Robot::rotateRight() {
  look_at += rotateSpeed;
}

bool Robot::moveUp() {
  Vec2f pos = Object::getpos();
  Vec2f newpos = pos + Vec2f(pos.x(), robotSpeed);
  if (withinArena(newpos)) {
    Object::getpos().y() += robotSpeed;
    return true;
  }

  return false;
}

bool Robot::moveDown() {
  Vec2f pos = Object::getpos();
  Vec2f newpos = pos - Vec2f(pos.x(), robotSpeed);
  if (withinArena(newpos)) {
    Object::getpos().y() -= robotSpeed;
    return true;
  }

  return false;
}

bool Robot::moveLeft() {
  Vec2f pos = Object::getpos();
  Vec2f newpos = pos - Vec2f(robotSpeed, pos.y());
  if (withinArena(newpos)) {
    Object::getpos().x() -= robotSpeed;
    return true;
  }

  return false;
}

bool Robot::moveRight() {
  Vec2f pos = Object::getpos();
  Vec2f newpos = pos + Vec2f(robotSpeed, pos.y());
  if (withinArena(newpos)) {
    Object::getpos().x() += robotSpeed;
    return true;
  }

  return false;
}

void Robot::draw() {
  Vec2f pos = Object::getpos();
  double x = pos.x(), y = pos.y();
  double r = Object::red(), g = Object::green(), b = Object::blue();
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
  nn_.create_layer(8);
  nn_.create_layer(10);
  nn_.create_layer(12);
  nn_.create_layer(7);
  nn_.create_layer(NUMBER_ROBOT_ACTIONS);                    // last layer: size = number of actions
}

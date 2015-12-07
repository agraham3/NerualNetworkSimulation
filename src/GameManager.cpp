#include <cstdlib>
#include <cmath>
#include "Config.h"
#include "GameManager.h"

void GameManager::checkRestart() {
  static int restartTimer = RESTART_TIMER;

  if (restartTimer == 0) {
    manager_->clear();
    restartTimer = RESTART_TIMER;
    
    if (robotStorage_.size() == 0) {
      //manager_->learn().checkReset();
      std::cout << "Current max score: " << manager_->learn().getScore() << std::endl;

      // Show the best two robots battle
      Object * robot0 = AbstractFactory::createRobot(-0.35, 0, robotRad, 0, 0, 1);
      Object * robot1 = AbstractFactory::createRobot( 0.35, 0, robotRad, 1, 0, 0);
      if (!manager_->learn().badBrains()) {
        robot0->brain() = manager_->learn().BestBrain();
        robot1->brain() = manager_->learn().BestBrain();
      }
      manager_->insert(robot0);
      manager_->insert(robot1);

      // draw
      bool useManager = true;
      while (1) {
        eventHandler();
        draw(useManager);
        bool ran = manager_->execute();
        if (!ran)
          break;
      }

      // New generation creation
      bool useLearning = (generationNumber_ != 0);
      createRobots(useLearning);
      manager_->learn().clear();
      ++generationNumber_;
      std::cout << "Generation Number: " << generationNumber_ << std::endl;
    }
    
    // pull a robot out of storage and set him up for battle
    for (int i = 0; i < 2; ++i) {
      Object * robot = robotStorage_[robotStorage_.size()-1];
      robotStorage_.pop_back();
      robot->getpos() = givePosition();
      manager_->insert(robot);
    }
    std::cout << "gen: " << generationNumber_ << ", Robots in storage: " << robotStorage_.size() << std::endl;

    positions_.clear();
  }

  --restartTimer;
}

void GameManager::run() {
  std::cout << "Welcome to my Neural Network simulation.\n"
            << "There is 100 brains in every generation" << std::endl;
  surface_ = singletonSDL2::getInstance();
  createRobots();

  clearScreen();
  drawGrid();
  display();
  std::cout << "Generation Number: " << generationNumber_ << std::endl;
  const int killTimer = 100;
  int kt = killTimer;
  while(!quitProgram_) {
    if (manager_->size() == 1) {
      Object* o = manager_->getObject(0);
      if (o->id() == "robot")
        --kt;
      if (kt == 0){
        kt = killTimer;
        manager_->remove(o);
      }
    }

    bool ran = manager_->execute();
    if (!ran)
      checkRestart();

    eventHandler();
  }

  surface_->close();
}

void GameManager::eventHandler() {
  while (SDL_PollEvent(&event_)) {
    switch(event_.type) {
    case SDL_QUIT:
      quitProgram_ = true;
      break;
    }
  }
}

bool GameManager::checkPointExitsOrNear(double x, double y, double rad) {
  // check to see if a robot is near other robots
  for (int i = 0; i < positions_.size(); ++i) {
    double cx = positions_[i].x(),
           cy = positions_[i].y();

    // check if point exists
    if (cx == x && cy == y)
      return true;

    // check if they are near
    double dx = x - cx,
           dy = y - cy,
           dist = sqrt(dx*dx + dy*dy);

    // check to see how close they are
    if (dist < rad + rad * 4)
      return true;
  }

  return false;
}

Vec2f GameManager::givePosition() {
  double x = 0, y = 0;
  while(1) {
    x = ((double)rand() / RAND_MAX) * 1.6 - .8, 
    y = ((double)rand() / RAND_MAX) * 1.6 - .8;
    if (checkPointExitsOrNear(x, y, robotRad))
      continue;

    positions_.push_back(Vec2f(x, y));
    break;
  }

  return Vec2f(x, y);
}

void GameManager::createRobot(bool useLearning) {
  // choose a starting (x, y)
  double x = 0, y = 0;
  double r = ((double)rand() / RAND_MAX) / 2,
         g = ((double)rand() / RAND_MAX) / 2,
         b = ((double)rand() / RAND_MAX) / 2;
  Object * robot = AbstractFactory::createRobot(x, y, robotRad, r, g, b);

  if (useLearning) {
      double percent = ((double)rand() / RAND_MAX) / 2 + 0.5;
      NeuralNetwork newBrain = manager_->learn().newBrain(percent);
      if (!manager_->learn().badBrains())
        robot->brain() = newBrain;
  }

  int brainSize = robot->brain().size();
  if (brainSize == 0)
    throw NoBrain();

  // Mutate the robots brain.
  int check = rand() % 4;
  for (int i = 0; i < check; ++i)
    robot->brain().randomWeightChange();

  robotStorage_.push_back(robot);
}

void GameManager::createRobots(bool useLearning) {
  for (int i = 0; i < 100; ++i)
    createRobot(useLearning);
}

void GameManager::draw(bool useManager) {
  int start = SDL_GetTicks();
  eventHandler();
  updateScreen(useManager);
  int end = SDL_GetTicks();
  if (useManager)
    delay(start, end);
}

void GameManager::updateScreen(bool useManager) {
  clearScreen();
  drawGrid();
  if (useManager)
    manager_->draw();

  display();
}

int GameManager::getDelayTime(int start, int end) {
  int frame_length = 1000 / FRAMES_PER_SEC;
  int dt = frame_length - (end - start);
  return dt;
}

void GameManager::delay(int start, int end) {
  int delay = getDelayTime(start, end);
  surface_->wait(delay);
}
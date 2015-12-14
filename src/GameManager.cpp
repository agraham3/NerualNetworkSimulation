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
      // Show the best two robots battle
      if (generationNumber_ % 20 == 0) {
        for (int i = 0; i < 3; ++i) {
          std::cout << "Fight num: " << i + 1 << std::endl;
          double x1 = ((double)rand() / RAND_MAX) - 0.5, 
                 x2 = ((double)rand() / RAND_MAX) - 0.5,
                 y1 = ((double)rand() / RAND_MAX) - 0.5, 
                 y2 = ((double)rand() / RAND_MAX) - 0.5;
          while(checkPointExitsOrNear(x2, y2, robotRad)) {
            x2 = ((double)rand() / RAND_MAX) - 0.5, 
            y2 = ((double)rand() / RAND_MAX) - 0.5;
          }

          Object * robot0 = AbstractFactory::createRobot(x1, y1, robotRad, 0, 0, 1);
          Object * robot1 = AbstractFactory::createRobot(x2, y2, robotRad, 1, 0, 0);

          NeuralNetwork brain = manager_->learn().bestBrain();
          robot0->brain() = brain;
          robot1->brain() = brain;

          manager_->insert(robot0);
          manager_->insert(robot1);

          // draw the demo
          bool useManager = true;
          while (!quitProgram_) {
            eventHandler();
            draw(useManager);
            bool ran = manager_->execute();
            if (!ran)
              break;
          }
        }
      }

      // New generation creation
      ++generationNumber_;
      bool useLearning = (generationNumber_ != 0);
      createRobots(useLearning);
      manager_->learn().clear();
      std::cout << "Generation Number: " << generationNumber_ 
                << "    score range: "
                << '[' << manager_->learn().scoreLow() << ", "
                << manager_->learn().scoreHigh() << ']' << std::endl;
    }
    
    // pull a robot out of storage and set him up for battle
    for (int i = 0; i < 2; ++i) {
      Object * robot = robotStorage_[robotStorage_.size()-1];
      robotStorage_.pop_back();
      robot->getpos() = givePosition();
      manager_->insert(robot);
    }

    //std::cout << "gen: " << generationNumber_ << ", Robots in storage: " << robotStorage_.size() << std::endl;
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
  while(!quitProgram_) {
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
    NeuralNetwork newBrain = manager_->learn().newBrain();
    robot->brain() = newBrain;
  }

  int brainSize = robot->brain().size();
  if (brainSize == 0)
    throw NoBrain();

  // Mutate the robots brain.
  int check = rand() % 10 + 1;
  if (check >= 8)
    robot->brain().randomWeightChange();

  robotStorage_.push_back(robot);
}

void GameManager::createRobots(bool useLearning) {
  if (useLearning)
    manager_->learn().run();
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
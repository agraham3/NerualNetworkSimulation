#include <cstdlib>
#include <cmath>
#include "Config.h"
#include "Object.h"
#include "GameManager.h"
#include "NeuralNetwork.h"

void GameManager::checkRestart() {
  static int restartTimer = RESTART_TIMER;
  static int newGenerationTimer = NUMBER_OF_ROUNDS;
  
  if (restartTimer == 0) {
    manager_->clear();
    restartTimer = RESTART_TIMER;

    bool useLearning = (generationNumber_ != 0);
    createRobots(useLearning);
    
    if (newGenerationTimer == 0) {
      newGenerationTimer = NUMBER_OF_ROUNDS;

      // New generation
      manager_->learn().clear();
      ++generationNumber_;
      std::cout << "Current max score: " << manager_->learn().getScore() << std::endl;
      std::cout << "Generation Number: " << generationNumber_ << std::endl;
    }
    --newGenerationTimer;
  }

  --restartTimer;
}

void GameManager::run() {
  surface_ = singletonSDL2::getInstance();
  std::cout << "Generation Number: " << generationNumber_ << std::endl;
  createRobots();

  while(!quitProgram_) {
    int start = SDL_GetTicks();

    if (manager_->size() == 1) {
      if (manager_->getObject(0)->id() == "robot")
        manager_->getObject(0)->score() += LAST_ONE_STANDING;
      manager_->remove(manager_->getObject(0));
    }

    bool ran = manager_->execute();

    if (!ran) {
      checkRestart();
    }

    if (generationNumber_ % 100 == 0) {
      eventHandler();
      updateScreen();

      int end = SDL_GetTicks();
      delay(start, end);
    }
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

void GameManager::createRobot(bool useLearning) {
  double robotRad = 0.05;

  // choose a starting (x, y)
  double x = 0, y = 0;
  while(1) {
    x = ((double)rand() / RAND_MAX) * 1.6 - .8, 
    y = ((double)rand() / RAND_MAX) * 1.6 - .8;

    if (checkPointExitsOrNear(x, y, robotRad))
      continue;

    positions_.push_back(Vec2f(x, y));
    break;
  }

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
  int check = rand() % 10 + 1;
  if (check > 6) {
    //std::cout << "Mutate a robots brain." << std::endl;
    robot->brain().randomWeightChange();
  }

  manager_->insert(robot);
}

void GameManager::createRobots(bool useLearning) {
  for (int i = 0; i < NUM_ROBOTS; ++i) {
    int check = rand() % 30 + 1;
    if (check > 28 && generationNumber_ != 0) {
      //std::cout << "Creating a dumb robot" << std::endl;
      createRobot(!useLearning);
    }
    else
      createRobot(useLearning);
  }

  positions_.clear();
}

void GameManager::updateScreen() {
  clearScreen();
  drawGrid();
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
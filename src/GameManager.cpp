#include "GameManager.h"
#include <cstdlib>
#include "Config.h"
#include "Object.h"
#include "NeuralNetwork.h"

void GameManager::checkRestart() {
  static int restartTimer = RESTART_TIMER;
  
  if (restartTimer == 0) {
    manager_->clear();
    restartTimer = RESTART_TIMER;

    bool useLearning = true;
    createRobots(useLearning);
    manager_->learn().clear();
    ++generationNumber_;
    std::cout << "Generation Number: " << generationNumber_ << std::endl;
  }

  --restartTimer;
}

void GameManager::run() {
  surface_ = singletonSDL2::getInstance();
  createRobots();
  std::cout << "Generation Number: " << generationNumber_ << std::endl;

  while(!quitProgram_) {
    int start = SDL_GetTicks();

    bool ran = manager_->execute();
    if (!ran)
      checkRestart();

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

void GameManager::createRobot(bool useLearning) {
  double x = ((double)rand() / RAND_MAX) - 0.5, 
         y = ((double)rand() / RAND_MAX) - 0.5;

  double r = ((double)rand() / RAND_MAX) / 2,
         g = ((double)rand() / RAND_MAX) / 2,
         b = ((double)rand() / RAND_MAX) / 2;
  Object * robot = AbstractFactory::createRobot(x, y, .05, r, g, b);

  if (useLearning)
    robot->brain() = manager_->learn().newBrain(0.60);

  int brainSize = robot->brain().size();
  if (brainSize == 0)
    throw NoBrain();

  // Mutate the robots brain.
  int check = rand() % 10 + 1;
  if (check > 8) {
    std::cout << "Mutate a robots brain." << std::endl;
    robot->brain().randomWeightChange();
  }

  manager_->insert(robot);
}

void GameManager::createRobots(bool useLearning) {
  for (int i = 0; i < NUM_ROBOTS; ++i) {
    int check = rand() % 10 + 1;
    if (check > 9 && generationNumber_ != 0) {
      std::cout << "Creating a dumb robot" << std::endl;
      createRobot(!useLearning);
    }
    else
      createRobot(useLearning);
  }
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
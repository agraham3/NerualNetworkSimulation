#include "GameManager.h"
#include <cstdlib>
#include "Config.h"
#include "Object.h"
#include "NeuralNetwork.h"

void GameManager::checkRestart() {
  static int restartTimer = RESTART_TIMER;
  static int generationNumber = 0;
  
  if (restartTimer == 0) {
    manager_->clear();
    restartTimer = RESTART_TIMER;
    ++generationNumber;

    bool useLearning = true;
    createRobots(useLearning, generationNumber);
    manager_->learn().clear();
    std::cout << "Generation Number: " << generationNumber << std::endl;
  }

  --restartTimer;
}

void GameManager::run() {
  createRobots();

  std::cout << "Generation Number: " << 0 << std::endl;
  while(!quitProgram_) {
    int start = SDL_GetTicks();

    eventHandler();
    bool ran = manager_->execute();
    updateScreen();

    if (!ran) {
      checkRestart();
    }

    int end = SDL_GetTicks();
    delay(start, end);
    ++frame_;
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
  double x = ((double)rand() / RAND_MAX) * 2 - 1, 
         y = ((double)rand() / RAND_MAX) * 2 - 1;

  double r = ((double)rand() / RAND_MAX) / 2,
         g = ((double)rand() / RAND_MAX) / 2,
         b = ((double)rand() / RAND_MAX) / 2;
  Object * robot = AbstractFactory::createRobot(x, y, .05, r, g, b);

  if (useLearning)
    robot->brain() = manager_->learn().newBrain(0.60);

  int brainSize = robot->brain().size();
  if (brainSize == 0)
    throw NoBrain();

  // Morph the robots brain.
  //   Change:  Layer swaps.                        (Do not change 1st or last layer)
  //            Change number of nuerons in a layer (Do not have 0 neurons in a layer)
  int check = rand() % 10;
  if (check > 8) {
    std::cout << "Changing a robot's brain. " << std::endl;
    int a = 0, b = 0;
    while(a == 0 || a >= brainSize - 1 ||
          b == 0 || b >= brainSize - 1 ||
          a == b) {
        a = rand() % brainSize + 1;
        b = rand() % brainSize + 1;
    }
    std::cout << "    Swaping layer #: " << a + 1 << ", " << b + 1 << std::endl;
    //robot->brain()->swap(a, b);
  }

  manager_->insert(robot);
}

void GameManager::createRobots(bool useLearning, int generationNumber) {
  for (int i = 0; i < NUM_ROBOTS; ++i) {
    int check = rand() % 10;
    if (check > 8 && generationNumber != 0) {
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
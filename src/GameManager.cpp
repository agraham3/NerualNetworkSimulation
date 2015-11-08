#include "GameManager.h"
#include <cstdlib>
#include "Config.h"

void GameManager::checkRestart() {
  static int restartTimer = RESTART_TIMER;
  static int generationNumber = 0;
  
  if (restartTimer == 0) {
    manager_->clear();
    createRobots();
    restartTimer = RESTART_TIMER;

    ++generationNumber;
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

void GameManager::createRobot() {
  double x = ((double)rand() / RAND_MAX) * 2 - 1, 
         y = ((double)rand() / RAND_MAX) * 2 - 1;

  double r = ((double)rand() / RAND_MAX) / 2,
         g = ((double)rand() / RAND_MAX) / 2,
         b = ((double)rand() / RAND_MAX) / 2;
         
  manager_->insert(AbstractFactory::createRobot(x, y, .05, r, g, b));
}

void GameManager::createRobots() {
  for (int i = 0; i < NUM_ROBOTS; ++i)
    createRobot();
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
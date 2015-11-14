#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "singletonSDL2.h"
#include "Drawing.h"
#include "AbstractFactory.h"
#include "ObjectManager.h"
#include "NeuralNetwork.h"

class GameManager {
public:
  GameManager()
   : surface_(singletonSDL2::getInstance()), quitProgram_(false),
     frame_(0), manager_(ObjectManager::getInstance())
  {}

  void run();

private:
  bool quitProgram_;
  int frame_;
  singletonSDL2 * surface_;
  SDL_Event event_;
  ObjectManager * manager_;

  void eventHandler();
  void createRobot(bool useLearning);
  void createRobots(bool useLearning=false);
  void updateScreen();
  int getDelayTime(int start, int end);
  void delay(int start, int end);
  void checkRestart();
};

#endif

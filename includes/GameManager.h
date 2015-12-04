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
   : quitProgram_(false), generationNumber_(0),
     manager_(ObjectManager::getInstance())
  {}

  void run();

private:
  bool quitProgram_;
  int generationNumber_;
  singletonSDL2 * surface_;
  SDL_Event event_;
  ObjectManager * manager_;
  std::vector< Vec2f > positions_;

  void eventHandler();
  void createRobot(bool useLearning);
  void createRobots(bool useLearning=false);
  void updateScreen();
  int getDelayTime(int start, int end);
  void delay(int start, int end);
  void checkRestart();
  bool checkPointExitsOrNear(double x, double y, double rad);

};

#endif

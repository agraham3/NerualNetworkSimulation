#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "singletonSDL2.h"
#include "Drawing.h"
#include "Object.h"
#include "AbstractFactory.h"
#include "ObjectManager.h"
#include "NeuralNetwork.h"

class GameManager {
public:
  GameManager()
   : quitProgram_(false), generationNumber_(0), robotRad(0.05),
     manager_(ObjectManager::getInstance())
  {}

  void run();

private:
  bool quitProgram_;
  double robotRad;
  singletonSDL2 * surface_;
  SDL_Event event_;
  int generationNumber_;
  ObjectManager * manager_;
  std::vector< Object* > robotStorage_;
  std::vector< Vec2f > positions_;

  void checkRestart();

  void createRobots(bool useLearning=false);  
  void createRobot(bool useLearning);
  Vec2f givePosition();

  void eventHandler();
  void draw(bool);
  void updateScreen(bool);
  int getDelayTime(int start, int end);
  void delay(int start, int end);

  bool checkPointExitsOrNear(double x, double y, double rad);
};

#endif

// My libraries
#include <cstdlib>
#include "GameManager.h"

// Main
int main(int argc, char* args[]) {
  srand((unsigned int) time(NULL));

  GameManager gamemanager;

  // Application running
  gamemanager.run();    

  return 0;
}
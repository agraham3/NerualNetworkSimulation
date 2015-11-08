#ifndef SINGLETONSDL2_H
#define SINGLETONSDL2_H

#include <SDL2/SDL.h>
#include <GL/freeglut.h>

#include "Config.h"

class singletonSDL2
{
public:
  static singletonSDL2 * getInstance() {
    if ( p == NULL ) 
      p = new singletonSDL2(HEIGHT, WIDTH);
    
    return p;
  }
  ~singletonSDL2() {
    delete p;
  }
  
  void wait(int);
  void close();
  
  SDL_Window * get_window() { return window; }
  
 private:
  singletonSDL2(int, int);
  int _width, _height;
  SDL_Window* window = NULL;
  SDL_GLContext context;
  
  static singletonSDL2 * p;
  
  // The quadric object
  GLUquadricObj * gluQuadObj = gluNewQuadric();
};

#endif

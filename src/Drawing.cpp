#include <SDL2/SDL.h>
#include <GL/freeglut.h>
#include "singletonSDL2.h"

void grid() {
  glBegin( GL_LINES ); {
    glColor3f( 0.75, 0.75, 0.75 );
    
    for ( double x = -1.0; x <= 1.0; x += 0.1f ) {
      glVertex2f( x, -1 );
      glVertex2f( x, 1 );
    }
    
    for ( double y = -1.0; y <= 1.0; y += 0.1f ) {
      glVertex2f( -1, y );
      glVertex2f( 1, y );
    }
  }
  glEnd();
}

void axes() {
  glBegin( GL_LINES ); {
    // x-axis
    glColor3f( 0.7, 0.0, 0.0 );
    glVertex2f( -1, 0 );
    glVertex2f( 1, 0 );
    
    // y-axis
    glColor3f( 0.7, 0.0, 0.0 );
    glVertex2f( 0, -1 );
    glVertex2f( 0, 1 );
  }
  glEnd();
}

void drawGrid() {
  grid();
  axes();
}

void clearScreen() {
  glClear( GL_COLOR_BUFFER_BIT );
}

void display() {
  singletonSDL2 * surface = singletonSDL2::getInstance();
  SDL_GL_SwapWindow( surface -> get_window() );
}

#include "singletonSDL2.h"

singletonSDL2 * singletonSDL2::p = NULL;

singletonSDL2::singletonSDL2(int width, int height)
  : _width(width), _height(height) {
  // ****************************
  // Initialize SDL
  // ****************************
  
  if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
    printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
    exit(0);
  }
  
  //Use OpenGL 2.1
  SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 2 );
  SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 1 );
  
  // Create SDL window
  window = SDL_CreateWindow( TITLE, SDL_WINDOWPOS_CENTERED, 
                             SDL_WINDOWPOS_CENTERED, 
                             width, height, SDL_WINDOW_OPENGL );
  if( window == NULL ) {
    printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
    exit(1);
  }

  // Create context
  context = SDL_GL_CreateContext( window );
  if( context == NULL ) {
    printf( "OpenGL context could not be created! SDL Error: %s\n", 
            SDL_GetError() );
    exit(2);
  }

  //Use Vsync
  if( SDL_GL_SetSwapInterval( 1 ) < 0 ) {
    printf( "Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError() );
  }

  
  // ****************************
  // Initialize OpenGL
  // ****************************
  GLenum error = GL_NO_ERROR;

  //Initialize Projection Matrix
  glMatrixMode( GL_PROJECTION );
  glLoadIdentity();
  
  //Check for error
  error = glGetError();
  if( error != GL_NO_ERROR ) {
    printf( "Error initializing OpenGL! %s\n", gluErrorString( error ) );
    exit(3);
  }

  //Initialize Modelview Matrix
  glMatrixMode( GL_MODELVIEW );
  glLoadIdentity();

  //Check for error
  error = glGetError();
  if( error != GL_NO_ERROR ) {
    printf( "Error initializing OpenGL! %s\n", gluErrorString( error ) );
    exit(4);
  }

  //Initialize clear color
  glClearColor( 1.0f, 1.0f, 1.0f, 1.0f );
  
  //Check for error
  error = glGetError();
  if( error != GL_NO_ERROR ) {
    printf( "Error initializing OpenGL! %s\n", gluErrorString( error ) );
    exit(5);
  }
}

// A window delay timer
void singletonSDL2::wait(int time) {
  if (time < 0)
    return;
  
  SDL_Delay( time );
}

// Close the SDL window
void singletonSDL2::close() {
  //Destroy window
  SDL_DestroyWindow( window );
  
  gluDeleteQuadric( gluQuadObj );
  
  //Quit SDL subsystems
  SDL_Quit();
}

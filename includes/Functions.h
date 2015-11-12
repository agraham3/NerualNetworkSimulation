#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <GL/freeglut.h>
#include "Vec2f.h"
#include <vector>
#include "Object.h"

// Game Related Functions
bool withinArena(Vec2f);
bool circleCollisionCheck(Object* a, Object* b, bool vision = false);


// Math
void cartesian(double & x, double & y, double r, double theta);
double sigmoid(double);
double dotProduct(std::vector< double > a, std::vector< double > b);


// Drawling
void draw_square(double cx, double cy, double w, double h);

void regular_polygon(double cx, double cy, double r, 
                     int num_segments, const int gl_draw_type = GL_LINE_LOOP); 
void regular_polygon2(double cx, double cy, double r, double r2,
                      int num_segments, const int gl_draw_type);


// Other
bool inList(int x, std::vector<int> v);

#endif

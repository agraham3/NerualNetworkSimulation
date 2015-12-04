#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <vector>
#include <GL/freeglut.h>
#include "Vec2f.h"

// Game Related Functions
bool withinArena(Vec2f);


// Math
void cartesian(double & x, double & y, double r, double theta);
bool lookingAt(double theta, Vec2f robot, Vec2f enemy);
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

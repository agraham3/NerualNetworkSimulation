#include "Functions.h"
#include "Exceptions.h"  
#include "Config.h"

#include <cmath>
#include <iostream>

bool withinArena(Vec2f d) {
  if (d.x() < -1 || d.y() < -1 ||
      d.x() > 1  || d.y() > 1) {
    return false;
  }

  return true;
}

bool circleCollisionCheck(Object* a, Object* b, bool vision) {
  Vec2f apos = a->getpos();
  Vec2f bpos = b->getpos();

  double dx   = apos.x() - bpos.x(),
         dy   = apos.y() - bpos.y(),
         dist = sqrt(dx*dx + dy*dy);

  if (vision) {
    return (dist < a->visionSize() + b->radius());
  }

  return (dist < (a->radius() + b->radius()));
}

void cartesian(double & x, double & y, double r, double theta) {
  x = r * cos(theta) + x;
  y = r * sin(theta) + y;
}

double sigmoid(double x) {
  double n = 1.0;
  double d = 1.0 + pow(M_E, x * -1);
  return n / d;
}

// a and b should be of equal sizes
double dotProduct(const std::vector< double > a, 
                  const std::vector< double > b) {
  if (a.size() != b.size()) {
    std::cout << "Vector a and b must be of equal sizes:\n"
              << "A: " << a.size() << ", "
              << "B: " << b.size() << std::endl;
    throw SizeError();
  }

  double sum = 0.0;
  for(int i = 0; i < a.size(); ++i) {
    sum += a[i] * b[i];
  }
  return sum;
}

void draw_square(double cx, double cy, double w, double h) {
  glBegin(GL_QUADS); {
    glVertex2f(cx - w/2, cy + h/2);  // top left
    glVertex2f(cx + w/2, cy + h/2);  // top right
    glVertex2f(cx + w/2, cy - h/2);  // bot right
    glVertex2f(cx - w/2, cy - h/2);  // bot left
  }
  glEnd();
}

void regular_polygon2(double cx, double cy, double r, double r2,
                     int num_segments, int gl_draw_type)  { 
  double theta  = PI / 2,
        dtheta = TAU / num_segments; 
    
  glBegin(gl_draw_type);
  for(int ii = 0; ii < num_segments; ++ii)  { 
    double x = cx + r  * cos(theta),
          y = cy + r2 * sin(theta);
    glVertex2f(x, y);
    theta += dtheta;
  }
  glEnd(); 
}

void regular_polygon(double cx, double cy, double r, 
                     int num_segments, int gl_draw_type)  { 
  regular_polygon2(cx, cy, r, r, num_segments, gl_draw_type);
}

bool inList(int x, std::vector<int> v) {
  bool in = false;
  for (int i = 0; i < v.size(); ++i) {
    if (x = v[i]) {
      in = true;
      break;
    }
  }

  return in;
}


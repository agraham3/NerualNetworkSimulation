#ifndef Vec2f_H
#define Vec2f_H

#include <iostream>

class Vec2f {
 public:
 
 Vec2f(double x = 0, double y = 0)
   : _x(x), _y(y) 
  {}
  
 Vec2f(const Vec2f & a)
   :_x(a._x), _y(a._y)
    {}

  double & x() { return _x; }
  double & y() { return _y; }
  double x() const { return _x; }
  double y() const { return _y; }

  Vec2f & operator+=(const Vec2f& a) {
    _x += a._x;
    _y += a._y;
    return *this;
  }

  Vec2f operator+(const Vec2f& a) {
    return Vec2f(*this) += a;
  }

  Vec2f & operator-=(const Vec2f& a) {
    _x -= a._x;
    _y -= a._y;
    return *this;
  }

  Vec2f operator-(const Vec2f& a) {
    return Vec2f(*this) -= a;
  }

  Vec2f & operator*=(const Vec2f& a) {
    _x *= a._x;
    _y *= a._y;
    return *this;
  }

  Vec2f operator*(const Vec2f& a) {
    return Vec2f(*this) *= a;
  }

  Vec2f & operator/=(const Vec2f& a) {
    _x /= a._x;
    _y /= a._y;
    return *this;
  }

  Vec2f operator/(const Vec2f& a) {
    return Vec2f(*this) /= a;
  }

 private:
  double _x, _y;
};

inline
std::ostream & operator <<(std::ostream & cout, const Vec2f& v) {
  cout << "< " << v.x() << ", " << v.y() << ">";
  return cout;
}

#endif

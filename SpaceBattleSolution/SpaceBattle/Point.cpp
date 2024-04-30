#include "pch.h"
#include "Point.h"

Point::Point(double _x, double _y) :
    x(_x), y(_y) {
}

int Point::GetIntX() const {
  return static_cast<int>(this->x);
}

int Point::GetIntY() const {
  return static_cast<int>(this->y);
}

double Point::GetX() {
  return x;
}

double Point::GetY() {
  return y;
}

void Point::SetX(double new_x) {
  this->x = new_x;
}

void Point::SetY(double new_y) {
  this->y = new_y;
}

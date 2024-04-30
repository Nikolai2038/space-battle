#pragma once
class Point {
  private:
    double x;
    double y;
  public:
    Point(double _x = 0, double _y = 0);

    int GetIntX() const;
    int GetIntY() const;

    double GetX();
    double GetY();

    void SetX(double new_x);
    void SetY(double new_y);
};

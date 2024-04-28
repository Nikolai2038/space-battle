#pragma once
#include "Point.h"

interface IEntity {
private:
  Point location = Point();
public:
  // ���������� ������� ��������
  Point GetLocation() const;

  // ������������� ����� ������� ��������
  void SetLocation(const Point new_location);

  // ������������ ��������
  void Draw();
};

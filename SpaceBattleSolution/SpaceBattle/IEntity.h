#pragma once
#include "Point.h"

interface IEntity {
private:
  Point location = Point();
public:
  // Возвращает позицию сущности
  Point GetLocation() const;

  // Устанавливает новую позицию сущности
  void SetLocation(const Point new_location);

  // Отрисовывает сущность
  void Draw();
};

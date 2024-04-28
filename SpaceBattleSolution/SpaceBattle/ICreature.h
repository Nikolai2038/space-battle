#pragma once
#include "IEntity.h"
#include "Point.h"

class ICreature : IEntity {
private:
  Point location;
public:
  Point get_location() const {
    return location;
  }
};

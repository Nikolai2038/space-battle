#pragma once

#include "Entity.h"
#include <list>

// Корабль
class Ship : public Entity {
protected:
  Ship();
  explicit Ship(int image_resource_id);
public:
  void Shoot(std::list<Entity *> &entities);
};

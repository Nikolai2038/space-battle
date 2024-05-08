#pragma once

#include "Entity.h"
#include <list>

// �������
class Ship : public Entity {
protected:
  explicit Ship(int image_resource_id);
public:
  void Shoot(std::list<Entity *> &entities);
};

#pragma once

#include "Entity.h"
#include "Ship.h"

// Снаряд
class Bullet : public Entity {
public:
  explicit Bullet(Ship* new_owner);
};

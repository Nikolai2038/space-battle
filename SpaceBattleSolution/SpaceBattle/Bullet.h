#pragma once
#include "Entity.h"
#include "Ship.h"

// ������
class Bullet : public Entity {
  public:
    Bullet(Ship* new_owner);
};

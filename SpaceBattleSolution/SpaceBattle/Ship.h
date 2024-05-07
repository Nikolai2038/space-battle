#pragma once
#include "Entity.h"

// Корабль
class Ship : public Entity {
  private:
    double health;
  protected:
    Ship(int image_resource_id);
};

#pragma once
#include <list>

#include "Entity.h"

// �������
class Ship : public Entity {
  private:
    double health;
  protected:
    Ship(int image_resource_id);
  public:
    void Shoot(std::list<Entity *> &entities);
};

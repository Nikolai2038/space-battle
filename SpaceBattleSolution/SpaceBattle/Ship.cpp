#include "pch.h"
#include "Bullet.h"
#include "Ship.h"
#include <list>

Ship::Ship(const int image_resource_id) :
    Entity(image_resource_id) {
}

void Ship::Shoot(std::list<Entity *> &entities) {
  const auto bullet = new Bullet(this);
  bullet->SetLocation(this->GetX(), this->GetY());
  bullet->SetAngle(this->GetAngle());
  bullet->SetActionMovement(ActionMovement::ToAngle);
  bullet->AddToList(entities);
}

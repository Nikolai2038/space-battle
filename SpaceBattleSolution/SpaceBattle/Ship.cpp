#include "pch.h"
#include "Ship.h"

Ship::Ship(int image_resource_id) :
    Entity(image_resource_id, 0.2) {
  this->health = 100;
}

void Ship::Shoot() {
  Bullet* bullet = new Bullet();
  bullet->SetLocation(this->GetX(), this->GetY());
  bullet->SetAngle(this->GetAngle());
  bullet->SetActionMovement(ActionMovement::ToAngle);
  this->childs.push_back(bullet);
}

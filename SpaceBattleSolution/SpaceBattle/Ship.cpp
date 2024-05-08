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
  // ƒобавл€ем в начало, так как при отрисовке, последние сущности будут перекрывать новые
  entities.push_front(bullet);
}

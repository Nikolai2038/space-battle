#include "pch.h"
#include "Ship.h"

#include <list>

#include "Bullet.h"

Ship::Ship(int image_resource_id) :
    Entity(image_resource_id, 0.2) {
  this->health = 100;
}

void Ship::Shoot(std::list<Entity *> &entities) {
  Bullet *bullet = new Bullet(this);
  bullet->SetLocation(this->GetX(), this->GetY());
  bullet->SetAngle(this->GetAngle());
  bullet->SetActionMovement(ActionMovement::ToAngle);
  // ��������� � ������, ��� ��� ��� ���������, ��������� �������� ����� ����������� �����
  entities.push_front(bullet);
}

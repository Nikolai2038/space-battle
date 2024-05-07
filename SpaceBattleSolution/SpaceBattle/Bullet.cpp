#include "pch.h"
#include "Bullet.h"

#include "Config.h"
#include "resource.h"

Bullet::Bullet(Ship* new_owner) :
    Entity(IDB_BULLET, 0.5) {
  this->speed = DEFAULT_SPEED * 2;
  this->owner = new_owner;
}

#include "pch.h"
#include "Bullet.h"

#include "Config.h"
#include "resource.h"

Bullet::Bullet() :
    Entity(IDB_BULLET, 0.5) {
  this->speed = DEFAULT_SPEED * 2;
}

#include "pch.h"
#include "Bullet.h"
#include "Config.h"
#include "resource.h"

Bullet::Bullet(Ship* new_owner) :
    Entity(IDB_BULLET) {
  this->owner = new_owner;
  this->scale = BULLET_IMAGE_SCALE;
  this->speed = new_owner->GetSpeed() + BULLET_SPEED;
  this->health = DEFAULT_BULLET_HEALTH;
}

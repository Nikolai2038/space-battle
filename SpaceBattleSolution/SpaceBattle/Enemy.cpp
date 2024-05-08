#include "pch.h"
#include "Config.h"
#include "Enemy.h"
#include "resource.h"

Enemy::Enemy() :
    Ship(IDB_ENEMY) {
  this->scale = ENEMY_IMAGE_SCALE;
  this->health = DEFAULT_ENEMY_HEALTH;

  // Враг сразу начинает движение в том направлении, в котором смотрит
  this->SetActionMovement(ActionMovement::ToAngle);
}

#include "pch.h"
#include "Enemy.h"

#include "resource.h"

Enemy::Enemy() :
    Ship(IDB_ENEMY) {
  // Враг сразу начинает движение в том направлении, в котором смотрит
  this->SetActionMovement(ActionMovement::ToAngle);
}

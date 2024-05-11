#include "pch.h"
#include "Config.h"
#include "Enemy.h"
#include "resource.h"

Enemy::Enemy() :
    Ship() {
  this->scale = ENEMY_IMAGE_SCALE;
  this->health = DEFAULT_ENEMY_HEALTH;

  const int image_id = GetRandom(0, 2);
  switch (image_id) {
    case 0:
      SetImage(IDB_ENEMY_1);
      break;
    case 1:
      SetImage(IDB_ENEMY_2);
      break;
    case 2:
    default:
      SetImage(IDB_ENEMY_3);
      break;
  }

  // Враг сразу начинает движение в том направлении, в котором смотрит
  this->SetActionMovement(ActionMovement::ToAngle);
}

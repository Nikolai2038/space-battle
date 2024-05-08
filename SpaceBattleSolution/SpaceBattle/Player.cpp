#include "pch.h"
#include "Config.h"
#include "Player.h"
#include "resource.h"

Player::Player() :
    Ship(IDB_PLAYER) {
  this->scale = PLAYER_IMAGE_SCALE;
  this->health = DEFAULT_PLAYER_HEALTH;

  // Игрок всегда двигается в том направлении, в котором смотрит
  this->SetActionMovement(ActionMovement::ToAngle);
  // но изначально имеет нулевую скорость
  this->speed = 0;
}

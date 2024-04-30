#include "pch.h"
#include "Ship.h"

Ship::Ship(int image_resource_id) :
    Entity(image_resource_id) {
  this->health = 100;
}

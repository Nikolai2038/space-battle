#include "pch.h"
#include "IEntity.h"

Point IEntity::GetLocation() const {
  return location;
}

void IEntity::SetLocation(const Point new_location) {
  location = new_location;
}

void IEntity::Draw() {
}

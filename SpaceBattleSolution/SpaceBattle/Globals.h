#pragma once
#include <list>

#include "Entity.h"

// „исло ѕи = 3.14...
const double PI = atan(1) * 4;

template <class T>
T GetRandom(T min, T max) {
  return (static_cast<double>(rand()) / (RAND_MAX - min)) * max + min;
}

enum class SideToSpawn {
  Left,
  Right,
  Top,
  Bottom
};

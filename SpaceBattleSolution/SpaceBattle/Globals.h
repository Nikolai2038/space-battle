#pragma once

// Число Пи = 3.14...
const double PI = atan(1) * 4;

// Угол поворота сущностей по умолчанию
static const double DEFAULT_ANGLE = PI / 2;

// Функция получения случайного числа в заданном диапазоне
template <class T>
T GetRandom(T min, T max) {
  return (static_cast<double>(rand()) / (RAND_MAX - min)) * max + min;
}

// Сторона экрана для создания врага
enum class SideToSpawn {
  Left,
  Right,
  Top,
  Bottom
};

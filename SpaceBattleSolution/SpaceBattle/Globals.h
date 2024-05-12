#pragma once

#include <string>
#include <windows.h>

// Число Пи = 3.14...
const double PI = atan(1) * 4;

// Угол поворота сущностей по умолчанию
static const double DEFAULT_ANGLE = PI / 2;

// Функция получения случайного числа в заданном диапазоне
template <typename T>
T GetRandom(T min, T max) {
  return (static_cast<double>(rand() + 1) / RAND_MAX * (max - min + 1) + min);
}

// Сторона экрана для создания врага
enum class SideToSpawn {
  Left,
  Right,
  Top,
  Bottom
};

// Возвращает путь к директории с EXE-файлом
inline std::string GetExeDirectory() {
  // Получаем путь к EXE-файлу
  char result[MAX_PATH];
  const auto exe_path = std::basic_string<char>(result, GetModuleFileNameA(nullptr, result, MAX_PATH));

  // Получаем путь к директории с ним
  std::string directory;
  const size_t last_slash_idx = exe_path.rfind('\\');
  if (std::string::npos != last_slash_idx) {
    directory = exe_path.substr(0, last_slash_idx);
  }
  return directory;
}

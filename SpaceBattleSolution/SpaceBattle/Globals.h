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

// Function to convert LPCWSTR to std::string
inline std::string ConvertLPCWSTRToString(const LPCWSTR lpcwsz_str) {
  // Determine the length of the converted string
  // - 1 at the end - to remove NULL-terminator
  const int str_length = WideCharToMultiByte(CP_UTF8, 0, lpcwsz_str, -1, nullptr, 0, nullptr, nullptr) - 1;

  // Create a std::string with the determined length
  std::string str(str_length, 0);

  // Perform the conversion from LPCWSTR to std::string
  WideCharToMultiByte(CP_UTF8, 0, lpcwsz_str, -1, &str[0], str_length, nullptr, nullptr);

  // Return the converted std::string
  return str;
}

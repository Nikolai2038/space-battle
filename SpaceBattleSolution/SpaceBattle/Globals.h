#pragma once

#include <string>
#include <windows.h>

// ����� �� = 3.14...
const double PI = atan(1) * 4;

// ���� �������� ��������� �� ���������
static const double DEFAULT_ANGLE = PI / 2;

// ������� ��������� ���������� ����� � �������� ���������
template <typename T>
T GetRandom(T min, T max) {
  return (static_cast<double>(rand() + 1) / RAND_MAX * (max - min + 1) + min);
}

// ������� ������ ��� �������� �����
enum class SideToSpawn {
  Left,
  Right,
  Top,
  Bottom
};

// ���������� ���� � ���������� � EXE-������
inline std::string GetExeDirectory() {
  // �������� ���� � EXE-�����
  char result[MAX_PATH];
  const auto exe_path = std::basic_string<char>(result, GetModuleFileNameA(nullptr, result, MAX_PATH));

  // �������� ���� � ���������� � ���
  std::string directory;
  const size_t last_slash_idx = exe_path.rfind('\\');
  if (std::string::npos != last_slash_idx) {
    directory = exe_path.substr(0, last_slash_idx);
  }
  return directory;
}

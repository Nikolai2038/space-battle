#pragma once

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

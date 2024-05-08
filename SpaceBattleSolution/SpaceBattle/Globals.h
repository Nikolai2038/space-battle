#pragma once

// ����� �� = 3.14...
const double PI = atan(1) * 4;

// ���� �������� ��������� �� ���������
static const double DEFAULT_ANGLE = PI / 2;

// ������� ��������� ���������� ����� � �������� ���������
template <class T>
T GetRandom(T min, T max) {
  return (static_cast<double>(rand()) / (RAND_MAX - min)) * max + min;
}

// ������� ������ ��� �������� �����
enum class SideToSpawn {
  Left,
  Right,
  Top,
  Bottom
};

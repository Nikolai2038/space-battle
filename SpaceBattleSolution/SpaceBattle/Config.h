#pragma once
#include <string>

#include "Globals.h"

// ����� � ������������� ��� ����� ���������� ������� �������� ���������
static constexpr int TIMER_CLOCK_LOOP_IN_MS = 10;

// ����� � ������������� ��� ����� ���������� ������� ���������
static constexpr int TIMER_REDRAW_LOOP_IN_MS = 10;

// ����� � ������������� ��� ����� ���������� ������� ������ ������ � ������
static constexpr int TIMER_GARBAGE_COLLECTOR_LOOP_IN_MS = 1000;

// �������� ��������� �� ���������
static constexpr double DEFAULT_SPEED = 1;

// ����������� �������� ��������� �� ���������
static constexpr double DEFAULT_SPEED_MIN = -1;

// ������������ �������� ��������� �� ���������
static constexpr double DEFAULT_SPEED_MAX = 4;

// ��������� �� ��������� - ��������� �������� ����� �������� �������� �� ������� �������
static constexpr double DEFAULT_ACCELERATION = 0.1;

// ���������� �� ��������� - ��������� �������� ����� �������� �������� �� ������� �������
static constexpr double DEFAULT_DE_ACCELERATION = 0.2;

// �������� ���� �� ���������
static constexpr double BULLET_SPEED = DEFAULT_SPEED * 5;

// ��������� ��� ������� �������� ���������
static constexpr double INTERSECT_RADIUS_SCALE = 0.8;

// ����������� ��������������� ����������� ��������� �� ���������
static constexpr double DEFAULT_IMAGE_SCALE = 1.0;

// ����������� ��������������� ����������� ��� ������
static constexpr double PLAYER_IMAGE_SCALE = 1;

// ����������� ��������������� ����������� ��� �����
static constexpr double ENEMY_IMAGE_SCALE = 1;

// ����������� ��������������� ����������� ��� ����
static constexpr double BULLET_IMAGE_SCALE = 1;

// ���������� ������ �������� �� ��������� � ��������
static constexpr int DEFAULT_ENTITY_HEALTH = 1;

// ���������� ������ �������� �� ��������� � ������
static constexpr int DEFAULT_PLAYER_HEALTH = 10;

// ���������� ������ �������� �� ��������� � �����
static constexpr int DEFAULT_ENEMY_HEALTH = 3;

// ���������� ������ �������� �� ��������� � ����
static constexpr int DEFAULT_BULLET_HEALTH = 1;

// ���������� ����� �� ���������, ������� ���� �������� ��� �����������
static constexpr int DEFAULT_ENTITY_SELF_POINTS = 10;

// ����� � ��������, ������ ������� ����������� ����� ����� (�������� � ������ ����)
static constexpr int INITIAL_WAVE_TIME = 5;

// ���������� ������������ ������ �� ���� ��� (�������� � ������ ����)
static constexpr int INITIAL_WAVE_ENEMIES_COUNT = 1;

// ���������� ����, ������ ������� ����� �� ��������� ����� �����������
static constexpr int WAVES_TILL_DECREASE_WAVE_TIME = 2;

// �����, �� ������� ����������� ����� �� ��������� �����
static constexpr int DECREASE_WAVE_TIME = 1;

// ���������� (������������) ��������� ����� � ��������, ������ ������� ����������� ����� �����
static constexpr int MIN_WAVE_TIME = 1;

// ���������� ����, ������ ������� ���������� ������ ����� �������������
static constexpr int WAVES_TILL_INCREASE_WAVE_ENEMIES_COUNT = 2;

// ���������� ������, �� ������� ������������� ���������� ������ � ��������� �����
static constexpr int INCREASE_WAVE_ENEMIES_COUNT = 1;

// ������������ (������������) ���������� ������������ ������ �� ���� ���
static constexpr int MAX_WAVE_ENEMIES_COUNT = 10;

// ������� ������ �������� ����� ���������� ���������� ��� ������ �������� ���� ����� ������ ��������
static constexpr int DEFAULT_INVINCIBLE_FOR_GAME_FIELD_BORDERS_SECONDS_LEFT = 3;

// ������ �� ������� �������� ����, � ������� ���������� �����
static constexpr int PADDING_ON_SIDE_TO_SPAWN_ENEMY = 100;

// ���������� ���� �������� ��� ����� (� ������ �� ������ �� ����������� ��������)
// �� ���������� ������, ��� PI / 2
static const double ENEMY_ANGLE_RANGE = PI / 3;

// ��� �������� �� ���������
static const std::string ENTITY_DEFAULT_NAME = "Unnamed";

// ��� ������ �� ���������
static const auto PLAYER_DEFAULT_NAME = L"Player";

// ���� � ����� � ��������� ������������ ������������ �����
static const std::string RECORDS_FILE_PATH = "./records.txt";

// ����������� �������� � ����� � ���������
static constexpr char RECORDS_FILE_DELIMITER = '|';

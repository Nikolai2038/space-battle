#pragma once
#include "Globals.h"

static constexpr int TIMER_CLOCK_LOOP_IN_MS = 1;
static constexpr int TIMER_REDRAW_LOOP_IN_MS = 10;

static constexpr double DEFAULT_SPEED = 1;
static constexpr double BULLET_SPEED = DEFAULT_SPEED * 2;

static const double DEFAULT_ANGLE = PI / 2;

static constexpr double INTERSECT_RADIUS_SCALE = 0.8;

static constexpr double DEFAULT_IMAGE_SCALE = 1.0;
static constexpr double PLAYER_IMAGE_SCALE = 0.2;
static constexpr double ENEMY_IMAGE_SCALE = 0.2;
static constexpr double BULLET_IMAGE_SCALE = 0.5;

static constexpr int DEFAULT_ENTITY_HEALTH = 1;
static constexpr int DEFAULT_PLAYER_HEALTH = 10;
static constexpr int DEFAULT_ENEMY_HEALTH = 3;
static constexpr int DEFAULT_BULLET_HEALTH = 1;

static constexpr int DEFAULT_ENTITY_SELF_POINTS = 10;

// Время в секундах, спустя которое запускается новая волна (значение в начале игры)
static constexpr int INITIAL_WAVE_TIME = 5;

// Количество генерируемых врагов за один раз (значение в начале игры)
static constexpr int INITIAL_WAVE_ENEMIES_COUNT = 1;

// Количество волн, спустя которое время до следующей волны уменьшается
static constexpr int WAVES_TILL_DECREASE_WAVE_TIME = 2;

// Время, на которое уменьшается время до следующей волны
static constexpr int DECREASE_WAVE_TIME = 1;

// Минимально (включительно) возможное время в секундах, спустя которое запускается новая волна
static constexpr int MIN_WAVE_TIME = 1;

// Количество волн, спустя которое количество врагов волны увеличивается
static constexpr int WAVES_TILL_INCREASE_WAVE_ENEMIES_COUNT = 2;

// Количество врагов, на которое увеличивается количество врагов в очередной волне
static constexpr int INCREASE_WAVE_ENEMIES_COUNT = 1;

// Максимальное (включительно) количество генерируемых врагов за один раз
static constexpr int MAX_WAVE_ENEMIES_COUNT = 3;

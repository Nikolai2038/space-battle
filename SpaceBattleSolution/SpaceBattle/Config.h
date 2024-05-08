#pragma once
#include "Globals.h"

// ¬рем€ в миллисекундах дл€ между итераци€ми таймера действий сущностей
static constexpr int TIMER_CLOCK_LOOP_IN_MS = 10;

// ¬рем€ в миллисекундах дл€ между итераци€ми таймера отрисовки
static constexpr int TIMER_REDRAW_LOOP_IN_MS = 10;

// ¬рем€ в миллисекундах дл€ между итераци€ми таймера чистки мусора в пам€ти
static constexpr int TIMER_GARBAGE_COLLECTOR_LOOP_IN_MS = 1000;

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

// ¬рем€ в секундах, спуст€ которое запускаетс€ нова€ волна (значение в начале игры)
static constexpr int INITIAL_WAVE_TIME = 5;

//  оличество генерируемых врагов за один раз (значение в начале игры)
static constexpr int INITIAL_WAVE_ENEMIES_COUNT = 1;

//  оличество волн, спуст€ которое врем€ до следующей волны уменьшаетс€
static constexpr int WAVES_TILL_DECREASE_WAVE_TIME = 2;

// ¬рем€, на которое уменьшаетс€ врем€ до следующей волны
static constexpr int DECREASE_WAVE_TIME = 1;

// ћинимально (включительно) возможное врем€ в секундах, спуст€ которое запускаетс€ нова€ волна
static constexpr int MIN_WAVE_TIME = 1;

//  оличество волн, спуст€ которое количество врагов волны увеличиваетс€
static constexpr int WAVES_TILL_INCREASE_WAVE_ENEMIES_COUNT = 2;

//  оличество врагов, на которое увеличиваетс€ количество врагов в очередной волне
static constexpr int INCREASE_WAVE_ENEMIES_COUNT = 1;

// ћаксимальное (включительно) количество генерируемых врагов за один раз
static constexpr int MAX_WAVE_ENEMIES_COUNT = 3;

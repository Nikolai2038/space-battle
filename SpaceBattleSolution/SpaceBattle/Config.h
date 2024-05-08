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
static constexpr int DEFAULT_ENEMY_HEALTH = 1;
static constexpr int DEFAULT_BULLET_HEALTH = 1;

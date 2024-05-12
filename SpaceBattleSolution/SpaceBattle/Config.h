#pragma once
#include <string>

#include "Globals.h"

// Время в миллисекундах для между итерациями таймера действий сущностей
static constexpr int TIMER_CLOCK_LOOP_IN_MS = 10;

// Время в миллисекундах для между итерациями таймера отрисовки
static constexpr int TIMER_REDRAW_LOOP_IN_MS = 10;

// Время в миллисекундах для между итерациями таймера чистки мусора в памяти
static constexpr int TIMER_GARBAGE_COLLECTOR_LOOP_IN_MS = 1000;

// Скорость сущностей по умолчанию
static constexpr double DEFAULT_SPEED = 1;

// Минимальная скорость сущностей по умолчанию
static constexpr double DEFAULT_SPEED_MIN = -1;

// Максимальная скорость сущностей по умолчанию
static constexpr double DEFAULT_SPEED_MAX = 4;

// Ускорение по умолчанию - насколько сущность может повысить скорость за единицу времени
static constexpr double DEFAULT_ACCELERATION = 0.1;

// Замедление по умолчанию - насколько сущность может понизить скорость за единицу времени
static constexpr double DEFAULT_DE_ACCELERATION = 0.2;

// Скорость пуль по умолчанию
static constexpr double BULLET_SPEED = DEFAULT_SPEED * 5;

// Множитель для радиуса коллизии сущностей
static constexpr double INTERSECT_RADIUS_SCALE = 0.8;

// Коэффициент масштабирования изображений сущностей по умолчанию
static constexpr double DEFAULT_IMAGE_SCALE = 1.0;

// Коэффициент масштабирования изображения для игрока
static constexpr double PLAYER_IMAGE_SCALE = 1;

// Коэффициент масштабирования изображения для врага
static constexpr double ENEMY_IMAGE_SCALE = 1;

// Коэффициент масштабирования изображения для пули
static constexpr double BULLET_IMAGE_SCALE = 1;

// Количество единиц здоровья по умолчанию у сущности
static constexpr int DEFAULT_ENTITY_HEALTH = 1;

// Количество единиц здоровья по умолчанию у игрока
static constexpr int DEFAULT_PLAYER_HEALTH = 10;

// Количество единиц здоровья по умолчанию у врага
static constexpr int DEFAULT_ENEMY_HEALTH = 3;

// Количество единиц здоровья по умолчанию у пули
static constexpr int DEFAULT_BULLET_HEALTH = 1;

// Количество очков по умолчанию, которое даст сущность при уничтожении
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
static constexpr int MAX_WAVE_ENEMIES_COUNT = 10;

// Сколько секунд сущность будет оставаться неуязвимой для границ игрового поля после своего создания
static constexpr int DEFAULT_INVINCIBLE_FOR_GAME_FIELD_BORDERS_SECONDS_LEFT = 3;

// Отступ на стороне игрового поля, в котором появляются враги
static constexpr int PADDING_ON_SIDE_TO_SPAWN_ENEMY = 100;

// Допустимый угол поворота для врага (в каждую из сторон от направления движения)
// Не выставлять больше, чем PI / 2
static const double ENEMY_ANGLE_RANGE = PI / 3;

// Имя сущности по умолчанию
static const std::string ENTITY_DEFAULT_NAME = "Unnamed";

// Имя игрока по умолчанию
static const auto PLAYER_DEFAULT_NAME = L"Player";

// Путь к файлу с рекордами относительно исполняемого файла
static const std::string RECORDS_FILE_PATH = "./records.txt";

// Разделитель столбцов в файле с рекордами
static constexpr char RECORDS_FILE_DELIMITER = '|';

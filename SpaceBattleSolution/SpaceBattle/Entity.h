#pragma once

#include <list>

// Сущность на поле игры
class Entity {
protected:
  // Действие движения сущности
  enum class ActionMovement {
    // Сущность не двигается
    None,
    // Сущность двигается в направлении, в котором она смотрит (куда повёрнута)
    ToAngle
  };
private:
  // Позиция X сущности (относительно левого верхнего угла)
  double x;

  // Позиция Y сущности (относительно левого верхнего угла)
  double y;

  // Направление движения в радианах
  double angle;

  // Вращается ли сущность в правую сторону
  bool is_rotating_right;

  // Вращается ли сущность в левую сторону
  bool is_rotating_left;

  // Ускоряется ли сущность
  bool is_accelerating;

  // Замедляется ли сущность
  bool is_de_accelerating;

  // Действие движения, производимое сущностью в данный момент
  ActionMovement action_movement;

  // Является ли сущность уничтоженной.
  // Уничтоженная сущность не производит действий и не рисуется.
  bool is_destroyed;

  // Информация об изображении сущности
  BITMAP bmp_info;

  // Изображение сущности
  HBITMAP bmp_loaded;

  // Ширина сущности
  LONG width;

  // Высота сущности
  LONG height;

  // Сколько очков заработала эта сущность
  int points_earned;

  // Сколько сущностей уничтожила эта сущность
  int entities_destroyed;

  // Сколько очков стоит эта сущность
  int self_points;

  // Сколько единиц времени сущность ещё будет оставаться неуязвимой для границ игрового поля
  int is_invincible_for_game_field_borders_clocks_left;
protected:
  Entity* owner;

  // Параметр масштабирования сущности (1.0 - без масштабирования)
  double scale;

  // Текущая скорость движения
  double speed;

  // Минимальная скорость движения
  double min_speed;

  // Максимальная скорость движения
  double max_speed;

  // Ускорение - насколько сущность может повысить скорость за единицу времени
  double acceleration;

  // Замедление - насколько сущность может понизить скорость за единицу времени
  double de_acceleration;

  // Количество единиц здоровья.
  // Одно столкновение отбирает одну единицу здоровья.
  int health;

  /// Создаёт новую сущность
  /// @param image_resource_id ID ресурса изображения сущности
  explicit Entity(int image_resource_id);
public:
  ~Entity();

  // Возвращает позицию X сущности
  double GetX() const;

  // Возвращает позицию X сущности (целым числом)
  int GetIntX() const;

  /// Устанавливает позицию X сущности
  /// @param new_x Новая позиция X
  void SetX(double new_x);

  // Возвращает позицию Y сущности
  double GetY() const;

  // Возвращает позицию Y сущности (целым числом)
  int GetIntY() const;

  /// Устанавливает позицию Y сущности
  /// @param new_y Новая позиция Y
  void SetY(double new_y);

  // Устанавливает новую позицию сущности
  /// @param new_x Новая позиция X
  /// @param new_y Новая позиция Y
  void SetLocation(double new_x, double new_y);

  // Возвращает угол поворота сущности (в радианах)
  double GetAngle() const;

  // Устанавливает угол поворота сущности (в радианах)
  void SetAngle(double new_angle);

  // Сущность начнёт поворачиваться направо
  void StartRotatingRight();

  // Сущность перестанет поворачиваться направо
  void StopRotatingRight();

  // Сущность начнёт поворачиваться налево
  void StartRotatingLeft();

  // Сущность перестанет поворачиваться налево
  void StopRotatingLeft();

  // Сущность начинает ускоряться
  void StartAccelerating();

  // Сущность перестанет ускоряться
  void StopAccelerating();

  // Сущность начинает замедляться
  void StartDeAccelerating();

  // Сущность перестанет замедляться
  void StopDeAccelerating();

  // Возвращает действие движения, производимое сущностью в данный момент
  ActionMovement GetActionMovement() const;

  // Устанавливает действие движения, производимое сущностью в данный момент
  /// @param new_action_movement Новое действие движения
  void SetActionMovement(ActionMovement new_action_movement);

  // Является ли сущность уничтоженной
  bool IsDestroyed() const;

  // Возвращает размер радиуса, в котором может быть видна сущность относительно её центра
  LONG GetMaxVisibleRadiusOnField() const;

  // Возвращает количество заработанных очков
  int GetPointsEarned() const;

  // Возвращает количество уничтоженных сущностей этой сущностью
  int GetEntitiesDestroyed() const;

  // Возвращает самого первого владельца этой сущности (рекурсивно)
  Entity* GetMainOwner();

  // Возвращает параметр масштабирования сущности
  double GetScale() const;

  // Устанавливает параметр масштабирования сущности
  void SetScale(double new_scale);

  // Возвращает скорость сущности
  double GetSpeed() const;

  // Устанавливает скорость сущности
  void SetSpeed(double new_speed);

  // Возвращает количество здоровья сущности
  int GetHealth() const;

  // Возвращает радиус круга коллизии объекта (от его центра)
  int GetIntersectRadius() const;

  // Отрисовывает сущность
  void Draw(const HDC& hdc, const HDC& hdc_bits) const;

  // Обрабатывает действия сущности в текущую единицу времени
  void ProcessActions(const std::list<Entity*>& entities, const CRect& game_field);
private:
  // Уменьшает здоровье сущности на одну единицу.
  // Если здоровья не останется - сущность будет уничтожена.
  void Hit(Entity* by_whom);

  // Помечает сущность как уничтоженную
  void Destroy(Entity* by_whom = nullptr);

  // Проверяет, пересекается ли эта сущность с указанной
  bool IsIntersectsWith(const Entity& entity) const;
public:
  // Добавляет эту сущность в указанный список (заменит любую уничтоженную сущность в этом списке)
  void AddToList(std::list<Entity*>& entities);
};

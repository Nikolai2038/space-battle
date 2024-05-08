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
protected:
  /// Создаёт новую сущность
  /// @param image_resource_id ID ресурса изображения сущности
  explicit Entity(int image_resource_id);

  Entity* owner;

  // Параметр масштабирования сущности (1.0 - без масштабирования)
  double scale;

  // Скорость движения
  double speed;

  // Количество единиц здоровья.
  // Одно столкновение отбирает одну единицу здоровья.
  int health;
public:
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
  void StartRotatingRight() {
    this->is_rotating_right = true;
  }

  // Сущность перестанет поворачиваться направо
  void StopRotatingRight() {
    this->is_rotating_right = false;
  }

  // Сущность начнёт поворачиваться налево
  void StartRotatingLeft() {
    this->is_rotating_left = true;
  }

  // Сущность перестанет поворачиваться налево
  void StopRotatingLeft() {
    this->is_rotating_left = false;
  }

  // Возвращает действие движения, производимое сущностью в данный момент
  ActionMovement GetActionMovement() const;

  // Устанавливает действие движения, производимое сущностью в данный момент
  /// @param new_action_movement Новое действие движения
  void SetActionMovement(ActionMovement new_action_movement);

  // Возвращает ширину сущности
  LONG GetWidth() const;

  // Возвращает высоту сущности
  LONG GetHeight() const;

  // Возвращает параметр масштабирования сущности
  double GetScale() const;

  // Устанавливает параметр масштабирования сущности
  void SetScale(double new_scale);

  // Возвращает радиус круга коллизии объекта (от его центра)
  int GetIntersectRadius() const;

  // Отрисовывает сущность
  void Draw(const HDC& hdc, const HDC& hdc_bits) const;

  // Обрабатывает действия сущности в текущую единицу времени
  void ProcessActions(const std::list<Entity*>& entities, const CRect& game_field);
private:
  // Помечает сущность как уничтоженную
  void Destroy();

  bool IsIntersectsWith(const Entity& entity) const;
};

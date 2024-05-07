#pragma once

// Сущность на поле игры
class Entity {
  public:
    enum class ActionRotation {
      None,
      Right,
      Left
    };
    enum class ActionMovement {
      None,
      ToAngle
    };
  private:
    // Позиция X сущности (относительно левого верхнего угла)
    double x;

    // Позиция Y сущности (относительно левого верхнего угла)
    double y;

    // Направление движения в радианах
    double angle;

    // Скорость движения
    double speed;

    // Информация об изображении сущности
    BITMAP bmp_info;

    // Изображение сущности
    HBITMAP bmp_loaded;

    // Ширина сущности
    LONG width;

    // Высота сущности
    LONG height;

    // Параметр масштабирования сущности (1.0 - без масштабирования)
    double scale;

    ActionRotation action_rotation;

    ActionMovement action_movement;
  protected:
    /// Создаёт новую сущность
    /// @param image_resource_id ID ресурса изображения сущности
    /// @param scale Параметр масштабирования сущности (1.0 - без масштабирования)
    Entity(int image_resource_id, double scale = 1);
  public:
    // Возвращает позицию X сущности
    double GetX() const;

    // Возвращает позицию X сущности (целым числом)
    int GetIntX() const;

    // Возвращает позицию Y сущности
    double GetY() const;

    // Возвращает позицию Y сущности (целым числом)
    int GetIntY() const;

    // Устанавливает позицию X сущности
    void SetX(double new_x);

    // Устанавливает позицию Y сущности
    void SetY(double new_y);

    // Устанавливает новую позицию сущности
    void SetLocation(int new_x, int new_y);

    // Отрисовывает сущность
    void Draw(HDC& hdc, HDC& hdcBits);

    // Двигает сущность с её скоростью и направлением на одну единицу времени
    void ProcessActions();

    // Возвращает ширину сущности
    LONG GetWidth() const;

    // Возвращает высоту сущности
    LONG GetHeight() const;

    // Возвращает угол поворота сущности (в радианах)
    double GetAngle() const;

    // Устанавливает угол поворота сущности (в радианах)
    void SetAngle(double new_angle);

    // Возвращает параметр масштабирования сущности
    double GetScale() const;

    // Устанавливает параметр масштабирования сущности
    void SetScale(double new_scale);

    ActionRotation GetActionRotation();

    void SetActionRotation(ActionRotation new_action_rotation);

    ActionMovement GetActionMovement();

    void SetActionMovement(ActionMovement new_action_movement);
};

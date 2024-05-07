#pragma once
#include <vector>

// Сущность на поле игры
class Entity {
  public:
    // Действие поворота сущности
    enum class ActionRotation {
      // Сущность не поворачивается
      None,
      // Сущность поворачивается по часовой стрелке (направо)
      Right,
      // Сущность поворачивается против часовой стрелки (налево)
      Left
    };

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

    // Действие поворота, производимое сущностью в данный момент
    ActionRotation action_rotation;

    // Действие движения, производимое сущностью в данный момент
    ActionMovement action_movement;

    // Является ли сущность уничтоженной.
    // Уничтоженная сущность не производит действий и не рисуется.
    bool is_destroyed;

    // Помечает сущность как уничтоженную
    void Destroy();
  protected:
    /// Создаёт новую сущность
    /// @param image_resource_id ID ресурса изображения сущности
    /// @param scale Параметр масштабирования сущности (1.0 - без масштабирования)
    Entity(int image_resource_id, double scale = 1);

    // Скорость движения
    double speed;

    std::vector<Entity*> childs;
  public:
    ~Entity();

    // Возвращает позицию X сущности
    double GetX() const;

    // Возвращает позицию X сущности (целым числом)
    int GetIntX() const;

    // Возвращает позицию Y сущности
    double GetY() const;

    // Возвращает позицию Y сущности (целым числом)
    int GetIntY() const;

    /// Устанавливает позицию X сущности
    /// @param new_x Новая позиция X
    void SetX(double new_x);

    /// Устанавливает позицию Y сущности
    /// @param new_x Новая позиция Y
    void SetY(double new_y);

    // Устанавливает новую позицию сущности
    void SetLocation(double new_x, double new_y);

    // Отрисовывает сущность
    void Draw(HDC& hdc, HDC& hdc_bits);

    // Двигает сущность с её скоростью и направлением на одну единицу времени
    void ProcessActions(CRect game_field);

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

    // Возвращает действие поворота, производимое сущностью в данный момент
    ActionRotation GetActionRotation() const;

    // Устанавливает действие поворота, производимое сущностью в данный момент
    /// @param new_action_rotation Новое действие поворота
    void SetActionRotation(ActionRotation new_action_rotation);

    // Возвращает действие движения, производимое сущностью в данный момент
    ActionMovement GetActionMovement() const;

    // Устанавливает действие движения, производимое сущностью в данный момент
    /// @param new_action_movement Новое действие движения
    void SetActionMovement(ActionMovement new_action_movement);

    // Возвращает радиус круга коллизии объекта (от его центра)
    int GetIntersectRadius() const;

    // Является ли сущность уничтоженной.
    // Уничтоженная сущность не производит действий и не рисуется.
    bool IsDestroyed() const;
};

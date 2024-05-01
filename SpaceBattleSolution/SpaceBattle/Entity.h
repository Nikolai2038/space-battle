#pragma once

// Сущность на поле игры
class Entity {
  private:
    // Позиция сущности
    double x;
    double y;

    // Направление движения в радианах
    double angle;

    // Скорость движения
    double speed;

    BITMAP bmp_info;
    HBITMAP bmp_loaded;

    LONG width;
    LONG height;
  protected:
    Entity(int image_resource_id);
  public:
    int GetIntX() const;
    int GetIntY() const;

    double GetX() const;
    double GetY() const;

    void SetX(double new_x);
    void SetY(double new_y);

    // Устанавливает новую позицию сущности
    void SetLocation(int new_x, int new_y);

    // Отрисовывает сущность
    void Draw(HDC hdc) const;

    // Двигает сущность с её скоростью и направлением на одну единицу времени
    void Move();

    LONG GetWidth() const;
    LONG GetHeight() const;

    double GetAngle() const;
    void SetAngle(double new_angle);
};

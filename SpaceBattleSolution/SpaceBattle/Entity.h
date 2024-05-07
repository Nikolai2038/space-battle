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

    double scale;
  protected:
    Entity(int image_resource_id, double scale = 1);
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
    void Draw(HDC& hdc, HDC& hdcBits);

    // Двигает сущность с её скоростью и направлением на одну единицу времени
    void Move();

    // Возвращает ширину сущности
    LONG GetWidth() const;

    // Возвращает высоту сущности
    LONG GetHeight() const;

    // Возвращает угол поворота сущности (в радианах)
    double GetAngle() const;

    // Устанавливает угол поворота сущности (в радианах)
    void SetAngle(double new_angle);

    // Возвращает масштаб сущности
    double GetScale() const;

    // Устанавливает масштаб сущности
    void SetScale(double new_scale);
};

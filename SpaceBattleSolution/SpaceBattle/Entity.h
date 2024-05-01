#pragma once
#include "Point.h"

// Сущность на поле игры
class Entity {
  private:
    // Позиция сущности в относительных координатах
    Point location;

    BITMAP bmp_info;
    HBITMAP bmp_loaded;

    // Скорость движения
    double SPEED = 2;

    // Направление движения в радианах
    double angle = 0;

    LONG width;
    LONG height;
  protected:
    Entity(int image_resource_id);
  public:
    // Возвращает позицию сущности
    Point GetLocation() const;

    // Устанавливает новую позицию сущности
    void SetLocation(const Point new_location);

    // Отрисовывает сущность
    void Draw(CPaintDC& dc, HDC hdc, CRect game_screen_rectangle);

    // Двигает сущность с её скоростью и направлением на одну единицу времени
    void Move();

    LONG GetWidth();
    LONG GetHeight();
};

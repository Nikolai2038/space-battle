#include "pch.h"
#include "Entity.h"

#include <stdexcept>

#include "Config.h"
#include "Globals.h"

Entity::Entity(int image_resource_id) :
    x(0),
    y(0),
    bmp_info(BITMAP()),
    bmp_loaded(nullptr),
    speed(DEFAULT_SPEED),
    angle(0) {
  // Загружаем изображение из ресурса
  CPngImage pngImage;
  pngImage.Load(image_resource_id, AfxGetResourceHandle());

  // Получаем объект изображения
  this->bmp_loaded = static_cast<HBITMAP>(pngImage.Detach());

  // Получаем информацию об изображении
  GetObject(this->bmp_loaded, sizeof(BITMAP), (LPSTR) & this->bmp_info);

  this->width = bmp_info.bmWidth;
  this->height = bmp_info.bmHeight;
}

int Entity::GetIntX() const {
  return static_cast<int>(this->x);
}

int Entity::GetIntY() const {
  return static_cast<int>(this->y);
}

double Entity::GetX() const {
  return x;
}

double Entity::GetY() const {
  return y;
}

void Entity::SetX(double new_x) {
  this->x = new_x;
}

void Entity::SetY(double new_y) {
  this->y = new_y;
}

void Entity::SetLocation(int new_x, int new_y) {
  this->SetX(new_x);
  this->SetY(new_y);
}

void Entity::Draw(HDC& hdc, HDC& hdcBits) {
  // Цвет фона, который будет заменён прозрачным
  RGBQUAD rgb_quad;
  rgb_quad.rgbRed = 0;
  rgb_quad.rgbGreen = 255;
  rgb_quad.rgbBlue = 0;
  rgb_quad.rgbReserved = 0;
  // Получаем код UINT цвета
  const UINT color = rgb_quad.rgbReserved << 32 | rgb_quad.rgbBlue << 16 | rgb_quad.rgbBlue << 16 | rgb_quad.rgbGreen << 8 | rgb_quad.rgbRed;

  SelectObject(hdcBits, this->bmp_loaded);

  // Сохранение параметров ротации поля отрисовки
  XFORM xform_saved;
  GetWorldTransform(hdc, &xform_saved);

  // Матрица ротации
  XFORM xform;
  xform.eM11 = static_cast<FLOAT>(cos(this->angle - PI / 2));
  xform.eM12 = static_cast<FLOAT>(sin(this->angle + PI / 2));
  xform.eM21 = static_cast<FLOAT>(-sin(this->angle + PI / 2));
  xform.eM22 = static_cast<FLOAT>(cos(this->angle - PI / 2));
  xform.eDx = static_cast<FLOAT>(0.0);
  xform.eDy = static_cast<FLOAT>(0.0);

  // Ротация поля отрисовки
  SetGraphicsMode(hdc, GM_ADVANCED);
  SetWorldTransform(hdc, &xform);

  // Реинтерпретирование позиции сущности на повёрнутом поле
  auto entity_rectangle = CRect(this->GetIntX(), this->GetIntY(), this->GetIntX() + this->width, this->GetIntY() + this->height);
  DPtoLP(hdc, reinterpret_cast<LPPOINT>(&entity_rectangle), 2);
  const int entity_center_x = entity_rectangle.left - this->width / 2;
  const int entity_center_y = entity_rectangle.top - this->height / 2;

  // Отрисовка картинки с заменой указанного цвета на прозрачный
  /*TransparentBlt(hdc, entity_center_x, entity_center_y, this->width, this->height,
                 hdcBits, 0, 0, this->width, this->height,
                 color);*/

  // Отрисовка картинки без замены прозрачного цвета
  BitBlt(hdc, entity_center_x, entity_center_y, this->width, this->height, hdcBits, 0, 0, SRCCOPY);

  // Возврат ротации поля отрисовки
  SetWorldTransform(hdc, &xform_saved);
}

void Entity::Move() {
  this->SetX(this->GetX() + cos(angle) * speed);
  this->SetY(this->GetY() - sin(angle) * speed);
}

LONG Entity::GetWidth() const {
  return width;
}

LONG Entity::GetHeight() const {
  return height;
}

double Entity::GetAngle() const {
  return this->angle;
}

void Entity::SetAngle(double new_angle) {
  this->angle = new_angle;
}

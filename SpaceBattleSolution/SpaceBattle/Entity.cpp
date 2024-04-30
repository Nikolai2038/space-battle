#include "pch.h"
#include "Entity.h"

#include <stdexcept>

Entity::Entity(int image_resource_id) :
    location(Point()),
    bmp_info(BITMAP()),
    bmp_loaded(nullptr) {
  // Загружаем изображение из ресурса
  CPngImage pngImage;
  pngImage.Load(image_resource_id, AfxGetResourceHandle());

  // Получаем объект изображения
  this->bmp_loaded = static_cast<HBITMAP>(pngImage.Detach());

  // Получаем информацию об изображении
  GetObject(this->bmp_loaded, sizeof(BITMAP), (LPSTR) & this->bmp_info);
}

Point Entity::GetLocation() const {
  return this->location;
}

void Entity::SetLocation(const Point new_location) {
  this->location = new_location;
}

void Entity::Draw(CPaintDC& dc, HDC hdc, CRect game_screen_rectangle) {
  int x = game_screen_rectangle.TopLeft().x + this->location.GetIntX();
  int y = game_screen_rectangle.TopLeft().y + this->location.GetIntY();

  HDC hdcBits = ::CreateCompatibleDC(hdc);

  // Выбрать объект
  SelectObject(hdcBits, this->bmp_loaded);

  // Вывести изображение
  BitBlt(hdc, x, y, x + this->bmp_info.bmWidth, this->bmp_info.bmHeight, hdcBits, 0, 0, SRCCOPY);

  DeleteDC(hdcBits);
}

void Entity::Move() {
  this->location.SetX(this->location.GetX() + cos(angle) * SPEED);
  this->location.SetY(this->location.GetY() - sin(angle) * SPEED);
}

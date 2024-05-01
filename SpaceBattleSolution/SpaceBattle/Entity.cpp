#include "pch.h"
#include "Entity.h"

#include <stdexcept>

#include "GraphicsHelper.h"

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

  RGBQUAD rgbQuad = RGBQUAD();
  rgbQuad.rgbRed = 0;
  rgbQuad.rgbGreen = 255;
  rgbQuad.rgbBlue = 0;
  rgbQuad.rgbReserved = 0;

  UINT color = (rgbQuad.rgbReserved << 32) | (rgbQuad.rgbBlue << 16) | (rgbQuad.rgbBlue << 16) | (rgbQuad.rgbGreen << 8) | rgbQuad.rgbRed;

  // HBITMAP rotated = GraphicsHelper::GetRotatedBitmapNT(this->bmp_loaded, 2, color);

  HDC hdcBits = ::CreateCompatibleDC(hdc);
  SelectObject(hdcBits, this->bmp_loaded);

  // ========================================
  HDC hdc_used = hdc;
  CRect rect_used = game_screen_rectangle;
  // CRect rect_used = CRect(0, 0, this->bmp_info.bmWidth, this->bmp_info.bmHeight);

  XFORM xform_saved;
  GetWorldTransform(hdc_used, &xform_saved);

  SetGraphicsMode(hdc_used, GM_ADVANCED);
  // SetMapMode(hdc_used, MM_LOENGLISH);

  XFORM xform;
  xform.eM11 = (FLOAT)0.8660;
  xform.eM12 = (FLOAT)0.5000;
  xform.eM21 = (FLOAT)-0.5000;
  xform.eM22 = (FLOAT)0.8660;

  /*xform.eM11 = (FLOAT)0;
  xform.eM12 = (FLOAT)0;
  xform.eM21 = (FLOAT)0;
  xform.eM22 = (FLOAT)0;*/

  xform.eDx = (FLOAT)0.0;
  xform.eDy = (FLOAT)0.0;
  SetWorldTransform(hdc_used, &xform);
  DPtoLP(hdc_used, (LPPOINT)&rect_used, 2);

  // Select a hollow brush.
  SelectObject(hdc_used, GetStockObject(HOLLOW_BRUSH));

  float target_x1 = rect_used.TopLeft().x + rect_used.right / 2;
  float target_y1 = rect_used.TopLeft().y + rect_used.bottom / 2;
  // target_x1 = 0;
  // target_y1 = 0;

  // Draw the exterior circle.
  Ellipse(hdc_used, (target_x1 - 100), (target_y1 + 100),
          (target_x1 + 100), (target_y1 - 100));
  // Draw the interior circle.
  Ellipse(hdc_used, (target_x1 - 94), (target_y1 + 94),
          (target_x1 + 94), (target_y1 - 94));
  // Draw the key.
  Rectangle(hdc_used, (target_x1 - 13), (target_y1 + 113),
            (target_x1 + 13), (target_y1 + 50));
  Rectangle(hdc_used, (target_x1 - 13), (target_y1 + 96),
            (target_x1 + 13), (target_y1 + 50));
  // Draw the horizontal lines.
  MoveToEx(hdc_used, (target_x1 - 150), (target_y1 + 0), NULL);
  LineTo(hdc_used, (target_x1 - 16), (target_y1 + 0));
  MoveToEx(hdc_used, (target_x1 - 13), (target_y1 + 0), NULL);
  LineTo(hdc_used, (target_x1 + 13), (target_y1 + 0));
  MoveToEx(hdc_used, (target_x1 + 16), (target_y1 + 0), NULL);
  LineTo(hdc_used, (target_x1 + 150), (target_y1 + 0));
  // Draw the vertical lines.
  MoveToEx(hdc_used, (target_x1 + 0), (target_y1 - 150), NULL);
  LineTo(hdc_used, (target_x1 + 0), (target_y1 - 16));
  MoveToEx(hdc_used, (target_x1 + 0), (target_y1 - 13), NULL);
  LineTo(hdc_used, (target_x1 + 0), (target_y1 + 13));
  MoveToEx(hdc_used, (target_x1 + 0), (target_y1 + 16), NULL);
  LineTo(hdc_used, (target_x1 + 0), (target_y1 + 150));

  SetWorldTransform(hdc_used, &xform_saved);
  // ========================================

  /*TransparentBlt(hdc, x, y, this->bmp_info.bmWidth, this->bmp_info.bmHeight,
                 hdcBits, 0, 0, this->bmp_info.bmWidth, this->bmp_info.bmHeight,
                 color);*/

  DeleteDC(hdcBits);
}

void Entity::Move() {
  this->location.SetX(this->location.GetX() + cos(angle) * SPEED);
  this->location.SetY(this->location.GetY() - sin(angle) * SPEED);
}

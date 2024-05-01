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
  SelectObject(hdcBits, this->bmp_loaded);

  // ========================================
  // Вывести изображение
  // BitBlt(hdc, x, y, x + this->bmp_info.bmWidth, y + this->bmp_info.bmHeight, hdcBits, 0, 0, SRCCOPY);

  // ========================================
  RGBQUAD rgbQuad = RGBQUAD();
  rgbQuad.rgbRed = 0;
  rgbQuad.rgbGreen = 255;
  rgbQuad.rgbBlue = 0;
  rgbQuad.rgbReserved = 0;

  UINT color = (rgbQuad.rgbReserved << 32) | (rgbQuad.rgbBlue << 16) | (rgbQuad.rgbBlue << 16) | (rgbQuad.rgbGreen << 8) | rgbQuad.rgbRed;

  TransparentBlt(hdc, x, y, this->bmp_info.bmWidth, this->bmp_info.bmHeight,
                 hdcBits, 0, 0, this->bmp_info.bmWidth, this->bmp_info.bmHeight,
                 color);
  // ========================================

  // ========================================

  /*CDC* pdc = CDC::FromHandle(dc);
  CDC* hDC = CDC::FromHandle(hdcBits);

  const CRect rc_bounds = CRect(x, y, x + this->bmp_info.bmWidth, y + this->bmp_info.bmHeight);
  constexpr COLORREF c_transparent_color = 216;

  CBitmap bm_and_back, bm_and_object, bm_and_mem, bm_work_copy;
  CDC hdc_mem, hdc_back, hdc_object, hdc_work_copy;

  // Create some DCs to hold temporary data.
  hdc_back.CreateCompatibleDC(pdc);
  hdc_object.CreateCompatibleDC(pdc);
  hdc_mem.CreateCompatibleDC(pdc);
  hdc_work_copy.CreateCompatibleDC(pdc);

  // Create a bitmap for each DC. DCs are required for a number of GDI functions.

  // Monochrome DC
  bm_and_back.CreateBitmap(rc_bounds.Width(), rc_bounds.Height(), 1, 1, NULL);

  // Monochrome DC
  bm_and_object.CreateBitmap(rc_bounds.Width(), rc_bounds.Height(), 1, 1, NULL);

  bm_and_mem.CreateCompatibleBitmap(pdc, rc_bounds.Width(), rc_bounds.Height());
  bm_work_copy.CreateCompatibleBitmap(hDC, rc_bounds.Width(), rc_bounds.Height());

  // Each DC must select a bitmap object to store pixel data.
  CBitmap* pOldbmBack = hdc_back.SelectObject(&bm_and_back);
  CBitmap* pOldbmObject = hdc_object.SelectObject(&bm_and_object);
  CBitmap* pOldbmMem = hdc_mem.SelectObject(&bm_and_mem);

  // Transfer bitmap to working object
  CBitmap* pOldbmWorkCopy = hdc_work_copy.SelectObject(&bm_work_copy);
  hdc_work_copy.BitBlt(0, 0, rc_bounds.Width(), rc_bounds.Height(), hDC, 0, 0, SRCCOPY);

  hdc_work_copy.AlphaBlend()

  // Set the background color of the source DC to the color contained in the parts of the bitmap that should be transparent
  hdc_work_copy.SetBkColor(c_transparent_color);

  // Create the object mask for the bitmap by performing a BitBlt
  // from the source bitmap to a monochrome bitmap.
  hdc_object.BitBlt(0, 0, rc_bounds.Width(), rc_bounds.Height(), &hdc_work_copy, 0, 0, SRCCOPY);

  // Set the background color of the source DC back to the original color.
  hdc_work_copy.SetBkColor(hDC->GetBkColor());

  // Create the inverse of the object mask.
  hdc_back.BitBlt(0, 0, rc_bounds.Width(), rc_bounds.Height(), &hdc_object, 0, 0, NOTSRCCOPY);

  // Copy the background of the main DC to the destination.
  hdc_mem.BitBlt(0, 0, rc_bounds.Width(), rc_bounds.Height(), pdc, rc_bounds.left, rc_bounds.top, SRCCOPY);

  // Mask out the places where the bitmap will be placed.
  hdc_mem.BitBlt(0, 0, rc_bounds.Width(), rc_bounds.Height(), &hdc_object, 0, 0, SRCAND);

  // Mask out the transparent colored pixels on the bitmap.
  hdc_work_copy.BitBlt(0, 0, rc_bounds.Width(), rc_bounds.Height(), &hdc_back, 0, 0, SRCAND);

  // XOR the bitmap with the background on the destination DC.
  hdc_mem.BitBlt(0, 0, rc_bounds.Width(), rc_bounds.Height(), &hdc_work_copy, 0, 0, SRCPAINT);

  // Copy the destination to the screen.
  pdc->BitBlt(rc_bounds.left, rc_bounds.top, rc_bounds.Width(), rc_bounds.Height(), &hdc_mem, 0, 0, SRCCOPY);

  hdc_back.SelectObject(pOldbmBack);
  hdc_object.SelectObject(pOldbmObject);
  hdc_mem.SelectObject(pOldbmMem);
  hdc_work_copy.SelectObject(pOldbmWorkCopy);*/

  DeleteDC(hdcBits);
}

void Entity::Move() {
  this->location.SetX(this->location.GetX() + cos(angle) * SPEED);
  this->location.SetY(this->location.GetY() - sin(angle) * SPEED);
}

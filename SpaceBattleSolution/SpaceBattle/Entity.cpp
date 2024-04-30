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
  /*
  // Вывести изображение
  BitBlt(hdc, x, y, x + this->bmp_info.bmWidth, this->bmp_info.bmHeight, hdcBits, 0, 0, SRCCOPY);
*/

  CDC* pdc = CDC::FromHandle(dc);
  CDC* hDC = CDC::FromHandle(hdcBits);
  CRect rcBounds = CRect(x, y, x + this->bmp_info.bmWidth, this->bmp_info.bmHeight);
  COLORREF cTransparentColor = 0;

  COLORREF cColor;
  CBitmap bmAndBack, bmAndObject, bmAndMem, bmWorkCopy;
  CBitmap *pOldbmMem, *pOldbmBack, *pOldbmObject, *pOldbmWorkCopy;
  CDC hdcMem, hdcBack, hdcObject, hdcWorkCopy;

  // Create some DCs to hold temporary data.
  hdcBack.CreateCompatibleDC(pdc);
  hdcObject.CreateCompatibleDC(pdc);
  hdcMem.CreateCompatibleDC(pdc);
  hdcWorkCopy.CreateCompatibleDC(pdc);

  // Create a bitmap for each DC. DCs are required for a number of GDI functions.

  // Monochrome DC
  bmAndBack.CreateBitmap(rcBounds.Width(), rcBounds.Height(), 1, 1, NULL);

  // Monochrome DC
  bmAndObject.CreateBitmap(rcBounds.Width(), rcBounds.Height(), 1, 1,
                           NULL);

  bmAndMem.CreateCompatibleBitmap(pdc, rcBounds.Width(),
                                  rcBounds.Height());
  bmWorkCopy.CreateCompatibleBitmap(hDC, rcBounds.Width(),
                                    rcBounds.Height());

  // Each DC must select a bitmap object to store pixel data.
  pOldbmBack = hdcBack.SelectObject(&bmAndBack);
  pOldbmObject = hdcObject.SelectObject(&bmAndObject);
  pOldbmMem = hdcMem.SelectObject(&bmAndMem);

  // Transfer bitmap to working object
  pOldbmWorkCopy = hdcWorkCopy.SelectObject(&bmWorkCopy);
  hdcWorkCopy.BitBlt(0, 0, rcBounds.Width(), rcBounds.Height(), hDC, 0,
                     0, SRCCOPY);

  // Set the background color of the source DC to the color.
  // contained in the parts of the bitmap that should be transparent
  cColor = hdcWorkCopy.SetBkColor(cTransparentColor);

  // Create the object mask for the bitmap by performing a BitBlt
  // from the source bitmap to a monochrome bitmap.
  hdcObject.BitBlt(0, 0, rcBounds.Width(), rcBounds.Height(),
                   &hdcWorkCopy, 0, 0, SRCCOPY);

  // Set the background color of the source DC back to the original color.
  hdcWorkCopy.SetBkColor(hDC->GetBkColor());

  // Create the inverse of the object mask.
  hdcBack.BitBlt(0, 0, rcBounds.Width(), rcBounds.Height(), &hdcObject, 0,
                 0, NOTSRCCOPY);

  // Copy the background of the main DC to the destination.
  hdcMem.BitBlt(0, 0, rcBounds.Width(), rcBounds.Height(), pdc,
                rcBounds.left, rcBounds.top, SRCCOPY);

  // Mask out the places where the bitmap will be placed.
  hdcMem.BitBlt(0, 0, rcBounds.Width(), rcBounds.Height(), &hdcObject, 0,
                0, SRCAND);

  // Mask out the transparent colored pixels on the bitmap.
  hdcWorkCopy.BitBlt(0, 0, rcBounds.Width(), rcBounds.Height(), &hdcBack,
                     0, 0, SRCAND);

  // XOR the bitmap with the background on the destination DC.
  hdcMem.BitBlt(0, 0, rcBounds.Width(), rcBounds.Height(), &hdcWorkCopy,
                0, 0, SRCPAINT);

  // Copy the destination to the screen.
  pdc->BitBlt(rcBounds.left, rcBounds.top, rcBounds.Width(),
              rcBounds.Height(), &hdcMem, 0, 0, SRCCOPY);

  hdcBack.SelectObject(pOldbmBack);
  hdcObject.SelectObject(pOldbmObject);
  hdcMem.SelectObject(pOldbmMem);
  hdcWorkCopy.SelectObject(pOldbmWorkCopy);

  DeleteDC(hdcBits);
}

void Entity::Move() {
  this->location.SetX(this->location.GetX() + cos(angle) * SPEED);
  this->location.SetY(this->location.GetY() - sin(angle) * SPEED);
}

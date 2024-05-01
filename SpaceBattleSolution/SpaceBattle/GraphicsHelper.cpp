#include "pch.h"
#include "GraphicsHelper.h"

// GetRotatedBitmapNT	- Create a new bitmap with rotated image
// Returns		- Returns new bitmap with rotated image
// hBitmap		- Bitmap to rotate
// radians		- Angle of rotation in radians
// clrBack		- Color of pixels in the resulting bitmap that do
//			  not get covered by source pixels
HBITMAP GraphicsHelper::GetRotatedBitmapNT(HBITMAP hBitmap, float radians, COLORREF clrBack) {
  // Create a memory DC compatible with the display
  CDC sourceDC, destDC;
  sourceDC.CreateCompatibleDC(NULL);
  destDC.CreateCompatibleDC(NULL);

  // Get logical coordinates
  BITMAP bm;
  ::GetObject(hBitmap, sizeof(bm), &bm);

  float cosine = (float)cos(radians);
  float sine = (float)sin(radians);

  // Compute dimensions of the resulting bitmap
  // First get the coordinates of the 3 corners other than origin
  int x1 = (int)(bm.bmHeight * sine);
  int y1 = (int)(bm.bmHeight * cosine);
  int x2 = (int)(bm.bmWidth * cosine + bm.bmHeight * sine);
  int y2 = (int)(bm.bmHeight * cosine - bm.bmWidth * sine);
  int x3 = (int)(bm.bmWidth * cosine);
  int y3 = (int)(-bm.bmWidth * sine);

  int minx = min(0, min(x1, min(x2, x3)));
  int miny = min(0, min(y1, min(y2, y3)));
  int maxx = max(0, max(x1, max(x2, x3)));
  int maxy = max(0, max(y1, max(y2, y3)));

  int w = maxx - minx;
  int h = maxy - miny;

  // Create a bitmap to hold the result
  HBITMAP hbmResult = ::CreateCompatibleBitmap(CClientDC(NULL), w, h);

  HBITMAP hbmOldSource = (HBITMAP)::SelectObject(sourceDC.m_hDC, hBitmap);
  HBITMAP hbmOldDest = (HBITMAP)::SelectObject(destDC.m_hDC, hbmResult);

  // Draw the background color before we change mapping mode
  HBRUSH hbrBack = CreateSolidBrush(clrBack);
  HBRUSH hbrOld = (HBRUSH)::SelectObject(destDC.m_hDC, hbrBack);
  destDC.PatBlt(0, 0, w, h, PATCOPY);
  ::DeleteObject(::SelectObject(destDC.m_hDC, hbrOld));

  // We will use world transform to rotate the bitmap
  SetGraphicsMode(destDC.m_hDC, GM_ADVANCED);
  XFORM xform;
  xform.eM11 = cosine;
  xform.eM12 = -sine;
  xform.eM21 = sine;
  xform.eM22 = cosine;
  xform.eDx = (float)-minx;
  xform.eDy = (float)-miny;

  SetWorldTransform(destDC.m_hDC, &xform);

  // Now do the actual rotating - a pixel at a time
  destDC.BitBlt(0, 0, bm.bmWidth, bm.bmHeight, &sourceDC, 0, 0, SRCCOPY);

  // Restore DCs
  ::SelectObject(sourceDC.m_hDC, hbmOldSource);
  ::SelectObject(destDC.m_hDC, hbmOldDest);

  return hbmResult;
}

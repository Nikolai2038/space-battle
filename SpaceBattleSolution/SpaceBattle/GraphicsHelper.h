#pragma once
class GraphicsHelper {
  public:
    static RGBQUAD rgbQuad;
    static HBITMAP GetRotatedBitmapNT(HBITMAP hBitmap, float radians, COLORREF clrBack);
};

#pragma once
class GraphicsHelper {
  public:
    // Load png into CImage from resource
    static bool Load(CImage* pimage, LPCTSTR lpszResourceName, HINSTANCE hinstRes);
};

#include "pch.h"
#include "GraphicsHelper.h"

bool GraphicsHelper::Load(CImage* pimage, LPCTSTR lpszResourceName, HINSTANCE hinstRes) {
  if (hinstRes == NULL) {
    hinstRes = AfxFindResourceHandle(lpszResourceName, _T("PNG"));
  }

  HRSRC hRsrc = ::FindResource(hinstRes, lpszResourceName, _T("PNG"));
  if (hRsrc == NULL) {
    return false;
  }

  HGLOBAL hGlobal = LoadResource(hinstRes, hRsrc);
  if (hGlobal == NULL) {
    return false;
  }

  LPBYTE lpBuffer = (LPBYTE)::LockResource(hGlobal);
  if (lpBuffer == NULL) {
    FreeResource(hGlobal);
    return false;
  }

  bool bRes = false;
  {
    UINT uiSize = ::SizeofResource(hinstRes, hRsrc);

    HGLOBAL hRes = ::GlobalAlloc(GMEM_MOVEABLE, uiSize);
    if (hRes != NULL) {
      IStream* pStream = NULL;
      LPVOID lpResBuffer = ::GlobalLock(hRes);
      ASSERT(lpResBuffer != NULL);

      memcpy(lpResBuffer, lpBuffer, uiSize);

      HRESULT hResult = ::CreateStreamOnHGlobal(hRes, TRUE, &pStream);

      if (hResult == S_OK) {
        pimage->Load(pStream);
        pStream->Release();
        bRes = true;
      }
    }
  }

  UnlockResource(hGlobal);
  FreeResource(hGlobal);

  return bRes;
}

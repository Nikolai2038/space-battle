#pragma once
#include "afxdialogex.h"

// CSpaceBattleDlgGame dialog

class CSpaceBattleDlgGame : public CDialogEx {
  DECLARE_DYNAMIC(CSpaceBattleDlgGame)
public:
  CSpaceBattleDlgGame(CWnd* pParent = nullptr); // standard constructor
  virtual ~CSpaceBattleDlgGame();

// Dialog Data
#ifdef AFX_DESIGN_TIME
  enum { IDD = IDD_DIALOG_GAME };
#endif
protected:
  virtual void DoDataExchange(CDataExchange* pDX); // DDX/DDV support

  DECLARE_MESSAGE_MAP()
};

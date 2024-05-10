#pragma once

#include "afxdialogex.h"

class CSpaceBattleDlgRules final : public CDialogEx {
  DECLARE_DYNAMIC(CSpaceBattleDlgRules)
public:
  explicit CSpaceBattleDlgRules(CWnd* p_parent = nullptr); // standard constructor
  ~CSpaceBattleDlgRules() override;

// Dialog Data
#ifdef AFX_DESIGN_TIME
  enum { IDD = IDD_DIALOG_RULES };
#endif
protected:
  // »конка окна
  HICON window_icon;

  // DDX/DDV support
  void DoDataExchange(CDataExchange* p_dx) override;

  DECLARE_MESSAGE_MAP()
public:
  afx_msg void OnBnClickedButtonReturnToTheMenu();
  BOOL OnInitDialog() override;
};

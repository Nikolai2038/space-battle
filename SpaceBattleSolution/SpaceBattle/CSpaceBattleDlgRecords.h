#pragma once

#include "afxdialogex.h"

class CSpaceBattleDlgRecords final : public CDialogEx {
  DECLARE_DYNAMIC(CSpaceBattleDlgRecords)
public:
  explicit CSpaceBattleDlgRecords(CWnd* p_parent = nullptr); // standard constructor
  ~CSpaceBattleDlgRecords() override;

// Dialog Data
#ifdef AFX_DESIGN_TIME
  enum { IDD = IDD_DIALOG_RECORDS };
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
private:
  CListBox clistbox_records;
};

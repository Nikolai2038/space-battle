#pragma once

// CSpaceBattleDlgMenu dialog
class CSpaceBattleDlgMenu : public CDialogEx {
  // Construction
public:
  CSpaceBattleDlgMenu(CWnd* pParent = nullptr); // standard constructor

  // Dialog Data
#ifdef AFX_DESIGN_TIME
  enum { IDD = IDD_DIALOG_MENU };
#endif
protected:
  virtual void DoDataExchange(CDataExchange* pDX); // DDX/DDV support

  // Implementation
protected:
  HICON m_hIcon;

  // Generated message map functions
  virtual BOOL OnInitDialog();
  afx_msg void OnPaint();
  afx_msg HCURSOR OnQueryDragIcon();
  DECLARE_MESSAGE_MAP()
public:
  afx_msg void OnBnClickedButtonPlay();
  afx_msg void OnBnClickedButtonRules();
  afx_msg void OnBnClickedButtonRecords();
  afx_msg void OnBnClickedButtonExit();
};

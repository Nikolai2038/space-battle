#pragma once

class CSpaceBattleDlgMenu : public CDialogEx {
public:
  CSpaceBattleDlgMenu(CWnd* pParent = nullptr);

// Dialog Data
#ifdef AFX_DESIGN_TIME
  enum { IDD = IDD_SPACEBATTLE_DIALOG };
#endif
protected:
  virtual void DoDataExchange(CDataExchange* pDX); // DDX/DDV support
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

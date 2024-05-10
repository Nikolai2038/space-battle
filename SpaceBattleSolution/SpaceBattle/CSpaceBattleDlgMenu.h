#pragma once

class CSpaceBattleDlgMenu : public CDialogEx {
private:
  // Изображение-превью игры в меню
  CStatic cstatic_intro_image;
public:
  CSpaceBattleDlgMenu(CWnd* pParent = nullptr);
  ~CSpaceBattleDlgMenu();
// Dialog Data
#ifdef AFX_DESIGN_TIME
  enum { IDD = IDD_SPACEBATTLE_DIALOG };
#endif
protected:
  virtual void DoDataExchange(CDataExchange* p_dx); // DDX/DDV support
protected:
  // Иконка окна
  HICON window_icon;

  // Превью игры
  HBITMAP intro_image_bitmap;

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

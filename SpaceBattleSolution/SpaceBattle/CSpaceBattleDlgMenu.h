#pragma once

class CSpaceBattleDlgMenu final : public CDialogEx {
private:
  // Изображение-превью игры в меню
  CStatic cstatic_intro_image;
public:
  explicit CSpaceBattleDlgMenu(CWnd* p_parent = nullptr);
  ~CSpaceBattleDlgMenu() override;
// Dialog Data
#ifdef AFX_DESIGN_TIME
  enum { IDD = IDD_SPACEBATTLE_DIALOG };
#endif
protected:
  // DDX/DDV support
  void DoDataExchange(CDataExchange* p_dx) override;
protected:
  // Иконка окна
  HICON window_icon;

  // Превью игры
  HBITMAP intro_image_bitmap;

  // Generated message map functions
  BOOL OnInitDialog() override;
  afx_msg void OnPaint();
  afx_msg HCURSOR OnQueryDragIcon();
  DECLARE_MESSAGE_MAP()
public:
  afx_msg void OnBnClickedButtonPlay();
  afx_msg void OnBnClickedButtonRules();
  afx_msg void OnBnClickedButtonRecords();
  afx_msg void OnBnClickedButtonExit();
};

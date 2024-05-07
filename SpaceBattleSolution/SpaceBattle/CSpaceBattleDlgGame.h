#pragma once
#include "afxdialogex.h"
#include "Enemy.h"
#include "Player.h"

// CSpaceBattleDlgGame dialog

class CSpaceBattleDlgGame : public CDialogEx {
  private:
    DECLARE_DYNAMIC(CSpaceBattleDlgGame)

    enum Timers {
      TIMER_CLOCK,
      TIMER_REDRAW
    };
    HDC hdc;
    HDC hdcBits = nullptr;
    CWnd* game_screen;
    CRect game_screen_rectangle;
    CRect game_screen_rectangle_window;

    // Нужно ли очистить фон всего окна перед следующей отрисовкой объектов
    bool need_to_clear_screen = true;
  public:
    CSpaceBattleDlgGame(CWnd* pParent = nullptr); // standard constructor
    virtual ~CSpaceBattleDlgGame();

    void GameStart();
    void UpdateGameScreenInfo();

// Dialog Data
#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_DIALOG_GAME };
#endif
  protected:
    virtual void DoDataExchange(CDataExchange* pDX); // DDX/DDV support

    DECLARE_MESSAGE_MAP()
  public:
    afx_msg void OnBnClickedButtonReturnToTheMenu();
    afx_msg void OnPaint();
    Player player;
    Enemy enemy;
    virtual BOOL OnInitDialog();
    afx_msg void OnTimer(UINT_PTR nIDEvent);
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
    afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg
      afx_msg virtual BOOL
      PreTranslateMessage(MSG* pMsg);
};

#pragma once
#include <list>
#include <vector>

#include "afxdialogex.h"
#include "Enemy.h"
#include "Player.h"

// CSpaceBattleDlgGame dialog

class CSpaceBattleDlgGame : public CDialogEx {
  private:
    DECLARE_DYNAMIC(CSpaceBattleDlgGame)

    enum class Timers {
      TIMER_CLOCK,
      TIMER_REDRAW,
      TIMER_GAMETIME
    };
    HDC hdc;
    HDC hdcBits = nullptr;
    CWnd* game_screen;

    // Область отрисовки игрового поля
    CRect game_screen_rectangle;

    // Область всего диалога с игровым полем
    CRect game_screen_rectangle_window;

    // Нужно ли очистить фон всего окна перед следующей отрисовкой объектов
    bool need_to_clear_screen = true;

    enum class GameState {
      CREATED,
      PAUSED,
      PLAYING,
      FINISHED,
    };

    GameState game_state;

    CButton button_pause_or_resume_game;
    CButton button_start_or_end_game;

    int time_playing_seconds_passed;
    CStatic text_time_playing;

    void PauseGame();
    void ResumeGame();
    void EndGameAndDoNotSaveRecord();
    void EndGameAndSaveRecord();
  public:
    CSpaceBattleDlgGame(CWnd* pParent = nullptr); // standard constructor
    virtual ~CSpaceBattleDlgGame();

    void GameResume();
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

    // Игрок
    Player* player;
    // Список всех сущностей (включая игрока)
    std::list<Entity*> entities;

    virtual BOOL OnInitDialog();
    afx_msg void OnTimer(UINT_PTR nIDEvent);
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
    afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg
      afx_msg virtual BOOL
      PreTranslateMessage(MSG* pMsg);
  private:
    void CreateNewEnemy();
  public:
    afx_msg void OnBnClickedButtonPauseOrResumeGame();
    afx_msg void OnBnClickedButtonStartOrEndGame();
    afx_msg void OnClose();
};

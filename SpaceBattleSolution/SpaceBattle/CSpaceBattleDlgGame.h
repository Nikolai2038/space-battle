#pragma once
#include <list>

#include "afxdialogex.h"
#include "Player.h"

class CSpaceBattleDlgGame : public CDialogEx {
  private:
    enum class Timers;
    enum class GameState;

    DECLARE_DYNAMIC(CSpaceBattleDlgGame)

    HDC hdc;
    HDC hdcBits = nullptr;
    CWnd* game_screen;

    // ������� ��������� �������� ����
    CRect game_screen_rectangle;

    // ������� ����� ������� � ������� �����
    CRect game_screen_rectangle_window;

    // ����� �� �������� ��� ����� ���� ����� ��������� ���������� ��������
    bool need_to_clear_screen = true;

    GameState game_state;

    CButton button_pause_or_resume_game;
    CButton button_start_or_end_game;

    int time_playing_seconds_passed;
    CStatic text_time_playing;

    void PauseGame();
    void ResumeGame();
    void EndGameAndDoNotSaveRecord();
    void EndGameAndSaveRecord();
    void CreateNewEnemy();
  protected:
    virtual void DoDataExchange(CDataExchange* pDX); // DDX/DDV support

    DECLARE_MESSAGE_MAP()
  public:
    CSpaceBattleDlgGame(CWnd* pParent = nullptr); // standard constructor
    virtual ~CSpaceBattleDlgGame();

    void GameResume();
    void UpdateGameScreenInfo();

// Dialog Data
#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_DIALOG_GAME };
#endif

    afx_msg void OnBnClickedButtonReturnToTheMenu();
    afx_msg void OnPaint();

    // �����
    Player* player;
    // ������ ���� ��������� (������� ������)
    std::list<Entity*> entities;

    virtual BOOL OnInitDialog();
    afx_msg void OnTimer(UINT_PTR nIDEvent);
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
    afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg virtual BOOL PreTranslateMessage(MSG* pMsg);
    afx_msg void OnBnClickedButtonPauseOrResumeGame();
    afx_msg void OnBnClickedButtonStartOrEndGame();
    afx_msg void OnClose();
};

#pragma once

#include "afxdialogex.h"
#include "Player.h"
#include <list>

class CSpaceBattleDlgGame : public CDialogEx {
private:
  DECLARE_DYNAMIC(CSpaceBattleDlgGame)

  // �������������� ��������
  enum class Timers {
    // ������������� ������� �������� ���������
    TimerClock,

    // ������������� ������� ���������
    TimerRedraw,

    // ������������� ������� ������� ����
    TimerPlaying
  };

  // �������������� ��������� ����
  enum class GameState {
    // ���� �������
    Created,

    // ���� �������������� (�����)
    Paused,

    // ���� ���
    Playing,

    // ���� ���������
    Finished,
  };

  HDC hdc;

  HDC hdc_bits = nullptr;

  CWnd* game_screen;

  // ������� ��������� �������� ����
  CRect game_screen_rectangle;

  // ������� ����� ������� � ������� �����
  CRect game_screen_rectangle_window;

  // ����� �� �������� ��� ����� ���� ����� ��������� ���������� ��������
  bool need_to_clear_screen = true;

  // ��������� ����
  GameState game_state;

  int time_playing_seconds_passed;

  // ������ �����/����������� ����
  CButton button_pause_or_resume_game;

  // ������ ������/���������� ����
  CButton button_start_or_end_game;

  // ��������� ���� �� �������� ����
  CStatic text_time_playing;

  // ������ ���� ��������� (������� ������)
  std::list<Entity*> entities;

  // �����
  Player* player;
protected:
  void DoDataExchange(CDataExchange* p_dx) override; // DDX/DDV support

  DECLARE_MESSAGE_MAP()
public:
  // �����������
  explicit CSpaceBattleDlgGame(CWnd* p_parent = nullptr);

  // ����������
  ~CSpaceBattleDlgGame() override;

// Dialog Data
#ifdef AFX_DESIGN_TIME
  enum { IDD = IDD_DIALOG_GAME };
#endif

  // ������� �������� ����������� ����
  afx_msg BOOL OnInitDialog() override;

  // ������� ��������� �������� �����
  afx_msg void OnSize(UINT n_type, int cx, int cy);

  // ������� ������� ����.
  // ������� ��������� �� ���������, ��� ��� � ��� ����������� ���� ���������.
  afx_msg BOOL OnEraseBkgnd(CDC* p_dc);

  // ������� ��������� �����
  afx_msg void OnPaint();

  // ����� ��������� ������� �����.
  // ���������� ��� ��� ������� ������� ������, ��� ��� � OnKeyDown ��� �� �������������.
  afx_msg BOOL PreTranslateMessage(MSG* p_msg) override;

  // ������� ������������� �������
  afx_msg void OnTimer(UINT_PTR n_id_event);

  // ������� �������� ����
  afx_msg void OnClose();

  // ������� ������� �� ������ �������� � ����
  afx_msg void OnBnClickedButtonReturnToTheMenu();

  // ������� ������� �� ������ �����/������������� ����
  afx_msg void OnBnClickedButtonPauseOrResumeGame();

  // ������� ������� �� ������ ������/���������� ����
  afx_msg void OnBnClickedButtonStartOrEndGame();
private:
  // ��������� ���������� �� ������� ����
  // (��������, ��� ��������� ��� �������� - ������������� ������� ���������)
  void UpdateGameScreenInfo();

  // ���������������� ���� (�����)
  void PauseGame();

  // ������������ ���������������� ����
  void ResumeGame();

  // ��������� ���� ��� ���������� �������
  void EndGameAndDoNotSaveRecord();

  // ��������� ���� � ����������� �������
  void EndGameAndSaveRecord();

  // ������ ������ ����� �� ����
  void CreateNewEnemy();
};

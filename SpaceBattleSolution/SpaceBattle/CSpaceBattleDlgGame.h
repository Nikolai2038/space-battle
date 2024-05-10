#pragma once

#include "afxdialogex.h"
#include "Player.h"
#include <list>

#include "Globals.h"

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
    TimerPlaying,

    // ������������� ������� ������ ������ � ������
    TimerGarbageCollector
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

  HDC hdc_bits;

  CWnd* game_screen;

  // ������� ��������� �������� ����
  CRect game_screen_rectangle;

  // ������� ����� ������� � ������� �����
  CRect game_screen_rectangle_window;

  // ��������� ����
  GameState game_state;

  int time_playing_seconds_passed;

  // ������ �����/����������� ����
  CButton button_pause_or_resume_game;

  // ������ ������/���������� ����
  CButton button_start_or_end_game;

  // ��������� ���� � ����������� ������������ �����
  CStatic cstatic_points_earned;

  // ��������� ���� � ����������� ������������ ������
  CStatic cstatic_enemies_defeated;

  // ��������� ���� � ����������� �������� ������
  CStatic cstatic_health_left;

  // ��������� ���� �� �������� ����
  CStatic cstatic_time_playing;

  // ������ ���� ��������� (������� ������)
  std::list<Entity*> entities;

  // �����
  Player* player;

  // ���������� ���������� ����
  int waves_passed;

  // ����� � ��������, ������ ������� ����������� ����� �����
  int wave_time;

  // ���������� ������������ ������ �� ���� ���
  int wave_enemies_count;

  // ���������� ������, ��������� � ��������� �����
  int seconds_passed_since_last_wave;

  // ���������� ���������� ���� � ������� ���������� ���������� ������� �� ��������� �����
  int waves_passed_since_last_wave_time_decrease;

  // ���������� ���������� ���� � ������� ���������� ���������� ���������� ������ �����
  int waves_passed_since_last_wave_enemies_count_increase;

  // ����� �� �������� ���
  BOOL need_to_erase_background;
protected:
  // ������ ����
  HICON window_icon;

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

  // ����������� ������ �� ������ ������
  void CenterPlayer() const;

  // ��������� ����� ����� ������
  void CreateNewEnemiesWave();

  // ������ ������ ����� �� ����
  void CreateNewEnemy();
public:
  afx_msg void OnNcPaint();
};

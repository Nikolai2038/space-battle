#include "pch.h"
#include "afxdialogex.h"
#include "Config.h"
#include "CSpaceBattleDlgGame.h"
#include "Enemy.h"
#include "Globals.h"
#include "SpaceBattle.h"
#include <string>

IMPLEMENT_DYNAMIC(CSpaceBattleDlgGame, CDialogEx)

CSpaceBattleDlgGame::CSpaceBattleDlgGame(CWnd* p_parent) :
    CDialogEx(IDD_DIALOG_GAME, p_parent),
    hdc(nullptr),
    game_screen(nullptr),
    time_playing_seconds_passed(0) {
  this->game_state = GameState::Created;

  this->entities = std::list<Entity*>();

  this->player = new Player();
  this->entities.push_back(player);
}

CSpaceBattleDlgGame::~CSpaceBattleDlgGame() {
  for (auto entity : this->entities) {
    delete entity;
  }
}

void CSpaceBattleDlgGame::DoDataExchange(CDataExchange* p_dx) {
  CDialogEx::DoDataExchange(p_dx);
  DDX_Control(p_dx, IDC_BUTTON_PAUSE_OR_RESUME_GAME, button_pause_or_resume_game);
  DDX_Control(p_dx, IDC_BUTTON_START_OR_END_GAME, button_start_or_end_game);
  DDX_Control(p_dx, IDC_TEXT_TIME_PLAYING, text_time_playing);
}

BEGIN_MESSAGE_MAP(CSpaceBattleDlgGame, CDialogEx)
ON_BN_CLICKED(IDC_BUTTON_RETURN_TO_THE_MENU, &CSpaceBattleDlgGame::OnBnClickedButtonReturnToTheMenu)
ON_WM_PAINT()
ON_WM_TIMER()
ON_WM_ERASEBKGND()
ON_WM_SIZE()
ON_WM_KEYDOWN()
ON_WM_KEYUP()
ON_BN_CLICKED(IDC_BUTTON_PAUSE_OR_RESUME_GAME, &CSpaceBattleDlgGame::OnBnClickedButtonPauseOrResumeGame)
ON_BN_CLICKED(IDC_BUTTON_START_OR_END_GAME, &CSpaceBattleDlgGame::OnBnClickedButtonStartOrEndGame)
ON_WM_CLOSE()
END_MESSAGE_MAP()

BOOL CSpaceBattleDlgGame::OnInitDialog() {
  CDialogEx::OnInitDialog();

  game_screen = GetDlgItem(IDC_GAME_SCREEN);
  UpdateGameScreenInfo();

  // ����������� ������ �� ������ ������
  this->player->SetLocation(static_cast<double>(game_screen_rectangle.Width()) / 2, static_cast<double>(game_screen_rectangle.Height()) / 2);

  CreateNewEnemy();

  // �������� ��������� �� DC.
  hdc = ::GetDC(game_screen->m_hWnd);

  UINT_PTR create_timer_result = SetTimer(static_cast<UINT_PTR>(Timers::TimerClock), TIMER_CLOCK_LOOP_IN_MS, nullptr);
  if (create_timer_result == FALSE) {
    MessageBox(
      L"Cannot install timer",
      L"Error message",
      MB_OK + MB_ICONERROR);
  }
  time_playing_seconds_passed = 0;

  create_timer_result = SetTimer(static_cast<UINT_PTR>(Timers::TimerRedraw), TIMER_REDRAW_LOOP_IN_MS, nullptr);
  if (create_timer_result == FALSE) {
    MessageBox(
      L"Cannot install timer",
      L"Error message",
      MB_OK + MB_ICONERROR);
  }

  create_timer_result = SetTimer(static_cast<UINT_PTR>(Timers::TimerPlaying), 1000, nullptr);
  if (create_timer_result == FALSE) {
    MessageBox(
      L"Cannot install timer",
      L"Error message",
      MB_OK + MB_ICONERROR);
  }

  return TRUE;
}

void CSpaceBattleDlgGame::OnSize(UINT n_type, int cx, int cy) {
  // CDialogEx::OnSize(nType, cx, cy);

  UpdateGameScreenInfo();
  Invalidate(false);
}

BOOL CSpaceBattleDlgGame::OnEraseBkgnd(CDC* p_dc) {
  return true;
}

void CSpaceBattleDlgGame::OnPaint() {
  if (hdc_bits != nullptr) {
    DeleteDC(hdc_bits);
  }

  hdc_bits = CreateCompatibleDC(hdc);

  // Device context for painting
  CPaintDC dc(this);

  // ���� ����� �������� ��� ����� ���� - ������� ���.
  // ��������� ��� ��������� �������� ����.
  if (need_to_clear_screen) {
    // �������� ������� ����
    CRect game_screen_rectangle_for_dc;
    GetWindowRect(&game_screen_rectangle_for_dc);
    GetClientRect(game_screen_rectangle_for_dc);

    // ������� ��� ���� �����
    dc.Rectangle(game_screen_rectangle_for_dc);

    // ���������� ������������� ������� ���� ����� ����
    need_to_clear_screen = false;
  }

  // ����������� ���� ������ ������
  constexpr COLORREF m_brush_color = RGB(0, 0, 0);
  CBrush m_brush(m_brush_color);
  dc.SelectObject(&m_brush);
  Rectangle(dc, game_screen_rectangle_window.TopLeft().x, game_screen_rectangle_window.TopLeft().y, game_screen_rectangle_window.BottomRight().x, game_screen_rectangle_window.BottomRight().y);

  // ������ ��� ��������
  for (auto entity : this->entities) {
    entity->Draw(hdc, hdc_bits);
  }

  // CDialogEx::OnPaint();
}

BOOL CSpaceBattleDlgGame::PreTranslateMessage(MSG* p_msg) {
  switch (p_msg->message) {
    case WM_KEYDOWN:
      switch (p_msg->wParam) {
        case 'Q':
          // ������������ ������ ������
          this->player->SetActionRotation(Ship::ActionRotation::Left);
          break;
        case 'E':
          // ������������ ������ �������
          this->player->SetActionRotation(Ship::ActionRotation::Right);
          break;
        case VK_SPACE:
          this->player->Shoot(this->entities);
        default:
          break;
      }
      return true;
    case WM_KEYUP:
      switch (p_msg->wParam) {
        case 'Q':
        case 'E':
          // �������� ������������ ������
          this->player->SetActionRotation(Ship::ActionRotation::None);
          break;
        default:
          break;
      }
      return true;
    default:
      return CDialogEx::PreTranslateMessage(p_msg);
  }
}

void CSpaceBattleDlgGame::OnTimer(UINT_PTR n_id_event) {
  // CDialogEx::OnTimer(nIDEvent);

  if (this->game_state == GameState::Playing) {
    if (n_id_event == static_cast<UINT_PTR>(Timers::TimerClock)) {
      // ��������� �������� ���� ���������
      for (auto entity : this->entities) {
        entity->ProcessActions(this->entities, this->game_screen_rectangle);
      }
    } else if (n_id_event == static_cast<UINT_PTR>(Timers::TimerRedraw)) {
      // ������������ ���������� ������� OnPaint()
      RedrawWindow(game_screen_rectangle_window);
    } else if (n_id_event == static_cast<UINT_PTR>(Timers::TimerPlaying)) {
      time_playing_seconds_passed++;

      int seconds = time_playing_seconds_passed % 60;
      int minutes = (time_playing_seconds_passed - seconds) / 60 % 60;
      int hours = (time_playing_seconds_passed - seconds - minutes * 60) / 60 / 60;

      CString time_playing;
      time_playing.Format(L"Time playing: %.2d:%.2d:%.2d", hours, minutes, seconds);
      text_time_playing.SetWindowText(time_playing);
    }
  }
}

void CSpaceBattleDlgGame::OnClose() {
  OnBnClickedButtonReturnToTheMenu();
}

void CSpaceBattleDlgGame::OnBnClickedButtonReturnToTheMenu() {
  PauseGame();
  int dialog_result = MessageBox(
    L"Return to the menu?\nYour progress will be lost!",
    L"Return to the menu",
    MB_YESNO + MB_ICONQUESTION);
  if (dialog_result == IDYES) {
    EndGameAndDoNotSaveRecord();
  } else {
    ResumeGame();
  }
}

void CSpaceBattleDlgGame::OnBnClickedButtonPauseOrResumeGame() {
  switch (this->game_state) {
    case GameState::Paused:
      ResumeGame();
      break;
    case GameState::Playing:
      PauseGame();
      break;
    default:
      break;
  }
}

void CSpaceBattleDlgGame::OnBnClickedButtonStartOrEndGame() {
  switch (this->game_state) {
    case GameState::Created:
      this->game_state = GameState::Playing;
      this->button_pause_or_resume_game.EnableWindow(true);
      this->button_start_or_end_game.SetWindowTextW(L"End game");
      break;
    default:
      PauseGame();
      const int dialog_result = MessageBox(
        L"End the game?\nYour progress will be saved in records.",
        L"End the game",
        MB_YESNO + MB_ICONQUESTION);

      if (dialog_result == IDYES) {
        EndGameAndSaveRecord();
      } else {
        ResumeGame();
      }
      break;
  }
}

void CSpaceBattleDlgGame::UpdateGameScreenInfo() {
  if (game_screen != nullptr) {
    // �������� ���������� �� ������� ����
    game_screen->GetClientRect(&game_screen_rectangle);
    game_screen->GetWindowRect(&game_screen_rectangle_window);
    ScreenToClient(&game_screen_rectangle_window);

    // ���������, ��� ����� �������� ��� ����� ����
    need_to_clear_screen = true;
  }
}

void CSpaceBattleDlgGame::PauseGame() {
  this->game_state = GameState::Paused;
  this->button_pause_or_resume_game.SetWindowTextW(L"Resume game");
}

void CSpaceBattleDlgGame::ResumeGame() {
  this->game_state = GameState::Playing;
  this->button_pause_or_resume_game.SetWindowTextW(L"Pause game");
}

void CSpaceBattleDlgGame::EndGameAndDoNotSaveRecord() {
  this->game_state = GameState::Finished;
  OnOK();
}

void CSpaceBattleDlgGame::EndGameAndSaveRecord() {
  this->game_state = GameState::Finished;

  // TODO: Save record
  // ...

  OnOK();
}

void CSpaceBattleDlgGame::CreateNewEnemy() {
  auto enemy = new Enemy();
  enemy->SetLocation(static_cast<double>(game_screen_rectangle.Width()) / 4, static_cast<double>(game_screen_rectangle.Height()) / 4);
  enemy->SetAngle(-PI / 4);
  this->entities.push_back(enemy);
}

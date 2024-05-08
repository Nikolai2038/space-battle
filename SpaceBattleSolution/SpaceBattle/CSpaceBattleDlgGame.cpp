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
  DDX_Control(p_dx, IDC_TEXT_POINTS_EARNED, cstatic_points_earned);
  DDX_Control(p_dx, IDC_TEXT_ENEMIES_DEFEATED, cstatic_enemies_defeated);
  DDX_Control(p_dx, IDC_TEXT_HEALTH_LEFT, cstatic_health_left);
  DDX_Control(p_dx, IDC_TEXT_TIME_PLAYING, cstatic_time_playing);
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

  hdc = ::GetDC(game_screen->m_hWnd);

  UpdateGameScreenInfo();

  CenterPlayer();

  return TRUE;
}

void CSpaceBattleDlgGame::OnSize(UINT n_type, int cx, int cy) {
  // CDialogEx::OnSize(nType, cx, cy);

  UpdateGameScreenInfo();
  Invalidate(false);

  CenterPlayer();
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

  // Если нужно очистить фон всего окна - очищаем его.
  // Требуется при изменении размеров окна.
  if (need_to_clear_screen) {
    // Получаем размеры окна
    CRect game_screen_rectangle_for_dc;
    GetWindowRect(&game_screen_rectangle_for_dc);
    GetClientRect(game_screen_rectangle_for_dc);

    // Очищаем фон всей формы
    dc.Rectangle(game_screen_rectangle_for_dc);

    // Сбрасываем необходимость очистки фона всего окна
    need_to_clear_screen = false;
  }

  // Закрашиваем поле чёрным цветом
  constexpr COLORREF m_brush_color = RGB(0, 0, 0);
  CBrush m_brush(m_brush_color);
  dc.SelectObject(&m_brush);
  Rectangle(dc, game_screen_rectangle_window.TopLeft().x, game_screen_rectangle_window.TopLeft().y, game_screen_rectangle_window.BottomRight().x, game_screen_rectangle_window.BottomRight().y);

  // Рисуем все сущности
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
          // Поворачиваем игрока налево
          this->player->StartRotatingLeft();
          break;
        case 'E':
          // Поворачиваем игрока направо
          this->player->StartRotatingRight();
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
          // Перестаём поворачивать игрока
          this->player->StopRotatingLeft();
        case 'E':
          // Перестаём поворачивать игрока
          this->player->StopRotatingRight();
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
      // Обработка действий всех сущностей
      for (auto entity : this->entities) {
        entity->ProcessActions(this->entities, this->game_screen_rectangle);
      }
    } else if (n_id_event == static_cast<UINT_PTR>(Timers::TimerRedraw)) {
      // Инициировать исполнение функции OnPaint()
      RedrawWindow(game_screen_rectangle_window);

      CString text_points_earned;
      text_points_earned.Format(L"Points earned: %d", this->player->GetPointsEarned());
      cstatic_points_earned.SetWindowText(text_points_earned);

      CString text_enemies_defeated;
      text_enemies_defeated.Format(L"Enemies defeated: %d", this->player->GetEntitiesDestroyed());
      cstatic_enemies_defeated.SetWindowText(text_enemies_defeated);

      CString text_health_left;
      text_health_left.Format(L"Health: %d", this->player->GetHealth());
      cstatic_health_left.SetWindowText(text_health_left);
    } else if (n_id_event == static_cast<UINT_PTR>(Timers::TimerPlaying)) {
      time_playing_seconds_passed++;

      int seconds = time_playing_seconds_passed % 60;
      int minutes = (time_playing_seconds_passed - seconds) / 60 % 60;
      int hours = (time_playing_seconds_passed - seconds - minutes * 60) / 60 / 60;

      CString time_playing;
      time_playing.Format(L"Time playing: %.2d:%.2d:%.2d", hours, minutes, seconds);
      cstatic_time_playing.SetWindowText(time_playing);
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
  if (this->game_state == GameState::Created) {
    this->game_state = GameState::Playing;
    this->button_pause_or_resume_game.EnableWindow(true);
    this->button_start_or_end_game.SetWindowTextW(L"End game");

    CreateNewEnemy();

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
  } else {
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
  }
}

void CSpaceBattleDlgGame::UpdateGameScreenInfo() {
  if (game_screen != nullptr) {
    // Получаем информацию об игровом поле
    game_screen->GetClientRect(&game_screen_rectangle);
    game_screen->GetWindowRect(&game_screen_rectangle_window);
    ScreenToClient(&game_screen_rectangle_window);

    // Указываем, что нужно очистить фон всего окна
    need_to_clear_screen = true;
  }
}

void CSpaceBattleDlgGame::PauseGame() {
  if (this->game_state == GameState::Playing) {
    this->game_state = GameState::Paused;
    this->button_pause_or_resume_game.SetWindowTextW(L"Resume game");
  }
}

void CSpaceBattleDlgGame::ResumeGame() {
  if (this->game_state == GameState::Paused) {
    this->game_state = GameState::Playing;
    this->button_pause_or_resume_game.SetWindowTextW(L"Pause game");
  }
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

void CSpaceBattleDlgGame::CenterPlayer() const {
  // Центрируем игрока только, если игра не началась
  if (this->game_state == GameState::Created) {
    this->player->SetLocation(static_cast<double>(game_screen_rectangle.Width()) / 2, static_cast<double>(game_screen_rectangle.Height()) / 2);
  }
}

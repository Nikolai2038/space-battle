#include "pch.h"
#include "afxdialogex.h"
#include "CSpaceBattleDlgGame.h"

#include <string>

#include "Config.h"
#include "Enemy.h"
#include "Globals.h"
#include "SpaceBattle.h"

IMPLEMENT_DYNAMIC(CSpaceBattleDlgGame, CDialogEx)

enum class CSpaceBattleDlgGame::Timers {
  TIMER_CLOCK,
  TIMER_REDRAW,
  TIMER_GAMETIME
};

enum class CSpaceBattleDlgGame::GameState {
  CREATED,
  PAUSED,
  PLAYING,
  FINISHED,
};

void CSpaceBattleDlgGame::PauseGame() {
  this->game_state = GameState::PAUSED;
  this->button_pause_or_resume_game.SetWindowTextW(L"Resume game");
}

void CSpaceBattleDlgGame::ResumeGame() {
  this->game_state = GameState::PLAYING;
  this->button_pause_or_resume_game.SetWindowTextW(L"Pause game");
}

void CSpaceBattleDlgGame::EndGameAndDoNotSaveRecord() {
  OnOK();
}

void CSpaceBattleDlgGame::EndGameAndSaveRecord() {
  // TODO: Save record
  // ...

  OnOK();
}

CSpaceBattleDlgGame::CSpaceBattleDlgGame(CWnd* pParent /*=nullptr*/) :
    CDialogEx(IDD_DIALOG_GAME, pParent),
    hdc(nullptr),
    game_screen(nullptr),
    time_playing_seconds_passed(0) {
  this->game_state = GameState::CREATED;

  this->entities = std::list<Entity*>();

  this->player = new Player();
  this->entities.push_back(player);
}

CSpaceBattleDlgGame::~CSpaceBattleDlgGame() {
  for (auto entity : this->entities) {
    delete entity;
  }
}

void CSpaceBattleDlgGame::DoDataExchange(CDataExchange* pDX) {
  CDialogEx::DoDataExchange(pDX);
  DDX_Control(pDX, IDC_BUTTON_PAUSE_OR_RESUME_GAME, button_pause_or_resume_game);
  DDX_Control(pDX, IDC_BUTTON_START_OR_END_GAME, button_start_or_end_game);
  DDX_Control(pDX, IDC_TEXT_TIME_PLAYING, text_time_playing);
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

// CSpaceBattleDlgGame message handlers

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
    case GameState::PAUSED:
      ResumeGame();
      break;
    case GameState::PLAYING:
      PauseGame();
      break;
    default:
      break;
  }
}

void CSpaceBattleDlgGame::OnBnClickedButtonStartOrEndGame() {
  switch (this->game_state) {
    case GameState::CREATED:
      this->game_state = GameState::PLAYING;
      this->button_pause_or_resume_game.EnableWindow(true);
      this->button_start_or_end_game.SetWindowTextW(L"End game");
      break;
    default:
      PauseGame();
      int dialog_result = MessageBox(
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

void CSpaceBattleDlgGame::GameResume() {
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

void CSpaceBattleDlgGame::OnPaint() {
  if (hdcBits != nullptr) {
    DeleteDC(hdcBits);
  }

  hdcBits = CreateCompatibleDC(hdc);

  // device context for painting
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

  CBrush m_Brush;
  COLORREF m_BrushColor = RGB(0, 0, 0);
  m_Brush.CreateSolidBrush(m_BrushColor);
  dc.SelectObject(&m_Brush);

  // Закрасить область рисования белым цветом
  // dc.Rectangle(game_screen_rectangle_for_dc);
  ::SelectObject(dc, &m_Brush);
  ::Rectangle(dc, game_screen_rectangle_window.TopLeft().x, game_screen_rectangle_window.TopLeft().y, game_screen_rectangle_window.BottomRight().x, game_screen_rectangle_window.BottomRight().y);

  for (auto entity : this->entities) {
    entity->Draw(hdc, hdcBits);
  }

  // CDialogEx::OnPaint();
}

BOOL CSpaceBattleDlgGame::OnInitDialog() {
  CDialogEx::OnInitDialog();

  game_screen = GetDlgItem(IDC_GAME_SCREEN);
  UpdateGameScreenInfo();

  // Располагаем игрока по центру экрана
  this->player->SetLocation(static_cast<double>(game_screen_rectangle.Width()) / 2, static_cast<double>(game_screen_rectangle.Height()) / 2);

  CreateNewEnemy();

  // Получить указатель на DC.
  hdc = ::GetDC(game_screen->m_hWnd);

  UINT_PTR create_timer_result = SetTimer(static_cast<UINT_PTR>(Timers::TIMER_CLOCK), TIMER_CLOCK_LOOP_IN_MS, nullptr);
  if (create_timer_result == FALSE) {
    MessageBox(
      L"Cannot install timer",
      L"Error message",
      MB_OK + MB_ICONERROR);
  }
  time_playing_seconds_passed = 0;

  create_timer_result = SetTimer(static_cast<UINT_PTR>(Timers::TIMER_REDRAW), TIMER_REDRAW_LOOP_IN_MS, nullptr);
  if (create_timer_result == FALSE) {
    MessageBox(
      L"Cannot install timer",
      L"Error message",
      MB_OK + MB_ICONERROR);
  }

  create_timer_result = SetTimer(static_cast<UINT_PTR>(Timers::TIMER_GAMETIME), TIMER_GAMETIME_LOOP_IN_MS, nullptr);
  if (create_timer_result == FALSE) {
    MessageBox(
      L"Cannot install timer",
      L"Error message",
      MB_OK + MB_ICONERROR);
  }

  return TRUE;
}

void CSpaceBattleDlgGame::OnTimer(UINT_PTR nIDEvent) {
  // CDialogEx::OnTimer(nIDEvent);

  if (this->game_state == GameState::PLAYING) {
    if (nIDEvent == static_cast<UINT_PTR>(Timers::TIMER_CLOCK)) {
      // Обработка действий всех сущностей
      for (auto entity : this->entities) {
        entity->ProcessActions(this->entities, this->game_screen_rectangle);
      }
    } else if (nIDEvent == static_cast<UINT_PTR>(Timers::TIMER_REDRAW)) {
      // Инициировать исполнение функции OnPaint()
      RedrawWindow(game_screen_rectangle_window);
    } else if (nIDEvent == static_cast<UINT_PTR>(Timers::TIMER_GAMETIME)) {
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

BOOL CSpaceBattleDlgGame::OnEraseBkgnd(CDC* pDC) {
  return true;
}

void CSpaceBattleDlgGame::OnSize(UINT nType, int cx, int cy) {
  // CDialogEx::OnSize(nType, cx, cy);

  UpdateGameScreenInfo();
  Invalidate(false);
}

BOOL CSpaceBattleDlgGame::PreTranslateMessage(MSG* pMsg) {
  switch (pMsg->message) {
    case WM_KEYDOWN:
      switch (pMsg->wParam) {
        case 'Q':
          // Поворачиваем игрока налево
          this->player->SetActionRotation(Ship::ActionRotation::Left);
          break;
        case 'E':
          // Поворачиваем игрока направо
          this->player->SetActionRotation(Ship::ActionRotation::Right);
          break;
        case VK_SPACE:
          this->player->Shoot(this->entities);
        default:
          break;
      }
      return true;
    case WM_KEYUP:
      switch (pMsg->wParam) {
        case 'Q':
        case 'E':
          // Перестаём поворачивать игрока
          this->player->SetActionRotation(Ship::ActionRotation::None);
          break;
        default:
          break;
      }
      return true;
    default:
      return CDialogEx::PreTranslateMessage(pMsg);
  }
}

void CSpaceBattleDlgGame::CreateNewEnemy() {
  Enemy* enemy = new Enemy();
  enemy->SetLocation(static_cast<double>(game_screen_rectangle.Width()) / 4, static_cast<double>(game_screen_rectangle.Height()) / 4);
  enemy->SetAngle(-PI / 4);
  this->entities.push_back(enemy);
}

void CSpaceBattleDlgGame::OnClose() {
  OnBnClickedButtonReturnToTheMenu();
}

#include "pch.h"
#include "afxdialogex.h"
#include "Config.h"
#include "CSpaceBattleDlgGame.h"

#include <stdexcept>

#include "Enemy.h"
#include "Globals.h"
#include "SpaceBattle.h"
#include <string>

IMPLEMENT_DYNAMIC(CSpaceBattleDlgGame, CDialogEx)

CSpaceBattleDlgGame::CSpaceBattleDlgGame(CWnd* p_parent) :
    CDialogEx(IDD_DIALOG_GAME, p_parent),
    hdc(nullptr),
    hdc_bits(nullptr),
    game_screen(nullptr),
    need_to_clear_screen(true),
    time_playing_seconds_passed(0),
    waves_passed(0),
    wave_time(0),
    wave_enemies_count(0),
    seconds_passed_since_last_wave(0),
    waves_passed_since_last_wave_time_decrease(0),
    waves_passed_since_last_wave_enemies_count_increase(0) {
  this->game_state = GameState::Created;

  this->entities = std::list<Entity*>();

  this->player = new Player();
  this->entities.push_back(player);
}

CSpaceBattleDlgGame::~CSpaceBattleDlgGame() {
  DeleteObject(this->hdc);
  DeleteObject(this->hdc_bits);
  DeleteObject(this->game_screen);

  for (auto entity : this->entities) {
    delete entity;
  }
  DeleteObject(this->player);
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
ON_WM_NCPAINT()
END_MESSAGE_MAP()

BOOL CSpaceBattleDlgGame::OnInitDialog() {
  CDialogEx::OnInitDialog();

  m_bMyDraw = FALSE;

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
  if (m_bMyDraw)
    return TRUE;
  else
    return CDialogEx::OnEraseBkgnd(p_dc);
}

void CSpaceBattleDlgGame::OnPaint() {
  // Device context for painting
  CPaintDC dc(this);

  // ������ DC � ������
  CDC dc_in_memory;
  const int create_dc_result = dc_in_memory.CreateCompatibleDC(&dc);
  if (create_dc_result == 0) {
    throw std::runtime_error("Cannot create memory dc!");
  }

  if (hdc_bits != nullptr) {
    DeleteDC(hdc_bits);
  }

  hdc_bits = CreateCompatibleDC(dc_in_memory);

  // ������ ����������� ��� ��������� � DC � ������ - ����� �� ����� �������� � ��
  CBitmap bitmap_in_memory;
  const int create_bitmap_result = bitmap_in_memory.CreateCompatibleBitmap(&dc, game_screen_rectangle.Width(), game_screen_rectangle.Height());
  if (create_bitmap_result == 0) {
    throw std::runtime_error("Cannot create compatible bitmap!");
  }

  // select the bitmap to memory dc
  const auto bitmap_in_memory_old = dc_in_memory.SelectObject(&bitmap_in_memory);

  // ���� ����� �������� ��� ����� ���� - ������� ���.
  // ��������� ��� ��������� �������� ����.
  if (need_to_clear_screen) {
    // �������� ������� ����
    CRect game_screen_rectangle_for_dc;
    GetWindowRect(&game_screen_rectangle_for_dc);
    GetClientRect(game_screen_rectangle_for_dc);

    // ������� ��� ���� �����
    dc_in_memory.Rectangle(game_screen_rectangle_for_dc);

    // ���������� ������������� ������� ���� ����� ����
    need_to_clear_screen = false;
  }

  // ����������� ���� ������ ������
  constexpr COLORREF m_brush_color = RGB(0, 0, 0);
  CBrush m_brush(m_brush_color);
  dc_in_memory.SelectObject(&m_brush);
  Rectangle(dc_in_memory, game_screen_rectangle.left, game_screen_rectangle.top, game_screen_rectangle.right, game_screen_rectangle.bottom);

  // ������ ��� ��������
  for (auto entity : this->entities) {
    entity->Draw(dc_in_memory, hdc_bits);
  }

  // ���������� ���������� DC � ������ �� �������� DC
  dc.BitBlt(game_screen_rectangle_window.left,
            game_screen_rectangle_window.top,
            game_screen_rectangle_window.Width(),
            game_screen_rectangle_window.Height(),
            &dc_in_memory,
            0,
            0,
            SRCCOPY);

  // ������� ������
  dc_in_memory.SelectObject(bitmap_in_memory_old);
  bitmap_in_memory.DeleteObject();

  dc_in_memory.DeleteDC();

  m_bMyDraw = FALSE;

  // CDialogEx::OnPaint();
}

BOOL CSpaceBattleDlgGame::PreTranslateMessage(MSG* p_msg) {
  switch (p_msg->message) {
    case WM_KEYDOWN:
      switch (p_msg->wParam) {
        case 'Q':
          // ������������ ������ ������
          this->player->StartRotatingLeft();
          break;
        case 'E':
          // ������������ ������ �������
          this->player->StartRotatingRight();
          break;
        case 'W':
          // �������� ������
          this->player->StartAccelerating();
          break;
        case 'S':
          // ��������� ������
          this->player->StartDeAccelerating();
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
          // �������� ������������ ������
          this->player->StopRotatingLeft();
        case 'E':
          // �������� ������������ ������
          this->player->StopRotatingRight();
          break;
        case 'W':
          // �������� �������� ������
          this->player->StopAccelerating();
          break;
        case 'S':
          // �������� ��������� ������
          this->player->StopDeAccelerating();
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
      if (this->player->IsDestroyed()) {
        EndGameAndSaveRecord();
      }
    } else if (n_id_event == static_cast<UINT_PTR>(Timers::TimerRedraw)) {
      m_bMyDraw = TRUE;
      // ������������ ���������� ������� OnPaint()
      InvalidateRect(&game_screen_rectangle_window);
      // RedrawWindow(game_screen_rectangle_window);

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
      seconds_passed_since_last_wave++;

      if (seconds_passed_since_last_wave >= wave_time) {
        CreateNewEnemiesWave();
      }

      int seconds = time_playing_seconds_passed % 60;
      int minutes = (time_playing_seconds_passed - seconds) / 60 % 60;
      int hours = (time_playing_seconds_passed - seconds - minutes * 60) / 60 / 60;

      CString time_playing;
      time_playing.Format(L"Time playing: %.2d:%.2d:%.2d", hours, minutes, seconds);
      cstatic_time_playing.SetWindowText(time_playing);
    } else if (n_id_event == static_cast<UINT_PTR>(Timers::TimerGarbageCollector)) {
      // ������� �� ������ ������������ ��������
      entities.erase(std::remove_if(entities.begin(), entities.end(), [](const Entity* entity) {
                       if (entity->IsDestroyed()) {
                         delete entity;
                         return true;
                       }
                       return false;
                     }),
                     entities.end());
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

    waves_passed = 0;
    wave_time = INITIAL_WAVE_TIME;
    wave_enemies_count = INITIAL_WAVE_ENEMIES_COUNT;

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

    create_timer_result = SetTimer(static_cast<UINT_PTR>(Timers::TimerGarbageCollector), TIMER_GARBAGE_COLLECTOR_LOOP_IN_MS, nullptr);
    if (create_timer_result == FALSE) {
      MessageBox(
        L"Cannot install timer",
        L"Error message",
        MB_OK + MB_ICONERROR);
    }

    CreateNewEnemiesWave();
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
    // �������� ���������� �� ������� ����
    game_screen->GetClientRect(&game_screen_rectangle);
    game_screen->GetWindowRect(&game_screen_rectangle_window);
    ScreenToClient(&game_screen_rectangle_window);

    // ���������, ��� ����� �������� ��� ����� ����
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

void CSpaceBattleDlgGame::CenterPlayer() const {
  // ���������� ������ ������, ���� ���� �� ��������
  if (this->game_state == GameState::Created) {
    this->player->SetLocation(static_cast<double>(game_screen_rectangle.Width()) / 2, static_cast<double>(game_screen_rectangle.Height()) / 2);
  }
}

void CSpaceBattleDlgGame::CreateNewEnemiesWave() {
  waves_passed++;
  waves_passed_since_last_wave_time_decrease++;
  waves_passed_since_last_wave_enemies_count_increase++;

  seconds_passed_since_last_wave = 0;

  // ��������� ����� �� ��������� �����
  if (waves_passed_since_last_wave_time_decrease >= WAVES_TILL_DECREASE_WAVE_TIME && wave_time - DECREASE_WAVE_TIME >= MIN_WAVE_TIME) {
    waves_passed_since_last_wave_time_decrease = 0;
    wave_time -= DECREASE_WAVE_TIME;
  }

  // ����������� ���������� ������
  if (waves_passed_since_last_wave_enemies_count_increase >= WAVES_TILL_INCREASE_WAVE_ENEMIES_COUNT && wave_enemies_count + INCREASE_WAVE_ENEMIES_COUNT <= MAX_WAVE_ENEMIES_COUNT) {
    waves_passed_since_last_wave_enemies_count_increase = 0;
    wave_enemies_count += INCREASE_WAVE_ENEMIES_COUNT;
  }

  // ������ ����������� ���������� ������
  for (int i = 0; i < wave_enemies_count; ++i) {
    CreateNewEnemy();
  }
}

void CSpaceBattleDlgGame::CreateNewEnemy() {
  const auto side = static_cast<SideToSpawn>(GetRandom(0, 3));

  double random_x;
  double random_y;

  switch (side) {
    case SideToSpawn::Left:
      random_x = 50;
      random_y = GetRandom(0, game_screen_rectangle.Height());
      break;
    case SideToSpawn::Right:
      random_x = game_screen_rectangle.Width() - 50;
      random_y = GetRandom(0, game_screen_rectangle.Height());
      break;
    case SideToSpawn::Top:
      random_x = GetRandom(0, game_screen_rectangle.Width());
      random_y = 50;
      break;
    case SideToSpawn::Bottom:
      random_x = GetRandom(0, game_screen_rectangle.Width());
      random_y = game_screen_rectangle.Height() - 50;
      break;
    default:
      throw new std::runtime_error("side is unknown!");
  }

  const auto enemy = new Enemy();
  enemy->SetLocation(random_x, random_y);
  enemy->SetAngle(-PI / 4);
  enemy->AddToList(this->entities);
}

void CSpaceBattleDlgGame::OnNcPaint() {
  // TODO: Add your message handler code here
  // Do not call CDialogEx::OnNcPaint() for painting messages

  m_bMyDraw = FALSE; // you can comment out this line of code
                     // and see what will happen, after you press the "Start" button
                     //     then resize the window. have fun!
  CWnd::OnNcPaint();
}

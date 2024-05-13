#include "pch.h"
#include "afxdialogex.h"
#include "Config.h"
#include "CSpaceBattleDlgGame.h"
#include "Enemy.h"
#include "Globals.h"
#include "Record.h"
#include "SpaceBattle.h"
#include <ctime>
#include <stdexcept>
#include <string>

IMPLEMENT_DYNAMIC(CSpaceBattleDlgGame, CDialogEx)

CSpaceBattleDlgGame::CSpaceBattleDlgGame(CWnd* p_parent) :
    CDialogEx(IDD_DIALOG_GAME, p_parent),
    hdc(nullptr),
    hdc_bits(nullptr),
    game_screen(nullptr),
    time_playing_seconds_passed(0),
    waves_passed(0),
    wave_time(0),
    wave_enemies_count(0),
    seconds_passed_since_last_wave(0),
    waves_passed_since_last_wave_time_decrease(0),
    waves_passed_since_last_wave_enemies_count_increase(0),
    need_to_erase_background(FALSE) {
  // �������� ������ ����
  window_icon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

  this->game_state = GameState::Created;

  this->entities = std::list<Entity*>();

  this->player = new Player();
  this->entities.push_back(player);
}

CSpaceBattleDlgGame::~CSpaceBattleDlgGame() {
  DeleteObject(this->hdc);
  DeleteObject(this->hdc_bits);
  DeleteObject(this->game_screen);

  for (const auto entity : this->entities) {
    delete entity;
  }
  DeleteObject(this->player);
}

void CSpaceBattleDlgGame::DoDataExchange(CDataExchange* p_dx) {
  CDialogEx::DoDataExchange(p_dx);
  DDX_Control(p_dx, IDC_BUTTON_PAUSE_OR_RESUME_GAME, this->button_pause_or_resume_game);
  DDX_Control(p_dx, IDC_BUTTON_START_OR_END_GAME, this->button_start_or_end_game);
  DDX_Control(p_dx, IDC_TEXT_POINTS_EARNED, this->cstatic_points_earned);
  DDX_Control(p_dx, IDC_TEXT_ENEMIES_DEFEATED, this->cstatic_enemies_defeated);
  DDX_Control(p_dx, IDC_TEXT_HEALTH_LEFT, this->cstatic_health_left);
  DDX_Control(p_dx, IDC_TEXT_TIME_PLAYING, this->cstatic_time_playing);
  DDX_Control(p_dx, IDC_EDIT_PLAYER_NAME, this->cedit_player_name);
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

  // ��������� ������ ����
  SetIcon(this->window_icon, FALSE);

  // ������������� ��� ������ �� ���������
  this->cedit_player_name.SetWindowTextW(PLAYER_DEFAULT_NAME);

  this->need_to_erase_background = FALSE;

  this->game_screen = GetDlgItem(IDC_GAME_SCREEN);

  this->hdc = ::GetDC(this->game_screen->m_hWnd);

  UpdateGameScreenInfo();

  CenterPlayer();

  // �� ������������ �� ������ ������
  return FALSE;
}

void CSpaceBattleDlgGame::OnSize(UINT n_type, int cx, int cy) {
  // CDialogEx::OnSize(nType, cx, cy);

  UpdateGameScreenInfo();
  Invalidate(false);

  CenterPlayer();
}

BOOL CSpaceBattleDlgGame::OnEraseBkgnd(CDC* p_dc) {
  if (this->need_to_erase_background) {
    return TRUE;
  }

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

  if (this->hdc_bits != nullptr) {
    DeleteDC(this->hdc_bits);
  }

  this->hdc_bits = CreateCompatibleDC(dc_in_memory);

  // ������ ����������� ��� ��������� � DC � ������ - ����� �� ����� �������� � ��
  CBitmap bitmap_in_memory;
  const int create_bitmap_result = bitmap_in_memory.CreateCompatibleBitmap(&dc, this->game_screen_rectangle.Width(), this->game_screen_rectangle.Height());
  if (create_bitmap_result == 0) {
    throw std::runtime_error("Cannot create compatible bitmap!");
  }

  // ������������ ����������� � DC � ������
  const auto bitmap_in_memory_old = dc_in_memory.SelectObject(&bitmap_in_memory);

  // ���� ����, ������� ����� ������ ����������
  COLORREF transparent_color = RGB(0, 255, 0);
  // dc_in_memory.FillSolidRect(&game_screen_rectangle, transparent_color);

  // ����������� ���� ������ ������
  dc_in_memory.FillSolidRect(&this->game_screen_rectangle, RGB(0, 0, 0));

  // ������ ��� ��������
  for (const auto entity : this->entities) {
    entity->Draw(dc_in_memory, this->hdc_bits);
  }

  // ���������� ���������� DC � ������ �� �������� DC
  dc.BitBlt(this->game_screen_rectangle_window.left,
            this->game_screen_rectangle_window.top,
            this->game_screen_rectangle_window.Width(),
            this->game_screen_rectangle_window.Height(),
            &dc_in_memory,
            0,
            0,
            SRCCOPY);

  // ������� ������
  dc_in_memory.SelectObject(bitmap_in_memory_old);
  bitmap_in_memory.DeleteObject();

  dc_in_memory.DeleteDC();

  this->need_to_erase_background = FALSE;

  // CDialogEx::OnPaint();
}

BOOL CSpaceBattleDlgGame::PreTranslateMessage(MSG* p_msg) {
  if (this->game_state != GameState::Playing) {
    return CDialogEx::PreTranslateMessage(p_msg);
  }

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
          // ����� �� �������� ��������� CDialogEx, �����, ��������, ������� ������� �� �������� ������� ��������������� ������
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
          return CDialogEx::PreTranslateMessage(p_msg);
      }
      return true;
    default:
      return CDialogEx::PreTranslateMessage(p_msg);
  }
}

void CSpaceBattleDlgGame::OnTimer(UINT_PTR n_id_event) {
  // CDialogEx::OnTimer(n_id_event);

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
      this->need_to_erase_background = TRUE;
      // ������������ ���������� ������� OnPaint()
      RedrawWindow(this->game_screen_rectangle_window);

      // ��������� ����� � ����������� ����� ������
      CString text_points_earned;
      text_points_earned.Format(L"Points earned: %d", this->player->GetPointsEarned());
      this->cstatic_points_earned.SetWindowText(text_points_earned);

      // ��������� ����� � ����������� ������������ ������
      CString text_enemies_defeated;
      text_enemies_defeated.Format(L"Enemies defeated: %d", this->player->GetEntitiesDestroyed());
      this->cstatic_enemies_defeated.SetWindowText(text_enemies_defeated);

      // ��������� ����� � ����������� �������� ������
      CString text_health_left;
      text_health_left.Format(L"Health: %d", this->player->GetHealth());
      this->cstatic_health_left.SetWindowText(text_health_left);
    } else if (n_id_event == static_cast<UINT_PTR>(Timers::TimerPlaying)) {
      this->time_playing_seconds_passed++;
      this->seconds_passed_since_last_wave++;

      // ���� ������ ����� ��������� �����
      if (this->seconds_passed_since_last_wave >= this->wave_time) {
        CreateNewEnemiesWave();
      }

      // ��������� ����� � �������� ����
      const int seconds = this->time_playing_seconds_passed % 60;
      const int minutes = (this->time_playing_seconds_passed - seconds) / 60 % 60;
      const int hours = (this->time_playing_seconds_passed - seconds - minutes * 60) / 60 / 60;
      CString time_playing;
      time_playing.Format(L"Time playing: %.2d:%.2d:%.2d", hours, minutes, seconds);
      this->cstatic_time_playing.SetWindowText(time_playing);
    } else if (n_id_event == static_cast<UINT_PTR>(Timers::TimerGarbageCollector)) {
      // ������� �� ������ ������������ ��������
      this->entities.erase(std::remove_if(this->entities.begin(), this->entities.end(), [](const Entity* entity) {
                             if (entity->IsDestroyed()) {
                               delete entity;
                               return true;
                             }
                             return false;
                           }),
                           this->entities.end());
    }
  }
}

void CSpaceBattleDlgGame::OnClose() {
  OnBnClickedButtonReturnToTheMenu();
}

void CSpaceBattleDlgGame::OnBnClickedButtonReturnToTheMenu() {
  // ��������� ������� ��������� ����
  const GameState saved_game_state = this->game_state;
  // ���� ���� ��� - ������ ���� �� �����
  if (saved_game_state == GameState::Playing) {
    PauseGame();
  }

  // ���������� ������ � �������������� ������
  const int dialog_result = MessageBox(
    L"Return to the menu?\nYour progress will be lost!",
    L"Return to the menu",
    MB_YESNO + MB_ICONQUESTION);

  // ���� ����������� �����
  if (dialog_result == IDYES) {
    EndGameAndDoNotSaveRecord();
  }
  // ���� �������� �����
  else {
    // ���� ���� ��� - ������������ ����
    if (saved_game_state == GameState::Playing) {
      ResumeGame();
    }
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
    // ������ ����� � ����������� ������
    this->button_pause_or_resume_game.EnableWindow(true);
    this->button_start_or_end_game.SetWindowTextW(L"End game");

    // ����� ���������� ��������������� �����
    std::srand(std::time(nullptr));

    // ���������� ������ ����������
    this->game_state = GameState::Playing;
    this->waves_passed = 0;
    this->wave_time = INITIAL_WAVE_TIME;
    this->wave_enemies_count = INITIAL_WAVE_ENEMIES_COUNT;
    this->time_playing_seconds_passed = 0;

    // ��������� ���� ����� ����� ������
    this->cedit_player_name.EnableWindow(false);

    // �������� ��� ������ � ��������� ���
    CString entered_player_name;
    this->cedit_player_name.GetWindowTextW(entered_player_name);
    this->player->SetName(ConvertLPCWSTRToString(entered_player_name.GetString()));

    // ������ ��� ����������� �������
    if (!SetTimer(static_cast<UINT_PTR>(Timers::TimerClock), TIMER_CLOCK_LOOP_IN_MS, nullptr)) {
      throw std::runtime_error("Failed to create timer TimerClock!");
    }
    if (!SetTimer(static_cast<UINT_PTR>(Timers::TimerRedraw), TIMER_REDRAW_LOOP_IN_MS, nullptr)) {
      throw std::runtime_error("Failed to create timer TimerRedraw!");
    }
    if (!SetTimer(static_cast<UINT_PTR>(Timers::TimerPlaying), 1000, nullptr)) {
      throw std::runtime_error("Failed to create timer TimerPlaying!");
    }
    if (!SetTimer(static_cast<UINT_PTR>(Timers::TimerGarbageCollector), TIMER_GARBAGE_COLLECTOR_LOOP_IN_MS, nullptr)) {
      throw std::runtime_error("Failed to create timer TimerGarbageCollector!");
    }

    CreateNewEnemiesWave();
  } else {
    // ��������� ������� ��������� ����
    const GameState saved_game_state = this->game_state;
    // ���� ���� ��� - ������ ���� �� �����
    if (saved_game_state == GameState::Playing) {
      PauseGame();
    }

    // ���������� ������ � �������������� ���������� ����
    const int dialog_result = MessageBox(
      L"End the game?\nYour progress will be saved in records.",
      L"End the game",
      MB_YESNO + MB_ICONQUESTION);

    // ���� ����������� ���������� ����
    if (dialog_result == IDYES) {
      EndGameAndSaveRecord();
    }
    // ���� �������� ���������� ����
    else {
      // ���� ���� ��� - ������������ ����
      if (saved_game_state == GameState::Playing) {
        ResumeGame();
      }
    }
  }
}

void CSpaceBattleDlgGame::UpdateGameScreenInfo() {
  if (this->game_screen != nullptr) {
    // �������� ���������� �� ������� ����
    this->game_screen->GetClientRect(&this->game_screen_rectangle);
    this->game_screen->GetWindowRect(&this->game_screen_rectangle_window);
    ScreenToClient(&this->game_screen_rectangle_window);
  }
}

void CSpaceBattleDlgGame::PauseGame() {
  if (this->game_state == GameState::Playing) {
    this->game_state = GameState::Paused;

    // ������ ����� ������
    this->button_pause_or_resume_game.SetWindowTextW(L"Resume game");
  }
}

void CSpaceBattleDlgGame::ResumeGame() {
  if (this->game_state == GameState::Paused) {
    this->game_state = GameState::Playing;

    // ������ ����� ������
    this->button_pause_or_resume_game.SetWindowTextW(L"Pause game");
  }
}

void CSpaceBattleDlgGame::EndGameAndDoNotSaveRecord() {
  this->game_state = GameState::Finished;
  OnOK();
}

void CSpaceBattleDlgGame::EndGameAndSaveRecord() {
  this->game_state = GameState::Finished;

  // ���������� �������
  const Record record(this->player->GetName(),
                      this->player->GetPointsEarned(),
                      this->player->GetEntitiesDestroyed(),
                      this->time_playing_seconds_passed);
  record.Save();

  // ������� ���������
  MessageBox(
    L"Your record has been saved!",
    L"Record saved",
    MB_OK + MB_ICONINFORMATION);

  OnOK();
}

void CSpaceBattleDlgGame::CenterPlayer() const {
  // ���������� ������ ������, ���� ���� �� ��������
  if (this->game_state == GameState::Created) {
    this->player->SetLocation(static_cast<double>(this->game_screen_rectangle.Width()) / 2, static_cast<double>(game_screen_rectangle.Height()) / 2);
  }
}

void CSpaceBattleDlgGame::CreateNewEnemiesWave() {
  this->waves_passed++;
  this->waves_passed_since_last_wave_time_decrease++;
  this->waves_passed_since_last_wave_enemies_count_increase++;

  this->seconds_passed_since_last_wave = 0;

  // ��������� ����� �� ��������� �����
  if (this->waves_passed_since_last_wave_time_decrease >= WAVES_TILL_DECREASE_WAVE_TIME && this->wave_time - DECREASE_WAVE_TIME >= MIN_WAVE_TIME) {
    this->waves_passed_since_last_wave_time_decrease = 0;
    this->wave_time -= DECREASE_WAVE_TIME;
  }

  // ����������� ���������� ������
  if (this->waves_passed_since_last_wave_enemies_count_increase >= WAVES_TILL_INCREASE_WAVE_ENEMIES_COUNT && this->wave_enemies_count + INCREASE_WAVE_ENEMIES_COUNT <= MAX_WAVE_ENEMIES_COUNT) {
    this->waves_passed_since_last_wave_enemies_count_increase = 0;
    this->wave_enemies_count += INCREASE_WAVE_ENEMIES_COUNT;
  }

  // ������ ����������� ���������� ������
  for (int i = 0; i < this->wave_enemies_count; ++i) {
    CreateNewEnemy();
  }
}

void CSpaceBattleDlgGame::CreateNewEnemy() {
  const auto side_to_spawn = static_cast<SideToSpawn>(GetRandom(0, 3));

  const auto enemy = new Enemy();
  const int max_visible_radius = enemy->GetMaxVisibleRadiusOnField();

  // ������� ��������
  double random_x;
  double random_y;
  switch (side_to_spawn) {
    case SideToSpawn::Left:
      random_x = -max_visible_radius;
      random_y = GetRandom(PADDING_ON_SIDE_TO_SPAWN_ENEMY, this->game_screen_rectangle.Height() - PADDING_ON_SIDE_TO_SPAWN_ENEMY);
      break;
    case SideToSpawn::Right:
      random_x = this->game_screen_rectangle.Width() + max_visible_radius;
      random_y = GetRandom(PADDING_ON_SIDE_TO_SPAWN_ENEMY, this->game_screen_rectangle.Height() - PADDING_ON_SIDE_TO_SPAWN_ENEMY);
      break;
    case SideToSpawn::Top:
      random_x = GetRandom(PADDING_ON_SIDE_TO_SPAWN_ENEMY, this->game_screen_rectangle.Width() - PADDING_ON_SIDE_TO_SPAWN_ENEMY);
      random_y = -max_visible_radius;
      break;
    case SideToSpawn::Bottom:
    default: // NOLINT(clang-diagnostic-covered-switch-default)
      random_x = GetRandom(PADDING_ON_SIDE_TO_SPAWN_ENEMY, this->game_screen_rectangle.Width() - PADDING_ON_SIDE_TO_SPAWN_ENEMY);
      random_y = this->game_screen_rectangle.Height() + max_visible_radius;
      break;
  }
  enemy->SetLocation(random_x, random_y);

  // �����������, � ������� ����� �������� ����
  double angle;
  switch (side_to_spawn) {
    case SideToSpawn::Left:
      angle = GetRandom(-ENEMY_ANGLE_RANGE, ENEMY_ANGLE_RANGE);
      break;
    case SideToSpawn::Right:
      angle = GetRandom(PI - ENEMY_ANGLE_RANGE, PI + ENEMY_ANGLE_RANGE);
      break;
    case SideToSpawn::Top:
      angle = GetRandom(-PI / 2 - ENEMY_ANGLE_RANGE, -PI / 2 + ENEMY_ANGLE_RANGE);
      break;
    case SideToSpawn::Bottom:
    default: // NOLINT(clang-diagnostic-covered-switch-default)
      angle = GetRandom(PI / 2 - ENEMY_ANGLE_RANGE, PI / 2 + ENEMY_ANGLE_RANGE);
      break;
  }
  enemy->SetAngle(angle);

  // �������� �����
  enemy->SetSpeed(GetRandom(DEFAULT_SPEED, DEFAULT_SPEED_MAX));

  // ��������� ����� �� ����
  enemy->AddToList(this->entities);
}

void CSpaceBattleDlgGame::OnNcPaint() {
  this->need_to_erase_background = FALSE;
  CDialogEx::OnNcPaint();
}

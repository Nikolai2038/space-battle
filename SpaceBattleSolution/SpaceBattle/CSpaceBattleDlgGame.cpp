// CSpaceBattleDlgGame.cpp : implementation file
//

#include "pch.h"
#include "afxdialogex.h"
#include "CSpaceBattleDlgGame.h"

#include "Config.h"
#include "Globals.h"
#include "SpaceBattle.h"

// CSpaceBattleDlgGame dialog

IMPLEMENT_DYNAMIC(CSpaceBattleDlgGame, CDialogEx)

CSpaceBattleDlgGame::CSpaceBattleDlgGame(CWnd* pParent /*=nullptr*/) :
    CDialogEx(IDD_DIALOG_GAME, pParent) {
  this->entities = std::vector<Entity*>();

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
}

BEGIN_MESSAGE_MAP(CSpaceBattleDlgGame, CDialogEx)
ON_BN_CLICKED(IDC_BUTTON_RETURN_TO_THE_MENU, &CSpaceBattleDlgGame::OnBnClickedButtonReturnToTheMenu)
ON_WM_PAINT()
ON_WM_TIMER()
ON_WM_ERASEBKGND()
ON_WM_SIZE()
ON_WM_KEYDOWN()
ON_WM_KEYUP()
END_MESSAGE_MAP()

// CSpaceBattleDlgGame message handlers

void CSpaceBattleDlgGame::OnBnClickedButtonReturnToTheMenu() {
  this->OnOK();
}

void CSpaceBattleDlgGame::GameStart() {
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

void CSpaceBattleDlgGame::OnPaint() {
  if (hdcBits != nullptr) {
    DeleteDC(hdcBits);
  }

  hdcBits = CreateCompatibleDC(hdc);

  // device context for painting
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

  CBrush m_Brush;
  COLORREF m_BrushColor = RGB(0, 0, 0);
  m_Brush.CreateSolidBrush(m_BrushColor);
  dc.SelectObject(&m_Brush);

  // ��������� ������� ��������� ����� ������
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

  // ���������� ��������� ������
  // - 1-� ��������: ������������� �������: "1" ��������� ������ ��� "������#1".
  // - 2-� ��������: ������������� ������ � �������������, � ������� ����� ����������� ��������� WM_TIMER
  // - 3-� ��������: ������ ����� �������, ������� ����� ����������� ������ N �����������. ����� ������� NULL.
  int iInstallResult = SetTimer(TIMER_CLOCK, TIMER_CLOCK_LOOP_IN_MS, nullptr);
  if (iInstallResult == FALSE) {
    MessageBox(
      L"Cannot install timer",
      L"Error message",
      MB_OK + MB_ICONERROR);
  }

  // ���������� ��������� ������
  // - 1-� ��������: ������������� �������: "1" ��������� ������ ��� "������#1".
  // - 2-� ��������: ������������� ������ � �������������, � ������� ����� ����������� ��������� WM_TIMER
  // - 3-� ��������: ������ ����� �������, ������� ����� ����������� ������ N �����������. ����� ������� NULL.
  iInstallResult = SetTimer(TIMER_REDRAW, TIMER_REDRAW_LOOP_IN_MS, nullptr);
  if (iInstallResult == FALSE) {
    MessageBox(
      L"Cannot install timer",
      L"Error message",
      MB_OK + MB_ICONERROR);
  }

  game_screen = GetDlgItem(IDC_GAME_SCREEN);
  UpdateGameScreenInfo();

  // ����������� ������ �� ������ ������
  this->player->SetLocation(game_screen_rectangle.Width() / 2, game_screen_rectangle.Height() / 2);

  CreateNewEnemy();

  // �������� ��������� �� DC.
  hdc = ::GetDC(game_screen->m_hWnd);

  return TRUE;
}

void CSpaceBattleDlgGame::OnTimer(UINT_PTR nIDEvent) {
  // CDialogEx::OnTimer(nIDEvent);

  if (nIDEvent == static_cast<UINT_PTR>(TIMER_CLOCK)) {
    // ��������� �������� ���� ���������
    for (auto entity : this->entities) {
      entity->ProcessActions();
    }
  } else if (nIDEvent == static_cast<UINT_PTR>(TIMER_REDRAW)) {
    // ������������ ���������� ������� OnPaint()
    RedrawWindow(game_screen_rectangle_window);
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
          // ������������ ������ ������
          this->player->SetActionRotation(Ship::ActionRotation::Left);
          break;
        case 'E':
          // ������������ ������ �������
          this->player->SetActionRotation(Ship::ActionRotation::Right);
          break;
        default:
          break;
      }
      return true;
    case WM_KEYUP:
      switch (pMsg->wParam) {
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
      return CDialogEx::PreTranslateMessage(pMsg);
  }
}

void CSpaceBattleDlgGame::CreateNewEnemy() {
  Enemy* enemy = new Enemy();
  enemy->SetLocation(game_screen_rectangle.Width() / 4, game_screen_rectangle.Height() / 4);
  enemy->SetAngle(-PI / 4);
  this->entities.push_back(enemy);
}

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
  this->player = Player();
  this->enemy = Enemy();
}

CSpaceBattleDlgGame::~CSpaceBattleDlgGame() {
}

void CSpaceBattleDlgGame::DoDataExchange(CDataExchange* pDX) {
  CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CSpaceBattleDlgGame, CDialogEx)
ON_BN_CLICKED(IDC_BUTTON_RETURN_TO_THE_MENU, &CSpaceBattleDlgGame::OnBnClickedButtonReturnToTheMenu)
ON_WM_PAINT()
ON_WM_TIMER()
END_MESSAGE_MAP()

// CSpaceBattleDlgGame message handlers

void CSpaceBattleDlgGame::OnBnClickedButtonReturnToTheMenu() {
  this->OnOK();
}

void CSpaceBattleDlgGame::GameStart() {
}

void CSpaceBattleDlgGame::OnPaint() {
  CWnd* game_screen = GetDlgItem(IDC_GAME_SCREEN);
  CRect game_screen_rectangle;
  game_screen->GetClientRect(&game_screen_rectangle);

  // device context for painting
  CPaintDC dc(this);

  // Получить указатель на DC.
  HDC hdc = ::GetDC(game_screen->m_hWnd);

  this->player.Draw(hdc);
  this->enemy.Draw(hdc);

  ::ReleaseDC(game_screen->m_hWnd, hdc);

  CDialogEx::OnPaint();
}

BOOL CSpaceBattleDlgGame::OnInitDialog() {
  CDialogEx::OnInitDialog();

  // Установить системный таймер
  // - 1-й параметр: Идентификатор таймера: "1" объявляет таймер как "таймер#1".
  // - 2-й параметр: Устанавливает период в миллисекундах, с которым будет происходить сообщение WM_TIMER
  // - 3-й параметр: Задает адрес функции, которая будет выполняться каждые 50 миллисекунд. Можно указать NULL.
  int iInstallResult = SetTimer(TIMER_ID, REPAINT_TIMER_LOOP_IN_MS, nullptr);
  if (iInstallResult == FALSE) {
    MessageBox(
      L"Cannot install timer",
      L"Error message",
      MB_OK + MB_ICONERROR);
  }

  CWnd* game_screen = GetDlgItem(IDC_GAME_SCREEN);
  CRect game_screen_rectangle;
  game_screen->GetClientRect(&game_screen_rectangle);
  this->player.SetLocation(game_screen_rectangle.Width() / 2, game_screen_rectangle.Height() / 2);
  this->enemy.SetAngle(-PI / 4);

  return TRUE;
}

void CSpaceBattleDlgGame::OnTimer(UINT_PTR nIDEvent) {
  CDialogEx::OnTimer(nIDEvent);

  if (nIDEvent == static_cast<UINT_PTR>(TIMER_ID)) {
    // Передвижение врага
    this->enemy.Move();

    // Поворачивание игрока
    this->player.SetAngle(this->player.GetAngle() + 0.1);

    // Получаем информацию об игровом поле
    CWnd* game_screen = GetDlgItem(IDC_GAME_SCREEN);
    CRect game_screen_rectangle;
    game_screen->GetWindowRect(&game_screen_rectangle);
    ScreenToClient(&game_screen_rectangle);

    // Инициировать исполнение функции OnPaint()
    RedrawWindow(game_screen_rectangle);
  }
}

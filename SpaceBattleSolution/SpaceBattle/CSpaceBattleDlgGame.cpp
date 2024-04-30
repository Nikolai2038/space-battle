// CSpaceBattleDlgGame.cpp : implementation file
//

#include "pch.h"
#include "afxdialogex.h"
#include "CSpaceBattleDlgGame.h"
#include "SpaceBattle.h"

// CSpaceBattleDlgGame dialog

IMPLEMENT_DYNAMIC(CSpaceBattleDlgGame, CDialogEx)

CSpaceBattleDlgGame::CSpaceBattleDlgGame(CWnd* pParent /*=nullptr*/) :
    CDialogEx(IDD_DIALOG_GAME, pParent) {
  this->player = Player();
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
  game_screen->GetWindowRect(&game_screen_rectangle);
  ScreenToClient(&game_screen_rectangle);

  CPaintDC dc(this); // device context for painting

  // Получить указатель на DC.
  HDC hdc = ::GetDC(m_hWnd);

  this->player.Draw(dc, hdc, game_screen_rectangle);

  ::ReleaseDC(m_hWnd, hdc);

  // CDialogEx::OnPaint();
  /*
  CPictureControl m_pictureControl;

  HBITMAP hBitmap = (HBITMAP)LoadImage(NULL, MAKEINTRESOURCE(IDB_MY_BITMAP), IMAGE_BITMAP, 0, 0, LR_LOADFROMLOCALE);
  CDC dc;
  dc.SelectObject(m_pictureControl.GetDC()->GetDeviceContext());
  dc.BitBlt(0, 0, m_pictureControl.GetClientRect().Width(), m_pictureControl.GetClientRect().Height(), dc.GetDC()->GetDeviceContext(), 0, 0, hBitmap, SRCCOPY);

  */

  // TODO: Add your message handler code here
  // Do not call CDialogEx::OnPaint() for painting messages
}

BOOL CSpaceBattleDlgGame::OnInitDialog() {
  CDialogEx::OnInitDialog();

  // TODO:  Add extra initialization here

  // Установить системный таймер
  // - 1-й параметр: Идентификатор таймера: "1" объявляет таймер как "таймер#1".
  // - 2-й параметр: Устанавливает период в миллисекундах, с которым будет происходить сообщение WM_TIMER
  // - 3-й параметр: Задает адрес функции, которая будет выполняться каждые 50 миллисекунд. Можно указать NULL.
  int iInstallResult = SetTimer(TIMER_ID, 100, nullptr);
  if (iInstallResult == FALSE) {
    MessageBox(
      L"Cannot install timer",
      L"Error message",
      MB_OK + MB_ICONERROR);
  }

  return TRUE; // return TRUE unless you set the focus to a control
  // EXCEPTION: OCX Property Pages should return FALSE
}

void CSpaceBattleDlgGame::OnTimer(UINT_PTR nIDEvent) {
  if (nIDEvent == static_cast<UINT_PTR>(TIMER_ID)) {
    /*  // Кнопка, при столкновении с которой круг будет разбиваться на три
      CButton* button = (CButton*)GetDlgItem(IDC_DRAWGRAPHICS_BUTTON);
      CRect button_rectangle;
      button->GetWindowRect(&button_rectangle);
      ScreenToClient(&button_rectangle);

      // Область окна - не будем выпускать круги из неё
      CRect window_rectangle;
      this->GetWindowRect(&window_rectangle);
      ScreenToClient(&window_rectangle);

      int circles_count = circles.size();
      for (int circle_id = 0; circle_id < circles_count; ++circle_id) {
        Circle& circle = circles.at(circle_id);

        // Передвигаем круг
        circle.Move(window_rectangle);

        // Если круг сталкивается с кнопкой "Draw"
        if (circle.IsIntersectsWith(button_rectangle)) {
          // Разбиваем круг на три
          circle.Multiply(circles);
        }
      }*/

    this->player.Move();

    // Инициировать исполнение функции OnPaint()
    Invalidate();

    // OnPaint();
  }

  CDialogEx::OnTimer(nIDEvent);
}

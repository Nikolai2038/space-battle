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
  // device context for painting
  CPaintDC dc(this);

  // �������� ���������
  HMETAFILE hmf = m_pMF->Close();
  // ��������������� ���������
  dc.PlayMetaFile(hmf);

  // ������������ ��������� �� ������ ������ ���������� temp
  CMetaFileDC* temp = new CMetaFileDC;
  // �������� �������
  temp->Create();
  // ������������ ���������
  temp->PlayMetaFile(hmf);

  // �������� ������������� � ���������
  DeleteMetaFile(hmf);

  // ������������ ���������� ��������� �����������
  m_pMF = temp;

  // CDialogEx::OnPaint();
}

BOOL CSpaceBattleDlgGame::OnInitDialog() {
  CDialogEx::OnInitDialog();

  // ���������� ��������� ������
  // - 1-� ��������: ������������� �������: "1" ��������� ������ ��� "������#1".
  // - 2-� ��������: ������������� ������ � �������������, � ������� ����� ����������� ��������� WM_TIMER
  // - 3-� ��������: ������ ����� �������, ������� ����� ����������� ������ 50 �����������. ����� ������� NULL.
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

  // ========================================
  // ��������� ������� ���������
  // ========================================
  // �������� ��������� �� ������� ���������� Picture
  CWnd* p_Canvas = GetDlgItem(IDC_GAME_SCREEN);

  // �������� ���������� ���� � ���������� m_Canvas
  p_Canvas->GetWindowRect(&m_Canvas);

  // ����������� ���������� ��� ���������� �������
  ScreenToClient(&m_Canvas);

  // �������� ���������� ����
  m_Canvas.DeflateRect(2, 2, 1, 1);
  // ========================================

  // ���������� � ������ ������ ���������
  m_pMF = new CMetaFileDC;

  // ������� ��������
  m_pMF->Create();

  return TRUE;
}

void CSpaceBattleDlgGame::OnTimer(UINT_PTR nIDEvent) {
  CDialogEx::OnTimer(nIDEvent);

  if (nIDEvent == static_cast<UINT_PTR>(TIMER_ID)) {
    // ������������ �����
    this->enemy.Move();

    // ������������� ������
    this->player.SetAngle(this->player.GetAngle() + 0.1);

    // �������� ���������� �� ������� ����
    CWnd* game_screen = GetDlgItem(IDC_GAME_SCREEN);
    CRect game_screen_rectangle;
    game_screen->GetWindowRect(&game_screen_rectangle);
    ScreenToClient(&game_screen_rectangle);

    // ������������ ���������� ������� OnPaint()
    // RedrawWindow(game_screen_rectangle);
    Clear();
    Draw();
  }
}

void CSpaceBattleDlgGame::Draw() {
  // �������� ������ ��������� ����������
  CClientDC dc(this);

  // ���������� �������� DC
  dc.SetAttribDC(dc);
  // dc.SelectObject(&m_Brush);
  m_pMF->SetAttribDC(dc);
  dc.IntersectClipRect(m_Canvas);
  m_pMF->IntersectClipRect(m_Canvas);

  CWnd* game_screen = GetDlgItem(IDC_GAME_SCREEN);
  /*CRect game_screen_rectangle;
  game_screen->GetClientRect(&game_screen_rectangle);*/

  // �������� ��������� �� DC.
  HDC hdc = ::GetDC(game_screen->m_hWnd);

  this->player.Draw(hdc);
  this->enemy.Draw(hdc);

  ::ReleaseDC(game_screen->m_hWnd, hdc);
}

void CSpaceBattleDlgGame::Clear() {
  // �������� ��������� �� �������� ����������
  CClientDC dc(this);

  // ��������� ������� ��������� ����� ������
  dc.SelectStockObject(NULL_PEN);
  dc.Rectangle(m_Canvas);
  /*
  // ������� ��������
  HMETAFILE hmf = m_pMF->Close();
  // ������� ������ � ���������
  ::DeleteMetaFile(hmf);

  // ������� ����� ��������
  m_pMF = new CMetaFileDC;
  m_pMF->Create();
  m_pMF->SetAttribDC(dc);
  // ��������� ������� ��������� ����� ������
  dc.SelectStockObject(NULL_PEN);
  dc.Rectangle(m_Canvas);

  // �������� ������� � ��������
  m_pMF->SelectStockObject(NULL_PEN);
  m_pMF->Rectangle(
    m_Canvas.left,
    m_Canvas.top,
    m_Canvas.right + 1,
    m_Canvas.bottom + 1);*/
}

#include "pch.h"
#include "afxdialogex.h"
#include "CSpaceBattleDlgMenu.h"

#include "CSpaceBattleDlgGame.h"
#include "CSpaceBattleDlgRecords.h"
#include "framework.h"
#include "SpaceBattle.h"

#include "CSpaceBattleDlgRules.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CSpaceBattleDlgMenu::CSpaceBattleDlgMenu(CWnd* pParent /*=nullptr*/) :
    CDialogEx(IDD_SPACEBATTLE_DIALOG, pParent) {
  m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSpaceBattleDlgMenu::DoDataExchange(CDataExchange* pDX) {
  CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CSpaceBattleDlgMenu, CDialogEx)
ON_WM_PAINT()
ON_WM_QUERYDRAGICON()
ON_BN_CLICKED(IDC_BUTTON_PLAY, &CSpaceBattleDlgMenu::OnBnClickedButtonPlay)
ON_BN_CLICKED(IDC_BUTTON_RULES, &CSpaceBattleDlgMenu::OnBnClickedButtonRules)
ON_BN_CLICKED(IDC_BUTTON_RECORDS, &CSpaceBattleDlgMenu::OnBnClickedButtonRecords)
ON_BN_CLICKED(IDC_BUTTON_EXIT, &CSpaceBattleDlgMenu::OnBnClickedButtonExit)
END_MESSAGE_MAP()

// CSpaceBattleDlgMenu message handlers

BOOL CSpaceBattleDlgMenu::OnInitDialog() {
  CDialogEx::OnInitDialog();

  // Set icon
  SetIcon(m_hIcon, FALSE);

  // TODO: Add extra initialization here

  // return TRUE  unless you set the focus to a control
  return TRUE;
}

void CSpaceBattleDlgMenu::OnPaint() {
  // Draw the icon when minimize dialog
  if (IsIconic()) {
    // device context for painting
    CPaintDC dc(this);

    SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

    // Center icon in client rectangle
    int cxIcon = GetSystemMetrics(SM_CXICON);
    int cyIcon = GetSystemMetrics(SM_CYICON);
    CRect rect;
    GetClientRect(&rect);
    int x = (rect.Width() - cxIcon + 1) / 2;
    int y = (rect.Height() - cyIcon + 1) / 2;

    // Draw the icon
    dc.DrawIcon(x, y, m_hIcon);
  } else {
    CDialogEx::OnPaint();
  }
}

// The system calls this function to obtain the cursor to display while the user drags the minimized window.
HCURSOR CSpaceBattleDlgMenu::OnQueryDragIcon() {
  return static_cast<HCURSOR>(m_hIcon);
}

// Событие нажатия на кнопку начала игры
void CSpaceBattleDlgMenu::OnBnClickedButtonPlay() {
  CSpaceBattleDlgGame dialog_game;
  dialog_game.DoModal();
}

// Событие нажатия на кнопку просмотра правил
void CSpaceBattleDlgMenu::OnBnClickedButtonRules() {
  CSpaceBattleDlgRules dialog_rules;
  dialog_rules.DoModal();
}

// Событие нажатия на кнопку просмотра рекордов
void CSpaceBattleDlgMenu::OnBnClickedButtonRecords() {
  CSpaceBattleDlgRecords dialog_records;
  dialog_records.DoModal();
}

// Событие нажатия на кнопку выхода
void CSpaceBattleDlgMenu::OnBnClickedButtonExit() {
  int iResults = MessageBox(
    L"Exit the game?",
    L"Exit",
    MB_YESNO + MB_ICONQUESTION);

  if (iResults == IDYES) {
    OnOK();
  }
}

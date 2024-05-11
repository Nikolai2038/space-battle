#include "pch.h"
#include "afxdialogex.h"
#include "CSpaceBattleDlgGame.h"
#include "CSpaceBattleDlgMenu.h"
#include "CSpaceBattleDlgRecords.h"
#include "CSpaceBattleDlgRules.h"
#include "framework.h"
#include "SpaceBattle.h"

#ifdef _DEBUG
// ReSharper disable CppInconsistentNaming
#define new DEBUG_NEW
// ReSharper restore CppInconsistentNaming
#endif

CSpaceBattleDlgMenu::CSpaceBattleDlgMenu(CWnd* p_parent /*=nullptr*/) :
    CDialogEx(IDD_SPACEBATTLE_DIALOG, p_parent) {
  // Загрузка иконки окна
  window_icon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

  // Загружаем изображение из ресурса
  CPngImage intro_image;
  intro_image.Load(IDB_INTRO, AfxGetResourceHandle());
  // Получаем объект изображения
  this->intro_image_bitmap = static_cast<HBITMAP>(intro_image.Detach());
}

CSpaceBattleDlgMenu::~CSpaceBattleDlgMenu() {
  DeleteObject(this->intro_image_bitmap);
}

void CSpaceBattleDlgMenu::DoDataExchange(CDataExchange* p_dx) {
  CDialogEx::DoDataExchange(p_dx);
  DDX_Control(p_dx, IDC_INTRO, cstatic_intro_image);
}

BEGIN_MESSAGE_MAP(CSpaceBattleDlgMenu, CDialogEx)
ON_WM_PAINT()
ON_WM_QUERYDRAGICON()
ON_BN_CLICKED(IDC_BUTTON_PLAY, &CSpaceBattleDlgMenu::OnBnClickedButtonPlay)
ON_BN_CLICKED(IDC_BUTTON_RULES, &CSpaceBattleDlgMenu::OnBnClickedButtonRules)
ON_BN_CLICKED(IDC_BUTTON_RECORDS, &CSpaceBattleDlgMenu::OnBnClickedButtonRecords)
ON_BN_CLICKED(IDC_BUTTON_EXIT, &CSpaceBattleDlgMenu::OnBnClickedButtonExit)
END_MESSAGE_MAP()

BOOL CSpaceBattleDlgMenu::OnInitDialog() {
  CDialogEx::OnInitDialog();

  // Установка иконки окна
  SetIcon(window_icon, FALSE);

  this->cstatic_intro_image.SetBitmap(this->intro_image_bitmap);

  // Фокусируемся на первой кнопке
  return TRUE;
}

void CSpaceBattleDlgMenu::OnPaint() {
  // Draw the icon when minimize dialog
  if (IsIconic()) {
    // Device context for painting
    CPaintDC dc(this);

    SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

    // Center icon in client rectangle
    const int cx_icon = GetSystemMetrics(SM_CXICON);
    const int cy_icon = GetSystemMetrics(SM_CYICON);
    CRect rect;
    GetClientRect(&rect);
    const int x = (rect.Width() - cx_icon + 1) / 2;
    const int y = (rect.Height() - cy_icon + 1) / 2;

    // Draw the icon
    dc.DrawIcon(x, y, window_icon);
  } else {
    CDialogEx::OnPaint();
  }
}

// The system calls this function to obtain the cursor to display while the user drags the minimized window.
HCURSOR CSpaceBattleDlgMenu::OnQueryDragIcon() {
  return static_cast<HCURSOR>(window_icon);
}

// Событие нажатия на кнопку начала игры
void CSpaceBattleDlgMenu::OnBnClickedButtonPlay() {
  CSpaceBattleDlgGame dialog_game(this);
  dialog_game.DoModal();
}

// Событие нажатия на кнопку просмотра правил
void CSpaceBattleDlgMenu::OnBnClickedButtonRules() {
  CSpaceBattleDlgRules dialog_rules(this);
  dialog_rules.DoModal();
}

// Событие нажатия на кнопку просмотра рекордов
void CSpaceBattleDlgMenu::OnBnClickedButtonRecords() {
  CSpaceBattleDlgRecords dialog_records(this);
  dialog_records.DoModal();
}

// Событие нажатия на кнопку выхода
void CSpaceBattleDlgMenu::OnBnClickedButtonExit() {
  const int dialog_result = MessageBox(
    L"Exit the game?",
    L"Exit",
    MB_YESNO + MB_ICONQUESTION);

  if (dialog_result == IDYES) {
    OnOK();
  }
}

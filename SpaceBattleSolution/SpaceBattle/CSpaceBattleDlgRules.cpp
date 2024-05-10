#include "pch.h"
#include "afxdialogex.h"
#include "CSpaceBattleDlgRules.h"
#include "SpaceBattle.h"

IMPLEMENT_DYNAMIC(CSpaceBattleDlgRules, CDialogEx)

CSpaceBattleDlgRules::CSpaceBattleDlgRules(CWnd* p_parent /*=nullptr*/) :
    CDialogEx(IDD_DIALOG_RULES, p_parent) {
  // Загрузка иконки окна
  window_icon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CSpaceBattleDlgRules::~CSpaceBattleDlgRules() = default;

BOOL CSpaceBattleDlgRules::OnInitDialog() {
  CDialogEx::OnInitDialog();

  // Установка иконки окна
  SetIcon(window_icon, FALSE);

  return TRUE;
}

void CSpaceBattleDlgRules::DoDataExchange(CDataExchange* p_dx) {
  CDialogEx::DoDataExchange(p_dx);
}

BEGIN_MESSAGE_MAP(CSpaceBattleDlgRules, CDialogEx)
ON_BN_CLICKED(IDC_BUTTON_RETURN_TO_THE_MENU, &CSpaceBattleDlgRules::OnBnClickedButtonReturnToTheMenu)
END_MESSAGE_MAP()

void CSpaceBattleDlgRules::OnBnClickedButtonReturnToTheMenu() {
  this->OnOK();
}

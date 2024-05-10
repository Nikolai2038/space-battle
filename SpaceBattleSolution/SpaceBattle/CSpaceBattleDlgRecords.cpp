#include "pch.h"
#include "afxdialogex.h"
#include "CSpaceBattleDlgRecords.h"
#include "SpaceBattle.h"

IMPLEMENT_DYNAMIC(CSpaceBattleDlgRecords, CDialogEx)

CSpaceBattleDlgRecords::CSpaceBattleDlgRecords(CWnd* p_parent /*=nullptr*/) :
    CDialogEx(IDD_DIALOG_RECORDS, p_parent) {
  // Загрузка иконки окна
  window_icon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CSpaceBattleDlgRecords::~CSpaceBattleDlgRecords() = default;

BOOL CSpaceBattleDlgRecords::OnInitDialog() {
  CDialogEx::OnInitDialog();

  // Установка иконки окна
  SetIcon(window_icon, FALSE);

  return TRUE;
}

void CSpaceBattleDlgRecords::DoDataExchange(CDataExchange* p_dx) {
  CDialogEx::DoDataExchange(p_dx);
}

BEGIN_MESSAGE_MAP(CSpaceBattleDlgRecords, CDialogEx)
ON_BN_CLICKED(IDC_BUTTON_RETURN_TO_THE_MENU, &CSpaceBattleDlgRecords::OnBnClickedButtonReturnToTheMenu)
END_MESSAGE_MAP()

void CSpaceBattleDlgRecords::OnBnClickedButtonReturnToTheMenu() {
  this->OnOK();
}

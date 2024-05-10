// CSpaceBattleDlgRules.cpp : implementation file
//

#include "pch.h"
#include "afxdialogex.h"
#include "CSpaceBattleDlgRules.h"
#include "SpaceBattle.h"

// CSpaceBattleDlgRules dialog

IMPLEMENT_DYNAMIC(CSpaceBattleDlgRules, CDialogEx)

CSpaceBattleDlgRules::CSpaceBattleDlgRules(CWnd* pParent /*=nullptr*/) :
    CDialogEx(IDD_DIALOG_RULES, pParent) {
  // Загрузка иконки окна
  window_icon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CSpaceBattleDlgRules::~CSpaceBattleDlgRules() {
}

BOOL CSpaceBattleDlgRules::OnInitDialog() {
  CDialogEx::OnInitDialog();

  // Установка иконки окна
  SetIcon(window_icon, FALSE);

  return TRUE;
}

void CSpaceBattleDlgRules::DoDataExchange(CDataExchange* pDX) {
  CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CSpaceBattleDlgRules, CDialogEx)
ON_BN_CLICKED(IDC_BUTTON_RETURN_TO_THE_MENU, &CSpaceBattleDlgRules::OnBnClickedButtonReturnToTheMenu)
END_MESSAGE_MAP()

// CSpaceBattleDlgRules message handlers

void CSpaceBattleDlgRules::OnBnClickedButtonReturnToTheMenu() {
  this->OnOK();
}

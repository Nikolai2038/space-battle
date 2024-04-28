// CSpaceBattleDlgRecords.cpp : implementation file
//

#include "pch.h"
#include "afxdialogex.h"
#include "CSpaceBattleDlgRecords.h"
#include "SpaceBattle.h"

// CSpaceBattleDlgRecords dialog

IMPLEMENT_DYNAMIC(CSpaceBattleDlgRecords, CDialogEx)

CSpaceBattleDlgRecords::CSpaceBattleDlgRecords(CWnd* pParent /*=nullptr*/) :
    CDialogEx(IDD_DIALOG_RECORDS, pParent) {
}

CSpaceBattleDlgRecords::~CSpaceBattleDlgRecords() {
}

void CSpaceBattleDlgRecords::DoDataExchange(CDataExchange* pDX) {
  CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CSpaceBattleDlgRecords, CDialogEx)
ON_BN_CLICKED(IDC_BUTTON_RETURN_TO_THE_MENU, &CSpaceBattleDlgRecords::OnBnClickedButtonReturnToTheMenu)
END_MESSAGE_MAP()

// CSpaceBattleDlgRecords message handlers

void CSpaceBattleDlgRecords::OnBnClickedButtonReturnToTheMenu() {
  this->OnOK();
}

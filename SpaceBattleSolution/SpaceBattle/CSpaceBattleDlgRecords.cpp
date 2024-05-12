#include "pch.h"
#include "afxdialogex.h"
#include "CSpaceBattleDlgRecords.h"
#include "Record.h"
#include "SpaceBattle.h"

IMPLEMENT_DYNAMIC(CSpaceBattleDlgRecords, CDialogEx)

CSpaceBattleDlgRecords::CSpaceBattleDlgRecords(CWnd* p_parent /*=nullptr*/) :
    CDialogEx(IDD_DIALOG_RECORDS, p_parent) {
  // �������� ������ ����
  window_icon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CSpaceBattleDlgRecords::~CSpaceBattleDlgRecords() = default;

BOOL CSpaceBattleDlgRecords::OnInitDialog() {
  CDialogEx::OnInitDialog();

  // ��������� ������ ����
  SetIcon(window_icon, FALSE);

  const std::list<Record> records = Record::GetRecords();
  // ���� �������� ��� ���
  if (records.empty()) {
    clistbox_records.AddString(L"No records");
  }
  // ���� ������� ����
  else {
    // ������� ��� �������
    for (const auto& record : records) {
      clistbox_records.AddString(record.ToString());
    }
  }

  return TRUE;
}

void CSpaceBattleDlgRecords::DoDataExchange(CDataExchange* p_dx) {
  CDialogEx::DoDataExchange(p_dx);
  DDX_Control(p_dx, IDC_LIST_RECORDS, this->clistbox_records);
}

BEGIN_MESSAGE_MAP(CSpaceBattleDlgRecords, CDialogEx)
ON_BN_CLICKED(IDC_BUTTON_RETURN_TO_THE_MENU, &CSpaceBattleDlgRecords::OnBnClickedButtonReturnToTheMenu)
END_MESSAGE_MAP()

void CSpaceBattleDlgRecords::OnBnClickedButtonReturnToTheMenu() {
  this->OnOK();
}

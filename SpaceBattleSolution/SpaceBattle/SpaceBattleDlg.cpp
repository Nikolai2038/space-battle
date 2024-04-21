
// SpaceBattleDlg.cpp : implementation file
//

#include "pch.h"
#include "afxdialogex.h"
#include "framework.h"
#include "SpaceBattle.h"
#include "SpaceBattleDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CSpaceBattleDlg dialog

CSpaceBattleDlg::CSpaceBattleDlg(CWnd* pParent /*=nullptr*/) :
    CDialogEx(IDD_SPACEBATTLE_DIALOG, pParent) {
  m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSpaceBattleDlg::DoDataExchange(CDataExchange* pDX) {
  CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CSpaceBattleDlg, CDialogEx)
ON_WM_PAINT()
ON_WM_QUERYDRAGICON()
ON_BN_CLICKED(IDC_BUTTON_PLAY, &CSpaceBattleDlg::OnBnClickedButtonPlay)
ON_BN_CLICKED(IDC_BUTTON_RULES, &CSpaceBattleDlg::OnBnClickedButtonRules)
ON_BN_CLICKED(IDC_BUTTON_RECORDS, &CSpaceBattleDlg::OnBnClickedButtonRecords)
ON_BN_CLICKED(IDC_BUTTON_EXIT, &CSpaceBattleDlg::OnBnClickedButtonExit)
END_MESSAGE_MAP()

// CSpaceBattleDlg message handlers

BOOL CSpaceBattleDlg::OnInitDialog() {
  CDialogEx::OnInitDialog();

  // Set the icon for this dialog.  The framework does this automatically
  //  when the application's main window is not a dialog
  SetIcon(m_hIcon, TRUE); // Set big icon
  SetIcon(m_hIcon, FALSE); // Set small icon

  // TODO: Add extra initialization here

  return TRUE; // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSpaceBattleDlg::OnPaint() {
  if (IsIconic()) {
    CPaintDC dc(this); // device context for painting

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

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSpaceBattleDlg::OnQueryDragIcon() {
  return static_cast<HCURSOR>(m_hIcon);
}

void CSpaceBattleDlg::OnBnClickedButtonPlay() {
  // TODO: Add your control notification handler code here
}

void CSpaceBattleDlg::OnBnClickedButtonRules() {
  // TODO: Add your control notification handler code here
}

void CSpaceBattleDlg::OnBnClickedButtonRecords() {
  // TODO: Add your control notification handler code here
}

void CSpaceBattleDlg::OnBnClickedButtonExit() {
  OnOK();
}

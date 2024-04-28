#pragma once
#include "afxdialogex.h"


// CSpaceBattleDlgRules dialog

class CSpaceBattleDlgRules : public CDialogEx
{
	DECLARE_DYNAMIC(CSpaceBattleDlgRules)

public:
	CSpaceBattleDlgRules(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CSpaceBattleDlgRules();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_RULES };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
  afx_msg void OnBnClickedButtonReturnToTheMenu();
};

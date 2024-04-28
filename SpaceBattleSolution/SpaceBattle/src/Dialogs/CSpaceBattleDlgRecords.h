#pragma once
#include "afxdialogex.h"


// CSpaceBattleDlgRecords dialog

class CSpaceBattleDlgRecords : public CDialogEx
{
	DECLARE_DYNAMIC(CSpaceBattleDlgRecords)

public:
	CSpaceBattleDlgRecords(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CSpaceBattleDlgRecords();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_RECORDS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};

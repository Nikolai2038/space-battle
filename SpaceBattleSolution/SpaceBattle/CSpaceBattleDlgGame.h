#pragma once
#include "afxdialogex.h"
#include "Enemy.h"
#include "Player.h"

// CSpaceBattleDlgGame dialog

class CSpaceBattleDlgGame : public CDialogEx {
  private:
    DECLARE_DYNAMIC(CSpaceBattleDlgGame)

    const int TIMER_ID = 1;

    CMetaFileDC* m_pMF;

    // ���������� �������� Picture ������������ ������
    CRect m_Canvas;
  public:
    CSpaceBattleDlgGame(CWnd* pParent = nullptr); // standard constructor
    virtual ~CSpaceBattleDlgGame();

    void GameStart();

// Dialog Data
#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_DIALOG_GAME };
#endif
  protected:
    virtual void DoDataExchange(CDataExchange* pDX); // DDX/DDV support

    DECLARE_MESSAGE_MAP()
  public:
    afx_msg void OnBnClickedButtonReturnToTheMenu();
    afx_msg void OnPaint();
    Player player;
    Enemy enemy;
    virtual BOOL OnInitDialog();
    afx_msg void OnTimer(UINT_PTR nIDEvent);

    void Draw();
    void Clear();
};

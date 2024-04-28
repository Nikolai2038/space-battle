// CSpaceBattleDlgGame.cpp : implementation file
//

#include "pch.h"
#include "../SpaceBattle.h"
#include "afxdialogex.h"
#include "CSpaceBattleDlgGame.h"

// CSpaceBattleDlgGame dialog

IMPLEMENT_DYNAMIC(CSpaceBattleDlgGame, CDialogEx)

CSpaceBattleDlgGame::CSpaceBattleDlgGame(CWnd* pParent /*=nullptr*/) :
    CDialogEx(IDD_DIALOG_GAME, pParent) {
}

CSpaceBattleDlgGame::~CSpaceBattleDlgGame() {
}

void CSpaceBattleDlgGame::DoDataExchange(CDataExchange* pDX) {
  CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CSpaceBattleDlgGame, CDialogEx)
END_MESSAGE_MAP()

// CSpaceBattleDlgGame message handlers

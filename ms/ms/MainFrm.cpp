
#include "stdafx.h"
#include "ms.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)
const int  iMaxUserToolbars = 10;
const UINT uiFirstUserToolBarId = AFX_IDW_CONTROLBAR_FIRST + 40;
const UINT uiLastUserToolBarId = uiFirstUserToolBarId + iMaxUserToolbars - 1;
BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_COMMAND(ID_GAME_SOUND, &CMainFrame::OnGameSound)
	ON_COMMAND(ID_MODEL_EASY, &CMainFrame::OnModelEasy)
	ON_COMMAND(ID_MODEL_NORMAL, &CMainFrame::OnModelNormal)
	ON_COMMAND(ID_MODEL_HARD, &CMainFrame::OnModelHard)
	ON_UPDATE_COMMAND_UI(ID_GAME_SOUND, &CMainFrame::OnUpdateGameSound)
	ON_UPDATE_COMMAND_UI(ID_MODEL_EASY, &CMainFrame::OnUpdateModelEasy)
	ON_UPDATE_COMMAND_UI(ID_MODEL_NORMAL, &CMainFrame::OnUpdateModelNormal)
	ON_UPDATE_COMMAND_UI(ID_MODEL_HARD, &CMainFrame::OnUpdateModelHard)
END_MESSAGE_MAP()
static UINT indicators[] =
{
	ID_SEPARATOR,           // 状态行指示器
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame 构造/析构
CMainFrame::CMainFrame()
{
	// TODO: 在此添加成员初始化代码
}
CMainFrame::~CMainFrame()
{
}

// CMainFrame 诊断
#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG

/************************************************** Thea.R 2016.09.06 02:32*/

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)	return -1;
	HICON m_hIcon = AfxGetApp()->LoadIcon(_icon);						//加载图标
	SetIcon(m_hIcon, TRUE);
	sound = 1, model = 2;
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if (!CFrameWnd::PreCreateWindow(cs))	return FALSE;

	cs.style = WS_SYSMENU | WS_OVERLAPPED | WS_MINIMIZEBOX;				//样式
	cs.cx = 830 + 26, cs.cy = 551 + 114;								//窗口宽度、高度
	cs.lpszName = _T("MineSweeping");									//窗口名称

	return TRUE;
}

/************************************************** */


/************************************************** Thea.R 2016.09.08 20:33*/
void CMainFrame::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CFrameWnd::OnTimer(nIDEvent);
}
/************************************************** */

void CMainFrame::OnGameSound()
{
	sound ^= 1;
	return ;
}

void CMainFrame::OnUpdateGameSound(CCmdUI *pCmdUI)
{/*
	pCmdUI->SetCheck(sound);*/
	return ;
}

void CMainFrame::OnModelEasy()
{
	switch (model)
	{
		case 0:
			break;
		case 1: GetMenu()->GetSubMenu(0)->GetSubMenu(1)->CheckMenuItem(1, MF_UNCHECKED | MF_BYPOSITION);
				GetMenu()->GetSubMenu(0)->GetSubMenu(1)->CheckMenuItem(0, MF_CHECKED | MF_BYPOSITION);
				model = 0;
			break;
		case 2: GetMenu()->GetSubMenu(0)->GetSubMenu(1)->CheckMenuItem(2, MF_UNCHECKED | MF_BYPOSITION);
				GetMenu()->GetSubMenu(0)->GetSubMenu(1)->CheckMenuItem(0, MF_CHECKED | MF_BYPOSITION);
				model = 0;
			break;
	}
	model = 0;
	return ;
}

void CMainFrame::OnUpdateModelEasy(CCmdUI *pCmdUI)
{/*
	pCmdUI->SetCheck(true);*/
	return ;
}

void CMainFrame::OnModelNormal()
{
	switch (model)
	{
		case 0:	GetMenu()->GetSubMenu(0)->GetSubMenu(1)->CheckMenuItem(0, MF_UNCHECKED | MF_BYPOSITION);
				GetMenu()->GetSubMenu(0)->GetSubMenu(1)->CheckMenuItem(1, MF_CHECKED | MF_BYPOSITION);
				model = 1;
			break;
		case 1:
			break;
		case 2: GetMenu()->GetSubMenu(0)->GetSubMenu(1)->CheckMenuItem(2, MF_UNCHECKED | MF_BYPOSITION);
				GetMenu()->GetSubMenu(0)->GetSubMenu(1)->CheckMenuItem(1, MF_CHECKED | MF_BYPOSITION);
				model = 1;
			break;
	}
	model = 1;
	return ;
}

void CMainFrame::OnUpdateModelNormal(CCmdUI *pCmdUI)
{/*
	pCmdUI->SetCheck(true);*/
	return ;
}

void CMainFrame::OnModelHard()
{
	switch (model)
	{
		case 0:	GetMenu()->GetSubMenu(0)->GetSubMenu(1)->CheckMenuItem(0, MF_UNCHECKED | MF_BYPOSITION);
				GetMenu()->GetSubMenu(0)->GetSubMenu(1)->CheckMenuItem(2, MF_CHECKED | MF_BYPOSITION);
				model = 2;
			break;
		case 1: GetMenu()->GetSubMenu(0)->GetSubMenu(1)->CheckMenuItem(1, MF_UNCHECKED | MF_BYPOSITION);
				GetMenu()->GetSubMenu(0)->GetSubMenu(1)->CheckMenuItem(2, MF_CHECKED | MF_BYPOSITION);
				model = 2;
			break;
		case 2:
			break;
	}
	model = 2;
	return ;
}

void CMainFrame::OnUpdateModelHard(CCmdUI *pCmdUI)
{/*
	pCmdUI->SetCheck(false);*/
	return ;
}
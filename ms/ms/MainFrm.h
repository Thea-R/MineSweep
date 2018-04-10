
// MainFrm.h : CMainFrame ��Ľӿ�
//

#pragma once

class CMainFrame : public CFrameWnd
{
	
protected: // �������л�����
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// ����
public:

// ����
public:

// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// ʵ��
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // �ؼ���Ƕ���Ա
	CToolBar          m_wndToolBar;
	CStatusBar        m_wndStatusBar;

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()

/************************************************** Thea.R 2016.09.12 23:11*/
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnGameSound();
	afx_msg void OnUpdateGameSound(CCmdUI *pCmdUI);
	afx_msg void OnModelEasy();
	afx_msg void OnModelNormal();
	afx_msg void OnModelHard();
	afx_msg void OnUpdateModelEasy(CCmdUI *pCmdUI);
	afx_msg void OnUpdateModelNormal(CCmdUI *pCmdUI);
	afx_msg void OnUpdateModelHard(CCmdUI *pCmdUI);

public:
	int sound, model;
/************************************************** */

};



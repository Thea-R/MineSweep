
// MainFrm.h : CMainFrame 类的接口
//

#pragma once

class CMainFrame : public CFrameWnd
{
	
protected: // 仅从序列化创建
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// 特性
public:

// 操作
public:

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 实现
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // 控件条嵌入成员
	CToolBar          m_wndToolBar;
	CStatusBar        m_wndStatusBar;

// 生成的消息映射函数
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



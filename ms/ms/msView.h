
#include <windows.h>
#include <mmsystem.h>
#include <queue>
#pragma comment(lib, "WINMM.LIB")
#pragma once
using namespace std;

/************************************************** Thea.R 2016.09.06 02:51*/

struct Mine												//雷
{
	bool is_mine, is_opened;							//雷、已打开
	int cnt, flag;										//周围雷数、右键点击次数
};
/************************************************** */

class CmsView : public CView
{
public:
	virtual ~CmsView();
	CmsDoc* GetDocument() const;
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	CmsView();
	DECLARE_DYNCREATE(CmsView)
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	DECLARE_MESSAGE_MAP()

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif


	/************************************************** Thea.R 2016.09.06 02:51*/
public:
	int R, G, B;									//背景颜色
	int col, row, tot, width, height;				//列、行、总雷数
	int siz, bod, ico_width, ico_height;			//雷区大小、边线宽度、表情宽度、表情高度
	int up, down, left, right;						//雷区周围宽度
	int cnt_flag, rest, opened;						//旗数、剩余雷数、打开格子数
	bool win, failed, sound, start;					//成功、失败、声音、开始
	Mine mmp[50][50];								//雷区信息
public:
	void Init(int _col, int _row, int _tot);		//初始化
	void Open(int x, int y);						//显示格子
	void Open_zero(int x, int y);					//无雷区
	void Open_mine(int x, int y);					//触雷
	void Open_dig(int x, int y);					//数字
	void Show_rest();								//显示剩余
	void Show_icon(int d);							//显示表情
	void Show_dig(int x, int y, int d);				//显示数字
	void Show_mine(int x, int y);					//显示雷
	void Show_flag(int x, int y, int d);			//显示右键图标
	void Show_error(int x, int y);					
	void Back_flag(int x, int y);
	void Draw_all(int _col, int _row, int _tot);	//绘制棋盘
	void Get_id(int &x, int &y, int xx, int yy);	//获取格子坐标
	bool Win();										//判断获胜
	afx_msg void OnNew();												//菜单栏响应函数
	afx_msg void OnEasy();
	afx_msg void OnNormal();
	afx_msg void OnHard();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);				//鼠标响应函数
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnSound();
	/************************************************** */
};

#ifndef _DEBUG  // msView.cpp 中的调试版本
inline CmsDoc* CmsView::GetDocument() const
   { return reinterpret_cast<CmsDoc*>(m_pDocument); }
#endif


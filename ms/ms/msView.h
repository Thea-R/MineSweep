
#include <windows.h>
#include <mmsystem.h>
#include <queue>
#pragma comment(lib, "WINMM.LIB")
#pragma once
using namespace std;

/************************************************** Thea.R 2016.09.06 02:51*/

struct Mine												//��
{
	bool is_mine, is_opened;							//�ס��Ѵ�
	int cnt, flag;										//��Χ�������Ҽ��������
};
/************************************************** */

class CmsView : public CView
{
public:
	virtual ~CmsView();
	CmsDoc* GetDocument() const;
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
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
	int R, G, B;									//������ɫ
	int col, row, tot, width, height;				//�С��С�������
	int siz, bod, ico_width, ico_height;			//������С�����߿�ȡ������ȡ�����߶�
	int up, down, left, right;						//������Χ���
	int cnt_flag, rest, opened;						//������ʣ���������򿪸�����
	bool win, failed, sound, start;					//�ɹ���ʧ�ܡ���������ʼ
	Mine mmp[50][50];								//������Ϣ
public:
	void Init(int _col, int _row, int _tot);		//��ʼ��
	void Open(int x, int y);						//��ʾ����
	void Open_zero(int x, int y);					//������
	void Open_mine(int x, int y);					//����
	void Open_dig(int x, int y);					//����
	void Show_rest();								//��ʾʣ��
	void Show_icon(int d);							//��ʾ����
	void Show_dig(int x, int y, int d);				//��ʾ����
	void Show_mine(int x, int y);					//��ʾ��
	void Show_flag(int x, int y, int d);			//��ʾ�Ҽ�ͼ��
	void Show_error(int x, int y);					
	void Back_flag(int x, int y);
	void Draw_all(int _col, int _row, int _tot);	//��������
	void Get_id(int &x, int &y, int xx, int yy);	//��ȡ��������
	bool Win();										//�жϻ�ʤ
	afx_msg void OnNew();												//�˵�����Ӧ����
	afx_msg void OnEasy();
	afx_msg void OnNormal();
	afx_msg void OnHard();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);				//�����Ӧ����
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnSound();
	/************************************************** */
};

#ifndef _DEBUG  // msView.cpp �еĵ��԰汾
inline CmsDoc* CmsView::GetDocument() const
   { return reinterpret_cast<CmsDoc*>(m_pDocument); }
#endif


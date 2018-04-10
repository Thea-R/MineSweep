#include "stdafx.h"

#ifndef SHARED_HANDLERS
#include "ms.h"
#endif
#include "msDoc.h"
#include "msView.h"
#include "MainFrm.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CmsView, CView)
BEGIN_MESSAGE_MAP(CmsView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)

	ON_COMMAND(ID_FILE_NEW, &CmsView::OnNew)
	ON_COMMAND(ID_MODEL_EASY, &CmsView::OnEasy)
	ON_COMMAND(ID_MODEL_NORMAL, &CmsView::OnNormal)
	ON_COMMAND(ID_MODEL_HARD, &CmsView::OnHard)
	ON_COMMAND(ID_GAME_SOUND, &CmsView::OnSound)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()
BOOL CmsView::PreCreateWindow(CREATESTRUCT& cs){return CView::PreCreateWindow(cs);}

// CmsView 打印
BOOL CmsView::OnPreparePrinting(CPrintInfo* pInfo){return DoPreparePrinting(pInfo);}
void CmsView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/){}
void CmsView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/){}

// CmsView 诊断
#ifdef _DEBUG
void CmsView::AssertValid() const{CView::AssertValid();}
void CmsView::Dump(CDumpContext& dc) const{CView::Dump(dc);}
CmsDoc* CmsView::GetDocument() const /* 非调试版本是内联的*/{ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CmsDoc)));return (CmsDoc*)m_pDocument;}
#endif //_DEBUG

/************************************************** Thea.R 2016.09.06 03:06*/

// CmsView 构造/析构
CmsView::CmsView()	
{	
	Init(30, 16, 99);
	sound = true;
	start = false;
	return;
}
CmsView::~CmsView()	{	}

void CmsView::OnDraw(CDC *pDC)
{
	CmsDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)	return;

	//背景
	CBrush mybrush;
	mybrush.CreateSolidBrush(RGB(R, G, B));
	CRect myrect(0, 0, 1200, 1200);
	pDC->FillRect(myrect, &mybrush);

	CPen mypen, mypen2, *myoldPen, *myoldPen2;
	//雷区
	mypen.CreatePen(PS_SOLID, 3, RGB(232, 232, 232));								//白线打底
	myoldPen = pDC->SelectObject(&mypen);
	for (int i = 0; i <= col; i++)	pDC->MoveTo(left + i * siz, up), pDC->LineTo(left + i * siz, up + row * siz);
	for (int j = 0; j <= row; j++)	pDC->MoveTo(left, up + j * siz), pDC->LineTo(left + col * siz, up + j * siz);
	pDC->SelectObject(myoldPen);

	mypen2.CreatePen(PS_SOLID, 2, RGB(28, 28, 28));									//黑线重描，更立体
	myoldPen2 = pDC->SelectObject(&mypen2);
	for (int i = 0; i <= col; i++)	pDC->MoveTo(left + i * siz, up), pDC->LineTo(left + i * siz, up + row * siz);
	for (int j = 0; j <= row; j++)	pDC->MoveTo(left, up + j * siz), pDC->LineTo(left + col * siz, up + j * siz);
	pDC->SelectObject(myoldPen2);

	//状态区
	/*
	mypen3.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	myoldPen3 = pDC->SelectObject(&mypen3);
	pDC->MoveTo(left, bod);
	pDC->LineTo(left+ico_width, bod), pDC->LineTo(left+ico_width, bod+ico_height);
	pDC->LineTo(left, bod+ico_height), pDC->LineTo(left, bod);
	pDC->MoveTo((width - ico_height) / 2, bod);
	pDC->LineTo((width - ico_height) / 2 + ico_height, bod), pDC->LineTo((width - ico_height) / 2 + ico_height, bod + ico_height);
	pDC->LineTo((width - ico_height) / 2, bod + ico_height), pDC->LineTo((width - ico_height) / 2, bod);
	pDC->MoveTo(width - ico_width - bod, bod);
	pDC->LineTo(width - bod, bod), pDC->LineTo(width - bod, bod + ico_height);
	pDC->LineTo(width - ico_width - bod, bod + ico_height), pDC->LineTo(width - ico_width - bod, bod);
	*/
	Show_icon(0);
	return;
}

void CmsView::Init(int _col, int _row, int _tot)
{
	R = 112, G = 128, B = 180;
	col = _col, row = _row, tot = _tot, siz = 25;														//设置参数
	cnt_flag = tot, rest = tot, opened = 0;
	switch (tot)
	{
		case 99:	bod = 40, ico_width = 110, ico_height = 55;
			break;
		case 40:	bod = 30, ico_width = 90, ico_height = 45;
			break;
		case 10:	bod = 20, ico_width = 70, ico_height = 35;
			break;
	}
	up = bod + ico_height + bod, down = left = right = bod;
	width = left + col*siz + right, height = up + row*siz + down;
	win = failed = start = false;
	memset(mmp, 0, sizeof mmp);

	srand((unsigned int)time(0));																		//随机布雷
	for (int i = 1; i <= tot; )
	{
		int x = rand() % col, y = rand() % row;
		if (!mmp[x][y].is_mine)
		{
			mmp[x][y].is_mine = true;
			i++;
		}
	}

	int dd[8][2] = { -1, -1, -1, 0, -1, 1, 0, -1, 0, 1, 1, -1, 1, 0, 1, 1 };
	for (int i = 0; i < col; i++)
		for (int j = 0; j < row; j++) if(!mmp[i][j].is_mine)
			for (int k = 0; k < 8; k++)
			{
				int x = i + dd[k][0], y = j + dd[k][1];
				if (x >= 0 && x < col && y >= 0 && y < row && mmp[x][y].is_mine)	++mmp[i][j].cnt;	//计算周围雷数
			}

	return ;
}

void CmsView::Open(int x, int y)
{
	if (mmp[x][y].is_mine)	Open_mine(x, y);
	else if (mmp[x][y].cnt)	Open_dig(x, y);
	else Open_zero(x, y);
	return;
}

void CmsView::Open_mine(int x, int y)
{
	CDC *pDC;
	pDC = GetDC();

	CBrush brush;
	brush.CreateSolidBrush(RGB(205, 0, 0));
	CRect rect(x*siz + left + 3, y*siz + up + 3, x*siz + siz + left, y*siz + siz + up);
	pDC->FillRect(rect, &brush);

	for (int i = 0; i < col; i++)
		for (int j = 0; j < row; j++)
		{
			if (mmp[i][j].is_mine && mmp[i][j].flag!=1)	Show_mine(i, j);
			if (!mmp[i][j].is_mine && mmp[i][j].flag==1) Show_error(i, j);
		}
	failed = true;
	Show_icon(3);
	if (sound)
	{
		HMODULE hmod = AfxGetResourceHandle();
		HRSRC hSndResource = FindResource(hmod, MAKEINTRESOURCE(IDR_WAVE1), _T("WAVE"));
		HGLOBAL hGlobalMem = LoadResource(hmod, hSndResource);
		LPCTSTR lpMemSound = (LPCTSTR)LockResource(hGlobalMem);
		PlaySound(lpMemSound, AfxGetResourceHandle(), SND_MEMORY);
		FreeResource(hGlobalMem);
	}
	return;
}

void CmsView::Open_zero(int x, int y)
{
	CDC *pDC;																						//制定设备环境并获得指针
	pDC = GetDC();

	CBrush brush;
	brush.CreateSolidBrush(RGB(255, 255, 255));
	CRect rect(x*siz + left + 3, y*siz + up + 3, x*siz + siz + left, y*siz + siz + up);
	pDC->FillRect(rect, &brush);
	mmp[x][y].is_opened = true;
	++opened;

	int tx, ty, dd[8][2] = { -1, -1, -1, 0, -1, 1, 0, -1, 0, 1, 1, -1, 1, 0, 1, 1 };
	queue<pair<int, int>> q;
	q.push(make_pair(x, y));
	while (!q.empty())
	{
		x = q.front().first, y = q.front().second;
		q.pop();

		for (int k = 0; k < 8; k++)
		{
			tx = x + dd[k][0], ty = y + dd[k][1];
			if (tx < 0 || tx >= col || ty < 0 || ty >= row)	continue;
			if (mmp[tx][ty].is_opened || mmp[tx][ty].is_mine || mmp[tx][ty].flag)	continue;

			if (mmp[tx][ty].cnt)	Open_dig(tx, ty);
			else
			{
				CRect rect(tx*siz + left + 3, ty*siz + up + 3, tx*siz + siz + left, ty*siz + siz + up);
				pDC->FillRect(rect, &brush);
				mmp[tx][ty].is_opened = true;
				++opened;
				q.push(make_pair(tx, ty));
			}
		}

	}
	return ;
}

void CmsView::Open_dig(int x, int y)
{
	++opened;
	mmp[x][y].is_opened = true;
	Show_dig(left + x*siz + 3, up + y*siz + 3, mmp[x][y].cnt);
	return;
}

void CmsView::Get_id(int &x, int &y, int xx, int yy)
{
	x = (xx - left) / siz;
	y = (yy - up) / siz;
	return;
}

void CmsView::Show_rest()
{
	return ;
}

void CmsView::Show_icon(int d)
{
	CDC *pDC;																						//制定设备环境并获得指针
	pDC = GetDC();

	CBitmap ico;																					//创建位图对象
	switch (d)
	{
		case 0:	ico.LoadBitmapW(pic3);																//未开始状态
			break;
		case 1: ico.LoadBitmapW(pic4);																//点击中
			break;
		case 2: ico.LoadBitmapW(pic5);																//点击后
			break;
		case 3: ico.LoadBitmapW(pic1);																//失败
			break;
		case 4: ico.LoadBitmapW(pic2);																//成功
			break;
	}

	BITMAP bmp;																						//定义位图变量
	
	CDC dc_memory;																					//定义并创建内存环境
	dc_memory.CreateCompatibleDC(pDC);

	ico.GetObject(sizeof bmp, &bmp);																//将位图对象的图片放入位图变量
	dc_memory.SelectObject(ico);																	//将位图变量放入内存环境
	pDC->StretchBlt((width - ico_height) / 2, bod, ico_height, ico_height, &dc_memory, 0, 0, bmp.bmWidth, bmp.bmHeight, SRCCOPY);
	ReleaseDC(pDC);	
	
	/*
	CBitmap *tmp = dc_memory.SelectObject(&ico);
	TransparentBlt(pDC->m_hDC, (width - ico_height) / 2, bod, ico_height, ico_height, dc_memory.m_hDC, 0, 0, bmp.bmWidth, bmp.bmHeight, RGB(255, 255, 255));
	dc_memory.SelectObject(ico);
	ReleaseDC(pDC);																					//释放设备环境
	*/
	return ;
}

void CmsView::Show_dig(int x, int y, int d)
{
	CDC *pDC;																						//制定设备环境并获得指针
	pDC = GetDC();

	CBitmap dig;																					//创建位图对象
	switch (d)
	{
		case 1:	dig.LoadBitmapW(dig1);
			break;
		case 2: dig.LoadBitmapW(dig2);
			break;
		case 3: dig.LoadBitmapW(dig3);
			break;
		case 4: dig.LoadBitmapW(dig4);
			break;
		case 5: dig.LoadBitmapW(dig5);
			break;
		case 6: dig.LoadBitmapW(dig6);
			break;
		case 7: dig.LoadBitmapW(dig7);
			break;
		case 8: dig.LoadBitmapW(dig8);
			break;
	}
	BITMAP bmp;																						//定义位图变量

	CDC dc_memory;																					//定义并创建内存环境
	dc_memory.CreateCompatibleDC(pDC);

	dig.GetObject(sizeof bmp, &bmp);																//将位图对象的图片放入位图变量
	dc_memory.SelectObject(dig);																	//将位图变量放入内存环境

	//pDC->BitBlt((width-ico_height)/2, bod, bmp.bmWidth, bmp.bmHeight, &dc_memory, 0, 0, SRCCOPY);	//图片由内存环境传送至设备环境
	pDC->StretchBlt(x, y, siz-3, siz-3, &dc_memory, 0, 0, bmp.bmWidth, bmp.bmHeight, SRCCOPY);
	ReleaseDC(pDC);																					//释放设备环境
	return;
}

void CmsView::Show_mine(int x, int y)
{
	CDC *pDC;																						//制定设备环境并获得指针
	pDC = GetDC();

	CBitmap _mine;																					//创建位图对象
	_mine.LoadBitmapW(mou0);
	BITMAP bmp;																						//定义位图变量

	CDC dc_memory;																					//定义并创建内存环境
	dc_memory.CreateCompatibleDC(pDC);

	_mine.GetObject(sizeof bmp, &bmp);																//将位图对象的图片放入位图变量
	dc_memory.SelectObject(_mine);																	//将位图变量放入内存环境

																									//pDC->BitBlt((width-ico_height)/2, bod, bmp.bmWidth, bmp.bmHeight, &dc_memory, 0, 0, SRCCOPY);	//图片由内存环境传送至设备环境
	pDC->StretchBlt(x*siz + left + 3, y*siz + up + 3, siz - 3, siz - 3, &dc_memory, 0, 0, bmp.bmWidth, bmp.bmHeight, SRCCOPY);
	ReleaseDC(pDC);																					//释放设备环境
	return;
}

void CmsView::Show_flag(int x, int y, int d)
{
	CDC *pDC;																						//制定设备环境并获得指针
	pDC = GetDC();

	CBitmap flg;																					//创建位图对象
	switch (d)
	{
		case 0:	flg.LoadBitmapW(mou1);
			break;
		case 1: flg.LoadBitmapW(mou2);
			break;
	}
	BITMAP bmp;																						//定义位图变量

	CDC dc_memory;																					//定义并创建内存环境
	dc_memory.CreateCompatibleDC(pDC);

	flg.GetObject(sizeof bmp, &bmp);																//将位图对象的图片放入位图变量
	dc_memory.SelectObject(flg);																	//将位图变量放入内存环境

																									//pDC->BitBlt((width-ico_height)/2, bod, bmp.bmWidth, bmp.bmHeight, &dc_memory, 0, 0, SRCCOPY);	//图片由内存环境传送至设备环境
	pDC->StretchBlt(x, y, siz-3, siz-3, &dc_memory, 0, 0, bmp.bmWidth, bmp.bmHeight, SRCCOPY);
	ReleaseDC(pDC);																					//释放设备环境
	return;
}

void CmsView::Show_error(int x, int y)
{
	CDC *pDC;																						//制定设备环境并获得指针
	pDC = GetDC();

	CPen pen, *_pen;
	pen.CreatePen(PS_SOLID, 2, RGB(205, 0, 0));							
	_pen = pDC->SelectObject(&pen);
	pDC->MoveTo(x*siz + left + 3, y*siz + up+3), pDC->LineTo(x*siz + siz + left, y*siz + siz + up);
	pDC->MoveTo(x*siz + siz + left, y*siz + up + 3), pDC->LineTo(x*siz + left + 3, y*siz + siz + up);
	pDC->SelectObject(_pen);

	return;
}

void CmsView::Back_flag(int x, int y)
{
	CDC *pDC;																						//制定设备环境并获得指针
	pDC = GetDC();
	CBrush brush;
	brush.CreateSolidBrush(RGB(R, G, B));
	CRect rect(x*siz + left + 3, y*siz + up + 3, x*siz + siz + left, y*siz + siz + up);
	pDC->FillRect(rect, &brush);
	return ;
}

void CmsView::Draw_all(int _col, int _row, int _tot)
{
	Init(_col, _row, _tot);
	Invalidate();
	
	CWnd *CWnd = AfxGetMainWnd();						//扫雷窗口  
	CRect c_rect, m_rect;								//客户区、主区
	GetClientRect(&c_rect);
	CWnd->GetWindowRect(&m_rect);

	int bdx = m_rect.Width() - c_rect.Width();
	int bdy = m_rect.Height() - c_rect.Height();
	CWnd->MoveWindow(m_rect.left, m_rect.top, bdx + width, bdy + height, true);
	return ;
}

bool CmsView::Win()
{
	if (rest == 0 && cnt_flag == 0)	return true;
	if (opened == col*row - tot)	return true;
	return false;
}

void CmsView::OnNew()
{
	Draw_all(col, row, tot);
	return;
}

void CmsView::OnEasy()
{
	Draw_all(9, 9, 10);
	return ;
}

void CmsView::OnNormal()
{
	Draw_all(16, 16, 40);
	return ;
}

void CmsView::OnHard()
{
	Draw_all(30, 16, 99);
	return ;
}

void CmsView::OnSound()
{
	sound = !sound;
	return ;
}

void CmsView::OnLButtonDown(UINT nFlags, CPoint point)
{
	int l = (width - ico_height) / 2, u = bod;
	int r = l + ico_height, d = u + ico_height;
	if (point.x >= l && point.x <= r && point.y >= u && point.y <= d)	Draw_all(col, row, tot);									//表情区
	else if (point.x >= left && point.x <= left + col * siz && point.y >= up && point.y <= up + row * siz)							//雷区
	{
		int x, y;
		bool flag = (!win) && (!failed);
		if (flag)	for (int i = 0; i <= col; i++)	if (point.x == left + i*siz || point.x == left + i*siz + 1)	flag = false;		//排除边线
		if (flag)	for (int j = 0; j <= row; j++)	if (point.y == up + j*siz || point.y == up + j*siz +1)	flag = false;
		if (flag)	start = true, Show_icon(1);
		if (flag)	Get_id(x, y, point.x, point.y);
		if (flag && !mmp[x][y].is_opened)	Open(x, y);
	}
	if (Win())
	{
		win = true;
		for (int i = 0; i < col; i++)
			for (int j = 0; j < row; j++)
			{
				if (mmp[i][j].is_mine && mmp[i][j].flag != 1)	Show_mine(i, j);
				if (!mmp[i][j].is_mine && mmp[i][j].flag == 1)	Show_error(i, j);
			}
		if (sound)
		{
			HMODULE hmod = AfxGetResourceHandle();
			HRSRC hSndResource = FindResource(hmod, MAKEINTRESOURCE(IDR_WAVE2), _T("WAVE"));
			HGLOBAL hGlobalMem = LoadResource(hmod, hSndResource);
			LPCTSTR lpMemSound = (LPCTSTR)LockResource(hGlobalMem);
			PlaySound(lpMemSound, AfxGetResourceHandle(), SND_MEMORY);
			FreeResource(hGlobalMem);
		}
	}
	CView::OnLButtonDown(nFlags, point);
}

void CmsView::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (start)
	{
		if (failed)	Show_icon(3);
		else if (win)	Show_icon(4);
		else Show_icon(2);
	}
	CView::OnLButtonUp(nFlags, point);
}

void CmsView::OnRButtonDown(UINT nFlags, CPoint point)
{
	int l = (width - ico_height) / 2, u = bod;
	int r = l + ico_height, d = u + ico_height;
	if (point.x >= left && point.x <= left + col * siz && point.y >= up && point.y <= up + row * siz)									//雷区
	{
		int x, y;
		bool flag = (!win) && (!failed);
		if (flag)	for (int i = 0; i <= col; i++)	if (point.x == left + i*siz || point.x == left + i*siz + 1)	flag = false;		//排除边线
		if (flag)	for (int j = 0; j <= row; j++)	if (point.y == up + j*siz || point.y == up + j*siz + 1)	flag = false;
		if (flag)	start = true, Show_icon(1);
		if (flag)	Get_id(x, y, point.x, point.y);
		if (flag && !mmp[x][y].is_opened)
		{
			switch (mmp[x][y].flag)
			{
				case 0: Show_flag(left + x*siz + 3, up + y*siz + 3, 0);	--cnt_flag;
						mmp[x][y].flag = 1;	if (mmp[x][y].is_mine)	--rest;
					break;
				case 1: Show_flag(left + x*siz + 3, up + y*siz + 3, 1);	++cnt_flag;
						mmp[x][y].flag = 2;	if (mmp[x][y].is_mine)	++rest;
					break;
				case 2: Back_flag(x, y); mmp[x][y].flag = 0;
					break;
			}
		}
	}
	if (Win())
	{
		win = true;
		for (int i = 0; i < col; i++)
			for (int j = 0; j < row; j++)
			{
				if (mmp[i][j].is_mine && mmp[i][j].flag != 1)	Show_mine(i, j);
				if (!mmp[i][j].is_mine && mmp[i][j].flag == 1) Show_error(i, j);
			}
		HMODULE hmod = AfxGetResourceHandle();
		HRSRC hSndResource = FindResource(hmod, MAKEINTRESOURCE(IDR_WAVE2), _T("WAVE"));
		HGLOBAL hGlobalMem = LoadResource(hmod, hSndResource);
		LPCTSTR lpMemSound = (LPCTSTR)LockResource(hGlobalMem);
		PlaySound(lpMemSound, AfxGetResourceHandle(), SND_MEMORY);
		FreeResource(hGlobalMem);
	}
	CView::OnRButtonDown(nFlags, point);
}

void CmsView::OnRButtonUp(UINT nFlags, CPoint point)
{
	if (start)
	{
		if (failed)	Show_icon(3);
		else if (win)	Show_icon(4);
		else Show_icon(2);
	}
	CView::OnRButtonUp(nFlags, point);
}

/************************************************** */
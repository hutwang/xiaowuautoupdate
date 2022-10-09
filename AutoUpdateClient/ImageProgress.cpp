// ImageProgress.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "AutoUpdateClient.h"
#include "ImageProgress.h"


// CImageProgress

IMPLEMENT_DYNAMIC(CImageProgress, CProgressCtrl)

CImageProgress::CImageProgress()
{
	m_brTrans = CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));
}

CImageProgress::~CImageProgress()
{
}


BEGIN_MESSAGE_MAP(CImageProgress, CProgressCtrl)
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	ON_WM_CREATE()
	ON_WM_NCCALCSIZE()
END_MESSAGE_MAP()

// CImageProgress ��Ϣ�������

//BOOL CImageProgress::OnEraseBkgnd(CDC* pDC)
//{
//	CRect rect;
//	GetClientRect(&rect);
//	pDC->FillRect(&rect , m_brTrans);
//	
//	return TRUE;
//}

void CImageProgress::OnPaint()
{
	PAINTSTRUCT ps;//����һ���滭����   
	CDC *pDC=BeginPaint(&ps);//�ѻ滭����ѡ���豸�����Ĳ���ʼ   
	int AdrPos=GetPos();//��ȡ�������Ľ���λ��   
	 
	CRect WindowRC;	
	GetWindowRect(&WindowRC);

	CRect ClientRC;   
	//ClientRC.left = 0;
	//ClientRC.top = 0;
	//ClientRC.right = WindowRC.right - WindowRC.left;
	//ClientRC.bottom = WindowRC.bottom - WindowRC.top;
	GetClientRect(&ClientRC);//��ȡ�ͻ�������   
	pDC->SetBkMode (TRANSPARENT);//���ñ���ģʽΪ͸��   
	int nMin,nMax;//�����������������С����   
	GetRange(nMin,nMax);//��ȡ����   
	double Every=(double)ClientRC.Width ()/(nMax-nMin);//��ȡ��λ�̶�   
	int Now=Every*AdrPos;//��ǰ����   
	CRect LeftRC,RightRC;//��������������Ϳհ�����   
	LeftRC=RightRC=ClientRC;
	LeftRC.right =Now;//����������  
	RightRC.left =Now;//�հ�����   

	CBitmap bmpProgress  , bmpBlank;
	bmpProgress.LoadBitmap(IDB_BITMAP2);
	bmpBlank.LoadBitmap(IDB_BITMAP4);
	CBrush brProgress(&bmpProgress);
	CBrush brBlank(&bmpBlank);

	pDC->SelectObject(m_brTrans);

	pDC->FillRect (LeftRC,&brProgress);	//������������  
	pDC->FillRect (RightRC,&brBlank);	//���հ�����   
	ReleaseDC(pDC);//�����豸������   
	EndPaint(&ps);//�����滭����滭
}
void CImageProgress::OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	lpncsp->rgrc[0].left -= 1;
	lpncsp->rgrc[0].top -= 1;
	lpncsp->rgrc[0].right += 1;
	lpncsp->rgrc[0].bottom += 1;;

	CProgressCtrl::OnNcCalcSize(bCalcValidRects, lpncsp);
}

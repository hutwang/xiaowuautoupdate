// AniStatic.cpp : implementation file
//

#include "stdafx.h"
#include "AutoUpdateClient.h"
#include "AniStatic.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAniStatic

CAniStatic::CAniStatic()
{
	m_strWindowText = _T("");
	m_strPaintText = _T("");

	m_bDrawBoard = false;
	m_TextColor = RGB(0x80 , 0xFF , 0x80);

	LOGFONT logFont;
	m_Font.CreatePointFont(12,_T("����"), NULL);
	m_Font.GetLogFont(&logFont);
	logFont.lfCharSet = GB2312_CHARSET;
	logFont.lfHeight = 12;
	//logFont.lfWidth = 6;
	logFont.lfWeight = FW_BOLD;
	m_Font.CreateFontIndirect(&logFont);

	SetFont(&m_Font);
}

CAniStatic::~CAniStatic()
{
}


BEGIN_MESSAGE_MAP(CAniStatic, CStatic)
	//{{AFX_MSG_MAP(CAniStatic)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAniStatic message handlers

void CAniStatic::SetWindowText(LPCTSTR lpszString)
{
	m_strWindowText = (CString)lpszString;  
	CRect rct;  
	GetWindowRect(&rct);  
	GetParent()->ScreenToClient(&rct);  
	GetParent()->InvalidateRect(&rct); //ʹ������Ч �ػ��ֹ�����ı��ص� 

}

void CAniStatic::DrawBoard(CDC* dc,CRect rct)
{
	CPen pen;  
	pen.CreatePen(PS_SOLID, 2, RGB(255, 0, 0));  
	CPen  *oldPen;  
	oldPen = dc->SelectObject(&pen);  
	dc->MoveTo(rct.left, rct.top);  
	dc->LineTo(rct.right, rct.top);  
	dc->LineTo(rct.right, rct.bottom);  
	dc->LineTo(rct.left, rct.bottom);  
	dc->LineTo(rct.left, rct.top);  
	dc->SelectObject(oldPen);  
}

void CAniStatic::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	CRect rct;  
	GetWindowRect(&rct);  
	ScreenToClient(&rct);  

	CPaintDC *pDC = &dc;  
	pDC->SetBkMode(TRANSPARENT);  
	pDC->SetBkColor(TRANSPARENT);  

	/*�ڴ��ͼ*/  
	CDC memDC;  
	memDC.CreateCompatibleDC(&dc);  
	CBitmap m_MemMap;  
	m_MemMap.CreateCompatibleBitmap(pDC, rct.Width(), rct.Height()); 
	memDC.SelectObject(&m_MemMap); 
	memDC.SelectObject(&m_Font);
	memDC.FillSolidRect(rct, RGB(255, 0, 255));  
	memDC.SetBkMode(TRANSPARENT);  
	memDC.SetBkColor(TRANSPARENT);  

	if (m_strPaintText != m_strWindowText)  
	{  
		//m_Font.CreatePointFont(12, _T("����"));  
		memDC.SetTextColor(m_TextColor);  
		memDC.DrawText(m_strWindowText, rct, DT_VCENTER | DT_VCENTER | DT_SINGLELINE);  
		if (m_bDrawBoard)  DrawBoard(&memDC,rct);  
		m_strPaintText = m_strWindowText;  
	}  

	else  
	{  
		memDC.SetTextColor(m_TextColor);  
		memDC.DrawText(m_strWindowText, rct, DT_VCENTER | DT_VCENTER | DT_SINGLELINE);  
		if (m_bDrawBoard)  DrawBoard(&memDC,rct);  
	}  

	/*���Ƶ�����dc*/  
	pDC->TransparentBlt(rct.left, rct.top, rct.Width(), rct.Height(), &memDC, 0, 0, rct.Width(), rct.Height(), RGB(255, 0, 255)); // SRCCOPY);  

	/*�����ڴ�*/  
	m_MemMap.DeleteObject();  
	memDC.DeleteDC();  

	// ��Ϊ��ͼ��Ϣ���� CStatic::OnPaint()
}

HBRUSH CAniStatic::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CStatic::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(RGB(255, 0, 0));

	return (HBRUSH)GetStockObject(NULL_BRUSH) ;


	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}

LRESULT CAniStatic::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	// TODO: �ڴ����ר�ô����/����û���

	/*if(WM_SETTEXT == message)
	{
		CRect rect;
		GetWindowRect(&rect);
		CWnd *pParentWnd = GetParent();
		if(pParentWnd)
		{
			pParentWnd->ScreenToClient(&rect);
			pParentWnd->InvalidateRect(&rect);
		}

	}*/

	return CStatic::DefWindowProc(message, wParam, lParam);
}

BOOL CAniStatic::OnEraseBkgnd(CDC* pDC)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetBkColor(TRANSPARENT);
	return TRUE;

	return CStatic::OnEraseBkgnd(pDC);
}

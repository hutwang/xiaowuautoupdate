// AutoUpdateClient.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error �ڰ������� PCH �Ĵ��ļ�֮ǰ������stdafx.h��
#endif

#include "resource.h"		// ������


// CAutoUpdateClientApp:
// �йش����ʵ�֣������ AutoUpdateClient.cpp
//

class CAutoUpdateClientApp : public CWinApp
{
public:
	CAutoUpdateClientApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
};

extern CAutoUpdateClientApp theApp;

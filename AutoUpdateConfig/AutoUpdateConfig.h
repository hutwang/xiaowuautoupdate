// AutoUpdateConfig.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error �ڰ������� PCH �Ĵ��ļ�֮ǰ������stdafx.h��
#endif

#include "resource.h"		// ������


// CAutoUpdateConfigApp:
// �йش����ʵ�֣������ AutoUpdateConfig.cpp
//

class CAutoUpdateConfigApp : public CWinApp
{
public:
	CAutoUpdateConfigApp();

// ��д
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CAutoUpdateConfigApp theApp;

// AutoUpdateConfigDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "AutoUpdateConfig.h"
#include "AutoUpdateConfigDlg.h"
#include "AutoUpdateFileDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CAutoUpdateConfigDlg �Ի���



CAutoUpdateConfigDlg::CAutoUpdateConfigDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAutoUpdateConfigDlg::IDD, pParent)
	, m_sCommonURL(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAutoUpdateConfigDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LST_FILES, m_lstFiles);
	DDX_Text(pDX, IDC_EDT_URL, m_sCommonURL);
}

BEGIN_MESSAGE_MAP(CAutoUpdateConfigDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(ID_BTN_TEST, OnBnClickedBtnTest)
	ON_BN_CLICKED(IDC_BTN_ADDFILE, OnBnClickedBtnAddfile)
	ON_BN_CLICKED(IDC_BTN_ADDFOLDER, OnBnClickedBtnAddfolder)
	ON_BN_CLICKED(IDC_BTN_SAVE, OnBnClickedBtnSave)
	ON_NOTIFY(NM_RCLICK, IDC_LST_FILES, OnNMRclickLstFiles)
	ON_BN_CLICKED(IDC_BTN_DELSEL, OnBnClickedBtnDelsel)
	ON_BN_CLICKED(IDOK, &CAutoUpdateConfigDlg::OnBnClickedOk)
	ON_WM_DROPFILES()
	ON_BN_CLICKED(IDC_BUTTON1, &CAutoUpdateConfigDlg::OnBnClickedUpdateFile)
	ON_BN_CLICKED(IDC_BUTTON2, &CAutoUpdateConfigDlg::OnBnClickedButton2)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CAutoUpdateConfigDlg ��Ϣ�������

BOOL CAutoUpdateConfigDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��\������...\���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	SetWindowText(_T("�Զ����������ļ��Զ�����XML || SL"));

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	DWORD dwExStyle = m_lstFiles.GetExtendedStyle();
	dwExStyle |= LVS_EX_GRIDLINES;
	dwExStyle |= LVS_EX_FULLROWSELECT ;
	//dwStyle |= LVS_EX_CHECKBOXES;
	m_lstFiles.SetExtendedStyle(dwExStyle);

	m_lstFiles.InsertColumn(0, _T("���"), LVCFMT_LEFT, 40, 0);
	m_lstFiles.InsertColumn(1, _T("�ļ��汾"), LVCFMT_LEFT, 80, 0);
	m_lstFiles.InsertColumn(2, _T("����"), LVCFMT_LEFT, 80, 0);
	m_lstFiles.InsertColumn(3, _T("�ļ���"), LVCFMT_LEFT, 200, 0);
	m_lstFiles.InsertColumn(4, _T("�ļ�·��"), LVCFMT_LEFT, 800, 0);

	ReadCommonSet();

	if(m_UpdateFiles.ReadFromXMLFile((LPTSTR)(LPCTSTR)m_sCommonXML, FALSE))
		RefreshCtrl();
	
	return TRUE;  // ���������˿ؼ��Ľ��㣬���򷵻� TRUE
}


BOOL CAutoUpdateConfigDlg::DestroyWindow()
{
	// TODO: �ڴ����ר�ô����/����û���

	SaveCommonSet();

	return CDialog::DestroyWindow();
}


void CAutoUpdateConfigDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CAutoUpdateConfigDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ��������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
HCURSOR CAutoUpdateConfigDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CAutoUpdateConfigDlg::OnBnClickedBtnTest()
{
#ifdef _DEBUG
	TCHAR szFilename[MAX_PATH];
	::GetModuleFileName(NULL, szFilename, sizeof(szFilename));
	m_UpdateFiles.AddUpdateFile(szFilename);
	RefreshCtrl();

	TCHAR* pszFileName = _T("C:\\publish.xml");
	m_UpdateFiles.SaveToXMLFile(pszFileName);
	::ShellExecute(m_hWnd, NULL, pszFileName, NULL, NULL, SW_SHOW);
#endif
}

#define NAMEBUF 1024

void CAutoUpdateConfigDlg::OnBnClickedBtnAddfile()
{
	TCHAR szFilters[] = _T("All Files (*.*)|*.*||");

	CFileDialog fileDlg (true, _T(""), _T("*.*"),
		OFN_FILEMUSTEXIST | OFN_ALLOWMULTISELECT, szFilters, this);

	
	fileDlg.m_ofn.lpstrFile=new TCHAR[NAMEBUF];
	memset(fileDlg.m_ofn.lpstrFile, 0, sizeof(TCHAR[NAMEBUF]));  
	fileDlg.m_ofn.nMaxFile = NAMEBUF;

	CString sPathName;
	if(fileDlg.DoModal ()==IDOK)
	{ 
		SaveCommonSet();
		POSITION mPos=fileDlg.GetStartPosition();
		while(mPos!=NULL) 
		{ 
			sPathName=fileDlg.GetNextPathName(mPos);
			m_UpdateFiles.AddUpdateFile((TCHAR *)(LPCTSTR)sPathName);
			USES_CONVERSION;
			TRACE("%s\n",T2A(sPathName));
		} 
		RefreshCtrl();
	}

	delete [] fileDlg.m_ofn.lpstrFile;
}

void CAutoUpdateConfigDlg::OnBnClickedBtnAddfolder()
{
	BROWSEINFO bi = { 0 };
    bi.lpszTitle = _T("Pick a Directory");
    LPITEMIDLIST pidl = SHBrowseForFolder ( &bi );
    if ( pidl != 0 )
    {
		SaveCommonSet();
        TCHAR szPath[MAX_PATH];
        if ( SHGetPathFromIDList ( pidl, szPath ) )
        {
			CFileFind fFind;
			_tcscat(szPath, _T("\\*.*"));
			USES_CONVERSION;
			int fCount = fFind.FindFile(szPath) ;
			while(fCount) 
			{
				fCount = fFind.FindNextFile(); 
				if (!fFind.IsDirectory() && !fFind.IsDots()) 
				{
					m_UpdateFiles.AddUpdateFile((LPTSTR)(LPCTSTR)fFind.GetFilePath());
					TRACE("%s\n", T2A(fFind.GetFilePath()));
				}
				else 
				{
					//�����������Ŀ¼
				}
			}

			RefreshCtrl();
		}
	}
}

void CAutoUpdateConfigDlg::OnBnClickedBtnSaveXml()
{
	TCHAR szFilters[] = _T("XML File (*.xml)|*.xml||");

	CFileDialog fileDlg (false, _T("xml"), _T("*.xml"),
		OFN_FILEMUSTEXIST, szFilters, this);

	if( fileDlg.DoModal() == IDOK )
	{
		UpdateData(TRUE);
		m_UpdateFiles.m_sCommonURL = m_sCommonURL;

		m_UpdateFiles.SaveToXMLFile((LPTSTR)(LPCTSTR)fileDlg.GetPathName());
		m_sCommonXML = fileDlg.GetPathName();
		::ShellExecute(m_hWnd, NULL, fileDlg.GetPathName(), NULL, NULL, SW_SHOW);
	}

	SaveCommonSet();
}

void CAutoUpdateConfigDlg::OnBnClickedBtnSave()
{
	// ���� LST
	UpdateData(TRUE);
	m_UpdateFiles.m_sCommonURL = m_sCommonURL;

	TCHAR szModulePath[MAX_PATH];
	TCHAR szTargetPath[MAX_PATH];
	
	TCHAR fulldir[_MAX_DIR];
	TCHAR filedrive[MAX_PATH];
	TCHAR filename[MAX_PATH];
	TCHAR fileext[MAX_PATH];

	GetModuleFileName(NULL, szModulePath, MAX_PATH);

	_tsplitpath(szModulePath, filedrive, fulldir, filename, fileext);
	
	m_UpdateFiles.m_sRootPath = TEXT("");
	m_UpdateFiles.m_sRootPath.Format(TEXT("%s%s"), filedrive, fulldir);

	if(true)
	{
		_tcscpy(szTargetPath, filedrive);
		_tcscat(szTargetPath, fulldir);
		_tcscat(szTargetPath, _T("\\autoupdate.xml"));

		m_UpdateFiles.SaveToXMLFile(szTargetPath);

		MessageBox(TEXT("�б��ļ�����ɹ������ autoupdate.xml"));
	}
	else
	{
		_tcscpy(szTargetPath, filedrive);
		_tcscat(szTargetPath, fulldir);
		_tcscat(szTargetPath, _T("\\autoupdate.lst"));

		m_UpdateFiles.SaveToLstFile(szTargetPath);

		MessageBox(TEXT("�б��ļ�����ɹ������ autoupdate.lst"));
	}

	m_sCommonLst = szTargetPath;

	SaveCommonSet();

	::ShellExecute(m_hWnd, NULL, szTargetPath, NULL, NULL, SW_SHOW);

	return;

	TCHAR szFilters[] = _T("XML File (*.xml)|*.xml||");

	CFileDialog fileDlg (false, _T("xml"), _T("*.xml"),
		OFN_FILEMUSTEXIST, szFilters, this);

	if( fileDlg.DoModal() == IDOK )
	{
		UpdateData(TRUE);
		m_UpdateFiles.m_sCommonURL = m_sCommonURL;

		m_UpdateFiles.SaveToXMLFile((LPTSTR)(LPCTSTR)fileDlg.GetPathName());
		m_sCommonXML = fileDlg.GetPathName();
		::ShellExecute(m_hWnd, NULL, fileDlg.GetPathName(), NULL, NULL, SW_SHOW);
	}

	SaveCommonSet();
}
void CAutoUpdateConfigDlg::RefreshCtrl(void)
{
	m_lstFiles.DeleteAllItems();
	m_UpdateFiles.FillListCtrl(m_lstFiles);
}

void CAutoUpdateConfigDlg::OnNMRclickLstFiles(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}

void CAutoUpdateConfigDlg::OnBnClickedBtnDelsel()
{
	POSITION pos = m_lstFiles.GetFirstSelectedItemPosition();
	if (pos == NULL)
		TRACE0("No items were selected!\n");
	else
	{
		TCHAR szText[256];
		_stprintf(szText, _T("ȷʵҪɾ���� %u ����"), m_lstFiles.GetSelectedCount());
		if (MessageBox(szText, _T("ϵͳ��ʾ"), MB_YESNOCANCEL) == IDYES) {
			while (pos)
			{
				int nItem = m_lstFiles.GetNextSelectedItem(pos);
				TRACE1("Item %d was selected!\n", nItem);
				CUpdateFile *pUpdateFile = (CUpdateFile *)m_lstFiles.GetItemData(nItem);
				m_UpdateFiles.DeleteItem(pUpdateFile);
			}
			RefreshCtrl();
		}
	}
}

void CAutoUpdateConfigDlg::OnBnClickedUpdateFile()
{
	POSITION pos = m_lstFiles.GetFirstSelectedItemPosition();
	if (pos == NULL)
		TRACE0("No items were selected!\n");
	else
	{
		int nItem = m_lstFiles.GetNextSelectedItem(pos);

		CUpdateFile *pUpdateFile = (CUpdateFile *)m_lstFiles.GetItemData(nItem);
		if(pUpdateFile != NULL)
		{
			CAutoUpdateFileDlg dlg;
			dlg.SetUpdateFile(pUpdateFile);
			if(dlg.DoModal() == IDOK)
			{
				
				RefreshCtrl();
			}
		}
	}
}


void CAutoUpdateConfigDlg::ReadCommonSet(void)
{
	TCHAR szIniPath[_MAX_PATH], szCommonURL[_MAX_PATH], szCommonXML[MAX_PATH];
	::GetModuleFileName(NULL, szIniPath, sizeof(szIniPath));
	_tcscat(szIniPath, _T(".ini"));
	::GetPrivateProfileString(_T("COMMON"), _T("COMMONURL"), _T("default"), szCommonURL, sizeof(szCommonURL), szIniPath);
	::GetPrivateProfileString(_T("COMMON"), _T("COMMONXML"), _T("autoupdate.xml"), szCommonXML, sizeof(szCommonXML), szIniPath);
	m_sCommonURL = szCommonURL;
	m_sCommonXML = szCommonXML;
	UpdateData(false);
}

void CAutoUpdateConfigDlg::SaveCommonSet(void)
{
	UpdateData();
	TCHAR szIniPath[_MAX_PATH];
	::GetModuleFileName(NULL, szIniPath, sizeof(szIniPath));
	_tcscat(szIniPath, _T(".ini"));
	::WritePrivateProfileString(_T("COMMON"), _T("COMMONURL") , m_sCommonURL, szIniPath);
	::WritePrivateProfileString(_T("COMMON"), _T("COMMONXML") , m_sCommonXML, szIniPath);
	m_UpdateFiles.m_sCommonURL = m_sCommonURL;
	m_UpdateFiles.m_sCommonXML = m_sCommonXML;
}


//void CMainFrame::OnFileOpen() 
//{
//	// TODO: Add your command handler code here
//	CFileDialog mFileDlg(TRUE,NULL,NULL,
//		OFN_ALLOWMULTISELECT,
//		_T("Text Files (*.txt)|*.txt|All Files (*.*)|*.*||"),
//		AfxGetMainWnd());
//
//	mFileDlg.m_ofn.lpstrFile=new TCHAR[NAMEBUF];   // ���¶��� lpstrFile �����С
//	memset(mFileDlg.m_ofn.lpstrFile,0,NAMEBUF);  // ��ʼ������Ļ��� 
//	mFileDlg.m_ofn.nMaxFile = NAMEBUF;           // �ض��� nMaxFile 
//	
//	TRACE("nMaxFile :%d\n",mFileDlg.m_ofn.nMaxFile);
//	
//	CString pathName;
//	if(mFileDlg.DoModal ()==IDOK)
//	{ 
//		POSITION mPos=mFileDlg.GetStartPosition();
//		while(mPos!=NULL) 
//		{ 
//			pathName=mFileDlg.GetNextPathName(mPos);
//			TRACE("%s\n",pathName);
//		} 
//	}
//	else
//		TRACE("IDCANCLE\n");
//
//	delete [] mFileDlg.m_ofn.lpstrFile;             // �м�ʹ������ͷ���Դ
//}
void CAutoUpdateConfigDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnOK();
}

void CAutoUpdateConfigDlg::OnDropFiles(HDROP hDropInfo)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	TCHAR strFilePath[MAX_PATH]; memset(strFilePath, 0x0, sizeof(strFilePath));
	int nFileCount = DragQueryFile(hDropInfo, 0xFFFFFFFF, NULL,  0);

	if(nFileCount > 0)
	{
		SaveCommonSet();

		for(int i = 0 ; i < nFileCount ; i++)
		{
			// ȡ����0���ļ�
			int nFileLen = DragQueryFile(hDropInfo, i, strFilePath,  MAX_PATH);
			if(nFileLen > 0)
			{
				m_UpdateFiles.AddUpdateFile((TCHAR *)(LPCTSTR)strFilePath);
			}
		}
		RefreshCtrl();
	}

	DragFinish(hDropInfo);

	CDialog::OnDropFiles(hDropInfo);
}

void CAutoUpdateConfigDlg::OnBnClickedButton2()
{
	m_UpdateFiles.ClearAllList();

	TCHAR dirpath[_MAX_DIR];
	TCHAR drivename[MAX_PATH];
	TCHAR filename[MAX_PATH];

	TCHAR fullpath[MAX_PATH];
	GetModuleFileName(NULL, fullpath, MAX_PATH );

	::_tsplitpath(fullpath, drivename, dirpath, filename, NULL); 

	memset(fullpath, 0x00, sizeof(fullpath));
	_tcscpy(fullpath, drivename);
	_tcscat(fullpath, TEXT("\\"));
	_tcscat(fullpath, dirpath);

	m_UpdateFiles.m_sModulePath = filename;
	m_UpdateFiles.m_sModuleDir = fullpath;

	InsertFolderFiles(fullpath);

}

void CAutoUpdateConfigDlg::InsertFolderFiles(TCHAR* dirpath)
{
	TCHAR fullpath[MAX_PATH];
	_tcscpy(fullpath, dirpath);
	_tcscat(fullpath, TEXT("\\*"));

	WIN32_FIND_DATA hFindData;
	HANDLE hFindHandle = FindFirstFile(fullpath, &hFindData);

	if(hFindHandle != INVALID_HANDLE_VALUE)
	{
		if(_tcscmp(hFindData.cFileName, TEXT(".")) != 0 && _tcscmp(hFindData.cFileName, TEXT("..")) != 0)
		{
			if((hFindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ) == FILE_ATTRIBUTE_DIRECTORY)
			{
				TCHAR findpath[_MAX_DIR];
				_tcscpy(findpath, dirpath);
				_tcscat(findpath, TEXT("\\"));
				_tcscat(findpath, hFindData.cFileName);
				_tcscat(findpath, TEXT("\\"));
				InsertFolderFiles(findpath);
			}
			else
			{
				TCHAR cFileName[MAX_PATH];
				_tcscpy(cFileName, dirpath);
				_tcscat(cFileName, hFindData.cFileName);
				m_UpdateFiles.AddUpdateFile((TCHAR *)(LPCTSTR)cFileName);
			}
		}

		while(FindNextFile(hFindHandle, &hFindData))
		{
			if(_tcscmp(hFindData.cFileName, TEXT(".")) != 0 && _tcscmp(hFindData.cFileName, TEXT("..")) != 0)
			{
				if((hFindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ) == FILE_ATTRIBUTE_DIRECTORY)
				{
					TCHAR findpath[_MAX_DIR];
					_tcscpy(findpath, dirpath);
					_tcscat(findpath, TEXT("\\"));
					_tcscat(findpath, hFindData.cFileName);
					_tcscat(findpath, TEXT("\\"));
					InsertFolderFiles(findpath);
				}
				else
				{
					TCHAR cFileName[MAX_PATH];
					_tcscpy(cFileName, dirpath);
					_tcscat(cFileName, hFindData.cFileName);
					m_UpdateFiles.AddUpdateFile((TCHAR *)(LPCTSTR)cFileName);
				}
			}
		}
		
		//CloseHandle(hFindHandle);
	}

	RefreshCtrl();
}
void CAutoUpdateConfigDlg::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CDialog::OnClose();
}

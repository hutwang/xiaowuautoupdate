// AutoUpdateConfigDlg.h : ͷ�ļ�
//

#pragma once
#include "..\\AutoUpdateClient\\updatefiles.h"
#include "afxcmn.h"


// CAutoUpdateConfigDlg �Ի���
class CAutoUpdateConfigDlg : public CDialog
{
// ����
public:
	CAutoUpdateConfigDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_AUTOUPDATECONFIG_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
private:
	CUpdateFiles m_UpdateFiles;

public:
	afx_msg void OnBnClickedBtnTest();
	CListCtrl m_lstFiles;
	afx_msg void OnBnClickedBtnAddfile();
	afx_msg void OnBnClickedBtnAddfolder();
	afx_msg void OnBnClickedBtnSaveXml();
	afx_msg void OnBnClickedBtnSave();
	void RefreshCtrl(void);
	afx_msg void OnNMRclickLstFiles(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedBtnDelsel();
	afx_msg void OnBnClickedUpdateFile();
	CString m_sCommonURL;
	CString m_sCommonXML;
	CString m_sCommonLst;
	void ReadCommonSet(void);
	void SaveCommonSet(void);
	afx_msg void OnBnClickedOk();
	afx_msg void OnDropFiles(HDROP hDropInfo);
	
	virtual BOOL DestroyWindow();
	afx_msg void OnBnClickedButton2();

	void InsertFolderFiles(TCHAR* dirpath);
	afx_msg void OnClose();
};

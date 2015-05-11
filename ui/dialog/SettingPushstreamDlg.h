#pragma once

#include "Configuration.h"
#include "afxwin.h"

// CSettingPushstreamDlg �Ի���

class CSettingPushstreamDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSettingPushstreamDlg)

public:
	CSettingPushstreamDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSettingPushstreamDlg();

// �Ի�������
	enum { IDD = IDD_SET_PUSHSTREAM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
private:
	BOOL m_bEnableMajor;
	BOOL m_bEnableMinor;
	CString m_strMajorUrl;
	CString m_strMinorUrl;

public:
	void GetPushstreamConfig(PushStreamAttribute * config);
private:
	CEdit m_editMajorUrl;
	CEdit m_editMinorUrl;
public:
	afx_msg void OnBnClickedPushstreamEnableMajor();
	afx_msg void OnBnClickedPushstreamEnableMinor();
};

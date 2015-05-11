#pragma once

#include "Configuration.h"
#include "afxwin.h"

// CSettingPushstreamDlg 对话框

class CSettingPushstreamDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSettingPushstreamDlg)

public:
	CSettingPushstreamDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSettingPushstreamDlg();

// 对话框数据
	enum { IDD = IDD_SET_PUSHSTREAM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

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

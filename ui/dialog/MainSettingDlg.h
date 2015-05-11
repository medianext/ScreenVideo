#pragma once
#include "afxcmn.h"

#include "SettingBasicDlg.h"
#include "SettingCodecDlg.h"
#include "SettingRecordDlg.h"
#include "SettingLiveDlg.h"
#include "SettingPushstreamDlg.h"
#include "SettingAboutDlg.h"

enum DLG_SET_INDEX_E
{
	DLG_SET_INDEX_BASIC = 0,
	DLG_SET_INDEX_CODEC,
	DLG_SET_INDEX_RECORD,
	DLG_SET_INDEX_LIVE,
	DLG_SET_INDEX_PUSHSTREAM,
	DLG_SET_INDEX_ABOUT
};
// CMainSettingDlg 对话框

class CMainSettingDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMainSettingDlg)

public:
	CMainSettingDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMainSettingDlg();

// 对话框数据
	enum { IDD = IDD_SETTING_DIALOG };

	CSettingBasicDlg * m_dlgBasicSet;
	CSettingCodecDlg * m_dlgCodecSet;
	CSettingRecordDlg * m_dlgRecordSet;
	CSettingLiveDlg * m_dlgLiveSet;
	CSettingPushstreamDlg * m_dlgPushstreamSet;
	CSettingAboutDlg * m_dlgAboutSet;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

public:
	void SaveConfiguration();

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	CTabCtrl m_MainTab;
	afx_msg void OnMainTabSelChange(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnClose();
	afx_msg void OnBnClickedApply();
	afx_msg void OnBnClickedOk();
};

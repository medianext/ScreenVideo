#pragma once
#include "afxwin.h"


// CSettingBasicDlg 对话框

class CSettingBasicDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSettingBasicDlg)

public:
	CSettingBasicDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSettingBasicDlg();

// 对话框数据
	enum { IDD = IDD_SET_BASIC };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	bool m_bCloseQuit;
	BOOL m_bAutoHide;
	BOOL m_bAutoRecord;
	BOOL m_bAutoLive;
	BOOL m_bAutoPushstream;
public:
	virtual BOOL OnInitDialog();
	CButton m_radioEnableClose;
	CButton m_radioEnableQuit;
	afx_msg void OnBnClickedBasicEnableAutomin();
	afx_msg void OnBnClickedBasicEnableClose();
	afx_msg void OnBnClickedBasicEnableQuit();
	afx_msg void OnBnClickedBasicEnableAutorecord();
	afx_msg void OnBnClickedBasicEnableAutolive();
	afx_msg void OnBnClickedBasicEnableAutopush();
};

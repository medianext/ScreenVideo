#pragma once
#include "afxwin.h"


// CSettingBasicDlg �Ի���

class CSettingBasicDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSettingBasicDlg)

public:
	CSettingBasicDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSettingBasicDlg();

// �Ի�������
	enum { IDD = IDD_SET_BASIC };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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

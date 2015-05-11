#pragma once

#include "Configuration.h"
#include "afxwin.h"
#include "afxcmn.h"

// CSettingLiveDlg 对话框

class CSettingLiveDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSettingLiveDlg)

public:
	CSettingLiveDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSettingLiveDlg();

// 对话框数据
	enum { IDD = IDD_SET_LIVE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
private:
	BOOL m_bEnableRTMP;
	BOOL m_bEnableRTSP;
	BOOL m_bEnableWDM;
	BOOL m_bEnableP2P;
	BOOL m_bEnableMULTICAST;
	short m_iRtmpPort;
	short m_iRtspPort;
	short m_iWdmPort;
	short m_iP2pPort;
	short m_iMulticastPort;
	DWORD m_dwMulticastIP;

	CEdit m_editRtmpPort;
	CEdit m_editRtspPort;
	CEdit m_editWdmPort;
	CEdit m_editP2pPort;
	CEdit m_editMulticastPort;
	CIPAddressCtrl m_editMulticastIP;
public:
	afx_msg void OnBnClickedLiveEnableRtmp();
	afx_msg void OnBnClickedLiveEnableRtsp();
	afx_msg void OnBnClickedLiveEnableWdm();
	afx_msg void OnBnClickedLiveEnableP2p();
	afx_msg void OnBnClickedLiveEnableMulticast();

	void GetLiveConfig(LiveAttribute *config);
};

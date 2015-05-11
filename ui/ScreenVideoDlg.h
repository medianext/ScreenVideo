
// ScreenVideoDlg.h : 头文件
//

#pragma once
#define WM_NOTYFICATION_MESSAGE (WM_USER+1000)

#include "MainSettingDlg.h"

// CScreenVideoDlg 对话框
class CScreenVideoDlg : public CDialogEx
{
// 构造
public:
	CScreenVideoDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_SCREENVIDEO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
private:
	CMainSettingDlg m_MainSettingDlg;
// 实现
protected:
	HICON m_hIcon;
	NOTIFYICONDATA m_NotifyIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedRecordStart();
	afx_msg void OnBnClickedRecordStop();
	afx_msg void OnBnClickedRecordSetting();
	afx_msg LRESULT OnNotifyMsg(WPARAM wparam, LPARAM lparam);
	afx_msg void OnClose();
	afx_msg void OnDestroy();
	afx_msg void OnNcPaint();
};

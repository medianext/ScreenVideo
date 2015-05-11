#pragma once


// SettingAboutDlg 对话框

class CSettingAboutDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSettingAboutDlg)

public:
	CSettingAboutDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSettingAboutDlg();

// 对话框数据
	enum { IDD = IDD_SET_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};

#pragma once


// SettingAboutDlg �Ի���

class CSettingAboutDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSettingAboutDlg)

public:
	CSettingAboutDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSettingAboutDlg();

// �Ի�������
	enum { IDD = IDD_SET_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};

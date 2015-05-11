
// ScreenVideoDlg.h : ͷ�ļ�
//

#pragma once
#define WM_NOTYFICATION_MESSAGE (WM_USER+1000)

#include "MainSettingDlg.h"

// CScreenVideoDlg �Ի���
class CScreenVideoDlg : public CDialogEx
{
// ����
public:
	CScreenVideoDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_SCREENVIDEO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��
private:
	CMainSettingDlg m_MainSettingDlg;
// ʵ��
protected:
	HICON m_hIcon;
	NOTIFYICONDATA m_NotifyIcon;

	// ���ɵ���Ϣӳ�亯��
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

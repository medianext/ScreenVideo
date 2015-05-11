#pragma once

#include "Configuration.h"

// CSettingRecordDlg �Ի���

class CSettingRecordDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSettingRecordDlg)

public:
	CSettingRecordDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSettingRecordDlg();

// �Ի�������
	enum { IDD = IDD_SET_RECORD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
private:
	int m_iRecordType;
	CString m_strRecordPath;
	CString m_strRecordName;
	int m_iAutoSplitTime;
public:
	virtual BOOL OnInitDialog();

	void GetRecordConfig(RecordAttribute *config);
};

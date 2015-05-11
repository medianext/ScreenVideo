#pragma once

#include "Configuration.h"

// CSettingRecordDlg 对话框

class CSettingRecordDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSettingRecordDlg)

public:
	CSettingRecordDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSettingRecordDlg();

// 对话框数据
	enum { IDD = IDD_SET_RECORD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

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

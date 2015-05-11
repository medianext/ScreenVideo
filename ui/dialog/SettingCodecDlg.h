#pragma once

#include "Configuration.h"

// CSettingCodecDlg 对话框

class CSettingCodecDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSettingCodecDlg)

public:
	CSettingCodecDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSettingCodecDlg();

// 对话框数据
	enum { IDD = IDD_SET_CODEC };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	int m_iMajorCodecType;
	int m_iMajorResolution;
	int m_iMajorFps;
	int m_iMajorBitrateType;
	int m_iMajorBitrate;
	int m_iMajorInternal;
	int m_iMinorCodecType;
	int m_iMinorResolution;
	int m_iMinorFps;
	int m_iMinorBitrateType;
	int m_iMinorBitrate;
	int m_iMinorInternal;
public:
	virtual BOOL OnInitDialog();

	void GetCodecConfig(CodecAttribute *major, CodecAttribute *minor);
};

#pragma once

#include "Configuration.h"

// CSettingCodecDlg �Ի���

class CSettingCodecDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSettingCodecDlg)

public:
	CSettingCodecDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSettingCodecDlg();

// �Ի�������
	enum { IDD = IDD_SET_CODEC };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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

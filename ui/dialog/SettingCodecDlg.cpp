// SettingCodecDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ScreenVideo.h"
#include "SettingCodecDlg.h"
#include "afxdialogex.h"

#include "Configuration.h"


// CSettingCodecDlg 对话框

IMPLEMENT_DYNAMIC(CSettingCodecDlg, CDialogEx)

CSettingCodecDlg::CSettingCodecDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSettingCodecDlg::IDD, pParent)
	, m_iMajorCodecType(0)
	, m_iMajorResolution(0)
	, m_iMajorFps(25)
	, m_iMajorBitrateType(0)
	, m_iMajorBitrate(4096)
	, m_iMajorInternal(30)
	, m_iMinorCodecType(0)
	, m_iMinorResolution(0)
	, m_iMinorFps(25)
	, m_iMinorBitrateType(0)
	, m_iMinorBitrate(1024)
	, m_iMinorInternal(30)
{

}

CSettingCodecDlg::~CSettingCodecDlg()
{
}

void CSettingCodecDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_CBIndex(pDX, IDC_CODEC_MAJOR_CODECTYPE, m_iMajorCodecType);
	DDX_CBIndex(pDX, IDC_CODEC_MAJOR_RESOLUTION, m_iMajorResolution);
	DDX_Text(pDX, IDC_CODEC_MAJOR_FPS, m_iMajorFps);
	DDX_CBIndex(pDX, IDC_CODEC_MAJOR_BITRATETYPE, m_iMajorBitrateType);
	DDX_Text(pDX, IDC_CODEC_MAJOR_BITRATE, m_iMajorBitrate);
	DDX_Text(pDX, IDC_CODEC_MAJOR_INTERVAL, m_iMajorInternal);
	DDX_CBIndex(pDX, IDC_CODEC_MINOR_CODECTYPE, m_iMinorCodecType);
	DDX_CBIndex(pDX, IDC_CODEC_MINOR_RESOLUTION, m_iMinorResolution);
	DDX_Text(pDX, IDC_CODEC_MINOR_FPS, m_iMajorFps);
	DDX_CBIndex(pDX, IDC_CODEC_MINOR_BITRATETYPE, m_iMinorBitrateType);
	DDX_Text(pDX, IDC_CODEC_MINOR_BITRATE, m_iMinorBitrate);
	DDX_Text(pDX, IDC_CODEC_MINOR_INTERVAL, m_iMinorInternal);
}


BEGIN_MESSAGE_MAP(CSettingCodecDlg, CDialogEx)
END_MESSAGE_MAP()


// CSettingCodecDlg 消息处理程序


BOOL CSettingCodecDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CodecAttribute * major = Configuration::GetInstance()->GetMajorCodecCoinfig();
	CodecAttribute * minor = Configuration::GetInstance()->GetMinorCodecCoinfig();

	m_iMajorCodecType = major->codecType;
	if (major->iWidth == 1920 && major->iHeight == 1080)
	{
		m_iMajorResolution = 0;
	}
	else if (major->iWidth == 1280 && major->iHeight == 720)
	{
		m_iMajorResolution = 1;
	}
	else if (major->iWidth == 1600 && major->iHeight == 900)
	{
		m_iMajorResolution = 2;
	}
	else if (major->iWidth == 1440 && major->iHeight == 900)
	{
		m_iMajorResolution = 3;
	}
	else if (major->iWidth == 1024 && major->iHeight == 768)
	{
		m_iMajorResolution = 4;
	}
	else
	{
		m_iMajorResolution = 0;
	}
	m_iMajorFps = major->iFps;
	m_iMajorBitrateType = major->bitrateMethod;
	m_iMajorBitrate = major->iBitrate;
	m_iMajorInternal = major->iInternal;

	m_iMinorCodecType = minor->codecType;
	if (minor->iWidth == 960 && minor->iHeight == 540)
	{
		m_iMinorResolution = 0;
	}
	else if (minor->iWidth == 640 && minor->iHeight == 360)
	{
		m_iMinorResolution = 1;
	}
	else if (minor->iWidth == 800 && minor->iHeight == 600)
	{
		m_iMinorResolution = 2;
	}
	else if (minor->iWidth == 680 && minor->iHeight == 480)
	{
		m_iMinorResolution = 3;
	}
	else
	{
		m_iMinorResolution = 0;
	}
	m_iMinorFps = minor->iFps;
	m_iMinorBitrateType = minor->bitrateMethod;
	m_iMinorBitrate = minor->iBitrate;
	m_iMinorInternal = minor->iInternal;
	this->UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}

void CSettingCodecDlg::GetCodecConfig(CodecAttribute *major, CodecAttribute *minor)
{
	this->UpdateData(TRUE);
	if (major)
	{
		major->codecType = (CODEC_TYPE_E)m_iMajorCodecType;
		switch (m_iMajorResolution)
		{
		case 0:
			major->iWidth = 1920;
			major->iHeight = 1080;
			break;
		case 1:
			major->iWidth = 1280;
			major->iHeight = 720;
			break;
		case 2:
			major->iWidth = 1600;
			major->iHeight = 900;
			break;
		case 3:
			major->iWidth = 1440;
			major->iHeight = 900;
			break;
		case 4:
			major->iWidth = 1024;
			major->iHeight = 768;
			break;
		default:
			major->iWidth = 1920;
			major->iHeight = 1080;
			break;
		}
		major->iFps = m_iMajorFps;
		major->bitrateMethod = (BITRATE_METHOD_E)m_iMajorBitrateType;
		major->iBitrate = m_iMajorBitrate;
		major->iInternal = m_iMajorInternal;
	}


	if (minor)
	{
		minor->codecType = (CODEC_TYPE_E)m_iMinorCodecType;
		switch (m_iMinorResolution)
		{
		case 0:
			minor->iWidth = 960;
			minor->iHeight = 540;
			break;
		case 1:
			minor->iWidth = 640;
			minor->iHeight = 360;
			break;
		case 2:
			minor->iWidth = 800;
			minor->iHeight = 600;
			break;
		case 3:
			minor->iWidth = 640;
			minor->iHeight = 480;
			break;
		default:
			minor->iWidth = 960;
			minor->iHeight = 540;
			break;
		}
		minor->iFps = m_iMinorFps;
		minor->bitrateMethod = (BITRATE_METHOD_E)m_iMinorBitrateType;
		minor->iBitrate = m_iMinorBitrate;
		minor->iInternal = m_iMinorInternal;
	}
}
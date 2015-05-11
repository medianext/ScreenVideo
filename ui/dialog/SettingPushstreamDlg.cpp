// SettingPushstreamDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ScreenVideo.h"
#include "SettingPushstreamDlg.h"
#include "afxdialogex.h"


// CSettingPushstreamDlg 对话框

IMPLEMENT_DYNAMIC(CSettingPushstreamDlg, CDialogEx)

CSettingPushstreamDlg::CSettingPushstreamDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSettingPushstreamDlg::IDD, pParent)
	, m_bEnableMajor(FALSE)
	, m_bEnableMinor(TRUE)
	, m_strMajorUrl(_T("rtmp://127.0.0.1:1935/live/screen"))
	, m_strMinorUrl(_T("rtmp://127.0.0.1:1935/live/screen_sub"))
{

}

CSettingPushstreamDlg::~CSettingPushstreamDlg()
{
}

void CSettingPushstreamDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_PUSHSTREAM_ENABLE_MAJOR, m_bEnableMajor);
	DDX_Check(pDX, IDC_PUSHSTREAM_ENABLE_MINOR, m_bEnableMinor);
	DDX_Text(pDX, IDC_PUSHSTREAM_MAJOR_URL, m_strMajorUrl);
	DDX_Text(pDX, IDC_PUSHSTREAM_MINOR_URL, m_strMinorUrl);
	DDX_Control(pDX, IDC_PUSHSTREAM_MAJOR_URL, m_editMajorUrl);
	DDX_Control(pDX, IDC_PUSHSTREAM_MINOR_URL, m_editMinorUrl);
}


BEGIN_MESSAGE_MAP(CSettingPushstreamDlg, CDialogEx)
	ON_BN_CLICKED(IDC_PUSHSTREAM_ENABLE_MAJOR, &CSettingPushstreamDlg::OnBnClickedPushstreamEnableMajor)
	ON_BN_CLICKED(IDC_PUSHSTREAM_ENABLE_MINOR, &CSettingPushstreamDlg::OnBnClickedPushstreamEnableMinor)
END_MESSAGE_MAP()


// CSettingPushstreamDlg 消息处理程序


BOOL CSettingPushstreamDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	PushStreamAttribute * config = Configuration::GetInstance()->GetPushstramConfig();
	this->m_bEnableMajor = config->EnableMajor;
	this->m_bEnableMinor = config->EnableMinor;
	this->m_strMajorUrl = config->MajorUrl.c_str();
	this->m_strMinorUrl = config->MinorUrl.c_str();
	if (this->m_bEnableMajor)
	{
		this->m_editMajorUrl.EnableWindow(TRUE);
	} 
	else
	{
		this->m_editMajorUrl.EnableWindow(FALSE);
	}
	if (this->m_bEnableMinor)
	{
		this->m_editMinorUrl.EnableWindow(TRUE);
	}
	else
	{
		this->m_editMinorUrl.EnableWindow(FALSE);
	}
	this->UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}

void CSettingPushstreamDlg::GetPushstreamConfig(PushStreamAttribute * config)
{
	if (config)
	{
		this->UpdateData(TRUE);
		char tmp[1024];
		config->EnableMajor = m_bEnableMajor;
		config->EnableMinor = m_bEnableMinor;
		wcstombs(tmp, m_strMajorUrl.GetBuffer(), 1024);
		config->MajorUrl = tmp;
		wcstombs(tmp, m_strMinorUrl.GetBuffer(), 1024);
		config->MinorUrl = tmp;
	}
}

void CSettingPushstreamDlg::OnBnClickedPushstreamEnableMajor()
{
	// TODO:  在此添加控件通知处理程序代码
	this->UpdateData(TRUE);
	if (this->m_bEnableMajor)
	{
		this->m_editMajorUrl.EnableWindow(TRUE);
	}
	else
	{
		this->m_editMajorUrl.EnableWindow(FALSE);
	}
}


void CSettingPushstreamDlg::OnBnClickedPushstreamEnableMinor()
{
	// TODO:  在此添加控件通知处理程序代码
	this->UpdateData(TRUE);
	if (this->m_bEnableMinor)
	{
		this->m_editMinorUrl.EnableWindow(TRUE);
	}
	else
	{
		this->m_editMinorUrl.EnableWindow(FALSE);
	}
}

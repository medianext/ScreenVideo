// SettingBasicDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ScreenVideo.h"
#include "SettingBasicDlg.h"
#include "afxdialogex.h"

#include "Configuration.h"

// CSettingBasicDlg 对话框

IMPLEMENT_DYNAMIC(CSettingBasicDlg, CDialogEx)

CSettingBasicDlg::CSettingBasicDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSettingBasicDlg::IDD, pParent)
	, m_bCloseQuit(true)
	, m_bAutoHide(FALSE)
	, m_bAutoRecord(FALSE)
	, m_bAutoLive(FALSE)
	, m_bAutoPushstream(FALSE)
{

}

CSettingBasicDlg::~CSettingBasicDlg()
{
}

void CSettingBasicDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_BASIC_ENABLE_AUTOMIN, m_bAutoHide);
	DDX_Check(pDX, IDC_BASIC_ENABLE_AUTORECORD, m_bAutoRecord);
	DDX_Check(pDX, IDC_BASIC_ENABLE_AUTOLIVE, m_bAutoLive);
	DDX_Check(pDX, IDC_BASIC_ENABLE_AUTOPUSH, m_bAutoPushstream);
	DDX_Control(pDX, IDC_BASIC_ENABLE_CLOSE, m_radioEnableClose);
	DDX_Control(pDX, IDC_BASIC_ENABLE_QUIT, m_radioEnableQuit);
}


BEGIN_MESSAGE_MAP(CSettingBasicDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BASIC_ENABLE_AUTOMIN, &CSettingBasicDlg::OnBnClickedBasicEnableAutomin)
	ON_BN_CLICKED(IDC_BASIC_ENABLE_CLOSE, &CSettingBasicDlg::OnBnClickedBasicEnableClose)
	ON_BN_CLICKED(IDC_BASIC_ENABLE_QUIT, &CSettingBasicDlg::OnBnClickedBasicEnableQuit)
	ON_BN_CLICKED(IDC_BASIC_ENABLE_AUTORECORD, &CSettingBasicDlg::OnBnClickedBasicEnableAutorecord)
	ON_BN_CLICKED(IDC_BASIC_ENABLE_AUTOLIVE, &CSettingBasicDlg::OnBnClickedBasicEnableAutolive)
	ON_BN_CLICKED(IDC_BASIC_ENABLE_AUTOPUSH, &CSettingBasicDlg::OnBnClickedBasicEnableAutopush)
END_MESSAGE_MAP()


// CSettingBasicDlg 消息处理程序


BOOL CSettingBasicDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	Configuration * pConfig = Configuration::GetInstance();
	this->m_bCloseQuit = pConfig->IsQuitApp();
	this->m_bAutoHide = pConfig->IsAutoHideWindow();
	this->m_bAutoRecord = pConfig->IsAutoRecord();
	this->m_bAutoLive = pConfig->IsAutoLive();
	this->m_bAutoPushstream = pConfig->IsAutoPushstream();

	if (this->m_bCloseQuit == true)
	{
		m_radioEnableClose.SetCheck(0);
		m_radioEnableQuit.SetCheck(1);
	}
	else
	{
		m_radioEnableClose.SetCheck(1);
		m_radioEnableQuit.SetCheck(0);
	}
	this->UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}

void CSettingBasicDlg::OnBnClickedBasicEnableClose()
{
	// TODO:  在此添加控件通知处理程序代码
	if (m_radioEnableClose.GetCheck())
	{
		Configuration::GetInstance()->SetQuitApp(false);
	}
	else
	{
		Configuration::GetInstance()->SetQuitApp(true);
	}
}

void CSettingBasicDlg::OnBnClickedBasicEnableQuit()
{
	// TODO:  在此添加控件通知处理程序代码
	if (m_radioEnableQuit.GetCheck())
	{
		Configuration::GetInstance()->SetQuitApp(true);
	}
	else
	{
		Configuration::GetInstance()->SetQuitApp(false);
	}
}

void CSettingBasicDlg::OnBnClickedBasicEnableAutomin()
{
	// TODO:  在此添加控件通知处理程序代码
	this->UpdateData(TRUE);
	if (this->m_bAutoHide)
	{
		Configuration::GetInstance()->SetAutoHideWindow(true);
	}
	else
	{
		Configuration::GetInstance()->SetAutoHideWindow(false);
	}
}



void CSettingBasicDlg::OnBnClickedBasicEnableAutorecord()
{
	// TODO:  在此添加控件通知处理程序代码
	this->UpdateData(TRUE);
	if (this->m_bAutoRecord)
	{
		Configuration::GetInstance()->SetAutoRecord(true);
	}
	else
	{
		Configuration::GetInstance()->SetAutoRecord(false);
	}
}


void CSettingBasicDlg::OnBnClickedBasicEnableAutolive()
{
	// TODO:  在此添加控件通知处理程序代码
	this->UpdateData(TRUE);
	if (this->m_bAutoLive)
	{
		Configuration::GetInstance()->SetAutoLive(true);
	}
	else
	{
		Configuration::GetInstance()->SetAutoLive(false);
	}
}


void CSettingBasicDlg::OnBnClickedBasicEnableAutopush()
{
	// TODO:  在此添加控件通知处理程序代码
	this->UpdateData(TRUE);
	if (this->m_bAutoPushstream)
	{
		Configuration::GetInstance()->SetAutoPushstream(true);
	}
	else
	{
		Configuration::GetInstance()->SetAutoPushstream(false);
	}
}

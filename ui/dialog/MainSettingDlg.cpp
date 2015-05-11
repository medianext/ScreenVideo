// MainSettingDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ScreenVideo.h"
#include "MainSettingDlg.h"
#include "SettingRecordDlg.h"
#include "afxdialogex.h"


// CMainSettingDlg 对话框

IMPLEMENT_DYNAMIC(CMainSettingDlg, CDialogEx)

CMainSettingDlg::CMainSettingDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMainSettingDlg::IDD, pParent)
{
	m_dlgBasicSet = new CSettingBasicDlg;
	m_dlgCodecSet = new CSettingCodecDlg();
	m_dlgRecordSet = new CSettingRecordDlg();
	m_dlgLiveSet = new CSettingLiveDlg();
	m_dlgPushstreamSet = new CSettingPushstreamDlg;
	m_dlgAboutSet = new CSettingAboutDlg();
}

CMainSettingDlg::~CMainSettingDlg()
{
	delete m_dlgBasicSet;
	delete m_dlgCodecSet;
	delete m_dlgRecordSet;
	delete m_dlgLiveSet;
	delete m_dlgPushstreamSet;
	delete m_dlgAboutSet;
}

void CMainSettingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MAINTAB, m_MainTab);
}


BEGIN_MESSAGE_MAP(CMainSettingDlg, CDialogEx)
	ON_NOTIFY(TCN_SELCHANGE, IDC_MAINTAB, &CMainSettingDlg::OnMainTabSelChange)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_APPLY, &CMainSettingDlg::OnBnClickedApply)
	ON_BN_CLICKED(IDOK, &CMainSettingDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CMainSettingDlg 消息处理程序


BOOL CMainSettingDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_MainTab.InsertItem(DLG_SET_INDEX_BASIC, TEXT("基本设置"));
	m_MainTab.InsertItem(DLG_SET_INDEX_CODEC, TEXT("编码设置"));
	m_MainTab.InsertItem(DLG_SET_INDEX_RECORD, TEXT("录像设置"));
	m_MainTab.InsertItem(DLG_SET_INDEX_LIVE, TEXT("直播设置"));
	m_MainTab.InsertItem(DLG_SET_INDEX_PUSHSTREAM, TEXT("推流设置"));
	m_MainTab.InsertItem(DLG_SET_INDEX_ABOUT, TEXT("关于"));

	CRect rect;
	m_MainTab.GetClientRect(&rect);
	rect.top += 21;
	rect.bottom -= 3;
	rect.left += 3;
	rect.right -= 3;
	m_dlgBasicSet->Create(IDD_SET_BASIC, &m_MainTab);
	m_dlgBasicSet->MoveWindow(&rect);
	m_dlgCodecSet->Create(IDD_SET_CODEC, &m_MainTab);
	m_dlgCodecSet->MoveWindow(&rect);
	m_dlgRecordSet->Create(IDD_SET_RECORD, &m_MainTab);
	m_dlgRecordSet->MoveWindow(&rect);
	m_dlgLiveSet->Create(IDD_SET_LIVE, &m_MainTab);
	m_dlgLiveSet->MoveWindow(&rect);
	m_dlgPushstreamSet->Create(IDD_SET_PUSHSTREAM, &m_MainTab);
	m_dlgPushstreamSet->MoveWindow(&rect);
	m_dlgAboutSet->Create(IDD_SET_ABOUTBOX, &m_MainTab);
	m_dlgAboutSet->MoveWindow(&rect);

	m_MainTab.SetCurSel(0);
	m_dlgBasicSet->ShowWindow(SW_SHOW);


	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void CMainSettingDlg::OnOK()
{
	// TODO:  在此添加专用代码和/或调用基类

	CDialogEx::OnOK();
}


void CMainSettingDlg::OnMainTabSelChange(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO:  在此添加控件通知处理程序代码
	*pResult = 0;
	int index = m_MainTab.GetCurSel();
	if (index == DLG_SET_INDEX_BASIC)
	{
		m_dlgBasicSet->ShowWindow(SW_SHOW);
		m_dlgCodecSet->ShowWindow(SW_HIDE);
		m_dlgRecordSet->ShowWindow(SW_HIDE);
		m_dlgLiveSet->ShowWindow(SW_HIDE);
		m_dlgPushstreamSet->ShowWindow(SW_HIDE);
		m_dlgAboutSet->ShowWindow(SW_HIDE);
	}
	else if (index == DLG_SET_INDEX_CODEC)
	{
		m_dlgBasicSet->ShowWindow(SW_HIDE);
		m_dlgCodecSet->ShowWindow(SW_SHOW);
		m_dlgRecordSet->ShowWindow(SW_HIDE);
		m_dlgLiveSet->ShowWindow(SW_HIDE);
		m_dlgPushstreamSet->ShowWindow(SW_HIDE);
		m_dlgAboutSet->ShowWindow(SW_HIDE);
	}
	else if (index == DLG_SET_INDEX_RECORD)
	{
		m_dlgBasicSet->ShowWindow(SW_HIDE);
		m_dlgCodecSet->ShowWindow(SW_HIDE);
		m_dlgRecordSet->ShowWindow(SW_SHOW);
		m_dlgLiveSet->ShowWindow(SW_HIDE);
		m_dlgPushstreamSet->ShowWindow(SW_HIDE);
		m_dlgAboutSet->ShowWindow(SW_HIDE);
	}
	else if (index == DLG_SET_INDEX_LIVE)
	{
		m_dlgBasicSet->ShowWindow(SW_HIDE);
		m_dlgCodecSet->ShowWindow(SW_HIDE);
		m_dlgRecordSet->ShowWindow(SW_HIDE);
		m_dlgLiveSet->ShowWindow(SW_SHOW);
		m_dlgPushstreamSet->ShowWindow(SW_HIDE);
		m_dlgAboutSet->ShowWindow(SW_HIDE);
	}
	else if (index == DLG_SET_INDEX_PUSHSTREAM)
	{
		m_dlgBasicSet->ShowWindow(SW_HIDE);
		m_dlgCodecSet->ShowWindow(SW_HIDE);
		m_dlgRecordSet->ShowWindow(SW_HIDE);
		m_dlgLiveSet->ShowWindow(SW_HIDE);
		m_dlgPushstreamSet->ShowWindow(SW_SHOW);
		m_dlgAboutSet->ShowWindow(SW_HIDE);
	}
	else if (index == DLG_SET_INDEX_ABOUT)
	{
		m_dlgBasicSet->ShowWindow(SW_HIDE);
		m_dlgCodecSet->ShowWindow(SW_HIDE);
		m_dlgRecordSet->ShowWindow(SW_HIDE);
		m_dlgLiveSet->ShowWindow(SW_HIDE);
		m_dlgPushstreamSet->ShowWindow(SW_HIDE);
		m_dlgAboutSet->ShowWindow(SW_SHOW);
	}
	else{
	}
}


void CMainSettingDlg::OnClose()
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值

	m_dlgCodecSet->DestroyWindow();
	m_dlgRecordSet->DestroyWindow();
	m_dlgLiveSet->DestroyWindow();
	m_dlgAboutSet->DestroyWindow();
	CDialogEx::OnClose();
}

void CMainSettingDlg::SaveConfiguration()
{
	Configuration *config = Configuration::GetInstance();
	m_dlgCodecSet->GetCodecConfig(config->GetMajorCodecCoinfig(), config->GetMinorCodecCoinfig());
	m_dlgRecordSet->GetRecordConfig(config->GetRecordConfig());
	m_dlgLiveSet->GetLiveConfig(config->GetLiveConfig());
	m_dlgPushstreamSet->GetPushstreamConfig(config->GetPushstramConfig());
	config->Save();
}

void CMainSettingDlg::OnBnClickedApply()
{
	// TODO:  在此添加控件通知处理程序代码
	this->SaveConfiguration();
}


void CMainSettingDlg::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	this->SaveConfiguration();
	CDialogEx::OnOK();
}

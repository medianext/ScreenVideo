// MainSettingDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ScreenVideo.h"
#include "MainSettingDlg.h"
#include "SettingRecordDlg.h"
#include "afxdialogex.h"


// CMainSettingDlg �Ի���

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


// CMainSettingDlg ��Ϣ�������


BOOL CMainSettingDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_MainTab.InsertItem(DLG_SET_INDEX_BASIC, TEXT("��������"));
	m_MainTab.InsertItem(DLG_SET_INDEX_CODEC, TEXT("��������"));
	m_MainTab.InsertItem(DLG_SET_INDEX_RECORD, TEXT("¼������"));
	m_MainTab.InsertItem(DLG_SET_INDEX_LIVE, TEXT("ֱ������"));
	m_MainTab.InsertItem(DLG_SET_INDEX_PUSHSTREAM, TEXT("��������"));
	m_MainTab.InsertItem(DLG_SET_INDEX_ABOUT, TEXT("����"));

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
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void CMainSettingDlg::OnOK()
{
	// TODO:  �ڴ����ר�ô����/����û���

	CDialogEx::OnOK();
}


void CMainSettingDlg::OnMainTabSelChange(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ

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
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	this->SaveConfiguration();
}


void CMainSettingDlg::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	this->SaveConfiguration();
	CDialogEx::OnOK();
}

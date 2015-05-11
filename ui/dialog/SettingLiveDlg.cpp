// SettingLiveDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ScreenVideo.h"
#include "SettingLiveDlg.h"
#include "afxdialogex.h"


// CSettingLiveDlg 对话框

IMPLEMENT_DYNAMIC(CSettingLiveDlg, CDialogEx)

CSettingLiveDlg::CSettingLiveDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSettingLiveDlg::IDD, pParent)
	, m_bEnableRTMP(FALSE)
	, m_bEnableRTSP(FALSE)
	, m_bEnableWDM(TRUE)
	, m_bEnableP2P(FALSE)
	, m_bEnableMULTICAST(FALSE)
	, m_iRtmpPort(1935)
	, m_iRtspPort(554)
	, m_iWdmPort(1989)
	, m_iP2pPort(2015)
	, m_iMulticastPort(1990)
	, m_dwMulticastIP(0)
{

}

CSettingLiveDlg::~CSettingLiveDlg()
{
}

void CSettingLiveDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_LIVE_ENABLE_RTMP, m_bEnableRTMP);
	DDX_Check(pDX, IDC_LIVE_ENABLE_RTSP, m_bEnableRTSP);
	DDX_Check(pDX, IDC_LIVE_ENABLE_WDM, m_bEnableWDM);
	DDX_Check(pDX, IDC_LIVE_ENABLE_P2P, m_bEnableP2P);
	DDX_Check(pDX, IDC_LIVE_ENABLE_MULTICAST, m_bEnableMULTICAST);
	DDX_Text(pDX, IDC_LIVE_PORT_RTMP, m_iRtmpPort);
	DDX_Text(pDX, IDC_LIVE_PORT_RTSP, m_iRtspPort);
	DDX_Text(pDX, IDC_LIVE_PORT_WDM, m_iWdmPort);
	DDX_Text(pDX, IDC_LIVE_PORT_P2P, m_iP2pPort);
	DDX_Text(pDX, IDC_LIVE_PORT_MULTICAST, m_iMulticastPort);
	DDX_IPAddress(pDX, IDC_LIVE_IP_MULTICAST, m_dwMulticastIP);
	DDX_Control(pDX, IDC_LIVE_PORT_RTMP, m_editRtmpPort);
	DDX_Control(pDX, IDC_LIVE_PORT_RTSP, m_editRtspPort);
	DDX_Control(pDX, IDC_LIVE_PORT_WDM, m_editWdmPort);
	DDX_Control(pDX, IDC_LIVE_PORT_P2P, m_editP2pPort);
	DDX_Control(pDX, IDC_LIVE_PORT_MULTICAST, m_editMulticastPort);
	DDX_Control(pDX, IDC_LIVE_IP_MULTICAST, m_editMulticastIP);
}


BEGIN_MESSAGE_MAP(CSettingLiveDlg, CDialogEx)
	ON_BN_CLICKED(IDC_LIVE_ENABLE_RTMP, &CSettingLiveDlg::OnBnClickedLiveEnableRtmp)
	ON_BN_CLICKED(IDC_LIVE_ENABLE_RTSP, &CSettingLiveDlg::OnBnClickedLiveEnableRtsp)
	ON_BN_CLICKED(IDC_LIVE_ENABLE_WDM, &CSettingLiveDlg::OnBnClickedLiveEnableWdm)
	ON_BN_CLICKED(IDC_LIVE_ENABLE_P2P, &CSettingLiveDlg::OnBnClickedLiveEnableP2p)
	ON_BN_CLICKED(IDC_LIVE_ENABLE_MULTICAST, &CSettingLiveDlg::OnBnClickedLiveEnableMulticast)
END_MESSAGE_MAP()


// CSettingLiveDlg 消息处理程序


BOOL CSettingLiveDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	LiveAttribute * config = Configuration::GetInstance()->GetLiveConfig();
	if (config)
	{
		this->m_bEnableRTMP = config->EnableRtmp;
		this->m_iRtmpPort = config->RtmpPort;
		if (this->m_bEnableRTMP)
		{
			m_editRtmpPort.EnableWindow(TRUE);
		} 
		else
		{
			m_editRtmpPort.EnableWindow(FALSE);
		}
		this->m_bEnableRTSP = config->EnableRtsp;
		this->m_iRtspPort = config->RtspPort;
		if (this->m_bEnableRTSP)
		{
			m_editRtspPort.EnableWindow(TRUE);
		}
		else
		{
			m_editRtspPort.EnableWindow(FALSE);
		}
		this->m_bEnableWDM = config->EnableWdm;
		this->m_iWdmPort = config->WdmPort;
		if (this->m_bEnableWDM)
		{
			m_editWdmPort.EnableWindow(TRUE);
		}
		else
		{
			m_editWdmPort.EnableWindow(FALSE);
		}
		this->m_bEnableP2P = config->EnableP2p;
		this->m_iP2pPort = config->P2pPort;
		if (this->m_bEnableP2P)
		{
			m_editP2pPort.EnableWindow(TRUE);
		}
		else
		{
			m_editP2pPort.EnableWindow(FALSE);
		}
		this->m_bEnableMULTICAST = config->EnableMulticast;
		this->m_iMulticastPort = config->MulticastPort;
		this->m_dwMulticastIP = config->MulticastIP;
		if (this->m_bEnableMULTICAST)
		{
			m_editMulticastPort.EnableWindow(TRUE);
			m_editMulticastIP.EnableWindow(TRUE);
		}
		else
		{
			m_editMulticastPort.EnableWindow(FALSE);
			m_editMulticastIP.EnableWindow(FALSE);
		}
		this->UpdateData(FALSE);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}

void CSettingLiveDlg::GetLiveConfig(LiveAttribute *config)
{
	if (config)
	{
		this->UpdateData(TRUE);
		config->EnableRtmp = this->m_bEnableRTMP;
		config->RtmpPort = this->m_iRtmpPort;
		config->EnableRtsp = this->m_bEnableRTSP;
		config->RtspPort = this->m_iRtspPort;
		config->EnableWdm = this->m_bEnableWDM;
		config->WdmPort = this->m_iWdmPort;
		config->EnableP2p = this->m_bEnableP2P;
		config->P2pPort = this->m_iP2pPort;
		config->EnableMulticast = this->m_bEnableMULTICAST;
		config->MulticastPort = this->m_iMulticastPort;
		config->MulticastIP = this->m_dwMulticastIP;
	}
}

void CSettingLiveDlg::OnBnClickedLiveEnableRtmp()
{
	// TODO:  在此添加控件通知处理程序代码
	this->UpdateData(TRUE);
	if (this->m_bEnableRTMP)
	{
		m_editRtmpPort.EnableWindow(TRUE);
	}
	else
	{
		m_editRtmpPort.EnableWindow(FALSE);
	}
}


void CSettingLiveDlg::OnBnClickedLiveEnableRtsp()
{
	// TODO:  在此添加控件通知处理程序代码
	this->UpdateData(TRUE);
	if (this->m_bEnableRTSP)
	{
		m_editRtspPort.EnableWindow(TRUE);
	}
	else
	{
		m_editRtspPort.EnableWindow(FALSE);
	}
}


void CSettingLiveDlg::OnBnClickedLiveEnableWdm()
{
	// TODO:  在此添加控件通知处理程序代码
	this->UpdateData(TRUE);
	if (this->m_bEnableWDM)
	{
		m_editWdmPort.EnableWindow(TRUE);
	}
	else
	{
		m_editWdmPort.EnableWindow(FALSE);
	}
}


void CSettingLiveDlg::OnBnClickedLiveEnableP2p()
{
	// TODO:  在此添加控件通知处理程序代码
	this->UpdateData(TRUE);
	if (this->m_bEnableP2P)
	{
		m_editP2pPort.EnableWindow(TRUE);
	}
	else
	{
		m_editP2pPort.EnableWindow(FALSE);
	}
}


void CSettingLiveDlg::OnBnClickedLiveEnableMulticast()
{
	// TODO:  在此添加控件通知处理程序代码
	this->UpdateData(TRUE);
	if (this->m_bEnableMULTICAST)
	{
		m_editMulticastPort.EnableWindow(TRUE);
		m_editMulticastIP.EnableWindow(TRUE);
	}
	else
	{
		m_editMulticastPort.EnableWindow(FALSE);
		m_editMulticastIP.EnableWindow(FALSE);
	}
}

// SettingRecordDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ScreenVideo.h"
#include "SettingRecordDlg.h"
#include "afxdialogex.h"

#include "Configuration.h"


// CSettingRecordDlg 对话框

IMPLEMENT_DYNAMIC(CSettingRecordDlg, CDialogEx)

CSettingRecordDlg::CSettingRecordDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSettingRecordDlg::IDD, pParent)
	, m_iRecordType(0)
	, m_strRecordPath(_T("D:\\ScreenVideo\\record"))
	, m_strRecordName(_T("record_%year%%month%%day%%hour%%minute%%second%"))
	, m_iAutoSplitTime(60)
{

}

CSettingRecordDlg::~CSettingRecordDlg()
{
}

void CSettingRecordDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_CBIndex(pDX, IDC_RECORD_TYPE, m_iRecordType);
	DDX_Text(pDX, IDC_RECORD_PATH, m_strRecordPath);
	DDX_Text(pDX, IDC_RECORD_NAME, m_strRecordName);
	DDX_Text(pDX, IDC_RECORD_AUTOSPLIT, m_iAutoSplitTime);
}


BEGIN_MESSAGE_MAP(CSettingRecordDlg, CDialogEx)
END_MESSAGE_MAP()


// CSettingRecordDlg 消息处理程序


BOOL CSettingRecordDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	RecordAttribute * attr = Configuration::GetInstance()->GetRecordConfig();
	this->m_iRecordType = attr->fileType;
	this->m_strRecordPath = attr->recordPath.c_str();
	this->m_strRecordName = attr->filenamePattern.c_str();
	//this->m_strRecordPath.Format(_T("%s"), attr->recordPath.c_str());
	//this->m_strRecordName.Format(_T("%s"), attr->filenamePattern.c_str());
	this->m_iAutoSplitTime = attr->m_iAutoSplitTime;
	this->UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}

void CSettingRecordDlg::GetRecordConfig(RecordAttribute *config)
{
	this->UpdateData(TRUE);
	if (config)
	{
		char tmp[1024];
		config->fileType = (MEDIA_FILE_TYPE_E)m_iRecordType;
		wcstombs(tmp, m_strRecordPath.GetBuffer(), 1024);
		config->recordPath = tmp;
		wcstombs(tmp, m_strRecordName.GetBuffer(), 1024);
		config->filenamePattern = tmp;
		config->m_iAutoSplitTime = m_iAutoSplitTime;
	}
}

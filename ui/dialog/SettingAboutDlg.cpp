// SettingAboutDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ScreenVideo.h"
#include "SettingAboutDlg.h"
#include "afxdialogex.h"


// SettingAboutDlg 对话框

IMPLEMENT_DYNAMIC(CSettingAboutDlg, CDialogEx)

CSettingAboutDlg::CSettingAboutDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSettingAboutDlg::IDD, pParent)
{

}

CSettingAboutDlg::~CSettingAboutDlg()
{
}

void CSettingAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSettingAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// SettingAboutDlg 消息处理程序

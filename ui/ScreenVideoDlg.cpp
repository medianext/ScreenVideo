
// ScreenVideoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ScreenVideo.h"
#include "ScreenVideoDlg.h"
#include "afxdialogex.h"

#include "Configuration.h"

#include "pthread.h"
extern "C" {
//#include "libavutil\avutil.h"
#include "libswscale\swscale.h"
#include "libavcodec\avcodec.h"
}

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CScreenVideoDlg 对话框



CScreenVideoDlg::CScreenVideoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CScreenVideoDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

}

void CScreenVideoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CScreenVideoDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_RECORD_START, &CScreenVideoDlg::OnBnClickedRecordStart)
	ON_BN_CLICKED(IDC_RECORD_STOP, &CScreenVideoDlg::OnBnClickedRecordStop)
	ON_BN_CLICKED(IDC_RECORD_SETTING, &CScreenVideoDlg::OnBnClickedRecordSetting)
	ON_MESSAGE(WM_NOTYFICATION_MESSAGE, OnNotifyMsg)
	ON_WM_CLOSE()
	ON_WM_DESTROY()
	ON_WM_NCPAINT()
END_MESSAGE_MAP()


// CScreenVideoDlg 消息处理程序

BOOL CScreenVideoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	m_NotifyIcon.cbSize = sizeof(NOTIFYICONDATA);
	m_NotifyIcon.hWnd = this->m_hWnd;
	m_NotifyIcon.uID = IDR_MAINFRAME;
	m_NotifyIcon.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;
	m_NotifyIcon.uCallbackMessage = WM_NOTYFICATION_MESSAGE;
	m_NotifyIcon.hIcon = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_MAINFRAME));
	lstrcpy(m_NotifyIcon.szTip, TEXT("测试程序"));//图标提示为"测试程序"
	Shell_NotifyIcon(NIM_ADD, &m_NotifyIcon);//向任务栏添加图标

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CScreenVideoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
		CDialogEx::OnSysCommand(nID, lParam);
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CScreenVideoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CScreenVideoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

int getwindowspic(unsigned char ** pdata)
{
	HWND hwnd = ::GetDesktopWindow();
	HDC hDC = ::GetDC(hwnd);//获取屏幕DC  

	RECT rect;
	::GetClientRect(hwnd, &rect);//获取屏幕大小  
	HDC hDCMem = ::CreateCompatibleDC(hDC);//创建兼容DC  

	HBITMAP hBitMap = ::CreateCompatibleBitmap(hDC, rect.right, rect.bottom);//创建兼容位图  
	HBITMAP hOldMap = (HBITMAP)::SelectObject(hDCMem, hBitMap);//将位图选入DC，并保存返回值  

	::BitBlt(hDCMem, 0, 0, rect.right, rect.bottom, hDC, 0, 0, SRCCOPY);//将屏幕DC的图象复制到内存DC中  

	BITMAPINFO * pbitmapInfo = (BITMAPINFO *)malloc(sizeof(BITMAPINFOHEADER) + 32);
	memset(pbitmapInfo, 0, sizeof(BITMAPINFOHEADER) + 32);
	pbitmapInfo->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	GetDIBits(hDCMem, hBitMap, 0, 0, NULL, pbitmapInfo, DIB_RGB_COLORS);  //第一次调用获取BITMAPINFO信息
	pbitmapInfo->bmiHeader.biCompression = BI_RGB;
	if (*pdata==NULL)
	{
		*pdata = (unsigned char *)malloc(pbitmapInfo->bmiHeader.biSizeImage);
	}
	if (*pdata)
	{
		GetDIBits(hDCMem, hBitMap, 0, pbitmapInfo->bmiHeader.biHeight, (*pdata), pbitmapInfo, DIB_RGB_COLORS);
	}
	free(pbitmapInfo);
// 	CImage image;
// 	image.Attach(hBitMap);
// 	image.Save(_T("c://B.jpg"));//如果文件后缀为.bmp，则保存为为bmp格式  
// 	image.Detach();

	::SelectObject(hDCMem, hOldMap);//选入上次的返回值  

	//释放  
	::DeleteObject(hBitMap);
	::DeleteDC(hDCMem);
	::DeleteDC(hDC);
	return 0;
}

int bStart = 0;
int bPause = 0;

void *PTW32_CDECL record_thread(void * arg)
{
// 	while (g_record)
// 	{
// 		OutputDebugString(TEXT("record_thread start...\n"));
// 		Sleep(1000);
// 	}
	int ret;
	FILE * yuvfile = NULL;
	AVFrame * rgb_picture = NULL;
	AVFrame * yuv_picture = NULL;
	AVCodec * codec = NULL;
	AVCodecContext * codec_ctx = NULL;
	SwsContext * sws_ctx = NULL;
	unsigned char * pRGBdata = NULL;
	Sleep(2);
	yuvfile = fopen("screenvideo.yuv", "w+");
	if (yuvfile==NULL)
	{
	}
	avcodec_register_all();

	codec = avcodec_find_encoder(CODEC_ID_H264);
	if (codec==NULL)
	{
		return NULL;
	}

	codec_ctx = avcodec_alloc_context3(codec);

	rgb_picture = av_frame_alloc();

	yuv_picture = av_frame_alloc();

	codec_ctx->width = 1920;
	codec_ctx->height = 1080;
	codec_ctx->bit_rate = 1024 * 4;
	codec_ctx->gop_size = 30;

	int size = codec_ctx->width*codec_ctx->height;

	yuv_picture->data[0] = (uint8_t *)malloc(960*540 * 3 / 2);
	yuv_picture->data[1] = yuv_picture->data[0] + 960 * 540;
	yuv_picture->data[2] = yuv_picture->data[1] + 960 * 540 / 4;
	yuv_picture->linesize[0] = 960;// codec_ctx->width;
	yuv_picture->linesize[1] = 540 / 2;// codec_ctx->width / 2;
	yuv_picture->linesize[2] = 540 / 2;//codec_ctx->width / 2;

	rgb_picture->data[0] = (uint8_t *)malloc(size * 3);
	rgb_picture->data[1] = rgb_picture->data[0] + size;
	rgb_picture->data[2] = rgb_picture->data[1] + size;
	rgb_picture->linesize[0] = codec_ctx->width*3;
	rgb_picture->linesize[1] = codec_ctx->width;
	rgb_picture->linesize[2] = codec_ctx->width;

	sws_ctx = sws_getContext(codec_ctx->width, codec_ctx->height, PIX_FMT_RGB24,960, 540, PIX_FMT_YUV420P, SWS_FAST_BILINEAR, NULL, NULL, NULL);

	int count = 0;
	while (bStart==1)
	{
		if (bPause==0)
		{
			Sleep(10);
			continue;
		}
		getwindowspic(&pRGBdata);
// 		rgb_picture->format = PIX_FMT_RGB24;
// 		ret = avpicture_fill((AVPicture *)rgb_picture, (uint8_t*)pRGBdata, PIX_FMT_RGB32, codec_ctx->width, codec_ctx->height);
		for (int i = 0; i < codec_ctx->height; i++)
		{
			for (int j = 0; j < codec_ctx->width; j++)
			{
 				rgb_picture->data[0][3 * (i*codec_ctx->width + j) + 0] = pRGBdata[4 * ((codec_ctx->height - i - 1)*codec_ctx->width + j) + 0];
 				rgb_picture->data[0][3 * (i*codec_ctx->width + j) + 1] = pRGBdata[4 * ((codec_ctx->height - i - 1)*codec_ctx->width + j) + 1];
 				rgb_picture->data[0][3 * (i*codec_ctx->width + j) + 2] = pRGBdata[4 * ((codec_ctx->height - i - 1)*codec_ctx->width + j) + 2];
// 				if (i<codec_ctx->height/3)
// 				{
// 					rgb_picture->data[0][3 * (i*codec_ctx->width + j) + 0] = 0xff;
// 					rgb_picture->data[0][3 * (i*codec_ctx->width + j) + 1] = 0;
// 					rgb_picture->data[0][3 * (i*codec_ctx->width + j) + 2] = 0;
// 				}
// 				else if (i>codec_ctx->height * 2/ 3)
// 				{
// 					rgb_picture->data[0][3 * (i*codec_ctx->width + j) + 0] = 0;
// 					rgb_picture->data[0][3 * (i*codec_ctx->width + j) + 1] = 0;
// 					rgb_picture->data[0][3 * (i*codec_ctx->width + j) + 2] = 0xff;
// 				}else
// 				{
// 					rgb_picture->data[0][3 * (i*codec_ctx->width + j) + 0] = 0;
// 					rgb_picture->data[0][3 * (i*codec_ctx->width + j) + 1] = 0xff;
// 					rgb_picture->data[0][3 * (i*codec_ctx->width + j) + 2] = 0;
// 				}

			}
		}

		if (pRGBdata)
		{
			ret = sws_scale(sws_ctx, rgb_picture->data, rgb_picture->linesize, 0, codec_ctx->height, yuv_picture->data, yuv_picture->linesize);
			{
				count++;
// 				fwrite(rgb_picture->data[0], size * 3, 1, yuvfile);
// 				fwrite(pRGBdata, size * 4, 1, yuvfile);
				fwrite(yuv_picture->data[0], 960 * 540 * 3 / 2, 1, yuvfile);
// 				fwrite(yuv_picture->data[1], size / 4, 1, yuvfile);
// 				fwrite(yuv_picture->data[2], size / 4, 1, yuvfile);
			}
		}
	}
	fclose(yuvfile);
	if (pRGBdata)
	{
		free(pRGBdata);
		pRGBdata = NULL;
	}
	return NULL;
}

void CScreenVideoDlg::OnBnClickedRecordStart()
{
	// TODO:  在此添加控件通知处理程序代码
	CButton* btn = (CButton *)this->GetDlgItem(IDC_RECORD_START);
	if (bPause == 0)
	{
		btn->SetWindowText(TEXT("Pause"));
		this->ShowWindow(SW_HIDE);
		bPause = 1;
		bStart = 1;
	}
	else{
		btn->SetWindowText(TEXT("Record"));
		bPause = 0;
	}
	pthread_t thread;
	pthread_create(&thread,NULL,record_thread,NULL);
}


void CScreenVideoDlg::OnBnClickedRecordStop()
{
	// TODO:  在此添加控件通知处理程序代码
	bStart = 0;
	if (bPause == 1)
	{
		CButton* btn = (CButton *)this->GetDlgItem(IDC_RECORD_START);
		btn->SetWindowText(TEXT("Record"));
		bPause = 0;
	}
}


void CScreenVideoDlg::OnBnClickedRecordSetting()
{
	// TODO:  在此添加控件通知处理程序代码
	INT_PTR ret = m_MainSettingDlg.DoModal();
	if (ret==IDOK)
	{
		OutputDebugString(TEXT("IDOK\n"));
	}else if (ret == IDCANCEL)
	{
	}
}

LRESULT  CScreenVideoDlg::OnNotifyMsg(WPARAM wparam, LPARAM lparam)
//wParam接收的是图标的ID，而lParam接收的是鼠标的行为     
{
	if (wparam != IDR_MAINFRAME)
		return    1;
	switch (lparam)
	{
	case WM_RBUTTONUP://右键起来时弹出快捷菜单，这里只有一个“关闭”     
	{
		LPPOINT lpoint = new tagPOINT;
		::GetCursorPos(lpoint);//得到鼠标位置     
		CMenu menu;
		menu.CreatePopupMenu();//声明一个弹出式菜单     
		//增加菜单项“关闭”，点击则发送消息WM_DESTROY给主窗口（已     
		//隐藏），将程序结束。     
		menu.AppendMenu(MF_STRING, WM_DESTROY, TEXT("关闭"));
		//确定弹出式菜单的位置
//		menu.LoadMenu(IDR_MENU_NOTIFYICON);
		menu.TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, lpoint->x, lpoint->y, this);
		//资源回收     
		//HMENU    hmenu = menu.Detach();
		//menu.DestroyMenu();
		delete    lpoint;
	}
		break;
	case WM_LBUTTONDBLCLK://双击左键的处理     
	{
		this->ShowWindow(SW_SHOW);//简单的显示主窗口完事儿     
	}
		break;
	}
	return 0;
}


void CScreenVideoDlg::OnClose()
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	this->ShowWindow(SW_HIDE);
	if (Configuration::GetInstance()->IsQuitApp())
	{
		CDialogEx::OnClose();
	}
}


void CScreenVideoDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	Shell_NotifyIcon(NIM_DELETE, &m_NotifyIcon);//向任务栏添加图标
	// TODO:  在此处添加消息处理程序代码
}


void CScreenVideoDlg::OnNcPaint()
{
	// TODO:  在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialogEx::OnNcPaint()
	static int i = 2;
	if (i>0 && Configuration::GetInstance()->IsAutoHideWindow())
	{
		i--;
		this->ShowWindow(SW_HIDE);
	} 
	else
	{
		CDialogEx::OnNcPaint();
	}
}

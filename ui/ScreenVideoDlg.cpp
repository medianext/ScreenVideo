
// ScreenVideoDlg.cpp : ʵ���ļ�
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

// CScreenVideoDlg �Ի���



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


// CScreenVideoDlg ��Ϣ�������

BOOL CScreenVideoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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
	lstrcpy(m_NotifyIcon.szTip, TEXT("���Գ���"));//ͼ����ʾΪ"���Գ���"
	Shell_NotifyIcon(NIM_ADD, &m_NotifyIcon);//�����������ͼ��

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CScreenVideoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
		CDialogEx::OnSysCommand(nID, lParam);
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CScreenVideoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CScreenVideoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

int getwindowspic(unsigned char ** pdata)
{
	HWND hwnd = ::GetDesktopWindow();
	HDC hDC = ::GetDC(hwnd);//��ȡ��ĻDC  

	RECT rect;
	::GetClientRect(hwnd, &rect);//��ȡ��Ļ��С  
	HDC hDCMem = ::CreateCompatibleDC(hDC);//��������DC  

	HBITMAP hBitMap = ::CreateCompatibleBitmap(hDC, rect.right, rect.bottom);//��������λͼ  
	HBITMAP hOldMap = (HBITMAP)::SelectObject(hDCMem, hBitMap);//��λͼѡ��DC�������淵��ֵ  

	::BitBlt(hDCMem, 0, 0, rect.right, rect.bottom, hDC, 0, 0, SRCCOPY);//����ĻDC��ͼ���Ƶ��ڴ�DC��  

	BITMAPINFO * pbitmapInfo = (BITMAPINFO *)malloc(sizeof(BITMAPINFOHEADER) + 32);
	memset(pbitmapInfo, 0, sizeof(BITMAPINFOHEADER) + 32);
	pbitmapInfo->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	GetDIBits(hDCMem, hBitMap, 0, 0, NULL, pbitmapInfo, DIB_RGB_COLORS);  //��һ�ε��û�ȡBITMAPINFO��Ϣ
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
// 	image.Save(_T("c://B.jpg"));//����ļ���׺Ϊ.bmp���򱣴�ΪΪbmp��ʽ  
// 	image.Detach();

	::SelectObject(hDCMem, hOldMap);//ѡ���ϴεķ���ֵ  

	//�ͷ�  
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
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	INT_PTR ret = m_MainSettingDlg.DoModal();
	if (ret==IDOK)
	{
		OutputDebugString(TEXT("IDOK\n"));
	}else if (ret == IDCANCEL)
	{
	}
}

LRESULT  CScreenVideoDlg::OnNotifyMsg(WPARAM wparam, LPARAM lparam)
//wParam���յ���ͼ���ID����lParam���յ���������Ϊ     
{
	if (wparam != IDR_MAINFRAME)
		return    1;
	switch (lparam)
	{
	case WM_RBUTTONUP://�Ҽ�����ʱ������ݲ˵�������ֻ��һ�����رա�     
	{
		LPPOINT lpoint = new tagPOINT;
		::GetCursorPos(lpoint);//�õ����λ��     
		CMenu menu;
		menu.CreatePopupMenu();//����һ������ʽ�˵�     
		//���Ӳ˵���رա������������ϢWM_DESTROY�������ڣ���     
		//���أ��������������     
		menu.AppendMenu(MF_STRING, WM_DESTROY, TEXT("�ر�"));
		//ȷ������ʽ�˵���λ��
//		menu.LoadMenu(IDR_MENU_NOTIFYICON);
		menu.TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, lpoint->x, lpoint->y, this);
		//��Դ����     
		//HMENU    hmenu = menu.Detach();
		//menu.DestroyMenu();
		delete    lpoint;
	}
		break;
	case WM_LBUTTONDBLCLK://˫������Ĵ���     
	{
		this->ShowWindow(SW_SHOW);//�򵥵���ʾ���������¶�     
	}
		break;
	}
	return 0;
}


void CScreenVideoDlg::OnClose()
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	this->ShowWindow(SW_HIDE);
	if (Configuration::GetInstance()->IsQuitApp())
	{
		CDialogEx::OnClose();
	}
}


void CScreenVideoDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	Shell_NotifyIcon(NIM_DELETE, &m_NotifyIcon);//�����������ͼ��
	// TODO:  �ڴ˴������Ϣ����������
}


void CScreenVideoDlg::OnNcPaint()
{
	// TODO:  �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnNcPaint()
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

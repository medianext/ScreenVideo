
// ScreenVideo.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CScreenVideoApp: 
// �йش����ʵ�֣������ ScreenVideo.cpp
//

class CScreenVideoApp : public CWinApp
{
public:
	CScreenVideoApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CScreenVideoApp theApp;
// controlSerialNetPort.h : PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号
#define SAVE_PARATOFILE WM_USER+30	//自行定义之讯息
#define RECOVER_UIPARA  WM_USER+31	//自行定义之讯息
#define LOAD_FILETOPARA  WM_USER+32	//自行定义之讯息

// CcontrolSerialNetPortApp:
// 有关此类的实现，请参阅 controlSerialNetPort.cpp
//



class CcontrolSerialNetPortApp : public CWinApp
{
public:
	CcontrolSerialNetPortApp();

// 重写
	public:
	virtual BOOL InitInstance();

// 实现

	DECLARE_MESSAGE_MAP()
};

extern CcontrolSerialNetPortApp theApp;
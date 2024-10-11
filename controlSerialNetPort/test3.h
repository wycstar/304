
// test3.h : PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

//包含BeckOff软件头文件
#include "TcAdsDef.h"
#include "TcAdsAPI.h"

#include <iostream>
#include "resource.h"		// 主符号
#include <conio.h>
#include "MMSystem.h"
#include "time.h"
#include <Windows.h>
#include <sapi.h>//TTS语音头文件
#pragma comment(lib,"WinMM.Lib") 
#pragma comment(lib,"TcAdsDll.lib") 


// Ctest3App: 
// 有关此类的实现，请参阅 test3.cpp
//

class Ctest3App : public CWinApp
{
public:
	Ctest3App();

// 重写
public:
	virtual BOOL InitInstance();


// 实现

	DECLARE_MESSAGE_MAP()
};

//extern Ctest3App theApp;



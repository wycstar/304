
// test3.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

//����BeckOff���ͷ�ļ�
#include "TcAdsDef.h"
#include "TcAdsAPI.h"

#include <iostream>
#include "resource.h"		// ������
#include <conio.h>
#include "MMSystem.h"
#include "time.h"
#include <Windows.h>
#include <sapi.h>//TTS����ͷ�ļ�
#pragma comment(lib,"WinMM.Lib") 
#pragma comment(lib,"TcAdsDll.lib") 


// Ctest3App: 
// �йش����ʵ�֣������ test3.cpp
//

class Ctest3App : public CWinApp
{
public:
	Ctest3App();

// ��д
public:
	virtual BOOL InitInstance();


// ʵ��

	DECLARE_MESSAGE_MAP()
};

//extern Ctest3App theApp;



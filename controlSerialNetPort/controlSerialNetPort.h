// controlSerialNetPort.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������
#define SAVE_PARATOFILE WM_USER+30	//���ж���֮ѶϢ
#define RECOVER_UIPARA  WM_USER+31	//���ж���֮ѶϢ
#define LOAD_FILETOPARA  WM_USER+32	//���ж���֮ѶϢ

// CcontrolSerialNetPortApp:
// �йش����ʵ�֣������ controlSerialNetPort.cpp
//



class CcontrolSerialNetPortApp : public CWinApp
{
public:
	CcontrolSerialNetPortApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CcontrolSerialNetPortApp theApp;
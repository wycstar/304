// Joivel.cpp : 实现文件
//

#include "stdafx.h"
#include "test3.h"
#include "Joivel.h"
#include "afxdialogex.h"


// CJoivel 对话框

IMPLEMENT_DYNAMIC(CJoivel, CDialogEx)

CJoivel::CJoivel(CWnd* pParent /*=NULL*/)
	: CDialogEx(CJoivel::IDD, pParent)
	, m_Jov_edit1(0)
	, m_Jov_edit2(0)
	, m_Jov_edit3(0)
	, m_Jov_edit4(0)
{

}

CJoivel::~CJoivel()
{
}

void CJoivel::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER1, m_Jov_slider1);
	DDX_Control(pDX, IDC_SLIDER2, m_Jov_slider2);
	DDX_Control(pDX, IDC_SLIDER3, m_Jov_slider3);
	DDX_Control(pDX, IDC_SLIDER4, m_Jov_slider4);
	DDX_Text(pDX, IDC_EDIT1, m_Jov_edit1);
	DDX_Text(pDX, IDC_EDIT2, m_Jov_edit2);
	DDX_Text(pDX, IDC_EDIT3, m_Jov_edit3);
	DDX_Text(pDX, IDC_EDIT4, m_Jov_edit4);
}


BEGIN_MESSAGE_MAP(CJoivel, CDialogEx)
END_MESSAGE_MAP()


// CJoivel 消息处理程序



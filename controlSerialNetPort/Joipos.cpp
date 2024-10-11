// Joipos.cpp : 实现文件
//

#include "stdafx.h"
#include "test3.h"
#include "Joipos.h"
#include "afxdialogex.h"


// CJoipos 对话框

IMPLEMENT_DYNAMIC(CJoipos, CDialogEx)

CJoipos::CJoipos(CWnd* pParent /*=NULL*/)
	: CDialogEx(CJoipos::IDD, pParent)
	, m_Jop_edit1(0)
	, m_Jop_edit2(0)
	, m_Jop_edit3(0)
	, m_Jop_edit4(0)
	
{

}

CJoipos::~CJoipos()
{
}

void CJoipos::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER1, m_Jop_slider1);
	DDX_Control(pDX, IDC_SLIDER2, m_Jop_slider2);
	DDX_Control(pDX, IDC_SLIDER3, m_Jop_slider3);
	DDX_Control(pDX, IDC_SLIDER4, m_Jop_slider4);
	DDX_Text(pDX, IDC_EDIT1, m_Jop_edit1);
	DDX_Text(pDX, IDC_EDIT2, m_Jop_edit2);
	DDX_Text(pDX, IDC_EDIT3, m_Jop_edit3);
	DDX_Text(pDX, IDC_EDIT4, m_Jop_edit4);
}


BEGIN_MESSAGE_MAP(CJoipos, CDialogEx)
END_MESSAGE_MAP()


// CJoipos 消息处理程序



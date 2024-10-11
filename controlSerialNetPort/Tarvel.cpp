// Tarvel.cpp : 实现文件
//

#include "stdafx.h"
#include "test3.h"
#include "Tarvel.h"
#include "afxdialogex.h"


// CTarvel 对话框

IMPLEMENT_DYNAMIC(CTarvel, CDialogEx)

CTarvel::CTarvel(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTarvel::IDD, pParent)
	, m_Tav_edit1(0)
	, m_Tav_edit2(0)
	, m_Tav_edit3(0)
	, m_Tav_edit4(0)
{

}

CTarvel::~CTarvel()
{
}

void CTarvel::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER1, m_Tav_slider1);
	DDX_Control(pDX, IDC_SLIDER2, m_Tav_slider2);
	DDX_Control(pDX, IDC_SLIDER3, m_Tav_slider3);
	DDX_Control(pDX, IDC_SLIDER4, m_Tav_slider4);
	DDX_Text(pDX, IDC_EDIT1, m_Tav_edit1);
	DDX_Text(pDX, IDC_EDIT2, m_Tav_edit2);
	DDX_Text(pDX, IDC_EDIT3, m_Tav_edit3);
	DDX_Text(pDX, IDC_EDIT4, m_Tav_edit4);
}


BEGIN_MESSAGE_MAP(CTarvel, CDialogEx)
END_MESSAGE_MAP()


// CTarvel 消息处理程序


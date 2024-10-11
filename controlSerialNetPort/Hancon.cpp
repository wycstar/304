// Hancon.cpp : 实现文件
//

#include "stdafx.h"
#include "test3.h"
#include "Hancon.h"
#include "afxdialogex.h"


// CHancon 对话框

IMPLEMENT_DYNAMIC(CHancon, CDialogEx)

CHancon::CHancon(CWnd* pParent /*=NULL*/)
	: CDialogEx(CHancon::IDD, pParent)
	, Xpos(0)
	, Ypos(0)
	, Zpos(0)
	, Rpos(0)
{

}

CHancon::~CHancon()
{
}

void CHancon::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Control(pDX, IDC_BUTTON_ADDPOINT, m_Axis1);
	//  DDX_Text(pDX, IDC_EDIT1, m_axis1);
	DDX_Control(pDX, IDC_CHECK_AXIS1, m_check_axis1);
	DDX_Control(pDX, IDC_CHECK_AXIS2, m_check_axis2);
	DDX_Control(pDX, IDC_CHECK_AXIS3, m_check_axis3);
	DDX_Control(pDX, IDC_CHECK_AXIS4, m_check_axis4);
	DDX_Control(pDX, IDC_CHECK_FORWARD, m_check_forward);
	DDX_Control(pDX, IDC_CHECK_LEFT, m_check_left);
	DDX_Control(pDX, IDC_CHECK_RIGHT, m_check_right);
	DDX_Control(pDX, IDC_CHECK_UP, m_check_up);
	DDX_Control(pDX, IDC_CHECK_DOWN, m_check_down);
	DDX_Control(pDX, IDC_CHECK_BACKWARD, m_check_backward);
	DDX_Text(pDX, IDC_EDIT_OUT_wXpos, Xpos);
	DDX_Text(pDX, IDC_EDIT_OUT_wYpos, Ypos);
	DDX_Text(pDX, IDC_EDIT_OUT_wZpos, Zpos);
	DDX_Text(pDX, IDC_EDIT_OUT_wRpos, Rpos);
	//  DDX_Control(pDX, IDC_CHECK_NEGATIVE, m_check_positive);
	DDX_Control(pDX, IDC_CHECK_NEGATIVE, m_check_negative);
	DDX_Control(pDX, IDC_CHECK_POSITIVE, m_check_positive);
}


BEGIN_MESSAGE_MAP(CHancon, CDialogEx)
END_MESSAGE_MAP()


// CHancon 消息处理程序




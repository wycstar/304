// Autcon.cpp : 实现文件
//

#include "stdafx.h"
#include "test3.h"
#include "Autcon.h"
#include "afxdialogex.h"


// CAutcon 对话框

IMPLEMENT_DYNAMIC(CAutcon, CDialogEx)

CAutcon::CAutcon(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAutcon::IDD, pParent)
{

}

CAutcon::~CAutcon()
{
}

void CAutcon::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	/*DDX_Text(pDX, IDC_EDIT1, m_Han_edit1);
	DDX_Text(pDX, IDC_EDIT5, key1);
	DDX_Text(pDX, IDC_EDIT6, key2);
	DDX_Text(pDX, IDC_EDIT7, key3);
	DDX_Text(pDX, IDC_EDIT8, key4);
	DDX_Control(pDX, IDC_CHECK_Axis1, m_Hancon_check1);
	DDX_Control(pDX, IDC_CHECK_Axis2, m_Hancon_check2);
	DDX_Control(pDX, IDC_CHECK_Axis3, m_Hancon_check3);
	DDX_Control(pDX, IDC_CHECK_Axis4, m_Hancon_check4);
	DDX_Control(pDX, IDC_CHECK_Switch1, m_Hancon_switch1);
	DDX_Control(pDX, IDC_CHECK_Switch2, m_Hancon_switch2);
	DDX_Control(pDX, IDC_CHECK_Switch3, m_Hancon_switch3);
	DDX_Control(pDX, IDC_CHECK_Switch4, m_Hancon_switch4);
	DDX_Text(pDX, IDC_EDIT9, switch1);
	DDX_Text(pDX, IDC_EDIT10, switch2);
	DDX_Text(pDX, IDC_EDIT11, switch3);
	DDX_Text(pDX, IDC_EDIT12, switch4);*/
}


BEGIN_MESSAGE_MAP(CAutcon, CDialogEx)
END_MESSAGE_MAP()


// CAutcon 消息处理程序

// DialogEditProcess.cpp : 实现文件
//

#include "stdafx.h"
#include "controlSerialNetPort.h"
#include "DialogEditProcess.h"
#include "afxdialogex.h"
#include "DialogCreatProcess.h"


extern CDialogCreatProcess* pEditProcess;

// CDialogEditProcess 对话框

IMPLEMENT_DYNAMIC(CDialogEditProcess, CDialogEx)

CDialogEditProcess::CDialogEditProcess(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_EditProcess, pParent)
	, m_ProcessName2(_T(""))
{

}

CDialogEditProcess::~CDialogEditProcess()
{
}

void CDialogEditProcess::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_STATIC1, m_ProcessName2);
}


BEGIN_MESSAGE_MAP(CDialogEditProcess, CDialogEx)
END_MESSAGE_MAP()


// CDialogEditProcess 消息处理程序


BOOL CDialogEditProcess::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	GetDlgItem(IDC_STATIC1)->SetWindowText(pEditProcess->m_ProcessName);

	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CDialogEditProcess::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类

	
	DestroyWindow();

}


void CDialogEditProcess::PostNcDestroy()
{
	// TODO: 在此添加专用代码和/或调用基类

	CDialogEx::PostNcDestroy();

	delete this;
}

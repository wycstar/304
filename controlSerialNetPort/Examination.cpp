// Examination.cpp : 实现文件
//

#include "stdafx.h"
#include "controlSerialNetPort.h"
#include "Examination.h"
#include "afxdialogex.h"


// CExamination 对话框
CExamination*pExam;//定义全局变量
IMPLEMENT_DYNAMIC(CExamination, CDialogEx)

CExamination::CExamination(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_Examination, pParent)
{

}

CExamination::~CExamination()
{
}

void CExamination::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_LOG, m_ListResult);
}


BEGIN_MESSAGE_MAP(CExamination, CDialogEx)
END_MESSAGE_MAP()


// CExamination 消息处理程序


BOOL CExamination::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	pExam = this;
	//初始化日志显示
	m_ListResult.InitStorage(200000, 200000 * 1024);//日志列表关联的变量m_boxlog 初始化分配内存
	m_ListResult.SetHorizontalExtent(10000);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

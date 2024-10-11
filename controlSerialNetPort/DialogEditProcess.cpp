// DialogEditProcess.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "controlSerialNetPort.h"
#include "DialogEditProcess.h"
#include "afxdialogex.h"
#include "DialogCreatProcess.h"


extern CDialogCreatProcess* pEditProcess;

// CDialogEditProcess �Ի���

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


// CDialogEditProcess ��Ϣ�������


BOOL CDialogEditProcess::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	GetDlgItem(IDC_STATIC1)->SetWindowText(pEditProcess->m_ProcessName);

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


void CDialogEditProcess::OnCancel()
{
	// TODO: �ڴ����ר�ô����/����û���

	
	DestroyWindow();

}


void CDialogEditProcess::PostNcDestroy()
{
	// TODO: �ڴ����ר�ô����/����û���

	CDialogEx::PostNcDestroy();

	delete this;
}

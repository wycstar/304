// Examination.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "controlSerialNetPort.h"
#include "Examination.h"
#include "afxdialogex.h"


// CExamination �Ի���
CExamination*pExam;//����ȫ�ֱ���
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


// CExamination ��Ϣ�������


BOOL CExamination::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	pExam = this;
	//��ʼ����־��ʾ
	m_ListResult.InitStorage(200000, 200000 * 1024);//��־�б�����ı���m_boxlog ��ʼ�������ڴ�
	m_ListResult.SetHorizontalExtent(10000);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}

// DialogCreatProcess.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "controlSerialNetPort.h"
#include "DialogCreatProcess.h"
#include "afxdialogex.h"


CDialogCreatProcess* pEditProcess;
CDialogCreatProcess* pCreateProcess;
// CDialogCreatProcess �Ի���

IMPLEMENT_DYNAMIC(CDialogCreatProcess, CDialogEx)

CDialogCreatProcess::CDialogCreatProcess(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_CreateProcess, pParent)
	, m_ProcessName(_T(""))
	, m_PersonName(_T(""))
	, m_ProcessRemarks(_T(""))
{
	m_editprocess = NULL;
}

CDialogCreatProcess::~CDialogCreatProcess()
{
	/*if (NULL != m_editprocess)
	{
		delete m_editprocess;
		m_editprocess = NULL;
	}
*/
}

void CDialogCreatProcess::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_ProcessName);
	DDX_Text(pDX, IDC_EDIT2, m_PersonName);
	DDX_Text(pDX, IDC_EDIT3, m_ProcessRemarks);
}


BEGIN_MESSAGE_MAP(CDialogCreatProcess, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDialogCreatProcess::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CDialogCreatProcess::OnBnClickedCancel)
END_MESSAGE_MAP()


// CDialogCreatProcess ��Ϣ�������


void CDialogCreatProcess::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);// �����ؼ��е����ݱ��浽��Ӧ�ı��� 

	CString path;
	GetModuleFileName(NULL, path.GetBufferSetLength(MAX_PATH + 1), MAX_PATH);
	path.ReleaseBuffer();
	int pos = path.ReverseFind('\\');
	path = path.Left(pos);
	path = path + _T("\\");
	

	CStdioFile file;
	CString strValue;
	CFileFind filefind;
	CString filepath, filename;

	filepath = path; //�ļ�λ��
	filename = m_ProcessName+_T(".txt");  //�ļ���
	filepath = filepath + filename;  //�ļ�·��

	

	if (filefind.FindFile(filepath, 0) != 0)
	{
		CString str = filename + _T("�Ѵ��ڣ����������");
		AfxMessageBox(str);    //�����ļ�ʧ�ܱ��沢����
	}
	else//�½��ɹ�
	{
		file.Open(filepath, CFile::modeCreate | CFile::modeNoTruncate);//�����ļ�
		file.Close();  //�ر��ļ�

		//�����༭���̡���ģ̬�Ի���
		if (NULL == m_editprocess)//// ���ָ�����m_pTipDlg��ֵΪNULL����Ի���δ��������Ҫ��̬����   
		{
			m_editprocess = new CDialogEditProcess(); //��̬��������
			m_editprocess->Create(IDD_DIALOG_EditProcess, this);//Ҫ�õ������create������Ϊ�˷�ֹ�����������ڵĽ����������Ի��򣬲���ָ�롣
		}
		m_editprocess->ShowWindow(SW_SHOW); // ��ʾ��ģ̬�Ի���  
		m_editprocess->SetWindowPos(NULL, 800, 250, 0, 0, SWP_NOSIZE);//SWP_NOSIZE���ֵ�ǰ��С��cx��cy�ᱻ���ԣ����÷�ģ̬�Ի���λ��

	}
	
}



BOOL CDialogCreatProcess::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	pCreateProcess = this;
	pEditProcess = this;
	
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


void CDialogCreatProcess::OnCancel()
{
	// TODO: �ڴ����ר�ô����/����û���

	DestroyWindow();
}



void CDialogCreatProcess::PostNcDestroy()
{
	// TODO: �ڴ����ר�ô����/����û���

	CDialogEx::PostNcDestroy();
	delete this;
}


void CDialogCreatProcess::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogCreatProcess::OnCancel();
}


void CDialogCreatProcess::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���

	DestroyWindow();
}

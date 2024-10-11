// DialogCreatProcess.cpp : 实现文件
//

#include "stdafx.h"
#include "controlSerialNetPort.h"
#include "DialogCreatProcess.h"
#include "afxdialogex.h"


CDialogCreatProcess* pEditProcess;
CDialogCreatProcess* pCreateProcess;
// CDialogCreatProcess 对话框

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


// CDialogCreatProcess 消息处理程序


void CDialogCreatProcess::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);// 将各控件中的数据保存到相应的变量 

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

	filepath = path; //文件位置
	filename = m_ProcessName+_T(".txt");  //文件名
	filepath = filepath + filename;  //文件路径

	

	if (filefind.FindFile(filepath, 0) != 0)
	{
		CString str = filename + _T("已存在，请更换名称");
		AfxMessageBox(str);    //创建文件失败报告并返回
	}
	else//新建成功
	{
		file.Open(filepath, CFile::modeCreate | CFile::modeNoTruncate);//建立文件
		file.Close();  //关闭文件

		//创建编辑流程、非模态对话框
		if (NULL == m_editprocess)//// 如果指针变量m_pTipDlg的值为NULL，则对话框还未创建，需要动态创建   
		{
			m_editprocess = new CDialogEditProcess(); //动态创建对象
			m_editprocess->Create(IDD_DIALOG_EditProcess, this);//要用到基类的create函数，为了防止对象生命周期的结束而结束对话框，采用指针。
		}
		m_editprocess->ShowWindow(SW_SHOW); // 显示非模态对话框  
		m_editprocess->SetWindowPos(NULL, 800, 250, 0, 0, SWP_NOSIZE);//SWP_NOSIZE保持当前大小（cx和cy会被忽略）设置非模态对话框位置

	}
	
}



BOOL CDialogCreatProcess::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	pCreateProcess = this;
	pEditProcess = this;
	
	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CDialogCreatProcess::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类

	DestroyWindow();
}



void CDialogCreatProcess::PostNcDestroy()
{
	// TODO: 在此添加专用代码和/或调用基类

	CDialogEx::PostNcDestroy();
	delete this;
}


void CDialogCreatProcess::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogCreatProcess::OnCancel();
}


void CDialogCreatProcess::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	DestroyWindow();
}

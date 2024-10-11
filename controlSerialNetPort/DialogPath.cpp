// DialogPath.cpp : 实现文件
//

#include "stdafx.h"
#include "controlSerialNetPort.h"
#include "DialogPath.h"
#include "afxdialogex.h"
#include "DiailogEditor.h"


CDialogPath* pEdit;//声明一个全局变量
// CDialogPath 对话框

IMPLEMENT_DYNAMIC(CDialogPath, CDialogEx)

CDialogPath::CDialogPath(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_Path, pParent)
{
}

CDialogPath::~CDialogPath()
{
}

void CDialogPath::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Text(pDX, IDC_EDIT1, m_editpath);
	//  DDX_Control(pDX, IDC_EDIT1, m_editpath);
	//  DDX_Text(pDX, IDC_EDIT1, m_editpath);
	DDX_Control(pDX, IDC_EDIT1, m_editpath);
}


BEGIN_MESSAGE_MAP(CDialogPath, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CDialogPath::OnBnClickedButton1)
	ON_BN_CLICKED(IDOK, &CDialogPath::OnBnClickedOk)
	

	ON_EN_CHANGE(IDC_EDIT1, &CDialogPath::OnEnChangeEdit1)
END_MESSAGE_MAP()


// CDialogPath 消息处理程序


void CDialogPath::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	if (folderSelect)
	{
		CFolderPickerDialog dlg(NULL, OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST, this);
		if (dlg.DoModal() != IDOK) {
			return;
		}
		resultFileName = dlg.GetPathName();
	}
	else {
		CFileDialog dlg(TRUE, _T("DXF Files"), _T("*.dxf"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
			_T("DXF Files(*.dxf)|All Files(*.*)|*.*||"));
		if (dlg.DoModal() != IDOK)
		{
			return;
		}
		resultFileName = dlg.GetPathName();
	}
	resultFileName = _T("Path=") + resultFileName;
	m_editpath.SetWindowText(resultFileName);	//显示文件完整路径

	UpdateData(FALSE);
}


void CDialogPath::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
	UpdateData(true);
	//CDiailogEditor *p = (CDiailogEditor*)GetParent();

	m_editpath.GetWindowTextW(resultFileName);//将变量的值m_editpath 传到editor当前编辑的单元格里面
	//p->m_edit.SetWindowText(resultFileName);
	WPARAM a = 0;
	LPARAM b = 0;

	//HWND hwnd = ::GetParent(m_hWnd);
//	::SendMessage(hwnd,WM_MyMessage,a, b);
	GetParent()->SendMessage(WM_MyMessage, a, b);
}


void CDialogPath::SetAsFolderSelector()
{
	folderSelect = 1;
}


BOOL CDialogPath::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	pEdit = this;

	// TODO:  在此添加额外的初始化
	m_editpath.SetWindowTextW(resultFileName);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CDialogPath::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}

// DialogPath.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "controlSerialNetPort.h"
#include "DialogPath.h"
#include "afxdialogex.h"
#include "DiailogEditor.h"


CDialogPath* pEdit;//����һ��ȫ�ֱ���
// CDialogPath �Ի���

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


// CDialogPath ��Ϣ�������


void CDialogPath::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	m_editpath.SetWindowText(resultFileName);	//��ʾ�ļ�����·��

	UpdateData(FALSE);
}


void CDialogPath::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnOK();
	UpdateData(true);
	//CDiailogEditor *p = (CDiailogEditor*)GetParent();

	m_editpath.GetWindowTextW(resultFileName);//��������ֵm_editpath ����editor��ǰ�༭�ĵ�Ԫ������
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

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	pEdit = this;

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_editpath.SetWindowTextW(resultFileName);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


void CDialogPath::OnEnChangeEdit1()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}

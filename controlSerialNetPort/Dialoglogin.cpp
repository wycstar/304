// Dialoglogin.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "controlSerialNetPort.h"
#include "Dialoglogin.h"
#include "afxdialogex.h"

CDialoglogin* pDlg;


IMPLEMENT_DYNAMIC(CDialoglogin, CDialog)

CDialoglogin::CDialoglogin(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_DIALOG_Login, pParent)
	, m_name(_T(""))
	, m_password(_T(""))
{
	
}

CDialoglogin::~CDialoglogin()
{
}

void CDialoglogin::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_name);
	DDX_Text(pDX, IDC_EDIT2, m_password);
	//  DDX_Control(pDX, IDC_BUTTON1, m_bbtn);
	//  DDX_Control(pDX, IDC_BUTTON1, m_bbtn);
	DDX_Control(pDX, IDC_BUTTON1, m_bbtn);
}


BEGIN_MESSAGE_MAP(CDialoglogin, CDialog)
	ON_EN_CHANGE(IDC_EDIT1, &CDialoglogin::OnEnChangeEdit1)
	ON_BN_CLICKED(IDC_BUTTON1, &CDialoglogin::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_CHECK1, &CDialoglogin::OnBnClickedCheck1)
	ON_EN_CHANGE(IDC_TIME, &CDialoglogin::OnEnChangeTime)
	ON_WM_TIMER()
	ON_WM_SETCURSOR()
	ON_WM_CTLCOLOR()
	ON_STN_CLICKED(IDC_STATIC3, &CDialoglogin::OnStnClickedStatic3)
	ON_STN_CLICKED(IDC_STATIC4, &CDialoglogin::OnStnClickedStatic4)
	ON_STN_CLICKED(IDC_STATIC6, &CDialoglogin::OnStnClickedStatic6)
END_MESSAGE_MAP()


// CDialoglogin ��Ϣ�������

void CDialoglogin::OnEnChangeEdit1()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CDialoglogin::OnBnClickedButton1()
{

	this->UpdateData(true);
	if (this->m_name.IsEmpty() || this->m_password.IsEmpty())
	{
		MessageBox(_T("�û��������벻��Ϊ�գ����������룡"), _T("��ܰ��ʾ"), MB_ICONINFORMATION);
		return;
	}
	else if (this->m_name == "MMT" && this->m_password == "123")
	{
		MessageBox(_T("��¼�ɹ�!"),_T("��ܰ��ʾ:"));
		CDialog::OnOK();
	}
	else
	{
		MessageBox(_T("�û��������벻��ȷ�����������룡"), _T("��¼ʧ��"), MB_ICONERROR);
		return;
	}
	this->UpdateData(false);
}



void CDialoglogin::OnBnClickedCheck1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


BOOL CDialoglogin::OnInitDialog()
{
	CDialog::OnInitDialog();
	pDlg = this;

	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	
	SetTimer(1, 1000, NULL);         //������ʱ��

	m_bbtn.AutoLoad(IDC_BUTTON1, this);//���ذ�ťͼƬ

	//m_bbtn.SubclassDlgItem(IDC_BUTTON1, this);//��������Ҫ�İ�ť��
	//m_bbtn.LoadBitmaps(IDB_BITMAP2, IDB_BITMAP3, NULL, NULL);
	m_bbtn.SizeToContent();//����ʹ��ť�ʺ�ͼƬ��С��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}





void CDialoglogin::OnEnChangeTime()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CDialoglogin::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CString strTime;
	CTime tm;
	tm = CTime::GetCurrentTime();
	strTime = tm.Format("%Y-%m-%d %H:%M:%S");
	SetDlgItemText(IDC_TIME, strTime);        //��ʾϵͳʱ��
	CDialog::OnTimer(nIDEvent);
}


BOOL CDialoglogin::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)//�������״̬���ƶ����ؼ��ϱ���ʾС��ͼ��
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//����͸������
	if (pWnd == GetDlgItem(IDC_BUTTON1) || pWnd == GetDlgItem(IDC_STATIC6)||pWnd == GetDlgItem(IDC_CHECK2)||pWnd == GetDlgItem(IDC_CHECK1))
	{
		SetCursor(LoadCursor(NULL, IDC_HAND));
		return TRUE;
	}

	return CDialog::OnSetCursor(pWnd, nHitTest, message);
}


HBRUSH CDialoglogin::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)//OnCtlColor�����������Ǹı䣨����Ӧ���ؼ�����ɫ~~
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����
	if ((pWnd->GetDlgCtrlID() == IDC_STATIC6))//GetDlgCtrlID()�����ǻ�ȡָ���ؼ���ID��
	{
		pDC->SetTextColor(RGB(255, 0, 0));//���þ�̬�ı���������ɫ
		pDC->SetBkMode(TRANSPARENT);//����Ϊ͸��
		return HBRUSH(GetStockObject(HOLLOW_BRUSH));//����͸����仰���ܵ�
	}
	if ((pWnd->GetDlgCtrlID() == IDC_STATIC3))
	{
		pDC->SetTextColor(RGB(20, 20, 20));//���þ�̬�ı���������ɫ
		pDC->SetBkMode(TRANSPARENT);//����Ϊ͸��
		return HBRUSH(GetStockObject(HOLLOW_BRUSH));//����͸����仰���ܵ�
	}
	if ((pWnd->GetDlgCtrlID() == IDC_STATIC4))
	{
		pDC->SetTextColor(RGB(50, 50, 50));//���þ�̬�ı�������ɫ
		pDC->SetBkMode(TRANSPARENT);//�����ı�����Ϊ͸��   ��һ��ģʽOPAQUE
									//pDC->SetBkColor(RGB(0, 0, 255));//�����ı�����Ϊ��ɫ
									//hbr = CreateSolidBrush(RGB(0, 255, 0));//�����ؼ��ı���ɫΪ��ɫ
		return HBRUSH(GetStockObject(HOLLOW_BRUSH));//����͸����仰���ܵ�
	}
	if (pWnd->GetDlgCtrlID() == IDC_CHECK1 || pWnd->GetDlgCtrlID() == IDC_CHECK2)//�Ի水ť������ѡ��ؼ�͸������
	{
		CRect rc;
		pWnd->GetWindowRect(&rc);//��ȡ��������ĻΪ�����ᣬ��ť����Ļ�ϵ�λ�á�
		ScreenToClient(&rc);//Screen(��Ļ����) �� Client(�ͻ�������)��ת����
		CDC* dc = GetDC();//DC�ĳ�����Ϊ�豸������,GetDC()����ȡ�����Ļ������
		pDC->BitBlt(0, 0, rc.Width(), rc.Height(), dc, rc.left, rc.top, SRCCOPY);  //�豸�����Ļ�ͼ�����ǽ�һ��λͼ��һ���豸�������Ƶ���һ����

		ReleaseDC(dc);

		hbr = (HBRUSH) ::GetStockObject(NULL_BRUSH); //���ڻ�ȡ��ˢ��������壬��ɫ��ľ��
	}

	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}


void CDialoglogin::OnStnClickedStatic3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CDialoglogin::OnStnClickedStatic4()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CDialoglogin::OnStnClickedStatic6()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


// Dialoglogin.cpp : 实现文件
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


// CDialoglogin 消息处理程序

void CDialoglogin::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CDialoglogin::OnBnClickedButton1()
{

	this->UpdateData(true);
	if (this->m_name.IsEmpty() || this->m_password.IsEmpty())
	{
		MessageBox(_T("用户名或密码不能为空，请重新输入！"), _T("温馨提示"), MB_ICONINFORMATION);
		return;
	}
	else if (this->m_name == "MMT" && this->m_password == "123")
	{
		MessageBox(_T("登录成功!"),_T("温馨提示:"));
		CDialog::OnOK();
	}
	else
	{
		MessageBox(_T("用户名或密码不正确，请重新输入！"), _T("登录失败"), MB_ICONERROR);
		return;
	}
	this->UpdateData(false);
}



void CDialoglogin::OnBnClickedCheck1()
{
	// TODO: 在此添加控件通知处理程序代码
}


BOOL CDialoglogin::OnInitDialog()
{
	CDialog::OnInitDialog();
	pDlg = this;

	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	
	SetTimer(1, 1000, NULL);         //启动定时器

	m_bbtn.AutoLoad(IDC_BUTTON1, this);//加载按钮图片

	//m_bbtn.SubclassDlgItem(IDC_BUTTON1, this);//关联到想要的按钮，
	//m_bbtn.LoadBitmaps(IDB_BITMAP2, IDB_BITMAP3, NULL, NULL);
	m_bbtn.SizeToContent();//函数使按钮适合图片大小。

	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}





void CDialoglogin::OnEnChangeTime()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CDialoglogin::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CString strTime;
	CTime tm;
	tm = CTime::GetCurrentTime();
	strTime = tm.Format("%Y-%m-%d %H:%M:%S");
	SetDlgItemText(IDC_TIME, strTime);        //显示系统时间
	CDialog::OnTimer(nIDEvent);
}


BOOL CDialoglogin::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)//设置鼠标状态，移动到控件上便显示小手图标
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//设置透明背景
	if (pWnd == GetDlgItem(IDC_BUTTON1) || pWnd == GetDlgItem(IDC_STATIC6)||pWnd == GetDlgItem(IDC_CHECK2)||pWnd == GetDlgItem(IDC_CHECK1))
	{
		SetCursor(LoadCursor(NULL, IDC_HAND));
		return TRUE;
	}

	return CDialog::OnSetCursor(pWnd, nHitTest, message);
}


HBRUSH CDialoglogin::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)//OnCtlColor函数的作用是改变（或响应）控件的颜色~~
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	if ((pWnd->GetDlgCtrlID() == IDC_STATIC6))//GetDlgCtrlID()功能是获取指定控件的ID号
	{
		pDC->SetTextColor(RGB(255, 0, 0));//设置静态文本框字体颜色
		pDC->SetBkMode(TRANSPARENT);//设置为透明
		return HBRUSH(GetStockObject(HOLLOW_BRUSH));//设置透明这句话不能掉
	}
	if ((pWnd->GetDlgCtrlID() == IDC_STATIC3))
	{
		pDC->SetTextColor(RGB(20, 20, 20));//设置静态文本框字体颜色
		pDC->SetBkMode(TRANSPARENT);//设置为透明
		return HBRUSH(GetStockObject(HOLLOW_BRUSH));//设置透明这句话不能掉
	}
	if ((pWnd->GetDlgCtrlID() == IDC_STATIC4))
	{
		pDC->SetTextColor(RGB(50, 50, 50));//设置静态文本字体颜色
		pDC->SetBkMode(TRANSPARENT);//设置文本背景为透明   另一种模式OPAQUE
									//pDC->SetBkColor(RGB(0, 0, 255));//设置文本背景为蓝色
									//hbr = CreateSolidBrush(RGB(0, 255, 0));//整个控件的背景色为绿色
		return HBRUSH(GetStockObject(HOLLOW_BRUSH));//设置透明这句话不能掉
	}
	if (pWnd->GetDlgCtrlID() == IDC_CHECK1 || pWnd->GetDlgCtrlID() == IDC_CHECK2)//自绘按钮，设置选择控件透明背景
	{
		CRect rc;
		pWnd->GetWindowRect(&rc);//获取的是以屏幕为坐标轴，按钮在屏幕上的位置。
		ScreenToClient(&rc);//Screen(屏幕坐标) 到 Client(客户区坐标)的转换。
		CDC* dc = GetDC();//DC的常被称为设备上下文,GetDC()即获取上下文环境句柄
		pDC->BitBlt(0, 0, rc.Width(), rc.Height(), dc, rc.left, rc.top, SRCCOPY);  //设备上下文绘图，它是将一幅位图从一个设备场景复制到另一个。

		ReleaseDC(dc);

		hbr = (HBRUSH) ::GetStockObject(NULL_BRUSH); //用于获取画刷句柄，字体，调色板的句柄
	}

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}


void CDialoglogin::OnStnClickedStatic3()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CDialoglogin::OnStnClickedStatic4()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CDialoglogin::OnStnClickedStatic6()
{
	// TODO: 在此添加控件通知处理程序代码
}


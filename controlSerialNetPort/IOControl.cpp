// IOControl.cpp : 实现文件
//

#include "stdafx.h"
#include "controlSerialNetPort.h"
#include "IOControl.h"
#include "afxdialogex.h"
#include "controlSerialNetPortDlg.h"

extern CcontrolSerialNetPortDlg* mainDlg;
// CIOControl 对话框

IMPLEMENT_DYNAMIC(CIOControl, CDialogEx)

CIOControl::CIOControl(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_IOControl, pParent)
{
	//CString IPaddr;//连接时，是本地IP？
	//CString Port;
	//m_IOIP.GetWindowText(IPaddr);
	//m_localIPio.GetWindowText(IPaddr);
	CString IPaddr = _T("192.168.0.131");//连接时，是本地IP？
	CString Port;
	//m_IOIP.GetWindowText(IPaddr);



	io_d = new CIO();//？//实例化类

	io_d->isConnect = m_IOConnectc;



	if (!io_d->openPort(IPaddr, m_IOPortc))          //连接成功返回1,否则返回0
	{
		AfxMessageBox(_T("打开IO网口失败！"));
		return;
	}

	//AddString(_T("IO网口已成功连接！"));
	m_IOConnectc = true;
	io_d->isConnect = m_IOConnectc;

	//CEdit* m_IOvalue_up = (CEdit*)GetDlgItem(IDC_EDIT13);
	//CEdit* m_IOvalue_down = (CEdit*)GetDlgItem(IDC_EDIT14);

	

	return;
}

CIOControl::~CIOControl()
{
	if (m_IOConnectc != false)
	{
		io_d->closePort();
	}
	delete io_d;
}

void CIOControl::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT8, m_OUPval);
	DDX_Control(pDX, IDC_IPADDRESS1, m_IOControlIP);
	DDX_Control(pDX, IDC_IPADDRESS2, m_AxisControlIP);
	DDX_Control(pDX, IDC_EDIT10, m_axisnum);
	DDX_Control(pDX, IDC_EDIT13, m_axisvalu);
	DDX_Control(pDX, IDC_COMBO1, m_AxisNumCombo);
	DDX_Control(pDX, IDC_IPADDRESS3, m_inquiryIP);
	DDX_Control(pDX, IDC_EDIT9, m_inquiryvalu);
	DDX_Control(pDX, IDC_COMBO2, m_inquirycommand);
	DDX_Control(pDX, IDC_EDIT11, m_inquiryresultvalu);
	DDX_Control(pDX, IDC_EDIT7, m_Y);
	DDX_Control(pDX, IDC_EDIT16, m_Z);
	DDX_Control(pDX, IDC_EDIT12, m_A);
	DDX_Control(pDX, IDC_EDIT14, m_B);
	DDX_Control(pDX, IDC_EDIT15, m_C);
	DDX_Control(pDX, IDC_IPADDRESS4, m_localIPio);
}



BEGIN_MESSAGE_MAP(CIOControl, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CIOControl::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CIOControl::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CIOControl::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CIOControl::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CIOControl::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CIOControl::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &CIOControl::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &CIOControl::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON9, &CIOControl::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON10, &CIOControl::OnBnClickedButton10)
	ON_BN_CLICKED(IDC_BUTTON11, &CIOControl::OnBnClickedButton11)
	ON_BN_CLICKED(IDC_BUTTON12, &CIOControl::OnBnClickedButton12)
	ON_BN_CLICKED(IDC_BUTTON13, &CIOControl::OnBnClickedButton13)
	ON_BN_CLICKED(IDC_BUTTON14, &CIOControl::OnBnClickedButton14)
	ON_BN_CLICKED(IDC_BUTTON15, &CIOControl::OnBnClickedButton15)
	ON_BN_CLICKED(IDC_BUTTON16, &CIOControl::OnBnClickedButton16)
	ON_BN_CLICKED(IDC_BUTTON17, &CIOControl::OnBnClickedButton17)
	ON_BN_CLICKED(IDC_BUTTON18, &CIOControl::OnBnClickedButton18)
	ON_BN_CLICKED(IDC_BUTTON19, &CIOControl::OnBnClickedButton19)
	ON_BN_CLICKED(IDC_BUTTON20, &CIOControl::OnBnClickedButton20)
	ON_BN_CLICKED(IDC_BUTTON21, &CIOControl::OnBnClickedButton21)
	ON_BN_CLICKED(IDC_BUTTON22, &CIOControl::OnBnClickedButton22)
	ON_BN_CLICKED(IDC_BUTTON23, &CIOControl::OnBnClickedButton23)
	ON_BN_CLICKED(IDC_BUTTON24, &CIOControl::OnBnClickedButton24)
	ON_BN_CLICKED(IDC_BUTTON25, &CIOControl::OnBnClickedButton25)
	ON_BN_CLICKED(IDC_BUTTON26, &CIOControl::OnBnClickedButton26)
	ON_BN_CLICKED(IDC_BUTTON27, &CIOControl::OnBnClickedButton27)
	ON_BN_CLICKED(IDC_BUTTON28, &CIOControl::OnBnClickedButton28)
	ON_BN_CLICKED(IDC_BUTTON29, &CIOControl::OnBnClickedButton29)
	ON_BN_CLICKED(IDC_BUTTON30, &CIOControl::OnBnClickedButton30)
	ON_BN_CLICKED(IDC_BUTTON31, &CIOControl::OnBnClickedButton31)
	ON_BN_CLICKED(IDC_BUTTON32, &CIOControl::OnBnClickedButton32)
	ON_BN_CLICKED(IDC_BUTTON33, &CIOControl::OnBnClickedButton33)
	ON_BN_CLICKED(IDC_BUTTON34, &CIOControl::OnBnClickedButton34)
	ON_BN_CLICKED(IDC_BUTTON35, &CIOControl::OnBnClickedButton35)
	ON_BN_CLICKED(IDC_BUTTON36, &CIOControl::OnBnClickedButton36)
	ON_BN_CLICKED(IDC_BUTTON37, &CIOControl::OnBnClickedButton37)
	ON_EN_CHANGE(IDC_EDIT14, &CIOControl::OnEnChangeEdit14)
END_MESSAGE_MAP()

BOOL CIOControl::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_AxisControlIP.SetWindowText(_T("192.168.0.2"));//初始化ip
	m_IOControlIP.SetWindowText(_T("192.168.0.8"));//初始化ip
	m_inquiryIP.SetWindowText(_T("192.168.0.2"));
	m_localIPio.SetWindowText(_T("192.168.0.131"));//初始化ip

	m_AxisNumCombo.AddString(_T("X"));
	m_AxisNumCombo.AddString(_T("Y"));
	m_AxisNumCombo.AddString(_T("Z"));
	m_AxisNumCombo.AddString(_T("A"));
	m_AxisNumCombo.AddString(_T("B"));
	m_AxisNumCombo.AddString(_T("C"));
	m_AxisNumCombo.SetCurSel(0); // 设置初始选择项

	m_inquirycommand.AddString(_T("IN?"));
	m_inquirycommand.AddString(_T("OP?"));
	m_inquirycommand.AddString(_T("TR?"));
	m_inquirycommand.AddString(_T("GS?"));
	m_inquirycommand.SetCurSel(0); // 设置初始选择项

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}


// CIOControl 消息处理程序


void CIOControl::OnBnClickedButton1()
{
	mainDlg->sendComm(_T("4->SOUP 2 1"), 0);
}


void CIOControl::OnBnClickedButton2()
{
	mainDlg->sendComm(_T("4->SOUP 2 2"), 0);
}


void CIOControl::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	mainDlg->sendComm(_T("4->SOUP 1 16"), 0);
}


void CIOControl::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	mainDlg->sendComm(_T("3->SOUP 2 2"), 0);
}

void CIOControl::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	mainDlg->sendComm(_T("4->SOUP 2 4"), 0);
}


void CIOControl::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码
	mainDlg->sendComm(_T("4->SOUP 2 8"), 0);
}


void CIOControl::OnBnClickedButton7()
{
	// TODO: 在此添加控件通知处理程序代码
	mainDlg->sendComm(_T("4->SOUP 2 16"), 0);
}


void CIOControl::OnBnClickedButton8()
{
	// TODO: 在此添加控件通知处理程序代码
	mainDlg->sendComm(_T("3->SOUP 2 1"), 0);
}


void CIOControl::OnBnClickedButton9()
{
	mainDlg->sendComm(_T("4->SOUP 1 17"), 0);
}


void CIOControl::OnBnClickedButton10()
{
	mainDlg->sendComm(_T("4->SOUP 1 18"), 0);
}


void CIOControl::OnBnClickedButton11()
{
	mainDlg->sendComm(_T("6->SOUP 1 1"), 1);
}


void CIOControl::OnBnClickedButton12()
{
	mainDlg->sendComm(_T("6->SOUP 1 2"), 1);
}


void CIOControl::OnBnClickedButton13()
{
	mainDlg->sendComm(_T("6->SOUP 1 4"), 1);
}


void CIOControl::OnBnClickedButton14()
{
	mainDlg->sendComm(_T("6->SOUP 1 8"), 1);
}


void CIOControl::OnBnClickedButton15()
{
	mainDlg->sendComm(_T("6->SOUP 2 4"), 1);
}


void CIOControl::OnBnClickedButton16()
{
	mainDlg->sendComm(_T("6->SOUP 2 8"), 1);
}


void CIOControl::OnBnClickedButton17()
{
	mainDlg->sendComm(_T("6->SOUP 2 16"), 1);
}


void CIOControl::OnBnClickedButton18()
{
	mainDlg->sendComm(_T("5->SOUP 2 4"), 1);
}


void CIOControl::OnBnClickedButton19()
{
	mainDlg->sendComm(_T("5->SOUP 2 2"), 1);
}


void CIOControl::OnBnClickedButton20()
{
	mainDlg->sendComm(_T("5->SOUP 1 0"), 1);
	Sleep(100);
	mainDlg->sendComm(_T("6->SOUP 2 0"), 1);
}


void CIOControl::OnBnClickedButton21()
{
	mainDlg->sendComm(_T("4->SOUP 2 1"), 0);
	Sleep(100);
	mainDlg->sendComm(_T("4->SOUP 1 4"), 0);
}


void CIOControl::OnBnClickedButton22()
{
	mainDlg->sendComm(_T("4->SOUP 1 24"), 0);
}


void CIOControl::OnBnClickedButton23()
{
	mainDlg->sendComm(_T("6->SOUP 1 0"), 1);
}


void CIOControl::OnBnClickedButton24()
{
	mainDlg->sendComm(_T("5->SOUP 2 0"), 1);
}


void CIOControl::OnBnClickedButton25()
{
	mainDlg->sendComm(_T("3->SOUP 1 1"), 0);
}


void CIOControl::OnBnClickedButton26()
{
	mainDlg->sendComm(_T("3->SOUP 1 2"), 0);
}


void CIOControl::OnBnClickedButton27()
{
	mainDlg->sendComm(_T("3->SOUP 1 5"), 0);
}


void CIOControl::OnBnClickedButton28()
{
	mainDlg->sendComm(_T("3->SOUP 1 8"), 0);
}


void CIOControl::OnBnClickedButton29()
{
	mainDlg->sendComm(_T("3->SOUP 1 16"), 0);
}


void CIOControl::OnBnClickedButton30()
{
	mainDlg->sendComm(_T("3->SOUP 2 16"), 0);
}


void CIOControl::OnBnClickedButton31()
{
	mainDlg->sendComm(_T("4->SOUP 2 0"), 0);
	
}


void CIOControl::OnBnClickedButton32()
{
	mainDlg->sendComm(_T("4->SOUP 1 0"), 0);
}


void CIOControl::OnBnClickedButton33()
{
	mainDlg->sendComm(_T("3->SOUP 2 0"), 0);
}


void CIOControl::OnBnClickedButton34()
{
	mainDlg->sendComm(_T("3->SOUP 1 0"), 0);
}


void CIOControl::OnBnClickedButton35()
{
	// TODO: 在此添加控件通知处理程序代码
	CString IPaddr;//连接时，是本地IP？
	//CString Port;
	//m_IOIP.GetWindowText(IPaddr);
	m_IOControlIP.GetWindowText(IPaddr);
	CString abb;
	m_OUPval.GetWindowTextW(abb);
	CString Command = _T("OUP X") + abb;
	io_d->sendComm(IPaddr, Command);
}


int CIOControl::boolArrayToInt(bool boolArray[], int arraySize) {
	int result = 0;

	for (int i = 0; i < arraySize; i++) {
		result |= (boolArray[i] ? 1 : 0) << i;
	}
	return result;
}
int CIOControl::sal() {
	bool val[16] = { true, false, true, false, true, false, true, false,
					true, false, true, false, true, false, true, false };
	int intVal = boolArrayToInt(val, 16);
	std::cout << "Boolean Array: ";
	for (bool b : val) {
		std::cout << b << " ";
	}
	std::cout << "Converted Integer : " << intVal << std::endl;
	return 0;
}

void CIOControl::OnBnClickedButton36()
{
	// TODO: 在此添加控件通知处理程序代码
	// TODO: 在此添加控件通知处理程序代码
	CString IPaddr;//连接时，是本地IP？
	//CString Port;
	//m_IOIP.GetWindowText(IPaddr);
	m_AxisControlIP.GetWindowText(IPaddr);
	CString abb;
	m_axisvalu.GetWindowTextW(abb);
	
	int selectedIndex = m_AxisNumCombo.GetCurSel();
	CString selectedText;
	if (selectedIndex != CB_ERR) {
		
		m_AxisNumCombo.GetLBText(selectedIndex, selectedText);
		//AfxMessageBox(selectedText); // 显示所选的文本
	}
	/*CString strValue;
	strValue.Format(_T("%d"), selectedText);*/
	CString Command = _T("MOV ")+ selectedText + abb;
	io_d->sendComm(IPaddr, Command);
}


void CIOControl::OnBnClickedButton37()
{
	// TODO: 在此添加控件通知处理程序代码
	CString IPaddr;//连接时，是本地IP？
	//CString Port;
	//m_IOIP.GetWindowText(IPaddr);
	m_inquiryIP.GetWindowText(IPaddr);
	CString abb;
	m_inquiryvalu.GetWindowTextW(abb);

	int selectedIndex = m_inquirycommand.GetCurSel();
	CString selectedText;
	if (selectedIndex != CB_ERR) {

		m_inquirycommand.GetLBText(selectedIndex, selectedText);
		//AfxMessageBox(selectedText); // 显示所选的文本
	}
	/*CString strValue;
	strValue.Format(_T("%d"), selectedText);*/
	CString Command = selectedText + abb;
	io_d->sendComm(IPaddr, Command);
	int AxisBitValues[6] = {};
	CString inquiryresultvalue[6];
	
	io_d->inquiryAxisPOS(IPaddr, Command, AxisBitValues);
	
	//CString downvalue;
	for (int i=0;i<6; i++)
	{
		inquiryresultvalue[i].Format(_T("%d"), AxisBitValues[i]);
	}

	//downvalue.Format(_T("%d"), intVal_down);
	GetDlgItem(IDC_EDIT11)->SetWindowText(inquiryresultvalue[0]);
	GetDlgItem(IDC_EDIT7)->SetWindowText(inquiryresultvalue[1]);
	GetDlgItem(IDC_EDIT10)->SetWindowText(inquiryresultvalue[2]);
	GetDlgItem(IDC_EDIT12)->SetWindowText(inquiryresultvalue[3]);
	GetDlgItem(IDC_EDIT14)->SetWindowText(inquiryresultvalue[4]);
	GetDlgItem(IDC_EDIT15)->SetWindowText(inquiryresultvalue[5]);
	//GetDlgItem(IDC_EDIT14)->SetWindowText(downvalue);
	
	/*if (abb == inquiryresultvalue[2])
	{
		return;
	}*/
	


	
	

}


void CIOControl::OnEnChangeEdit14()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}

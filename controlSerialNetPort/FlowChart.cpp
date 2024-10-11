// FlowChart.cpp : 实现文件
//

#include "stdafx.h"
#include "controlSerialNetPort.h"
#include "FlowChart.h"
#include "afxdialogex.h"
#include "controlSerialNetPortDlg.h"
#include <afxtempl.h>
#include "Public.h"

// CFlowChart 对话框
CFlowChart* pFlow;
extern CcontrolSerialNetPortDlg* pMainDlg;
//CString CPublic::initFileName1;
//CString CPublic::initFileName2;
//CString CPublic::autoFileName1;
//CString CPublic::autoFileName2;


IMPLEMENT_DYNAMIC(CFlowChart, CDialogEx)

CFlowChart::CFlowChart(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_FlowChart, pParent)
{
}

CFlowChart::~CFlowChart()
{
}

void CFlowChart::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_STATIC1001, m_flowIcon1001);
	DDX_Control(pDX, IDC_STATIC2001, m_flowIcon2001);
	DDX_Control(pDX, IDC_STATIC1002, m_flowIcon1002);
	DDX_Control(pDX, IDC_STATIC2002, m_flowIcon2002);
	DDX_Control(pDX, IDC_STATIC1003, m_flowIcon1003);
	DDX_Control(pDX, IDC_STATIC2003, m_flowIcon2003);
	DDX_Control(pDX, IDC_STATIC1004, m_flowIcon1004);
	DDX_Control(pDX, IDC_STATIC2004, m_flowIcon2004);
	DDX_Control(pDX, IDC_STATIC1005, m_flowIcon1005);
	DDX_Control(pDX, IDC_STATIC2005, m_flowIcon2005);
	DDX_Control(pDX, IDC_STATIC1006, m_flowIcon1006);
	DDX_Control(pDX, IDC_STATIC2006, m_flowIcon2006);
	DDX_Control(pDX, IDC_STATIC1007, m_flowIcon1007);
	DDX_Control(pDX, IDC_STATIC2007, m_flowIcon2007);
	DDX_Control(pDX, IDC_STATIC1008, m_flowIcon1008);
	DDX_Control(pDX, IDC_STATIC2008, m_flowIcon2008);
	DDX_Control(pDX, IDC_STATIC1009, m_flowIcon1009);
	DDX_Control(pDX, IDC_STATIC2009, m_flowIcon2009);
	DDX_Control(pDX, IDC_STATIC1010, m_flowIcon1010);
	DDX_Control(pDX, IDC_STATIC2010, m_flowIcon2010);
	DDX_Control(pDX, IDC_STATIC1011, m_flowIcon1011);
	DDX_Control(pDX, IDC_STATIC2011, m_flowIcon2011);
	DDX_Control(pDX, IDC_STATIC2012, m_flowIcon2012);
	DDX_Control(pDX, IDC_STATIC2013, m_flowIcon2013);
	DDX_Control(pDX, IDC_STATIC2014, m_flowIcon2014);
	DDX_Control(pDX, IDC_STATIC2015, m_flowIcon2015);
	DDX_Control(pDX, IDC_STATIC2016, m_flowIcon2016);
	DDX_Control(pDX, IDC_STATIC2017, m_flowIcon2017);
	DDX_Control(pDX, IDC_STATIC2018, m_flowIcon2018);
	DDX_Control(pDX, IDC_STATIC2019, m_flowIcon2019);
	DDX_Control(pDX, IDC_STATIC2020, m_flowIcon2020);
	DDX_Control(pDX, IDC_STATIC2021, m_flowIcon2021);
	DDX_Control(pDX, IDC_STATIC2022, m_flowIcon2022);
	DDX_Control(pDX, IDC_STATIC1022, m_flowIcon1022);
	DDX_Control(pDX, IDC_STATIC1021, m_flowIcon1021);
	DDX_Control(pDX, IDC_STATIC1020, m_flowIcon1020);
	DDX_Control(pDX, IDC_STATIC1019, m_flowIcon1019);
	DDX_Control(pDX, IDC_STATIC1018, m_flowIcon1018);
	DDX_Control(pDX, IDC_STATIC1017, m_flowIcon1017);
	DDX_Control(pDX, IDC_STATIC1016, m_flowIcon1016);
	DDX_Control(pDX, IDC_STATIC1015, m_flowIcon1015);
	DDX_Control(pDX, IDC_STATIC1014, m_flowIcon1014);
	DDX_Control(pDX, IDC_STATIC1013, m_flowIcon1013);
	DDX_Control(pDX, IDC_STATIC1012, m_flowIcon1012);
	DDX_Control(pDX, IDC_STATICstart, m_startflow);

	DDX_Control(pDX, IDC_STATIC1023, m_flowIcon1023);
	DDX_Control(pDX, IDC_STATIC1024, m_flowIcon1024);
	DDX_Control(pDX, IDC_STATIC1025, m_flowIcon1025);
	DDX_Control(pDX, IDC_STATIC1026, m_flowIcon1026);
	DDX_Control(pDX, IDC_STATIC1027, m_flowIcon1027);
	DDX_Control(pDX, IDC_STATIC1028, m_flowIcon1028);
	DDX_Control(pDX, IDC_STATIC1029, m_flowIcon1029);
	DDX_Control(pDX, IDC_STATIC1030, m_flowIcon1030);
	DDX_Control(pDX, IDC_STATIC1031, m_flowIcon1031);
	DDX_Control(pDX, IDC_STATIC1032, m_flowIcon1032);
	DDX_Control(pDX, IDC_STATIC1033, m_flowIcon1033);
	DDX_Control(pDX, IDC_STATIC1034, m_flowIcon1034);
	DDX_Control(pDX, IDC_STATIC1035, m_flowIcon1035);
	DDX_Control(pDX, IDC_STATIC1036, m_flowIcon1036);
	DDX_Control(pDX, IDC_STATIC1037, m_flowIcon1037);
	DDX_Control(pDX, IDC_STATIC1038, m_flowIcon1038);
	DDX_Control(pDX, IDC_STATIC1039, m_flowIcon1039);
	DDX_Control(pDX, IDC_STATIC1040, m_flowIcon1040);
	DDX_Control(pDX, IDC_STATIC1041, m_flowIcon1041);
	DDX_Control(pDX, IDC_STATIC1042, m_flowIcon1042);
	DDX_Control(pDX, IDC_STATIC1043, m_flowIcon1043);
	DDX_Control(pDX, IDC_STATIC1044, m_flowIcon1044);
	DDX_Control(pDX, IDC_STATIC2023, m_flowIcon2023);
	DDX_Control(pDX, IDC_STATIC2024, m_flowIcon2024);
	DDX_Control(pDX, IDC_STATIC2025, m_flowIcon2025);
	DDX_Control(pDX, IDC_STATIC2026, m_flowIcon2026);
	DDX_Control(pDX, IDC_STATIC2027, m_flowIcon2027);
	DDX_Control(pDX, IDC_STATIC2028, m_flowIcon2028);
	DDX_Control(pDX, IDC_STATIC2029, m_flowIcon2029);
	DDX_Control(pDX, IDC_STATIC2030, m_flowIcon2030);
	DDX_Control(pDX, IDC_STATIC2031, m_flowIcon2031);
	DDX_Control(pDX, IDC_STATIC2032, m_flowIcon2032);
	DDX_Control(pDX, IDC_STATIC2033, m_flowIcon2033);
	DDX_Control(pDX, IDC_STATIC2034, m_flowIcon2034);
	DDX_Control(pDX, IDC_STATIC2035, m_flowIcon2035);
	DDX_Control(pDX, IDC_STATIC2036, m_flowIcon2036);
	DDX_Control(pDX, IDC_STATIC2037, m_flowIcon2037);
	DDX_Control(pDX, IDC_STATIC2038, m_flowIcon2038);
	DDX_Control(pDX, IDC_STATIC2039, m_flowIcon2039);
	DDX_Control(pDX, IDC_STATIC2040, m_flowIcon2040);
	DDX_Control(pDX, IDC_STATIC2041, m_flowIcon2041);
	DDX_Control(pDX, IDC_STATIC2042, m_flowIcon2042);
	DDX_Control(pDX, IDC_STATIC2043, m_flowIcon2043);
	DDX_Control(pDX, IDC_STATIC2044, m_flowIcon2044);
}


BEGIN_MESSAGE_MAP(CFlowChart, CDialogEx)
	ON_BN_CLICKED(IDOK, &CFlowChart::OnBnClickedOk)
	ON_BN_CLICKED(IDOK2, &CFlowChart::OnBnClickedOk2)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CFlowChart 消息处理程序
void CFlowChart::LoadFlowchart(UINT ID, CStatic*m_mm)//加载icon函数
{
	CBitmap bitmap;  // CBitmap对象，用于加载位图   
	HBITMAP hBmp;    // 保存CBitmap加载的位图的句柄   
	bitmap.LoadBitmap(ID);  // 将位图IDB_BITMAP1加载到bitmap   
	hBmp = (HBITMAP)bitmap.GetSafeHandle();  // 获取bitmap加载位图的句柄  
	(*m_mm).SetBitmap(hBmp);    // 设置图片控件m_jzmPicture的位图图片为IDB_BITMAP1  
}
void CFlowChart::DrawLine(CPoint p1, CPoint p2)//带箭头
{
	CClientDC dc(this);//获取DC
	CPen pen, pen1, *oldpen;
	int PenLineWidth = 2;//为了根据线条宽度设置箭头的大小
	pen.CreatePen(PS_SOLID, PenLineWidth, RGB(80, 80, 80));
	pen1.CreatePen(PS_SOLID, PenLineWidth, RGB(80, 80, 80));
	oldpen = dc.SelectObject(&pen);

	double theta = 3.1415926 / 15 * PenLineWidth;//转换为弧度
	double Px, Py, P1x, P1y, P2x, P2y;
	//以P2为原点得到向量P2P1（P）
	Px = p1.x - p2.x;
	Py = p1.y - p2.y;
	//向量P旋转theta角得到向量P1
	P1x = Px*cos(theta) - Py*sin(theta);
	P1y = Px*sin(theta) + Py*cos(theta);
	//向量P旋转-theta角得到向量P2
	P2x = Px*cos(-theta) - Py*sin(-theta);
	P2y = Px*sin(-theta) + Py*cos(-theta);
	//伸缩向量至制定长度
	double x1, x2;
	int length = 10;
	x1 = sqrt(P1x*P1x + P1y*P1y);
	P1x = P1x*length / x1;
	P1y = P1y*length / x1;
	x2 = sqrt(P2x*P2x + P2y*P2y);
	P2x = P2x*length / x2;
	P2y = P2y*length / x2;
	//平移变量到直线的末端
	P1x = P1x + p2.x;
	P1y = P1y + p2.y;
	P2x = P2x + p2.x;
	P2y = P2y + p2.y;
	dc.MoveTo(p1.x, p1.y);//移动画笔到第一个点
	dc.LineTo(p2.x, p2.y);//划线
	dc.SelectObject(&pen1);
	dc.MoveTo(p2.x, p2.y);//移动到第二个点
	dc.LineTo(P1x, P1y);//划线到第三个点
	dc.MoveTo(p2.x, p2.y);//移动到第二个点
	dc.LineTo(P2x, P2y);//划线到第四个点
	dc.MoveTo(P1x, P1y);//移动到第三个点
	dc.LineTo(P2x, P2y);//划线到第四个点

						//填充三角形区域
	CPoint ptVertex[3];
	ptVertex[0].x = p2.x;
	ptVertex[0].y = p2.y;
	ptVertex[1].x = P1x;
	ptVertex[1].y = P1y;
	ptVertex[2].x = P2x;
	ptVertex[2].y = P2y;
	CBrush br(RGB(80, 80, 80));
	CRgn rgn;
	rgn.CreatePolygonRgn(ptVertex, 3, ALTERNATE);//可以创建一个由一系列点围成的区域。
	dc.FillRgn(&rgn, &br);//指定刷子填充指定区域

	dc.SelectObject(oldpen);

	br.DeleteObject();
	rgn.DeleteObject();
}
void CFlowChart::DrawCommonLine(CPoint p1, CPoint p2)//不带箭头的直线
{
	CClientDC dc(this);//获取DC
	CPen pen, *oldpen;
	int PenLineWidth = 2;//为了根据线条宽度设置箭头的大小
	pen.CreatePen(PS_SOLID, PenLineWidth, RGB(80, 80, 80));
	oldpen = dc.SelectObject(&pen);
	dc.MoveTo(p1.x, p1.y);//移动画笔到第一个点
	dc.LineTo(p2.x, p2.y);//划线
	dc.SelectObject(oldpen);
}

//CMap<int, int, CStatic, CStatic&> myMap;

BOOL CFlowChart::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// TODO:  在此添加额外的初始化
	pFlow = this;
	CStaticArray();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
void CFlowChart::CStaticArray()//定义指针数组
{
	for (int i = 0; i < 2000; i++)
	{
		m[i] = new CStatic;
	}
	m[1] = &m_flowIcon1001;
	m[2] = &m_flowIcon1002;
	m[3] = &m_flowIcon1003;
	m[4] = &m_flowIcon1004;
	m[5] = &m_flowIcon1005;
	m[6] = &m_flowIcon1006;
	m[7] = &m_flowIcon1007;
	m[8] = &m_flowIcon1008;
	m[9] = &m_flowIcon1009;
	m[10] = &m_flowIcon1010;
	m[11] = &m_flowIcon1011;
	m[12] = &m_flowIcon1012;
	m[13] = &m_flowIcon1013;
	m[14] = &m_flowIcon1014;
	m[15] = &m_flowIcon1015;
	m[16] = &m_flowIcon1016;
	m[17] = &m_flowIcon1017;
	m[18] = &m_flowIcon1018;
	m[19] = &m_flowIcon1019;
	m[20] = &m_flowIcon1020;
	m[21] = &m_flowIcon1021;
	m[22] = &m_flowIcon1022;
	m[23] = &m_flowIcon1023;
	m[24] = &m_flowIcon1024;
	m[25] = &m_flowIcon1025;
	m[26] = &m_flowIcon1026;
	m[27] = &m_flowIcon1027;
	m[28] = &m_flowIcon1028;
	m[29] = &m_flowIcon1029;
	m[30] = &m_flowIcon1030;
	m[31] = &m_flowIcon1031;
	m[32] = &m_flowIcon1032;
	m[33] = &m_flowIcon1033;
	m[34] = &m_flowIcon1034;
	m[35] = &m_flowIcon1035;
	m[36] = &m_flowIcon1036;
	m[37] = &m_flowIcon1037;
	m[38] = &m_flowIcon1038;
	m[39] = &m_flowIcon1039;
	m[40] = &m_flowIcon1040;
	m[41] = &m_flowIcon1041;
	m[42] = &m_flowIcon1042;
	m[43] = &m_flowIcon1043;
	m[44] = &m_flowIcon1044;

	m[1001] = &m_flowIcon2001;
	m[1002] = &m_flowIcon2002;
	m[1003] = &m_flowIcon2003;
	m[1004] = &m_flowIcon2004;
	m[1005] = &m_flowIcon2005;
	m[1006] = &m_flowIcon2006;
	m[1007] = &m_flowIcon2007;
	m[1008] = &m_flowIcon2008;
	m[1009] = &m_flowIcon2009;
	m[1010] = &m_flowIcon2010;
	m[1011] = &m_flowIcon2011;
	m[1012] = &m_flowIcon2012;
	m[1013] = &m_flowIcon2013;
	m[1014] = &m_flowIcon2014;
	m[1015] = &m_flowIcon2015;
	m[1016] = &m_flowIcon2016;
	m[1017] = &m_flowIcon2017;
	m[1018] = &m_flowIcon2018;
	m[1019] = &m_flowIcon2019;
	m[1020] = &m_flowIcon2020;
	m[1021] = &m_flowIcon2021;
	m[1022] = &m_flowIcon2022;
	m[1023] = &m_flowIcon2023;
	m[1024] = &m_flowIcon2024;
	m[1025] = &m_flowIcon2025;
	m[1026] = &m_flowIcon2026;
	m[1027] = &m_flowIcon2027;
	m[1028] = &m_flowIcon2028;
	m[1029] = &m_flowIcon2029;
	m[1030] = &m_flowIcon2030;
	m[1031] = &m_flowIcon2031;
	m[1032] = &m_flowIcon2032;
	m[1033] = &m_flowIcon2033;
	m[1034] = &m_flowIcon2034;
	m[1035] = &m_flowIcon2035;
	m[1036] = &m_flowIcon2036;
	m[1037] = &m_flowIcon2037;
	m[1038] = &m_flowIcon2038;
	m[1039] = &m_flowIcon2039;
	m[1040] = &m_flowIcon2040;
	m[1041] = &m_flowIcon2041;
	m[1042] = &m_flowIcon2042;
	m[1043] = &m_flowIcon2043;
	m[1044] = &m_flowIcon2044;

}

void CFlowChart::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}


void CFlowChart::OnBnClickedOk2()
{
	// TODO: 在此添加控件通知处理程序代码
}




void CFlowChart::OnPaint()//---------------------------------------------------------------------1解析并画流程图的入口函数
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码

	int workNum[MAX_CAM];//设置流程个数
	CString filePath[MAX_CAM];//流程文件路径
	CString name[MAX_CAM];//流程名称
	CStdioFile file[MAX_CAM];//流程文档
	int m_commNum[MAX_CAM];
	CString str;
	BOOL ret[MAX_CAM];
	CString path;
	GetModuleFileName(NULL, path.GetBufferSetLength(MAX_PATH + 1), MAX_PATH);//获取默认exe路径
	path.ReleaseBuffer();
	int pos = path.ReverseFind('\\');
	path = path.Left(pos);//去掉路径中的exe
	path = path + _T("\\");
	
	name[0] = pMainDlg->m_initTXT1;
	name[1] = pMainDlg->m_initTXT2;
	for (int i = 0; i < MAX_CAM; i++)
	{
		workNum[i] = i;
		str.Format(_T("%d"), i + 1);
		filePath[i] = path + name[i];//完整路径
		//LPCTSTR pszFileName[i] = filePath[i].GetBufferSetLength(filePath[i].GetLength());将CString转换成LPCTSTR
		ret[i] = file[i].Open(filePath[i].GetBufferSetLength(filePath[i].GetLength()), CFile::modeRead);//打开文件
	}
	UpdateData(FALSE);
	if (ret[0] == 1&&ret[1]==1)
	{
		BeginTransformation(file,m_commNum,workNum);//---------------------------------------------1.1开始解析函数
		//BeginTransformation(file[1],m_commNum[1],workNum[1]);//开始转换
	}
	else
	{
		AfxMessageBox(_T("请检查所选脚本文件是否在默认路径"));
		return;
		for (int i = 0; i < MAX_CAM; i++)//
		{
			file[workNum[i]].Close();
		}
	}
	
	for (int i = 0; i < MAX_CAM; i++)//
	{
		file[workNum[i]].Close();
	}
}
void CFlowChart::BeginTransformation(CStdioFile file[], int m_commNum[], int workNum[])//-----------------1.1开始解析函数
{
	CString str;
	
	for (int i = 0; i < MAX_CAM; i++)//
	{
		m_commNum[i] = pMainDlg->findCoronNum(&file[i]);//冒号个数，即指令的条数
	}
	
	if (m_commNum[0] == 0&& m_commNum[1] == 0)//两个线程均无指令再报警
		{
			AfxMessageBox(_T("脚本中无任何指令？"));
		}
	else
	{
		CommandTransformation(file, m_commNum, workNum);//------------------------------------------------1.1.1划线函数
	}
	
}

CString CFlowChart::flowchart(CStdioFile&file, int IDTXT, int m_m, int workNum)//根据命令名称来选择显示的图标和txt
{
	CString m_fileComm;//存储命令名称
	int commandnum;
	CString MiddleComm;
	if(workNum==1)
	{ 
		m_m = m_m + 1000;
	}
	//CStatic &m_mm=m_flowIcon1001;
	//if ()//myMap.Lookup(m_m, m_mm))//找到则为1，找不到返回null将值存入m_mm中
//	{m_m[1] = &m_flowIcon1001;
	if (feof(file.m_pStream)==FALSE)//feof检查文档是否到末尾，循环读取指令
	{
			
			m_fileComm = pMainDlg->findCoron(&file);//return str返回冒号和它前面的字符数据，即指令名称（包括冒号）：//如果到了结尾返回null？
			if (m_fileComm == _T("\r\nCommon:") || m_fileComm == _T("\r\nInquiry:"))//--------------------------------普通指令1
			{
				CString comm;
				comm = pMainDlg->ChineseTransformation(MiddleComm, &file);
				if (comm == _T("\r\nIO"))
				{
					SetDlgItemText(IDTXT, _T("IO"));//传值位置序号即可定这两个控件的ID编号和变量
					LoadFlowchart(30006, m[m_m]);//传值位置序号
					commandnum++;
				}
				else if (comm == _T("\r\nAxisMove"))
				{
					SetDlgItemText(IDTXT, _T("M"));//传值位置序号即可定这两个控件的ID编号和变量
					LoadFlowchart(30009, m[m_m]);//传值位置序号
					commandnum++;
				}
				else if (comm == _T("\r\nAxisSetTargetSpeed"))
				{
					SetDlgItemText(IDTXT, _T("SS"));//传值位置序号即可定这两个控件的ID编号和变量
					LoadFlowchart(30015, m[m_m]);//传值位置序号
					commandnum++;
				}
				else if (comm == _T("\r\nAxisSetHomePosition"))
				{
					SetDlgItemText(IDTXT, _T("SH"));//传值位置序号即可定这两个控件的ID编号和变量
					LoadFlowchart(30014, m[m_m]);//传值位置序号
					commandnum++;
				}
				else if (comm == _T("\r\nAxisGoHomePosition"))
				{
					SetDlgItemText(IDTXT, _T("H"));//传值位置序号即可定这两个控件的ID编号和变量
					LoadFlowchart(30012, m[m_m]);//传值位置序号
					commandnum++;
				}
				else if (comm == _T("\r\nAxisGoPositiveLimit"))
				{
					SetDlgItemText(IDTXT, _T("PL"));//传值位置序号即可定这两个控件的ID编号和变量
					LoadFlowchart(30011, m[m_m]);//传值位置序号
					commandnum++;
				}
				else if (comm == _T("\r\nAxisGoNegativeLimit"))
				{
					SetDlgItemText(IDTXT, _T("NL"));//传值位置序号即可定这两个控件的ID编号和变量
					LoadFlowchart(30010, m[m_m]);//传值位置序号
					commandnum++;
				}
				else if (comm == _T("\r\nAxisSMVR"))
				{
					SetDlgItemText(IDTXT, _T("S"));//传值位置序号即可定这两个控件的ID编号和变量
					LoadFlowchart(30013, m[m_m]);//传值位置序号
					commandnum++;
				}
				else if (comm == _T("\r\nAxisSMVR"))
				{
					SetDlgItemText(IDTXT, _T("S"));//传值位置序号即可定这两个控件的ID编号和变量
					LoadFlowchart(30013, m[m_m]);//传值位置序号
					commandnum++;
				}
				else if (comm == _T("\r\nLimit?"))
				{
					SetDlgItemText(IDTXT, _T("L?"));//传值位置序号即可定这两个控件的ID编号和变量
					LoadFlowchart(30017, m[m_m]);//传值位置序号
					commandnum++;
				}
				else if (comm == _T("\r\nRelativePosition?"))
				{
					SetDlgItemText(IDTXT, _T("RP?"));//传值位置序号即可定这两个控件的ID编号和变量
					LoadFlowchart(30018, m[m_m]);//传值位置序号
					commandnum++;
				}
				else if (comm == _T("\r\nAbsolutePosition?"))
				{
					SetDlgItemText(IDTXT, _T("AP?"));//传值位置序号即可定这两个控件的ID编号和变量
					LoadFlowchart(30016, m[m_m]);//传值位置序号
					commandnum++;
				}
				else if (comm == _T("\r\nIO?"))
				{
					SetDlgItemText(IDTXT, _T("AP?"));//传值位置序号即可定这两个控件的ID编号和变量
					LoadFlowchart(30006, m[m_m]);//传值位置序号
					commandnum++;
				}
				return comm;
			}
			else if (m_fileComm == _T("\r\nRobot:"))
			{
				CString comm[2];

				comm[1] = pMainDlg->ChineseTransformation(MiddleComm, &file);
				comm[2] = pMainDlg->ChineseTransformation(MiddleComm, &file);
			
				if (comm[1] == _T("\r\nRoute=MoveJ"))
				{
					SetDlgItemText(IDTXT, _T("J"));//传值位置序号即可定这两个控件的ID编号和变量
					LoadFlowchart(30004, m[m_m]);//传值位置序号
					commandnum++;
					return comm[1];
				}
				else if (comm[1] == _T("\r\nRoute=MoveL"))
				{
					SetDlgItemText(IDTXT, _T("L"));//传值位置序号即可定这两个控件的ID编号和变量
					LoadFlowchart(30004, m[m_m]);//传值位置序号
					commandnum++;
					return comm[1];
				}
				else if (comm[1] == _T("\r\nRobotAbsolutePosition?"))
				{
					SetDlgItemText(IDTXT, _T("P?"));//传值位置序号即可定这两个控件的ID编号和变量
					LoadFlowchart(30004, m[m_m]);//传值位置序号
					commandnum++;
					return comm[0];
				}
				else if (comm[1] == _T("\r\nRobotStatus?"))
				{
					SetDlgItemText(IDTXT, _T("S?"));//传值位置序号即可定这两个控件的ID编号和变量
					LoadFlowchart(30004, m[m_m]);//传值位置序号
					commandnum++;
					return comm[0];
				}
			}
			else if (m_fileComm == _T("\r\nDelayTime:"))
			{
				SetDlgItemText(IDTXT, _T("Time"));//传值位置序号即可定这两个控件的ID编号和变量
				LoadFlowchart(30003, m[m_m]);//传值位置序号
				commandnum++;
				return m_fileComm;
			}
			else if (m_fileComm == _T("\r\nThreadInteraction:"))//---------------线程交互命令5
			{
				CString comm;
				comm = pMainDlg->ChineseTransformation(MiddleComm, &file);
				if (comm == _T("\r\nWaitUntil"))
				{
					SetDlgItemText(IDTXT, _T("Wait"));//传值位置序号即可定这两个控件的ID编号和变量
					LoadFlowchart(30007, m[m_m]);//传值位置序号
					commandnum++;
				}
				else if (comm == _T("\r\nOrderContinue"))
				{
					SetDlgItemText(IDTXT, _T("Order"));//传值位置序号即可定这两个控件的ID编号和变量
					LoadFlowchart(30008, m[m_m]);//传值位置序号
					commandnum++;
				}
				return comm;
			}
			else if (m_fileComm == _T("\r\nImageProcessing:"))
			{
				SetDlgItemText(IDTXT, _T("IP"));//传值位置序号即可定这两个控件的ID编号和变量
				LoadFlowchart(30019, m[m_m]);//传值位置序号
				commandnum++;
				return m_fileComm;
			}
			else if (m_fileComm == _T("\r\nLightAdjusting:"))
			{
				SetDlgItemText(IDTXT, _T("L"));//传值位置序号即可定这两个控件的ID编号和变量
				LoadFlowchart(30005, m[m_m]);//传值位置序号
				commandnum++;
				return m_fileComm;
			}
			else if (m_fileComm == _T("\r\nAdjustingWithResult:"))
			{
				SetDlgItemText(IDTXT, _T("AWR"));//传值位置序号即可定这两个控件的ID编号和变量
				LoadFlowchart(30019, m[m_m]);//传值位置序号
				commandnum++;
				return m_fileComm;
			}
			return L"";//其他情况返回空字符
	}
	if (feof(file.m_pStream) == TRUE)//到末尾了
	{
		return L"TheEnd";
	}

//	else
//	{
//		AfxMessageBox(_T("CMap中无对应的数值？"));
	//}
}

void CFlowChart::DrawCommonFlow(CPoint p1, CPoint p2, int IDTXT, int IDPicture, CString str, CStatic*m_m)//普通画流程 函数
{
	SetDlgItemText(IDTXT, str);
	LoadFlowchart(IDPicture, m_m);
}
void CFlowChart::DrawTurnFlow(CPoint p1, CPoint p2, CPoint p3, CPoint p4, int IDTXT, int IDPicture, CString str, CStatic *m_m)//拐弯处流程 函数
{
	//DrawCommonLine(p1, p2);//画横直线
	//DrawCommonLine(p2, p3);//画竖直线
	//DrawCommonFlow(p3, p4, IDTXT, IDPicture, str, m_m);//普通画流程 函数
}

CString* CFlowChart::DrawRowFlow(CStdioFile file[],int row, int workNum[], CString str[])//需要分奇数偶数行 不一样 一个从左到右一个从右到左
{
	int num[2] = {22*(row-1),22*(row-1) };//初始化每一排最新开始的序号
	int IDTXT[2] = {10000+num[0] ,20000+num[1]};
	while (1)
	{
		if (row % 2 == 1)//奇数行 从左到右画，箭头位置递增
		{
			if (str[0] == L"TheEnd"&&str[1] == L"TheEnd")
			{
				DrawLine(CPoint((num[0] - (row - 1) * 22) * 50, 75 + 160 * (row - 1)), CPoint((num[0] - (row - 1) * 22) * 50, 55 + 160 * (row - 1)));//绘制带箭头直线函数工位一
				SetDlgItemText(IDTXT[0], _T("CloseTXT"));//传值位置序号即可定这两个控件的ID编号和变量
				LoadFlowchart(30002, m[num[0]]);//close
				DrawLine(CPoint((num[1] - (row - 1) * 22) * 50, 85 + 160 * (row - 1)), CPoint((num[1] - (row - 1) * 22) * 50, 105 + 160 * (row - 1)));//绘制带箭头直线函数工位二
				SetDlgItemText(IDTXT[1], _T("CloseTXT"));//传值位置序号即可定这两个控件的ID编号和变量
				int s = num[1] + 1000;
				LoadFlowchart(30002, m[s]);//close
				return str;
				break;
			}
			if (max == row * 22)
			{
				return str;//return了就不往下执行了
				break;
			}
			else
			{
				if (str[0] == L"TheEnd")
				{
					num[0]++;
					IDTXT[0]++;
					num[1]++;
					IDTXT[1]++;
					DrawLine(CPoint((num[1] - (row - 1) * 22) * 50, 85 + 160 * (row - 1)), CPoint((num[1] - (row - 1) * 22) * 50, 105 + 160 * (row - 1)));//绘制带箭头直线函数工位二
					str[1] = flowchart(file[1], IDTXT[1], num[1], workNum[1]);
					max = num[1];
				}
				else if (str[1] == L"TheEnd")
				{
					num[0]++;
					IDTXT[0]++;
					DrawLine(CPoint((num[0] - (row - 1) * 22) * 50, 75 + 160 * (row - 1)), CPoint((num[0] - (row - 1) * 22) * 50, 55 + 160 * (row - 1)));//绘制带箭头直线函数工位一
					str[0] = flowchart(file[0], IDTXT[0], num[0], workNum[0]);
					num[1]++;
					IDTXT[1]++;
					max = num[1];

				}
				else if (str[0] != L"TheEnd"&&str[1] != L"TheEnd")
				{

					if (str[0] != L"WaitUntil"&&str[1] != L"OrderContinue")//正常运行
					{
						num[0]++;
						IDTXT[0]++;
						DrawLine(CPoint((num[0] - (row - 1) * 22) * 50, 75 + 160 * (row - 1)), CPoint((num[0] - (row - 1) * 22) * 50, 55 + 160 * (row - 1)));//绘制带箭头直线函数工位一
						str[0] = flowchart(file[0], IDTXT[0], num[0], workNum[0]);

						if (str[1] != L"WaitUntil" || str[0] == L"OrderContinue")//正常运行。
						{
							num[1]++;
							IDTXT[1]++;
							DrawLine(CPoint((num[1] - (row - 1) * 22) * 50, 85 + 160 * (row - 1)), CPoint((num[1] - (row - 1) * 22) * 50, 105 + 160 * (row - 1)));//绘制带箭头直线函数工位二
							str[1] = flowchart(file[1], IDTXT[1], num[1], workNum[1]);
						}
						else//未获激活的等待
						{
							num[1]++;
							IDTXT[1]++;
						}
						max = num[1];
					}
					else if (str[0] == L"WaitUntil"&&str[1] != L"OrderContinue")//等待
					{
						num[0]++;
						IDTXT[0]++;//置空

						num[1]++;//线程2正常运行
						IDTXT[1]++;
						DrawLine(CPoint((num[1] - (row - 1) * 22) * 50, 85 + 160 * (row - 1)), CPoint((num[1] - (row - 1) * 22) * 50, 105 + 160 * (row - 1)));//绘制带箭头直线函数线程2
						str[1] = flowchart(file[1], IDTXT[1], num[1], workNum[1]);
						max = num[1];
					}
					else if (str[0] == L"WaitUntil"&&str[1] == L"OrderContinue")//等待过程中获得激活
					{
						num[0]++;
						IDTXT[0]++;
						DrawLine(CPoint((num[0] - (row - 1) * 22) * 50, 75 + 160 * (row - 1)), CPoint((num[0] - (row - 1) * 22) * 50, 55 + 160 * (row - 1)));//绘制带箭头直线函数工位一
						str[0] = flowchart(file[0], IDTXT[0], num[0], workNum[0]);

						num[1]++;//线程2正常运行
						IDTXT[1]++;
						DrawLine(CPoint((num[1] - (row - 1) * 22) * 50, 85 + 160 * (row - 1)), CPoint((num[1] - (row - 1) * 22) * 50, 105 + 160 * (row - 1)));//绘制带箭头直线函数线程2
						str[1] = flowchart(file[1], IDTXT[1], num[1], workNum[1]);
						max = num[1];
					}
					continue;
				}
			}
			max = num[1];//一组一组画，画完结束是线程2的编号
		}
		else if (row % 2 == 0)//偶数行，从右向左画，箭头的位置递减
		{
			if (str[0] == L"TheEnd"&&str[1] == L"TheEnd")
			{
				DrawLine(CPoint(1150-(num[0] - (row - 1) * 22) * 50, 75 + 160 * (row - 1)), CPoint(1150 - (num[0] - (row - 1) * 22) * 50, 55 + 160 * (row - 1)));//绘制带箭头直线函数工位一
				SetDlgItemText(IDTXT[0], _T("CloseTXT"));//传值位置序号即可定这两个控件的ID编号和变量
				LoadFlowchart(30002, m[num[0]]);//close
				DrawLine(CPoint(1150 - (num[1] - (row - 1) * 22) * 50, 85 + 160 * (row - 1)), CPoint(1150 - (num[1] - (row - 1) * 22) * 50, 105 + 160 * (row - 1)));//绘制带箭头直线函数工位二
				SetDlgItemText(IDTXT[1], _T("CloseTXT"));//传值位置序号即可定这两个控件的ID编号和变量
				int s = num[1] + 1000;
				LoadFlowchart(30002, m[s]);//close
				return str;
				break;
			}
			else if (max == row * 22)
			{
				return str;
				break;
			}
			else
			{
				if (str[0] == L"TheEnd")
				{
					num[0]++;
					IDTXT[0]++;
					num[1]++;
					IDTXT[1]++;
					DrawLine(CPoint(1150 - (num[1] - (row - 1) * 22) * 50, 85 + 160 * (row - 1)), CPoint(1150 - (num[1] - (row - 1) * 22) * 50, 105 + 160 * (row - 1)));//绘制带箭头直线函数工位二
					str[1] = flowchart(file[1], IDTXT[1], num[1], workNum[1]);
					max = num[1];
				}
				else if (str[1] == L"TheEnd")
				{
					num[0]++;
					IDTXT[0]++;
					DrawLine(CPoint(1150 - (num[0] - (row - 1) * 22) * 50, 75 + 160 * (row - 1)), CPoint(1150 - (num[0] - (row - 1) * 22) * 50, 55 + 160 * (row - 1)));//绘制带箭头直线函数工位一
					str[0] = flowchart(file[0], IDTXT[0], num[0], workNum[0]);
					num[1]++;
					IDTXT[1]++;
					max = num[1];
				}
				else if (str[0] != L"TheEnd"&&str[1] != L"TheEnd")
				{

					if (str[0] != L"WaitUntil"&&str[1] != L"OrderContinue")//正常运行
					{
						num[0]++;
						IDTXT[0]++;
						DrawLine(CPoint(1150 - (num[0] - (row - 1) * 22) * 50, 75 + 160 * (row - 1)), CPoint(1150 - (num[0] - (row - 1) * 22) * 50, 55 + 160 * (row - 1)));//绘制带箭头直线函数工位一
						str[0] = flowchart(file[0], IDTXT[0], num[0], workNum[0]);

						if (str[1] != L"WaitUntil" || str[0] == L"OrderContinue")//正常运行。
						{
							num[1]++;
							IDTXT[1]++;
							DrawLine(CPoint(1150 - (num[1] - (row - 1) * 22) * 50, 85 + 160 * (row - 1)), CPoint(1150 - (num[1] - (row - 1) * 22) * 50, 105 + 160 * (row - 1)));//绘制带箭头直线函数工位二
							str[1] = flowchart(file[1], IDTXT[1], num[1], workNum[1]);
							max = num[1];
						}
						else//未获激活的等待
						{
							num[1]++;
							IDTXT[1]++;
							max = num[1];
						}

					}
					else if (str[0] == L"WaitUntil"&&str[1] != L"OrderContinue")//等待
					{
						num[0]++;
						IDTXT[0]++;//置空

						num[1]++;//线程2正常运行
						IDTXT[1]++;
						DrawLine(CPoint(1150 - (num[1] - (row - 1) * 22) * 50, 85 + 160 * (row - 1)), CPoint(1150 - (num[1] - (row - 1) * 22) * 50, 105 + 160 * (row - 1)));//绘制带箭头直线函数线程2
						str[1] = flowchart(file[1], IDTXT[1], num[1], workNum[1]);
						max = num[1];
					}
					else if (str[0] == L"WaitUntil"&&str[1] == L"OrderContinue")//等待过程中获得激活
					{
						num[0]++;
						IDTXT[0]++;
						DrawLine(CPoint(1150 - (num[0] - (row - 1) * 22) * 50, 75 + 160 * (row - 1)), CPoint(1150 - (num[0] - (row - 1) * 22) * 50, 55 + 160 * (row - 1)));//绘制带箭头直线函数工位一
						str[0] = flowchart(file[0], IDTXT[0], num[0], workNum[0]);

						num[1]++;//线程2正常运行
						IDTXT[1]++;
						DrawLine(CPoint(1150 - (num[1] - (row - 1) * 22) * 50, 85 + 160 * (row - 1)), CPoint(1150 - (num[1] - (row - 1) * 22) * 50, 105 + 160 * (row - 1)));//绘制带箭头直线函数线程2
						str[1] = flowchart(file[1], IDTXT[1], num[1], workNum[1]);
						max = num[1];
					}
					continue;
				}
			}
			max = num[1];//一组一组画，画完结束是线程2的编号
		}
	}
}

void CFlowChart::CommandTransformation(CStdioFile file[], int m_commNum[], int workNum[])//-----------------------1.1.1画线函数
{
	CString str[2] = { L"",L"" };//初始化返回的字符串
	max =0;// m_commNum[0] > m_commNum[1] ? m_commNum[0] : m_commNum[1];//最大的
	int row =1;//记录排号
	LoadFlowchart(IDB_BITMAP_Start, &m_startflow);//开始图标

	DrawCommonLine(CPoint(43, 75), CPoint(1130, 75));
	DrawCommonLine(CPoint(43, 85), CPoint(1120, 85));
	DrawCommonLine(CPoint(1130, 75), CPoint(1130, 245));
	DrawCommonLine(CPoint(1120, 85), CPoint(1120, 235));

	DrawCommonLine(CPoint(20, 235), CPoint(1120, 235));
	DrawCommonLine(CPoint(30, 245), CPoint(1130, 245));
	DrawCommonLine(CPoint(20, 235), CPoint(20, 405));
	DrawCommonLine(CPoint(30, 245), CPoint(30, 395));

	DrawCommonLine(CPoint(20, 405), CPoint(1120, 405));
	DrawCommonLine(CPoint(30, 395), CPoint(1130, 395));
	DrawCommonLine(CPoint(1130, 395), CPoint(1130, 565));
	DrawCommonLine(CPoint(1120, 405), CPoint(1120, 555));

	DrawCommonLine(CPoint(20, 555), CPoint(1120, 555));
	DrawCommonLine(CPoint(30, 565), CPoint(1130, 565));
	DrawCommonLine(CPoint(20, 555), CPoint(20, 725));
	DrawCommonLine(CPoint(30, 565), CPoint(30, 715));

	DrawCommonLine(CPoint(20, 725), CPoint(1120, 725));
	DrawCommonLine(CPoint(30, 715), CPoint(1130, 715));
	DrawCommonLine(CPoint(1130, 715), CPoint(1130, 885));
	DrawCommonLine(CPoint(1120, 725), CPoint(1120, 875));

	DrawCommonLine(CPoint(20, 875), CPoint(1120, 875));
	DrawCommonLine(CPoint(20, 885), CPoint(1130, 885));
	while (1)//无限循
	{
		if (max == 0)//画第一排的箭头和图标无需条件
		{
			CString *p = DrawRowFlow(file, 1, workNum, str);
			str[0] = *p[0];
			str[1] = *p[1];
		}
		else if (max == 22)//画第2排的箭头和图标
		{
			row++;
			CString *p = DrawRowFlow(file, 2, workNum, str);//传递出来str
			str[0] = *p[0];
			str[1] = *p[1];
		}
		else if (max == 44)//画第3排的箭头和图标
		{
			row++;
			CString *p = DrawRowFlow(file, 3,workNum, str);
			str[0] = *p[0];
			str[1] = *p[1];
		}
		else if (max == 66)//画第4排的箭头和图标
		{
			row++;
			CString *p = DrawRowFlow(file, 4, workNum, str);
			str[0] = *p[0];
			str[1] = *p[1];
		}

		else if (max == 88)//画第5排的箭头和图标
		{
			row++;
			CString *p = DrawRowFlow(file, 5, workNum, str);
			str[0] = *p[0];
			str[1] = *p[1];
		}
		else if (max == 110)//画第6排的箭头和图标
		{
			row++;
			CString *p = DrawRowFlow(file, 6, workNum, str);
			str[0] = *p[0];
			str[1] = *p[1];

		}
		else if (max == 132) // 画第7排的箭头和图标
		{
			row++;
			CString *p = DrawRowFlow(file, 7,  workNum, str);
			str[0] = *p[0];
			str[1] = *p[1];
		}
		else if (max == 154)//画第8排的箭头和图标
		{
			row++;
			CString *p = DrawRowFlow(file, 8,  workNum, str);
			str[0] = *p[0];
			str[1] = *p[1];
		}
		else
		{
			break;
		}
	}
}

HBRUSH CFlowChart::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	int i;
	// TODO:  在此更改 DC 的任何特性
	for (i = 10001; i <= 10044; i++)
	{
		if (pWnd->GetDlgCtrlID() == i)//GetDlgCtrlID()功能是获取指定控件的ID号
		{
			pDC->SetTextColor(RGB(50, 50, 50));//设置静态文本框字体颜色
			pDC->SetBkMode(TRANSPARENT);//设置为透明
			return HBRUSH(GetStockObject(HOLLOW_BRUSH));//设置透明这句话不能掉
		}// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	}

	for (i = 20001; i <= 20044; i++)
	{
		if (pWnd->GetDlgCtrlID() == i)//GetDlgCtrlID()功能是获取指定控件的ID号

		{
			pDC->SetTextColor(RGB(50, 50, 50));//设置静态文本框字体颜色
			pDC->SetBkMode(TRANSPARENT);//设置为透明
			return HBRUSH(GetStockObject(HOLLOW_BRUSH));//设置透明这句话不能掉
		}
		// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	}
	return hbr;
}

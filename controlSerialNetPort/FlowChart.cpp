// FlowChart.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "controlSerialNetPort.h"
#include "FlowChart.h"
#include "afxdialogex.h"
#include "controlSerialNetPortDlg.h"
#include <afxtempl.h>
#include "Public.h"

// CFlowChart �Ի���
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


// CFlowChart ��Ϣ�������
void CFlowChart::LoadFlowchart(UINT ID, CStatic*m_mm)//����icon����
{
	CBitmap bitmap;  // CBitmap�������ڼ���λͼ   
	HBITMAP hBmp;    // ����CBitmap���ص�λͼ�ľ��   
	bitmap.LoadBitmap(ID);  // ��λͼIDB_BITMAP1���ص�bitmap   
	hBmp = (HBITMAP)bitmap.GetSafeHandle();  // ��ȡbitmap����λͼ�ľ��  
	(*m_mm).SetBitmap(hBmp);    // ����ͼƬ�ؼ�m_jzmPicture��λͼͼƬΪIDB_BITMAP1  
}
void CFlowChart::DrawLine(CPoint p1, CPoint p2)//����ͷ
{
	CClientDC dc(this);//��ȡDC
	CPen pen, pen1, *oldpen;
	int PenLineWidth = 2;//Ϊ�˸�������������ü�ͷ�Ĵ�С
	pen.CreatePen(PS_SOLID, PenLineWidth, RGB(80, 80, 80));
	pen1.CreatePen(PS_SOLID, PenLineWidth, RGB(80, 80, 80));
	oldpen = dc.SelectObject(&pen);

	double theta = 3.1415926 / 15 * PenLineWidth;//ת��Ϊ����
	double Px, Py, P1x, P1y, P2x, P2y;
	//��P2Ϊԭ��õ�����P2P1��P��
	Px = p1.x - p2.x;
	Py = p1.y - p2.y;
	//����P��תtheta�ǵõ�����P1
	P1x = Px*cos(theta) - Py*sin(theta);
	P1y = Px*sin(theta) + Py*cos(theta);
	//����P��ת-theta�ǵõ�����P2
	P2x = Px*cos(-theta) - Py*sin(-theta);
	P2y = Px*sin(-theta) + Py*cos(-theta);
	//�����������ƶ�����
	double x1, x2;
	int length = 10;
	x1 = sqrt(P1x*P1x + P1y*P1y);
	P1x = P1x*length / x1;
	P1y = P1y*length / x1;
	x2 = sqrt(P2x*P2x + P2y*P2y);
	P2x = P2x*length / x2;
	P2y = P2y*length / x2;
	//ƽ�Ʊ�����ֱ�ߵ�ĩ��
	P1x = P1x + p2.x;
	P1y = P1y + p2.y;
	P2x = P2x + p2.x;
	P2y = P2y + p2.y;
	dc.MoveTo(p1.x, p1.y);//�ƶ����ʵ���һ����
	dc.LineTo(p2.x, p2.y);//����
	dc.SelectObject(&pen1);
	dc.MoveTo(p2.x, p2.y);//�ƶ����ڶ�����
	dc.LineTo(P1x, P1y);//���ߵ���������
	dc.MoveTo(p2.x, p2.y);//�ƶ����ڶ�����
	dc.LineTo(P2x, P2y);//���ߵ����ĸ���
	dc.MoveTo(P1x, P1y);//�ƶ�����������
	dc.LineTo(P2x, P2y);//���ߵ����ĸ���

						//�������������
	CPoint ptVertex[3];
	ptVertex[0].x = p2.x;
	ptVertex[0].y = p2.y;
	ptVertex[1].x = P1x;
	ptVertex[1].y = P1y;
	ptVertex[2].x = P2x;
	ptVertex[2].y = P2y;
	CBrush br(RGB(80, 80, 80));
	CRgn rgn;
	rgn.CreatePolygonRgn(ptVertex, 3, ALTERNATE);//���Դ���һ����һϵ�е�Χ�ɵ�����
	dc.FillRgn(&rgn, &br);//ָ��ˢ�����ָ������

	dc.SelectObject(oldpen);

	br.DeleteObject();
	rgn.DeleteObject();
}
void CFlowChart::DrawCommonLine(CPoint p1, CPoint p2)//������ͷ��ֱ��
{
	CClientDC dc(this);//��ȡDC
	CPen pen, *oldpen;
	int PenLineWidth = 2;//Ϊ�˸�������������ü�ͷ�Ĵ�С
	pen.CreatePen(PS_SOLID, PenLineWidth, RGB(80, 80, 80));
	oldpen = dc.SelectObject(&pen);
	dc.MoveTo(p1.x, p1.y);//�ƶ����ʵ���һ����
	dc.LineTo(p2.x, p2.y);//����
	dc.SelectObject(oldpen);
}

//CMap<int, int, CStatic, CStatic&> myMap;

BOOL CFlowChart::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	pFlow = this;
	CStaticArray();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}
void CFlowChart::CStaticArray()//����ָ������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnOK();
}


void CFlowChart::OnBnClickedOk2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}




void CFlowChart::OnPaint()//---------------------------------------------------------------------1������������ͼ����ں���
{
	CPaintDC dc(this); // device context for painting
					   // TODO: �ڴ˴������Ϣ����������

	int workNum[MAX_CAM];//�������̸���
	CString filePath[MAX_CAM];//�����ļ�·��
	CString name[MAX_CAM];//��������
	CStdioFile file[MAX_CAM];//�����ĵ�
	int m_commNum[MAX_CAM];
	CString str;
	BOOL ret[MAX_CAM];
	CString path;
	GetModuleFileName(NULL, path.GetBufferSetLength(MAX_PATH + 1), MAX_PATH);//��ȡĬ��exe·��
	path.ReleaseBuffer();
	int pos = path.ReverseFind('\\');
	path = path.Left(pos);//ȥ��·���е�exe
	path = path + _T("\\");
	
	name[0] = pMainDlg->m_initTXT1;
	name[1] = pMainDlg->m_initTXT2;
	for (int i = 0; i < MAX_CAM; i++)
	{
		workNum[i] = i;
		str.Format(_T("%d"), i + 1);
		filePath[i] = path + name[i];//����·��
		//LPCTSTR pszFileName[i] = filePath[i].GetBufferSetLength(filePath[i].GetLength());��CStringת����LPCTSTR
		ret[i] = file[i].Open(filePath[i].GetBufferSetLength(filePath[i].GetLength()), CFile::modeRead);//���ļ�
	}
	UpdateData(FALSE);
	if (ret[0] == 1&&ret[1]==1)
	{
		BeginTransformation(file,m_commNum,workNum);//---------------------------------------------1.1��ʼ��������
		//BeginTransformation(file[1],m_commNum[1],workNum[1]);//��ʼת��
	}
	else
	{
		AfxMessageBox(_T("������ѡ�ű��ļ��Ƿ���Ĭ��·��"));
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
void CFlowChart::BeginTransformation(CStdioFile file[], int m_commNum[], int workNum[])//-----------------1.1��ʼ��������
{
	CString str;
	
	for (int i = 0; i < MAX_CAM; i++)//
	{
		m_commNum[i] = pMainDlg->findCoronNum(&file[i]);//ð�Ÿ�������ָ�������
	}
	
	if (m_commNum[0] == 0&& m_commNum[1] == 0)//�����߳̾���ָ���ٱ���
		{
			AfxMessageBox(_T("�ű������κ�ָ�"));
		}
	else
	{
		CommandTransformation(file, m_commNum, workNum);//------------------------------------------------1.1.1���ߺ���
	}
	
}

CString CFlowChart::flowchart(CStdioFile&file, int IDTXT, int m_m, int workNum)//��������������ѡ����ʾ��ͼ���txt
{
	CString m_fileComm;//�洢��������
	int commandnum;
	CString MiddleComm;
	if(workNum==1)
	{ 
		m_m = m_m + 1000;
	}
	//CStatic &m_mm=m_flowIcon1001;
	//if ()//myMap.Lookup(m_m, m_mm))//�ҵ���Ϊ1���Ҳ�������null��ֵ����m_mm��
//	{m_m[1] = &m_flowIcon1001;
	if (feof(file.m_pStream)==FALSE)//feof����ĵ��Ƿ�ĩβ��ѭ����ȡָ��
	{
			
			m_fileComm = pMainDlg->findCoron(&file);//return str����ð�ź���ǰ����ַ����ݣ���ָ�����ƣ�����ð�ţ���//������˽�β����null��
			if (m_fileComm == _T("\r\nCommon:") || m_fileComm == _T("\r\nInquiry:"))//--------------------------------��ָͨ��1
			{
				CString comm;
				comm = pMainDlg->ChineseTransformation(MiddleComm, &file);
				if (comm == _T("\r\nIO"))
				{
					SetDlgItemText(IDTXT, _T("IO"));//��ֵλ����ż��ɶ��������ؼ���ID��źͱ���
					LoadFlowchart(30006, m[m_m]);//��ֵλ�����
					commandnum++;
				}
				else if (comm == _T("\r\nAxisMove"))
				{
					SetDlgItemText(IDTXT, _T("M"));//��ֵλ����ż��ɶ��������ؼ���ID��źͱ���
					LoadFlowchart(30009, m[m_m]);//��ֵλ�����
					commandnum++;
				}
				else if (comm == _T("\r\nAxisSetTargetSpeed"))
				{
					SetDlgItemText(IDTXT, _T("SS"));//��ֵλ����ż��ɶ��������ؼ���ID��źͱ���
					LoadFlowchart(30015, m[m_m]);//��ֵλ�����
					commandnum++;
				}
				else if (comm == _T("\r\nAxisSetHomePosition"))
				{
					SetDlgItemText(IDTXT, _T("SH"));//��ֵλ����ż��ɶ��������ؼ���ID��źͱ���
					LoadFlowchart(30014, m[m_m]);//��ֵλ�����
					commandnum++;
				}
				else if (comm == _T("\r\nAxisGoHomePosition"))
				{
					SetDlgItemText(IDTXT, _T("H"));//��ֵλ����ż��ɶ��������ؼ���ID��źͱ���
					LoadFlowchart(30012, m[m_m]);//��ֵλ�����
					commandnum++;
				}
				else if (comm == _T("\r\nAxisGoPositiveLimit"))
				{
					SetDlgItemText(IDTXT, _T("PL"));//��ֵλ����ż��ɶ��������ؼ���ID��źͱ���
					LoadFlowchart(30011, m[m_m]);//��ֵλ�����
					commandnum++;
				}
				else if (comm == _T("\r\nAxisGoNegativeLimit"))
				{
					SetDlgItemText(IDTXT, _T("NL"));//��ֵλ����ż��ɶ��������ؼ���ID��źͱ���
					LoadFlowchart(30010, m[m_m]);//��ֵλ�����
					commandnum++;
				}
				else if (comm == _T("\r\nAxisSMVR"))
				{
					SetDlgItemText(IDTXT, _T("S"));//��ֵλ����ż��ɶ��������ؼ���ID��źͱ���
					LoadFlowchart(30013, m[m_m]);//��ֵλ�����
					commandnum++;
				}
				else if (comm == _T("\r\nAxisSMVR"))
				{
					SetDlgItemText(IDTXT, _T("S"));//��ֵλ����ż��ɶ��������ؼ���ID��źͱ���
					LoadFlowchart(30013, m[m_m]);//��ֵλ�����
					commandnum++;
				}
				else if (comm == _T("\r\nLimit?"))
				{
					SetDlgItemText(IDTXT, _T("L?"));//��ֵλ����ż��ɶ��������ؼ���ID��źͱ���
					LoadFlowchart(30017, m[m_m]);//��ֵλ�����
					commandnum++;
				}
				else if (comm == _T("\r\nRelativePosition?"))
				{
					SetDlgItemText(IDTXT, _T("RP?"));//��ֵλ����ż��ɶ��������ؼ���ID��źͱ���
					LoadFlowchart(30018, m[m_m]);//��ֵλ�����
					commandnum++;
				}
				else if (comm == _T("\r\nAbsolutePosition?"))
				{
					SetDlgItemText(IDTXT, _T("AP?"));//��ֵλ����ż��ɶ��������ؼ���ID��źͱ���
					LoadFlowchart(30016, m[m_m]);//��ֵλ�����
					commandnum++;
				}
				else if (comm == _T("\r\nIO?"))
				{
					SetDlgItemText(IDTXT, _T("AP?"));//��ֵλ����ż��ɶ��������ؼ���ID��źͱ���
					LoadFlowchart(30006, m[m_m]);//��ֵλ�����
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
					SetDlgItemText(IDTXT, _T("J"));//��ֵλ����ż��ɶ��������ؼ���ID��źͱ���
					LoadFlowchart(30004, m[m_m]);//��ֵλ�����
					commandnum++;
					return comm[1];
				}
				else if (comm[1] == _T("\r\nRoute=MoveL"))
				{
					SetDlgItemText(IDTXT, _T("L"));//��ֵλ����ż��ɶ��������ؼ���ID��źͱ���
					LoadFlowchart(30004, m[m_m]);//��ֵλ�����
					commandnum++;
					return comm[1];
				}
				else if (comm[1] == _T("\r\nRobotAbsolutePosition?"))
				{
					SetDlgItemText(IDTXT, _T("P?"));//��ֵλ����ż��ɶ��������ؼ���ID��źͱ���
					LoadFlowchart(30004, m[m_m]);//��ֵλ�����
					commandnum++;
					return comm[0];
				}
				else if (comm[1] == _T("\r\nRobotStatus?"))
				{
					SetDlgItemText(IDTXT, _T("S?"));//��ֵλ����ż��ɶ��������ؼ���ID��źͱ���
					LoadFlowchart(30004, m[m_m]);//��ֵλ�����
					commandnum++;
					return comm[0];
				}
			}
			else if (m_fileComm == _T("\r\nDelayTime:"))
			{
				SetDlgItemText(IDTXT, _T("Time"));//��ֵλ����ż��ɶ��������ؼ���ID��źͱ���
				LoadFlowchart(30003, m[m_m]);//��ֵλ�����
				commandnum++;
				return m_fileComm;
			}
			else if (m_fileComm == _T("\r\nThreadInteraction:"))//---------------�߳̽�������5
			{
				CString comm;
				comm = pMainDlg->ChineseTransformation(MiddleComm, &file);
				if (comm == _T("\r\nWaitUntil"))
				{
					SetDlgItemText(IDTXT, _T("Wait"));//��ֵλ����ż��ɶ��������ؼ���ID��źͱ���
					LoadFlowchart(30007, m[m_m]);//��ֵλ�����
					commandnum++;
				}
				else if (comm == _T("\r\nOrderContinue"))
				{
					SetDlgItemText(IDTXT, _T("Order"));//��ֵλ����ż��ɶ��������ؼ���ID��źͱ���
					LoadFlowchart(30008, m[m_m]);//��ֵλ�����
					commandnum++;
				}
				return comm;
			}
			else if (m_fileComm == _T("\r\nImageProcessing:"))
			{
				SetDlgItemText(IDTXT, _T("IP"));//��ֵλ����ż��ɶ��������ؼ���ID��źͱ���
				LoadFlowchart(30019, m[m_m]);//��ֵλ�����
				commandnum++;
				return m_fileComm;
			}
			else if (m_fileComm == _T("\r\nLightAdjusting:"))
			{
				SetDlgItemText(IDTXT, _T("L"));//��ֵλ����ż��ɶ��������ؼ���ID��źͱ���
				LoadFlowchart(30005, m[m_m]);//��ֵλ�����
				commandnum++;
				return m_fileComm;
			}
			else if (m_fileComm == _T("\r\nAdjustingWithResult:"))
			{
				SetDlgItemText(IDTXT, _T("AWR"));//��ֵλ����ż��ɶ��������ؼ���ID��źͱ���
				LoadFlowchart(30019, m[m_m]);//��ֵλ�����
				commandnum++;
				return m_fileComm;
			}
			return L"";//����������ؿ��ַ�
	}
	if (feof(file.m_pStream) == TRUE)//��ĩβ��
	{
		return L"TheEnd";
	}

//	else
//	{
//		AfxMessageBox(_T("CMap���޶�Ӧ����ֵ��"));
	//}
}

void CFlowChart::DrawCommonFlow(CPoint p1, CPoint p2, int IDTXT, int IDPicture, CString str, CStatic*m_m)//��ͨ������ ����
{
	SetDlgItemText(IDTXT, str);
	LoadFlowchart(IDPicture, m_m);
}
void CFlowChart::DrawTurnFlow(CPoint p1, CPoint p2, CPoint p3, CPoint p4, int IDTXT, int IDPicture, CString str, CStatic *m_m)//���䴦���� ����
{
	//DrawCommonLine(p1, p2);//����ֱ��
	//DrawCommonLine(p2, p3);//����ֱ��
	//DrawCommonFlow(p3, p4, IDTXT, IDPicture, str, m_m);//��ͨ������ ����
}

CString* CFlowChart::DrawRowFlow(CStdioFile file[],int row, int workNum[], CString str[])//��Ҫ������ż���� ��һ�� һ��������һ�����ҵ���
{
	int num[2] = {22*(row-1),22*(row-1) };//��ʼ��ÿһ�����¿�ʼ�����
	int IDTXT[2] = {10000+num[0] ,20000+num[1]};
	while (1)
	{
		if (row % 2 == 1)//������ �����һ�����ͷλ�õ���
		{
			if (str[0] == L"TheEnd"&&str[1] == L"TheEnd")
			{
				DrawLine(CPoint((num[0] - (row - 1) * 22) * 50, 75 + 160 * (row - 1)), CPoint((num[0] - (row - 1) * 22) * 50, 55 + 160 * (row - 1)));//���ƴ���ͷֱ�ߺ�����λһ
				SetDlgItemText(IDTXT[0], _T("CloseTXT"));//��ֵλ����ż��ɶ��������ؼ���ID��źͱ���
				LoadFlowchart(30002, m[num[0]]);//close
				DrawLine(CPoint((num[1] - (row - 1) * 22) * 50, 85 + 160 * (row - 1)), CPoint((num[1] - (row - 1) * 22) * 50, 105 + 160 * (row - 1)));//���ƴ���ͷֱ�ߺ�����λ��
				SetDlgItemText(IDTXT[1], _T("CloseTXT"));//��ֵλ����ż��ɶ��������ؼ���ID��źͱ���
				int s = num[1] + 1000;
				LoadFlowchart(30002, m[s]);//close
				return str;
				break;
			}
			if (max == row * 22)
			{
				return str;//return�˾Ͳ�����ִ����
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
					DrawLine(CPoint((num[1] - (row - 1) * 22) * 50, 85 + 160 * (row - 1)), CPoint((num[1] - (row - 1) * 22) * 50, 105 + 160 * (row - 1)));//���ƴ���ͷֱ�ߺ�����λ��
					str[1] = flowchart(file[1], IDTXT[1], num[1], workNum[1]);
					max = num[1];
				}
				else if (str[1] == L"TheEnd")
				{
					num[0]++;
					IDTXT[0]++;
					DrawLine(CPoint((num[0] - (row - 1) * 22) * 50, 75 + 160 * (row - 1)), CPoint((num[0] - (row - 1) * 22) * 50, 55 + 160 * (row - 1)));//���ƴ���ͷֱ�ߺ�����λһ
					str[0] = flowchart(file[0], IDTXT[0], num[0], workNum[0]);
					num[1]++;
					IDTXT[1]++;
					max = num[1];

				}
				else if (str[0] != L"TheEnd"&&str[1] != L"TheEnd")
				{

					if (str[0] != L"WaitUntil"&&str[1] != L"OrderContinue")//��������
					{
						num[0]++;
						IDTXT[0]++;
						DrawLine(CPoint((num[0] - (row - 1) * 22) * 50, 75 + 160 * (row - 1)), CPoint((num[0] - (row - 1) * 22) * 50, 55 + 160 * (row - 1)));//���ƴ���ͷֱ�ߺ�����λһ
						str[0] = flowchart(file[0], IDTXT[0], num[0], workNum[0]);

						if (str[1] != L"WaitUntil" || str[0] == L"OrderContinue")//�������С�
						{
							num[1]++;
							IDTXT[1]++;
							DrawLine(CPoint((num[1] - (row - 1) * 22) * 50, 85 + 160 * (row - 1)), CPoint((num[1] - (row - 1) * 22) * 50, 105 + 160 * (row - 1)));//���ƴ���ͷֱ�ߺ�����λ��
							str[1] = flowchart(file[1], IDTXT[1], num[1], workNum[1]);
						}
						else//δ�񼤻�ĵȴ�
						{
							num[1]++;
							IDTXT[1]++;
						}
						max = num[1];
					}
					else if (str[0] == L"WaitUntil"&&str[1] != L"OrderContinue")//�ȴ�
					{
						num[0]++;
						IDTXT[0]++;//�ÿ�

						num[1]++;//�߳�2��������
						IDTXT[1]++;
						DrawLine(CPoint((num[1] - (row - 1) * 22) * 50, 85 + 160 * (row - 1)), CPoint((num[1] - (row - 1) * 22) * 50, 105 + 160 * (row - 1)));//���ƴ���ͷֱ�ߺ����߳�2
						str[1] = flowchart(file[1], IDTXT[1], num[1], workNum[1]);
						max = num[1];
					}
					else if (str[0] == L"WaitUntil"&&str[1] == L"OrderContinue")//�ȴ������л�ü���
					{
						num[0]++;
						IDTXT[0]++;
						DrawLine(CPoint((num[0] - (row - 1) * 22) * 50, 75 + 160 * (row - 1)), CPoint((num[0] - (row - 1) * 22) * 50, 55 + 160 * (row - 1)));//���ƴ���ͷֱ�ߺ�����λһ
						str[0] = flowchart(file[0], IDTXT[0], num[0], workNum[0]);

						num[1]++;//�߳�2��������
						IDTXT[1]++;
						DrawLine(CPoint((num[1] - (row - 1) * 22) * 50, 85 + 160 * (row - 1)), CPoint((num[1] - (row - 1) * 22) * 50, 105 + 160 * (row - 1)));//���ƴ���ͷֱ�ߺ����߳�2
						str[1] = flowchart(file[1], IDTXT[1], num[1], workNum[1]);
						max = num[1];
					}
					continue;
				}
			}
			max = num[1];//һ��һ�黭������������߳�2�ı��
		}
		else if (row % 2 == 0)//ż���У��������󻭣���ͷ��λ�õݼ�
		{
			if (str[0] == L"TheEnd"&&str[1] == L"TheEnd")
			{
				DrawLine(CPoint(1150-(num[0] - (row - 1) * 22) * 50, 75 + 160 * (row - 1)), CPoint(1150 - (num[0] - (row - 1) * 22) * 50, 55 + 160 * (row - 1)));//���ƴ���ͷֱ�ߺ�����λһ
				SetDlgItemText(IDTXT[0], _T("CloseTXT"));//��ֵλ����ż��ɶ��������ؼ���ID��źͱ���
				LoadFlowchart(30002, m[num[0]]);//close
				DrawLine(CPoint(1150 - (num[1] - (row - 1) * 22) * 50, 85 + 160 * (row - 1)), CPoint(1150 - (num[1] - (row - 1) * 22) * 50, 105 + 160 * (row - 1)));//���ƴ���ͷֱ�ߺ�����λ��
				SetDlgItemText(IDTXT[1], _T("CloseTXT"));//��ֵλ����ż��ɶ��������ؼ���ID��źͱ���
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
					DrawLine(CPoint(1150 - (num[1] - (row - 1) * 22) * 50, 85 + 160 * (row - 1)), CPoint(1150 - (num[1] - (row - 1) * 22) * 50, 105 + 160 * (row - 1)));//���ƴ���ͷֱ�ߺ�����λ��
					str[1] = flowchart(file[1], IDTXT[1], num[1], workNum[1]);
					max = num[1];
				}
				else if (str[1] == L"TheEnd")
				{
					num[0]++;
					IDTXT[0]++;
					DrawLine(CPoint(1150 - (num[0] - (row - 1) * 22) * 50, 75 + 160 * (row - 1)), CPoint(1150 - (num[0] - (row - 1) * 22) * 50, 55 + 160 * (row - 1)));//���ƴ���ͷֱ�ߺ�����λһ
					str[0] = flowchart(file[0], IDTXT[0], num[0], workNum[0]);
					num[1]++;
					IDTXT[1]++;
					max = num[1];
				}
				else if (str[0] != L"TheEnd"&&str[1] != L"TheEnd")
				{

					if (str[0] != L"WaitUntil"&&str[1] != L"OrderContinue")//��������
					{
						num[0]++;
						IDTXT[0]++;
						DrawLine(CPoint(1150 - (num[0] - (row - 1) * 22) * 50, 75 + 160 * (row - 1)), CPoint(1150 - (num[0] - (row - 1) * 22) * 50, 55 + 160 * (row - 1)));//���ƴ���ͷֱ�ߺ�����λһ
						str[0] = flowchart(file[0], IDTXT[0], num[0], workNum[0]);

						if (str[1] != L"WaitUntil" || str[0] == L"OrderContinue")//�������С�
						{
							num[1]++;
							IDTXT[1]++;
							DrawLine(CPoint(1150 - (num[1] - (row - 1) * 22) * 50, 85 + 160 * (row - 1)), CPoint(1150 - (num[1] - (row - 1) * 22) * 50, 105 + 160 * (row - 1)));//���ƴ���ͷֱ�ߺ�����λ��
							str[1] = flowchart(file[1], IDTXT[1], num[1], workNum[1]);
							max = num[1];
						}
						else//δ�񼤻�ĵȴ�
						{
							num[1]++;
							IDTXT[1]++;
							max = num[1];
						}

					}
					else if (str[0] == L"WaitUntil"&&str[1] != L"OrderContinue")//�ȴ�
					{
						num[0]++;
						IDTXT[0]++;//�ÿ�

						num[1]++;//�߳�2��������
						IDTXT[1]++;
						DrawLine(CPoint(1150 - (num[1] - (row - 1) * 22) * 50, 85 + 160 * (row - 1)), CPoint(1150 - (num[1] - (row - 1) * 22) * 50, 105 + 160 * (row - 1)));//���ƴ���ͷֱ�ߺ����߳�2
						str[1] = flowchart(file[1], IDTXT[1], num[1], workNum[1]);
						max = num[1];
					}
					else if (str[0] == L"WaitUntil"&&str[1] == L"OrderContinue")//�ȴ������л�ü���
					{
						num[0]++;
						IDTXT[0]++;
						DrawLine(CPoint(1150 - (num[0] - (row - 1) * 22) * 50, 75 + 160 * (row - 1)), CPoint(1150 - (num[0] - (row - 1) * 22) * 50, 55 + 160 * (row - 1)));//���ƴ���ͷֱ�ߺ�����λһ
						str[0] = flowchart(file[0], IDTXT[0], num[0], workNum[0]);

						num[1]++;//�߳�2��������
						IDTXT[1]++;
						DrawLine(CPoint(1150 - (num[1] - (row - 1) * 22) * 50, 85 + 160 * (row - 1)), CPoint(1150 - (num[1] - (row - 1) * 22) * 50, 105 + 160 * (row - 1)));//���ƴ���ͷֱ�ߺ����߳�2
						str[1] = flowchart(file[1], IDTXT[1], num[1], workNum[1]);
						max = num[1];
					}
					continue;
				}
			}
			max = num[1];//һ��һ�黭������������߳�2�ı��
		}
	}
}

void CFlowChart::CommandTransformation(CStdioFile file[], int m_commNum[], int workNum[])//-----------------------1.1.1���ߺ���
{
	CString str[2] = { L"",L"" };//��ʼ�����ص��ַ���
	max =0;// m_commNum[0] > m_commNum[1] ? m_commNum[0] : m_commNum[1];//����
	int row =1;//��¼�ź�
	LoadFlowchart(IDB_BITMAP_Start, &m_startflow);//��ʼͼ��

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
	while (1)//����ѭ
	{
		if (max == 0)//����һ�ŵļ�ͷ��ͼ����������
		{
			CString *p = DrawRowFlow(file, 1, workNum, str);
			str[0] = *p[0];
			str[1] = *p[1];
		}
		else if (max == 22)//����2�ŵļ�ͷ��ͼ��
		{
			row++;
			CString *p = DrawRowFlow(file, 2, workNum, str);//���ݳ���str
			str[0] = *p[0];
			str[1] = *p[1];
		}
		else if (max == 44)//����3�ŵļ�ͷ��ͼ��
		{
			row++;
			CString *p = DrawRowFlow(file, 3,workNum, str);
			str[0] = *p[0];
			str[1] = *p[1];
		}
		else if (max == 66)//����4�ŵļ�ͷ��ͼ��
		{
			row++;
			CString *p = DrawRowFlow(file, 4, workNum, str);
			str[0] = *p[0];
			str[1] = *p[1];
		}

		else if (max == 88)//����5�ŵļ�ͷ��ͼ��
		{
			row++;
			CString *p = DrawRowFlow(file, 5, workNum, str);
			str[0] = *p[0];
			str[1] = *p[1];
		}
		else if (max == 110)//����6�ŵļ�ͷ��ͼ��
		{
			row++;
			CString *p = DrawRowFlow(file, 6, workNum, str);
			str[0] = *p[0];
			str[1] = *p[1];

		}
		else if (max == 132) // ����7�ŵļ�ͷ��ͼ��
		{
			row++;
			CString *p = DrawRowFlow(file, 7,  workNum, str);
			str[0] = *p[0];
			str[1] = *p[1];
		}
		else if (max == 154)//����8�ŵļ�ͷ��ͼ��
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
	// TODO:  �ڴ˸��� DC ���κ�����
	for (i = 10001; i <= 10044; i++)
	{
		if (pWnd->GetDlgCtrlID() == i)//GetDlgCtrlID()�����ǻ�ȡָ���ؼ���ID��
		{
			pDC->SetTextColor(RGB(50, 50, 50));//���þ�̬�ı���������ɫ
			pDC->SetBkMode(TRANSPARENT);//����Ϊ͸��
			return HBRUSH(GetStockObject(HOLLOW_BRUSH));//����͸����仰���ܵ�
		}// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	}

	for (i = 20001; i <= 20044; i++)
	{
		if (pWnd->GetDlgCtrlID() == i)//GetDlgCtrlID()�����ǻ�ȡָ���ؼ���ID��

		{
			pDC->SetTextColor(RGB(50, 50, 50));//���þ�̬�ı���������ɫ
			pDC->SetBkMode(TRANSPARENT);//����Ϊ͸��
			return HBRUSH(GetStockObject(HOLLOW_BRUSH));//����͸����仰���ܵ�
		}
		// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	}
	return hbr;
}

#pragma once
#include "afxwin.h"
#include <afxtempl.h>


// CFlowChart 对话框

class CFlowChart : public CDialogEx
{
	DECLARE_DYNAMIC(CFlowChart)
	
public:
	CFlowChart(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CFlowChart();
	void LoadFlowchart(UINT ID, CStatic*m_mm);
	void DrawLine(CPoint p1, CPoint p2);
	int workNum;
	void DrawCommonLine(CPoint p1, CPoint p2);
	CString flowchart(CStdioFile&file, int IDTXT, int m_m, int workNum);
	void DrawCommonFlow(CPoint p1, CPoint p2, int IDTXT, int IDPicture, CString str, CStatic *m_m);
	void DrawTurnFlow(CPoint p1, CPoint p2, CPoint p3, CPoint p4, int IDTXT, int IDPicture, CString str, CStatic *m_m);
	void BeginTransformation(CStdioFile file[], int m_commNum[], int workNum[]);
	void CommandTransformation(CStdioFile file[], int m_commNum[], int workNum[]);
	CStatic m_startflow;
	CString* DrawRowFlow(CStdioFile file[], int row, int workNum[], CString str[]);
	void CStaticArray();
	int max;//流程图的最大位置序号
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_FlowChart };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedOk2();
	afx_msg void OnPaint();
	CStatic m_flowIcon1001;
	CStatic m_flowIcon2001;
	CStatic m_flowIcon1002;
	CStatic m_flowIcon2002;
	CStatic m_flowIcon1003;
	CStatic m_flowIcon2003;
	CStatic m_flowIcon1004;
	CStatic m_flowIcon2004;
	CStatic m_flowIcon1005;
	CStatic m_flowIcon2005;
	CStatic m_flowIcon1006;
	CStatic m_flowIcon2006;
	CStatic m_flowIcon1007;
	CStatic m_flowIcon2007;
	CStatic m_flowIcon1008;
	CStatic m_flowIcon2008;
	CStatic m_flowIcon1009;
	CStatic m_flowIcon2009;
	CStatic m_flowIcon1010;
	CStatic m_flowIcon2010;
	CStatic m_flowIcon1011;
	CStatic m_flowIcon2011;
	CStatic m_flowIcon2012;
	CStatic m_flowIcon2013;
	CStatic m_flowIcon2014;
	CStatic m_flowIcon2015;
	CStatic m_flowIcon2016;
	CStatic m_flowIcon2017;
	CStatic m_flowIcon2018;
	CStatic m_flowIcon2019;
	CStatic m_flowIcon2020;
	CStatic m_flowIcon2021;
	CStatic m_flowIcon2022;
	CStatic m_flowIcon1022;
	CStatic m_flowIcon1021;
	CStatic m_flowIcon1020;
	CStatic m_flowIcon1019;
	CStatic m_flowIcon1018;
	CStatic m_flowIcon1017;
	CStatic m_flowIcon1016;
	CStatic m_flowIcon1015;
	CStatic m_flowIcon1014;
	CStatic m_flowIcon1013;
	CStatic m_flowIcon1012;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CStatic *m[2000];
	int commandnum;
	afx_msg void OnStnClickedStatic2011();
	afx_msg void OnStnClickedStatic1020();
	afx_msg void OnStnClickedStatic1022();
//	CStatic m_flowIcon1023;
//	CStatic m_flowIcon1024;
//	CStatic m_flowIcon1025;
//	CStatic m_flowIcon1026;
//	CStatic m_flowIcon1027;
//	CStatic m_flowIcon1028;
//	CStatic m_flowIcon1029;
//	CStatic m_flowIcon1030;
//	CStatic m_flowIcon1031;
//	CStatic m_flowIcon1032;
//	CStatic m_flowIcon1033;
//	CStatic m_flowIcon1034;
//	CStatic m_flowIcon1035;
//	CStatic m_flowIcon1036;
//	CStatic m_flowIcon1037;
//	CStatic m_flowIcon1038;
//	CStatic m_flowIcon1039;
//	CStatic m_flowIcon1040;
//	CStatic m_flowIcon1041;
//	CStatic m_flowIcon1042;
//	CStatic m_flowIcon1043;
//	CStatic m_flowIcon1044;
//	CStatic m_flowIcon2023;
//	CStatic m_flowIcon2024;
//	CStatic m_flowIcon2025;
//	CStatic m_flowIcon2026;
//	CStatic m_flowIcon2027;
//	CStatic m_flowIcon2028;
//	CStatic m_flowIcon2029;
//	CStatic m_flowIcon2030;
//	CStatic m_flowIcon2031;
//	CStatic m_flowIcon2032;
//	CStatic m_flowIcon2033;
//	CStatic m_flowIcon2034;
//	CStatic m_flowIcon2035;
//	CStatic m_flowIcon2036;
//	CStatic m_flowIcon2037;
//	CStatic m_flowIcon2038;
//	CStatic m_flowIcon2039;
//	CStatic m_flowIcon2040;
//	CStatic m_flowIcon2041;
//	CStatic m_flowIcon2042;
//	CStatic m_flowIcon2043;
//	CStatic m_flowIcon2044;
	CStatic m_flowIcon1023;
	CStatic m_flowIcon1024;
	CStatic m_flowIcon1025;
	CStatic m_flowIcon1026;
	CStatic m_flowIcon1027;
	CStatic m_flowIcon1028;
	CStatic m_flowIcon1029;
	CStatic m_flowIcon1030;
	CStatic m_flowIcon1031;
	CStatic m_flowIcon1032;
	CStatic m_flowIcon1033;
	CStatic m_flowIcon1034;
	CStatic m_flowIcon1035;
	CStatic m_flowIcon1036;
	CStatic m_flowIcon1037;
	CStatic m_flowIcon1038;
	CStatic m_flowIcon1039;
	CStatic m_flowIcon1040;
	CStatic m_flowIcon1041;
	CStatic m_flowIcon1042;
	CStatic m_flowIcon1043;
	CStatic m_flowIcon1044;
	CStatic m_flowIcon2023;
	CStatic m_flowIcon2024;
	CStatic m_flowIcon2025;
	CStatic m_flowIcon2026;
	CStatic m_flowIcon2027;
	CStatic m_flowIcon2028;
	CStatic m_flowIcon2029;
	CStatic m_flowIcon2030;
	CStatic m_flowIcon2031;
	CStatic m_flowIcon2032;
	CStatic m_flowIcon2033;
	CStatic m_flowIcon2034;
	CStatic m_flowIcon2035;
	CStatic m_flowIcon2036;
	CStatic m_flowIcon2037;
	CStatic m_flowIcon2038;
	CStatic m_flowIcon2039;
	CStatic m_flowIcon2040;
	CStatic m_flowIcon2041;
	CStatic m_flowIcon2042;
	CStatic m_flowIcon2043;
	CStatic m_flowIcon2044;
};

#pragma once
#include"IO.h"

// CIOControl 对话框

class CIOControl : public CDialogEx
{
	DECLARE_DYNAMIC(CIOControl)

public:
	CIOControl(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CIOControl();

	CIO* io_d;
	bool m_IOConnectc;//IO连接状态
//#define m_IOConnect m_IOConnectc;
	//int m_localPort;
	int m_IOPortc;

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_IOControl };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton9();
	afx_msg void OnBnClickedButton10();
	afx_msg void OnBnClickedButton11();
	afx_msg void OnBnClickedButton12();
	afx_msg void OnBnClickedButton13();
	afx_msg void OnBnClickedButton14();
	afx_msg void OnBnClickedButton15();
	afx_msg void OnBnClickedButton16();
	afx_msg void OnBnClickedButton17();
	afx_msg void OnBnClickedButton18();
	afx_msg void OnBnClickedButton19();
	afx_msg void OnBnClickedButton20();
	afx_msg void OnBnClickedButton21();
	afx_msg void OnBnClickedButton22();
	afx_msg void OnBnClickedButton23();
	afx_msg void OnBnClickedButton24();
	afx_msg void OnBnClickedButton25();
	afx_msg void OnBnClickedButton26();
	afx_msg void OnBnClickedButton27();
	afx_msg void OnBnClickedButton28();
	afx_msg void OnBnClickedButton29();
	afx_msg void OnBnClickedButton30();
	afx_msg void OnBnClickedButton31();
	afx_msg void OnBnClickedButton32();
	afx_msg void OnBnClickedButton33();
	afx_msg void OnBnClickedButton34();
	afx_msg void OnBnClickedButton35();


	int boolArrayToInt(bool boolArray[], int arraySize);
	int sal();

	CEdit m_826;
	CEdit m_thd2;
	//CEdit m_showIO_up;
	///CEdit m_showIO_down;
//	CEdit m_IOvalue_up;
	CEdit m_IOvalue_up;
	CEdit m_IOvalue_down;
	CEdit m_OUPval;
	CIPAddressCtrl m_IOControlIP;
	CIPAddressCtrl m_AxisControlIP;
	CEdit m_axisnum;
	CEdit m_axisvalu;
	afx_msg void OnBnClickedButton36();
	CComboBox m_AxisNumCombo;
	afx_msg void OnBnClickedButton37();
	CIPAddressCtrl m_inquiryIP;
	CEdit m_inquiryvalu;
	CComboBox m_inquirycommand;
	CEdit m_inquiryresultvalu;
	CEdit m_Y;
	afx_msg void OnEnChangeEdit14();
	CEdit m_Z;
	CEdit m_A;
	CEdit m_B;
	CEdit m_C;
	CIPAddressCtrl m_localIPio;
};

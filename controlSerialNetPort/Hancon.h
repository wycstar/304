#pragma once
#include "afxwin.h"


// CHancon 对话框

class CHancon : public CDialogEx
{
	DECLARE_DYNAMIC(CHancon)

public:
	CHancon(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CHancon();

// 对话框数据
	enum { IDD = IDD_HANCON };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	//====================单轴控制按钮
	CButton m_check_axis1;
	CButton m_check_axis2;
	CButton m_check_axis3;
	CButton m_check_axis4;
	CButton m_check_negative;
	CButton m_check_positive;
	CButton *m_check_axis[7];
	int key[7];


	//====================空间运动控制按钮
	CButton m_check_forward;
	CButton m_check_left;
	CButton m_check_right;
	CButton m_check_up;
	CButton m_check_down;
	CButton m_check_backward;
	CButton *m_check_space[7];
	int Switch[7];
	bool key_temp[7];
	int  test[7];

	double Xpos;
	double Ypos;
	double Zpos;
	double Rpos;
	

};

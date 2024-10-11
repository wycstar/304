#pragma once
#include "afxwin.h"


// CHancon �Ի���

class CHancon : public CDialogEx
{
	DECLARE_DYNAMIC(CHancon)

public:
	CHancon(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CHancon();

// �Ի�������
	enum { IDD = IDD_HANCON };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	//====================������ư�ť
	CButton m_check_axis1;
	CButton m_check_axis2;
	CButton m_check_axis3;
	CButton m_check_axis4;
	CButton m_check_negative;
	CButton m_check_positive;
	CButton *m_check_axis[7];
	int key[7];


	//====================�ռ��˶����ư�ť
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

#pragma once
#include "afxcmn.h"


// CJoivel �Ի���

class CJoivel : public CDialogEx
{
	DECLARE_DYNAMIC(CJoivel)

public:
	CJoivel(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CJoivel();

// �Ի�������
	enum { IDD = IDD_JOIVEL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CSliderCtrl m_Jov_slider1;
	CSliderCtrl m_Jov_slider2;
	CSliderCtrl m_Jov_slider3;
	CSliderCtrl m_Jov_slider4;
	CSliderCtrl *m_Jov_slider[5];

	double m_Jov_edit1;
	double m_Jov_edit2;
	double m_Jov_edit3;
	double m_Jov_edit4;
	double *m_Jov_edit[5];
};

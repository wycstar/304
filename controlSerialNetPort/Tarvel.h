#pragma once
#include "afxcmn.h"


// CTarvel �Ի���

class CTarvel : public CDialogEx
{
	DECLARE_DYNAMIC(CTarvel)

public:
	CTarvel(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTarvel();

// �Ի�������
	enum { IDD = IDD_TARVEL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CSliderCtrl m_Tav_slider1;
	CSliderCtrl m_Tav_slider2;
	CSliderCtrl m_Tav_slider3;
	CSliderCtrl m_Tav_slider4;
	CSliderCtrl *m_Tav_slider[5];


	double m_Tav_edit1;
	double m_Tav_edit2;
	double m_Tav_edit3;
	double m_Tav_edit4;
	double *m_Tav_edit[5];

};

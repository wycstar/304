#pragma once
#include "afxcmn.h"


// CJoipos �Ի���

class CJoipos : public CDialogEx
{
	DECLARE_DYNAMIC(CJoipos)

public:
	CJoipos(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CJoipos();

// �Ի�������
	enum { IDD = IDD_JOIPOS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CSliderCtrl m_Jop_slider1;
	CSliderCtrl m_Jop_slider2;
	CSliderCtrl m_Jop_slider3;
	CSliderCtrl m_Jop_slider4;
	CSliderCtrl *m_Jop_slider[5];

	int m_Jop_edit1;
	int m_Jop_edit2;
	int m_Jop_edit3;
	int m_Jop_edit4;
	int *m_Jop_edit[5];
	afx_msg void OnNMCustomdrawSlider3(NMHDR *pNMHDR, LRESULT *pResult);
};

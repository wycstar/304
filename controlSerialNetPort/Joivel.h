#pragma once
#include "afxcmn.h"


// CJoivel 对话框

class CJoivel : public CDialogEx
{
	DECLARE_DYNAMIC(CJoivel)

public:
	CJoivel(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CJoivel();

// 对话框数据
	enum { IDD = IDD_JOIVEL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

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

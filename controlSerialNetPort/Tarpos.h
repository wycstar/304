#pragma once


// CTarpos 对话框

class CTarpos : public CDialogEx
{
	DECLARE_DYNAMIC(CTarpos)

public:
	CTarpos(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTarpos();

// 对话框数据
	enum { IDD = IDD_TARPOS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	double m_Tap_edit1;
	double m_Tap_edit2;
	double m_Tap_edit3;
	double m_Tap_edit4;
	double m_Tap_edit5;
	double *m_Tap_edit[5];

	//模式变量
	int Motionmode;
	double Targetmaxvelocity;
	afx_msg void OnBnClickedRadioMovej();
	afx_msg void OnBnClickedRadioMovel();
	afx_msg void OnBnClickedRadioMovec();
	
};

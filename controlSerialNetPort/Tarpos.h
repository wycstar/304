#pragma once


// CTarpos �Ի���

class CTarpos : public CDialogEx
{
	DECLARE_DYNAMIC(CTarpos)

public:
	CTarpos(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTarpos();

// �Ի�������
	enum { IDD = IDD_TARPOS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	double m_Tap_edit1;
	double m_Tap_edit2;
	double m_Tap_edit3;
	double m_Tap_edit4;
	double m_Tap_edit5;
	double *m_Tap_edit[5];

	//ģʽ����
	int Motionmode;
	double Targetmaxvelocity;
	afx_msg void OnBnClickedRadioMovej();
	afx_msg void OnBnClickedRadioMovel();
	afx_msg void OnBnClickedRadioMovec();
	
};

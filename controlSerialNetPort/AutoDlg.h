#pragma once


// CAutoDlg dialog

class CAutoDlg : public CDialog
{
	DECLARE_DYNAMIC(CAutoDlg)

public:
	CAutoDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CAutoDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG_AUTO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	/*int m_delayTime2;
	int m_steps4[6];
	int m_steps5_1;
	int m_steps5_2;
	int m_steps6;
	int m_delayTime7;
	int m_delayTime8;
	int m_steps9;
	int m_steps10_1;
	int m_steps10_2;
	int m_steps10_3;
	int m_delayTime10;
	int m_steps10_4;
	int m_steps10_6;
	int m_steps10_5;
	int m_steps11;
	int m_delayTime11;
	int m_dispense1;
	int m_dispense2;
	int m_dispenseA[6];
	double m_angelErrorX;
	double m_angelErrorY;
	double m_ratioA;
	double m_ratioX;
	double m_ratioY;*/
	virtual BOOL OnInitDialog();
	void setPara(int workNum);
	void setImagePara(int workNum);

	LRESULT OnSavePara(WPARAM WP, LPARAM LP);	
	LRESULT OnUpdateUIPara(WPARAM WP, LPARAM LP);	
	LRESULT OnLoadPara(WPARAM WP, LPARAM LP);	
//	afx_msg void OnDeltaposSpinRoix2(NMHDR *pNMHDR, LRESULT *pResult);

	/*int m_searchSpeedMode;
	int m_maxMatchNum;
	int m_matchNum;
	CString m_modelFilePath;
	int m_smoothness;
	int m_iterationNum;
	int m_modelDistance;
	int m_ROIx;
	int m_ROIy;
	int m_ROIw;
	int m_ROIh;
	CComboBox m_cmbRound;
	CComboBox m_cmbProcessNum;*/
	//afx_msg void OnBnClickedButtonModelpath();
	CString pathSwitch(CString strPath);
	//afx_msg void OnCbnSelchangeComboRound();
	int m_workNum;


//	afx_msg void OnEnChangeEditangleerror2();
	afx_msg void OnCbnSelchangeComboProcessnum();
//	afx_msg void OnEnChangeEditmicroadjust12();
};

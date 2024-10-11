#pragma once
//#include "SerialPort.h"
#include "afxwin.h"
#include "BtnST.h"

// CDlgSerial1 dialog


class CDlgSerial1 : public CDialog
{
	DECLARE_DYNAMIC(CDlgSerial1) 

public:
	CDlgSerial1(CWnd* pParent = NULL, int* port = NULL, int* axisNum = NULL);   // standard constructor
	virtual ~CDlgSerial1();

// Dialog Data
	enum { IDD = IDD_DIALOG_SERIAL1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	//{{AFX_MSG(CDlgSerial1) 
	//afx_msg LONG OnCommunication(WPARAM ch, LPARAM port);
	//{{AFX_MSG(CDlgSerial1) 

	//CSerialPort m_SerialPort;
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	int m_axisSum[2];
	int m_port;


	int m_startspeed;
	int m_targetspeed;
	//int m_stopspeed;
	int m_accelspeed;
	int m_steps;
	int m_startspeed2;
	int m_targetspeed2;
	//int m_stopspeed2;
	int m_accelspeed2;
	int m_steps2;
	CComboBox m_ctrlMode;
	CComboBox m_ctrlMode2;
	//afx_msg void OnBnClickedButtonmovesteps7();
	int m_absOrRel;
	int m_absOrRel2;
	afx_msg void OnBnClickedButtonstart();
	CComboBox m_cmbUnitX;
	CComboBox m_cmbUnitX2;
	afx_msg void OnCbnSelchangeCombounit();
	double m_unit;
	double m_unit2;
	void InitUI(void);
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	CButtonST m_bstplusLight;
	CButtonST m_bstzeroLight;
	CButtonST m_bstminusLight;
	CButtonST m_bstplusLight2;
	CButtonST m_bstzeroLight2;
	CButtonST m_bstminusLight2;
	CButtonST m_bstsave;
	CButtonST m_bstdefault;

	void start1(UINT_PTR nIDEvent);
	void loopComm(void);
	bool m_bLoop;
	CString m_sendData;
	int m_loopCommNum;
	void openLoopComm(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButtonstop();
	void closeLoopComm(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButtonpluslimit();
	afx_msg void OnBnClickedButtonzeroswitch();
	afx_msg void OnBnClickedButtonminuslimit();
	void settingComm(CString comm, int axisNum);
	afx_msg void OnBnClickedButtonabszero();
	afx_msg void OnBnClickedButtonfindzero();
	void makeJOG(int sign, int axisNum);
	void switchLight(int neg, int zero, int pos, int axisNum);
	void start2(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButtonstart2();
	afx_msg void OnBnClickedButtonstop2();
	afx_msg void OnBnClickedButtonpluslimit2();
	afx_msg void OnBnClickedButtonzeroswitch2();
	afx_msg void OnBnClickedButtonminuslimit2();
	afx_msg void OnBnClickedButtonabszero2();
	afx_msg void OnBnClickedButtonfindzero2();
	afx_msg void OnCbnSelchangeCombounit2();
	afx_msg void OnEnSetfocusEditstartspeed();
	afx_msg void OnEnSetfocusEdittargetspeed();
	afx_msg void OnEnSetfocusEditaccelspeed();
	afx_msg void OnEnSetfocusEditsteps();
	afx_msg void OnEnSetfocusEditstartspeed2();
	afx_msg void OnEnSetfocusEdittargetspeed2();
	afx_msg void OnEnSetfocusEditaccelspeed2();
	afx_msg void OnEnSetfocusEditsteps2();
	afx_msg void OnEnSetfocusEditunit();
	afx_msg void OnEnSetfocusEditunit2();
	afx_msg void OnBnClickedRadioabsposition();
	afx_msg void OnBnClickedRadiorelposition();
	afx_msg void OnBnClickedRadioabsposition2();
	afx_msg void OnBnClickedRadiorelposition2();
	afx_msg void OnBnClickedButtonsave();
	void setPara(void);
	afx_msg void OnBnClickedButtondefault();
};

#pragma once
#include "Public.h"
#include "controlSerialNetPort.h"
#include "BtnST.h"


// CDlgSerial4 dialog

class CDlgSerial4 : public CDialog
{
	DECLARE_DYNAMIC(CDlgSerial4)

public:
	CDlgSerial4(CWnd* pParent = NULL, int port = portNum1, int* axisNum = NULL, CString dlgName = _T(""));   // standard constructor
	virtual ~CDlgSerial4();

// Dialog Data
	enum { IDD = IDD_DIALOG_SERIAL4 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	int m_port;
	int m_axis[2];
	virtual BOOL OnInitDialog();

	virtual BOOL PreTranslateMessage(MSG* pMsg);
	int m_startspeed;
	int m_targetspeed;
	int m_accelspeed;
	int m_steps;
	int m_startspeed2;
	int m_targetspeed2;
	int m_accelspeed2;
	int m_steps2;
	CComboBox m_ctrlMode;
	CComboBox m_ctrlMode2;
	int m_absOrRel;
	int m_absOrRel2;
	CComboBox m_cmbUnitX;
	CComboBox m_cmbUnitX2;
	double m_unit;
	double m_unit2;
	void InitUI(void);

	CButtonST m_bstplusLight;
	CButtonST m_bstzeroLight;
	CButtonST m_bstminusLight;
	CButtonST m_bstplusLight2;
	CButtonST m_bstzeroLight2;
	CButtonST m_bstminusLight2;
	CButtonST m_bstsave;
	CButtonST m_bstdefault;



	afx_msg void OnBnClickedButtonstart();
	afx_msg void OnBnClickedButtonstop();
	afx_msg void OnBnClickedButtonpluslimit();
	afx_msg void OnBnClickedButtonzeroswitch();
	afx_msg void OnBnClickedButtonminuslimit();
	afx_msg void OnBnClickedButtonabszero();
	afx_msg void OnBnClickedButtonfindzero();
	afx_msg void OnCbnSelchangeCombounit();

	void settingComm(CString comm, int axisNum);
	void makeJOG(int sign, int axisNum);
	void switchLight(int neg, int zero, int pos, int axisNum);

	bool m_bLoop;
	CString m_sendData;
	int m_loopCommNum;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	void start(UINT_PTR nIDEvent, CComboBox* ctrlMode, int axisNum, int port);
	void loopComm(void);
	void openLoopComm(UINT_PTR nIDEvent);
	void closeLoopComm(UINT_PTR nIDEvent);

	afx_msg void OnBnClickedButtonstart2();
	afx_msg void OnBnClickedButtonstop2();
	afx_msg void OnBnClickedButtonpluslimit2();
	afx_msg void OnBnClickedButtonzeroswitch2();
	afx_msg void OnBnClickedButtonminuslimit2();
	afx_msg void OnBnClickedButtonabszero2();
	afx_msg void OnBnClickedButtonfindzero2();
	afx_msg void OnCbnSelchangeCombounit2();


	CString m_strDlgName;
	void setPara(void);

	afx_msg void OnBnClickedButtonsave4();
	afx_msg void OnBnClickedButtondefault4();
};

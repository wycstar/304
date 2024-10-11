#pragma once
#include "Public.h"
#include "BtnST.h"
#include "controlSerialNetPortDlg.h"


// CDlgSerial6 dialog

class CDlgSerial6 : public CDialog
{
	DECLARE_DYNAMIC(CDlgSerial6)

public:
	CDlgSerial6(CWnd* pParent = NULL, int* port = NULL, int* axisNum = NULL, CString dlgName = _T(""));   // standard constructor
	virtual ~CDlgSerial6();

// Dialog Data
	enum { IDD = IDD_DIALOG_SERIAL6 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	int m_port;
	int m_axis[4];
	virtual BOOL OnInitDialog();
	void InitUI(void);

	int m_startspeed;
	int m_targetspeed;
	int m_accelspeed;
	int m_steps;
	int m_startspeed2;
	int m_targetspeed2;
	int m_accelspeed2;
	int m_steps2;
	int m_startspeed3;
	int m_targetspeed3;
	int m_accelspeed3;
	int m_steps3;
	int m_startspeed4;
	int m_targetspeed4;
	int m_accelspeed4;
	int m_steps4;
	CComboBox m_ctrlMode;
	CComboBox m_ctrlMode2;
	CComboBox m_ctrlMode3;
	CComboBox m_ctrlMode4;

	CButtonST m_bstplusLight;
	CButtonST m_bstzeroLight;
	CButtonST m_bstminusLight;
	CButtonST m_bstplusLight2;
	CButtonST m_bstzeroLight2;
	CButtonST m_bstminusLight2;
	CButtonST m_bstplusLight3;
	CButtonST m_bstzeroLight3;
	CButtonST m_bstminusLight3;
	CButtonST m_bstplusLight4;
	CButtonST m_bstzeroLight4;
	CButtonST m_bstminusLight4;

	CButtonST m_bstsave;
	CButtonST m_bstdefault;


	int m_absOrRel;
	int m_absOrRel2;
	int m_absOrRel3;
	int m_absOrRel4;
	CComboBox m_cmbUnitX;
	CComboBox m_cmbUnitX2;
	CComboBox m_cmbUnitX3;
	CComboBox m_cmbUnitX4;
	double m_unit;
	double m_unit2;
	double m_unit3;
	double m_unit4;

	bool m_bLoop;
	CString m_sendData;
	int m_loopCommNum;

	afx_msg void OnTimer(UINT_PTR nIDEvent);
	void start(UINT_PTR nIDEvent, CComboBox* ctrlMode, int axisNum, int port);
	void loopComm(int* axis, int port);
	void openLoopComm(UINT_PTR nIDEvent);
	void closeLoopComm(UINT_PTR nIDEvent);

	void settingComm(CString comm, int axisNum,  int port);
	void makeJOG(int sign, int axisNum, int port);
	void switchLight(int neg, int zero, int pos, int axisNum);


	virtual BOOL PreTranslateMessage(MSG* pMsg);

	afx_msg void OnBnClickedButtonstart();
	afx_msg void OnBnClickedButtonstart2();
	afx_msg void OnBnClickedButtonstart3();
	afx_msg void OnBnClickedButtonstart4();
	afx_msg void OnBnClickedButtonstop();
	afx_msg void OnBnClickedButtonstop2();
	afx_msg void OnBnClickedButtonstop3();
	afx_msg void OnBnClickedButtonstop4();
	afx_msg void OnBnClickedButtonpluslimit3();
	afx_msg void OnBnClickedButtonpluslimit4();
	afx_msg void OnBnClickedButtonpluslimit();
	afx_msg void OnBnClickedButtonpluslimit2();
	afx_msg void OnBnClickedButtonzeroswitch();
	afx_msg void OnBnClickedButtonzeroswitch2();
	afx_msg void OnBnClickedButtonzeroswitch3();
	afx_msg void OnBnClickedButtonzeroswitch4();
	afx_msg void OnBnClickedButtonminuslimit();
	afx_msg void OnBnClickedButtonminuslimit2();
	afx_msg void OnBnClickedButtonminuslimit3();
	afx_msg void OnBnClickedButtonminuslimit4();
	afx_msg void OnBnClickedButtonabszero();
	afx_msg void OnBnClickedButtonabszero2();
	afx_msg void OnBnClickedButtonabszero3();
	afx_msg void OnBnClickedButtonabszero4();
	afx_msg void OnBnClickedButtonfindzero();
	afx_msg void OnBnClickedButtonfindzero2();
	afx_msg void OnBnClickedButtonfindzero3();
	afx_msg void OnBnClickedButtonfindzero4();
	afx_msg void OnCbnSelchangeCombounit6();
	afx_msg void OnCbnSelchangeCombounit7();
	afx_msg void OnCbnSelchangeCombounit8();
	afx_msg void OnCbnSelchangeCombounit9();

	CString m_strDlgName;

	afx_msg void OnBnClickedButtonsave6();

	void setPara(void);

	afx_msg void OnBnClickedButtondefault6();
};

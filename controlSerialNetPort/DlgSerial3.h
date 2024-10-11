#pragma once
#include "BtnST.h"
#include "Public.h"

// CDlgSerial3 dialog

class CDlgSerial3 : public CDialog
{
	DECLARE_DYNAMIC(CDlgSerial3)

public:
	CDlgSerial3(CWnd* pParent = NULL, int* port = NULL, int* axisNum = NULL);   // standard constructor
	virtual ~CDlgSerial3();

// Dialog Data
	enum { IDD = IDD_DIALOG_SERIAL3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
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
	void InitUI(void);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual BOOL OnInitDialog();

	int m_axisSum[4];
	CString m_sendData;
	int m_loopCommNum;
	bool m_bLoop;

	void start(UINT_PTR nIDEvent, CComboBox* ctrlMode, int axisNum, int port);
	void openLoopComm(UINT_PTR nIDEvent);
	void closeLoopComm(UINT_PTR nIDEvent);
	void loopComm(int* axis, int port);
	void settingComm(CString comm, int axisNum, int port);
	void switchLight(int neg, int zero, int pos, int axisNum);

	virtual BOOL PreTranslateMessage(MSG* pMsg);
	void makeJOG(int sign, int axisNum, int port);
	afx_msg void OnBnClickedButtonstart();
	int m_port;
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
	afx_msg void OnEnSetfocusEditunit6();
	afx_msg void OnEnSetfocusEditunit7();
	afx_msg void OnEnSetfocusEditstartspeed();
	afx_msg void OnEnSetfocusEdittargetspeed();
	afx_msg void OnEnSetfocusEditaccelspeed();
	afx_msg void OnEnSetfocusEditsteps();
	afx_msg void OnEnSetfocusEditstartspeed2();
	afx_msg void OnEnSetfocusEdittargetspeed2();
	afx_msg void OnEnSetfocusEditaccelspeed2();
	afx_msg void OnEnSetfocusEditsteps2();
	afx_msg void OnEnSetfocusEditstartspeed3();
	afx_msg void OnEnSetfocusEdittargetspeed3();
	afx_msg void OnEnSetfocusEditaccelspeed3();
	afx_msg void OnEnSetfocusEditsteps3();
	afx_msg void OnEnSetfocusEditunit8();
	afx_msg void OnEnSetfocusEditstartspeed4();
	afx_msg void OnEnSetfocusEdittargetspeed4();
	afx_msg void OnEnSetfocusEditaccelspeed4();
	afx_msg void OnEnSetfocusEditsteps4();
	afx_msg void OnEnSetfocusEditunit9();
	afx_msg void OnBnClickedRadioabsposition6();
	afx_msg void OnBnClickedRadiorelposition6();
	afx_msg void OnBnClickedRadioabsposition7();
	afx_msg void OnBnClickedRadiorelposition7();
	afx_msg void OnBnClickedRadioabsposition8();
	afx_msg void OnBnClickedRadiorelposition8();
	afx_msg void OnBnClickedRadioabsposition9();
	afx_msg void OnBnClickedRadiorelposition9();
	afx_msg void OnBnClickedButtonsave3();
	void setPara(void);
	afx_msg void OnBnClickedButtondefault3();
	afx_msg void OnBnClickedButtonopenup();

	afx_msg void OnBnClickedButtonopendown();
	afx_msg void OnBnClickedButtoninhale();


	afx_msg void OnBnClickedButtoninhale2();
};

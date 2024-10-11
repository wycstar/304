#pragma once
#include "BtnST.h"
#include "Public.h"

// CDlgSerial2 dialog

class CDlgSerial2 : public CDialog
{
	DECLARE_DYNAMIC(CDlgSerial2)

public:
	CDlgSerial2(CWnd* pParent = NULL, int* port = NULL, int* axisNum = NULL);   // standard constructor
	virtual ~CDlgSerial2();

// Dialog Data
	enum { IDD = IDD_DIALOG_SERIAL2 };

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
	//int m_startspeed3;
	int m_targetspeed3;
	int m_accelspeed3;
	int m_steps3;
	CComboBox m_ctrlMode;
	CComboBox m_ctrlMode2;
	CComboBox m_ctrlMode3;

	CButtonST m_bstplusLight;
	CButtonST m_bstzeroLight;
	CButtonST m_bstminusLight;
	CButtonST m_bstplusLight2;
	CButtonST m_bstzeroLight2;
	CButtonST m_bstminusLight2;
	CButtonST m_bstsave;
	CButtonST m_bstdefault;


	/*CButtonST m_bstplusLight3;
	CButtonST m_bstzeroLight3;
	CButtonST m_bstminusLight3;*/

	int m_absOrRel;
	int m_absOrRel2;
	//int m_absOrRel3;
	CComboBox m_cmbUnitX;
	CComboBox m_cmbUnitX2;
	//CComboBox m_cmbUnitX3;
	double m_unit;
	double m_unit2;
	//double m_unit3;
	afx_msg void OnCbnSelchangeCombounit3();
	afx_msg void OnCbnSelchangeCombounit4();
//	afx_msg void OnCbnSelchangeCombounit5();
	void InitUI(void);
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	CString m_sendData;
	int m_loopCommNum;
	bool m_bLoop;
	int m_axisSum[3];
	int m_port[2];

	void start(UINT_PTR nIDEvent, CComboBox* ctrlMode, int axisNum, int port);
	void openLoopComm(UINT_PTR nIDEvent);
	void closeLoopComm(UINT_PTR nIDEvent);
	void loopComm(int* axis, int* port);
	void settingComm(CString comm, int axisNum, int port);
	void settingComm(CString comm, int port);
    void switchLight(int neg, int zero, int pos, int axisNum);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	void makeJOG(int sign, int axisNum, int port);
	afx_msg void OnBnClickedButtonstart();
	afx_msg void OnBnClickedButtonstart2();
	afx_msg void OnBnClickedButtonstart3();
	afx_msg void OnBnClickedButtonstop();
	afx_msg void OnBnClickedButtonstop2();
	afx_msg void OnBnClickedButtonstop3();
	afx_msg void OnBnClickedButtonpluslimit();
	afx_msg void OnBnClickedButtonpluslimit2();
	//afx_msg void OnBnClickedButtonpluslimit3();
	afx_msg void OnBnClickedButtonzeroswitch();
	afx_msg void OnBnClickedButtonzeroswitch2();
	//afx_msg void OnBnClickedButtonzeroswitch3();
	afx_msg void OnBnClickedButtonminuslimit();
	afx_msg void OnBnClickedButtonminuslimit2();
//	afx_msg void OnBnClickedButtonminuslimit3();
	afx_msg void OnBnClickedButtonabszero();
	afx_msg void OnBnClickedButtonabszero2();
	//afx_msg void OnBnClickedButtonabszero3();
	afx_msg void OnBnClickedButtonfindzero();
	afx_msg void OnBnClickedButtonfindzero2();
	afx_msg void OnBnClickedButtonfindzero3();
	afx_msg void OnEnSetfocusEditstartspeed();
	afx_msg void OnEnSetfocusEditaccelspeed();
	afx_msg void OnEnSetfocusEditsteps();
	afx_msg void OnEnSetfocusEditunit3();
	afx_msg void OnEnSetfocusEdittargetspeed();
	afx_msg void OnEnSetfocusEditstartspeed2();
	afx_msg void OnEnSetfocusEdittargetspeed2();
	afx_msg void OnEnSetfocusEditaccelspeed2();
	afx_msg void OnEnSetfocusEditsteps2();
	afx_msg void OnEnSetfocusEditstartspeed3();
	afx_msg void OnEnSetfocusEdittargetspeed3();
	afx_msg void OnEnSetfocusEditaccelspeed3();
	afx_msg void OnEnSetfocusEditsteps3();
	afx_msg void OnEnSetfocusEditunit5();
	afx_msg void OnEnSetfocusEditunit4();
//	afx_msg void OnBnClickedRadioabsposition3();
//	afx_msg void OnBnClickedRadiorelposition3();
//	afx_msg void OnBnClickedRadioabsposition4();
//	afx_msg void OnBnClickedRadiorelposition4();
//	afx_msg void OnBnClickedRadioabsposition5();
//	afx_msg void OnBnClickedRadiorelposition5();
	afx_msg void OnBnClickedButtonEnable();
	afx_msg void OnBnClickedButtonsave2();
	void setPara(void);
	afx_msg void OnBnClickedButtondefault();
	afx_msg void OnBnClickedButtonopenup();
};

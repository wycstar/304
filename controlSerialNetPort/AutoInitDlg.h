#pragma once

#include "Public.h"


// CAutoInitDlg dialog

class CAutoInitDlg : public CDialog
{
	DECLARE_DYNAMIC(CAutoInitDlg)

public:
	CAutoInitDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CAutoInitDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG_AUTOINIT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

	void InitUI(void);

	/*int m_startspeed[initStepNum - 1];
	int m_targetspeed[initStepNum - 1];
	int m_accelspeed[initStepNum - 1];
	int m_steps[initStepNum - 1];
	int m_IOPara;*/
	/*int m_cameraSteps;
	int m_axisYSteps;
	int m_axisXSteps;
	int m_axis6Steps;
	int m_prismSteps;
	int m_axis3Steps;
	int m_axis8Steps;
	int m_axis9Steps;*/
	
	double m_angelErrorX;
	double m_angelErrorY;
	double m_ratioA;
	double m_ratioX;
	double m_ratioY;
	double m_posX[CALIBRATION_NUM];
	double m_posY[CALIBRATION_NUM];
	double m_posA[CALIBRATION_NUM];

	void setPara(int workNum);
	LRESULT OnSavePara(WPARAM WP, LPARAM LP);	
	LRESULT OnUpdateUIPara(WPARAM WP, LPARAM LP);	
	LRESULT OnLoadPara(WPARAM WP, LPARAM LP);	


};

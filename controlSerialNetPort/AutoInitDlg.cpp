// AutoInitDlg.cpp : implementation file
//

#include "stdafx.h"
#include "controlSerialNetPort.h"
#include "AutoInitDlg.h"
#include "controlSerialNetPortDlg.h"


// CAutoInitDlg dialog
extern CcontrolSerialNetPortDlg* mainDlg;



IMPLEMENT_DYNAMIC(CAutoInitDlg, CDialog)



CAutoInitDlg::CAutoInitDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAutoInitDlg::IDD, pParent)
{
	/*for (int i = 0; i < initStepNum - 1; i++)
	{
		m_startspeed[i] = 50000;
		m_targetspeed[i] = 100000;
		m_accelspeed[i] = 5000;
		m_steps[i] = 50000;
	}

	m_IOPara = 0;*/

	//m_cameraSteps = 500;
	//m_axisYSteps = 500;
	//m_axisXSteps = 500;
	//m_axis6Steps = 500;
	//m_prismSteps = 500;
	//m_axis3Steps = 500;
	//m_axis8Steps = 500;
	//m_axis9Steps = 500;

}

CAutoInitDlg::~CAutoInitDlg()
{
}

void CAutoInitDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	//DDX_Text(pDX, IDC_EDIT_camera, m_cameraSteps);
	//DDX_Text(pDX, IDC_EDIT_axisY, m_axisYSteps);
	//DDX_Text(pDX, IDC_EDIT_axisX, m_axisXSteps);
	//DDX_Text(pDX, IDC_EDIT_axis6, m_axis6Steps);
	//DDX_Text(pDX, IDC_EDIT_prism, m_prismSteps);
	//DDX_Text(pDX, IDC_EDIT_axis3, m_axis3Steps);
	//DDX_Text(pDX, IDC_EDIT_axis8, m_axis8Steps);
	//DDX_Text(pDX, IDC_EDIT_axis9, m_axis9Steps);

	DDX_Text(pDX, IDC_EDIT_angleErrorX, m_angelErrorX);
	DDX_Text(pDX, IDC_EDIT_angleErrorY, m_angelErrorY);
	DDX_Text(pDX, IDC_EDIT_Xratio, m_ratioX);
	DDX_Text(pDX, IDC_EDIT_Yratio, m_ratioY);
	DDX_Text(pDX, IDC_EDIT_Aratio, m_ratioA);

	DDX_Text(pDX, IDC_EDIT_XPos, m_posX[0]);
	DDX_Text(pDX, IDC_EDIT_YPos, m_posY[0]);
	DDX_Text(pDX, IDC_EDIT_APos, m_posA[0]);

	DDX_Text(pDX, IDC_EDIT_XPos2, m_posX[1]);
	DDX_Text(pDX, IDC_EDIT_YPos2, m_posY[1]);
	DDX_Text(pDX, IDC_EDIT_APos2, m_posA[1]);

	DDX_Text(pDX, IDC_EDIT_XPos3, m_posX[2]);
	DDX_Text(pDX, IDC_EDIT_YPos3, m_posY[2]);
	DDX_Text(pDX, IDC_EDIT_APos3, m_posA[2]);

	DDX_Text(pDX, IDC_EDIT_XPos4, m_posX[3]);
	DDX_Text(pDX, IDC_EDIT_YPos4, m_posY[3]);
	DDX_Text(pDX, IDC_EDIT_APos4, m_posA[3]);

	DDX_Text(pDX, IDC_EDIT_XPos5, m_posX[4]);
	DDX_Text(pDX, IDC_EDIT_YPos5, m_posY[4]);
	DDX_Text(pDX, IDC_EDIT_APos5, m_posA[4]);

	/*DDX_Text(pDX, IDC_EDIT_startSpeed, m_startspeed[0]);
	DDX_Text(pDX, IDC_EDIT_targetSpeed, m_targetspeed[0]);
	DDX_Text(pDX, IDC_EDIT_accelspeed, m_accelspeed[0]);
	DDX_Text(pDX, IDC_EDIT_steps, m_steps[0]);

	DDX_Text(pDX, IDC_EDIT_startSpeed2, m_startspeed[1]);
	DDX_Text(pDX, IDC_EDIT_targetSpeed2, m_targetspeed[1]);
	DDX_Text(pDX, IDC_EDIT_accelspeed2, m_accelspeed[1]);
	DDX_Text(pDX, IDC_EDIT_steps2, m_steps[1]);

	DDX_Text(pDX, IDC_EDIT_startSpeed3, m_startspeed[2]);
	DDX_Text(pDX, IDC_EDIT_targetSpeed3, m_targetspeed[2]);
	DDX_Text(pDX, IDC_EDIT_accelspeed3, m_accelspeed[2]);
	DDX_Text(pDX, IDC_EDIT_steps3, m_steps[2]);

	DDX_Text(pDX, IDC_EDIT_startSpeed4, m_startspeed[3]);
	DDX_Text(pDX, IDC_EDIT_targetSpeed4, m_targetspeed[3]);
	DDX_Text(pDX, IDC_EDIT_accelspeed4, m_accelspeed[3]);
	DDX_Text(pDX, IDC_EDIT_step4, m_steps[3]);

	DDX_Text(pDX, IDC_EDIT_startSpeed5, m_startspeed[4]);
	DDX_Text(pDX, IDC_EDIT_targetSpeed5, m_targetspeed[4]);
	DDX_Text(pDX, IDC_EDIT_accelspeed5, m_accelspeed[4]);
	DDX_Text(pDX, IDC_EDIT_steps5, m_steps[4]);

	DDX_Text(pDX, IDC_EDIT_startSpeed6, m_startspeed[5]);
	DDX_Text(pDX, IDC_EDIT_targetSpeed6, m_targetspeed[5]);
	DDX_Text(pDX, IDC_EDIT_accelspeed6, m_accelspeed[5]);
	DDX_Text(pDX, IDC_EDIT_steps6, m_steps[5]);

	DDX_Text(pDX, IDC_EDIT_startSpeed7, m_startspeed[6]);
	DDX_Text(pDX, IDC_EDIT_targetSpeed7, m_targetspeed[6]);
	DDX_Text(pDX, IDC_EDIT_accelspeed7, m_accelspeed[6]);
	DDX_Text(pDX, IDC_EDIT_steps7, m_steps[6]);

	DDX_Text(pDX, IDC_EDIT_startSpeed8, m_startspeed[7]);
	DDX_Text(pDX, IDC_EDIT_targetSpeed8, m_targetspeed[7]);
	DDX_Text(pDX, IDC_EDIT_accelspeed8, m_accelspeed[7]);
	DDX_Text(pDX, IDC_EDIT_steps8, m_steps[7]);

	DDX_Text(pDX, IDC_EDIT_startSpeed9, m_startspeed[8]);
	DDX_Text(pDX, IDC_EDIT_targetSpeed9, m_targetspeed[8]);
	DDX_Text(pDX, IDC_EDIT_accelspeed9, m_accelspeed[8]);
	DDX_Text(pDX, IDC_EDIT_steps9, m_steps[8]);

	DDX_Text(pDX, IDC_EDIT_startSpeed10, m_startspeed[9]);
	DDX_Text(pDX, IDC_EDIT_targetSpeed10, m_targetspeed[9]);
	DDX_Text(pDX, IDC_EDIT_accelspeed10, m_accelspeed[9]);
	DDX_Text(pDX, IDC_EDIT_steps10, m_steps[9]);

	DDX_Text(pDX, IDC_EDIT_IOPARA, m_IOPara);*/



}


BEGIN_MESSAGE_MAP(CAutoInitDlg, CDialog)
	ON_MESSAGE(SAVE_PARATOFILE, OnSavePara)
	ON_MESSAGE(RECOVER_UIPARA, OnUpdateUIPara)
	ON_MESSAGE(LOAD_FILETOPARA, OnLoadPara)
END_MESSAGE_MAP()


// CAutoInitDlg message handlers

BOOL CAutoInitDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	InitUI();


	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CAutoInitDlg::InitUI(void)
{
	
	setPara(0);

}

void CAutoInitDlg::setPara(int workNum)
{
	/*for (int i = 0; i < initStepNum - 1; i++)
	{
		m_startspeed[i] = CPublic::g_initParameter[workNum][i].startspeed;
		m_targetspeed[i] = CPublic::g_initParameter[workNum][i].targetspeed;
		m_accelspeed[i] = CPublic::g_initParameter[workNum][i].accelspeed;
		m_steps[i] = CPublic::g_initParameter[workNum][i].steps;
	}

	m_IOPara = CPublic::g_initIOPara[workNum];*/
	//m_cameraSteps = CPublic::g_newinitParameter[workNum].cameraSteps;
	//m_axisYSteps = CPublic::g_newinitParameter[workNum].axisYSteps;
	//m_axisXSteps = CPublic::g_newinitParameter[workNum].axisXSteps;
	//m_axis6Steps = CPublic::g_newinitParameter[workNum].axis6Steps;
	//m_prismSteps = CPublic::g_newinitParameter[workNum].prismSteps;
	//m_axis3Steps = CPublic::g_newinitParameter[workNum].axis3Steps;
	//m_axis8Steps = CPublic::g_newinitParameter[workNum].axis8Steps;
	//m_axis9Steps = CPublic::g_newinitParameter[workNum].axis9Steps;

	m_angelErrorX = CPublic::g_newinitParameter[workNum].angelErrorX;
	m_angelErrorY = CPublic::g_newinitParameter[workNum].angelErrorY;
	m_ratioX = CPublic::g_newinitParameter[workNum].ratioX;
	m_ratioY = CPublic::g_newinitParameter[workNum].ratioY;
	m_ratioA = CPublic::g_newinitParameter[workNum].ratioA;

	for (int i = 0; i < CALIBRATION_NUM; i++)
	{
		m_posX[i] = CPublic::g_newinitParameter[workNum].posX[i];
		m_posY[i] = CPublic::g_newinitParameter[workNum].posY[i];
		m_posA[i] = CPublic::g_newinitParameter[workNum].posA[i];
	}

	
	UpdateData(FALSE);


}

LRESULT CAutoInitDlg::OnSavePara(WPARAM WP, LPARAM LP)
{
	UpdateData();

	int workNum = (int)LP;

	/*for (int i = 0; i < initStepNum - 1; i++)
	{
		CPublic::g_initParameter[workNum][i].startspeed = m_startspeed[i];
		CPublic::g_initParameter[workNum][i].targetspeed = m_targetspeed[i];
		CPublic::g_initParameter[workNum][i].accelspeed = m_accelspeed[i];
		CPublic::g_initParameter[workNum][i].steps = m_steps[i];
	}
	CPublic::g_initIOPara[workNum] = m_IOPara;*/

	//CPublic::g_newinitParameter[workNum].cameraSteps = m_cameraSteps;
	//CPublic::g_newinitParameter[workNum].axisXSteps = m_axisXSteps;
	//CPublic::g_newinitParameter[workNum].axis6Steps = m_axis6Steps;
	//CPublic::g_newinitParameter[workNum].prismSteps = m_prismSteps;
	//CPublic::g_newinitParameter[workNum].axis3Steps = m_axis3Steps;
	//CPublic::g_newinitParameter[workNum].axis8Steps = m_axis8Steps;
	//CPublic::g_newinitParameter[workNum].axis9Steps = m_axis9Steps;


	CPublic::g_newinitParameter[workNum].angelErrorX = m_angelErrorX;
	CPublic::g_newinitParameter[workNum].angelErrorY = m_angelErrorY;
	CPublic::g_newinitParameter[workNum].ratioX = m_ratioX;
	CPublic::g_newinitParameter[workNum].ratioY = m_ratioY;
	CPublic::g_newinitParameter[workNum].ratioA = m_ratioA;

	for (int i = 0; i < CALIBRATION_NUM; i++)
	{
		CPublic::g_newinitParameter[workNum].posX[i] = m_posX[i];
		CPublic::g_newinitParameter[workNum].posY[i] = m_posY[i];
		CPublic::g_newinitParameter[workNum].posA[i] = m_posA[i];
	}



	mainDlg->updateInitValue2File(workNum, true);

	return 0;
	


	//mainDlg->updateAxisParameter2Value(para, axis, 2, true);
	//mainDlg->updateValue2File(axis, 2, true);

}

LRESULT CAutoInitDlg::OnUpdateUIPara(WPARAM WP, LPARAM LP)
{
	UpdateData();

	/*for (int i = 0; i < initStepNum - 1; i++)
	{
		m_startspeed[i] = 5000;
		m_targetspeed[i] = 100000;
		m_accelspeed[i] = 50000;
		m_steps[i] = 50000;
	}
	m_IOPara = 0;*/
	//m_cameraSteps = 50000;
	//m_axisYSteps = 50000;
	//m_axisXSteps = 50000;
	//m_axis6Steps = 50000;
	//m_prismSteps = 50000;
	//m_axis3Steps = 50000;
	//m_axis8Steps = 50000;
	//m_axis9Steps = 50000;

	m_angelErrorX = 5000;
	m_angelErrorY = 5000;
	m_ratioA = 5000;
	m_ratioX = 5000;
	m_ratioY = 5000;

	for (int i = 0; i < CALIBRATION_NUM; i++)
	{
		m_posX[i] = 5000;
		m_posY[i] = 5000;
		m_posA[i] = 5000;
	}

	UpdateData(FALSE);

	return 0;

}

LRESULT CAutoInitDlg::OnLoadPara(WPARAM WP, LPARAM LP)
{
	UpdateData();
	int workNum = (int)LP;

	setPara(workNum);
	UpdateData(FALSE);

	return 0;

}


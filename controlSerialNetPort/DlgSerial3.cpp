// DlgSerial3.cpp : implementation file
//

#include "stdafx.h"
#include "controlSerialNetPort.h"
#include "DlgSerial3.h"
#include "controlSerialNetPortDlg.h"

// CDlgSerial3 dialog
extern CcontrolSerialNetPortDlg* mainDlg;

IMPLEMENT_DYNAMIC(CDlgSerial3, CDialog)

CDlgSerial3::CDlgSerial3(CWnd* pParent /*=NULL*/, int* port, int* axisNum)
	: CDialog(CDlgSerial3::IDD, pParent)
	, m_startspeed(5000)
	, m_targetspeed(100000)
	, m_accelspeed(50000)
	, m_steps(0)
	, m_startspeed2(5000)
	, m_targetspeed2(100000)
	, m_accelspeed2(50000)
	, m_steps2(0)
	, m_startspeed3(5000)
	, m_targetspeed3(100000)
	, m_accelspeed3(50000)
	, m_steps3(0)
	, m_startspeed4(5000)
	, m_targetspeed4(100000)
	, m_accelspeed4(50000)
	, m_steps4(0)
	,m_absOrRel(0)
	,m_absOrRel2(0)
	,m_absOrRel3(0)
	,m_absOrRel4(0)
	,m_unit(1)
	,m_unit2(1)
	,m_unit3(1)
	,m_unit4(1)
	,m_sendData(_T(""))
	,m_loopCommNum(0)
	,m_bLoop(true)
{
	m_port = *port;
	for (int i = 0; i < 4; i++)
	{
		m_axisSum[i] = axisNum[i];
	}

}

CDlgSerial3::~CDlgSerial3()
{
}

void CDlgSerial3::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_startSpeed, m_startspeed);
	DDX_Text(pDX, IDC_EDIT_targetSpeed, m_targetspeed);
	DDX_Text(pDX, IDC_EDIT_accelspeed, m_accelspeed);
	DDX_Text(pDX, IDC_EDIT_steps, m_steps);
	DDX_Text(pDX, IDC_EDIT_startSpeed2, m_startspeed2);
	DDX_Text(pDX, IDC_EDIT_targetSpeed2, m_targetspeed2);
	DDX_Text(pDX, IDC_EDIT_accelspeed2, m_accelspeed2);
	DDX_Text(pDX, IDC_EDIT_steps2, m_steps2);
	DDX_Text(pDX, IDC_EDIT_startSpeed3, m_startspeed3);
	DDX_Text(pDX, IDC_EDIT_targetSpeed3, m_targetspeed3);
	DDX_Text(pDX, IDC_EDIT_accelspeed3, m_accelspeed3);
	DDX_Text(pDX, IDC_EDIT_steps3, m_steps3);
	DDX_Text(pDX, IDC_EDIT_startSpeed4, m_startspeed4);
	DDX_Text(pDX, IDC_EDIT_targetSpeed4, m_targetspeed4);
	DDX_Text(pDX, IDC_EDIT_accelspeed4, m_accelspeed4);
	DDX_Text(pDX, IDC_EDIT_steps4, m_steps4);
	DDX_Control(pDX, IDC_COMBO_MODE, m_ctrlMode);
	DDX_Control(pDX, IDC_COMBO_MODE2, m_ctrlMode2);
	DDX_Control(pDX, IDC_COMBO_MODE3, m_ctrlMode3);
	DDX_Control(pDX, IDC_COMBO_MODE4, m_ctrlMode4);

	DDX_Radio(pDX, IDC_RADIO_absPosition6, m_absOrRel);
	DDX_Radio(pDX, IDC_RADIO_absPosition7, m_absOrRel2);
	DDX_Radio(pDX, IDC_RADIO_absPosition8, m_absOrRel3);
	DDX_Radio(pDX, IDC_RADIO_absPosition9, m_absOrRel4);
	DDX_Control(pDX, IDC_COMBO_unit6, m_cmbUnitX);
	DDX_Control(pDX, IDC_COMBO_unit7, m_cmbUnitX2);
	DDX_Control(pDX, IDC_COMBO_unit8, m_cmbUnitX3);
	DDX_Control(pDX, IDC_COMBO_unit9, m_cmbUnitX4);
	DDX_Text(pDX, IDC_EDIT_unit6, m_unit);
	DDX_Text(pDX, IDC_EDIT_unit7, m_unit2);
	DDX_Text(pDX, IDC_EDIT_unit8, m_unit3);
	DDX_Text(pDX, IDC_EDIT_unit9, m_unit4);

	DDX_Control(pDX, IDC_BUTTON_plusLight, m_bstplusLight);
	DDX_Control(pDX, IDC_BUTTON_zeroLight, m_bstzeroLight);
	DDX_Control(pDX, IDC_BUTTON_minusLight, m_bstminusLight);
	DDX_Control(pDX, IDC_BUTTON_plusLight2, m_bstplusLight2);
	DDX_Control(pDX, IDC_BUTTON_zeroLight2, m_bstzeroLight2);
	DDX_Control(pDX, IDC_BUTTON_minusLight2, m_bstminusLight2);
	DDX_Control(pDX, IDC_BUTTON_plusLight3, m_bstplusLight3);
	DDX_Control(pDX, IDC_BUTTON_zeroLight3, m_bstzeroLight3);
	DDX_Control(pDX, IDC_BUTTON_minusLight3, m_bstminusLight3);
	DDX_Control(pDX, IDC_BUTTON_plusLight4, m_bstplusLight4);
	DDX_Control(pDX, IDC_BUTTON_zeroLight4, m_bstzeroLight4);
	DDX_Control(pDX, IDC_BUTTON_minusLight4, m_bstminusLight4);

	DDX_Control(pDX, IDC_BUTTON_save3, m_bstsave);
	DDX_Control(pDX, IDC_BUTTON_default3, m_bstdefault);


}


BEGIN_MESSAGE_MAP(CDlgSerial3, CDialog)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_start, &CDlgSerial3::OnBnClickedButtonstart)
	ON_BN_CLICKED(IDC_BUTTON_start2, &CDlgSerial3::OnBnClickedButtonstart2)
	ON_BN_CLICKED(IDC_BUTTON_start3, &CDlgSerial3::OnBnClickedButtonstart3)
	ON_BN_CLICKED(IDC_BUTTON_start4, &CDlgSerial3::OnBnClickedButtonstart4)
	ON_BN_CLICKED(IDC_BUTTON_stop, &CDlgSerial3::OnBnClickedButtonstop)
	ON_BN_CLICKED(IDC_BUTTON_stop2, &CDlgSerial3::OnBnClickedButtonstop2)
	ON_BN_CLICKED(IDC_BUTTON_stop3, &CDlgSerial3::OnBnClickedButtonstop3)
	ON_BN_CLICKED(IDC_BUTTON_stop4, &CDlgSerial3::OnBnClickedButtonstop4)
	ON_BN_CLICKED(IDC_BUTTON_plusLimit3, &CDlgSerial3::OnBnClickedButtonpluslimit3)
	ON_BN_CLICKED(IDC_BUTTON_plusLimit4, &CDlgSerial3::OnBnClickedButtonpluslimit4)
	ON_BN_CLICKED(IDC_BUTTON_plusLimit, &CDlgSerial3::OnBnClickedButtonpluslimit)
	ON_BN_CLICKED(IDC_BUTTON_plusLimit2, &CDlgSerial3::OnBnClickedButtonpluslimit2)
	ON_BN_CLICKED(IDC_BUTTON_zeroSwitch, &CDlgSerial3::OnBnClickedButtonzeroswitch)
	ON_BN_CLICKED(IDC_BUTTON_zeroSwitch2, &CDlgSerial3::OnBnClickedButtonzeroswitch2)
	ON_BN_CLICKED(IDC_BUTTON_zeroSwitch3, &CDlgSerial3::OnBnClickedButtonzeroswitch3)
	ON_BN_CLICKED(IDC_BUTTON_zeroSwitch4, &CDlgSerial3::OnBnClickedButtonzeroswitch4)
	ON_BN_CLICKED(IDC_BUTTON_minusLimit, &CDlgSerial3::OnBnClickedButtonminuslimit)
	ON_BN_CLICKED(IDC_BUTTON_minusLimit2, &CDlgSerial3::OnBnClickedButtonminuslimit2)
	ON_BN_CLICKED(IDC_BUTTON_minusLimit3, &CDlgSerial3::OnBnClickedButtonminuslimit3)
	ON_BN_CLICKED(IDC_BUTTON_minusLimit4, &CDlgSerial3::OnBnClickedButtonminuslimit4)
	ON_BN_CLICKED(IDC_BUTTON_absZero, &CDlgSerial3::OnBnClickedButtonabszero)
	ON_BN_CLICKED(IDC_BUTTON_absZero2, &CDlgSerial3::OnBnClickedButtonabszero2)
	ON_BN_CLICKED(IDC_BUTTON_absZero3, &CDlgSerial3::OnBnClickedButtonabszero3)
	ON_BN_CLICKED(IDC_BUTTON_absZero4, &CDlgSerial3::OnBnClickedButtonabszero4)
	ON_BN_CLICKED(IDC_BUTTON_findZero, &CDlgSerial3::OnBnClickedButtonfindzero)
	ON_BN_CLICKED(IDC_BUTTON_findZero2, &CDlgSerial3::OnBnClickedButtonfindzero2)
	ON_BN_CLICKED(IDC_BUTTON_findZero3, &CDlgSerial3::OnBnClickedButtonfindzero3)
	ON_BN_CLICKED(IDC_BUTTON_findZero4, &CDlgSerial3::OnBnClickedButtonfindzero4)
	ON_CBN_SELCHANGE(IDC_COMBO_unit6, &CDlgSerial3::OnCbnSelchangeCombounit6)
	ON_CBN_SELCHANGE(IDC_COMBO_unit7, &CDlgSerial3::OnCbnSelchangeCombounit7)
	ON_CBN_SELCHANGE(IDC_COMBO_unit8, &CDlgSerial3::OnCbnSelchangeCombounit8)
	ON_CBN_SELCHANGE(IDC_COMBO_unit9, &CDlgSerial3::OnCbnSelchangeCombounit9)
	ON_EN_SETFOCUS(IDC_EDIT_unit6, &CDlgSerial3::OnEnSetfocusEditunit6)
	ON_EN_SETFOCUS(IDC_EDIT_unit7, &CDlgSerial3::OnEnSetfocusEditunit7)
	ON_EN_SETFOCUS(IDC_EDIT_startSpeed, &CDlgSerial3::OnEnSetfocusEditstartspeed)
	ON_EN_SETFOCUS(IDC_EDIT_targetSpeed, &CDlgSerial3::OnEnSetfocusEdittargetspeed)
	ON_EN_SETFOCUS(IDC_EDIT_accelspeed, &CDlgSerial3::OnEnSetfocusEditaccelspeed)
	ON_EN_SETFOCUS(IDC_EDIT_steps, &CDlgSerial3::OnEnSetfocusEditsteps)
	ON_EN_SETFOCUS(IDC_EDIT_startSpeed2, &CDlgSerial3::OnEnSetfocusEditstartspeed2)
	ON_EN_SETFOCUS(IDC_EDIT_targetSpeed2, &CDlgSerial3::OnEnSetfocusEdittargetspeed2)
	ON_EN_SETFOCUS(IDC_EDIT_accelspeed2, &CDlgSerial3::OnEnSetfocusEditaccelspeed2)
	ON_EN_SETFOCUS(IDC_EDIT_steps2, &CDlgSerial3::OnEnSetfocusEditsteps2)
	ON_EN_SETFOCUS(IDC_EDIT_startSpeed3, &CDlgSerial3::OnEnSetfocusEditstartspeed3)
	ON_EN_SETFOCUS(IDC_EDIT_targetSpeed3, &CDlgSerial3::OnEnSetfocusEdittargetspeed3)
	ON_EN_SETFOCUS(IDC_EDIT_accelspeed3, &CDlgSerial3::OnEnSetfocusEditaccelspeed3)
	ON_EN_SETFOCUS(IDC_EDIT_steps3, &CDlgSerial3::OnEnSetfocusEditsteps3)
	ON_EN_SETFOCUS(IDC_EDIT_unit8, &CDlgSerial3::OnEnSetfocusEditunit8)
	ON_EN_SETFOCUS(IDC_EDIT_startSpeed4, &CDlgSerial3::OnEnSetfocusEditstartspeed4)
	ON_EN_SETFOCUS(IDC_EDIT_targetSpeed4, &CDlgSerial3::OnEnSetfocusEdittargetspeed4)
	ON_EN_SETFOCUS(IDC_EDIT_accelspeed4, &CDlgSerial3::OnEnSetfocusEditaccelspeed4)
	ON_EN_SETFOCUS(IDC_EDIT_steps4, &CDlgSerial3::OnEnSetfocusEditsteps4)
	ON_EN_SETFOCUS(IDC_EDIT_unit9, &CDlgSerial3::OnEnSetfocusEditunit9)
	ON_BN_CLICKED(IDC_RADIO_absPosition6, &CDlgSerial3::OnBnClickedRadioabsposition6)
	ON_BN_CLICKED(IDC_RADIO_relPosition6, &CDlgSerial3::OnBnClickedRadiorelposition6)
	ON_BN_CLICKED(IDC_RADIO_absPosition7, &CDlgSerial3::OnBnClickedRadioabsposition7)
	ON_BN_CLICKED(IDC_RADIO_relPosition7, &CDlgSerial3::OnBnClickedRadiorelposition7)
	ON_BN_CLICKED(IDC_RADIO_absPosition8, &CDlgSerial3::OnBnClickedRadioabsposition8)
	ON_BN_CLICKED(IDC_RADIO_relPosition8, &CDlgSerial3::OnBnClickedRadiorelposition8)
	ON_BN_CLICKED(IDC_RADIO_absPosition9, &CDlgSerial3::OnBnClickedRadioabsposition9)
	ON_BN_CLICKED(IDC_RADIO_relPosition9, &CDlgSerial3::OnBnClickedRadiorelposition9)
	ON_BN_CLICKED(IDC_BUTTON_save3, &CDlgSerial3::OnBnClickedButtonsave3)
	ON_BN_CLICKED(IDC_BUTTON_default3, &CDlgSerial3::OnBnClickedButtondefault3)
	ON_BN_CLICKED(IDC_BUTTON_openup, &CDlgSerial3::OnBnClickedButtonopenup)
	ON_BN_CLICKED(IDC_BUTTON_opendown, &CDlgSerial3::OnBnClickedButtonopendown)
	ON_BN_CLICKED(IDC_BUTTON_inhale, &CDlgSerial3::OnBnClickedButtoninhale)
	ON_BN_CLICKED(IDC_BUTTON_inhale2, &CDlgSerial3::OnBnClickedButtoninhale2)
END_MESSAGE_MAP()


// CDlgSerial3 message handlers

void CDlgSerial3::InitUI(void)
{
	//轴1
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_startSpeed))->SetRange32(0,0x7fffffff);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_targetspeed))->SetRange32(0,0x7fffffff);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_accelspeed))->SetRange32(0,0x7fffffff);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_steps))->SetRange32(0xffffffff,0x7fffffff);

	m_ctrlMode.SetCurSel(0);
	m_cmbUnitX.SetCurSel(0);

	//轴2
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_startSpeed2))->SetRange32(0,0x7fffffff);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_targetspeed2))->SetRange32(0,0x7fffffff);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_accelspeed2))->SetRange32(0,0x7fffffff);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_steps2))->SetRange32(0xffffffff,0x7fffffff);

	m_ctrlMode2.SetCurSel(0);
	m_cmbUnitX2.SetCurSel(0);


	//轴3
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_startSpeed3))->SetRange32(0,0x7fffffff);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_targetspeed3))->SetRange32(0,0x7fffffff);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_accelspeed3))->SetRange32(0,0x7fffffff);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_steps3))->SetRange32(0xffffffff,0x7fffffff);

	m_ctrlMode3.SetCurSel(0);
	m_cmbUnitX3.SetCurSel(0);

	//轴4
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_startSpeed4))->SetRange32(0,0x7fffffff);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_targetspeed4))->SetRange32(0,0x7fffffff);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_accelspeed4))->SetRange32(0,0x7fffffff);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_steps4))->SetRange32(0xffffffff,0x7fffffff);

	m_ctrlMode4.SetCurSel(0);
	m_cmbUnitX4.SetCurSel(0);

	//init indication button
	m_bstplusLight.SetIcon(IDI_ICON_Cgrey24);
	m_bstzeroLight.SetIcon(IDI_ICON_Cgrey24);
	m_bstminusLight.SetIcon(IDI_ICON_Cgrey24);

	m_bstplusLight.DrawBorder(FALSE);
	m_bstzeroLight.DrawBorder(FALSE);
	m_bstminusLight.DrawBorder(FALSE);

	m_bstplusLight2.SetIcon(IDI_ICON_Cgrey24);
	m_bstzeroLight2.SetIcon(IDI_ICON_Cgrey24);
	m_bstminusLight2.SetIcon(IDI_ICON_Cgrey24);

	m_bstplusLight2.DrawBorder(FALSE);
	m_bstzeroLight2.DrawBorder(FALSE);
	m_bstminusLight2.DrawBorder(FALSE);

	m_bstplusLight3.SetIcon(IDI_ICON_Cgrey24);
	m_bstzeroLight3.SetIcon(IDI_ICON_Cgrey24);
	m_bstminusLight3.SetIcon(IDI_ICON_Cgrey24);

	m_bstplusLight3.DrawBorder(FALSE);
	m_bstzeroLight3.DrawBorder(FALSE);
	m_bstminusLight3.DrawBorder(FALSE);

	m_bstplusLight4.SetIcon(IDI_ICON_Cgrey24);
	m_bstzeroLight4.SetIcon(IDI_ICON_Cgrey24);
	m_bstminusLight4.SetIcon(IDI_ICON_Cgrey24);

	m_bstplusLight4.DrawBorder(FALSE);
	m_bstzeroLight4.DrawBorder(FALSE);
	m_bstminusLight4.DrawBorder(FALSE);

	m_bstsave.SetIcon(IDI_ICON_save32);
	m_bstsave.SetTooltipText(_T("保存配置"));
	m_bstdefault.SetIcon(IDI_ICON_default32);
	m_bstdefault.SetTooltipText(_T("设置默认值"));

	setPara();

	SetTimer(1, loopTime, NULL);

}

BOOL CDlgSerial3::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_LBUTTONDOWN)
	{
		if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_JOGM)->m_hWnd)
		{
			((CButton*)GetDlgItem(IDC_BUTTON_JOGM))->SetState(TRUE);

			makeJOG(-1, m_axisSum[0], m_port);
			return TRUE;

		}
		if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_JOGP)->m_hWnd)
		{
			((CButton*)GetDlgItem(IDC_BUTTON_JOGP))->SetState(TRUE);
			makeJOG(1, m_axisSum[0], m_port);
			return TRUE;
		}

		if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_JOGM2)->m_hWnd)
		{
			((CButton*)GetDlgItem(IDC_BUTTON_JOGM2))->SetState(TRUE);

			makeJOG(-1, m_axisSum[1], m_port);
			return TRUE;

		}
		if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_JOGP2)->m_hWnd)
		{
			((CButton*)GetDlgItem(IDC_BUTTON_JOGP2))->SetState(TRUE);
			makeJOG(1, m_axisSum[1], m_port);
			return TRUE;
		}

		if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_JOGM3)->m_hWnd)
		{
			((CButton*)GetDlgItem(IDC_BUTTON_JOGM3))->SetState(TRUE);

			makeJOG(-1, m_axisSum[2], m_port);
			return TRUE;

		}
		if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_JOGP3)->m_hWnd)
		{
			((CButton*)GetDlgItem(IDC_BUTTON_JOGP3))->SetState(TRUE);
			makeJOG(1, m_axisSum[2], m_port);
			return TRUE;
		}

		if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_JOGM4)->m_hWnd)
		{
			((CButton*)GetDlgItem(IDC_BUTTON_JOGM4))->SetState(TRUE);

			makeJOG(-1, m_axisSum[3], m_port);
			return TRUE;

		}
		if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_JOGP4)->m_hWnd)
		{
			((CButton*)GetDlgItem(IDC_BUTTON_JOGP4))->SetState(TRUE);
			makeJOG(1, m_axisSum[3], m_port);
			return TRUE;
		}



	}

	if (pMsg->message==WM_LBUTTONUP)
	{
		if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_JOGP)->m_hWnd) 
		{
			((CButton*)GetDlgItem(IDC_BUTTON_JOGP))->SetState(FALSE);
			makeJOG(0, m_axisSum[0], m_port);
			return TRUE;
		}

		if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_JOGM)->m_hWnd)
		{
			((CButton*)GetDlgItem(IDC_BUTTON_JOGM))->SetState(FALSE);
			makeJOG(0, m_axisSum[0], m_port);
			return TRUE;
		}

		if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_JOGP2)->m_hWnd) 
		{
			((CButton*)GetDlgItem(IDC_BUTTON_JOGP2))->SetState(FALSE);
			makeJOG(0, m_axisSum[1], m_port);
			return TRUE;
		}

		if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_JOGM2)->m_hWnd)
		{
			((CButton*)GetDlgItem(IDC_BUTTON_JOGM2))->SetState(FALSE);
			makeJOG(0, m_axisSum[1], m_port);
			return TRUE;
		}

		if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_JOGP3)->m_hWnd) 
		{
			((CButton*)GetDlgItem(IDC_BUTTON_JOGP3))->SetState(FALSE);
			makeJOG(0, m_axisSum[2], m_port);
			return TRUE;
		}

		if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_JOGM3)->m_hWnd)
		{
			((CButton*)GetDlgItem(IDC_BUTTON_JOGM3))->SetState(FALSE);
			makeJOG(0, m_axisSum[2], m_port);
			return TRUE;
		}

		if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_JOGP4)->m_hWnd) 
		{
			((CButton*)GetDlgItem(IDC_BUTTON_JOGP4))->SetState(FALSE);
			makeJOG(0, m_axisSum[3], m_port);
			return TRUE;
		}

		if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_JOGM4)->m_hWnd)
		{
			((CButton*)GetDlgItem(IDC_BUTTON_JOGM4))->SetState(FALSE);
			makeJOG(0, m_axisSum[3], m_port);
			return TRUE;
		}

	}


	return CDialog::PreTranslateMessage(pMsg);
}



BOOL CDlgSerial3::OnInitDialog()
{
	CDialog::OnInitDialog();

	InitUI();
	SetWindowText(_T("工位1辅助部件手动调整"));


	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgSerial3::OnTimer(UINT_PTR nIDEvent)
{
	switch(nIDEvent)
	{

	case 1:

		loopComm(m_axisSum, m_port);		
		break;

	case 2:
		start(nIDEvent, &m_ctrlMode, m_axisSum[0], m_port);
		break;


	case 3:
		start(nIDEvent, &m_ctrlMode2, m_axisSum[1], m_port);
		break;

	case 4:
		start(nIDEvent, &m_ctrlMode3, m_axisSum[2], m_port);
		break;

	case 5:
		start(nIDEvent, &m_ctrlMode4, m_axisSum[3], m_port);
		break;		
	}

	CDialog::OnTimer(nIDEvent);
}

void CDlgSerial3::start(UINT_PTR nIDEvent, CComboBox* ctrlMode, int axisNum, int port)
{
	UpdateData();
	//CString comm = _T("");
	CString strAxis = CPublic::int2CString(axisNum);
	m_bLoop = false;


	if (CPublic::commCount == 0)
	{
		m_sendData = (ctrlMode->GetCurSel() == 0) ?  _T("OMOD ") : _T("CMOD ");
		m_sendData = m_sendData + CPublic::int2CString(axisNum);
		mainDlg->sendComm(m_sendData, port);

	}else if (CPublic::commCount == 1)
	{	
		if (CPublic::bfindTerminator[port - 1] == false)
			return;

		if (CPublic::receiveData[port - 1] != m_sendData)
		{
			mainDlg->AddString(ERRO1);
			KillTimer(nIDEvent);
			openLoopComm(1);
			return;
		}
		//mainDlg->AddString(CPublic::receiveData[portNum1 - 1]);

		int startspeed = (axisNum == m_axisSum[0]) ? m_startspeed * m_unit : 
						 ((axisNum == m_axisSum[1]) ? m_startspeed2 * m_unit2 : 
						 ((axisNum == m_axisSum[2]) ? m_startspeed3 * m_unit3 : m_startspeed4 * m_unit4));
		m_sendData = _T("SVEL ") + strAxis + _T(" ") + CPublic::int2CString(startspeed);
		mainDlg->sendComm(m_sendData, port);

	}else if (CPublic::commCount == 2)
	{
		if (CPublic::bfindTerminator[port - 1] == false)
			return;

		if (CPublic::receiveData[port - 1] != m_sendData)
		{
			mainDlg->AddString(ERRO1);
			KillTimer(nIDEvent);
			openLoopComm(1);
			return;
		}
		//mainDlg->AddString(CPublic::receiveData[portNum1 - 1]);

		int targetspeed = (axisNum == m_axisSum[0]) ? m_targetspeed * m_unit : 
						((axisNum == m_axisSum[1]) ? m_targetspeed2 * m_unit2 : 
						((axisNum == m_axisSum[2]) ? m_targetspeed3 * m_unit3 :
						m_targetspeed4 * m_unit4));

		m_sendData = _T("TVEL ") + strAxis + _T(" ") + CPublic::int2CString(targetspeed);
		mainDlg->sendComm(m_sendData, port);


	}else if (CPublic::commCount == 3)
	{
		if (CPublic::bfindTerminator[port - 1] == false)
			return;

		if (CPublic::receiveData[port - 1] != m_sendData)
		{
			mainDlg->AddString(ERRO1);
			KillTimer(nIDEvent);
			openLoopComm(1);
			return;
		}
		//mainDlg->AddString(CPublic::receiveData[portNum1 - 1]);
		int accelspeed = (axisNum == m_axisSum[0]) ? m_accelspeed * m_unit : 
						 ((axisNum == m_axisSum[1]) ? m_accelspeed2 * m_unit2 : 
						 ((axisNum == m_axisSum[2]) ? m_accelspeed3 * m_unit3 :
						   m_accelspeed4 * m_unit4));

		m_sendData = _T("SACC ") + strAxis + _T(" ") + CPublic::int2CString(accelspeed);
		mainDlg->sendComm(m_sendData, port);

	}else if (CPublic::commCount == 4)
	{
		if (CPublic::bfindTerminator[port - 1] == false)
			return;

		if (CPublic::receiveData[port - 1] != m_sendData)
		{
			mainDlg->AddString(ERRO1);
			KillTimer(nIDEvent);
			openLoopComm(1);
			return;
		}

		//mainDlg->AddString(CPublic::receiveData[portNum1 - 1]);

		int steps = 0;
		if (axisNum == m_axisSum[0])
		{
			m_sendData = (m_absOrRel == 0) ?  _T("SMOV ") : _T("SMVR ");
			steps = m_steps * m_unit;
		}else if (axisNum == m_axisSum[1])
		{
			m_sendData = (m_absOrRel2 == 0) ?  _T("SMOV ") : _T("SMVR ");
			steps = m_steps2 * m_unit2;
		}else if (axisNum == m_axisSum[2])
		{
			m_sendData = (m_absOrRel3 == 0) ?  _T("SMOV ") : _T("SMVR ");
			steps = m_steps3 * m_unit3;
		}else
		{
			m_sendData = (m_absOrRel4 == 0) ?  _T("SMOV ") : _T("SMVR ");
			steps = m_steps4 * m_unit4;
		}

		m_sendData = m_sendData + strAxis + _T(" ") + CPublic::int2CString(steps);
		mainDlg->sendComm(m_sendData, port);
	}

	if (CPublic::commCount == 5)
	{
		if (CPublic::bfindTerminator[port - 1] == false)
			return;

		if (CPublic::receiveData[port - 1] != m_sendData)
		{
			mainDlg->AddString(ERRO1);
			KillTimer(nIDEvent);
			openLoopComm(1);
			return;
		}

		//mainDlg->AddString(CPublic::receiveData[portNum1 - 1]);
		KillTimer(nIDEvent);
		openLoopComm(1);
	}


	CPublic::commCount++;
}

void CDlgSerial3::openLoopComm(UINT_PTR nIDEvent)
{
	SetTimer(nIDEvent, loopTime, NULL);
	m_loopCommNum = 0;
	m_bLoop = true;
}


void CDlgSerial3::closeLoopComm(UINT_PTR nIDEvent)
{
	KillTimer(nIDEvent);
	m_bLoop = false;
}

void CDlgSerial3::settingComm(CString comm, int axisNum, int port)
{
	if(CPublic::portIsOpen[port - 1] == false)
	{
		mainDlg->AddString(_T("该串口未打开，请先打开串口！"));
		return;
	}

	closeLoopComm(1);
	if (axisNum == 0)
		m_sendData = comm;
	else
		m_sendData = comm + CPublic::int2CString(axisNum);

	mainDlg->sendComm(m_sendData, port);
	//Sleep(500);
	openLoopComm(1);
}

void CDlgSerial3::loopComm(int* axis, int port)
{
	if (m_bLoop == true)
	{
		UpdateData();
		
		if (m_loopCommNum == 0)
		{
			if (CPublic::bfindTerminator[port - 1] == false)
				return;
			mainDlg->sendComm(_T("POS? ") + CPublic::int2CString(axis[0]), port);		
		}

		if (m_loopCommNum == 1)
		{
			if (CPublic::bfindTerminator[port - 1] == false)
				return;
			SetDlgItemText(IDC_EDIT_absPostion, CPublic::receiveData[port - 1]);
			//SetDlgItemText(IDC_EDIT_absPostion2, explainPos(CPublic::receiveData[portNum1 - 1]));
			UpdateData(FALSE);

			mainDlg->sendComm(_T("LIM? ") + CPublic::int2CString(axis[0]), port);		
					

		}

		if (m_loopCommNum == 2)
		{
			if (CPublic::bfindTerminator[port - 1] == false)
				return;

			CString t = CPublic::receiveData[port - 1];

			switchLight(CPublic::explainLim(t, -1), CPublic::explainLim(t, 0),
				CPublic::explainLim(t, 1), CPublic::explainLim(t, 2));
			UpdateData(FALSE);	

			mainDlg->sendComm(_T("POS? ") + CPublic::int2CString(axis[1]), port);		

		}

		if (m_loopCommNum == 3)
		{
			if (CPublic::bfindTerminator[port - 1] == false)
				return;
			SetDlgItemText(IDC_EDIT_absPostion2, CPublic::receiveData[port - 1]);
			//SetDlgItemText(IDC_EDIT_absPostion2, explainPos(CPublic::receiveData[portNum1 - 1]));
			UpdateData(FALSE);

			mainDlg->sendComm(_T("LIM? ") + CPublic::int2CString(axis[1]), port);		

		}

		if (m_loopCommNum == 4)
		{
			if (CPublic::bfindTerminator[port - 1] == false)
				return;

			CString t = CPublic::receiveData[port - 1];

			switchLight(CPublic::explainLim(t, -1), CPublic::explainLim(t, 0),
				CPublic::explainLim(t, 1), CPublic::explainLim(t, 2));
			UpdateData(FALSE);	

			mainDlg->sendComm(_T("POS? ") + CPublic::int2CString(axis[2]), port);		

		}

		if (m_loopCommNum == 5)
		{
			if (CPublic::bfindTerminator[port - 1] == false)
				return;

			CString t = CPublic::receiveData[port - 1];

			SetDlgItemText(IDC_EDIT_absPostion3, CPublic::receiveData[port - 1]);
			//SetDlgItemText(IDC_EDIT_absPostion3, explainPos(CPublic::receiveData[port - 1]));
			UpdateData(FALSE);

			mainDlg->sendComm(_T("LIM? ") + CPublic::int2CString(axis[2]), port);		

		}

		if (m_loopCommNum == 6)
		{
			if (CPublic::bfindTerminator[port - 1] == false)
				return;

			CString t = CPublic::receiveData[port - 1];

			switchLight(CPublic::explainLim(t, -1), CPublic::explainLim(t, 0),
				CPublic::explainLim(t, 1), CPublic::explainLim(t, 2));
			UpdateData(FALSE);	

			mainDlg->sendComm(_T("POS? ") + CPublic::int2CString(axis[3]), port);		

		}

		if (m_loopCommNum == 7)
		{
			if (CPublic::bfindTerminator[port - 1] == false)
				return;

			CString t = CPublic::receiveData[port - 1];

			SetDlgItemText(IDC_EDIT_absPostion4, CPublic::receiveData[port - 1]);
			//SetDlgItemText(IDC_EDIT_absPostion3, explainPos(CPublic::receiveData[port - 1]));
			UpdateData(FALSE);

			mainDlg->sendComm(_T("LIM? ") + CPublic::int2CString(axis[3]), port);		

		}

		if (m_loopCommNum == 8)
		{
			if (CPublic::bfindTerminator[port - 1] == false)
				return;

			CString t = CPublic::receiveData[port - 1];

			switchLight(CPublic::explainLim(t, -1), CPublic::explainLim(t, 0),
				CPublic::explainLim(t, 1), CPublic::explainLim(t, 2));
			UpdateData(FALSE);	

			m_loopCommNum = 0;
			return;
		}


		m_loopCommNum++;


	}	
}

void CDlgSerial3::switchLight(int neg, int zero, int pos, int axisNum)
{
	if (axisNum == m_axisSum[0])
	{
		if (pos == 1)
			m_bstplusLight.SetIcon(IDI_ICON_green24);
		else
			m_bstplusLight.SetIcon(IDI_ICON_Cgrey24);

		if (zero == 1)
			m_bstzeroLight.SetIcon(IDI_ICON_green24);
		else
			m_bstzeroLight.SetIcon(IDI_ICON_Cgrey24);

		if (neg == 1)
			m_bstminusLight.SetIcon(IDI_ICON_green24);
		else
			m_bstminusLight.SetIcon(IDI_ICON_Cgrey24);

	}else if (axisNum == m_axisSum[1])
	{
		if (pos == 1)
			m_bstplusLight2.SetIcon(IDI_ICON_green24);
		else
			m_bstplusLight2.SetIcon(IDI_ICON_Cgrey24);

		if (zero == 1)
			m_bstzeroLight2.SetIcon(IDI_ICON_green24);
		else
			m_bstzeroLight2.SetIcon(IDI_ICON_Cgrey24);

		if (neg == 1)
			m_bstminusLight2.SetIcon(IDI_ICON_green24);
		else
			m_bstminusLight2.SetIcon(IDI_ICON_Cgrey24);
	}else if (axisNum == m_axisSum[2])
	{
		if (pos == 1)
			m_bstplusLight3.SetIcon(IDI_ICON_green24);
		else
			m_bstplusLight3.SetIcon(IDI_ICON_Cgrey24);

		if (zero == 1)
			m_bstzeroLight3.SetIcon(IDI_ICON_green24);
		else
			m_bstzeroLight3.SetIcon(IDI_ICON_Cgrey24);

		if (neg == 1)
			m_bstminusLight3.SetIcon(IDI_ICON_green24);
		else
			m_bstminusLight3.SetIcon(IDI_ICON_Cgrey24);
		
	}else if (axisNum == m_axisSum[3])
	{
		if (pos == 1)
			m_bstplusLight4.SetIcon(IDI_ICON_green24);
		else
			m_bstplusLight4.SetIcon(IDI_ICON_Cgrey24);

		if (zero == 1)
			m_bstzeroLight4.SetIcon(IDI_ICON_green24);
		else
			m_bstzeroLight4.SetIcon(IDI_ICON_Cgrey24);

		if (neg == 1)
			m_bstminusLight4.SetIcon(IDI_ICON_green24);
		else
			m_bstminusLight4.SetIcon(IDI_ICON_Cgrey24);

	}
}

void CDlgSerial3::makeJOG(int sign, int axisNum, int port)
{
	if (sign == -1)
	{
		settingComm(_T("FFNL "), axisNum, port);
	}else if (sign == 1)
	{
		settingComm(_T("FFPL "), axisNum, port);
	}else if (sign == 0)
	{
		settingComm(_T("STOP "), axisNum, port);
	}

}


void CDlgSerial3::OnBnClickedButtonstart()
{
	UpdateData();

	if(CPublic::portIsOpen[m_port - 1] == false)
	{
		mainDlg->AddString(_T("该串口未打开，请先打开串口！"));
		return;
	}

	closeLoopComm(1);
	CPublic::commCount = 0;
	SetTimer(2, startTime, NULL);
}

void CDlgSerial3::OnBnClickedButtonstart2()
{
	UpdateData();

	if(CPublic::portIsOpen[m_port - 1] == false)
	{
		mainDlg->AddString(_T("该串口未打开，请先打开串口！"));
		return;
	}

	closeLoopComm(1);
	CPublic::commCount = 0;
	SetTimer(3, startTime, NULL);
}

void CDlgSerial3::OnBnClickedButtonstart3()
{
	UpdateData();

	if(CPublic::portIsOpen[m_port - 1] == false)
	{
		mainDlg->AddString(_T("该串口未打开，请先打开串口！"));
		return;
	}

	closeLoopComm(1);
	CPublic::commCount = 0;
	SetTimer(4, startTime, NULL);
}

void CDlgSerial3::OnBnClickedButtonstart4()
{
	UpdateData();

	if(CPublic::portIsOpen[m_port - 1] == false)
	{
		mainDlg->AddString(_T("该串口未打开，请先打开串口！"));
		return;
	}

	closeLoopComm(1);
	CPublic::commCount = 0;
	SetTimer(5, startTime, NULL);
}

void CDlgSerial3::OnBnClickedButtonstop()
{
	settingComm(_T("STOP "), m_axisSum[0], m_port);

}

void CDlgSerial3::OnBnClickedButtonstop2()
{
	settingComm(_T("STOP "), m_axisSum[1], m_port);

}

void CDlgSerial3::OnBnClickedButtonstop3()
{
	settingComm(_T("STOP "), m_axisSum[2], m_port);

}

void CDlgSerial3::OnBnClickedButtonstop4()
{
	settingComm(_T("STOP "), m_axisSum[3], m_port);

}

void CDlgSerial3::OnBnClickedButtonpluslimit3()
{
	settingComm(_T("FFPL "), m_axisSum[2], m_port);

}

void CDlgSerial3::OnBnClickedButtonpluslimit4()
{
	settingComm(_T("FFPL "), m_axisSum[3], m_port);

}

void CDlgSerial3::OnBnClickedButtonpluslimit()
{
	settingComm(_T("FFPL "), m_axisSum[0], m_port);

}

void CDlgSerial3::OnBnClickedButtonpluslimit2()
{
	settingComm(_T("FFPL "), m_axisSum[1], m_port);

}

void CDlgSerial3::OnBnClickedButtonzeroswitch()
{
	settingComm(_T("FFRL "), m_axisSum[0], m_port);

}

void CDlgSerial3::OnBnClickedButtonzeroswitch2()
{
	settingComm(_T("FFRL "), m_axisSum[1], m_port);

}

void CDlgSerial3::OnBnClickedButtonzeroswitch3()
{
	settingComm(_T("FFRL "), m_axisSum[2], m_port);

}

void CDlgSerial3::OnBnClickedButtonzeroswitch4()
{
	settingComm(_T("FFRL "), m_axisSum[3], m_port);

}

void CDlgSerial3::OnBnClickedButtonminuslimit()
{
	settingComm(_T("FFNL "), m_axisSum[0], m_port);

}

void CDlgSerial3::OnBnClickedButtonminuslimit2()
{
	settingComm(_T("FFNL "), m_axisSum[1], m_port);

}

void CDlgSerial3::OnBnClickedButtonminuslimit3()
{
	settingComm(_T("FFNL "), m_axisSum[2], m_port);

}

void CDlgSerial3::OnBnClickedButtonminuslimit4()
{
	settingComm(_T("FFNL "), m_axisSum[3], m_port);

}

void CDlgSerial3::OnBnClickedButtonabszero()
{
	settingComm(_T("DHOM "), m_axisSum[0], m_port);

}

void CDlgSerial3::OnBnClickedButtonabszero2()
{
	settingComm(_T("DHOM "), m_axisSum[1], m_port);

}

void CDlgSerial3::OnBnClickedButtonabszero3()
{
	settingComm(_T("DHOM "), m_axisSum[2], m_port);

}

void CDlgSerial3::OnBnClickedButtonabszero4()
{
	settingComm(_T("DHOM "), m_axisSum[3], m_port);

}

void CDlgSerial3::OnBnClickedButtonfindzero()
{
	settingComm(_T("GHOM "), m_axisSum[0], m_port);

}

void CDlgSerial3::OnBnClickedButtonfindzero2()
{
	settingComm(_T("GHOM "), m_axisSum[1], m_port);

}

void CDlgSerial3::OnBnClickedButtonfindzero3()
{
	settingComm(_T("GHOM "), m_axisSum[2], m_port);

}

void CDlgSerial3::OnBnClickedButtonfindzero4()
{
	settingComm(_T("GHOM "), m_axisSum[3], m_port);

}

void CDlgSerial3::OnCbnSelchangeCombounit6()
{
	if (m_cmbUnitX.GetCurSel() == 0)
	{
		((CStatic*)GetDlgItem(IDC_STATIC_start6))->SetWindowText(_T("(counts/s)"));
		((CStatic*)GetDlgItem(IDC_STATIC_target6))->SetWindowText(_T("(counts/s)"));
		((CStatic*)GetDlgItem(IDC_STATIC_accel6))->SetWindowText(_T("(counts/s2)"));
		((CStatic*)GetDlgItem(IDC_STATIC_steps6))->SetWindowText(_T("(counts)"));
	}else if ((m_cmbUnitX.GetCurSel() == 1))
	{

		((CStatic*)GetDlgItem(IDC_STATIC_start6))->SetWindowText(_T("(mm/s)"));
		((CStatic*)GetDlgItem(IDC_STATIC_target6))->SetWindowText(_T("(mm/s)"));
		((CStatic*)GetDlgItem(IDC_STATIC_accel6))->SetWindowText(_T("(mm/s2)"));
		((CStatic*)GetDlgItem(IDC_STATIC_steps6))->SetWindowText(_T("(mm)"));

	}else if ((m_cmbUnitX.GetCurSel() == 2))
	{

		((CStatic*)GetDlgItem(IDC_STATIC_start6))->SetWindowText(_T("(deg/s)"));
		((CStatic*)GetDlgItem(IDC_STATIC_target6))->SetWindowText(_T("(deg/s)"));
		((CStatic*)GetDlgItem(IDC_STATIC_accel6))->SetWindowText(_T("(deg/s2)"));
		((CStatic*)GetDlgItem(IDC_STATIC_steps6))->SetWindowText(_T("(deg)"));

	}
}

void CDlgSerial3::OnCbnSelchangeCombounit7()
{
	if (m_cmbUnitX2.GetCurSel() == 0)
	{
		((CStatic*)GetDlgItem(IDC_STATIC_start7))->SetWindowText(_T("(counts/s)"));
		((CStatic*)GetDlgItem(IDC_STATIC_target7))->SetWindowText(_T("(counts/s)"));
		((CStatic*)GetDlgItem(IDC_STATIC_accel7))->SetWindowText(_T("(counts/s2)"));
		((CStatic*)GetDlgItem(IDC_STATIC_steps7))->SetWindowText(_T("(counts)"));
	}else if ((m_cmbUnitX2.GetCurSel() == 1))
	{

		((CStatic*)GetDlgItem(IDC_STATIC_start7))->SetWindowText(_T("(mm/s)"));
		((CStatic*)GetDlgItem(IDC_STATIC_target7))->SetWindowText(_T("(mm/s)"));
		((CStatic*)GetDlgItem(IDC_STATIC_accel7))->SetWindowText(_T("(mm/s2)"));
		((CStatic*)GetDlgItem(IDC_STATIC_steps7))->SetWindowText(_T("(mm)"));

	}else if ((m_cmbUnitX2.GetCurSel() == 2))
	{

		((CStatic*)GetDlgItem(IDC_STATIC_start7))->SetWindowText(_T("(deg/s)"));
		((CStatic*)GetDlgItem(IDC_STATIC_target7))->SetWindowText(_T("(deg/s)"));
		((CStatic*)GetDlgItem(IDC_STATIC_accel7))->SetWindowText(_T("(deg/s2)"));
		((CStatic*)GetDlgItem(IDC_STATIC_steps7))->SetWindowText(_T("(deg)"));

	}
}

void CDlgSerial3::OnCbnSelchangeCombounit8()
{
	if (m_cmbUnitX3.GetCurSel() == 0)
	{
		((CStatic*)GetDlgItem(IDC_STATIC_start8))->SetWindowText(_T("(counts/s)"));
		((CStatic*)GetDlgItem(IDC_STATIC_target8))->SetWindowText(_T("(counts/s)"));
		((CStatic*)GetDlgItem(IDC_STATIC_accel8))->SetWindowText(_T("(counts/s2)"));
		((CStatic*)GetDlgItem(IDC_STATIC_steps8))->SetWindowText(_T("(counts)"));
	}else if ((m_cmbUnitX3.GetCurSel() == 1))
	{

		((CStatic*)GetDlgItem(IDC_STATIC_start8))->SetWindowText(_T("(mm/s)"));
		((CStatic*)GetDlgItem(IDC_STATIC_target8))->SetWindowText(_T("(mm/s)"));
		((CStatic*)GetDlgItem(IDC_STATIC_accel8))->SetWindowText(_T("(mm/s2)"));
		((CStatic*)GetDlgItem(IDC_STATIC_steps8))->SetWindowText(_T("(mm)"));

	}else if ((m_cmbUnitX3.GetCurSel() == 2))
	{

		((CStatic*)GetDlgItem(IDC_STATIC_start8))->SetWindowText(_T("(deg/s)"));
		((CStatic*)GetDlgItem(IDC_STATIC_target8))->SetWindowText(_T("(deg/s)"));
		((CStatic*)GetDlgItem(IDC_STATIC_accel8))->SetWindowText(_T("(deg/s2)"));
		((CStatic*)GetDlgItem(IDC_STATIC_steps8))->SetWindowText(_T("(deg)"));

	}
}

void CDlgSerial3::OnCbnSelchangeCombounit9()
{
	if (m_cmbUnitX4.GetCurSel() == 0)
	{
		((CStatic*)GetDlgItem(IDC_STATIC_start9))->SetWindowText(_T("(counts/s)"));
		((CStatic*)GetDlgItem(IDC_STATIC_target9))->SetWindowText(_T("(counts/s)"));
		((CStatic*)GetDlgItem(IDC_STATIC_accel9))->SetWindowText(_T("(counts/s2)"));
		((CStatic*)GetDlgItem(IDC_STATIC_steps9))->SetWindowText(_T("(counts)"));
	}else if ((m_cmbUnitX4.GetCurSel() == 1))
	{

		((CStatic*)GetDlgItem(IDC_STATIC_start9))->SetWindowText(_T("(mm/s)"));
		((CStatic*)GetDlgItem(IDC_STATIC_target9))->SetWindowText(_T("(mm/s)"));
		((CStatic*)GetDlgItem(IDC_STATIC_accel9))->SetWindowText(_T("(mm/s2)"));
		((CStatic*)GetDlgItem(IDC_STATIC_steps9))->SetWindowText(_T("(mm)"));

	}else if ((m_cmbUnitX4.GetCurSel() == 2))
	{

		((CStatic*)GetDlgItem(IDC_STATIC_start))->SetWindowText(_T("(deg/s)"));
		((CStatic*)GetDlgItem(IDC_STATIC_target))->SetWindowText(_T("(deg/s)"));
		((CStatic*)GetDlgItem(IDC_STATIC_accel))->SetWindowText(_T("(deg/s2)"));
		((CStatic*)GetDlgItem(IDC_STATIC_steps))->SetWindowText(_T("(deg)"));

	}
}

void CDlgSerial3::OnEnSetfocusEditunit6()
{
	if (m_bLoop == true)
	{
		closeLoopComm(1);
	}
}

void CDlgSerial3::OnEnSetfocusEditunit7()
{
	if (m_bLoop == true)
	{
		closeLoopComm(1);
	}
}

void CDlgSerial3::OnEnSetfocusEditstartspeed()
{
	if (m_bLoop == true)
	{
		closeLoopComm(1);
	}
}

void CDlgSerial3::OnEnSetfocusEdittargetspeed()
{
	if (m_bLoop == true)
	{
		closeLoopComm(1);
	}
}

void CDlgSerial3::OnEnSetfocusEditaccelspeed()
{
	if (m_bLoop == true)
	{
		closeLoopComm(1);
	}
}

void CDlgSerial3::OnEnSetfocusEditsteps()
{
	if (m_bLoop == true)
	{
		closeLoopComm(1);
	}
}

void CDlgSerial3::OnEnSetfocusEditstartspeed2()
{
	if (m_bLoop == true)
	{
		closeLoopComm(1);
	}
}

void CDlgSerial3::OnEnSetfocusEdittargetspeed2()
{
	if (m_bLoop == true)
	{
		closeLoopComm(1);
	}
}

void CDlgSerial3::OnEnSetfocusEditaccelspeed2()
{
	if (m_bLoop == true)
	{
		closeLoopComm(1);
	}
}

void CDlgSerial3::OnEnSetfocusEditsteps2()
{
	if (m_bLoop == true)
	{
		closeLoopComm(1);
	}
}

void CDlgSerial3::OnEnSetfocusEditstartspeed3()
{
	if (m_bLoop == true)
	{
		closeLoopComm(1);
	}
}

void CDlgSerial3::OnEnSetfocusEdittargetspeed3()
{
	if (m_bLoop == true)
	{
		closeLoopComm(1);
	}
}

void CDlgSerial3::OnEnSetfocusEditaccelspeed3()
{
	if (m_bLoop == true)
	{
		closeLoopComm(1);
	}
}

void CDlgSerial3::OnEnSetfocusEditsteps3()
{
	if (m_bLoop == true)
	{
		closeLoopComm(1);
	}
}

void CDlgSerial3::OnEnSetfocusEditunit8()
{
	if (m_bLoop == true)
	{
		closeLoopComm(1);
	}
}

void CDlgSerial3::OnEnSetfocusEditstartspeed4()
{
	if (m_bLoop == true)
	{
		closeLoopComm(1);
	}
}

void CDlgSerial3::OnEnSetfocusEdittargetspeed4()
{
	if (m_bLoop == true)
	{
		closeLoopComm(1);
	}
}

void CDlgSerial3::OnEnSetfocusEditaccelspeed4()
{
	if (m_bLoop == true)
	{
		closeLoopComm(1);
	}
}

void CDlgSerial3::OnEnSetfocusEditsteps4()
{
	if (m_bLoop == true)
	{
		closeLoopComm(1);
	}
}

void CDlgSerial3::OnEnSetfocusEditunit9()
{
	if (m_bLoop == true)
	{
		closeLoopComm(1);
	}
}

void CDlgSerial3::OnBnClickedRadioabsposition6()
{
	if (m_bLoop == true)
		closeLoopComm(1);

	m_absOrRel = 0;
	UpdateData(FALSE);

	if (m_bLoop == false)
		openLoopComm(1);
}

void CDlgSerial3::OnBnClickedRadiorelposition6()
{
	if (m_bLoop == true)
		closeLoopComm(1);

	m_absOrRel = 1;
	UpdateData(FALSE);

	if (m_bLoop == false)
		openLoopComm(1);
}

void CDlgSerial3::OnBnClickedRadioabsposition7()
{
	if (m_bLoop == true)
		closeLoopComm(1);

	m_absOrRel2 = 0;
	UpdateData(FALSE);

	if (m_bLoop == false)
		openLoopComm(1);
}

void CDlgSerial3::OnBnClickedRadiorelposition7()
{
	if (m_bLoop == true)
		closeLoopComm(1);

	m_absOrRel2 = 1;
	UpdateData(FALSE);

	if (m_bLoop == false)
		openLoopComm(1);
}

void CDlgSerial3::OnBnClickedRadioabsposition8()
{
	if (m_bLoop == true)
		closeLoopComm(1);

	m_absOrRel3 = 0;
	UpdateData(FALSE);

	if (m_bLoop == false)
		openLoopComm(1);
}

void CDlgSerial3::OnBnClickedRadiorelposition8()
{
	if (m_bLoop == true)
		closeLoopComm(1);

	m_absOrRel3 = 1;
	UpdateData(FALSE);

	if (m_bLoop == false)
		openLoopComm(1);
}

void CDlgSerial3::OnBnClickedRadioabsposition9()
{
	if (m_bLoop == true)
		closeLoopComm(1);

	m_absOrRel4 = 0;
	UpdateData(FALSE);

	if (m_bLoop == false)
		openLoopComm(1);
}

void CDlgSerial3::OnBnClickedRadiorelposition9()
{
	if (m_bLoop == true)
		closeLoopComm(1);

	m_absOrRel4 = 1;
	UpdateData(FALSE);

	if (m_bLoop == false)
		openLoopComm(1);
}

void CDlgSerial3::OnBnClickedButtonsave3()
{
	UpdateData();
	int axis[4] = {m_axisSum[0] - 1, m_axisSum[1] - 1, m_axisSum[2] - 1, m_axisSum[3] - 1};
	AxisParameter para[4];

	para[0].mode = m_ctrlMode.GetCurSel();
	para[0].startSpeed = m_startspeed;
	para[0].targetSpeed = m_targetspeed;
	para[0].accelSpeed = m_accelspeed;
	para[0].steps = m_steps;

	para[1].mode = m_ctrlMode2.GetCurSel();
	para[1].startSpeed = m_startspeed2;
	para[1].targetSpeed = m_targetspeed2;
	para[1].accelSpeed = m_accelspeed2;
	para[1].steps = m_steps2;

	para[2].mode = m_ctrlMode3.GetCurSel();
	para[2].startSpeed = m_startspeed3;
	para[2].targetSpeed = m_targetspeed3;
	para[2].accelSpeed = m_accelspeed3;
	para[2].steps = m_steps3;

	para[3].mode = m_ctrlMode4.GetCurSel();
	para[3].startSpeed = m_startspeed4;
	para[3].targetSpeed = m_targetspeed4;
	para[3].accelSpeed = m_accelspeed4;
	para[3].steps = m_steps4;

	mainDlg->updateAxisParameter2Value(para, axis, 4, true);
	mainDlg->updateValue2File(axis, 4, true);
}

void CDlgSerial3::setPara(void)
{
	m_ctrlMode.SetCurSel(CPublic::g_parameter[m_axisSum[0] - 1].mode);
	m_startspeed = CPublic::g_parameter[m_axisSum[0] - 1].startSpeed;
	m_targetspeed = CPublic::g_parameter[m_axisSum[0] - 1].targetSpeed;
	m_accelspeed = CPublic::g_parameter[m_axisSum[0] - 1].accelSpeed;
	m_steps = CPublic::g_parameter[m_axisSum[0] - 1].steps;

	m_ctrlMode2.SetCurSel(CPublic::g_parameter[m_axisSum[1] - 1].mode);
	m_startspeed2 = CPublic::g_parameter[m_axisSum[1] - 1].startSpeed;
	m_targetspeed2 = CPublic::g_parameter[m_axisSum[1] - 1].targetSpeed;
	m_accelspeed2 = CPublic::g_parameter[m_axisSum[1] - 1].accelSpeed;
	m_steps2 = CPublic::g_parameter[m_axisSum[1] - 1].steps;

	m_ctrlMode3.SetCurSel(CPublic::g_parameter[m_axisSum[2] - 1].mode);
	m_startspeed3 = CPublic::g_parameter[m_axisSum[2] - 1].startSpeed;
	m_targetspeed3 = CPublic::g_parameter[m_axisSum[2] - 1].targetSpeed;
	m_accelspeed3 = CPublic::g_parameter[m_axisSum[2] - 1].accelSpeed;
	m_steps3 = CPublic::g_parameter[m_axisSum[2] - 1].steps;

	m_ctrlMode4.SetCurSel(CPublic::g_parameter[m_axisSum[3] - 1].mode);
	m_startspeed4 = CPublic::g_parameter[m_axisSum[3] - 1].startSpeed;
	m_targetspeed4 = CPublic::g_parameter[m_axisSum[3] - 1].targetSpeed;
	m_accelspeed4 = CPublic::g_parameter[m_axisSum[3] - 1].accelSpeed;
	m_steps4 = CPublic::g_parameter[m_axisSum[3] - 1].steps;

	UpdateData(FALSE);


}

void CDlgSerial3::OnBnClickedButtondefault3()
{
	m_ctrlMode.SetCurSel(0);
	m_startspeed = 5000;
	m_targetspeed = 100000;
	m_accelspeed = 50000;
	m_steps = 0;

	m_ctrlMode2.SetCurSel(0);
	m_startspeed2 = 5000;
	m_targetspeed2 = 100000;
	m_accelspeed2 = 50000;
	m_steps2 = 0;

	m_ctrlMode3.SetCurSel(0);
	m_startspeed3 = 5000;
	m_targetspeed3 = 100000;
	m_accelspeed3 = 50000;
	m_steps3 = 0;

	m_ctrlMode4.SetCurSel(0);
	m_startspeed4 = 5000;
	m_targetspeed4 = 100000;
	m_accelspeed4 = 50000;
	m_steps4 = 0;


	UpdateData(FALSE);
}

void CDlgSerial3::OnBnClickedButtonopenup()
{
	if (CPublic::g_buplight == false)
	{
		settingComm(_T("SOUP 1 "), CPublic::g_iLight | 0x01, m_port);
		((CButton*)GetDlgItem(IDC_BUTTON_openup))->SetWindowText(_T("关上光源"));
		CPublic::g_buplight = true;

	}else
	{
		settingComm(_T("SOUP 1 "), CPublic::g_iLight & 0xFFFFFFFE, m_port);
		((CButton*)GetDlgItem(IDC_BUTTON_openup))->SetWindowText(_T("开上光源"));
		CPublic::g_buplight = false;
	}

}

void CDlgSerial3::OnBnClickedButtonopendown()
{
	if (CPublic::g_bdownlight == false)
	{
		settingComm(_T("SOUP 1 "), CPublic::g_iLight | 0x02, m_port);
		((CButton*)GetDlgItem(IDC_BUTTON_opendown))->SetWindowText(_T("关下光源"));
		CPublic::g_bdownlight = true;

	}else
	{
		settingComm(_T("SOUP 1 "), CPublic::g_iLight & 0xFFFFFFFD, m_port);
		((CButton*)GetDlgItem(IDC_BUTTON_opendown))->SetWindowText(_T("开下光源"));
		CPublic::g_bdownlight = false;
	}
}

void CDlgSerial3::OnBnClickedButtoninhale()
{
	if (CPublic::g_bInhale1 == false)
	{
		settingComm(_T("SOUP 1 "), CPublic::g_iInhale | 0x08, m_port);
		((CButton*)GetDlgItem(IDC_BUTTON_inhale))->SetWindowText(_T("1号吸附头吸气"));
		CPublic::g_bInhale1 = true;

	}else
	{
		settingComm(_T("SOUP 1 "), CPublic::g_iInhale & 0xFFFFFFF7, m_port);
		((CButton*)GetDlgItem(IDC_BUTTON_inhale))->SetWindowText(_T("1号吸附头松气"));
		CPublic::g_bInhale1 = false;
	}
}

void CDlgSerial3::OnBnClickedButtoninhale2()
{
	if (CPublic::g_bInhale2 == false)
	{
		settingComm(_T("SOUP 1 "), CPublic::g_iInhale | 0x00000010, m_port);
		((CButton*)GetDlgItem(IDC_BUTTON_inhale2))->SetWindowText(_T("1号吸附头吸气"));
		CPublic::g_bInhale2 = true;

	}else
	{
		settingComm(_T("SOUP 1 "), CPublic::g_iInhale & 0xFFFFFFEF, m_port);
		((CButton*)GetDlgItem(IDC_BUTTON_inhale2))->SetWindowText(_T("1号吸附头松气"));
		CPublic::g_bInhale2 = false;
	}
}

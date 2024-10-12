// DlgSerial5.cpp : implementation file
//

#include "stdafx.h"
#include "controlSerialNetPort.h"
#include "DlgSerial5.h"



// CDlgSerial5 dialog
extern CcontrolSerialNetPortDlg* mainDlg;

IMPLEMENT_DYNAMIC(CDlgSerial5, CDialog)

CDlgSerial5::CDlgSerial5(CWnd* pParent, int* port, int* axisNum, CString dlgName)
	: CDialog(CDlgSerial5::IDD, pParent)
	, m_startspeed(5000)
	, m_targetspeed(100000)
	, m_accelspeed(50000)
	, m_steps(0)
	, m_startspeed2(5000)
	, m_targetspeed2(100000)
	, m_accelspeed2(50000)
	, m_steps2(0)
	//, m_startspeed3(0)
	, m_targetspeed3(100)
	, m_accelspeed3(50)
	, m_steps3(0)
	,m_sendData(_T(""))
	,m_loopCommNum(0)
	,m_bLoop(true)
	,m_unit(1)
	,m_unit2(1)
	//,m_unit3(1)
	,m_absOrRel(0)
	,m_absOrRel2(0)
	//,m_absOrRel3(0)
{
	m_port[0] = port[0];
	m_port[1] = port[1];
	m_axis[0] = axisNum[0];
	m_axis[1] = axisNum[1];
	m_axis[2] = axisNum[2];

	m_strDlgName = dlgName;


}

CDlgSerial5::~CDlgSerial5()
{
}

void CDlgSerial5::DoDataExchange(CDataExchange* pDX)
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
	//DDX_Text(pDX, IDC_EDIT_startSpeed3, m_startspeed3);
	DDX_Text(pDX, IDC_EDIT_targetSpeed3, m_targetspeed3);
	DDX_Text(pDX, IDC_EDIT_accelspeed3, m_accelspeed3);
	DDX_Text(pDX, IDC_EDIT_steps3, m_steps3);
	DDX_Control(pDX, IDC_COMBO_MODE, m_ctrlMode);
	DDX_Control(pDX, IDC_COMBO_MODE2, m_ctrlMode2);
	DDX_Control(pDX, IDC_COMBO_MODE3, m_ctrlMode3);

	DDX_Radio(pDX, IDC_RADIO_absPosition3, m_absOrRel);
	DDX_Radio(pDX, IDC_RADIO_absPosition4, m_absOrRel2);
	//DDX_Radio(pDX, IDC_RADIO_absPosition5, m_absOrRel3);
	DDX_Control(pDX, IDC_COMBO_unit3, m_cmbUnitX);
	DDX_Control(pDX, IDC_COMBO_unit4, m_cmbUnitX2);
	//DDX_Control(pDX, IDC_COMBO_unit5, m_cmbUnitX3);
	DDX_Text(pDX, IDC_EDIT_unit3, m_unit);
	DDX_Text(pDX, IDC_EDIT_unit4, m_unit2);
	//DDX_Text(pDX, IDC_EDIT_unit5, m_unit3);

	DDX_Control(pDX, IDC_BUTTON_plusLight, m_bstplusLight);
	DDX_Control(pDX, IDC_BUTTON_zeroLight, m_bstzeroLight);
	DDX_Control(pDX, IDC_BUTTON_minusLight, m_bstminusLight);
	DDX_Control(pDX, IDC_BUTTON_plusLight2, m_bstplusLight2);
	DDX_Control(pDX, IDC_BUTTON_zeroLight2, m_bstzeroLight2);
	DDX_Control(pDX, IDC_BUTTON_minusLight2, m_bstminusLight2);

	DDX_Control(pDX, IDC_BUTTON_save5, m_bstsave);
	DDX_Control(pDX, IDC_BUTTON_default5, m_bstdefault);


	//DDX_Control(pDX, IDC_BUTTON_plusLight3, m_bstplusLight3);
	//DDX_Control(pDX, IDC_BUTTON_zeroLight3, m_bstzeroLight3);
	//DDX_Control(pDX, IDC_BUTTON_minusLight3, m_bstminusLight3);
}


BEGIN_MESSAGE_MAP(CDlgSerial5, CDialog)
	ON_WM_TIMER()
	ON_CBN_SELCHANGE(IDC_COMBO_unit3, &CDlgSerial5::OnCbnSelchangeCombounit3)
	ON_CBN_SELCHANGE(IDC_COMBO_unit4, &CDlgSerial5::OnCbnSelchangeCombounit4)
	//ON_CBN_SELCHANGE(IDC_COMBO_unit5, &CDlgSerial5::OnCbnSelchangeCombounit5)
	ON_BN_CLICKED(IDC_BUTTON_start, &CDlgSerial5::OnBnClickedButtonstart)
	ON_BN_CLICKED(IDC_BUTTON_start2, &CDlgSerial5::OnBnClickedButtonstart2)
	ON_BN_CLICKED(IDC_BUTTON_start3, &CDlgSerial5::OnBnClickedButtonstart3)
	ON_BN_CLICKED(IDC_BUTTON_stop, &CDlgSerial5::OnBnClickedButtonstop)
	ON_BN_CLICKED(IDC_BUTTON_stop2, &CDlgSerial5::OnBnClickedButtonstop2)
	ON_BN_CLICKED(IDC_BUTTON_stop3, &CDlgSerial5::OnBnClickedButtonstop3)
	ON_BN_CLICKED(IDC_BUTTON_plusLimit, &CDlgSerial5::OnBnClickedButtonpluslimit)
	ON_BN_CLICKED(IDC_BUTTON_plusLimit2, &CDlgSerial5::OnBnClickedButtonpluslimit2)
	ON_BN_CLICKED(IDC_BUTTON_ENABLE, &CDlgSerial5::OnBnClickedButtonenable)
	ON_BN_CLICKED(IDC_BUTTON_zeroSwitch, &CDlgSerial5::OnBnClickedButtonzeroswitch)
	ON_BN_CLICKED(IDC_BUTTON_zeroSwitch2, &CDlgSerial5::OnBnClickedButtonzeroswitch2)
	//ON_BN_CLICKED(IDC_BUTTON_zeroSwitch3, &CDlgSerial5::OnBnClickedButtonzeroswitch3)
	ON_BN_CLICKED(IDC_BUTTON_minusLimit, &CDlgSerial5::OnBnClickedButtonminuslimit)
	ON_BN_CLICKED(IDC_BUTTON_minusLimit2, &CDlgSerial5::OnBnClickedButtonminuslimit2)
	//ON_BN_CLICKED(IDC_BUTTON_minusLimit3, &CDlgSerial5::OnBnClickedButtonminuslimit3)
	ON_BN_CLICKED(IDC_BUTTON_absZero, &CDlgSerial5::OnBnClickedButtonabszero)
	ON_BN_CLICKED(IDC_BUTTON_absZero2, &CDlgSerial5::OnBnClickedButtonabszero2)
	//ON_BN_CLICKED(IDC_BUTTON_absZero3, &CDlgSerial5::OnBnClickedButtonabszero3)
	ON_BN_CLICKED(IDC_BUTTON_findZero, &CDlgSerial5::OnBnClickedButtonfindzero)
	ON_BN_CLICKED(IDC_BUTTON_findZero2, &CDlgSerial5::OnBnClickedButtonfindzero2)
	ON_BN_CLICKED(IDC_BUTTON_findZero3, &CDlgSerial5::OnBnClickedButtonfindzero3)
	ON_BN_CLICKED(IDC_BUTTON_save5, &CDlgSerial5::OnBnClickedButtonsave5)
	ON_BN_CLICKED(IDC_BUTTON_default5, &CDlgSerial5::OnBnClickedButtondefault5)
END_MESSAGE_MAP()


// CDlgSerial5 message handlers

BOOL CDlgSerial5::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	InitUI();
	SetWindowText(m_strDlgName);


	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgSerial5::InitUI(void)
{
	//轴1
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_startSpeed))->SetRange32(0,0x7fffffff);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_targetspeed))->SetRange32(0,0x7fffffff);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_accelspeed))->SetRange32(0,0x7fffffff);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_steps))->SetRange32(0xffffffff,0x7fffffff);

	m_ctrlMode.SetCurSel(0);
	m_cmbUnitX.SetCurSel(0);
	//m_unit = 1;

	//轴2
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_startSpeed2))->SetRange32(0,0x7fffffff);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_targetspeed2))->SetRange32(0,0x7fffffff);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_accelspeed2))->SetRange32(0,0x7fffffff);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_steps2))->SetRange32(0xffffffff,0x7fffffff);

	m_ctrlMode2.SetCurSel(0);
	m_cmbUnitX2.SetCurSel(0);
	//m_unit2 = 1;

	//轴3
	//((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_startSpeed3))->SetRange32(0,0x7fffffff);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_targetspeed3))->SetRange32(0,0x7fffffff);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_accelspeed3))->SetRange32(0,0x7fffffff);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_steps3))->SetRange32(0xffffffff,0x7fffffff);

	m_ctrlMode3.SetCurSel(0);
	//m_cmbUnitX3.SetCurSel(0);
	//m_unit3 = 1;
	//m_absOrRel3 = 0;



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

	m_bstsave.SetIcon(IDI_ICON_save32);
	m_bstsave.SetTooltipText(_T("保存配置"));
	m_bstdefault.SetIcon(IDI_ICON_default32);
	m_bstdefault.SetTooltipText(_T("设置默认值"));

	//m_bstplusLight3.SetIcon(IDI_ICON_Cgrey24);
	//m_bstzeroLight3.SetIcon(IDI_ICON_Cgrey24);
	//m_bstminusLight3.SetIcon(IDI_ICON_Cgrey24);

	//m_bstplusLight3.DrawBorder(FALSE);
	//m_bstzeroLight3.DrawBorder(FALSE);
	//m_bstminusLight3.DrawBorder(FALSE);
	setPara();

	SetTimer(1, loopTime, NULL);


}

void CDlgSerial5::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	switch(nIDEvent)
	{

	case 1:

		loopComm(m_axis, m_port);		
		break;

	case 2:
		start(nIDEvent, &m_ctrlMode, m_axis[0], m_port[0]);
		break;


	case 3:
		start(nIDEvent, &m_ctrlMode2, m_axis[1], m_port[0]);
		break;

	case 4:
		start(nIDEvent, &m_ctrlMode3, m_axis[2], m_port[1]);
		break;

	}

	CDialog::OnTimer(nIDEvent);
}

void CDlgSerial5::start(UINT_PTR nIDEvent, CComboBox* ctrlMode, int axisNum, int port)
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

		//int startspeed = (axisNum == m_axis[0]) ? m_startspeed * m_unit : ((axisNum == m_axis[1]) ? m_startspeed2 * m_unit2 : m_startspeed3 * m_unit3);
		int startspeed = (axisNum == m_axis[0]) ? m_startspeed * m_unit :  m_startspeed2 * m_unit2 ;
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

		//int targetspeed = (axisNum == m_axis[0]) ? m_targetspeed * m_unit : ((axisNum == m_axis[1]) ? m_targetspeed2 * m_unit2 : m_targetspeed3 * m_unit3);
		int targetspeed = (axisNum == m_axis[0]) ? m_targetspeed * m_unit : m_targetspeed2 * m_unit2;

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
		//int accelspeed = (axisNum == m_axis[0]) ? m_accelspeed * m_unit : ((axisNum == m_axis[1]) ? m_accelspeed2 * m_unit2 : m_accelspeed3 * m_unit3);
		int accelspeed = (axisNum == m_axis[0]) ? m_accelspeed * m_unit : m_accelspeed2 * m_unit2;

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
		if (axisNum == m_axis[0])
		{
			m_sendData = (m_absOrRel == 0) ?  _T("SMOV ") : _T("SMVR ");
			steps = m_steps * m_unit;
		}else if (axisNum == m_axis[1])
		{
			m_sendData = (m_absOrRel2 == 0) ?  _T("SMOV ") : _T("SMVR ");
			steps = m_steps2 * m_unit2;
		}
		/*else
		{
			m_sendData = (m_absOrRel3 == 0) ?  _T("SMOV ") : _T("SMVR ");
			steps = m_steps3 * m_unit3;
		}*/

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

void CDlgSerial5::loopComm(int* axis, int* port)
{
	if (m_bLoop == true)
	{
		UpdateData();

		if (m_loopCommNum == 0)
		{
			if (CPublic::bfindTerminator[port[0] - 1] == false)
				return;
			mainDlg->sendComm(_T("POS? ") + CPublic::int2CString(axis[0]), port[0]);		
		}

		if (m_loopCommNum == 1)
		{
			if (CPublic::bfindTerminator[port[0] - 1] == false)
				return;

			SetDlgItemText(IDC_EDIT_absPostion, CPublic::receiveData[port[0] - 1]);
			//SetDlgItemText(IDC_EDIT_absPostion, explainPos(CPublic::receiveData[portNum1 - 1]));

			UpdateData(FALSE);

			mainDlg->sendComm(_T("LIM? ") + CPublic::int2CString(axis[0]), port[0]);		

		}

		if (m_loopCommNum == 2)
		{
			if (CPublic::bfindTerminator[port[0] - 1] == false)
				return;

			CString t = CPublic::receiveData[port[0] - 1];

			switchLight(CPublic::explainLim(t, -1), CPublic::explainLim(t, 0),
				CPublic::explainLim(t, 1), CPublic::explainLim(t, 2));
			UpdateData(FALSE);	

			mainDlg->sendComm(_T("POS? ") + CPublic::int2CString(axis[1]), port[0]);		

		}

		if (m_loopCommNum == 3)
		{
			if (CPublic::bfindTerminator[port[0] - 1] == false)
				return;
			SetDlgItemText(IDC_EDIT_absPostion2, CPublic::receiveData[port[0] - 1]);
			//SetDlgItemText(IDC_EDIT_absPostion2, explainPos(CPublic::receiveData[portNum1 - 1]));
			UpdateData(FALSE);

			mainDlg->sendComm(_T("LIM? ") + CPublic::int2CString(axis[1]), port[0]);		

		}

		if (m_loopCommNum == 4)
		{
			if (CPublic::bfindTerminator[port[0] - 1] == false)
				return;

			CString t = CPublic::receiveData[port[0] - 1];

			switchLight(CPublic::explainLim(t, -1), CPublic::explainLim(t, 0),
				CPublic::explainLim(t, 1), CPublic::explainLim(t, 2));
			UpdateData(FALSE);	

			mainDlg->sendComm(_T("PFB"), port[1]);		

		}

		if (m_loopCommNum == 5)
		{
			if (CPublic::bfindTerminator[port[1] - 1] == false)
				return;

			SetDlgItemText(IDC_EDIT_absPostion3, CPublic::receiveData[port[1] - 1]);
			UpdateData(FALSE);	

			m_loopCommNum = 0;
			return;

		}

		m_loopCommNum++;


	}	
}

void CDlgSerial5::openLoopComm(UINT_PTR nIDEvent)
{
	SetTimer(nIDEvent, loopTime, NULL);
	m_loopCommNum = 0;
	m_bLoop = true;
}


void CDlgSerial5::closeLoopComm(UINT_PTR nIDEvent)
{
	KillTimer(nIDEvent);
	m_bLoop = false;
}

void CDlgSerial5::switchLight(int neg, int zero, int pos, int axisNum)
{
	if (axisNum == m_axis[0])
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

	}else if (axisNum == m_axis[1])
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
	}/*else if (axisNum == m_axis[2])
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
	}*/
}

void CDlgSerial5::settingComm(CString comm, int axisNum, int port)
{
	if(CPublic::portIsOpen[port - 1] == false)
	{
		mainDlg->AddString(_T("该串口未打开，请先打开串口！"));
		return;
	}

	closeLoopComm(1);

	m_sendData =  comm + CPublic::int2CString(axisNum);
	mainDlg->sendComm(m_sendData, port);
	//Sleep(500);
	openLoopComm(1);
}

void CDlgSerial5::settingComm(CString comm, int port)
{
	if(CPublic::portIsOpen[port - 1] == false)
	{
		mainDlg->AddString(_T("该串口未打开，请先打开串口！"));
		return;
	}

	closeLoopComm(1);

	m_sendData =  comm;
	mainDlg->sendComm(m_sendData, port);
	//Sleep(500);
	openLoopComm(1);
}

void CDlgSerial5::makeJOG(int sign, int axisNum, int port)
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
BOOL CDlgSerial5::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	if (pMsg->message == WM_LBUTTONDOWN)
	{
		if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_JOGM)->m_hWnd)
		{
			((CButton*)GetDlgItem(IDC_BUTTON_JOGM))->SetState(TRUE);

			makeJOG(-1, m_axis[0], m_port[0]);
			return TRUE;

		}
		if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_JOGP)->m_hWnd)
		{
			((CButton*)GetDlgItem(IDC_BUTTON_JOGP))->SetState(TRUE);
			makeJOG(1, m_axis[0], m_port[0]);
			return TRUE;
		}

		if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_JOGM2)->m_hWnd)
		{
			((CButton*)GetDlgItem(IDC_BUTTON_JOGM2))->SetState(TRUE);

			makeJOG(-1, m_axis[1], m_port[0]);
			return TRUE;

		}
		if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_JOGP2)->m_hWnd)
		{
			((CButton*)GetDlgItem(IDC_BUTTON_JOGP2))->SetState(TRUE);
			makeJOG(1, m_axis[1], m_port[0]);
			return TRUE;
		}

		/*if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_JOGM3)->m_hWnd)
		{
			((CButton*)GetDlgItem(IDC_BUTTON_JOGM3))->SetState(TRUE);

			makeJOG(-1, m_axis[2], m_port[0]);
			return TRUE;

		}
		if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_JOGP3)->m_hWnd)
		{
			((CButton*)GetDlgItem(IDC_BUTTON_JOGP3))->SetState(TRUE);
			makeJOG(1, m_axis[2], m_port[0]);
			return TRUE;
		}*/



	}

	if (pMsg->message==WM_LBUTTONUP)
	{
		if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_JOGP)->m_hWnd) 
		{
			((CButton*)GetDlgItem(IDC_BUTTON_JOGP))->SetState(FALSE);
			makeJOG(0, m_axis[0], m_port[0]);
			return TRUE;
		}

		if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_JOGM)->m_hWnd)
		{
			((CButton*)GetDlgItem(IDC_BUTTON_JOGM))->SetState(FALSE);
			makeJOG(0, m_axis[0], m_port[0]);
			return TRUE;
		}

		if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_JOGP2)->m_hWnd) 
		{
			((CButton*)GetDlgItem(IDC_BUTTON_JOGP2))->SetState(FALSE);
			makeJOG(0, m_axis[1], m_port[0]);
			return TRUE;
		}

		if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_JOGM2)->m_hWnd)
		{
			((CButton*)GetDlgItem(IDC_BUTTON_JOGM2))->SetState(FALSE);
			makeJOG(0, m_axis[1], m_port[0]);
			return TRUE;
		}

		/*if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_JOGP3)->m_hWnd) 
		{
			((CButton*)GetDlgItem(IDC_BUTTON_JOGP3))->SetState(FALSE);
			makeJOG(0, m_axis[2], m_port[0]);
			return TRUE;
		}

		if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_JOGM3)->m_hWnd)
		{
			((CButton*)GetDlgItem(IDC_BUTTON_JOGM3))->SetState(FALSE);
			makeJOG(0, m_axis[2], m_port[0]);
			return TRUE;
		}*/

	}

	return CDialog::PreTranslateMessage(pMsg);
}


void CDlgSerial5::OnBnClickedButtonstart()
{
	UpdateData();

	if(CPublic::portIsOpen[m_port[0] - 1] == false)
	{
		mainDlg->AddString(_T("该串口未打开，请先打开串口！"));
		return;
	}

	closeLoopComm(1);
	CPublic::commCount = 0;
	SetTimer(2, myStartTime, NULL);
}

void CDlgSerial5::OnBnClickedButtonstart2()
{
	UpdateData();

	if(CPublic::portIsOpen[m_port[0] - 1] == false)
	{
		mainDlg->AddString(_T("该串口未打开，请先打开串口！"));
		return;
	}

	closeLoopComm(1);
	CPublic::commCount = 0;
	SetTimer(3, myStartTime, NULL);
}

void CDlgSerial5::OnBnClickedButtonstart3()
{
	UpdateData();
	//set position
	m_sendData = (m_ctrlMode3.GetCurSel() == 0) ? _T("MOVEABS ") : _T("MOVEINC ");
	m_sendData +=  CPublic::int2CString(m_steps3) +  _T(" ") + CPublic::int2CString(m_targetspeed3);

	settingComm(m_sendData, m_port[1]);

	//set accelspeed
	m_sendData = _T("ACC ") + CPublic::int2CString(m_accelspeed3);
	settingComm(m_sendData, m_port[1]);

	//SetTimer(4, startTime, NULL);
}

void CDlgSerial5::OnBnClickedButtonstop()
{
	settingComm(_T("STOP "), m_axis[0], m_port[0]);
}

void CDlgSerial5::OnBnClickedButtonstop2()
{
	settingComm(_T("STOP "), m_axis[1], m_port[0]);

}

void CDlgSerial5::OnBnClickedButtonstop3()
{
	settingComm(_T("STOP "), m_axis[2], m_port[0]);

}

void CDlgSerial5::OnBnClickedButtonpluslimit()
{
	settingComm(_T("FFPL "), m_axis[0], m_port[0]);
}

void CDlgSerial5::OnBnClickedButtonpluslimit2()
{
	settingComm(_T("FFPL "), m_axis[1], m_port[0]);

}

void CDlgSerial5::OnBnClickedButtonenable()
{
	settingComm(_T("EN"), m_port[1]);

}

void CDlgSerial5::OnBnClickedButtonzeroswitch()
{
	settingComm(_T("FFRL "), m_axis[0], m_port[0]);

}

void CDlgSerial5::OnBnClickedButtonzeroswitch2()
{
	settingComm(_T("FFRL "), m_axis[1], m_port[0]);

}

//void CDlgSerial5::OnBnClickedButtonzeroswitch3()
//{
//	settingComm(_T("FFRL "), m_axis[2], m_port[0]);
//
//}

void CDlgSerial5::OnBnClickedButtonminuslimit()
{
	settingComm(_T("FFNL "), m_axis[0], m_port[0]);

}

void CDlgSerial5::OnBnClickedButtonminuslimit2()
{
	settingComm(_T("FFNL "), m_axis[1], m_port[0]);

}

//void CDlgSerial5::OnBnClickedButtonminuslimit3()
//{
//	settingComm(_T("FFNL "), m_axis[2], m_port[0]);
//
//}

void CDlgSerial5::OnBnClickedButtonabszero()
{
	settingComm(_T("DHOM "), m_axis[0], m_port[0]);

}

void CDlgSerial5::OnBnClickedButtonabszero2()
{
	settingComm(_T("DHOM "), m_axis[1], m_port[0]);

}

//void CDlgSerial5::OnBnClickedButtonabszero3()
//{
//	settingComm(_T("DHOM "), m_axis[2], m_port[0]);
//
//}

void CDlgSerial5::OnBnClickedButtonfindzero()
{
	settingComm(_T("GHOM "), m_axis[0], m_port[0]);

}

void CDlgSerial5::OnBnClickedButtonfindzero2()
{
	settingComm(_T("GHOM "), m_axis[1], m_port[0]);

}

void CDlgSerial5::OnBnClickedButtonfindzero3()
{
	settingComm(_T("HOMETYPE 33"),  m_port[1]);
	settingComm(_T("HOMECMD"),  m_port[1]);

}

void CDlgSerial5::OnCbnSelchangeCombounit3()
{

	if (m_cmbUnitX.GetCurSel() == 0)
	{
		((CStatic*)GetDlgItem(IDC_STATIC_start3))->SetWindowText(_T("(counts/s)"));
		((CStatic*)GetDlgItem(IDC_STATIC_target3))->SetWindowText(_T("(counts/s)"));
		((CStatic*)GetDlgItem(IDC_STATIC_accel3))->SetWindowText(_T("(counts/s2)"));
		((CStatic*)GetDlgItem(IDC_STATIC_steps3))->SetWindowText(_T("(counts)"));

	}else if ((m_cmbUnitX.GetCurSel() == 1))
	{
		((CStatic*)GetDlgItem(IDC_STATIC_start3))->SetWindowText(_T("(mm/s)"));
		((CStatic*)GetDlgItem(IDC_STATIC_target3))->SetWindowText(_T("(mm/s)"));
		((CStatic*)GetDlgItem(IDC_STATIC_accel3))->SetWindowText(_T("(mm/s2)"));
		((CStatic*)GetDlgItem(IDC_STATIC_steps3))->SetWindowText(_T("(mm)"));

	}else if ((m_cmbUnitX.GetCurSel() == 2))
	{
		((CStatic*)GetDlgItem(IDC_STATIC_start3))->SetWindowText(_T("(deg/s)"));
		((CStatic*)GetDlgItem(IDC_STATIC_target3))->SetWindowText(_T("(deg/s)"));
		((CStatic*)GetDlgItem(IDC_STATIC_accel3))->SetWindowText(_T("(deg/s2)"));
		((CStatic*)GetDlgItem(IDC_STATIC_steps3))->SetWindowText(_T("(deg)"));
	}


}

void CDlgSerial5::OnCbnSelchangeCombounit4()
{
	if (m_cmbUnitX2.GetCurSel() == 0)
	{
		((CStatic*)GetDlgItem(IDC_STATIC_start4))->SetWindowText(_T("(counts/s)"));
		((CStatic*)GetDlgItem(IDC_STATIC_target4))->SetWindowText(_T("(counts/s)"));
		((CStatic*)GetDlgItem(IDC_STATIC_accel4))->SetWindowText(_T("(counts/s2)"));
		((CStatic*)GetDlgItem(IDC_STATIC_steps4))->SetWindowText(_T("(counts)"));

	}else if ((m_cmbUnitX2.GetCurSel() == 1))
	{
		((CStatic*)GetDlgItem(IDC_STATIC_start4))->SetWindowText(_T("(mm/s)"));
		((CStatic*)GetDlgItem(IDC_STATIC_target4))->SetWindowText(_T("(mm/s)"));
		((CStatic*)GetDlgItem(IDC_STATIC_accel4))->SetWindowText(_T("(mm/s2)"));
		((CStatic*)GetDlgItem(IDC_STATIC_steps4))->SetWindowText(_T("(mm)"));

	}else if ((m_cmbUnitX2.GetCurSel() == 2))
	{
		((CStatic*)GetDlgItem(IDC_STATIC_start4))->SetWindowText(_T("(deg/s)"));
		((CStatic*)GetDlgItem(IDC_STATIC_target4))->SetWindowText(_T("(deg/s)"));
		((CStatic*)GetDlgItem(IDC_STATIC_accel4))->SetWindowText(_T("(deg/s2)"));
		((CStatic*)GetDlgItem(IDC_STATIC_steps4))->SetWindowText(_T("(deg)"));
	}
}

//void CDlgSerial5::OnCbnSelchangeCombounit5()
//{
//	if (m_cmbUnitX3.GetCurSel() == 0)
//	{
//		((CStatic*)GetDlgItem(IDC_STATIC_start5))->SetWindowText(_T("(counts/s)"));
//		((CStatic*)GetDlgItem(IDC_STATIC_target5))->SetWindowText(_T("(counts/s)"));
//		((CStatic*)GetDlgItem(IDC_STATIC_accel5))->SetWindowText(_T("(counts/s2)"));
//		((CStatic*)GetDlgItem(IDC_STATIC_steps5))->SetWindowText(_T("(counts)"));
//
//	}else if ((m_cmbUnitX3.GetCurSel() == 1))
//	{
//		((CStatic*)GetDlgItem(IDC_STATIC_start5))->SetWindowText(_T("(mm/s)"));
//		((CStatic*)GetDlgItem(IDC_STATIC_target5))->SetWindowText(_T("(mm/s)"));
//		((CStatic*)GetDlgItem(IDC_STATIC_accel5))->SetWindowText(_T("(mm/s2)"));
//		((CStatic*)GetDlgItem(IDC_STATIC_steps5))->SetWindowText(_T("(mm)"));
//
//	}else if ((m_cmbUnitX3.GetCurSel() == 2))
//	{
//		((CStatic*)GetDlgItem(IDC_STATIC_start5))->SetWindowText(_T("(deg/s)"));
//		((CStatic*)GetDlgItem(IDC_STATIC_target5))->SetWindowText(_T("(deg/s)"));
//		((CStatic*)GetDlgItem(IDC_STATIC_accel5))->SetWindowText(_T("(deg/s2)"));
//		((CStatic*)GetDlgItem(IDC_STATIC_steps5))->SetWindowText(_T("(deg)"));
//	}
//}

void CDlgSerial5::setPara(void)
{
	int index[3] = {0};
	int var = (_T("工位2-微动平台手动调整") == m_strDlgName) ? 1 : 2;
	for (int i = 0; i < 3; i++)
	{
		index[i] = m_axis[i] + var * 9 - 1;
	}

	m_ctrlMode.SetCurSel(CPublic::g_parameter[index[0]].mode);
	m_startspeed = CPublic::g_parameter[index[0]].startSpeed;
	m_targetspeed = CPublic::g_parameter[index[0]].targetSpeed;
	m_accelspeed = CPublic::g_parameter[index[0]].accelSpeed;
	m_steps = CPublic::g_parameter[index[0]].steps;

	m_ctrlMode2.SetCurSel(CPublic::g_parameter[index[1]].mode);
	m_startspeed2 = CPublic::g_parameter[index[1]].startSpeed;
	m_targetspeed2 = CPublic::g_parameter[index[1]].targetSpeed;
	m_accelspeed2 = CPublic::g_parameter[index[1]].accelSpeed;
	m_steps2 = CPublic::g_parameter[index[1]].steps;

	m_ctrlMode3.SetCurSel(CPublic::g_parameter[index[2]].mode);
	//m_startspeed3 = CPublic::g_parameter[m_axisSum[1] - 1].startSpeed;
	m_targetspeed3 = CPublic::g_parameter[index[2]].targetSpeed;
	m_accelspeed3 = CPublic::g_parameter[index[2]].accelSpeed;
	m_steps3 = CPublic::g_parameter[index[2]].steps;

	UpdateData(FALSE);
}

void CDlgSerial5::OnBnClickedButtonsave5()
{
	UpdateData();

	int index[3] = {0};
	int var = (_T("工位2-微动平台手动调整") == m_strDlgName) ? 1 : 2;
	for (int i = 0; i < 3; i++)
	{
		index[i] = m_axis[i] + var * 9 - 1;
	}

	AxisParameter para[3];
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
	para[2].targetSpeed = m_targetspeed3;
	para[2].accelSpeed = m_accelspeed3;
	para[2].steps = m_steps3;


	mainDlg->updateAxisParameter2Value(para, index, 3, true);
	mainDlg->updateValue2File(index, 3, true);
}

void CDlgSerial5::OnBnClickedButtondefault5()
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
	//m_startspeed3 = 5000;
	m_targetspeed3 = 100000;
	m_accelspeed3 = 50000;
	m_steps3 = 0;


	UpdateData(FALSE);
}

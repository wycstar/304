// DlgSerial1.cpp : implementation file
//

#include "stdafx.h"
#include "controlSerialNetPort.h"
#include "DlgSerial1.h"
#include "Public.h"
#include "controlSerialNetPortDlg.h"



extern CcontrolSerialNetPortDlg* mainDlg;
// CDlgSerial1 dialog

IMPLEMENT_DYNAMIC(CDlgSerial1, CDialog)

CDlgSerial1::CDlgSerial1(CWnd* pParent /*=NULL*/, int* port, int* axisNum)
	: CDialog(CDlgSerial1::IDD, pParent)
	, m_startspeed(5000)
	, m_targetspeed(100000)
	//, m_stopspeed(0)
	, m_accelspeed(50000)
	, m_steps(0)
	, m_startspeed2(5000)
	, m_targetspeed2(100000)
	//, m_stopspeed2(0)
	, m_accelspeed2(50000)
	, m_steps2(0)
	, m_absOrRel(0)
	, m_absOrRel2(0)
	, m_unit(1)
	, m_unit2(1)
	, m_bLoop(true)
	, m_sendData(_T(""))
	, m_loopCommNum(0)
{
	//m_axisSum[0] = axisNum[0];
	//m_axisSum[1] = axisNum[1];
	//m_port = *port;


}

CDlgSerial1::~CDlgSerial1()
{
}

void CDlgSerial1::DoDataExchange(CDataExchange* pDX)
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

	DDX_Control(pDX, IDC_COMBO_MODE, m_ctrlMode);
	DDX_Control(pDX, IDC_COMBO_MODE2, m_ctrlMode2);
	DDX_Radio(pDX, IDC_RADIO_absPosition, m_absOrRel);
	DDX_Radio(pDX, IDC_RADIO_absPosition2, m_absOrRel2);
	DDX_Control(pDX, IDC_COMBO_unit, m_cmbUnitX);
	DDX_Control(pDX, IDC_COMBO_unit2, m_cmbUnitX2);
	DDX_Text(pDX, IDC_EDIT_unit, m_unit);
	DDX_Text(pDX, IDC_EDIT_unit2, m_unit2);

	DDX_Control(pDX, IDC_BUTTON_plusLight, m_bstplusLight);
	DDX_Control(pDX, IDC_BUTTON_zeroLight, m_bstzeroLight);
	DDX_Control(pDX, IDC_BUTTON_minusLight, m_bstminusLight);
	DDX_Control(pDX, IDC_BUTTON_plusLight2, m_bstplusLight2);
	DDX_Control(pDX, IDC_BUTTON_zeroLight2, m_bstzeroLight2);
	DDX_Control(pDX, IDC_BUTTON_minusLight2, m_bstminusLight2);
	DDX_Control(pDX, IDC_BUTTON_save, m_bstsave);
	DDX_Control(pDX, IDC_BUTTON_default, m_bstdefault);
}


BEGIN_MESSAGE_MAP(CDlgSerial1, CDialog)

//ON_MESSAGE(WM_COMM_RXCHAR, OnCommunication)

ON_BN_CLICKED(IDC_BUTTON_start, &CDlgSerial1::OnBnClickedButtonstart)
ON_CBN_SELCHANGE(IDC_COMBO_unit, &CDlgSerial1::OnCbnSelchangeCombounit)
ON_WM_TIMER()
ON_BN_CLICKED(IDC_BUTTON_stop, &CDlgSerial1::OnBnClickedButtonstop)
ON_BN_CLICKED(IDC_BUTTON_plusLimit, &CDlgSerial1::OnBnClickedButtonpluslimit)
ON_BN_CLICKED(IDC_BUTTON_zeroSwitch, &CDlgSerial1::OnBnClickedButtonzeroswitch)
ON_BN_CLICKED(IDC_BUTTON_minusLimit, &CDlgSerial1::OnBnClickedButtonminuslimit)
ON_BN_CLICKED(IDC_BUTTON_absZero, &CDlgSerial1::OnBnClickedButtonabszero)
ON_BN_CLICKED(IDC_BUTTON_findZero, &CDlgSerial1::OnBnClickedButtonfindzero)
ON_BN_CLICKED(IDC_BUTTON_start2, &CDlgSerial1::OnBnClickedButtonstart2)
ON_BN_CLICKED(IDC_BUTTON_stop2, &CDlgSerial1::OnBnClickedButtonstop2)
ON_BN_CLICKED(IDC_BUTTON_plusLimit2, &CDlgSerial1::OnBnClickedButtonpluslimit2)
ON_BN_CLICKED(IDC_BUTTON_zeroSwitch2, &CDlgSerial1::OnBnClickedButtonzeroswitch2)
ON_BN_CLICKED(IDC_BUTTON_minusLimit2, &CDlgSerial1::OnBnClickedButtonminuslimit2)
ON_BN_CLICKED(IDC_BUTTON_absZero2, &CDlgSerial1::OnBnClickedButtonabszero2)
ON_BN_CLICKED(IDC_BUTTON_findZero2, &CDlgSerial1::OnBnClickedButtonfindzero2)
ON_CBN_SELCHANGE(IDC_COMBO_unit2, &CDlgSerial1::OnCbnSelchangeCombounit2)
ON_EN_SETFOCUS(IDC_EDIT_startSpeed, &CDlgSerial1::OnEnSetfocusEditstartspeed)
ON_EN_SETFOCUS(IDC_EDIT_targetSpeed, &CDlgSerial1::OnEnSetfocusEdittargetspeed)
ON_EN_SETFOCUS(IDC_EDIT_accelspeed, &CDlgSerial1::OnEnSetfocusEditaccelspeed)
ON_EN_SETFOCUS(IDC_EDIT_steps, &CDlgSerial1::OnEnSetfocusEditsteps)
ON_EN_SETFOCUS(IDC_EDIT_startSpeed2, &CDlgSerial1::OnEnSetfocusEditstartspeed2)
ON_EN_SETFOCUS(IDC_EDIT_targetSpeed2, &CDlgSerial1::OnEnSetfocusEdittargetspeed2)
ON_EN_SETFOCUS(IDC_EDIT_accelspeed2, &CDlgSerial1::OnEnSetfocusEditaccelspeed2)
ON_EN_SETFOCUS(IDC_EDIT_steps2, &CDlgSerial1::OnEnSetfocusEditsteps2)
ON_EN_SETFOCUS(IDC_EDIT_unit, &CDlgSerial1::OnEnSetfocusEditunit)
ON_EN_SETFOCUS(IDC_EDIT_unit2, &CDlgSerial1::OnEnSetfocusEditunit2)
ON_BN_CLICKED(IDC_RADIO_absPosition, &CDlgSerial1::OnBnClickedRadioabsposition)
ON_BN_CLICKED(IDC_RADIO_relPosition, &CDlgSerial1::OnBnClickedRadiorelposition)
ON_BN_CLICKED(IDC_RADIO_absPosition2, &CDlgSerial1::OnBnClickedRadioabsposition2)
ON_BN_CLICKED(IDC_RADIO_relPosition2, &CDlgSerial1::OnBnClickedRadiorelposition2)
ON_BN_CLICKED(IDC_BUTTON_save, &CDlgSerial1::OnBnClickedButtonsave)
ON_BN_CLICKED(IDC_BUTTON_default, &CDlgSerial1::OnBnClickedButtondefault)
END_MESSAGE_MAP()


// CDlgSerial1 message handlers

BOOL CDlgSerial1::OnInitDialog()
{
	CDialog::OnInitDialog();
	InitUI();
	SetWindowText(_T("工位1装配机械手手动调整"));

	
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


//LONG CDlgSerial1::OnCommunication(WPARAM ch, LPARAM port)
//{
//	UpdateData(true);
//
//	
//
//	return TRUE;
//}


BOOL CDlgSerial1::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->message == WM_LBUTTONDOWN)
	{
		if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_JOGM)->m_hWnd)
		{
			((CButton*)GetDlgItem(IDC_BUTTON_JOGM))->SetState(TRUE);

			makeJOG(-1, m_axisSum[0]);
			return TRUE;

		}
		if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_JOGP)->m_hWnd)
		{
			((CButton*)GetDlgItem(IDC_BUTTON_JOGP))->SetState(TRUE);
			makeJOG(1, m_axisSum[0]);
			return TRUE;
		}

		if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_JOGM2)->m_hWnd)
		{
			((CButton*)GetDlgItem(IDC_BUTTON_JOGM2))->SetState(TRUE);

			makeJOG(-1, m_axisSum[1]);
			return TRUE;

		}
		if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_JOGP2)->m_hWnd)
		{
			((CButton*)GetDlgItem(IDC_BUTTON_JOGP2))->SetState(TRUE);
			makeJOG(1, m_axisSum[1]);
			return TRUE;
		}

	}

	if (pMsg->message==WM_LBUTTONUP)
	{
		if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_JOGP)->m_hWnd) 
		{
			((CButton*)GetDlgItem(IDC_BUTTON_JOGP))->SetState(FALSE);
			makeJOG(0, m_axisSum[0]);
			return TRUE;
		}

		if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_JOGM)->m_hWnd)
		{
			((CButton*)GetDlgItem(IDC_BUTTON_JOGM))->SetState(FALSE);
			makeJOG(0, m_axisSum[0]);
			return TRUE;
		}

		if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_JOGP2)->m_hWnd) 
		{
			((CButton*)GetDlgItem(IDC_BUTTON_JOGP2))->SetState(FALSE);
			makeJOG(0, m_axisSum[1]);
			return TRUE;
		}

		if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_JOGM2)->m_hWnd)
		{
			((CButton*)GetDlgItem(IDC_BUTTON_JOGM2))->SetState(FALSE);
			makeJOG(0, m_axisSum[1]);
			return TRUE;
		}

	}

	return CDialog::PreTranslateMessage(pMsg);
}

void CDlgSerial1::OnBnClickedButtonstart()
{
	UpdateData();

	if(CPublic::portIsOpen[m_port - 1] == false)
	{
		mainDlg->AddString(_T("该串口未打开，请先打开串口！"));
		return;
	}
	
	closeLoopComm(2);
	CPublic::commCount = 0;
	SetTimer(1, startTime, NULL);

}

void CDlgSerial1::OnCbnSelchangeCombounit()
{
	if (m_cmbUnitX.GetCurSel() == 0)
	{
		((CStatic*)GetDlgItem(IDC_STATIC_start))->SetWindowText(_T("(counts/s)"));
		((CStatic*)GetDlgItem(IDC_STATIC_target))->SetWindowText(_T("(counts/s)"));
		((CStatic*)GetDlgItem(IDC_STATIC_accel))->SetWindowText(_T("(counts/s2)"));
		((CStatic*)GetDlgItem(IDC_STATIC_steps))->SetWindowText(_T("(counts)"));
	}else if ((m_cmbUnitX.GetCurSel() == 1))
	{
		
		((CStatic*)GetDlgItem(IDC_STATIC_start))->SetWindowText(_T("(mm/s)"));
		((CStatic*)GetDlgItem(IDC_STATIC_target))->SetWindowText(_T("(mm/s)"));
		((CStatic*)GetDlgItem(IDC_STATIC_accel))->SetWindowText(_T("(mm/s2)"));
		((CStatic*)GetDlgItem(IDC_STATIC_steps))->SetWindowText(_T("(mm)"));

	}else if ((m_cmbUnitX.GetCurSel() == 2))
	{

		((CStatic*)GetDlgItem(IDC_STATIC_start))->SetWindowText(_T("(deg/s)"));
		((CStatic*)GetDlgItem(IDC_STATIC_target))->SetWindowText(_T("(deg/s)"));
		((CStatic*)GetDlgItem(IDC_STATIC_accel))->SetWindowText(_T("(deg/s2)"));
		((CStatic*)GetDlgItem(IDC_STATIC_steps))->SetWindowText(_T("(deg)"));

	}
}

void CDlgSerial1::InitUI(void)
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

	setPara();

	SetTimer(2, loopTime, NULL);

	
}

void CDlgSerial1::OnTimer(UINT_PTR nIDEvent)
{
	switch(nIDEvent)
	{

	case 1:
		start1(nIDEvent);
		break;

	case 2:

		loopComm();		
		break;

	case 3:
		start2(nIDEvent);
		break;

	}

	CDialog::OnTimer(nIDEvent);
}

//start axis 1
void CDlgSerial1::start1(UINT_PTR nIDEvent)
{
	UpdateData();
	//CString comm = _T("");
	CString strAxis = CPublic::int2CString(m_axisSum[0]);
	m_bLoop = false;
	

	if (CPublic::commCount == 0)
	{
		m_sendData = (m_ctrlMode.GetCurSel() == 0) ?  _T("OMOD ") : _T("CMOD ");
		m_sendData = m_sendData + CPublic::int2CString(m_axisSum[0]);
		mainDlg->sendComm(m_sendData, m_port);

	}else if (CPublic::commCount == 1)
	{	
		if (CPublic::bfindTerminator[m_port - 1] == false)
			return;

		if (CPublic::receiveData[m_port - 1] != m_sendData)
		{
			mainDlg->AddString(ERRO1);
			KillTimer(nIDEvent);
			openLoopComm(2);
			return;
		}
		//mainDlg->AddString(CPublic::receiveData[portNum1 - 1]);

		m_sendData = _T("SVEL ") + strAxis + _T(" ") + CPublic::int2CString(m_startspeed * m_unit);
		mainDlg->sendComm(m_sendData, m_port);

	}else if (CPublic::commCount == 2)
	{
		if (CPublic::bfindTerminator[m_port - 1] == false)
			return;

		if (CPublic::receiveData[m_port - 1] != m_sendData)
		{
			mainDlg->AddString(ERRO1);
			KillTimer(nIDEvent);
			openLoopComm(2);
			return;
		}
		//mainDlg->AddString(CPublic::receiveData[portNum1 - 1]);

		m_sendData = _T("TVEL ") + strAxis + _T(" ") + CPublic::int2CString(m_targetspeed * m_unit);
		mainDlg->sendComm(m_sendData, m_port);
		

	}else if (CPublic::commCount == 3)
	{
		if (CPublic::bfindTerminator[m_port - 1] == false)
			return;

		if (CPublic::receiveData[m_port - 1] != m_sendData)
		{
			mainDlg->AddString(ERRO1);
			KillTimer(nIDEvent);
			openLoopComm(2);
			return;
		}
		//mainDlg->AddString(CPublic::receiveData[portNum1 - 1]);

		m_sendData = _T("SACC ") + strAxis + _T(" ") + CPublic::int2CString(m_accelspeed * m_unit);
		mainDlg->sendComm(m_sendData, m_port);

	}else if (CPublic::commCount == 4)
	{
		if (CPublic::bfindTerminator[m_port - 1] == false)
			return;

		if (CPublic::receiveData[m_port - 1] != m_sendData)
		{
			mainDlg->AddString(ERRO1);
			KillTimer(nIDEvent);
			openLoopComm(2);
			return;
		}

		//mainDlg->AddString(CPublic::receiveData[portNum1 - 1]);

		m_sendData = (m_absOrRel == 0) ?  _T("SMOV ") : _T("SMVR ");
		m_sendData = m_sendData + strAxis + _T(" ") + CPublic::int2CString(m_steps * m_unit);
		mainDlg->sendComm(m_sendData, m_port);
	}

	if (CPublic::commCount == 5)
	{
		if (CPublic::bfindTerminator[m_port - 1] == false)
			return;

		if (CPublic::receiveData[m_port - 1] != m_sendData)
		{
			mainDlg->AddString(ERRO1);
			KillTimer(nIDEvent);
			openLoopComm(2);
			return;
		}

		//mainDlg->AddString(CPublic::receiveData[portNum1 - 1]);
		KillTimer(nIDEvent);
		openLoopComm(2);
	}


	CPublic::commCount++;
}

void CDlgSerial1::loopComm(void)
{
	if (m_bLoop == true)
	{
		UpdateData();
		
		if (m_loopCommNum == 0)
		{
			if (CPublic::bfindTerminator[m_port - 1] == false)
				return;
			mainDlg->sendComm(_T("POS? ") + CPublic::int2CString(m_axisSum[0]), m_port);		
		}

		if (m_loopCommNum == 1)
		{
			if (CPublic::bfindTerminator[m_port - 1] == false)
				return;

			SetDlgItemText(IDC_EDIT_absPostion, CPublic::receiveData[m_port - 1]);
			//SetDlgItemText(IDC_EDIT_absPostion, explainPos(CPublic::receiveData[portNum1 - 1]));

			//UpdateData(FALSE);

			mainDlg->sendComm(_T("LIM? ") + CPublic::int2CString(m_axisSum[0]), m_port);		

		}

		if (m_loopCommNum == 2)
		{
			if (CPublic::bfindTerminator[m_port - 1] == false)
				return;

			CString t = CPublic::receiveData[m_port - 1];
			
			switchLight(CPublic::explainLim(t, -1), CPublic::explainLim(t, 0),
						CPublic::explainLim(t, 1), CPublic::explainLim(t, 2));
			//UpdateData(FALSE);	

			mainDlg->sendComm(_T("POS? ") + CPublic::int2CString(m_axisSum[1]), m_port);		

		}

		if (m_loopCommNum == 3)
		{
			if (CPublic::bfindTerminator[m_port - 1] == false)
				return;
			SetDlgItemText(IDC_EDIT_absPostion2, CPublic::receiveData[m_port - 1]);
			//SetDlgItemText(IDC_EDIT_absPostion2, explainPos(CPublic::receiveData[portNum1 - 1]));
			//UpdateData(FALSE);

			mainDlg->sendComm(_T("LIM? ") + CPublic::int2CString(m_axisSum[1]), m_port);		

		}

		if (m_loopCommNum == 4)
		{
			if (CPublic::bfindTerminator[m_port - 1] == false)
				return;

			CString t = CPublic::receiveData[m_port - 1];
			switchLight(CPublic::explainLim(t, -1), CPublic::explainLim(t, 0),
						CPublic::explainLim(t, 1), CPublic::explainLim(t, 2));
			//UpdateData(FALSE);	

			m_loopCommNum = 0;
			return;
		}

		m_loopCommNum++;
		
		
	}	
}



void CDlgSerial1::openLoopComm(UINT_PTR nIDEvent)
{
	SetTimer(nIDEvent, loopTime, NULL);
	m_loopCommNum = 0;
	//CPublic::receiveData[portNum1 - 1] = _T("");
	m_bLoop = true;
}

void CDlgSerial1::OnBnClickedButtonstop()
{
	settingComm(_T("STOP "), m_axisSum[0]);
}


void CDlgSerial1::closeLoopComm(UINT_PTR nIDEvent)
{
	KillTimer(nIDEvent);
	m_bLoop = false;
}

void CDlgSerial1::OnBnClickedButtonpluslimit()
{
	settingComm(_T("FFPL "), m_axisSum[0]);
}

void CDlgSerial1::OnBnClickedButtonzeroswitch()
{
	settingComm(_T("FFRL "), m_axisSum[0]);
}

void CDlgSerial1::OnBnClickedButtonminuslimit()
{
	settingComm(_T("FFNL "), m_axisSum[0]);
}

void CDlgSerial1::settingComm(CString comm, int axisNum)
{
	if(CPublic::portIsOpen[m_port - 1] == false)
	{
		mainDlg->AddString(_T("该串口未打开，请先打开串口！"));
		return;
	}

	closeLoopComm(2);

	m_sendData =  comm + CPublic::int2CString(axisNum);
	mainDlg->sendComm(m_sendData, m_port);
	//Sleep(500);
	openLoopComm(2);
}



void CDlgSerial1::OnBnClickedButtonabszero()
{
	settingComm(_T("DHOM "), m_axisSum[0]);

}

void CDlgSerial1::OnBnClickedButtonfindzero()
{
	settingComm(_T("GHOM "), m_axisSum[0]);

}

void CDlgSerial1::makeJOG(int sign, int axisNum)
{
	if (sign == -1)
	{
		settingComm(_T("FFNL "), axisNum);
	}else if (sign == 1)
	{
		settingComm(_T("FFPL "), axisNum);
	}else if (sign == 0)
	{
		settingComm(_T("STOP "), axisNum);
	}
		
}


void CDlgSerial1::switchLight(int neg, int zero, int pos, int axisNum)
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
	}
}

void CDlgSerial1::start2(UINT_PTR nIDEvent)
{
	UpdateData();
	CString strAxis = CPublic::int2CString(m_axisSum[1]);
	m_bLoop = false;


	if (CPublic::commCount == 0)
	{
		m_sendData = (m_ctrlMode2.GetCurSel() == 0) ?  _T("OMOD ") : _T("CMOD ");
		m_sendData = m_sendData + strAxis;
		mainDlg->sendComm(m_sendData, m_port);

	}else if (CPublic::commCount == 1)
	{	
		if (CPublic::bfindTerminator[m_port - 1] == false)
			return;

		if (CPublic::receiveData[m_port - 1] != m_sendData)
		{
			mainDlg->AddString(ERRO1);
			KillTimer(nIDEvent);
			openLoopComm(2);
			return;
		}

		m_sendData = _T("SVEL ") + strAxis + _T(" ") + CPublic::int2CString(m_startspeed2 * m_unit2);
		mainDlg->sendComm(m_sendData, m_port);

	}else if (CPublic::commCount == 2)
	{
		if (CPublic::bfindTerminator[m_port - 1] == false)
			return;

		if (CPublic::receiveData[m_port - 1] != m_sendData)
		{
			mainDlg->AddString(ERRO1);
			KillTimer(nIDEvent);
			openLoopComm(2);
			return;
		}
		//mainDlg->AddString(CPublic::receiveData[portNum1 - 1]);

		m_sendData = _T("TVEL ") + strAxis + _T(" ") + CPublic::int2CString(m_targetspeed2 * m_unit2);
		mainDlg->sendComm(m_sendData, m_port);


	}else if (CPublic::commCount == 3)
	{
		if (CPublic::bfindTerminator[m_port - 1] == false)
			return;

		if (CPublic::receiveData[m_port - 1] != m_sendData)
		{
			mainDlg->AddString(ERRO1);
			KillTimer(nIDEvent);
			openLoopComm(2);
			return;
		}
		//mainDlg->AddString(CPublic::receiveData[portNum1 - 1]);

		m_sendData = _T("SACC ") + strAxis + _T(" ") + CPublic::int2CString(m_accelspeed2 * m_unit2);
		mainDlg->sendComm(m_sendData, m_port);

	}else if (CPublic::commCount == 4)
	{
		if (CPublic::bfindTerminator[m_port - 1] == false)
			return;

		if (CPublic::receiveData[m_port - 1] != m_sendData)
		{
			mainDlg->AddString(ERRO1);
			KillTimer(nIDEvent);
			openLoopComm(2);
			return;
		}

		//mainDlg->AddString(CPublic::receiveData[portNum1 - 1]);

		m_sendData = (m_absOrRel2 == 0) ?  _T("SMOV ") : _T("SMVR ");
		m_sendData = m_sendData + strAxis + _T(" ") + CPublic::int2CString(m_steps2 * m_unit2);
		mainDlg->sendComm(m_sendData, m_port);
	}

	if (CPublic::commCount == 5)
	{
		if (CPublic::bfindTerminator[m_port - 1] == false)
			return;

		if (CPublic::receiveData[m_port - 1] != m_sendData)
		{
			mainDlg->AddString(ERRO1);
			KillTimer(nIDEvent);
			openLoopComm(2);
			return;
		}

		KillTimer(nIDEvent);
		openLoopComm(2);
	}


	CPublic::commCount++;
}



void CDlgSerial1::OnBnClickedButtonstart2()
{
	UpdateData();

	if(CPublic::portIsOpen[m_port - 1] == false)
	{
		mainDlg->AddString(_T("该串口未打开，请先打开串口！"));
		return;
	}

	closeLoopComm(2);
	CPublic::commCount = 0;
	SetTimer(3, startTime, NULL);
}

void CDlgSerial1::OnBnClickedButtonstop2()
{
	settingComm(_T("STOP "), m_axisSum[1]);
}

void CDlgSerial1::OnBnClickedButtonpluslimit2()
{
	settingComm(_T("FFPL "), m_axisSum[1]);

}

void CDlgSerial1::OnBnClickedButtonzeroswitch2()
{
	settingComm(_T("FFRL "), m_axisSum[1]);

}

void CDlgSerial1::OnBnClickedButtonminuslimit2()
{
	settingComm(_T("FFNL "), m_axisSum[1]);

}

void CDlgSerial1::OnBnClickedButtonabszero2()
{
	settingComm(_T("DHOM "), m_axisSum[1]);

}

void CDlgSerial1::OnBnClickedButtonfindzero2()
{
	settingComm(_T("GHOM "), m_axisSum[1]);

}


void CDlgSerial1::OnCbnSelchangeCombounit2()
{
	if (m_cmbUnitX2.GetCurSel() == 0)
	{
		((CStatic*)GetDlgItem(IDC_STATIC_start2))->SetWindowText(_T("(counts/s)"));
		((CStatic*)GetDlgItem(IDC_STATIC_target2))->SetWindowText(_T("(counts/s)"));
		((CStatic*)GetDlgItem(IDC_STATIC_accel2))->SetWindowText(_T("(counts/s2)"));
		((CStatic*)GetDlgItem(IDC_STATIC_steps2))->SetWindowText(_T("(counts)"));
	}else if ((m_cmbUnitX2.GetCurSel() == 1))
	{

		((CStatic*)GetDlgItem(IDC_STATIC_start2))->SetWindowText(_T("(mm/s)"));
		((CStatic*)GetDlgItem(IDC_STATIC_target2))->SetWindowText(_T("(mm/s)"));
		((CStatic*)GetDlgItem(IDC_STATIC_accel2))->SetWindowText(_T("(mm/s2)"));
		((CStatic*)GetDlgItem(IDC_STATIC_steps2))->SetWindowText(_T("(mm)"));

	}else if ((m_cmbUnitX2.GetCurSel() == 2))
	{

		((CStatic*)GetDlgItem(IDC_STATIC_start2))->SetWindowText(_T("(deg/s)"));
		((CStatic*)GetDlgItem(IDC_STATIC_target2))->SetWindowText(_T("(deg/s)"));
		((CStatic*)GetDlgItem(IDC_STATIC_accel2))->SetWindowText(_T("(deg/s2)"));
		((CStatic*)GetDlgItem(IDC_STATIC_steps2))->SetWindowText(_T("(deg)"));

	}
}

void CDlgSerial1::OnEnSetfocusEditstartspeed()
{
	if (m_bLoop == true)
	{
		closeLoopComm(2);
	}
	
}

void CDlgSerial1::OnEnSetfocusEdittargetspeed()
{
	if (m_bLoop == true)
	{
		closeLoopComm(2);
	}

}

void CDlgSerial1::OnEnSetfocusEditaccelspeed()
{
	if (m_bLoop == true)
	{
		closeLoopComm(2);
	}

}

void CDlgSerial1::OnEnSetfocusEditsteps()
{
	if (m_bLoop == true)
	{
		closeLoopComm(2);
	}

}

void CDlgSerial1::OnEnSetfocusEditstartspeed2()
{
	if (m_bLoop == true)
	{
		closeLoopComm(2);
	}

}

void CDlgSerial1::OnEnSetfocusEdittargetspeed2()
{
	if (m_bLoop == true)
	{
		closeLoopComm(2);
	}

}

void CDlgSerial1::OnEnSetfocusEditaccelspeed2()
{
	if (m_bLoop == true)
	{
		closeLoopComm(2);
	}

}

void CDlgSerial1::OnEnSetfocusEditsteps2()
{
	if (m_bLoop == true)
	{
		closeLoopComm(2);
	}

}

void CDlgSerial1::OnEnSetfocusEditunit()
{
	if (m_bLoop == true)
	{
		closeLoopComm(2);
	}
}

void CDlgSerial1::OnEnSetfocusEditunit2()
{
	if (m_bLoop == true)
	{
		closeLoopComm(2);
	}
}

void CDlgSerial1::OnBnClickedRadioabsposition()
{
	if (m_bLoop == true)
		closeLoopComm(2);

	m_absOrRel = 0;
	UpdateData(FALSE);

	if (m_bLoop == false)
		openLoopComm(2);
}

void CDlgSerial1::OnBnClickedRadiorelposition()
{
	if (m_bLoop == true)
		closeLoopComm(2);

	m_absOrRel = 1;
	UpdateData(FALSE);

	if (m_bLoop == false)
		openLoopComm(2);
}

void CDlgSerial1::OnBnClickedRadioabsposition2()
{
	if (m_bLoop == true)
		closeLoopComm(2);

	m_absOrRel2 = 0;
	UpdateData(FALSE);

	if (m_bLoop == false)
		openLoopComm(2);
}

void CDlgSerial1::OnBnClickedRadiorelposition2()
{
	if (m_bLoop == true)
		closeLoopComm(2);

	m_absOrRel2 = 1;
	UpdateData(FALSE);

	if (m_bLoop == false)
		openLoopComm(2);
}

void CDlgSerial1::OnBnClickedButtonsave()
{
	UpdateData();
	int axis[2] = {m_axisSum[0] - 1, m_axisSum[1] - 1};
	AxisParameter para[2];
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


	mainDlg->updateAxisParameter2Value(para, axis, 2, true);
	mainDlg->updateValue2File(axis, 2, true);
}

void CDlgSerial1::setPara(void)
{
	m_ctrlMode.SetCurSel(CPublic::g_parameter[m_axisSum[0] - 1].mode);
	m_startspeed = CPublic::g_parameter[m_axisSum[0] - 1].startSpeed;
	m_targetspeed = CPublic::g_parameter[m_axisSum[0] - 1].targetSpeed;
	m_accelspeed = CPublic::g_parameter[m_axisSum[0] - 1].accelSpeed;
	m_steps= CPublic::g_parameter[m_axisSum[0] - 1].steps;

	m_ctrlMode2.SetCurSel(CPublic::g_parameter[m_axisSum[1] - 1].mode);
	m_startspeed2 = CPublic::g_parameter[m_axisSum[1] - 1].startSpeed;
	m_targetspeed2 = CPublic::g_parameter[m_axisSum[1] - 1].targetSpeed;
	m_accelspeed2 = CPublic::g_parameter[m_axisSum[1] - 1].accelSpeed;
	m_steps2= CPublic::g_parameter[m_axisSum[1] - 1].steps;
	UpdateData(FALSE);


}
void CDlgSerial1::OnBnClickedButtondefault()
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


	UpdateData(FALSE);
}

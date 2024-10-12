// DlgSerial4.cpp : implementation file
//

#include "stdafx.h"
#include "controlSerialNetPort.h"
#include "controlSerialNetPortDlg.h"
#include "DlgSerial4.h"


// CDlgSerial4 dialog
extern CcontrolSerialNetPortDlg* mainDlg;


IMPLEMENT_DYNAMIC(CDlgSerial4, CDialog)

CDlgSerial4::CDlgSerial4(CWnd* pParent /*=NULL*/, int port, int* axisNum, CString dlgName)
	: CDialog(CDlgSerial4::IDD, pParent)
	, m_startspeed(5000)
	, m_targetspeed(100000)
	, m_accelspeed(50000)
	, m_steps(0)
	, m_startspeed2(5000)
	, m_targetspeed2(100000)
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
	m_port = port;
	m_axis[0] = axisNum[0];
	m_axis[1] = axisNum[1];

	m_strDlgName = dlgName;



}

CDlgSerial4::~CDlgSerial4()
{
}

void CDlgSerial4::DoDataExchange(CDataExchange* pDX)
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

	DDX_Control(pDX, IDC_BUTTON_save4, m_bstsave);
	DDX_Control(pDX, IDC_BUTTON_default4, m_bstdefault);


}


BEGIN_MESSAGE_MAP(CDlgSerial4, CDialog)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_start, &CDlgSerial4::OnBnClickedButtonstart)
	ON_BN_CLICKED(IDC_BUTTON_stop, &CDlgSerial4::OnBnClickedButtonstop)
	ON_BN_CLICKED(IDC_BUTTON_plusLimit, &CDlgSerial4::OnBnClickedButtonpluslimit)
	ON_BN_CLICKED(IDC_BUTTON_zeroSwitch, &CDlgSerial4::OnBnClickedButtonzeroswitch)
	ON_BN_CLICKED(IDC_BUTTON_minusLimit, &CDlgSerial4::OnBnClickedButtonminuslimit)
	ON_BN_CLICKED(IDC_BUTTON_absZero, &CDlgSerial4::OnBnClickedButtonabszero)
	ON_BN_CLICKED(IDC_BUTTON_findZero, &CDlgSerial4::OnBnClickedButtonfindzero)
	ON_CBN_SELCHANGE(IDC_COMBO_unit, &CDlgSerial4::OnCbnSelchangeCombounit)

	ON_BN_CLICKED(IDC_BUTTON_start2, &CDlgSerial4::OnBnClickedButtonstart2)
	ON_BN_CLICKED(IDC_BUTTON_stop2, &CDlgSerial4::OnBnClickedButtonstop2)
	ON_BN_CLICKED(IDC_BUTTON_plusLimit2, &CDlgSerial4::OnBnClickedButtonpluslimit2)
	ON_BN_CLICKED(IDC_BUTTON_zeroSwitch2, &CDlgSerial4::OnBnClickedButtonzeroswitch2)
	ON_BN_CLICKED(IDC_BUTTON_minusLimit2, &CDlgSerial4::OnBnClickedButtonminuslimit2)
	ON_BN_CLICKED(IDC_BUTTON_absZero2, &CDlgSerial4::OnBnClickedButtonabszero2)
	ON_BN_CLICKED(IDC_BUTTON_findZero2, &CDlgSerial4::OnBnClickedButtonfindzero2)
	ON_CBN_SELCHANGE(IDC_COMBO_unit2, &CDlgSerial4::OnCbnSelchangeCombounit2)
	
	ON_BN_CLICKED(IDC_BUTTON_save4, &CDlgSerial4::OnBnClickedButtonsave4)
	ON_BN_CLICKED(IDC_BUTTON_default4, &CDlgSerial4::OnBnClickedButtondefault4)
END_MESSAGE_MAP()


// CDlgSerial4 message handlers

BOOL CDlgSerial4::OnInitDialog()
{
	CDialog::OnInitDialog();
	InitUI();

	SetWindowText(m_strDlgName);


	// TODO:  Add extra initialization here

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgSerial4::InitUI(void)
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


	SetTimer(1, loopTime, NULL);



}

BOOL CDlgSerial4::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->message == WM_LBUTTONDOWN)
	{
		if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_JOGM)->m_hWnd)
		{
			((CButton*)GetDlgItem(IDC_BUTTON_JOGM))->SetState(TRUE);

			makeJOG(-1, m_axis[0]);
			return TRUE;

		}
		if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_JOGP)->m_hWnd)
		{
			((CButton*)GetDlgItem(IDC_BUTTON_JOGP))->SetState(TRUE);
			makeJOG(1, m_axis[0]);
			return TRUE;
		}

		if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_JOGM2)->m_hWnd)
		{
			((CButton*)GetDlgItem(IDC_BUTTON_JOGM2))->SetState(TRUE);

			makeJOG(-1, m_axis[1]);
			return TRUE;

		}
		if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_JOGP2)->m_hWnd)
		{
			((CButton*)GetDlgItem(IDC_BUTTON_JOGP2))->SetState(TRUE);
			makeJOG(1, m_axis[1]);
			return TRUE;
		}

	}

	if (pMsg->message==WM_LBUTTONUP)
	{
		if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_JOGP)->m_hWnd) 
		{
			((CButton*)GetDlgItem(IDC_BUTTON_JOGP))->SetState(FALSE);
			makeJOG(0, m_axis[0]);
			return TRUE;
		}

		if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_JOGM)->m_hWnd)
		{
			((CButton*)GetDlgItem(IDC_BUTTON_JOGM))->SetState(FALSE);
			makeJOG(0, m_axis[0]);
			return TRUE;
		}

		if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_JOGP2)->m_hWnd) 
		{
			((CButton*)GetDlgItem(IDC_BUTTON_JOGP2))->SetState(FALSE);
			makeJOG(0, m_axis[1]);
			return TRUE;
		}

		if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_JOGM2)->m_hWnd)
		{
			((CButton*)GetDlgItem(IDC_BUTTON_JOGM2))->SetState(FALSE);
			makeJOG(0, m_axis[1]);
			return TRUE;
		}

	}

	return CDialog::PreTranslateMessage(pMsg);
}


void CDlgSerial4::OnTimer(UINT_PTR nIDEvent)
{
	switch(nIDEvent)
	{

	case 1:
		loopComm();	
		break;

	case 2:
		start(nIDEvent, &m_ctrlMode, m_axis[0], m_port);
		break;

	case 3:
		start(nIDEvent, &m_ctrlMode, m_axis[1], m_port);
		break;

	}

	CDialog::OnTimer(nIDEvent);
}


void CDlgSerial4::OnBnClickedButtonstart()
{
	UpdateData();

	if(CPublic::portIsOpen[m_port - 1] == false)
	{
		mainDlg->AddString(_T("该串口未打开，请先打开串口！"));
		return;
	}

	closeLoopComm(1);
	CPublic::commCount = 0;
	SetTimer(2, myStartTime, NULL);

}

void CDlgSerial4::OnBnClickedButtonstop()
{
	settingComm(_T("STOP "), m_axis[0]);
}

void CDlgSerial4::OnBnClickedButtonpluslimit()
{
	settingComm(_T("FFPL "), m_axis[0]);
}

void CDlgSerial4::OnBnClickedButtonzeroswitch()
{
	settingComm(_T("FFRL "), m_axis[0]);
}

void CDlgSerial4::OnBnClickedButtonminuslimit()
{
	settingComm(_T("FFNL "), m_axis[0]);
}

void CDlgSerial4::OnBnClickedButtonabszero()
{
	settingComm(_T("DHOM "), m_axis[0]);

}

void CDlgSerial4::OnBnClickedButtonfindzero()
{
	settingComm(_T("GHOM "), m_axis[0]);

}

void CDlgSerial4::OnCbnSelchangeCombounit()
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

void CDlgSerial4::settingComm(CString comm, int axisNum)
{
	if(CPublic::portIsOpen[m_port - 1] == false)
	{
		mainDlg->AddString(_T("该串口未打开，请先打开串口！"));
		return;
	}

	closeLoopComm(1);

	m_sendData =  comm + CPublic::int2CString(axisNum);
	mainDlg->sendComm(m_sendData, m_port);
	//Sleep(500);
	openLoopComm(1);
}


void CDlgSerial4::makeJOG(int sign, int axisNum)
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

void CDlgSerial4::switchLight(int neg, int zero, int pos, int axisNum)
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
	}
}

void CDlgSerial4::start(UINT_PTR nIDEvent, CComboBox* ctrlMode, int axisNum, int port)
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
		//mainDlg->AddString(CPublic::receiveData[m_port - 1]);

		int startspeed = (axisNum == m_axis[0]) ? m_startspeed * m_unit : m_startspeed2 * m_unit2;
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
		//mainDlg->AddString(CPublic::receiveData[m_port - 1]);

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
		//mainDlg->AddString(CPublic::receiveData[m_port - 1]);
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

		//mainDlg->AddString(CPublic::receiveData[m_port - 1]);

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

		//mainDlg->AddString(CPublic::receiveData[m_port - 1]);
		KillTimer(nIDEvent);
		openLoopComm(1);
	}


	CPublic::commCount++;
}

void CDlgSerial4::loopComm(void)
{
	if (m_bLoop == true)
	{
		UpdateData();

		if (m_loopCommNum == 0)
		{
			if (CPublic::bfindTerminator[m_port - 1] == false)
				return;
			mainDlg->sendComm(_T("POS? ") + CPublic::int2CString(m_axis[0]), m_port);		
		}

		if (m_loopCommNum == 1)
		{
			if (CPublic::bfindTerminator[m_port - 1] == false)
				return;

			SetDlgItemText(IDC_EDIT_absPostion, CPublic::receiveData[m_port - 1]);
			//SetDlgItemText(IDC_EDIT_absPostion, explainPos(CPublic::receiveData[m_port - 1]));

			//UpdateData(FALSE);

			mainDlg->sendComm(_T("LIM? ") + CPublic::int2CString(m_axis[0]), m_port);		

		}

		if (m_loopCommNum == 2)
		{
			if (CPublic::bfindTerminator[m_port - 1] == false)
				return;

			CString t = CPublic::receiveData[m_port - 1];

			switchLight(CPublic::explainLim(t, -1), CPublic::explainLim(t, 0),
				CPublic::explainLim(t, 1), CPublic::explainLim(t, 2));
			//UpdateData(FALSE);	

			mainDlg->sendComm(_T("POS? ") + CPublic::int2CString(m_axis[1]), m_port);		

		}

		if (m_loopCommNum == 3)
		{
			if (CPublic::bfindTerminator[m_port - 1] == false)
				return;
			SetDlgItemText(IDC_EDIT_absPostion2, CPublic::receiveData[m_port - 1]);
			//SetDlgItemText(IDC_EDIT_absPostion2, explainPos(CPublic::receiveData[m_port - 1]));
			//UpdateData(FALSE);

			mainDlg->sendComm(_T("LIM? ") + CPublic::int2CString(m_axis[1]), m_port);		

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

void CDlgSerial4::openLoopComm(UINT_PTR nIDEvent)
{
	SetTimer(nIDEvent, loopTime, NULL);
	m_loopCommNum = 0;
	m_bLoop = true;
}

void CDlgSerial4::closeLoopComm(UINT_PTR nIDEvent)
{
	KillTimer(nIDEvent);
	m_bLoop = false;
}

void CDlgSerial4::OnBnClickedButtonstart2()
{
	UpdateData();

	if(CPublic::portIsOpen[m_port - 1] == false)
	{
		mainDlg->AddString(_T("该串口未打开，请先打开串口！"));
		return;
	}

	closeLoopComm(1);
	CPublic::commCount = 0;
	SetTimer(3, myStartTime, NULL);
}

void CDlgSerial4::OnBnClickedButtonstop2()
{
	settingComm(_T("STOP "), m_axis[1]);
}

void CDlgSerial4::OnBnClickedButtonpluslimit2()
{
	settingComm(_T("FFPL "), m_axis[1]);

}

void CDlgSerial4::OnBnClickedButtonzeroswitch2()
{
	settingComm(_T("FFRL "), m_axis[1]);

}

void CDlgSerial4::OnBnClickedButtonminuslimit2()
{
	settingComm(_T("FFNL "), m_axis[1]);

}

void CDlgSerial4::OnBnClickedButtonabszero2()
{
	settingComm(_T("DHOM "), m_axis[1]);

}

void CDlgSerial4::OnBnClickedButtonfindzero2()
{
	settingComm(_T("GHOM "), m_axis[1]);

}


void CDlgSerial4::OnCbnSelchangeCombounit2()
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

void CDlgSerial4::setPara(void)
{
	int index[2] = {0};
	int i = (_T("工位2-装配机械手手动调整") == m_strDlgName) ? 1 : 2;
	index[0] = m_axis[0] + i * 9 - 1;
	index[1] = m_axis[1] + i * 9 - 1;

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

	UpdateData(FALSE);

}

void CDlgSerial4::OnBnClickedButtonsave4()
{
	UpdateData();

	int index[2] = {0};
	int i = (_T("工位2-装配机械手手动调整") == m_strDlgName) ? 1 : 2;
	index[0] = m_axis[0] + i * 9 - 1;
	index[1] = m_axis[1] + i * 9 - 1;

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


	mainDlg->updateAxisParameter2Value(para, index, 2, true);
	mainDlg->updateValue2File(index, 2, true);
}

void CDlgSerial4::OnBnClickedButtondefault4()
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

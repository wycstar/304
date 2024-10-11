// AutoSettingDlg.cpp : implementation file
//

#include "stdafx.h"
#include "controlSerialNetPort.h"
#include "AutoSettingDlg.h"


// CAutoSettingDlg dialog

IMPLEMENT_DYNAMIC(CAutoSettingDlg, CDialog)

CAutoSettingDlg::CAutoSettingDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAutoSettingDlg::IDD, pParent)
{
	m_stepsError = CPublic::stepsError;
	m_sensorError = CPublic::sensorError;
}

CAutoSettingDlg::~CAutoSettingDlg()
{
}

void CAutoSettingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_BUTTON_autosave, m_bstsave);
	DDX_Control(pDX, IDC_BUTTON_autodefault, m_bstdefault);
	DDX_Control(pDX, IDC_TAB_AUTO, m_ctrlTab);
	DDX_Text(pDX, IDC_EDIT_stepserror, m_stepsError);
	DDX_Text(pDX, IDC_EDIT_sensorError, m_sensorError);
	DDX_Control(pDX, IDC_COMBO_WORKNUM, m_ctrlWorkNum);
}


BEGIN_MESSAGE_MAP(CAutoSettingDlg, CDialog)
	ON_WM_DESTROY()
	ON_WM_CLOSE()
//	ON_WM_VSCROLL()
	ON_BN_CLICKED(IDC_BUTTON_autosave, &CAutoSettingDlg::OnBnClickedButtonautosave)
	ON_BN_CLICKED(IDC_BUTTON_autodefault, &CAutoSettingDlg::OnBnClickedButtonautodefault)
//	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_AUTO, &CAutoSettingDlg::OnTcnSelchangeTabAuto)
	ON_CBN_SELCHANGE(IDC_COMBO_WORKNUM, &CAutoSettingDlg::OnCbnSelchangeComboWorknum)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_sensorError, &CAutoSettingDlg::OnDeltaposSpinsensorerror)
END_MESSAGE_MAP()


// CAutoSettingDlg message handlers

void CAutoSettingDlg::OnDestroy()
{
	CDialog::OnDestroy();
}

void CAutoSettingDlg::OnClose()
{
	// TODO: Add your message handler code here and/or call default

	CDialog::OnClose();

	/*if (NULL != this)
	{
		delete this;
	}*/


	
}

BOOL CAutoSettingDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_bstsave.SetIcon(IDI_ICON_save32);
	m_bstsave.SetTooltipText(_T("保存配置"));
	m_bstdefault.SetIcon(IDI_ICON_default32);
	m_bstdefault.SetTooltipText(_T("设置默认值"));

	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_stepsError))->SetRange32(0,0x7fffffff);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_sensorError))->SetRange32(-10000,10000);

	for (int i = 0; i < MAX_CAM; i++)
	{
		m_ctrlWorkNum.InsertString(i, _T("工位") + CPublic::int2CString(i+1));
	}
	m_ctrlWorkNum.SetCurSel(0);

	//CSpinButtonCtrl* pErrorSpin = (CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_sensorError);  
	//pErrorSpin->SetRange(-10000, 10000);  
	//pErrorSpin->GetBuddy()->SetWindowText(_T("0.001"));  

	//m_ctrlTab.InsertItem(0, _T("初始化参数设置")); 
	//m_ctrlTab.InsertItem(1, _T("工位自动操作参数设置"));

	m_pageAutoInitDlg.Create(IDD_DIALOG_AUTOINIT, GetDlgItem(IDC_TAB_AUTO)); 
	//m_pageAutoDlg.Create(IDD_DIALOG_AUTO, GetDlgItem(IDC_TAB_AUTO)); 
	// 将子窗口显示在m_Tab范围内 
	CRect rs; 
	m_ctrlTab.GetClientRect(rs); 
	//rs.top+=20; 
	rs.bottom-=4; 
	//rs.left+=4; 
	rs.right-=4; 
	m_pageAutoInitDlg.MoveWindow(rs); 
	//m_pageAutoDlg.MoveWindow(rs); 
	// 默认显示第一个子窗口 
	m_ctrlTab.SetCurSel(0); 
	m_pageAutoInitDlg.ShowWindow(TRUE);

	m_stepsError = CPublic::stepsError;
	m_sensorError = CPublic::sensorError;

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

//void CAutoSettingDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
//{
//	// TODO: Add your message handler code here and/or call default
//	/*switch(pScrollBar->GetDlgCtrlID())     
//	{     
//		case IDC_SPIN_sensorError:      
//		{     
//			int pos = (int)nPos;
//			double nStep=0.001;   
//			CString str;     
//			str.Format(_T("%.3f"), (double)pos * nStep);  
//			((CSpinButtonCtrl*) pScrollBar)->GetBuddy()->SetWindowText(str);  
//			break;  
//		}     
//		break;     
//	}  */
//	UpdateData();
//	int i = m_sensorError;
//
//	//Spin Button
//	if( pScrollBar->GetDlgCtrlID() == IDC_SPIN_sensorError )
//	{
//		CString strValue;
//		strValue.Format( _T("%3.3f"), (double)nPos / 1000.0 );
//		//((CSpinButtonCtrl*)pScrollBar)->GetBuddy()->SetWindowTextW( strValue );
//		CEdit* pEdit =(CEdit*) ((CSpinButtonCtrl*)pScrollBar)->GetBuddy();
//		pEdit->SetWindowText( strValue );
//	}
//
//	CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
//}

void CAutoSettingDlg::OnBnClickedButtonautosave()
{
	UpdateData();

	//CPublic::g_workNum = m_ctrlWorkNum.GetCurSel();

	CPublic::stepsError = m_stepsError;
	CPublic::sensorError = m_sensorError;

	::PostMessage(m_pageAutoInitDlg.m_hWnd, SAVE_PARATOFILE, 0, m_ctrlWorkNum.GetCurSel());
}

void CAutoSettingDlg::OnBnClickedButtonautodefault()
{
	UpdateData();

	//CPublic::g_workNum = m_ctrlWorkNum.GetCurSel();

	::PostMessage(m_pageAutoInitDlg.m_hWnd, RECOVER_UIPARA, 0, m_ctrlWorkNum.GetCurSel());

}

//void CAutoSettingDlg::OnTcnSelchangeTabAuto(NMHDR *pNMHDR, LRESULT *pResult)
//{
//	// TODO: Add your control notification handler code here
//
//	if ((m_ctrlTab.GetCurSel() == 0))
//	{
//		m_pageAutoInitDlg.ShowWindow(TRUE);
//		//m_pageAutoDlg.ShowWindow(FALSE);
//		::PostMessage(m_pageAutoInitDlg.m_hWnd, LOAD_FILETOPARA, 0, m_ctrlWorkNum.GetCurSel());
//	}else
//	{
//		m_pageAutoInitDlg.ShowWindow(FALSE);
//		//m_pageAutoDlg.ShowWindow(TRUE);
//		//::PostMessage(m_pageAutoDlg.m_hWnd, LOAD_FILETOPARA, 0, m_ctrlWorkNum.GetCurSel());
//	}
//
//	*pResult = 0;
//}

void CAutoSettingDlg::OnCbnSelchangeComboWorknum()
{
	::PostMessage(m_pageAutoInitDlg.m_hWnd, LOAD_FILETOPARA, 0, m_ctrlWorkNum.GetCurSel());

}

void CAutoSettingDlg::OnDeltaposSpinsensorerror(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: Add your control notification handler code here

	OnDeltaposSpinAll(pNMHDR, pResult, true);
	*pResult = 0;
}

void CAutoSettingDlg::OnDeltaposSpinAll(NMHDR *pNMHDR, LRESULT *pResult, bool littleNum)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);


	// TODO: Add your control notification handler code here
	MSG* pMsg = (MSG*)GetCurrentMessage(); // 得到你当前正在处理的消息的MSG结构  
	UINT nID = LOWORD(pMsg->wParam);    // 消息wParam参数的低16位为发送消息的控件ID  
	CWnd* pWnd = ((CSpinButtonCtrl*)GetDlgItem(nID))->GetBuddy();  

	if (littleNum == true)
	{
		SpinChange(pNMUpDown,pWnd, 0.001, 2);  

	} 
	else  
	{  
		SpinChange(pNMUpDown, pWnd);  
	}
	((CSpinButtonCtrl*)GetDlgItem(nID))->SetFocus();

	*pResult = 0;
}

void CAutoSettingDlg::SpinChange(NM_UPDOWN* pNMUpDown,CWnd* pWnd,double fstep,int iFormat)  
{  
	CString strValue;  
	pWnd->GetWindowText(strValue); //得到编辑框中的内容  
	double fvalue;  
	if(pNMUpDown->iDelta > 0) //如果点击的是Spin中的往上按钮  
	{  
		double pos = _tstof(strValue); 
		fvalue = pos + fstep;  
	}  
	else if(pNMUpDown->iDelta < 0) //如果点击的是Spin中往下按钮  
	{  
		double pos = _tstof(strValue); 
		fvalue = pos - fstep;//此处预防0.1-0.1 != 0 时，出现-0.0的情况  
	}  

	switch(iFormat)  
	{  
	case 1:  
		strValue.Format(_T("%d"),int(fvalue));  
		break;  
	case 2:  
		strValue.Format(_T("%10.3f"),fvalue);  
		break;  
	default:  
		break;  
	}  
	pWnd->SetWindowText(strValue); //保存修改  

	//((CEdit*)pWnd)->SetSel(strValue.GetLength(), 0);	

	int len = strValue.GetLength();
	//((CEdit*)pWnd)->PostMessage(WM_KILLFOCUS, 0, 0);
	/*((CEdit*)pWnd)->SetFocus();
	((CEdit*)pWnd)->SetSel(-1);*/


	//GetNextDlgTabItem(pWnd)->SetFocus();




	//数据校检  
	CDataExchange dx(this, true);     
	TRY  
	{  
		DoDataExchange(&dx);  
	}  
	CATCH(CUserException, e)  
	{  

	}  
	AND_CATCH_ALL(e)  
	{  

	}  
	END_CATCH_ALL 

}  

// AutoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "controlSerialNetPort.h"
#include "AutoDlg.h"
#include "Public.h"
#include "controlSerialNetPortDlg.h"


// CAutoInitDlg dialog
extern CcontrolSerialNetPortDlg* mainDlg;

// CAutoDlg dialog

IMPLEMENT_DYNAMIC(CAutoDlg, CDialog)

CAutoDlg::CAutoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAutoDlg::IDD, pParent)

	, m_workNum(0)
{
	//m_delayTime2 = 0;
	//memset(m_steps4, 0, 6);
	////m_steps4 = 0;
	//m_steps5_1 = 0;
	//m_steps5_2 = 0;
	//m_steps6 = 0;
	//m_delayTime7 = 0;
	//m_delayTime8 = 0;
	//m_steps9 = 0;
	//m_steps10_1 = 0;
	//m_steps10_2 = 0;
	//m_steps10_3 = 0;
	//m_delayTime10 = 0;
	//m_steps10_4 = 0;
	//m_steps10_5 = 0;
	//m_steps10_6 = 0;
	//m_delayTime11 = 0;
	//m_steps11 = 0;
	//m_dispense1 = 0;
	//m_dispense2 = 0;
	//memset(m_dispenseA, 0, 6);

	/*m_angelErrorX = 0;
	m_angelErrorY = 0;
	m_ratioX = 1;
	m_ratioY = 1;
	m_ratioA = 1;

	m_searchSpeedMode = 0;
	m_maxMatchNum = 16;
	m_matchNum = 1;
	m_modelFilePath = _T("D:\\MOBAN\\1.dxf");
	m_smoothness = 70; 
	m_iterationNum = 200;
	m_modelDistance = 0;
	m_ROIx = 900;
	m_ROIy = 900;
	m_ROIw = 800;
	m_ROIh = 80;*/
}

CAutoDlg::~CAutoDlg()
{
}

void CAutoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	/*DDX_Text(pDX, IDC_EDIT_handIn, m_delayTime2);
	DDX_Text(pDX, IDC_EDIT_handdown, m_steps4[0]);
	DDX_Text(pDX, IDC_EDIT_handdown2, m_steps4[1]);
	DDX_Text(pDX, IDC_EDIT_handdown3, m_steps4[2]);
	DDX_Text(pDX, IDC_EDIT_handdown4, m_steps4[3]);
	DDX_Text(pDX, IDC_EDIT_handdown5, m_steps4[4]);
	DDX_Text(pDX, IDC_EDIT_handdown6, m_steps4[5]);
	DDX_Text(pDX, IDC_EDIT_handrotate, m_steps5_1);
	DDX_Text(pDX, IDC_EDIT_handrotate2, m_steps5_2);
	DDX_Text(pDX, IDC_EDIT_openprism, m_steps6);
	DDX_Text(pDX, IDC_EDIT_uplight, m_delayTime7);
	DDX_Text(pDX, IDC_EDIT_downlight, m_delayTime8);
	DDX_Text(pDX, IDC_EDIT_closeprism, m_steps9);
	DDX_Text(pDX, IDC_EDIT_microAdjust1, m_steps10_1);
	DDX_Text(pDX, IDC_EDIT_microAdjust2, m_steps10_2);
	DDX_Text(pDX, IDC_EDIT_microAdjust3, m_steps10_3);
	DDX_Text(pDX, IDC_EDIT_microAdjusttime, m_delayTime10);
	DDX_Text(pDX, IDC_EDIT_microAdjust4, m_steps10_4);
	DDX_Text(pDX, IDC_EDIT_microAdjust5, m_steps10_5);
	DDX_Text(pDX, IDC_EDIT_microAdjust6, m_steps10_6);
	DDX_Text(pDX, IDC_EDIT_handZdown, m_steps11);
	DDX_Text(pDX, IDC_EDIT_handZdownTime, m_delayTime11);
	DDX_Text(pDX, IDC_EDIT_dipense1, m_dispense1);
	DDX_Text(pDX, IDC_EDIT_dipense2, m_dispense2);
	DDX_Text(pDX, IDC_EDIT_dispenseA, m_dispenseA[0]);
	DDX_Text(pDX, IDC_EDIT_dispenseA2, m_dispenseA[1]);
	DDX_Text(pDX, IDC_EDIT_dispenseA3, m_dispenseA[2]);
	DDX_Text(pDX, IDC_EDIT_dispenseA4, m_dispenseA[3]);
	DDX_Text(pDX, IDC_EDIT_dispenseA5, m_dispenseA[4]);
	DDX_Text(pDX, IDC_EDIT_dispenseA6, m_dispenseA[5]);*/

	/*DDX_Text(pDX, IDC_EDIT_angleErrorX, m_angelErrorX);
	DDX_Text(pDX, IDC_EDIT_angleErrorY, m_angelErrorY);
	DDX_Text(pDX, IDC_EDIT_Xratio, m_ratioX);
	DDX_Text(pDX, IDC_EDIT_Yratio, m_ratioY);
	DDX_Text(pDX, IDC_EDIT_Aratio, m_ratioA);


	DDX_Text(pDX, IDC_EDIT_maxMatchNum, m_maxMatchNum);
	DDX_Text(pDX, IDC_EDIT_MatchNum, m_matchNum);
	DDX_Text(pDX, IDC_EDIT_Smoothness, m_smoothness);
	DDX_Text(pDX, IDC_EDIT_iterationNum, m_iterationNum);
	DDX_Text(pDX, IDC_EDIT_modelDistance, m_modelDistance);
	DDX_Text(pDX, IDC_EDIT_ROIX, m_ROIx);
	DDX_Text(pDX, IDC_EDIT_ROIY, m_ROIy);
	DDX_Text(pDX, IDC_EDIT_ROIW, m_ROIw);
	DDX_Text(pDX, IDC_EDIT_ROIH, m_ROIh);  
	DDX_Control(pDX, IDC_COMBO_ROUND, m_cmbRound);
	DDX_Control(pDX, IDC_COMBO_PROCESSNUM, m_cmbProcessNum);
	DDX_CBIndex(pDX, IDC_COMBO_searchSpeedMode, m_searchSpeedMode);
	DDX_Text(pDX, IDC_EDIT_MODELPATH, m_modelFilePath);*/
}


BEGIN_MESSAGE_MAP(CAutoDlg, CDialog)
	ON_MESSAGE(SAVE_PARATOFILE, OnSavePara)
	ON_MESSAGE(RECOVER_UIPARA, OnUpdateUIPara)
	ON_MESSAGE(LOAD_FILETOPARA, OnLoadPara)
//	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_ROIX2, &CAutoDlg::OnDeltaposSpinRoix2)
//ON_BN_CLICKED(IDC_BUTTON_MODELPATH, &CAutoDlg::OnBnClickedButtonModelpath)
//ON_CBN_SELCHANGE(IDC_COMBO_ROUND, &CAutoDlg::OnCbnSelchangeComboRound)
//ON_EN_CHANGE(IDC_EDIT_angleError2, &CAutoDlg::OnEnChangeEditangleerror2)
//ON_CBN_SELCHANGE(IDC_COMBO_PROCESSNUM, &CAutoDlg::OnCbnSelchangeComboProcessnum)
//ON_EN_CHANGE(IDC_EDIT_microAdjust12, &CAutoDlg::OnEnChangeEditmicroadjust12)
END_MESSAGE_MAP()


// CAutoDlg message handlers

BOOL CAutoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	//((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_handIn))->SetRange32(0,0x7fffffff);
	//((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_handdown))->SetRange32(0,0x7fffffff);
	//((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_handrotate))->SetRange32(0,0x7fffffff);
	//((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_handrotate2))->SetRange32(0,0x7fffffff);
	//((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_openprism))->SetRange32(0,0x7fffffff);
	//((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_uplight))->SetRange32(0,0x7fffffff);
	//((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_downlight))->SetRange32(0,0x7fffffff);
	//((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_closeprism))->SetRange32(0,0x7fffffff);
	//((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_microAdjust1))->SetRange32(0,0x7fffffff);
	//((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_microAdjust2))->SetRange32(0,0x7fffffff);
	//((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_microAdjust3))->SetRange32(0,0x7fffffff);
	//((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_microAdjusttime))->SetRange32(0,0x7fffffff);
	//((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_handZdown))->SetRange32(0,0x7fffffff);
	//((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_handZdownTime))->SetRange32(0,0x7fffffff);

	//((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_angleError))->SetRange32(0,0x7fffffff);
	//((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN__Xratio))->SetRange32(0,0x7fffffff);
	//((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_Yratio))->SetRange32(0,0x7fffffff);
	//((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_Aratio))->SetRange32(0,0x7fffffff);

	//((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_maxMatchNum))->SetRange32(0,0x7fffffff);
	//((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_MatchNum))->SetRange32(0,0x7fffffff);
	//((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_Smoothness))->SetRange32(0,0x7fffffff);
	//((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_iterationNum))->SetRange32(0,0x7fffffff);
	//((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_ROIX))->SetRange32(0,0x7fffffff);
	//((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_ROIY))->SetRange32(0,0x7fffffff);
	//((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_ROIW))->SetRange32(0,0x7fffffff);
	//((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_ROIH))->SetRange32(0,0x7fffffff);

	setPara(0);
	//m_cmbRound.SetCurSel(0);
	//m_cmbProcessNum.SetCurSel(0);
	setImagePara(0);
	

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CAutoDlg::setPara(int workNum)
{
	//m_delayTime2 = CPublic::g_AutoParameter[workNum].delayTime2;
	////memcpy(m_steps4, CPublic::g_AutoParameter[workNum].steps4, 6);
	//m_steps5_1 = CPublic::g_AutoParameter[workNum].steps5_1;
	//m_steps5_2 = CPublic::g_AutoParameter[workNum].steps5_2;
	//m_steps6 = CPublic::g_AutoParameter[workNum].steps6;
	//m_delayTime7 = CPublic::g_AutoParameter[workNum].delayTime7;
	//m_delayTime8 = CPublic::g_AutoParameter[workNum].delayTime8;
	//m_steps9 = CPublic::g_AutoParameter[workNum].steps9;
	//m_steps10_1 = CPublic::g_AutoParameter[workNum].steps10_1;
	//m_steps10_2 = CPublic::g_AutoParameter[workNum].steps10_2;
	//m_steps10_3 =  CPublic::g_AutoParameter[workNum].steps10_3;
	//m_delayTime10 = CPublic::g_AutoParameter[workNum].delayTime10;
	//m_steps10_4 = CPublic::g_AutoParameter[workNum].steps10_4;
	//m_steps10_5 = CPublic::g_AutoParameter[workNum].steps10_5;
	//m_steps10_6 =  CPublic::g_AutoParameter[workNum].steps10_6;
	//m_delayTime11 = CPublic::g_AutoParameter[workNum].delayTime11;
	//m_steps11 = CPublic::g_AutoParameter[workNum].steps11;
	//m_dispense1 = CPublic::g_AutoParameter[workNum].dispense1;
	//m_dispense2 = CPublic::g_AutoParameter[workNum].dispense2;
	//memcpy(m_dispenseA, CPublic::g_AutoParameter[workNum].dispenseA, 6);

	/*m_angelErrorX = CPublic::g_AutoParameter[workNum].angErrorX;
	m_angelErrorY = CPublic::g_AutoParameter[workNum].angErrorY;
	m_ratioX = CPublic::g_AutoParameter[workNum].ratioX;
	m_ratioY = CPublic::g_AutoParameter[workNum].ratioY;
	m_ratioA = CPublic::g_AutoParameter[workNum].ratioA;

	for (int i = 0; i < 6; i++)
	{
		m_steps4[i] = CPublic::g_AutoParameter[workNum].steps4[i];
		m_dispenseA[i] = CPublic::g_AutoParameter[workNum].dispenseA[i];
	}*/


	UpdateData(FALSE);
}

void CAutoDlg::setImagePara(int workNum)
{
	//int round = m_cmbRound.GetCurSel();
	//int proNum = m_cmbProcessNum.GetCurSel();
	// 

	//m_maxMatchNum = CPublic::g_imagePara[workNum][round][proNum].maxMatchNum;
	//m_matchNum = CPublic::g_imagePara[workNum][round][proNum].matchNum;
	//m_modelFilePath = CPublic::g_imagePara[workNum][round][proNum].modelFilePath;
	//m_smoothness = CPublic::g_imagePara[workNum][round][proNum].smoothness;
	//m_iterationNum = CPublic::g_imagePara[workNum][round][proNum].iterationNum;
	//m_modelDistance = CPublic::g_imagePara[workNum][round][proNum].modelDistance;
	//m_ROIx = CPublic::g_imagePara[workNum][round][proNum].ROI_x;
	//m_ROIy = CPublic::g_imagePara[workNum][round][proNum].ROI_y;
	//m_ROIw = CPublic::g_imagePara[workNum][round][proNum].ROI_w;
	//m_ROIh = CPublic::g_imagePara[workNum][round][proNum].ROI_h;
	////m_cmbRound.SetCurSel(CPublic::g_imagePara[workNum][round].);
	//m_searchSpeedMode = CPublic::g_imagePara[workNum][round][proNum].searchSpeedMode;



	UpdateData(FALSE);
}

LRESULT CAutoDlg::OnSavePara(WPARAM WP, LPARAM LP)
{
	UpdateData();

	int workNum = (int)LP;

	//CPublic::g_AutoParameter[workNum].delayTime2 = m_delayTime2;
	////memcpy(CPublic::g_AutoParameter[workNum].steps4, m_steps4, 6);
	////CPublic::g_AutoParameter[workNum].steps4 = m_steps4;
	//CPublic::g_AutoParameter[workNum].steps5_1 = m_steps5_1;
	//CPublic::g_AutoParameter[workNum].steps5_2 = m_steps5_2;
	//CPublic::g_AutoParameter[workNum].steps6 = m_steps6;
	//
	//CPublic::g_AutoParameter[workNum].delayTime7 = m_delayTime7;
	//CPublic::g_AutoParameter[workNum].delayTime8 = m_delayTime8;
	//CPublic::g_AutoParameter[workNum].steps9 = m_steps9;
	//CPublic::g_AutoParameter[workNum].steps10_1 = m_steps10_1;
	//CPublic::g_AutoParameter[workNum].steps10_2 = m_steps10_2;
	//CPublic::g_AutoParameter[workNum].steps10_3=  m_steps10_3 ;
	//CPublic::g_AutoParameter[workNum].delayTime10 = m_delayTime10;
	//CPublic::g_AutoParameter[workNum].steps10_4 = m_steps10_4;
	//CPublic::g_AutoParameter[workNum].steps10_5 = m_steps10_5;
	//CPublic::g_AutoParameter[workNum].steps10_6=  m_steps10_6 ;

	//CPublic::g_AutoParameter[workNum].delayTime11 = m_delayTime11;
	//CPublic::g_AutoParameter[workNum].steps11 = m_steps11;

	//CPublic::g_AutoParameter[workNum].dispense1 = m_dispense1;
	//CPublic::g_AutoParameter[workNum].dispense2 = m_dispense2;
	//memcpy(CPublic::g_AutoParameter[workNum].dispenseA, m_dispenseA, 6);

	/*CPublic::g_AutoParameter[workNum].angErrorX = m_angelErrorX;
	CPublic::g_AutoParameter[workNum].angErrorY = m_angelErrorY;
	CPublic::g_AutoParameter[workNum].ratioX = m_ratioX;
	CPublic::g_AutoParameter[workNum].ratioY = m_ratioY;
	CPublic::g_AutoParameter[workNum].ratioA = m_ratioA;

	for (int i = 0; i < 6; i++)
	{
		CPublic::g_AutoParameter[workNum].steps4[i] = m_steps4[i];
		CPublic::g_AutoParameter[workNum].dispenseA[i] = m_dispenseA[i];
	}

	int round = m_cmbRound.GetCurSel();
	int proNum = m_cmbProcessNum.GetCurSel();


	CPublic::g_imagePara[workNum][round][proNum].maxMatchNum = m_maxMatchNum;
	CPublic::g_imagePara[workNum][round][proNum].matchNum = m_matchNum;
	CPublic::g_imagePara[workNum][round][proNum].modelFilePath = m_modelFilePath;
	CPublic::g_imagePara[workNum][round][proNum].smoothness = m_smoothness;
	CPublic::g_imagePara[workNum][round][proNum].iterationNum = m_iterationNum;
	CPublic::g_imagePara[workNum][round][proNum].modelDistance = m_modelDistance;
	CPublic::g_imagePara[workNum][round][proNum].ROI_x = m_ROIx;
	CPublic::g_imagePara[workNum][round][proNum].ROI_y = m_ROIy;
	CPublic::g_imagePara[workNum][round][proNum].ROI_w = m_ROIw;
	CPublic::g_imagePara[workNum][round][proNum].ROI_h = m_ROIh;
	CPublic::g_imagePara[workNum][round][proNum].searchSpeedMode = m_searchSpeedMode;
*/



	//mainDlg->updateAutoValue2File(workNum, round, proNum, true);

	return 0;



	//mainDlg->updateAxisParameter2Value(para, axis, 2, true);
	//mainDlg->updateValue2File(axis, 2, true);

}

LRESULT CAutoDlg::OnUpdateUIPara(WPARAM WP, LPARAM LP)
{
	UpdateData();

	/*m_delayTime2 = 0;
	memset(m_steps4, 0, 6);
	m_steps5_1 = 0;
	m_steps5_2 = 0;
	m_steps6 = 0;
	m_delayTime7 = 0;
	m_delayTime8 = 0;
	m_steps9 = 0;
	m_steps10_1 = 0;
	m_steps10_2 = 0;
	m_steps10_3 =  0;
	m_delayTime10 = 0;
	m_steps10_4 = 0;
	m_steps10_5 = 0;
	m_steps10_6 =  0;
	m_steps11 = 0;
	m_delayTime11 = 0;
	m_dispense1 = 0;
	m_dispense2 = 0;
	memset(m_dispenseA, 0, 6);

	m_angelErrorX = 0;
	m_angelErrorY = 0;
	m_ratioX = 1;
	m_ratioY = 1;
	m_ratioA = 1;

	m_searchSpeedMode = 0;
	m_maxMatchNum = 16;
	m_matchNum = 1;
	m_modelFilePath = _T("D:\\MOBAN\\1.dxf");
	m_smoothness = 70; 
	m_iterationNum = 200;
	m_modelDistance = 0;
	m_ROIx = 900;
	m_ROIy = 900;
	m_ROIw = 800;
	m_ROIh = 80;

	UpdateData(FALSE);*/

	return 0;

}

LRESULT CAutoDlg::OnLoadPara(WPARAM WP, LPARAM LP)
{
	UpdateData();
	m_workNum = (int)LP;

	setPara(m_workNum);
	setImagePara(m_workNum);
	UpdateData(FALSE);

	return 0;

}

//void CAutoDlg::OnDeltaposSpinRoix2(NMHDR *pNMHDR, LRESULT *pResult)
//{
//	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
//	// TODO: Add your control notification handler code here
//	*pResult = 0;
//}

//void CAutoDlg::OnBnClickedButtonModelpath()
//{
//	UpdateData(TRUE);
//	CString strPath;
//	CFileDialog dlg(TRUE, NULL, NULL, NULL,  _T("文件(*.DXF)|*.dxf|"), NULL );///TRUE为OPEN对话框，FALSE为SAVE AS对话框
//	if(dlg.DoModal() == IDOK)
//		strPath =  dlg.GetPathName();
//	m_modelFilePath = pathSwitch(strPath);
//
//	GetDlgItem(IDC_EDIT_MODELPATH)->SetWindowText(m_modelFilePath); //显示路径
//	
//	//GetDlgItem(IDC_EDIT_MODELPATH)->UpdateData(FALSE);
//
//}

CString CAutoDlg::pathSwitch(CString strPath)
{
	int index = 0;
	int pos = 0;
	//CString strNewPath = strPath;
	while(1)
	{
		pos = strPath.Find('\\', index);
		
		if (pos == -1)
			break;
		strPath.Insert(pos, '\\');
		index = pos + 2;

	}

	return strPath;

}

//void CAutoDlg::OnCbnSelchangeComboRound()
//{
	//int round = m_cmbRound.GetCurSel();
	//int proNum = m_cmbProcessNum.GetCurSel();
	//int workNum = m_workNum;

	//m_maxMatchNum = CPublic::g_imagePara[workNum][round][proNum].maxMatchNum;
	//m_matchNum = CPublic::g_imagePara[workNum][round][proNum].matchNum;
	//m_modelFilePath = CPublic::g_imagePara[workNum][round][proNum].modelFilePath;
	//m_smoothness = CPublic::g_imagePara[workNum][round][proNum].smoothness;
	//m_iterationNum = CPublic::g_imagePara[workNum][round][proNum].iterationNum;
	//m_modelDistance = CPublic::g_imagePara[workNum][round][proNum].modelDistance;
	//m_ROIx = CPublic::g_imagePara[workNum][round][proNum].ROI_x;
	//m_ROIy = CPublic::g_imagePara[workNum][round][proNum].ROI_y;
	//m_ROIw = CPublic::g_imagePara[workNum][round][proNum].ROI_w;
	//m_ROIh = CPublic::g_imagePara[workNum][round][proNum].ROI_h;
	//m_searchSpeedMode = CPublic::g_imagePara[workNum][round][proNum].searchSpeedMode;
	////m_cmbRound.SetCurSel(CPublic::g_imagePara[workNum][round].);


	//UpdateData(FALSE);
//}

//void CAutoDlg::OnEnChangeEditangleerror2()
//{
//	// TODO:  If this is a RICHEDIT control, the control will not
//	// send this notification unless you override the CDialog::OnInitDialog()
//	// function and call CRichEditCtrl().SetEventMask()
//	// with the ENM_CHANGE flag ORed into the mask.
//
//	// TODO:  Add your control notification handler code here
//}

void CAutoDlg::OnCbnSelchangeComboProcessnum()
{
	/*int round = m_cmbRound.GetCurSel();
	int proNum = m_cmbProcessNum.GetCurSel();
	int workNum = m_workNum;

	m_maxMatchNum = CPublic::g_imagePara[workNum][round][proNum].maxMatchNum;
	m_matchNum = CPublic::g_imagePara[workNum][round][proNum].matchNum;
	m_modelFilePath = CPublic::g_imagePara[workNum][round][proNum].modelFilePath;
	m_smoothness = CPublic::g_imagePara[workNum][round][proNum].smoothness;
	m_iterationNum = CPublic::g_imagePara[workNum][round][proNum].iterationNum;
	m_modelDistance = CPublic::g_imagePara[workNum][round][proNum].modelDistance;
	m_ROIx = CPublic::g_imagePara[workNum][round][proNum].ROI_x;
	m_ROIy = CPublic::g_imagePara[workNum][round][proNum].ROI_y;
	m_ROIw = CPublic::g_imagePara[workNum][round][proNum].ROI_w;
	m_ROIh = CPublic::g_imagePara[workNum][round][proNum].ROI_h;
	m_searchSpeedMode = CPublic::g_imagePara[workNum][round][proNum].searchSpeedMode;*/
	//m_cmbRound.SetCurSel(CPublic::g_imagePara[workNum][round].);


	UpdateData(FALSE);
}

//void CAutoDlg::OnEnChangeEditmicroadjust12()
//{
//	// TODO:  If this is a RICHEDIT control, the control will not
//	// send this notification unless you override the CDialog::OnInitDialog()
//	// function and call CRichEditCtrl().SetEventMask()
//	// with the ENM_CHANGE flag ORed into the mask.
//
//	// TODO:  Add your control notification handler code here
//}

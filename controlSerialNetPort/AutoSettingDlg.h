#pragma once
#include "BtnST.h"
#include "afxcmn.h"
#include "AutoInitDlg.h"
#include "afxwin.h"
#include "AutoDlg.h"

// CAutoSettingDlg dialog

class CAutoSettingDlg : public CDialog
{
	DECLARE_DYNAMIC(CAutoSettingDlg)

public:
	CAutoSettingDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CAutoSettingDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG_SETTING };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDestroy();
	afx_msg void OnClose();

	CButtonST m_bstsave;
	CButtonST m_bstdefault;
	virtual BOOL OnInitDialog();
	CTabCtrl m_ctrlTab;
	int m_stepsError;
	double m_sensorError;

	CAutoInitDlg m_pageAutoInitDlg;
	//CAutoDlg m_pageAutoDlg;
//	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnBnClickedButtonautosave();
	CComboBox m_ctrlWorkNum;
	afx_msg void OnBnClickedButtonautodefault();
//	afx_msg void OnTcnSelchangeTabAuto(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCbnSelchangeComboWorknum();
	afx_msg void OnDeltaposSpinsensorerror(NMHDR *pNMHDR, LRESULT *pResult);


	void SpinChange(NM_UPDOWN* pNMUpDown, CWnd* pWnd, double fstep = 1, int iFormat = 1); 
	void OnDeltaposSpinAll(NMHDR *pNMHDR, LRESULT *pResult, bool littleNum);


};

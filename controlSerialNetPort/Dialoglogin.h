#pragma once
#include "afxwin.h"
#include "afxext.h"

// CDialoglogin 对话框
//定义静态全局指针 


class CDialoglogin : public CDialog
{
	DECLARE_DYNAMIC(CDialoglogin)

public:
	CDialoglogin(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialoglogin();
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_Login };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	HICON m_hIcon;
	DECLARE_MESSAGE_MAP()
public:
	CString m_name;
	CString m_password;
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedCheck1();
	virtual BOOL OnInitDialog();
	afx_msg void OnStnClickedTime();
	afx_msg void OnEnChangeTime();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnStnClickedStatic3();
	afx_msg void OnStnClickedStatic4();
//	CButton m_bbtn;
//	CBitmapButton m_bbtn;
	CBitmapButton m_bbtn;
	afx_msg void OnStnClickedStatic6();
};

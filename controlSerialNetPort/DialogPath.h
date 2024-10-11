#pragma once
#include "afxwin.h"


// CDialogPath 对话框

class CDialogPath : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogPath)

public:
	CDialogPath(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialogPath();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_Path };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
//	CString m_editpath;
	afx_msg void OnBnClickedButton1();
//	CEdit m_editpath;
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
//	CString m_editpath;
	CEdit m_editpath;
	CString resultFileName;
	afx_msg void OnEnChangeEdit1();
	void SetAsFolderSelector();
	bool folderSelect = 0;
};

#pragma once
#include"DialogEditProcess.h"

// CDialogCreatProcess 对话框

class CDialogCreatProcess : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogCreatProcess)

public:
	CDialogCreatProcess(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialogCreatProcess();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_CreateProcess };
#endif
private:
	CDialogEditProcess* m_editprocess;//定义CTipDlg类型的指针变量.以前的指针大都是 int *pt1等  int为一种类型。这里CTipDlg为一种类，指向类的指针。
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_ProcessName;
	CString m_PersonName;
	CString m_ProcessRemarks;
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	virtual void PostNcDestroy();
	afx_msg void OnBnClickedCancel();
	virtual void OnOK();
};

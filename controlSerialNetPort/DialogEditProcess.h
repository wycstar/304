#pragma once


// CDialogEditProcess 对话框

class CDialogEditProcess : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogEditProcess)

public:
	CDialogEditProcess(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialogEditProcess();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_EditProcess };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_ProcessName2;
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	virtual void PostNcDestroy();
};

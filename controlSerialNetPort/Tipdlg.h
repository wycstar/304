#pragma once


// CTipdlg 对话框

class CTipdlg : public CDialogEx
{
	DECLARE_DYNAMIC(CTipdlg)

public:
	CTipdlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTipdlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_TIP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};

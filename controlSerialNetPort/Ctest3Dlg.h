#pragma once


// Ctest3Dlg 对话框

class Ctest3Dlg : public CDialogEx
{
	DECLARE_DYNAMIC(Ctest3Dlg)

public:
	Ctest3Dlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Ctest3Dlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TEST3_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};

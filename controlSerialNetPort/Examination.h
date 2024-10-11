#pragma once
#include "afxwin.h"


// CExamination 对话框

class CExamination : public CDialogEx
{
	DECLARE_DYNAMIC(CExamination)

public:
	CExamination(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CExamination();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_Examination };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListBox m_ListResult;
	int m_LogNum;//日志条数
	virtual BOOL OnInitDialog();
};

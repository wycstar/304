#pragma once
#include "afxwin.h"


// CExamination �Ի���

class CExamination : public CDialogEx
{
	DECLARE_DYNAMIC(CExamination)

public:
	CExamination(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CExamination();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_Examination };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CListBox m_ListResult;
	int m_LogNum;//��־����
	virtual BOOL OnInitDialog();
};

#pragma once


// CDialogEditProcess �Ի���

class CDialogEditProcess : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogEditProcess)

public:
	CDialogEditProcess(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDialogEditProcess();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_EditProcess };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_ProcessName2;
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	virtual void PostNcDestroy();
};

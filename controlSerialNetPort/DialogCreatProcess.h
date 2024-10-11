#pragma once
#include"DialogEditProcess.h"

// CDialogCreatProcess �Ի���

class CDialogCreatProcess : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogCreatProcess)

public:
	CDialogCreatProcess(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDialogCreatProcess();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_CreateProcess };
#endif
private:
	CDialogEditProcess* m_editprocess;//����CTipDlg���͵�ָ�����.��ǰ��ָ����� int *pt1��  intΪһ�����͡�����CTipDlgΪһ���ָ࣬�����ָ�롣
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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

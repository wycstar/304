#pragma once


// Ctest3Dlg �Ի���

class Ctest3Dlg : public CDialogEx
{
	DECLARE_DYNAMIC(Ctest3Dlg)

public:
	Ctest3Dlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Ctest3Dlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TEST3_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};

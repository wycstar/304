#pragma once


// CTipdlg �Ի���

class CTipdlg : public CDialogEx
{
	DECLARE_DYNAMIC(CTipdlg)

public:
	CTipdlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTipdlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_TIP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};

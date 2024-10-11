#pragma once


// CAutcon 对话框

class CAutcon : public CDialogEx
{
	DECLARE_DYNAMIC(CAutcon)

public:
	CAutcon(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CAutcon();
	/*double m_Han_edit1;
	double *m_Han_edit[5];

	int key1;
	int key2;
	int key3;
	int key4;
	int *key[13];

	CButton m_Hancon_check1;
	CButton m_Hancon_check2;
	CButton m_Hancon_check3;
	CButton m_Hancon_check4;
	CButton *m_Hancon_check[7];

	CButton m_Hancon_switch1;
	CButton m_Hancon_switch2;
	CButton m_Hancon_switch3;
	CButton m_Hancon_switch4;
	CButton *m_Hancon_switch[7];

	int switch1;
	int switch2;
	int switch3;
	int switch4;
	int *Switch[7];

	int  key_temp[7];
	int  test[7];*/

// 对话框数据
	enum { IDD = IDD_AUTCON };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};

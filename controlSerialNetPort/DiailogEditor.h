#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "DialogPath.h"
#include "Examination.h"
#define WM_MyMessage (WM_USER+100)

// CDiailogEditor �Ի���

class CDiailogEditor : public CDialogEx
{
	DECLARE_DYNAMIC(CDiailogEditor)

public:
	CDiailogEditor(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDiailogEditor();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_Editor };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	afx_msg LRESULT OnMyMessage(WPARAM wParam, LPARAM lParam); // add lyw
	DECLARE_MESSAGE_MAP()

	//afx_msg LRESULT Onadd_event_ok(WPARAM wParam, LPARAM lParam);
private:
	CDialogPath* m_path;
	CExamination* m_exam;
public:
	afx_msg void OnBnClickedButton1();
//	CListBox m_ListBox_Content;
	virtual BOOL OnInitDialog();
	CListCtrl m_ListCtrl;
	afx_msg void OnLvnItemchangedList4(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnPageup();//���ƺ���
	afx_msg void OnPagedown();//���ƺ���
	
	int e_Item;    //�ձ༭����  
	int e_SubItem; //�ձ༭����  
	CEdit m_Edit;  //���ɵ�Ԫ�༭�����
	bool haveeditcreate;//��־�༭���Ѿ�������
	void createEdit(NM_LISTVIEW  *pEditCtrl, CEdit *createdit, int &Item, int &SubItem, bool &havecreat);//������Ԫ��༭����
	void distroyEdit(CListCtrl *list, CEdit* distroyedit, int &Item, int &SubItem);//���ٵ�Ԫ��༭�����

	CComboBox m_comBox;//������Ԫ�������б����
	bool haveccomboboxcreate;//��־�����б���Ѿ�������
	void createCcombobox(NM_LISTVIEW  *pEditCtrl, CComboBox *createccomboboxobj, int &Item, int &SubItem, bool &havecreat);//������Ԫ�������б����
	void distroyCcombobox(CListCtrl *list, CComboBox* distroyccomboboxobj, int &Item, int &SubItem);//���ٵ�Ԫ�������б��

	void AddString(CString msg);
	virtual void OnOK();

	afx_msg void OnKillfocusEdit();//��̬���ɱ༭��ʧȥ������Ӧ����
	afx_msg void OnKillfocusCcomboBox();//��̬���������б��ʧȥ������Ӧ����
	

	afx_msg void OnBnClickedButton8();
//	CEdit m_EditTest;
	CEdit m_edit;
	CString m;
	
	int m_Row;//�к�
	int	m_Col;//�к�     ���ڱ���˫��ʱѡ�е��к��кţ�����ʼ��Ϊ-1��δѡ��״̬����

	afx_msg void OnEnChangeEdit6();
	afx_msg void OnEnKillfocusEdit6();
	afx_msg void OnNMDblclkList4(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickList4(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButton9();
	afx_msg void OnNMCustomdrawList4(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButton10();
	afx_msg void OnBnClickedButton11();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton4();
	afx_msg void SetListCell(NM_LISTVIEW *pNMListView);
	afx_msg void SaveListCell(CStdioFile & File);
	CString m_ProcessName;
	afx_msg void OnBnClickedButton12();

	void examCommon(CStdioFile&File, int i);
	void examInquiry(CStdioFile&File, int i);
	void examRobot(CStdioFile&File, int i);
	void examDelayTime(CStdioFile&File, int i);
	void examThreadInteraction(CStdioFile&File, int i);
	void examLightAdjusting(CStdioFile&File, int i);
	void examImageProcessing(CStdioFile&File, int i);
	void examAdjustingWithResult(CStdioFile&File, int i);
	void beginExamination(CStdioFile&File);
	void CommandExamination(CStdioFile&File);
	void examEmpty(int Min, int Max, CString comm[], CString a);
	CString m_fileComm;
	int m_commNum;
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnNMRClickList4(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedButton13();
};

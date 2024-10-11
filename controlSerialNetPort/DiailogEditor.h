#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "DialogPath.h"
#include "Examination.h"
#define WM_MyMessage (WM_USER+100)

// CDiailogEditor 对话框

class CDiailogEditor : public CDialogEx
{
	DECLARE_DYNAMIC(CDiailogEditor)

public:
	CDiailogEditor(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDiailogEditor();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_Editor };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
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
	afx_msg void OnPageup();//上移函数
	afx_msg void OnPagedown();//上移函数
	
	int e_Item;    //刚编辑的行  
	int e_SubItem; //刚编辑的列  
	CEdit m_Edit;  //生成单元编辑框对象
	bool haveeditcreate;//标志编辑框已经被创建
	void createEdit(NM_LISTVIEW  *pEditCtrl, CEdit *createdit, int &Item, int &SubItem, bool &havecreat);//创建单元格编辑框函数
	void distroyEdit(CListCtrl *list, CEdit* distroyedit, int &Item, int &SubItem);//销毁单元格编辑框对象

	CComboBox m_comBox;//生产单元格下拉列表对象
	bool haveccomboboxcreate;//标志下拉列表框已经被创建
	void createCcombobox(NM_LISTVIEW  *pEditCtrl, CComboBox *createccomboboxobj, int &Item, int &SubItem, bool &havecreat);//创建单元格下拉列表框函数
	void distroyCcombobox(CListCtrl *list, CComboBox* distroyccomboboxobj, int &Item, int &SubItem);//销毁单元格下拉列表框

	void AddString(CString msg);
	virtual void OnOK();

	afx_msg void OnKillfocusEdit();//动态生成编辑框失去焦点响应函数
	afx_msg void OnKillfocusCcomboBox();//动态生成下拉列表框失去焦点响应函数
	

	afx_msg void OnBnClickedButton8();
//	CEdit m_EditTest;
	CEdit m_edit;
	CString m;
	
	int m_Row;//行号
	int	m_Col;//列好     用于保存双击时选中的行和列号，并初始化为-1（未选中状态）；

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

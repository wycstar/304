 // DiailogEditor.cpp : 实现文件
//

#include "stdafx.h"
#include "controlSerialNetPort.h"
#include "DiailogEditor.h"
#include "afxdialogex.h"
#include "DialogPath.h"
#include <locale.h>
#include "Examination.h"
#include "controlSerialNetPortDlg.h"

// CDiailogEditor 对话框
//添加动态生成编辑框的失去焦点响应函数

extern CDialogPath* pEdit;
extern CcontrolSerialNetPortDlg*pMainDlg;
extern CExamination*pExam;
CDiailogEditor*pEditor;//定义全局变量

//ON_EN_KILLFOCUS(IDC_EDIT_CREATEID, &CDiailogEditor::OnKillfocusEdit)

//ON_CBN_KILLFOCUS(IDC_COMBOX_CREATEID, &CDiailogEditor::OnKillfocusCcomboBox)
IMPLEMENT_DYNAMIC(CDiailogEditor, CDialogEx)



void CDiailogEditor::OnKillfocusEdit()
{
	if (haveeditcreate == true)//如果之前创建了编辑框就销毁掉
	{
		distroyEdit(&m_ListCtrl, &m_Edit, e_Item, e_SubItem);//销毁单元格编辑框对象
		haveeditcreate = false;
	}
	if (haveccomboboxcreate == true)//如果之前创建了下拉列表框就销毁掉
	{
		distroyCcombobox(&m_ListCtrl, &m_comBox, e_Item, e_SubItem);
		haveccomboboxcreate = false;
	}
}

void CDiailogEditor::OnKillfocusCcomboBox()
{
	if (haveeditcreate == true)//如果之前创建了编辑框就销毁掉
	{
		distroyEdit(&m_ListCtrl, &m_Edit, e_Item, e_SubItem);//销毁单元格编辑框对象
		haveeditcreate = false;
	}
	if (haveccomboboxcreate == true)//如果之前创建了下拉列表框就销毁掉
	{
		distroyCcombobox(&m_ListCtrl, &m_comBox, e_Item, e_SubItem);
		haveccomboboxcreate = false;
	}
}


CDiailogEditor::CDiailogEditor(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_Editor, pParent)
	, m_ProcessName(_T(""))
{
	m_exam = NULL;
	m_path = NULL;
}

CDiailogEditor::~CDiailogEditor()
{
}

void CDiailogEditor::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Control(pDX, IDC_LIST1, m_ListBox_Content);
	DDX_Control(pDX, IDC_LIST4, m_ListCtrl);
	//  DDX_Control(pDX, IDC_EDIT6, m_EditTest);
	DDX_Control(pDX, IDC_EDIT6, m_edit);
	DDX_Text(pDX, IDC_EDIT5, m_ProcessName);
}


BEGIN_MESSAGE_MAP(CDiailogEditor, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CDiailogEditor::OnBnClickedButton1)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST4, &CDiailogEditor::OnLvnItemchangedList4)
	ON_BN_CLICKED(IDC_BUTTON8, &CDiailogEditor::OnBnClickedButton8)
	ON_EN_CHANGE(IDC_EDIT6, &CDiailogEditor::OnEnChangeEdit6)
	ON_EN_KILLFOCUS(IDC_EDIT6, &CDiailogEditor::OnEnKillfocusEdit6)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST4, &CDiailogEditor::OnNMDblclkList4)
	ON_NOTIFY(NM_CLICK, IDC_LIST4, &CDiailogEditor::OnNMClickList4)
	ON_BN_CLICKED(IDC_BUTTON9, &CDiailogEditor::OnBnClickedButton9)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_LIST4, &CDiailogEditor::OnNMCustomdrawList4)
	ON_BN_CLICKED(IDC_BUTTON10, &CDiailogEditor::OnBnClickedButton10)
	ON_BN_CLICKED(IDC_BUTTON11, &CDiailogEditor::OnBnClickedButton11)
	ON_BN_CLICKED(IDC_BUTTON3, &CDiailogEditor::OnBnClickedButton3)
	ON_WM_ACTIVATE()
	ON_MESSAGE(WM_MyMessage, OnMyMessage)

	ON_BN_CLICKED(IDC_BUTTON2, &CDiailogEditor::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON4, &CDiailogEditor::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON12, &CDiailogEditor::OnBnClickedButton12)
	ON_BN_CLICKED(IDC_BUTTON7, &CDiailogEditor::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON6, &CDiailogEditor::OnBnClickedButton6)
	ON_NOTIFY(NM_RCLICK, IDC_LIST4, &CDiailogEditor::OnNMRClickList4)
	ON_WM_MOUSEWHEEL()
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_BUTTON13, &CDiailogEditor::OnBnClickedButton13)
END_MESSAGE_MAP()


// CDiailogEditor 消息处理程序


void CDiailogEditor::OnBnClickedButton1()//打开导入txt
{
	// TODO: 在此添加控件通知处理程序代码
	//判断目前是否有编辑、提醒保存
	if (MessageBox(_T("导入新内容，当前内容将会清空！是否继续？"), _T("提示 "), MB_YESNO) == IDYES)
	{
		//ShellExecute(NULL,NULL,SW_SHOWNORMAL);
		//获取exe文件的路径
		if (haveeditcreate == true)//如果之前创建了编辑框就销毁掉
		{
			distroyEdit(&m_ListCtrl, &m_Edit, e_Item, e_SubItem);//销毁单元格编辑框对象
			haveeditcreate = false;
		}
		if (haveccomboboxcreate == true)//如果之前创建了下拉列表框就销毁掉
		{
			distroyCcombobox(&m_ListCtrl, &m_comBox, e_Item, e_SubItem);
			haveccomboboxcreate = false;
		}
		m_ListCtrl.DeleteAllItems(); // 全部清空  
		CString path;
		GetModuleFileName(NULL, path.GetBufferSetLength(MAX_PATH + 1), MAX_PATH);
		path.ReleaseBuffer();
		int pos = path.ReverseFind('\\');
		path = path.Left(pos);
		path = path + _T("\\");
	
		CString   strFileName;
		CFileDialog   m_ldFile(TRUE);

		m_ldFile.m_ofn.lpstrFilter = _T("*.txt "); //要选择的文件后缀
		m_ldFile.m_ofn.lpstrInitialDir = path;//默认的文件路径
		m_ldFile.m_ofn.lpstrDefExt = _T("txt");//默认扩展名

		if (m_ldFile.DoModal() == IDOK)
		{
			strFileName = m_ldFile.GetPathName();       //包括了路径和文件名 
		}
		//选择文件，并打开	
		LPCTSTR pszFileName = strFileName.GetBufferSetLength(strFileName.GetLength());
		CStdioFile myFile;
		BOOL ret = myFile.Open(pszFileName, CFile::modeRead);
		CString FullName = myFile.GetFileTitle();
		int index = 0;
		index = FullName.Find('.');//在指令的第三行字符中查找是否包含字符：value,从0位置开始查，返回的是位置
		m_ProcessName = FullName.Left(index);

		//SetDlgItemText(IDC_EDIT5, myFile.GetFileTitle());//将文件名称写在页面上
		UpdateData(FALSE);
		if (!ret)
		{
			AfxMessageBox(_T("打开文件失败"));
			return;
		}
		if (ret)//文件打开成功
		{
			CString content;//定义一个变量用于接收读取的一行内容
			int line = 0;//文本的行数txt
			int nItem;//行数list
			int iSubItem;//列数
			char* old_locale = _strdup(setlocale(LC_CTYPE, NULL));
			setlocale(LC_CTYPE, "chs");
			while (myFile.ReadString(content) != FALSE)//一行行读
			{
				iSubItem = line % 13;//取余数
				nItem = line / 13;//取商
				if (iSubItem == 0)//序号是v                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              
				{
					m_ListCtrl.InsertItem(nItem, _T(""));//InsertItem是向控件声请一行来放数据,记住只是声请,那么放置数据的工作就由SetItemText来实现
					m_ListCtrl.SetItemText(nItem, iSubItem, content);//第一列
					UpdateData(FALSE);
					line++;
				}
				if (iSubItem == 2|| iSubItem == 3||iSubItem == 4 || iSubItem == 5|| iSubItem == 6 || iSubItem == 7||iSubItem == 8 || iSubItem == 9 || iSubItem == 10 || iSubItem == 11 || iSubItem == 12)
				{
					m_ListCtrl.SetItemText(nItem, iSubItem, content);
					UpdateData(FALSE);
					line++;
				}
				if (iSubItem == 1)//备注列
				{
					m_ListCtrl.SetItemText(nItem, iSubItem, content);
					UpdateData(FALSE);
					line++;			
				}
			}
			line = line + 1;
			nItem = nItem + 1;

			setlocale(LC_CTYPE, old_locale);
			free(old_locale);

			CString temp;
			temp.Format(_T("%d"), nItem);//整形转换成字符

			CString str = _T("已读取数据行数：") + temp;

			MessageBox(str, _T("提示 "), MB_YESNO);    //读取晚报告并返回

			//myFile.GetFileName()   //得到完整的文件名，包括扩展名如：test1.txt
			//GetFileTitle()//获得文件名称，不含后缀
			
			myFile.Close();
		}
	}
}


BOOL CDiailogEditor::OnInitDialog()
{
	
	CDialogEx::OnInitDialog();
	pEditor = this;

	m_edit.ShowWindow(SW_HIDE);
	CRect rect;
	m_ListCtrl.GetClientRect(&rect); //获取list的客户区,方便调节每一列的宽度
	int iLength = rect.Width();
	m_ListCtrl.SetExtendedStyle(m_ListCtrl.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_ListCtrl.InsertColumn(0, _T("编号"), LVCFMT_CENTER, 50);
	m_ListCtrl.InsertColumn(1, _T("备注"), LVCFMT_CENTER, 135);
	m_ListCtrl.InsertColumn(2, _T("命令名称"), LVCFMT_CENTER, 120);
	m_ListCtrl.InsertColumn(3, _T("参数1"), LVCFMT_CENTER, 120);
	m_ListCtrl.InsertColumn(4, _T("参数2"), LVCFMT_CENTER, 120);
	m_ListCtrl.InsertColumn(5, _T("参数3"), LVCFMT_CENTER, 120);
	m_ListCtrl.InsertColumn(6, _T("参数4"), LVCFMT_CENTER, 120);
	m_ListCtrl.InsertColumn(7, _T("参数5"), LVCFMT_CENTER, 120);
	m_ListCtrl.InsertColumn(8, _T("参数6"), LVCFMT_CENTER, 120);
	m_ListCtrl.InsertColumn(9, _T("参数7"), LVCFMT_CENTER, 120);
	m_ListCtrl.InsertColumn(10, _T("参数8"), LVCFMT_CENTER, 120);
	m_ListCtrl.InsertColumn(11, _T("参数9"), LVCFMT_CENTER, 120);
	
	//设置list高度
	CImageList m_image;
	m_image.Create(1, 24, ILC_COLOR32, 1, 0);
	m_ListCtrl.SetImageList(&m_image, LVSIL_SMALL);
	
	m_ProcessName = _T("");//设置默认文件名称
	UpdateData(FALSE);

	haveeditcreate = false;//初始化标志位，表示还没有创建编辑框
	haveccomboboxcreate = false;//初始化标志位，表示还没有创建下拉列表框

	//设置列表获得焦点？
	m_ListCtrl.SetFocus();
	//确保List Control最后一行可见  
	m_ListCtrl.EnsureVisible(m_ListCtrl.GetItemCount(), FALSE);

	//每一行前面加上复选框
	DWORD dwStyle = m_ListCtrl.GetExtendedStyle();
	dwStyle |= LVS_EX_CHECKBOXES;//设置扩展样式
	m_ListCtrl.SetExtendedStyle(dwStyle);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CDiailogEditor::OnLvnItemchangedList4(NMHDR *pNMHDR, LRESULT *pResult)//为ListCtrl控件添加LVN_ITEMCHANGED消息
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}


//创建单元格编辑框函数 
//pEditCtrl为列表对象指针，createdit为编辑框指针对象，      
//Item为创建单元格在列表中的行，SubItem则为列，havecreat为对象创建标准

void CDiailogEditor::createEdit(NM_LISTVIEW  *pEditCtrl, CEdit *createdit, int &Item, int &SubItem, bool &havecreat)
{
	Item = pEditCtrl->iItem;//将点中的单元格的行赋值给“刚编辑过的行”以便后期处理
	SubItem = pEditCtrl->iSubItem;//将点中的单元格的行赋值给“刚编辑过的行”以便后期处理
	createdit->Create(ES_AUTOHSCROLL | WS_CHILD | ES_LEFT | ES_WANTRETURN,
		CRect(0, 0, 0, 0), this, IDC_EDIT_CREATEID);//创建编辑框对象,IDC_EDIT_CREATEID为控件ID号3000，在文章开头定义
	havecreat = true;
	createdit->SetFont(this->GetFont(), FALSE);//设置字体,不设置这里的话上面的字会很突兀的感觉
	createdit->SetParent(&m_ListCtrl);//将list control设置为父窗口,生成的Edit才能正确定位,这个也很重要
	CRect  EditRect;
	m_ListCtrl.GetSubItemRect(e_Item, e_SubItem, LVIR_LABEL, EditRect);//获取单元格的空间位置信息
	EditRect.SetRect(EditRect.left + 1, EditRect.top + 1, EditRect.left + m_ListCtrl.GetColumnWidth(e_SubItem) - 1, EditRect.bottom - 1);//+1和-1可以让编辑框不至于挡住列表框中的网格线
	CString strItem = m_ListCtrl.GetItemText(e_Item, e_SubItem);//获得相应单元格字符
	createdit->SetWindowText(strItem);//将单元格字符显示在编辑框上
	createdit->MoveWindow(&EditRect);//将编辑框位置放在相应单元格上
	createdit->ShowWindow(SW_SHOW);//显示编辑框在单元格上面
	createdit->SetFocus();//设置为焦点 
	createdit->SetSel(-1);//设置光标在文本框文字的最后
}

void CDiailogEditor::distroyEdit(CListCtrl *list, CEdit* distroyedit, int &Item, int &SubItem)
{
	CString meditdata;
	distroyedit->GetWindowTextW(meditdata);
	list->SetItemText(Item, SubItem, meditdata);//获得相应单元格字符
	distroyedit->DestroyWindow();//销毁对象，有创建就要有销毁，不然会报错
}

//创建单元格下拉列表框函数
//pEditCtrl为列表对象指针，createccombobox为下拉列表框指针对象，
//Item为创建单元格在列表中的行，SubItem则为列，havecreat为对象创建标准

void CDiailogEditor::createCcombobox(NM_LISTVIEW  *pEditCtrl, CComboBox *createccomboboxobj, int &Item, int &SubItem, bool &havecreat)
{
	Item = pEditCtrl->iItem;//将点中的单元格的行赋值给“刚编辑过的行”以便后期处理
	SubItem = pEditCtrl->iSubItem;//将点中的单元格的行赋值给“刚编辑过的行”以便后期处理
	havecreat = true;
	createccomboboxobj->Create(WS_CHILD | WS_VISIBLE | CBS_DROPDOWN | CBS_OEMCONVERT, CRect(0, 0, 0, 0), this, IDC_COMBOX_CREATEID);
	createccomboboxobj->SetFont(this->GetFont(), FALSE);//设置字体,不设置这里的话上面的字会很突兀的感觉
	createccomboboxobj->SetParent(&m_ListCtrl);//将list control设置为父窗口,生成的Ccombobox才能正确定位,这个也很重要
	CRect  EditRect;
	m_ListCtrl.GetSubItemRect(e_Item, e_SubItem, LVIR_LABEL, EditRect);//获取单元格的空间位置信息
	EditRect.SetRect(EditRect.left + 1, EditRect.top + 1, EditRect.left + m_ListCtrl.GetColumnWidth(e_SubItem) - 1, EditRect.bottom - 1);//+1和-1可以让编辑框不至于挡住列表框中的网格线
	CString strItem = m_ListCtrl.GetItemText(e_Item, e_SubItem);//获得相应单元格字符
	createccomboboxobj->SetWindowText(strItem);//将单元格字符显示在编辑框上
	createccomboboxobj->MoveWindow(&EditRect);//将编辑框位置放在相应单元格上
	createccomboboxobj->ShowWindow(SW_SHOW);//显示编辑框在单元格上面
}

void CDiailogEditor::distroyCcombobox(CListCtrl *list, CComboBox* distroyccomboboxobj, int &Item, int &SubItem)
{
	CString meditdata;
	distroyccomboboxobj->GetWindowTextW(meditdata);
	list->SetItemText(Item, SubItem, meditdata);//更新相应单元格字符
	distroyccomboboxobj->DestroyWindow();//销毁对象，有创建就要有销毁，不然会报错
}

void CDiailogEditor::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类
	//CDialogEx::OnOK();
}


void CDiailogEditor::OnEnChangeEdit6()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
	// TODO:  在此添加控件通知处理程序代码
}


void CDiailogEditor::OnEnKillfocusEdit6()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str;
	m_edit.GetWindowTextW(str);
	m_ListCtrl.SetItemText(m_Row, m_Col, str);
	m_edit.ShowWindow(SW_HIDE);
}


void CDiailogEditor::OnNMDblclkList4(NMHDR *pNMHDR, LRESULT *pResult)//双击响应
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}

void CDiailogEditor::OnNMRClickList4(NMHDR *pNMHDR, LRESULT *pResult)//右击鼠标响应事件
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	
	CRect rc;
	CString strTemp;
	NM_LISTVIEW *pNMListView = (NM_LISTVIEW *)pNMHDR;////NM_LISTVIEW结构．该结构用于存储列表视图的通知消息的有关信息，大部分列表视图的通知消息都会附带指向该结构的指针．
	m_Row = pNMListView->iItem; //行序号
	m_Col = pNMListView->iSubItem;//列序号
	int i = m_ListCtrl.GetSelectionMark();//获得选中行的行标
	CString s2 = m_ListCtrl.GetItemText(i, 2); //i是行，j是列。m_list是个list control 对象
	CString s3 = m_ListCtrl.GetItemText(i, 3); //i是行，j是列。m_list是个list control 对象
	CString s4 = m_ListCtrl.GetItemText(i, 4); //i是行，j是列。m_list是个list control 对象
	CString s5 = m_ListCtrl.GetItemText(i, 5); //i是行，j是列。m_list是个list control 对象
	CString s6 = m_ListCtrl.GetItemText(i, 6); //i是行，j是列。m_list是个list control 对象
	CString s7 = m_ListCtrl.GetItemText(i, 7); //i是行，j是列。m_list是个list control 对象
	CString s8 = m_ListCtrl.GetItemText(i, 8); //i是行，j是列。m_list是个list control 对象
	CString s9 = m_ListCtrl.GetItemText(i, 9); //i是行，j是列。m_list是个list control 对象
											   //CString s10 = m_ListCtrl.GetItemText(i, 10); //i是行，j是列。m_list是个list control 对象


	if (pNMListView->iItem == -1)//点击到非工作区（未新建的区域）
	{
		if (haveeditcreate == true)//如果之前创建了编辑框就销毁掉
		{
			distroyEdit(&m_ListCtrl, &m_Edit, e_Item, e_SubItem);//销毁单元格编辑框对象
			haveeditcreate = false;
		}
		if (haveccomboboxcreate == true)//如果之前创建了下拉列表框就销毁掉
		{
			distroyCcombobox(&m_ListCtrl, &m_comBox, e_Item, e_SubItem);
			haveccomboboxcreate = false;
		}//新建一行，序号加1
		m_Row = m_ListCtrl.GetItemCount();
		strTemp.Format(_T("%d"), m_Row + 1);
		m_ListCtrl.InsertItem(m_Row, strTemp);
		m_ListCtrl.SetItemState(m_Row, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);
		m_ListCtrl.EnsureVisible(m_Row, FALSE);
		//m_Col = 1;
	}
	if (pNMListView->iSubItem == 0)//如果是序号列
	{
		//不作为
	}
	if (pNMListView->iSubItem == 1)//如果是备注列
	{
		if (haveccomboboxcreate == true)//如果之前创建了下拉列表框就销毁掉
		{
			distroyCcombobox(&m_ListCtrl, &m_comBox, e_Item, e_SubItem);
			haveccomboboxcreate = false;
		}
		if (haveeditcreate == true)//如果之前创建了编辑框
		{
			if (!(e_Item == pNMListView->iItem && e_SubItem == pNMListView->iSubItem))//如果点中的单元格不是之前创建好的（编辑框在其它单元格
			{
				distroyEdit(&m_ListCtrl, &m_Edit, e_Item, e_SubItem);//销毁
				haveeditcreate = false;
				createEdit(pNMListView, &m_Edit, e_Item, e_SubItem, haveeditcreate);//在点击的位置创建新的编辑框
			}
			else//点中的单元格是之前创建好的
			{
				m_Edit.SetFocus();//设置为焦点（复活）
			}
		}
		else//目前什么框都没有创建
		{
			e_Item = pNMListView->iItem;//将点中的单元格的行赋值给“刚编辑过的行”以便后期处理
			e_SubItem = pNMListView->iSubItem;//将点中的单元格的列赋值给“刚编辑过的列”以便后期处理
			createEdit(pNMListView, &m_Edit, e_Item, e_SubItem, haveeditcreate);//在该位置创建编辑框
		}
	}
	if (pNMListView->iSubItem == 2 || pNMListView->iSubItem == 3 || pNMListView->iSubItem == 4 || pNMListView->iSubItem == 5 || pNMListView->iSubItem == 6 || pNMListView->iSubItem == 7 || pNMListView->iSubItem == 8 || pNMListView->iSubItem == 9 || pNMListView->iSubItem == 10 || pNMListView->iSubItem == 11)//如果是23456789选项，需要在该单元格生成列表框
	{
		if (haveeditcreate == true)//如果之前创建了编辑框就销毁掉
		{
			distroyEdit(&m_ListCtrl, &m_Edit, e_Item, e_SubItem);
			haveeditcreate = false;

		}
		if (haveccomboboxcreate == true)//如果之前创建了下拉列表(在其他单元格或是自己）
		{
			if (!(e_Item == pNMListView->iItem && e_SubItem == pNMListView->iSubItem))//如果点中的单元格不是之前创建好的（其他单元格有下拉列表框）
			{
				distroyCcombobox(&m_ListCtrl, &m_comBox, e_Item, e_SubItem);//销毁下拉列表框
				haveccomboboxcreate = false;
				UpdateData(TRUE); //更新listbox的内容
				createCcombobox(pNMListView, &m_comBox, e_Item, e_SubItem, haveccomboboxcreate);//在改单元格创建下拉列表框
				UpdateData(TRUE);
				int i = m_ListCtrl.GetSelectionMark();//获得选中行的行标
				CString s2 = m_ListCtrl.GetItemText(i, 2); //i是行，j是列。m_list是个list control 对象
				CString s3 = m_ListCtrl.GetItemText(i, 3); //i是行，j是列。m_list是个list control 对象
				CString s4 = m_ListCtrl.GetItemText(i, 4); //i是行，j是列。m_list是个list control 对象
				CString s5 = m_ListCtrl.GetItemText(i, 5); //i是行，j是列。m_list是个list control 对象
				CString s6 = m_ListCtrl.GetItemText(i, 6); //i是行，j是列。m_list是个list control 对象
				CString s7 = m_ListCtrl.GetItemText(i, 7); //i是行，j是列。m_list是个list control 对象
				CString s8 = m_ListCtrl.GetItemText(i, 8); //i是行，j是列。m_list是个list control 对象
				CString s9 = m_ListCtrl.GetItemText(i, 9); //i是行，j是列。m_list是个list control 对象
														   //CString s10 = m_ListCtrl.GetItemText(i, 10); //i是行，j是列。m_list是个list control 对象
				SetListCell(pNMListView);
			}
			else//点中的单元格是之前创建好的
			{
				m_comBox.SetFocus();//设置为焦点
			}
		}
		else//没有创建任何编辑框/下拉列表的情况下
		{
			e_Item = pNMListView->iItem;//将点中的单元格的行赋值给“刚编辑过的行”以便后期处理
			e_SubItem = pNMListView->iSubItem;//将点中的单元格的行赋值给“刚编辑过的行”以便后期处理
			createCcombobox(pNMListView, &m_comBox, e_Item, e_SubItem, haveccomboboxcreate);//创建编辑框
			SetListCell(pNMListView);
		}
	}
	*pResult = 0;
}

void CDiailogEditor::OnNMClickList4(NMHDR *pNMHDR, LRESULT *pResult)//单击响应函数
{
	UpdateData(TRUE);
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	CRect rc;
	CString strTemp;
	NM_LISTVIEW *pNMListView = (NM_LISTVIEW *)pNMHDR;////NM_LISTVIEW结构．该结构用于存储列表视图的通知消息的有关信息，大部分列表视图的通知消息都会附带指向该结构的指针．
	m_Row = pNMListView->iItem; //行序号
	m_Col = pNMListView->iSubItem;//列序号
	int i = m_ListCtrl.GetSelectionMark();//获得选中行的行标
	CString s2 = m_ListCtrl.GetItemText(i, 2); //i是行，j是列。m_list是个list control 对象
	CString s3 = m_ListCtrl.GetItemText(i, 3); //i是行，j是列。m_list是个list control 对象
	CString s4 = m_ListCtrl.GetItemText(i, 4); //i是行，j是列。m_list是个list control 对象
	CString s5 = m_ListCtrl.GetItemText(i, 5); //i是行，j是列。m_list是个list control 对象
	CString s6 = m_ListCtrl.GetItemText(i, 6); //i是行，j是列。m_list是个list control 对象
	CString s7 = m_ListCtrl.GetItemText(i, 7); //i是行，j是列。m_list是个list control 对象
	CString s8 = m_ListCtrl.GetItemText(i, 8); //i是行，j是列。m_list是个list control 对象
	CString s9 = m_ListCtrl.GetItemText(i, 9); //i是行，j是列。m_list是个list control 对象
	CString s10 = m_ListCtrl.GetItemText(i, 10); //i是行，j是列。m_list是个list control 对象


	if (pNMListView->iItem == -1 || pNMListView->iSubItem == 0)//点击到非工作区（未新建的区域）
	{
		//不作为
	}
	if (pNMListView->iSubItem == 1 || pNMListView->iSubItem == 2 || pNMListView->iSubItem == 3 || pNMListView->iSubItem == 4 || pNMListView->iSubItem == 5 || pNMListView->iSubItem == 6 || pNMListView->iSubItem == 7 || pNMListView->iSubItem == 8 || pNMListView->iSubItem == 9 || pNMListView->iSubItem == 10 || pNMListView->iSubItem == 11)//如果是23456789选项，需要在该单元格生成列表框)//如果是备注列
	{
		if (haveccomboboxcreate == true)//如果之前创建了下拉列表框就销毁掉
		{
			distroyCcombobox(&m_ListCtrl, &m_comBox, e_Item, e_SubItem);
			haveccomboboxcreate = false;
		}
		if (haveeditcreate == true)//如果之前创建了编辑框
		{
			if (!(e_Item == pNMListView->iItem && e_SubItem == pNMListView->iSubItem))//如果点中的单元格不是之前创建好的（编辑框在其它单元格
			{
				distroyEdit(&m_ListCtrl, &m_Edit, e_Item, e_SubItem);//销毁
				haveeditcreate = false;
				//createEdit(pNMListView, &m_Edit, e_Item, e_SubItem, haveeditcreate);//在点击的位置创建新的编辑框
				m_Edit.SetFocus();//设置为焦点（复活）
			}
			else//点中的单元格是之前创建好的
			{
				m_Edit.SetFocus();//设置为焦点（复活）
			}
		}
		else//目前什么框都没有创建
		{
			e_Item = pNMListView->iItem;//将点中的单元格的行赋值给“刚编辑过的行”以便后期处理
			e_SubItem = pNMListView->iSubItem;//将点中的单元格的列赋值给“刚编辑过的列”以便后期处理
			createEdit(pNMListView, &m_Edit, e_Item, e_SubItem, haveeditcreate);//在该位置创建编辑框
		}
	}

	UpdateData(FALSE);
	*pResult = 0;
}

void CDiailogEditor::SetListCell(NM_LISTVIEW* pNMListView)//设置单元格内容
{
	UpdateData(TRUE);
	m_Row = pNMListView->iItem; //行序号
	m_Col = pNMListView->iSubItem;//列序号
	int i = m_ListCtrl.GetSelectionMark();//获得选中行的行标
	CString s2 = m_ListCtrl.GetItemText(i, 2); //i是行，j是列。m_list是个list control 对象
	CString s3 = m_ListCtrl.GetItemText(i, 3); //i是行，j是列。m_list是个list control 对象
	CString s4 = m_ListCtrl.GetItemText(i, 4); //i是行，j是列。m_list是个list control 对象
	CString s5 = m_ListCtrl.GetItemText(i, 5); //i是行，j是列。m_list是个list control 对象
	CString s6 = m_ListCtrl.GetItemText(i, 6); //i是行，j是列。m_list是个list control 对象
	CString s7 = m_ListCtrl.GetItemText(i, 7); //i是行，j是列。m_list是个list control 对象
	CString s8 = m_ListCtrl.GetItemText(i, 8); //i是行，j是列。m_list是个list control 对象
	CString s9 = m_ListCtrl.GetItemText(i, 9); //i是行，j是列。m_list是个list control 对象
	//CString s10 = m_ListCtrl.GetItemText(i, 10); //i是行，j是列。m_list是个list control 对象
	if (pNMListView->iSubItem == 2)//-----------------------------7种指令
	{
		m_comBox.InsertString(0, _T("Common:"));
		m_comBox.InsertString(1, _T("Robot:"));
		m_comBox.InsertString(2, _T("DelayTime:"));
		m_comBox.InsertString(3, _T("Inquiry:"));
		m_comBox.InsertString(4, _T("LightAdjusting:"));
		m_comBox.InsertString(5, _T("ImageProcessing:"));
		m_comBox.InsertString(6, _T("AdjustingWithResult:"));
		m_comBox.InsertString(7, _T("ThreadInteraction:"));
		m_comBox.InsertString(8, _T("Unit:"));
		m_comBox.InsertString(9, _T("ControlDev:"));
		m_comBox.InsertString(10, _T("OmissionDetection:"));
		m_comBox.SetCurSel(0);//默认显示第一项

	}
	if (pNMListView->iSubItem == 3)
	{
		UpdateData(TRUE);
		if (s2 == "Common:")//--------------------------------8种子指令
		{
			m_comBox.InsertString(0, L"IO");
			m_comBox.InsertString(1, L"AxisMove");
			m_comBox.InsertString(2, L"ForceControlAxisMove");//力控轴动
			m_comBox.InsertString(3, L"AxisSetTargetSpeed");//设置目标速度
			m_comBox.InsertString(4, L"AxisSetHomePosition");//设置原点
			m_comBox.InsertString(5, L"AxisGoHomePosition");//回原点
			m_comBox.InsertString(6, L"AxisGoPositiveLimit");//回负限位
			m_comBox.InsertString(7, L"AxisGoNegativeLimit");//回正限位
			m_comBox.InsertString(8, L"AxisSMVR");//储存设定
			m_comBox.InsertString(9, L"ChangeMode");//切换模式、绝对相对
			m_comBox.SetCurSel(0);//默认显示第一项
		}
		if (s2 == "Robot:")//----------------------------------2种子指令
		{
			m_comBox.InsertString(0, L"MoveRobot");
			m_comBox.InsertString(1, L"InquiryRobot");
			m_comBox.SetCurSel(0);
		}
		if (s2 == "DelayTime:")
		{
			m_comBox.InsertString(0, L"Time=50");
			m_comBox.InsertString(1, L"Time=100");
			m_comBox.InsertString(2, L"Time=300");
			m_comBox.InsertString(3, L"Time=500");
			m_comBox.InsertString(4, L"Time=1000");
			m_comBox.InsertString(5, L"Time=1500");
			m_comBox.InsertString(6, L"Time=2000");
			m_comBox.InsertString(7, L"Time=5000");
			m_comBox.SetCurSel(4);
		}
		if (s2 == "Inquiry:")//------------------------------4种子指令
		{
			m_comBox.InsertString(0, L"Limit?");//限位查询
			m_comBox.InsertString(1, L"RelativePosition?");//相对位置查询
			m_comBox.InsertString(2, L"AbsolutePosition?");//绝对位置查询
			m_comBox.InsertString(3, L"IO?");//查询IO状态
			m_comBox.SetCurSel(0);
		}

		if (s2 == "LightAdjusting:")
		{
			m_comBox.InsertString(0, L"Channel=1");
			m_comBox.InsertString(1, L"Channel=2");
			m_comBox.SetCurSel(0);
		}
		if (s2 == "ImageProcessing:")//--------------------2种子指令
		{
			m_comBox.InsertString(0, L"TemplateMatching");
			m_comBox.InsertString(1, L"CricleDetection");
			m_comBox.SetCurSel(0);
		}

		if (s2 == "OmissionDetection:")//--------------------2种子指令
		{
			m_comBox.InsertString(0, L"Target_ABJG");
			m_comBox.InsertString(1, L"Target_WLG");
			m_comBox.SetCurSel(0);
		}

		if (s2 == "AdjustingWithResult:")
		{
			m_comBox.InsertString(0, L"TemplateMatching");
			m_comBox.InsertString(1, L"CricleDetection");
			m_comBox.SetCurSel(0);
		}
		if (s2 == "ThreadInteraction:")
		{
			m_comBox.InsertString(0, L"WaitUntil");
			m_comBox.InsertString(1, L"OrderContinue");
			m_comBox.SetCurSel(0);
		}
		if (s2 == "Unit:")
		{
			m_comBox.InsertString(0, L"UnitStart");
			m_comBox.InsertString(1, L"UnitEnd");
			m_comBox.SetCurSel(0);
		}

		if (s2 == "ControlDev:")
		{
			m_comBox.InsertString(0, L"IO_Control");
			m_comBox.InsertString(1, L"Axis_Control");
			m_comBox.SetCurSel(0);
		}
	}
	if (pNMListView->iSubItem == 4)
	{

		UpdateData(TRUE);
		int i = m_ListCtrl.GetSelectionMark();//获得选中行的行标
		CString s2 = m_ListCtrl.GetItemText(i, 2); //i是行，j是列。m_list是个list control 对象
		CString s3 = m_ListCtrl.GetItemText(i, 3); //i是行，j是列。m_list是个list control 对象
		CString s4 = m_ListCtrl.GetItemText(i, 4); //i是行，j是列。m_list是个list control 对象
		CString s5 = m_ListCtrl.GetItemText(i, 5); //i是行，j是列。m_list是个list control 对象
		CString s6 = m_ListCtrl.GetItemText(i, 6); //i是行，j是列。m_list是个list control 对象
		CString s7 = m_ListCtrl.GetItemText(i, 7); //i是行，j是列。m_list是个list control 对象
		CString s8 = m_ListCtrl.GetItemText(i, 8); //i是行，j是列。m_list是个list control 对象
		CString s9 = m_ListCtrl.GetItemText(i, 9); //i是行，j是列。m_list是个list control 对象
		//CString s10 = m_ListCtrl.GetItemText(i, 10); //i是行，j是列。m_list是个list control 对象
		if (s3 == "MoveRobot")
		{
			m_comBox.InsertString(0, L"MoveSpeed=10");
			m_comBox.InsertString(1, L"MoveSpeed=20");
			m_comBox.InsertString(2, L"MoveSpeed=50");
			m_comBox.InsertString(3, L"MoveSpeed=100");
			m_comBox.InsertString(4, L"MoveSpeed=500");
			m_comBox.InsertString(5, L"MoveSpeed=1000");
			m_comBox.SetCurSel(0);
		}

		if (s2 == "OmissionDetection:")
		{
			OutputDebugString(L"Show Edit text");
			if (haveccomboboxcreate == true)//如果之前创建了下拉列表框就销毁掉
			{
				distroyCcombobox(&m_ListCtrl, &m_comBox, e_Item, e_SubItem);
				haveccomboboxcreate = false;
			}
			if (haveeditcreate == true)//如果之前创建了编辑框
			{
				if (!(e_Item == pNMListView->iItem && e_SubItem == pNMListView->iSubItem))//如果点中的单元格不是之前创建好的（编辑框在其它单元格
				{
					distroyEdit(&m_ListCtrl, &m_Edit, e_Item, e_SubItem);//销毁
					haveeditcreate = false;
					createEdit(pNMListView, &m_Edit, e_Item, e_SubItem, haveeditcreate);//在点击的位置创建新的编辑框
				}
				else//点中的单元格是之前创建好的
				{
					m_Edit.SetFocus();//设置为焦点（复活）
				}
			}
			if (haveccomboboxcreate == false && haveeditcreate == false)//目前什么框都没有创建
			{
				e_Item = pNMListView->iItem;//将点中的单元格的行赋值给“刚编辑过的行”以便后期处理
				e_SubItem = pNMListView->iSubItem;//将点中的单元格的列赋值给“刚编辑过的列”以便后期处理
				createEdit(pNMListView, &m_Edit, e_Item, e_SubItem, haveeditcreate);//在该位置创建编辑框				
				if (NULL == m_path)  // 如果指针变量m_create的值为NULL，则对话框还未创建，需要动态创建   
				{
					m_path = new CDialogPath();   //动态创建对象
					m_path->SetAsFolderSelector();
					m_path->Create(IDD_DIALOG_Path, this);
				}
				m_path->ShowWindow(SW_SHOW);  // 显示非模态对话框   
				m_path->SetWindowPos(NULL, 900, 300, 0, 0, SWP_NOSIZE);
				//SWP_NOSIZE保持当前对话框大小（第4、5参数cx和cy会被忽略）设置非模态对话框的位置

			}
		}

		if (s3 == "InquiryRobot")//----------------------2种子命令
		{
			m_comBox.InsertString(0, L"RobotStatus?");
			m_comBox.InsertString(1, L"RobotAbsolutePosition?");
			m_comBox.SetCurSel(0);
		}

		if (s3 == "IO" || s3 == "IO?")
		{
			m_comBox.InsertString(0, L"IP=192.168.0.8");
			m_comBox.InsertString(1, L"IP=192.168.0.9");
			m_comBox.InsertString(2, L"IP=192.168.0.10");
			m_comBox.SetCurSel(0);
		}
		if (s3 == "ForceControlAxisMove" || s3 == "AxisMove" || s3 == "AxisSetTargetSpeed" || s3 == "AxisSetHomePosition" || s3 == "AxisGoHomePosition" || s3 == "AxisGoPositiveLimit" || s3 == "AxisGoNegativeLimit" || s3 == "AxisSMVR" || s3 == "Limit?" || s3 == "RelativePosition?" || s3 == "AbsolutePosition?" || s3 == "ChangeMode")
		{
			m_comBox.InsertString(0, L"IP=192.168.0.2");
			m_comBox.InsertString(1, L"IP=192.168.0.3");
			m_comBox.InsertString(2, L"IP=192.168.0.4");
			m_comBox.InsertString(3, L"IP=192.168.0.5");
			m_comBox.InsertString(4, L"IP=192.168.0.6");
			m_comBox.InsertString(5, L"IP=192.168.0.7");
			m_comBox.SetCurSel(0);
		}
		if (s2 == "LightAdjusting:")
		{
			m_comBox.InsertString(0, L"Intensity=0");
			m_comBox.InsertString(1, L"Intensity=255");
			m_comBox.SetCurSel(0);
		}
		if (s2 == "ImageProcessing:")
		{
			m_comBox.InsertString(0, L"Number=1");
			m_comBox.InsertString(1, L"Number=2");
			m_comBox.InsertString(2, L"Number=3");
			m_comBox.InsertString(3, L"Number=4");
			m_comBox.InsertString(4, L"Number=5");
			m_comBox.InsertString(5, L"Number=6");
			m_comBox.SetCurSel(0);
		}
		if (s2 == "AdjustingWithResult:")
		{
			m_comBox.InsertString(0, L"Algorithm=Angcalc");
			m_comBox.InsertString(1, L"Algorithm=Poscalc");
			m_comBox.SetCurSel(0);
		}
		if (s2 == "ThreadInteraction:")
		{
			m_comBox.InsertString(0, L"Sender=1");
			m_comBox.InsertString(1, L"Sender=2");
			m_comBox.InsertString(2, L"Sender=3");
			m_comBox.SetCurSel(0);
		}
		if (s2 == "Unit:")
		{
			m_comBox.InsertString(0, L"UnitName=Part1");
			m_comBox.InsertString(1, L"UnitName=Part2");
			m_comBox.InsertString(2, L"UnitName=Part3");
			m_comBox.InsertString(3, L"UnitName=Part4");
			m_comBox.InsertString(4, L"UnitName=Part5");
			m_comBox.InsertString(5, L"UnitName=Part6");
			m_comBox.InsertString(6, L"UnitName=Part7");
			m_comBox.InsertString(7, L"UnitName=Part8");
			m_comBox.InsertString(8, L"UnitName=Part9");
			m_comBox.InsertString(9, L"UnitName=Part10");
			m_comBox.SetCurSel(0);
		}
		if (s3 == "IO_Control")
		{
			m_comBox.InsertString(0, L"IP=192.168.0.8");
			m_comBox.InsertString(1, L"IP=192.168.0.9");
			m_comBox.InsertString(2, L"IP=192.168.0.10");
			m_comBox.SetCurSel(0);
		}
		if (s3 == "Axis_Control")
		{
			m_comBox.InsertString(0, L"IP=192.168.0.2");
			m_comBox.InsertString(1, L"IP=192.168.0.3");
			m_comBox.InsertString(2, L"IP=192.168.0.4");
			m_comBox.InsertString(3, L"IP=192.168.0.5");
			m_comBox.InsertString(4, L"IP=192.168.0.6");
			m_comBox.InsertString(5, L"IP=192.168.0.7");
			m_comBox.SetCurSel(0);
		}
	}
		if (pNMListView->iSubItem == 5)
		{
			UpdateData(TRUE);
			int i = m_ListCtrl.GetSelectionMark();//获得选中行的行标
			CString s2 = m_ListCtrl.GetItemText(i, 2); //i是行，j是列。m_list是个list control 对象
			CString s3 = m_ListCtrl.GetItemText(i, 3); //i是行，j是列。m_list是个list control 对象
			CString s4 = m_ListCtrl.GetItemText(i, 4); //i是行，j是列。m_list是个list control 对象
			CString s5 = m_ListCtrl.GetItemText(i, 5); //i是行，j是列。m_list是个list control 对象
			CString s6 = m_ListCtrl.GetItemText(i, 6); //i是行，j是列。m_list是个list control 对象
			CString s7 = m_ListCtrl.GetItemText(i, 7); //i是行，j是列。m_list是个list control 对象
			CString s8 = m_ListCtrl.GetItemText(i, 8); //i是行，j是列。m_list是个list control 对象
			CString s9 = m_ListCtrl.GetItemText(i, 9); //i是行，j是列。m_list是个list control 对象
			//CString s10 = m_ListCtrl.GetItemText(i, 10); //i是行，j是列。m_list是个list control 对象
			if (s3 == "MoveRobot")
			{
				m_comBox.InsertString(0, L"Coordinate=Cartesian");
				m_comBox.InsertString(1, L"Coordinate=Joint");
				m_comBox.SetCurSel(0);
			}
			if (s5 == "Coordinate=Joint")
			{
				m_comBox.InsertString(0, L"Axis1=-100");
				m_comBox.InsertString(1, L"Axis1=-60");
				m_comBox.InsertString(2, L"Axis1=-30");
				m_comBox.InsertString(3, L"Axis1=0");
				m_comBox.InsertString(4, L"Axis1=30");
				m_comBox.InsertString(5, L"Axis1=60");
				m_comBox.InsertString(5, L"Axis1=100");
				m_comBox.SetCurSel(3);
			}
			if (s4 == "RobotStatus?")
			{
				m_comBox.InsertString(0, L"Status=Busy");//繁忙
				m_comBox.InsertString(1, L"Status=Waiting");//等候
				m_comBox.SetCurSel(0);
			}
			if (s4 == "RobotAbsolutePosition?")
			{
				m_comBox.InsertString(0, L"Coordinate=Cartesian");
				m_comBox.InsertString(1, L"Coordinate=Joint");
				m_comBox.SetCurSel(0);
			}
			if (s2 == "AdjustingWithResult:" && s3 == "TemplateMatching")
			{
				m_comBox.InsertString(0, L"Result1=1");
				m_comBox.InsertString(1, L"Result1=2");
				m_comBox.InsertString(2, L"Result1=3");
				m_comBox.InsertString(3, L"Result1=4");
				m_comBox.InsertString(4, L"Result1=5");
				m_comBox.InsertString(5, L"Result1=6");
				m_comBox.SetCurSel(0);
			}
			if (s2 == "AdjustingWithResult:" && s3 == "CricleDetection")
			{
				m_comBox.InsertString(0, L"Result1=1");
				m_comBox.InsertString(1, L"Result1=2");
				m_comBox.InsertString(2, L"Result1=3");
				m_comBox.InsertString(3, L"Result1=4");
				m_comBox.InsertString(4, L"Result1=5");
				m_comBox.InsertString(5, L"Result1=6");
				m_comBox.InsertString(6, L"Result1=Preset1");
				m_comBox.InsertString(7, L"Result1=Preset2");
				m_comBox.InsertString(8, L"Result1=Preset3");
				m_comBox.InsertString(9, L"Result1=Preset4");
				m_comBox.InsertString(10, L"Result1=Preset5");
				m_comBox.InsertString(11, L"Result1=Preset6");
				m_comBox.SetCurSel(0);
			}
			if (s3 == "IO" || s3 == "IO?")
			{
				m_comBox.InsertString(0, L"Value=1");
				m_comBox.InsertString(1, L"Value=4");
				m_comBox.InsertString(2, L"Value=32");
				m_comBox.InsertString(3, L"Value=128");
				m_comBox.InsertString(4, L"Value=512");
				m_comBox.InsertString(5, L"Value=1024");
				m_comBox.InsertString(6, L"Value=4096");
				m_comBox.InsertString(7, L"Value=16384");
				m_comBox.InsertString(8, L"Value=32768");
				m_comBox.SetCurSel(0);
			}
			if (s3 == "IO_Control")
			{
				m_comBox.InsertString(0, L"Value=1");
				m_comBox.InsertString(1, L"Value=4");
				m_comBox.InsertString(2, L"Value=32");
				m_comBox.InsertString(3, L"Value=128");
				m_comBox.InsertString(4, L"Value=512");
				m_comBox.InsertString(5, L"Value=1024");
				m_comBox.InsertString(6, L"Value=4096");
				m_comBox.InsertString(7, L"Value=16384");
				m_comBox.InsertString(8, L"Value=32768");
				m_comBox.SetCurSel(0);
			}
			if (s2 == "Unit:")
			{
				m_comBox.InsertString(0, L"Sequence=1");
				m_comBox.InsertString(1, L"Sequence=2");
				m_comBox.InsertString(2, L"Sequence=3");
				m_comBox.InsertString(3, L"Sequence=4");
				m_comBox.InsertString(4, L"Sequence=5");
				m_comBox.InsertString(5, L"Sequence=6");
				m_comBox.InsertString(6, L"Sequence=7");
				m_comBox.InsertString(7, L"Sequence=8");
				m_comBox.InsertString(8, L"Sequence=9");
				m_comBox.InsertString(9, L"Sequence=10");
				m_comBox.SetCurSel(0);
			}
			if (s3 == "AxisMove" || s3 == "ForceControlAxisMove" || s3 == "AxisSetTargetSpeed" || s3 == "AxisSetHomePosition" || s3 == "AxisGoHomePosition" || s3 == "AxisGoPositiveLimit" || s3 == "AxisGoNegativeLimit" || s3 == "AxisSMVR" || s3 == "Limit?" || s3 == "RelativePosition?" || s3 == "AbsolutePosition?" || s3 == "ChangeMode")
			{
				m_comBox.InsertString(0, L"AxisNum=X");
				m_comBox.InsertString(1, L"AxisNum=Y");
				m_comBox.InsertString(2, L"AxisNum=Z");
				m_comBox.InsertString(3, L"AxisNum=A");
				m_comBox.InsertString(4, L"AxisNum=B");
				m_comBox.InsertString(5, L"AxisNum=C");
				m_comBox.SetCurSel(0);
			}
			if (s3 == "Limit?" || s3 == "RelativePosition?" || s3 == "AbsolutePosition?" || s3 == "ChangeMode")
			{
				m_comBox.InsertString(0, L"AxisNum=1");
				m_comBox.InsertString(1, L"AxisNum=2");
				m_comBox.InsertString(2, L"AxisNum=3");
				m_comBox.InsertString(3, L"AxisNum=4");
				m_comBox.InsertString(4, L"AxisNum=5");
				m_comBox.InsertString(5, L"AxisNum=6");
				m_comBox.SetCurSel(0);
			}
			if (s3 == "Axis_Control")
			{
				m_comBox.InsertString(0, L"Route=Absolute");
				m_comBox.InsertString(1, L"Route=Relative");
				m_comBox.SetCurSel(0);
			}
			if (s4 == "Intensity=0" || s4 == "Intensity=255")
			{
				m_comBox.InsertString(0, L"Port=1");
				m_comBox.InsertString(1, L"Port=2");
				m_comBox.SetCurSel(0);
			}
			if (s2 == "ImageProcessing:" && s3 == "CricleDetection")
			{
				m_comBox.InsertString(0, L"ROIX=1");
				m_comBox.InsertString(1, L"ROIX=10");
				m_comBox.InsertString(2, L"ROIX=100");
				m_comBox.InsertString(3, L"ROIX=1000");
				m_comBox.SetCurSel(0);
			}
			if (s2 == "ThreadInteraction:")
			{
				m_comBox.InsertString(0, L"Recipient=1");
				m_comBox.InsertString(1, L"Recipient=2");
				m_comBox.InsertString(2, L"Recipient=3");
				m_comBox.SetCurSel(0);
			}
			if (s2 == "ImageProcessing:" && s3 == "TemplateMatching")
			{//路径选择弹出一个非模态对话框，选取路径，填入该编辑框
				if (haveccomboboxcreate == true)//如果之前创建了下拉列表框就销毁掉
				{
					distroyCcombobox(&m_ListCtrl, &m_comBox, e_Item, e_SubItem);
					haveccomboboxcreate = false;
				}
				if (haveeditcreate == true)//如果之前创建了编辑框
				{
					if (!(e_Item == pNMListView->iItem && e_SubItem == pNMListView->iSubItem))//如果点中的单元格不是之前创建好的（编辑框在其它单元格
					{
						distroyEdit(&m_ListCtrl, &m_Edit, e_Item, e_SubItem);//销毁
						haveeditcreate = false;
						createEdit(pNMListView, &m_Edit, e_Item, e_SubItem, haveeditcreate);//在点击的位置创建新的编辑框
					}
					else//点中的单元格是之前创建好的
					{
						m_Edit.SetFocus();//设置为焦点（复活）
					}
				}
				if (haveccomboboxcreate == false && haveeditcreate == false)//目前什么框都没有创建
				{
					e_Item = pNMListView->iItem;//将点中的单元格的行赋值给“刚编辑过的行”以便后期处理
					e_SubItem = pNMListView->iSubItem;//将点中的单元格的列赋值给“刚编辑过的列”以便后期处理
					createEdit(pNMListView, &m_Edit, e_Item, e_SubItem, haveeditcreate);//在该位置创建编辑框				
					if (NULL == m_path)  // 如果指针变量m_create的值为NULL，则对话框还未创建，需要动态创建   
					{
						m_path = new CDialogPath();   //动态创建对象
						m_path->Create(IDD_DIALOG_Path, this);
					}
					m_path->ShowWindow(SW_SHOW);  // 显示非模态对话框   
					m_path->SetWindowPos(NULL, 900, 300, 0, 0, SWP_NOSIZE);
					//SWP_NOSIZE保持当前对话框大小（第4、5参数cx和cy会被忽略）设置非模态对话框的位置

				}

			}
		}
		if (pNMListView->iSubItem == 6)
		{
			UpdateData(TRUE);
			int i = m_ListCtrl.GetSelectionMark();//获得选中行的行标
			CString s2 = m_ListCtrl.GetItemText(i, 2); //i是行，j是列。m_list是个list control 对象
			CString s3 = m_ListCtrl.GetItemText(i, 3); //i是行，j是列。m_list是个list control 对象
			CString s4 = m_ListCtrl.GetItemText(i, 4); //i是行，j是列。m_list是个list control 对象
			CString s5 = m_ListCtrl.GetItemText(i, 5); //i是行，j是列。m_list是个list control 对象
			CString s6 = m_ListCtrl.GetItemText(i, 6); //i是行，j是列。m_list是个list control 对象
			CString s7 = m_ListCtrl.GetItemText(i, 7); //i是行，j是列。m_list是个list control 对象
			CString s8 = m_ListCtrl.GetItemText(i, 8); //i是行，j是列。m_list是个list control 对象
			CString s9 = m_ListCtrl.GetItemText(i, 9); //i是行，j是列。m_list是个list control 对象
		//	CString s10 = m_ListCtrl.GetItemText(i, 10); //i是行，j是列。m_list是个list control 对象

			if (s5 == "Coordinate=Joint")
			{
				m_comBox.InsertString(0, L"Axis1=-100");
				m_comBox.InsertString(1, L"Axis1=-60");
				m_comBox.InsertString(2, L"Axis1=-30");
				m_comBox.InsertString(3, L"Axis1=0");
				m_comBox.InsertString(4, L"Axis1=30");
				m_comBox.InsertString(5, L"Axis1=60");
				m_comBox.InsertString(5, L"Axis1=100");
				m_comBox.SetCurSel(3);
			}
			if (s5 == "Coordinate=Cartesian")
			{
				m_comBox.InsertString(0, L"Route=MoveJ");
				m_comBox.InsertString(1, L"Route=MoveL");
				m_comBox.SetCurSel(0);
			}

			/*if (s5 == "Coordinate = Joint")
			{
				m_comBox.InsertString(0, L"Route=MoveJ");
				m_comBox.InsertString(1, L"Route=MoveL");
				m_comBox.SetCurSel(0);
			}*/
			if (s4 == "RobotAbsolutePosition?" && s5 == "Coordinate=Cartesian")
			{
				m_comBox.InsertString(0, L"X=0");
				m_comBox.InsertString(1, L"X=50");
				m_comBox.InsertString(2, L"X=100");
				m_comBox.InsertString(3, L"X=500");
				m_comBox.InsertString(4, L"X=1000");
				m_comBox.InsertString(5, L"X=5000");
				m_comBox.SetCurSel(0);
			}
		/*	if (s3 == "IO" || s3 == "IO?")
			{
				m_comBox.InsertString(0, L"Value=1");
				m_comBox.InsertString(1, L"Value=2");
				m_comBox.InsertString(2, L"Value=4");
				m_comBox.InsertString(3, L"Value=8");
				m_comBox.InsertString(3, L"Value=16");
				m_comBox.SetCurSel(0);
			}*/
			if (s3 == "AxisMove" || s3 == "AxisSMVR" || s3 == "RelativePosition?" || s3 == "ForceControlAxisMove" || s3 == "AbsolutePosition?" || s3 == "ChangeMode")
			{
				m_comBox.InsertString(0, L"Value=1000");
				m_comBox.InsertString(1, L"Value=2000");
				m_comBox.InsertString(2, L"Value=3000");
				m_comBox.InsertString(3, L"Value=4000");
				m_comBox.InsertString(4, L"Value=5000");
				m_comBox.InsertString(5, L"Value=6000");
				m_comBox.SetCurSel(0);
			}
			if (s3 == "ChangeMode")
			{
				m_comBox.InsertString(0, L"Value=0");//0：开环相对运动
				m_comBox.InsertString(1, L"Value=1");//1：开环绝对运动
				m_comBox.InsertString(2, L"Value=2");//2：闭环相对运动
				m_comBox.InsertString(3, L"Value=3");//3：闭环绝对运动
				m_comBox.InsertString(4, L"Value=4");//4：速率运动
				m_comBox.SetCurSel(0);
			}
			if (s3 == "Axis_Control")
			{
				m_comBox.InsertString(0, L"AxisNum=X");
				m_comBox.InsertString(1, L"AxisNum=Y");
				m_comBox.InsertString(2, L"AxisNum=Z");
				m_comBox.InsertString(3, L"AxisNum=A");
				m_comBox.InsertString(4, L"AxisNum=B");
				m_comBox.InsertString(5, L"AxisNum=C");
				m_comBox.SetCurSel(0);
			}
			if (s3 == "Limit?")
			{
				m_comBox.InsertString(0, L"Value=-1");
				m_comBox.InsertString(1, L"Value=0");
				m_comBox.InsertString(2, L"Value=1");
				m_comBox.SetCurSel(0);
			}
			if (s3 == "AxisSetTargetSpeed")
			{
				m_comBox.InsertString(0, L"Speed=20");
				m_comBox.InsertString(1, L"Speed=50");
				m_comBox.InsertString(2, L"Speed=100");
				m_comBox.InsertString(3, L"Speed=200");
				m_comBox.InsertString(4, L"Speed=500");
				m_comBox.InsertString(5, L"Speed=1000");
				m_comBox.SetCurSel(0);
			}
			if (s2 == "ImageProcessing:" && s3 == "CricleDetection")
			{
				m_comBox.InsertString(0, L"ROIY=1");
				m_comBox.InsertString(1, L"ROIY=10");
				m_comBox.InsertString(2, L"ROIY=100");
				m_comBox.InsertString(3, L"ROIY=1000");
				m_comBox.SetCurSel(0);
			}
			if (s2 == "ImageProcessing:" && s3 == "TemplateMatching")
			{
				m_comBox.InsertString(0, L"ROIX=1");
				m_comBox.InsertString(1, L"ROIX=10");
				m_comBox.InsertString(2, L"ROIX=100");
				m_comBox.InsertString(3, L"ROIX=1000");
				m_comBox.SetCurSel(0);
			}
			if (s2 == "AdjustingWithResult:" && s3 == "TemplateMatching")
			{
				m_comBox.InsertString(0, L"Result2=1");
				m_comBox.InsertString(1, L"Result2=2");
				m_comBox.InsertString(2, L"Result2=3");
				m_comBox.InsertString(3, L"Result2=4");
				m_comBox.InsertString(4, L"Result2=5");
				m_comBox.InsertString(5, L"Result2=6");
				m_comBox.SetCurSel(0);
			}
			if (s2 == "AdjustingWithResult:" && s3 == "CricleDetection")
			{
				m_comBox.InsertString(0, L"Result2=1");
				m_comBox.InsertString(1, L"Result2=2");
				m_comBox.InsertString(2, L"Result2=3");
				m_comBox.InsertString(3, L"Result2=4");
				m_comBox.InsertString(4, L"Result2=5");
				m_comBox.InsertString(5, L"Result2=6");
				m_comBox.InsertString(6, L"Result2=Preset1");
				m_comBox.InsertString(7, L"Result2=Preset2");
				m_comBox.InsertString(8, L"Result2=Preset3");
				m_comBox.InsertString(9, L"Result2=Preset4");
				m_comBox.InsertString(10, L"Result2=Preset5");
				m_comBox.InsertString(11, L"Result2=Preset6");
				m_comBox.SetCurSel(0);
			}

		}
		if (pNMListView->iSubItem == 7)
		{
			UpdateData(TRUE);
			int i = m_ListCtrl.GetSelectionMark();//获得选中行的行标
			CString s2 = m_ListCtrl.GetItemText(i, 2); //i是行，j是列。m_list是个list control 对象
			CString s3 = m_ListCtrl.GetItemText(i, 3); //i是行，j是列。m_list是个list control 对象
			CString s4 = m_ListCtrl.GetItemText(i, 4); //i是行，j是列。m_list是个list control 对象
			CString s5 = m_ListCtrl.GetItemText(i, 5); //i是行，j是列。m_list是个list control 对象
			CString s6 = m_ListCtrl.GetItemText(i, 6); //i是行，j是列。m_list是个list control 对象
			CString s7 = m_ListCtrl.GetItemText(i, 7); //i是行，j是列。m_list是个list control 对象
			CString s8 = m_ListCtrl.GetItemText(i, 8); //i是行，j是列。m_list是个list control 对象
			CString s9 = m_ListCtrl.GetItemText(i, 9); //i是行，j是列。m_list是个list control 对象
			//CString s10 = m_ListCtrl.GetItemText(i, 10); //i是行，j是列。m_list是个list control 对象
			if (s5 == "Coordinate=Cartesian")
			{
				m_comBox.InsertString(0, L"X=0");
				m_comBox.InsertString(1, L"X=50");
				m_comBox.InsertString(2, L"X=100");
				m_comBox.InsertString(3, L"X=500");
				m_comBox.InsertString(4, L"X=1000");
				m_comBox.InsertString(5, L"X=5000");
				m_comBox.SetCurSel(0);
			}
			if (s5 == "Coordinate=Joint")
			{
				m_comBox.InsertString(0, L"Axis2=-150");
				m_comBox.InsertString(1, L"Axis2=-120");
				m_comBox.InsertString(2, L"Axis2=-90");
				m_comBox.InsertString(3, L"Axis2=-60");
				m_comBox.InsertString(4, L"Axis2=-30");
				m_comBox.InsertString(5, L"Axis2=0");
				m_comBox.InsertString(6, L"Axis2=30");
				m_comBox.InsertString(7, L"Axis2=60");
				m_comBox.InsertString(8, L"Axis2=90");
				m_comBox.InsertString(9, L"Axis2=120");
				m_comBox.InsertString(10, L"Axis2=150");
				m_comBox.SetCurSel(5);
			}

			if (s4 == "RobotAbsolutePosition?" && s5 == "Coordinate=Cartesian")
			{
				m_comBox.InsertString(0, L"Y=0");
				m_comBox.InsertString(1, L"Y=50");
				m_comBox.InsertString(2, L"Y=100");
				m_comBox.InsertString(3, L"Y=500");
				m_comBox.InsertString(4, L"Y=1000");
				m_comBox.InsertString(5, L"Y=5000");
				m_comBox.SetCurSel(0);
			}
			if (s2 == "ImageProcessing:" && s3 == "CricleDetection")
			{
				m_comBox.InsertString(0, L"ROIWidth=1");
				m_comBox.InsertString(1, L"ROIWidth=10");
				m_comBox.InsertString(2, L"ROIWidth=100");
				m_comBox.InsertString(3, L"ROIWidth=1000");
				m_comBox.SetCurSel(0);
			}
			if (s2 == "ImageProcessing:" && s3 == "TemplateMatching")
			{
				m_comBox.InsertString(0, L"ROIY=1");
				m_comBox.InsertString(1, L"ROIY=10");
				m_comBox.InsertString(2, L"ROIY=100");
				m_comBox.InsertString(3, L"ROIY=1000");
				m_comBox.SetCurSel(0);
			}
			if (s4 == "Algorithm=Angcalc")
			{
				m_comBox.InsertString(0, L"R_IP=192.168.0.2");
				m_comBox.InsertString(1, L"R_IP=192.168.0.3");
				m_comBox.InsertString(2, L"R_IP=192.168.0.4");
				m_comBox.InsertString(3, L"R_IP=192.168.0.5");
				m_comBox.InsertString(4, L"R_IP=192.168.0.6");
				m_comBox.InsertString(5, L"R_IP=192.168.0.7");
				m_comBox.SetCurSel(0);
			}
			if (s4 == "Algorithm=Poscalc")
			{
				m_comBox.InsertString(0, L"X_IP=192.168.0.2");
				m_comBox.InsertString(1, L"X_IP=192.168.0.3");
				m_comBox.InsertString(2, L"X_IP=192.168.0.4");
				m_comBox.InsertString(3, L"X_IP=192.168.0.5");
				m_comBox.InsertString(4, L"X_IP=192.168.0.6");
				m_comBox.InsertString(5, L"X_IP=192.168.0.7");
				m_comBox.SetCurSel(0);
			}
			if (s3 == "ForceControlAxisMove")
			{
				m_comBox.InsertString(0, L"MaxForce=1");
				m_comBox.InsertString(1, L"MaxForce=10");
				m_comBox.InsertString(2, L"MaxForce=100");
				m_comBox.SetCurSel(0);
			}
			if (s3 == "Axis_Control")
			{
				m_comBox.InsertString(0, L"Value=1000");
				m_comBox.InsertString(1, L"Value=2000");
				m_comBox.InsertString(2, L"Value=3000");
				m_comBox.InsertString(3, L"Value=4000");
				m_comBox.InsertString(4, L"Value=5000");
				m_comBox.InsertString(5, L"Value=6000");
				m_comBox.SetCurSel(0);
			}
		}

		if (pNMListView->iSubItem == 8)
		{
			UpdateData(TRUE);
			int i = m_ListCtrl.GetSelectionMark();//获得选中行的行标
			CString s2 = m_ListCtrl.GetItemText(i, 2); //i是行，j是列。m_list是个list control 对象
			CString s3 = m_ListCtrl.GetItemText(i, 3); //i是行，j是列。m_list是个list control 对象
			CString s4 = m_ListCtrl.GetItemText(i, 4); //i是行，j是列。m_list是个list control 对象
			CString s5 = m_ListCtrl.GetItemText(i, 5); //i是行，j是列。m_list是个list control 对象
			CString s6 = m_ListCtrl.GetItemText(i, 6); //i是行，j是列。m_list是个list control 对象
			CString s7 = m_ListCtrl.GetItemText(i, 7); //i是行，j是列。m_list是个list control 对象
			CString s9 = m_ListCtrl.GetItemText(i, 9); //i是行，j是列。m_list是个list control 对象
			//CString s10 = m_ListCtrl.GetItemText(i, 10); //i是行，j是列。m_list是个list control 对象
			if (s5 == "Coordinate=Cartesian")
			{
				m_comBox.InsertString(0, L"Y=0");
				m_comBox.InsertString(1, L"Y=50");
				m_comBox.InsertString(2, L"Y=100");
				m_comBox.InsertString(3, L"Y=500");
				m_comBox.InsertString(4, L"Y=1000");
				m_comBox.InsertString(5, L"Y=5000");
				m_comBox.SetCurSel(0);
			}
			if (s5 == "Coordinate=Joint")
			{
				m_comBox.InsertString(0, L"Axis3=-100");
				m_comBox.InsertString(1, L"Axis3=-60");
				m_comBox.InsertString(2, L"Axis3=-30");
				m_comBox.InsertString(3, L"Axis3=0");
				m_comBox.InsertString(4, L"Axis3=30");
				m_comBox.InsertString(5, L"Axis3=60");
				m_comBox.InsertString(5, L"Axis3=100");
				m_comBox.SetCurSel(3);
			}
			if (s4 == "RobotAbsolutePosition?" && s5 == "Coordinate=Cartesian")
			{
				m_comBox.InsertString(0, L"Z=0");
				m_comBox.InsertString(1, L"Z=50");
				m_comBox.InsertString(2, L"Z=100");
				m_comBox.InsertString(3, L"Z=500");
				m_comBox.InsertString(4, L"Z=1000");
				m_comBox.InsertString(5, L"Z=5000");
				m_comBox.SetCurSel(0);
			}
			if (s2 == "ImageProcessing:" && s3 == "CricleDetection")
			{
				m_comBox.InsertString(0, L"ROIHight=1");
				m_comBox.InsertString(1, L"ROIHight=10");
				m_comBox.InsertString(2, L"ROIHight=100");
				m_comBox.InsertString(3, L"ROIHight=1000");
				m_comBox.SetCurSel(0);
			}
			if (s2 == "ImageProcessing:" && s3 == "TemplateMatching")
			{
				m_comBox.InsertString(0, L"ROIWidth=1");
				m_comBox.InsertString(1, L"ROIWidth=10");
				m_comBox.InsertString(2, L"ROIWidth=100");
				m_comBox.InsertString(3, L"ROIWidth=1000");
				m_comBox.SetCurSel(0);
			}
			if (s4 == "Algorithm=Angcalc")
			{
				m_comBox.InsertString(0, L"RPort=1");
				m_comBox.InsertString(1, L"RPort=2");
				m_comBox.InsertString(2, L"RPort=3");
				m_comBox.InsertString(3, L"RPort=4");
				m_comBox.InsertString(4, L"RPort=5");
				m_comBox.InsertString(5, L"RPort=6");
				m_comBox.SetCurSel(0);
			}
			if (s4 == "Algorithm=Poscalc")
			{
				m_comBox.InsertString(0, L"XPort=1");
				m_comBox.InsertString(1, L"XPort=2");
				m_comBox.InsertString(2, L"XPort=3");
				m_comBox.InsertString(3, L"XPort=4");
				m_comBox.InsertString(4, L"XPort=5");
				m_comBox.InsertString(5, L"XPort=6");
				m_comBox.SetCurSel(0);
			}
			if (s3 == "ForceControlAxisMove")
			{
				m_comBox.InsertString(0, L"PartNum=1");
				m_comBox.InsertString(1, L"PartNum=2");
				m_comBox.InsertString(2, L"PartNum=3");
				m_comBox.SetCurSel(0);
			}

		}
		if (pNMListView->iSubItem == 9)
		{
			UpdateData(TRUE);
			int i = m_ListCtrl.GetSelectionMark();//获得选中行的行标
			CString s2 = m_ListCtrl.GetItemText(i, 2); //i是行，j是列。m_list是个list control 对象
			CString s3 = m_ListCtrl.GetItemText(i, 3); //i是行，j是列。m_list是个list control 对象
			CString s4 = m_ListCtrl.GetItemText(i, 4); //i是行，j是列。m_list是个list control 对象
			CString s5 = m_ListCtrl.GetItemText(i, 5); //i是行，j是列。m_list是个list control 对象
			CString s6 = m_ListCtrl.GetItemText(i, 6); //i是行，j是列。m_list是个list control 对象
			CString s7 = m_ListCtrl.GetItemText(i, 7); //i是行，j是列。m_list是个list control 对象
			CString s8 = m_ListCtrl.GetItemText(i, 8); //i是行，j是列。m_list是个list control 对象
			CString s9 = m_ListCtrl.GetItemText(i, 9); //i是行，j是列。m_list是个list control 对象
			//CString s10 = m_ListCtrl.GetItemText(i, 10); //i是行，j是列。m_list是个list control 对象
			if (s5 == "Coordinate=Cartesian")
			{
				m_comBox.InsertString(0, L"Z=0");
				m_comBox.InsertString(1, L"Z=50");
				m_comBox.InsertString(2, L"Z=100");
				m_comBox.InsertString(3, L"Z=500");
				m_comBox.InsertString(4, L"Z=1000");
				m_comBox.InsertString(5, L"Z=5000");
				m_comBox.SetCurSel(0);
			}
			if (s5 == "Coordinate=Joint")
			{
				m_comBox.InsertString(0, L"Axis4=-50");
				m_comBox.InsertString(1, L"Axis4=-30");
				m_comBox.InsertString(2, L"Axis4=-10");
				m_comBox.InsertString(3, L"Axis4=0");
				m_comBox.InsertString(4, L"Axis4=10");
				m_comBox.InsertString(5, L"Axis4=30");
				m_comBox.InsertString(5, L"Axis4=50");
				m_comBox.SetCurSel(3);
			}
			if (s4 == "RobotAbsolutePosition?" && s5 == "Coordinate=Cartesian")
			{
				m_comBox.InsertString(0, L"R=0");
				m_comBox.InsertString(1, L"R=15");
				m_comBox.InsertString(2, L"R=30");
				m_comBox.InsertString(3, L"R=60");
				m_comBox.InsertString(4, L"R=120");
				m_comBox.InsertString(5, L"R=180");
				m_comBox.SetCurSel(0);
			}
			if (s2 == "ImageProcessing:" && s3 == "TemplateMatching")
			{
				m_comBox.InsertString(0, L"ROIHight=1");
				m_comBox.InsertString(1, L"ROIHight=10");
				m_comBox.InsertString(2, L"ROIHight=100");
				m_comBox.InsertString(3, L"ROIHight=1000");
				m_comBox.SetCurSel(0);
			}
			if (s2 == "ImageProcessing:" && s3 == "CricleDetection")
			{
				m_comBox.InsertString(0, L"CricleRadiusLow = 1");
				m_comBox.InsertString(1, L"CricleRadiusLow = 10");
				m_comBox.InsertString(2, L"CricleRadiusLow = 100");
				m_comBox.InsertString(3, L"CricleRadiusLow = 1000");
				m_comBox.SetCurSel(0);
			}
			if (s4 == "Algorithm=Poscalc")
			{
				
				m_comBox.InsertString(0, L"Y_IP=192.168.0.2");
				m_comBox.InsertString(1, L"Y_IP=192.168.0.3");
				m_comBox.InsertString(2, L"Y_IP=192.168.0.4");
				m_comBox.InsertString(3, L"Y_IP=192.168.0.5");
				m_comBox.InsertString(4, L"Y_IP=192.168.0.6");
				m_comBox.InsertString(5, L"Y_IP=192.168.0.7");
				m_comBox.SetCurSel(0);
			}

		}
		if (pNMListView->iSubItem == 10)
		{
			UpdateData(TRUE);
			int i = m_ListCtrl.GetSelectionMark();//获得选中行的行标
			CString s2 = m_ListCtrl.GetItemText(i, 2); //i是行，j是列。m_list是个list control 对象
			CString s3 = m_ListCtrl.GetItemText(i, 3); //i是行，j是列。m_list是个list control 对象
			CString s4 = m_ListCtrl.GetItemText(i, 4); //i是行，j是列。m_list是个list control 对象
			CString s5 = m_ListCtrl.GetItemText(i, 5); //i是行，j是列。m_list是个list control 对象
			CString s6 = m_ListCtrl.GetItemText(i, 6); //i是行，j是列。m_list是个list control 对象
			CString s7 = m_ListCtrl.GetItemText(i, 7); //i是行，j是列。m_list是个list control 对象
			CString s8 = m_ListCtrl.GetItemText(i, 8); //i是行，j是列。m_list是个list control 对象
			CString s9 = m_ListCtrl.GetItemText(i, 9); //i是行，j是列。m_list是个list control 对象
			CString s10 = m_ListCtrl.GetItemText(i, 10); //i是行，j是列。m_list是个list control 对象
			if (s2 == "ImageProcessing:" && s3 == "CricleDetection")
			{
				m_comBox.InsertString(0, L"CricleRadiusHigh = 100");
				m_comBox.InsertString(1, L"CricleRadiusHigh = 400");
				m_comBox.InsertString(2, L"CricleRadiusHigh = 800");
				m_comBox.InsertString(3, L"CricleRadiusHigh = 1600");
				m_comBox.SetCurSel(0);
			}
			if (s2 == "ImageProcessing:" && s3 == "TemplateMatching")
			{
				m_comBox.InsertString(0, L"iterationNum = 1");
				m_comBox.InsertString(1, L"iterationNum = 10");
				m_comBox.InsertString(2, L"iterationNum = 100");
				m_comBox.InsertString(3, L"iterationNum = 1000");
				m_comBox.SetCurSel(0);
			}
			if (s4 == "Algorithm=Poscalc")
			{
				m_comBox.InsertString(0, L"YPort=1");
				m_comBox.InsertString(1, L"YPort=2");
				m_comBox.InsertString(2, L"YPort=3");
				m_comBox.InsertString(3, L"YPort=4");
				m_comBox.InsertString(4, L"YPort=5");
				m_comBox.InsertString(5, L"YPort=6");
				m_comBox.SetCurSel(0);
			}
			if (s3 == "MoveRobot" && s5 == "Coordinate=Cartesian")
			{
				m_comBox.InsertString(0, L"R=0");
				m_comBox.InsertString(1, L"R=15");
				m_comBox.InsertString(2, L"R=30");
				m_comBox.InsertString(3, L"R=60");
				m_comBox.InsertString(4, L"R=120");
				m_comBox.InsertString(5, L"R=180");
				m_comBox.SetCurSel(0);
			}
			if (s5 == "Coordinate=Joint")
			{
				m_comBox.InsertString(0, L"Axis5=-180");
				m_comBox.InsertString(1, L"Axis5=120");
				m_comBox.InsertString(2, L"Axis5=-60");
				m_comBox.InsertString(3, L"Axis5=-30");
				m_comBox.InsertString(4, L"Axis5=0");
				m_comBox.InsertString(5, L"Axis5=30");
				m_comBox.InsertString(6, L"Axis5=60");
				m_comBox.InsertString(7, L"Axis5=120");
				m_comBox.InsertString(8, L"Axis5=180");
				m_comBox.SetCurSel(4);
			}
		}

		if (pNMListView->iSubItem == 11)
		{
			UpdateData(TRUE);
			int i = m_ListCtrl.GetSelectionMark();//获得选中行的行标
			CString s2 = m_ListCtrl.GetItemText(i, 2); //i是行，j是列。m_list是个list control 对象
			CString s3 = m_ListCtrl.GetItemText(i, 3); //i是行，j是列。m_list是个list control 对象
			CString s4 = m_ListCtrl.GetItemText(i, 4); //i是行，j是列。m_list是个list control 对象
			CString s5 = m_ListCtrl.GetItemText(i, 5); //i是行，j是列。m_list是个list control 对象
			CString s6 = m_ListCtrl.GetItemText(i, 6); //i是行，j是列。m_list是个list control 对象
			CString s7 = m_ListCtrl.GetItemText(i, 7); //i是行，j是列。m_list是个list control 对象
			CString s8 = m_ListCtrl.GetItemText(i, 8); //i是行，j是列。m_list是个list control 对象
			CString s9 = m_ListCtrl.GetItemText(i, 9); //i是行，j是列。m_list是个list control 对象
			CString s10 = m_ListCtrl.GetItemText(i, 10); //i是行，j是列。m_list是个list control 对象
			CString s11 = m_ListCtrl.GetItemText(i, 11); //i是行，j是列。m_list是个list control 对象

			/*if (s6 == "Coordinate=Joint")
			{
					m_comBox.InsertString(0, L"Axis5=-180");
					m_comBox.InsertString(1, L"Axis5=120");
					m_comBox.InsertString(2, L"Axis5=-60");
					m_comBox.InsertString(3, L"Axis5=-30");
					m_comBox.InsertString(4, L"Axis5=0");
					m_comBox.InsertString(5, L"Axis5=30");
					m_comBox.InsertString(6, L"Axis5=60");
					m_comBox.InsertString(7, L"Axis5=120");
					m_comBox.InsertString(8, L"Axis5=180");
					m_comBox.SetCurSel(4);
			}*/

			if (s2 == "ImageProcessing:" && s3 == "TemplateMatching")
			{
				m_comBox.InsertString(0, L"smoothness = 1");
				m_comBox.InsertString(1, L"smoothness = 10");
				m_comBox.InsertString(2, L"smoothness = 100");
				m_comBox.InsertString(3, L"smoothness = 1000");
				m_comBox.SetCurSel(0);
			}


		}
		m_comBox.ShowDropDown();//自动下拉
	
}

void CDiailogEditor::OnPageup()//向上移动一行
{
	UpdateData(TRUE);

	if (haveeditcreate == true)//如果之前创建了编辑框就销毁掉
	{
		distroyEdit(&m_ListCtrl, &m_Edit, e_Item, e_SubItem);//销毁单元格编辑框对象
		haveeditcreate = false;
	}
	if (haveccomboboxcreate == true)//如果之前创建了下拉列表框就销毁掉
	{
		distroyCcombobox(&m_ListCtrl, &m_comBox, e_Item, e_SubItem);
		haveccomboboxcreate = false;
	}

	int nIdx = m_ListCtrl.GetSelectionMark();//获取当前行号

	if (nIdx == 0)//判断是否在第一行
	{
		return;//不作为
	}

	else//在非第一行的时候
	{// 提取内容   
		CString temp1[12];
		int i;
		for (i = 1; i < 13; i++)
			temp1[i - 1] = m_ListCtrl.GetItemText(nIdx, i);//将本行数据存起来

		CString temp2[12];
		int j;
		for (j = 1; j < 13; j++)
			temp2[j- 1] = m_ListCtrl.GetItemText(nIdx-1, j);//将上面一行数据存起来
		// 删除   
		//m_ListCtrl.DeleteItem(nIdx);//删除本行
		//m_ListCtrl.DeleteItem(nIdx-1);//删除上一行
		// 在nItem-1位置处插入   
		for (i = 1; i < 13; i++)
			m_ListCtrl.SetItemText(nIdx - 1, i, temp1[i - 1]);//除了第一列序号以外都移动
		//在nItem位置处插入
		for (j = 1; j < 13; j++)
			m_ListCtrl.SetItemText(nIdx, j, temp2[j - 1]);
		m_ListCtrl.SetItemState(nIdx-1, LVIS_FOCUSED | LVIS_SELECTED, LVIS_FOCUSED | LVIS_SELECTED);   //g高亮
		m_ListCtrl.SetSelectionMark(nIdx-1);//选中		
	}
}

void CDiailogEditor::OnPagedown()//向下移动一行
{
	int nIdx = m_ListCtrl.GetSelectionMark();//获得当前行号

	if (haveeditcreate == true)//如果之前创建了编辑框就销毁掉
	{
		distroyEdit(&m_ListCtrl, &m_Edit, e_Item, e_SubItem);//销毁单元格编辑框对象
		haveeditcreate = false;
	}
	if (haveccomboboxcreate == true)//如果之前创建了下拉列表框就销毁掉
	{
		distroyCcombobox(&m_ListCtrl, &m_comBox, e_Item, e_SubItem);
		haveccomboboxcreate = false;
	}

	if (nIdx == m_ListCtrl.GetItemCount() - 1)//判断是否位于最后一行
	{
		return;//不作为
	}
	else
	{
	// 提取内容   
		CString temp1[12];
		int i;
		for (i = 1; i<13; i++)
			temp1[i-1] = m_ListCtrl.GetItemText(nIdx, i);//将本行数据存储
		CString temp2[12];
		int j;
		for (j= 1; j<13; j++)
			temp2[j - 1] = m_ListCtrl.GetItemText(nIdx+1, j);//将下一行数据存储	
	// 删除   
	//m_ListCtrl.DeleteItem(nIdx);
	// 在nItem+1位置处插入   （交换数据）
		for (i = 1; i<13; i++)
			m_ListCtrl.SetItemText(nIdx + 1, i, temp1[i-1]);
		for (j = 1; j<13; j++)
			m_ListCtrl.SetItemText(nIdx, j, temp2[j - 1]);
	//高亮显示   
		m_ListCtrl.SetItemState(nIdx +1, LVIS_FOCUSED | LVIS_SELECTED, LVIS_FOCUSED | LVIS_SELECTED);   //g高亮
		m_ListCtrl.SetSelectionMark(nIdx + 1);//选中
	}
}

void CDiailogEditor::OnBnClickedButton8()//上移
{
	// TODO: 在此添加控件通知处理程序代码
	CDiailogEditor::OnPageup();
}
void CDiailogEditor::OnBnClickedButton9()//下移
{
	// TODO: 在此添加控件通知处理程序代码
	CDiailogEditor::OnPagedown(); 
}

void CDiailogEditor::OnNMCustomdrawList4(NMHDR *pNMHDR, LRESULT *pResult)//隔行设置listcontrol背景色
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	NMLVCUSTOMDRAW* pLVCD = reinterpret_cast<NMLVCUSTOMDRAW*>(pNMHDR);
	*pResult = CDRF_DODEFAULT;
	if (CDDS_PREPAINT == pLVCD->nmcd.dwDrawStage)
	{
		*pResult = CDRF_NOTIFYITEMDRAW;
	}

	else if (CDDS_ITEMPREPAINT == pLVCD->nmcd.dwDrawStage)
	{
		COLORREF crText, crBk;
		//奇偶判断
		if ((pLVCD->nmcd.dwItemSpec % 2) == 0)
		{
			crText = RGB(0, 0, 0);
			crBk = RGB(214, 240, 245);
		}
		else if ((pLVCD->nmcd.dwItemSpec % 2) == 1)
		{			
			crText = RGB(0, 0, 0);//RGB(32,32,255);
			crBk = RGB(255, 255, 255);
		}
		else
		{
			crText = RGB(0, 0, 0);
			crBk = RGB(0, 0, 126);
		}
		pLVCD->clrText = crText;
		pLVCD->clrTextBk = crBk;
		//设置选择项的颜色
		if (this->m_ListCtrl.GetItemState(pLVCD->nmcd.dwItemSpec, CDIS_SELECTED))
		{
			crBk = RGB(75, 149, 229);//itunes//RGB(10, 36, 106);//RGB(0, 0, 64);
			crText = RGB(255, 255, 255);
			pLVCD->clrText = crText;
			pLVCD->clrTextBk = crBk;
			*pResult = CDRF_NEWFONT;
		}
		if (LVIS_SELECTED == m_ListCtrl.GetItemState(pLVCD->nmcd.dwItemSpec, LVIS_SELECTED))
		{
			//清除选择状态，如果不清除的话，还是会显示出蓝色的高亮条
			BOOL b = m_ListCtrl.SetItemState(pLVCD->nmcd.dwItemSpec, 0, LVIS_SELECTED);
			pLVCD->clrText = crText;
			pLVCD->clrTextBk = crBk;
			*pResult = CDRF_NEWFONT;
			return;
		}
		*pResult = CDRF_NEWFONT;
	}
}
void CDiailogEditor::OnBnClickedButton13()//插入文件序列
{
	// TODO: 在此添加控件通知处理程序代码
	if (haveeditcreate == true)//如果之前创建了编辑框就销毁掉
	{
		distroyEdit(&m_ListCtrl, &m_Edit, e_Item, e_SubItem);//销毁单元格编辑框对象
		haveeditcreate = false;
	}
	if (haveccomboboxcreate == true)//如果之前创建了下拉列表框就销毁掉
	{
		distroyCcombobox(&m_ListCtrl, &m_comBox, e_Item, e_SubItem);
		haveccomboboxcreate = false;
	}

	UpdateData(TRUE);
	CString strTemp;
	m_Row = m_ListCtrl.GetItemCount();//当前总行数
	int nIdx = m_ListCtrl.GetSelectionMark();//获得目前鼠标点击的行号
	CString content;//定义一个变量用于接收读取的一行内容
	int line = 0;//插入文本的行数txt
	int nItem;//插入行数list
	int iSubItem;//插入的列数
				 //新建一行空白行在当前行的下一行

				 //strTemp.Format(_T("%d"), nIdx + 2);
				 //m_ListCtrl.InsertItem(nIdx + nItem, strTemp);

	if (MessageBox(_T("即将在鼠标所在位置插入一个文本序列"), _T("提示 "), MB_YESNO) == IDYES)
	{
		//ShellExecute(NULL,NULL,SW_SHOWNORMAL);
		//获取exe文件的路径

		//m_ListCtrl.DeleteAllItems(); // 全部清空  
		CString path;
		GetModuleFileName(NULL, path.GetBufferSetLength(MAX_PATH + 1), MAX_PATH);
		path.ReleaseBuffer();
		int pos = path.ReverseFind('\\');
		path = path.Left(pos);
		path = path + _T("\\");

		CString   strFileName;
		CFileDialog   m_ldFile(TRUE);

		m_ldFile.m_ofn.lpstrFilter = _T("*.txt "); //要选择的文件后缀
		m_ldFile.m_ofn.lpstrInitialDir = path;//默认的文件路径
		m_ldFile.m_ofn.lpstrDefExt = _T("txt");//默认扩展名

		if (m_ldFile.DoModal() == IDOK)
		{
			strFileName = m_ldFile.GetPathName();       //包括了路径和文件名 
		}
		//选择文件，并打开	
		LPCTSTR pszFileName = strFileName.GetBufferSetLength(strFileName.GetLength());
		CStdioFile myFile;
		BOOL ret = myFile.Open(pszFileName, CFile::modeRead);
		CString FullName = myFile.GetFileTitle();
		int index = 0;
		index = FullName.Find('.');//在指令的第三行字符中查找是否包含字符：value,从0位置开始查，返回的是位置
		//m_ProcessName = FullName.Left(index);

		//SetDlgItemText(IDC_EDIT5, myFile.GetFileTitle());//将文件名称写在页面上
		UpdateData(FALSE);
		if (!ret)
		{
			AfxMessageBox(_T("插入文件失败"));
			return;
		}
		if (ret)//文件打开成功
		{

			char* old_locale = _strdup(setlocale(LC_CTYPE, NULL));
			setlocale(LC_CTYPE, "chs");
			while (myFile.ReadString(content) != FALSE)//一行行读
			{
				iSubItem = line % 13;//取余数
				nItem = line / 13;//取商
				if (iSubItem == 0)//序号是v                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              
				{

					m_ListCtrl.InsertItem(nItem + nIdx, _T(""));//InsertItem是向控件声请一行来放数据,记住只是声请,那么放置数据的工作就由SetItemText来实现
					m_ListCtrl.SetItemText(nItem + nIdx, iSubItem, content);//插入的第一列
					CString nTemp;
					nTemp.Format(_T("%d"), nItem + nIdx + 1);
					m_ListCtrl.SetItemText(nItem + nIdx, 0, nTemp);

					UpdateData(FALSE);
					line++;
				}
				if (iSubItem == 2 || iSubItem == 3 || iSubItem == 4 || iSubItem == 5 || iSubItem == 6 || iSubItem == 7 || iSubItem == 8 || iSubItem == 9 || iSubItem == 10 || iSubItem == 11 || iSubItem == 12 )
				{
					m_ListCtrl.SetItemText(nItem + nIdx, iSubItem, content);
					UpdateData(FALSE);
					line++;
				}
				if (iSubItem == 1)//备注列
				{
					m_ListCtrl.SetItemText(nItem + nIdx, iSubItem, content);
					UpdateData(FALSE);
					line++;
				}
			}
			line = line + 1;
			nItem = nItem + 1;

			setlocale(LC_CTYPE, old_locale);
			free(old_locale);

			//改变鼠标下面行的序号
			int a;
			//后面的序号+
			for (a = nIdx + nItem; a <= nItem + m_Row; a++)
			{
				strTemp.Format(_T("%d"), a + 1);
				m_ListCtrl.SetItemText(a, 0, strTemp);
			}
			//设置高亮

			/*m_ListCtrl.SetItemState(nIdx + nItem, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);
			m_ListCtrl.EnsureVisible(m_Row, FALSE);*/


			CString temp;
			temp.Format(_T("%d"), nItem);//整形转换成字符

			CString str = _T("已插入数据行数：") + temp;

			MessageBox(str, _T("提示 "), MB_YESNO);    //读取晚报告并返回

													 //myFile.GetFileName()   //得到完整的文件名，包括扩展名如：test1.txt
													 //GetFileTitle()//获得文件名称，不含后缀

			myFile.Close();
		}
	}
}
void CDiailogEditor::OnBnClickedButton10() //在鼠标下方插入一行空行
{

	if (haveeditcreate == true)//如果之前创建了编辑框就销毁掉
	{
		distroyEdit(&m_ListCtrl, &m_Edit, e_Item, e_SubItem);//销毁单元格编辑框对象
		haveeditcreate = false;
	}
	if (haveccomboboxcreate == true)//如果之前创建了下拉列表框就销毁掉
	{
		distroyCcombobox(&m_ListCtrl, &m_comBox, e_Item, e_SubItem);
		haveccomboboxcreate = false;
	}
	//末端先新建一行
	UpdateData(TRUE);
	CString strTemp;
	m_Row = m_ListCtrl.GetItemCount();//当前行数
	int nIdx = m_ListCtrl.GetSelectionMark();//获得目前鼠标点击的行号
	
	//新建一行空白行在当前行的下一行
	
	strTemp.Format(_T("%d"), nIdx + 2);
	m_ListCtrl.InsertItem(nIdx + 1, strTemp);

	//m_ListCtrl.EnsureVisible(m_Row, FALSE);
	//改变下面行的序号
	int a;
	//后面的序号+1
	

	for (a = m_Row+1; a > nIdx - 1; a--)
	{
		strTemp.Format(_T("%d"), a+1);
		m_ListCtrl.SetItemText(a, 0, strTemp);
	}
	//设置高亮

	m_ListCtrl.SetItemState(nIdx + 1, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);
	

}


void CDiailogEditor::OnBnClickedButton11()//删除一行
{
	CString strTemp;

	if (haveeditcreate == true)//如果之前创建了编辑框就销毁掉
	{
		distroyEdit(&m_ListCtrl, &m_Edit, e_Item, e_SubItem);//销毁单元格编辑框对象
		haveeditcreate = false;
	}
	if (haveccomboboxcreate == true)//如果之前创建了下拉列表框就销毁掉
	{
		distroyCcombobox(&m_ListCtrl, &m_comBox, e_Item, e_SubItem);
		haveccomboboxcreate = false;
	}
	m_Row = m_ListCtrl.GetItemCount();//总行数
	int nIdx = m_ListCtrl.GetSelectionMark();//获得目前鼠标点击的行号
	m_ListCtrl.DeleteItem(nIdx);
	int a;
	//后面的序号-1
	for (a = m_Row ; a > nIdx-1; a--)
	{
		strTemp.Format(_T("%d"), a+1);
		m_ListCtrl.SetItemText(a,0, strTemp);
	}
}


void CDiailogEditor::OnBnClickedButton3()//保存文档txt
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	//GetDlgItem(IDC_EDIT4)->SetFocus();设置输入焦点
	if (haveeditcreate == true)//如果之前创建了编辑框就销毁掉
	{
		distroyEdit(&m_ListCtrl, &m_Edit, e_Item, e_SubItem);//销毁单元格编辑框对象
		haveeditcreate = false;
	}
	if (haveccomboboxcreate == true)//如果之前创建了下拉列表框就销毁掉
	{
		distroyCcombobox(&m_ListCtrl, &m_comBox, e_Item, e_SubItem);
		haveccomboboxcreate = false;
	}
	//获取exe文件的路径
	CString path;
	GetModuleFileName(NULL, path.GetBufferSetLength(MAX_PATH + 1), MAX_PATH);
	path.ReleaseBuffer();
	int pos = path.ReverseFind('\\');
	path = path.Left(pos);
	path = path + _T("\\");
	CString   strFileName;
	CFileDialog   m_ldFile(FALSE);
	m_ldFile.m_ofn.lpstrFilter = _T("*.txt "); //要选择的文件后缀
	m_ldFile.m_ofn.lpstrInitialDir = path;//默认的文件路径
	m_ldFile.m_ofn.lpstrDefExt = _T("txt");//默认扩展名
	LPWSTR  lpstr = (LPWSTR)(LPCWSTR)m_ProcessName;//类型转换
	CString imgName;
	imgName = m_ldFile.GetFileName();//获取文件名

	if (m_ProcessName == "")//如果未输入名称
	{
		m_ldFile.DoModal();//模态对话框创建，用户输入名称
		strFileName = m_ldFile.GetPathName();//包括了路径和文件名
	}
	//创建文件	
	if (m_ProcessName != "")//如果已经有了名称 直接保存在默认路径
	{
		m_ldFile.m_ofn.lpstrFile = lpstr;//设置默认文件名
		strFileName = path + m_ProcessName+_T(".txt");
	}  
	LPCTSTR pszFileName = strFileName.GetBufferSetLength(strFileName.GetLength());
	CStdioFile myFile;
	CFileException   fileException;
	if (true == (bool)PathFileExists(strFileName)) //判断是否已经存在
	{
		if (MessageBox(_T("已存在，是否覆盖？ "), _T("提示 "), MB_YESNO) == IDYES)
		{
			BOOL ret = myFile.Open(pszFileName, CFile::modeCreate | CFile::modeWrite | CFile::typeText, &fileException);
			if (!ret)
			{
				AfxMessageBox(_T("保存失败，请重新保存！"));
				return;
			}
				//文件中写入内容 
			SaveListCell(myFile);//存储txt函数
			//是否立即查看该文件 
			if (MessageBox(_T("已保存，要查看吗 "), _T("完成 "), MB_YESNO) == IDYES)
			{
				//ShellExecute(NULL,NULL,SW_SHOWNORMAL);
				ShellExecute(NULL, _T("open"), pszFileName, NULL, NULL, SW_SHOWNORMAL);//功能是运行一个外部程序记事本
			}
			//关闭文件 
			myFile.Close();		
		}
		else
		{
			MessageBox(_T("请修改名称重新保存 "), _T("提示 "), MB_YESNO);
		}
	}
	if (false == (bool)PathFileExists(strFileName))//名字是新名字
	{
		BOOL ret = myFile.Open(pszFileName, CFile::modeCreate | CFile::modeWrite | CFile::typeText, &fileException);
		if (!ret)
		{
			AfxMessageBox(_T("保存失败，请重新保存！"));
			return;
		}
		//文件中写入内容 
		SaveListCell(myFile);
		//是否立即查看该文件 
		if (MessageBox(_T("已保存，要查看吗 "), _T("完成 "), MB_YESNO) == IDYES)
		{
			//ShellExecute(NULL,NULL,SW_SHOWNORMAL);
			ShellExecute(NULL, _T("open"), pszFileName, NULL, NULL, SW_SHOWNORMAL);//功能是运行一个外部程序记事本
		}
		//关闭文件 
		myFile.Close();
	}

}
void CDiailogEditor::SaveListCell(CStdioFile & File)
{
	int   iColSum = 12;       //List中的栏数列数
	int   iCount = m_ListCtrl.GetItemCount();//行数
	for (int iItem = 0; iItem < iCount; iItem++)
	{
		for (int iCol = 0; iCol < iColSum; iCol++)//只保存后面5列
		{
			CString   strTemp = m_ListCtrl.GetItemText(iItem, iCol);
			if (iCol == 0 || iCol == 2 || iCol == 3 || iCol == 5 || iCol == 6 || iCol == 7 || iCol == 8||iCol == 1|| iCol == 4 || iCol == 9 || iCol == 10)
			{
				//lstrcat(strTemp.GetBuffer(strTemp.GetLength()), _T(")"));
				char* old_locale = _strdup(setlocale(LC_CTYPE, NULL));
				setlocale(LC_CTYPE, "chs");//设定
				try
				{
					lstrcat(strTemp.GetBuffer(strTemp.GetLength()), _T("\n"));//换行
					File.WriteString(strTemp.GetBuffer(strTemp.GetLength()));
				}
				catch (CException* e)
				{
					e->ReportError();
				}
				setlocale(LC_CTYPE, old_locale);
				free(old_locale);//还原区域设定
			}
			if (iCol == 11)
			{
				//lstrcat(strTemp.GetBuffer(strTemp.GetLength()), _T(")"));
				char* old_locale = _strdup(setlocale(LC_CTYPE, NULL));
				setlocale(LC_CTYPE, "chs");//设定
				try
				{
					lstrcat(strTemp.GetBuffer(strTemp.GetLength()), _T("\n\n"));//换两行
					File.WriteString(strTemp.GetBuffer(strTemp.GetLength()));
				}
				catch (CException* e)
				{
					e->ReportError();
				}
				setlocale(LC_CTYPE, old_locale);
				free(old_locale);//还原区域设定
			}
			
		}
	}
}


void CDiailogEditor::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	CDialogEx::OnActivate(nState, pWndOther, bMinimized);

	// TODO: 在此处添加消息处理程序代码
	UpdateData(FALSE);
}
LRESULT CDiailogEditor::OnMyMessage(WPARAM wParam, LPARAM lParam)
{
	//MessageBox("recv msg success");
	//添加自己的消息处理
	m = pEdit->resultFileName;
	//m_comBox.InsertString(0, m);
	//m_comBox.SetCurSel(0);
	m_Edit.SetWindowText(m);///////m_edit2为编辑框变量，类型为Cedit

	UpdateData(FALSE);

		return 0;
}

void CDiailogEditor::OnBnClickedButton2()//清空列表
{
	// TODO: 在此添加控件通知处理程序代码
	if (MessageBox(_T("当前内容将会清空！是否继续？"), _T("提示 "), MB_YESNO) == IDYES)
	{
		//ShellExecute(NULL,NULL,SW_SHOWNORMAL);
		//获取exe文件的路径
		m_ProcessName = _T("");
		UpdateData(FALSE);
		m_ListCtrl.DeleteAllItems(); // 全部清空  
	}
}


void CDiailogEditor::OnBnClickedButton4()//统计行数
{
	// TODO: 在此添加控件通知处理程序代码


	int Num = m_ListCtrl.GetItemCount();

	CString temp;
	temp.Format(_T("%d"), Num);//整形转换成字符


	CString str = _T("当前命令行数共计：") + temp;

	MessageBox(str, _T("提示 "), MB_YESNO) == IDYES;
}


void CDiailogEditor::OnBnClickedButton12()
{
	MessageBox(_T("请先先保存再检查"), _T("提示 "), MB_YESNO) == IDYES;
	//打开TXT文件。
	CString path;
	GetModuleFileName(NULL, path.GetBufferSetLength(MAX_PATH + 1), MAX_PATH);
	path.ReleaseBuffer();
	int pos = path.ReverseFind('\\');
	path = path.Left(pos);
	path = path + _T("\\");

	CString   strFileName;
	CFileDialog   m_ldFile(TRUE);

	m_ldFile.m_ofn.lpstrFilter = _T("*.txt "); //要选择的文件后缀
	m_ldFile.m_ofn.lpstrInitialDir = path;//默认的文件路径
	m_ldFile.m_ofn.lpstrDefExt = _T("txt");//默认扩展名

	if (m_ldFile.DoModal() == IDOK)
	{
		strFileName = m_ldFile.GetPathName();       //包括了路径和文件名 
	}
	//选择文件，并打开	
	LPCTSTR pszFileName = strFileName.GetBufferSetLength(strFileName.GetLength());
	CStdioFile myFile;
	BOOL ret = myFile.Open(pszFileName, CFile::modeRead);
	m_ProcessName = myFile.GetFileTitle();
	//SetDlgItemText(IDC_EDIT5, myFile.GetFileTitle());//将文件名称写在页面上
	UpdateData(FALSE);
	if (!ret)
	{
		AfxMessageBox(_T("打开文件失败"));
		return;
	}
	if (ret)//文件打开成功
	{
		beginExamination(myFile);//开始检查
	}
	CString m;
	m.Format(_T("%d"), m_commNum);//int转换成字符
	AddString(_T("一共检查了") + m + _T("条指令！"));
	AddString(_T(""));//空一行
	myFile.Close();
}
void CDiailogEditor::beginExamination(CStdioFile&File)
{
	//新建一个页面来输出检查结果
	if (NULL == m_exam)  // 如果指针变量m_create的值为NULL，则对话框还未创建，需要动态创建   
	{
		m_exam = new CExamination();   //动态创建对象
		m_exam->Create(IDD_DIALOG_Examination, this);
	}
	m_exam->ShowWindow(SW_SHOW);  // 显示非模态对话框   
	m_exam->SetWindowPos(NULL, 550, 250, 0, 0, SWP_NOSIZE);
	//SWP_NOSIZE保持当前对话框大小（第4、5参数cx和cy会被忽略）设置非模态对话框的位置

	m_commNum = pMainDlg->findCoronNum(&File);//冒号个数，即指令的条数
	if (m_commNum == 0)
	{
		AddString(_T("脚本中无任何指令？"));
	}
	else
	{
		CommandExamination(File);//指令检测函数
	}
}
void CDiailogEditor::AddString(CString msg)    //向日志列表添加日志
{

	if (msg.GetLength() > 10000)
	{
		if (pExam->m_ListResult.AddString(msg.Left(10000)) == LB_ERRSPACE)
		{
			pExam->m_ListResult.InsertString(pExam->m_LogNum % 200000, msg.Left(10000));
		}
	}
	else if (pExam->m_ListResult.AddString(msg) == LB_ERRSPACE)
	{
		pExam->m_ListResult.InsertString(pExam->m_LogNum % 200000, msg);
	}
	pExam->m_LogNum++;
	//添加日志到列表中	
	//更新
	//UpdateData(FALSE);	
	//将滚动条置于最下面
	pExam->m_ListResult.SetTopIndex(pExam->m_LogNum % 200000 - 1);
}
void CDiailogEditor::CommandExamination(CStdioFile&File)//8种指令的错误检查
{
	int i = 1;
	CString a;
	while (!feof(File.m_pStream))//feof检查文档是否到末尾
	{

		m_fileComm = pMainDlg->findCoron(&File);//return str返回冒号和它前面的字符数据，即指令名称（包括冒号）：//如果到了结尾返回null？
		a.Format(_T("%d"), i);//int转换成字符
		if (m_fileComm == _T(":"))//如果指令名称是空的，也就是空指令
		{
			AddString(_T("指令") + a + _T("：“空指令！”"));
			i++;
			continue;
		}
		if (m_fileComm== _T("Common:"))//--------------------------------普通指令1
		{
			AddString(_T("指令") + a + _T("：OK！"));
			examCommon(File, i);
			i++;
			continue;
		}
		if (m_fileComm==_T("Inquiry:"))
		{
			AddString(_T("指令") + a + _T("：OK！"));
			examInquiry(File, i);//---------------------------------------------------查询命令2
			i++;
			continue;
		}
		if (m_fileComm == _T("Robot:"))
		{
			AddString(_T("指令") + a + _T("：OK！"));
			examRobot(File, i);//---------------------------------------------------机器人命令3
			i++;
			continue;
		}
		if (m_fileComm== _T("DelayTime:"))
		{
			AddString(_T("指令") + a + _T("：OK！"));
			examDelayTime(File, i);
			i++;
			continue;//--------------------------------------------------------延时命令4
		}
		if (m_fileComm== _T("ThreadInteraction:"))//---------------线程交互命令5
		{
			AddString(_T("指令") + a + _T("：OK！"));
			examThreadInteraction(File, i);
			i++;
			continue;
		}
		if (m_fileComm == _T("ImageProcessing:"))
		{
			AddString(_T("指令") + a + _T("：OK！"));
			examImageProcessing(File, i);//------------------------------------图像处理命令6
			i++;
			continue;
		}
		if (m_fileComm == _T("LightAdjusting:"))
		{
			AddString(_T("指令") + a + _T("：OK！"));
			examLightAdjusting(File, i);//---------------------------------------光源调节命令7
			i++;
			continue;

		}
		if (m_fileComm == _T("AdjustingWithResult:"))
		{
			AddString(_T("指令") + a + _T("：OK！"));
			examAdjustingWithResult(File, i); //----------------------------------微调设备命令8
			i++;
			continue;
		}
		if (m_fileComm == "")//如果返回的是NULL
		{
			AddString(_T(""));
			AddString(_T("检查完毕！"));
			break;
		}
		else
		{
			AddString(_T("指令") + a + _T("：“未定义！”"));
			i++;
			continue;
		}
	}
}
void CDiailogEditor::examCommon(CStdioFile&File, int i)//一共八行
{
	CString comm[4];//存储读取到的4行数据
	
					//file->ReadString(m_fileComm);
	CString MiddleComm;
	for (i = 0; i < 4; i++)
	{
		comm[i] = pMainDlg->ChineseTransformation(MiddleComm, &File);
	}
	CString a;
	a.Format(_T("%d"), i);//int转换成字符
	if (comm[0] == "")
	{
		AddString(_T("    参数1：“空参数！”"));
	}

	else if (comm[0] == "\r\nIO" || comm[0] == "\r\nAxisMove" || comm[0] == "\r\nAxisSetTargetSpeed")
	{
		AddString(_T("    参数1："));
		examEmpty(1, 3, comm, a);
	}
	else if (comm[0] == "\r\nAxisSetHomePosition" || comm[0] == "\r\nAxisGoHomePosition" || comm[0] == "\r\nAxisGoPositiveLimit" || comm[0] == "\r\nAxisGoNegativeLimit" || comm[0] == "AxisSMVR")
	{
		AddString(_T("    参数1："));
		examEmpty(1, 2, comm, a);
	}
	else
	{
		AddString(_T("    参数1：“未定义！”"));
	}
}
void CDiailogEditor::examInquiry(CStdioFile&File, int i)
{

	CString comm[4];//存储读取到的4行数据
					//file->ReadString(m_fileComm);
	CString MiddleComm;
	for (i = 0; i < 4; i++)
	{
		comm[i] = pMainDlg->ChineseTransformation(MiddleComm, &File);
	}
	CString a;
	a.Format(_T("%d"), i);//int转换成字符
	examEmpty(0, 3, comm, a);

	if(comm[0]== "\r\nLimit?"&&comm[3]!="")
	{
		if (comm[3]!="\r\nValue=-1"&& comm[3] !="\r\nValue=1"&& comm[3] != "\r\nValue=0")
		{
			AddString(_T("    限位查询Value值错误"));
		}
	}
}
void CDiailogEditor::examRobot(CStdioFile&File, int i)
{
	CString comm[7];//存储读取到的4行数据
	//file->ReadString(m_fileComm);
	CString MiddleComm;
	for (i = 0; i < 7; i++)
	{
		comm[i] = pMainDlg->ChineseTransformation(MiddleComm, &File);
	}

	CString a;
	a.Format(_T("%d"), i);//int转换成字符
	if (comm[0] == "MoveRobot")
	{
		AddString(_T("    参数1："));
		examEmpty(1, 6, comm, a);
	}
	else if (comm[0] == "InquiryRobot")
	{
		AddString(_T("    参数1："));
		if (comm[1] == "RobotStatus?")
		{
			AddString(_T("    参数2："));
			examEmpty(2, 2, comm, a);
		}
		else if (comm[1] == "RobotAbsolutePosition?")
		{
			AddString(_T("    参数2："));
			examEmpty(2, 5, comm, a);
		}
		else if (comm[1] == "")
		{
			AddString(_T("    参数2：“空参数！”"));
		}
		else
		{
			AddString(_T("    参数2：“未定义！”"));
		}
	}
	else if (comm[0] == "")
	{
		AddString(_T("    参数1：“空参数！”"));
	}
	else
	{
		AddString(_T("    参数1：“未定义！”"));
	}

}
void CDiailogEditor::examDelayTime(CStdioFile&File, int i)
{
	CString comm[1];//存储读取到的4行数据
					//file->ReadString(m_fileComm);
	CString MiddleComm;
	for (i = 0; i < 1; i++)
	{
		comm[i] = pMainDlg->ChineseTransformation(MiddleComm, &File);
	}
	CString a;
	a.Format(_T("%d"), i);//int转换成字符
	examEmpty(0, 0, comm, a);
}
void CDiailogEditor::examThreadInteraction(CStdioFile&File, int i)
{
	CString comm[3];//存储读取到的4行数据
					//file->ReadString(m_fileComm);
	CString MiddleComm;
	for (i = 0; i < 4; i++)
	{
		comm[i] = pMainDlg->ChineseTransformation(MiddleComm, &File);
	}
	
	CString a;
	a.Format(_T("%d"), i);//int转换成字符
	examEmpty(0, 2, comm, a);
	if (comm[1].GetLength() != 0&& comm[2].GetLength() != 0)
	{

		int index = pMainDlg->findChar(comm[1], '=', 1);
		int SenderThreadNum = _ttoi(comm[1].Mid(index));
		index = pMainDlg->findChar(comm[2], '=', 1);
		int RecipientThreadNum = _ttoi(comm[2].Mid(index));
		if (SenderThreadNum-RecipientThreadNum==0)
		{
			AddString(_T("    线程的发送方和接收方不能相同！"));
		}
	}
}
void CDiailogEditor::examLightAdjusting(CStdioFile&File, int i)
{
	CString comm[3];//存储读取到的4行数据
					//file->ReadString(m_fileComm);
	File.ReadString(comm[0]);//参数1
	File.ReadString(comm[1]);//参数2
	File.ReadString(comm[2]);//参数3
	CString a;
	a.Format(_T("%d"), i);//int转换成字符
	examEmpty(0, 2, comm, a);
}
void CDiailogEditor::examImageProcessing(CStdioFile&File, int i)
{
	CString comm[8];//存储读取到的4行数据
					//file->ReadString(m_fileComm);
	CString MiddleComm;
	for (i = 0; i < 8; i++)
	{
		comm[i] = pMainDlg->ChineseTransformation(MiddleComm, &File);
	}
	
	CString a;
	a.Format(_T("%d"), i);//int转换成字符
	if (comm[0] == "\r\nTemplateMatching")
	{
		AddString(_T("    参数1："));
		examEmpty(1, 6, comm, a);
	}
	else if (comm[0] == "\r\nCricleDetection")
	{
		AddString(_T("    参数1："));
		examEmpty(1, 7, comm, a);
	}
	else
	{
		AddString(_T("    参数1：“未定义！”"));
	}
}
void CDiailogEditor::examAdjustingWithResult(CStdioFile&File, int i)
{
	CString comm[8];//存储读取到的4行数据
					//file->ReadString(m_fileComm);
	CString MiddleComm;
	for (i = 0; i < 8; i++)
	{
		comm[i] = pMainDlg->ChineseTransformation(MiddleComm, &File);
	}

	CString a;
	a.Format(_T("%d"), i);//int转换成字符
	examEmpty(0, 7, comm, a);
}

void CDiailogEditor::examEmpty(int Min, int Max, CString comm[], CString a)
{
	int j = Min;
	CString b;
	while (j <= Max)
	{
		b.Format(_T("%d"), j + 1);//int转换成字符
		if (comm[j].GetLength() == 0)//普通指令某些参数内容全是空的
		{
			AddString(_T("    参数") + b + _T("：“空参数！”"));
		}
		else
		{
			AddString(_T("    参数") + b );
		}
		j++;
	}
}


void CDiailogEditor::OnBnClickedButton7()
{
	// TODO: 在此添加控件通知处理程序代码
	OnBnClickedButton3();//保存文档txt
}


void CDiailogEditor::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	//GetDlgItem(IDC_EDIT4)->SetFocus();设置输入焦点
	if (haveeditcreate == true)//如果之前创建了编辑框就销毁掉
	{
		distroyEdit(&m_ListCtrl, &m_Edit, e_Item, e_SubItem);//销毁单元格编辑框对象
		haveeditcreate = false;
	}
	if (haveccomboboxcreate == true)//如果之前创建了下拉列表框就销毁掉
	{
		distroyCcombobox(&m_ListCtrl, &m_comBox, e_Item, e_SubItem);
		haveccomboboxcreate = false;
	}

	if(MessageBox(_T("是否已经保存？"), _T("提示 "), MB_YESNO) == IDYES)
	//打开TXT文件。
	{
		CDialog::OnOK();
	}
}




BOOL CDiailogEditor::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	return CDialogEx::OnMouseWheel(nFlags, zDelta, pt);
}


void CDiailogEditor::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	SetFocus();
	CDialogEx::OnLButtonDown(nFlags, point);
}




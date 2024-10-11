 // DiailogEditor.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "controlSerialNetPort.h"
#include "DiailogEditor.h"
#include "afxdialogex.h"
#include "DialogPath.h"
#include <locale.h>
#include "Examination.h"
#include "controlSerialNetPortDlg.h"

// CDiailogEditor �Ի���
//��Ӷ�̬���ɱ༭���ʧȥ������Ӧ����

extern CDialogPath* pEdit;
extern CcontrolSerialNetPortDlg*pMainDlg;
extern CExamination*pExam;
CDiailogEditor*pEditor;//����ȫ�ֱ���

//ON_EN_KILLFOCUS(IDC_EDIT_CREATEID, &CDiailogEditor::OnKillfocusEdit)

//ON_CBN_KILLFOCUS(IDC_COMBOX_CREATEID, &CDiailogEditor::OnKillfocusCcomboBox)
IMPLEMENT_DYNAMIC(CDiailogEditor, CDialogEx)



void CDiailogEditor::OnKillfocusEdit()
{
	if (haveeditcreate == true)//���֮ǰ�����˱༭������ٵ�
	{
		distroyEdit(&m_ListCtrl, &m_Edit, e_Item, e_SubItem);//���ٵ�Ԫ��༭�����
		haveeditcreate = false;
	}
	if (haveccomboboxcreate == true)//���֮ǰ�����������б������ٵ�
	{
		distroyCcombobox(&m_ListCtrl, &m_comBox, e_Item, e_SubItem);
		haveccomboboxcreate = false;
	}
}

void CDiailogEditor::OnKillfocusCcomboBox()
{
	if (haveeditcreate == true)//���֮ǰ�����˱༭������ٵ�
	{
		distroyEdit(&m_ListCtrl, &m_Edit, e_Item, e_SubItem);//���ٵ�Ԫ��༭�����
		haveeditcreate = false;
	}
	if (haveccomboboxcreate == true)//���֮ǰ�����������б������ٵ�
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


// CDiailogEditor ��Ϣ�������


void CDiailogEditor::OnBnClickedButton1()//�򿪵���txt
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//�ж�Ŀǰ�Ƿ��б༭�����ѱ���
	if (MessageBox(_T("���������ݣ���ǰ���ݽ�����գ��Ƿ������"), _T("��ʾ "), MB_YESNO) == IDYES)
	{
		//ShellExecute(NULL,NULL,SW_SHOWNORMAL);
		//��ȡexe�ļ���·��
		if (haveeditcreate == true)//���֮ǰ�����˱༭������ٵ�
		{
			distroyEdit(&m_ListCtrl, &m_Edit, e_Item, e_SubItem);//���ٵ�Ԫ��༭�����
			haveeditcreate = false;
		}
		if (haveccomboboxcreate == true)//���֮ǰ�����������б������ٵ�
		{
			distroyCcombobox(&m_ListCtrl, &m_comBox, e_Item, e_SubItem);
			haveccomboboxcreate = false;
		}
		m_ListCtrl.DeleteAllItems(); // ȫ�����  
		CString path;
		GetModuleFileName(NULL, path.GetBufferSetLength(MAX_PATH + 1), MAX_PATH);
		path.ReleaseBuffer();
		int pos = path.ReverseFind('\\');
		path = path.Left(pos);
		path = path + _T("\\");
	
		CString   strFileName;
		CFileDialog   m_ldFile(TRUE);

		m_ldFile.m_ofn.lpstrFilter = _T("*.txt "); //Ҫѡ����ļ���׺
		m_ldFile.m_ofn.lpstrInitialDir = path;//Ĭ�ϵ��ļ�·��
		m_ldFile.m_ofn.lpstrDefExt = _T("txt");//Ĭ����չ��

		if (m_ldFile.DoModal() == IDOK)
		{
			strFileName = m_ldFile.GetPathName();       //������·�����ļ��� 
		}
		//ѡ���ļ�������	
		LPCTSTR pszFileName = strFileName.GetBufferSetLength(strFileName.GetLength());
		CStdioFile myFile;
		BOOL ret = myFile.Open(pszFileName, CFile::modeRead);
		CString FullName = myFile.GetFileTitle();
		int index = 0;
		index = FullName.Find('.');//��ָ��ĵ������ַ��в����Ƿ�����ַ���value,��0λ�ÿ�ʼ�飬���ص���λ��
		m_ProcessName = FullName.Left(index);

		//SetDlgItemText(IDC_EDIT5, myFile.GetFileTitle());//���ļ�����д��ҳ����
		UpdateData(FALSE);
		if (!ret)
		{
			AfxMessageBox(_T("���ļ�ʧ��"));
			return;
		}
		if (ret)//�ļ��򿪳ɹ�
		{
			CString content;//����һ���������ڽ��ն�ȡ��һ������
			int line = 0;//�ı�������txt
			int nItem;//����list
			int iSubItem;//����
			char* old_locale = _strdup(setlocale(LC_CTYPE, NULL));
			setlocale(LC_CTYPE, "chs");
			while (myFile.ReadString(content) != FALSE)//һ���ж�
			{
				iSubItem = line % 13;//ȡ����
				nItem = line / 13;//ȡ��
				if (iSubItem == 0)//�����v                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              
				{
					m_ListCtrl.InsertItem(nItem, _T(""));//InsertItem����ؼ�����һ����������,��סֻ������,��ô�������ݵĹ�������SetItemText��ʵ��
					m_ListCtrl.SetItemText(nItem, iSubItem, content);//��һ��
					UpdateData(FALSE);
					line++;
				}
				if (iSubItem == 2|| iSubItem == 3||iSubItem == 4 || iSubItem == 5|| iSubItem == 6 || iSubItem == 7||iSubItem == 8 || iSubItem == 9 || iSubItem == 10 || iSubItem == 11 || iSubItem == 12)
				{
					m_ListCtrl.SetItemText(nItem, iSubItem, content);
					UpdateData(FALSE);
					line++;
				}
				if (iSubItem == 1)//��ע��
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
			temp.Format(_T("%d"), nItem);//����ת�����ַ�

			CString str = _T("�Ѷ�ȡ����������") + temp;

			MessageBox(str, _T("��ʾ "), MB_YESNO);    //��ȡ���沢����

			//myFile.GetFileName()   //�õ��������ļ�����������չ���磺test1.txt
			//GetFileTitle()//����ļ����ƣ�������׺
			
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
	m_ListCtrl.GetClientRect(&rect); //��ȡlist�Ŀͻ���,�������ÿһ�еĿ��
	int iLength = rect.Width();
	m_ListCtrl.SetExtendedStyle(m_ListCtrl.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_ListCtrl.InsertColumn(0, _T("���"), LVCFMT_CENTER, 50);
	m_ListCtrl.InsertColumn(1, _T("��ע"), LVCFMT_CENTER, 135);
	m_ListCtrl.InsertColumn(2, _T("��������"), LVCFMT_CENTER, 120);
	m_ListCtrl.InsertColumn(3, _T("����1"), LVCFMT_CENTER, 120);
	m_ListCtrl.InsertColumn(4, _T("����2"), LVCFMT_CENTER, 120);
	m_ListCtrl.InsertColumn(5, _T("����3"), LVCFMT_CENTER, 120);
	m_ListCtrl.InsertColumn(6, _T("����4"), LVCFMT_CENTER, 120);
	m_ListCtrl.InsertColumn(7, _T("����5"), LVCFMT_CENTER, 120);
	m_ListCtrl.InsertColumn(8, _T("����6"), LVCFMT_CENTER, 120);
	m_ListCtrl.InsertColumn(9, _T("����7"), LVCFMT_CENTER, 120);
	m_ListCtrl.InsertColumn(10, _T("����8"), LVCFMT_CENTER, 120);
	m_ListCtrl.InsertColumn(11, _T("����9"), LVCFMT_CENTER, 120);
	
	//����list�߶�
	CImageList m_image;
	m_image.Create(1, 24, ILC_COLOR32, 1, 0);
	m_ListCtrl.SetImageList(&m_image, LVSIL_SMALL);
	
	m_ProcessName = _T("");//����Ĭ���ļ�����
	UpdateData(FALSE);

	haveeditcreate = false;//��ʼ����־λ����ʾ��û�д����༭��
	haveccomboboxcreate = false;//��ʼ����־λ����ʾ��û�д��������б��

	//�����б��ý��㣿
	m_ListCtrl.SetFocus();
	//ȷ��List Control���һ�пɼ�  
	m_ListCtrl.EnsureVisible(m_ListCtrl.GetItemCount(), FALSE);

	//ÿһ��ǰ����ϸ�ѡ��
	DWORD dwStyle = m_ListCtrl.GetExtendedStyle();
	dwStyle |= LVS_EX_CHECKBOXES;//������չ��ʽ
	m_ListCtrl.SetExtendedStyle(dwStyle);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


void CDiailogEditor::OnLvnItemchangedList4(NMHDR *pNMHDR, LRESULT *pResult)//ΪListCtrl�ؼ����LVN_ITEMCHANGED��Ϣ
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}


//������Ԫ��༭���� 
//pEditCtrlΪ�б����ָ�룬createditΪ�༭��ָ�����      
//ItemΪ������Ԫ�����б��е��У�SubItem��Ϊ�У�havecreatΪ���󴴽���׼

void CDiailogEditor::createEdit(NM_LISTVIEW  *pEditCtrl, CEdit *createdit, int &Item, int &SubItem, bool &havecreat)
{
	Item = pEditCtrl->iItem;//�����еĵ�Ԫ����и�ֵ�����ձ༭�����С��Ա���ڴ���
	SubItem = pEditCtrl->iSubItem;//�����еĵ�Ԫ����и�ֵ�����ձ༭�����С��Ա���ڴ���
	createdit->Create(ES_AUTOHSCROLL | WS_CHILD | ES_LEFT | ES_WANTRETURN,
		CRect(0, 0, 0, 0), this, IDC_EDIT_CREATEID);//�����༭�����,IDC_EDIT_CREATEIDΪ�ؼ�ID��3000�������¿�ͷ����
	havecreat = true;
	createdit->SetFont(this->GetFont(), FALSE);//��������,����������Ļ�������ֻ��ͻأ�ĸо�
	createdit->SetParent(&m_ListCtrl);//��list control����Ϊ������,���ɵ�Edit������ȷ��λ,���Ҳ����Ҫ
	CRect  EditRect;
	m_ListCtrl.GetSubItemRect(e_Item, e_SubItem, LVIR_LABEL, EditRect);//��ȡ��Ԫ��Ŀռ�λ����Ϣ
	EditRect.SetRect(EditRect.left + 1, EditRect.top + 1, EditRect.left + m_ListCtrl.GetColumnWidth(e_SubItem) - 1, EditRect.bottom - 1);//+1��-1�����ñ༭�����ڵ�ס�б���е�������
	CString strItem = m_ListCtrl.GetItemText(e_Item, e_SubItem);//�����Ӧ��Ԫ���ַ�
	createdit->SetWindowText(strItem);//����Ԫ���ַ���ʾ�ڱ༭����
	createdit->MoveWindow(&EditRect);//���༭��λ�÷�����Ӧ��Ԫ����
	createdit->ShowWindow(SW_SHOW);//��ʾ�༭���ڵ�Ԫ������
	createdit->SetFocus();//����Ϊ���� 
	createdit->SetSel(-1);//���ù�����ı������ֵ����
}

void CDiailogEditor::distroyEdit(CListCtrl *list, CEdit* distroyedit, int &Item, int &SubItem)
{
	CString meditdata;
	distroyedit->GetWindowTextW(meditdata);
	list->SetItemText(Item, SubItem, meditdata);//�����Ӧ��Ԫ���ַ�
	distroyedit->DestroyWindow();//���ٶ����д�����Ҫ�����٣���Ȼ�ᱨ��
}

//������Ԫ�������б����
//pEditCtrlΪ�б����ָ�룬createccomboboxΪ�����б��ָ�����
//ItemΪ������Ԫ�����б��е��У�SubItem��Ϊ�У�havecreatΪ���󴴽���׼

void CDiailogEditor::createCcombobox(NM_LISTVIEW  *pEditCtrl, CComboBox *createccomboboxobj, int &Item, int &SubItem, bool &havecreat)
{
	Item = pEditCtrl->iItem;//�����еĵ�Ԫ����и�ֵ�����ձ༭�����С��Ա���ڴ���
	SubItem = pEditCtrl->iSubItem;//�����еĵ�Ԫ����и�ֵ�����ձ༭�����С��Ա���ڴ���
	havecreat = true;
	createccomboboxobj->Create(WS_CHILD | WS_VISIBLE | CBS_DROPDOWN | CBS_OEMCONVERT, CRect(0, 0, 0, 0), this, IDC_COMBOX_CREATEID);
	createccomboboxobj->SetFont(this->GetFont(), FALSE);//��������,����������Ļ�������ֻ��ͻأ�ĸо�
	createccomboboxobj->SetParent(&m_ListCtrl);//��list control����Ϊ������,���ɵ�Ccombobox������ȷ��λ,���Ҳ����Ҫ
	CRect  EditRect;
	m_ListCtrl.GetSubItemRect(e_Item, e_SubItem, LVIR_LABEL, EditRect);//��ȡ��Ԫ��Ŀռ�λ����Ϣ
	EditRect.SetRect(EditRect.left + 1, EditRect.top + 1, EditRect.left + m_ListCtrl.GetColumnWidth(e_SubItem) - 1, EditRect.bottom - 1);//+1��-1�����ñ༭�����ڵ�ס�б���е�������
	CString strItem = m_ListCtrl.GetItemText(e_Item, e_SubItem);//�����Ӧ��Ԫ���ַ�
	createccomboboxobj->SetWindowText(strItem);//����Ԫ���ַ���ʾ�ڱ༭����
	createccomboboxobj->MoveWindow(&EditRect);//���༭��λ�÷�����Ӧ��Ԫ����
	createccomboboxobj->ShowWindow(SW_SHOW);//��ʾ�༭���ڵ�Ԫ������
}

void CDiailogEditor::distroyCcombobox(CListCtrl *list, CComboBox* distroyccomboboxobj, int &Item, int &SubItem)
{
	CString meditdata;
	distroyccomboboxobj->GetWindowTextW(meditdata);
	list->SetItemText(Item, SubItem, meditdata);//������Ӧ��Ԫ���ַ�
	distroyccomboboxobj->DestroyWindow();//���ٶ����д�����Ҫ�����٣���Ȼ�ᱨ��
}

void CDiailogEditor::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���
	//CDialogEx::OnOK();
}


void CDiailogEditor::OnEnChangeEdit6()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CDiailogEditor::OnEnKillfocusEdit6()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString str;
	m_edit.GetWindowTextW(str);
	m_ListCtrl.SetItemText(m_Row, m_Col, str);
	m_edit.ShowWindow(SW_HIDE);
}


void CDiailogEditor::OnNMDblclkList4(NMHDR *pNMHDR, LRESULT *pResult)//˫����Ӧ
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}

void CDiailogEditor::OnNMRClickList4(NMHDR *pNMHDR, LRESULT *pResult)//�һ������Ӧ�¼�
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
	CRect rc;
	CString strTemp;
	NM_LISTVIEW *pNMListView = (NM_LISTVIEW *)pNMHDR;////NM_LISTVIEW�ṹ���ýṹ���ڴ洢�б���ͼ��֪ͨ��Ϣ���й���Ϣ���󲿷��б���ͼ��֪ͨ��Ϣ���ḽ��ָ��ýṹ��ָ�룮
	m_Row = pNMListView->iItem; //�����
	m_Col = pNMListView->iSubItem;//�����
	int i = m_ListCtrl.GetSelectionMark();//���ѡ���е��б�
	CString s2 = m_ListCtrl.GetItemText(i, 2); //i���У�j���С�m_list�Ǹ�list control ����
	CString s3 = m_ListCtrl.GetItemText(i, 3); //i���У�j���С�m_list�Ǹ�list control ����
	CString s4 = m_ListCtrl.GetItemText(i, 4); //i���У�j���С�m_list�Ǹ�list control ����
	CString s5 = m_ListCtrl.GetItemText(i, 5); //i���У�j���С�m_list�Ǹ�list control ����
	CString s6 = m_ListCtrl.GetItemText(i, 6); //i���У�j���С�m_list�Ǹ�list control ����
	CString s7 = m_ListCtrl.GetItemText(i, 7); //i���У�j���С�m_list�Ǹ�list control ����
	CString s8 = m_ListCtrl.GetItemText(i, 8); //i���У�j���С�m_list�Ǹ�list control ����
	CString s9 = m_ListCtrl.GetItemText(i, 9); //i���У�j���С�m_list�Ǹ�list control ����
											   //CString s10 = m_ListCtrl.GetItemText(i, 10); //i���У�j���С�m_list�Ǹ�list control ����


	if (pNMListView->iItem == -1)//������ǹ�������δ�½�������
	{
		if (haveeditcreate == true)//���֮ǰ�����˱༭������ٵ�
		{
			distroyEdit(&m_ListCtrl, &m_Edit, e_Item, e_SubItem);//���ٵ�Ԫ��༭�����
			haveeditcreate = false;
		}
		if (haveccomboboxcreate == true)//���֮ǰ�����������б������ٵ�
		{
			distroyCcombobox(&m_ListCtrl, &m_comBox, e_Item, e_SubItem);
			haveccomboboxcreate = false;
		}//�½�һ�У���ż�1
		m_Row = m_ListCtrl.GetItemCount();
		strTemp.Format(_T("%d"), m_Row + 1);
		m_ListCtrl.InsertItem(m_Row, strTemp);
		m_ListCtrl.SetItemState(m_Row, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);
		m_ListCtrl.EnsureVisible(m_Row, FALSE);
		//m_Col = 1;
	}
	if (pNMListView->iSubItem == 0)//����������
	{
		//����Ϊ
	}
	if (pNMListView->iSubItem == 1)//����Ǳ�ע��
	{
		if (haveccomboboxcreate == true)//���֮ǰ�����������б������ٵ�
		{
			distroyCcombobox(&m_ListCtrl, &m_comBox, e_Item, e_SubItem);
			haveccomboboxcreate = false;
		}
		if (haveeditcreate == true)//���֮ǰ�����˱༭��
		{
			if (!(e_Item == pNMListView->iItem && e_SubItem == pNMListView->iSubItem))//������еĵ�Ԫ����֮ǰ�����õģ��༭����������Ԫ��
			{
				distroyEdit(&m_ListCtrl, &m_Edit, e_Item, e_SubItem);//����
				haveeditcreate = false;
				createEdit(pNMListView, &m_Edit, e_Item, e_SubItem, haveeditcreate);//�ڵ����λ�ô����µı༭��
			}
			else//���еĵ�Ԫ����֮ǰ�����õ�
			{
				m_Edit.SetFocus();//����Ϊ���㣨���
			}
		}
		else//Ŀǰʲô��û�д���
		{
			e_Item = pNMListView->iItem;//�����еĵ�Ԫ����и�ֵ�����ձ༭�����С��Ա���ڴ���
			e_SubItem = pNMListView->iSubItem;//�����еĵ�Ԫ����и�ֵ�����ձ༭�����С��Ա���ڴ���
			createEdit(pNMListView, &m_Edit, e_Item, e_SubItem, haveeditcreate);//�ڸ�λ�ô����༭��
		}
	}
	if (pNMListView->iSubItem == 2 || pNMListView->iSubItem == 3 || pNMListView->iSubItem == 4 || pNMListView->iSubItem == 5 || pNMListView->iSubItem == 6 || pNMListView->iSubItem == 7 || pNMListView->iSubItem == 8 || pNMListView->iSubItem == 9 || pNMListView->iSubItem == 10 || pNMListView->iSubItem == 11)//�����23456789ѡ���Ҫ�ڸõ�Ԫ�������б��
	{
		if (haveeditcreate == true)//���֮ǰ�����˱༭������ٵ�
		{
			distroyEdit(&m_ListCtrl, &m_Edit, e_Item, e_SubItem);
			haveeditcreate = false;

		}
		if (haveccomboboxcreate == true)//���֮ǰ�����������б�(��������Ԫ������Լ���
		{
			if (!(e_Item == pNMListView->iItem && e_SubItem == pNMListView->iSubItem))//������еĵ�Ԫ����֮ǰ�����õģ�������Ԫ���������б��
			{
				distroyCcombobox(&m_ListCtrl, &m_comBox, e_Item, e_SubItem);//���������б��
				haveccomboboxcreate = false;
				UpdateData(TRUE); //����listbox������
				createCcombobox(pNMListView, &m_comBox, e_Item, e_SubItem, haveccomboboxcreate);//�ڸĵ�Ԫ�񴴽������б��
				UpdateData(TRUE);
				int i = m_ListCtrl.GetSelectionMark();//���ѡ���е��б�
				CString s2 = m_ListCtrl.GetItemText(i, 2); //i���У�j���С�m_list�Ǹ�list control ����
				CString s3 = m_ListCtrl.GetItemText(i, 3); //i���У�j���С�m_list�Ǹ�list control ����
				CString s4 = m_ListCtrl.GetItemText(i, 4); //i���У�j���С�m_list�Ǹ�list control ����
				CString s5 = m_ListCtrl.GetItemText(i, 5); //i���У�j���С�m_list�Ǹ�list control ����
				CString s6 = m_ListCtrl.GetItemText(i, 6); //i���У�j���С�m_list�Ǹ�list control ����
				CString s7 = m_ListCtrl.GetItemText(i, 7); //i���У�j���С�m_list�Ǹ�list control ����
				CString s8 = m_ListCtrl.GetItemText(i, 8); //i���У�j���С�m_list�Ǹ�list control ����
				CString s9 = m_ListCtrl.GetItemText(i, 9); //i���У�j���С�m_list�Ǹ�list control ����
														   //CString s10 = m_ListCtrl.GetItemText(i, 10); //i���У�j���С�m_list�Ǹ�list control ����
				SetListCell(pNMListView);
			}
			else//���еĵ�Ԫ����֮ǰ�����õ�
			{
				m_comBox.SetFocus();//����Ϊ����
			}
		}
		else//û�д����κα༭��/�����б�������
		{
			e_Item = pNMListView->iItem;//�����еĵ�Ԫ����и�ֵ�����ձ༭�����С��Ա���ڴ���
			e_SubItem = pNMListView->iSubItem;//�����еĵ�Ԫ����и�ֵ�����ձ༭�����С��Ա���ڴ���
			createCcombobox(pNMListView, &m_comBox, e_Item, e_SubItem, haveccomboboxcreate);//�����༭��
			SetListCell(pNMListView);
		}
	}
	*pResult = 0;
}

void CDiailogEditor::OnNMClickList4(NMHDR *pNMHDR, LRESULT *pResult)//������Ӧ����
{
	UpdateData(TRUE);
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	CRect rc;
	CString strTemp;
	NM_LISTVIEW *pNMListView = (NM_LISTVIEW *)pNMHDR;////NM_LISTVIEW�ṹ���ýṹ���ڴ洢�б���ͼ��֪ͨ��Ϣ���й���Ϣ���󲿷��б���ͼ��֪ͨ��Ϣ���ḽ��ָ��ýṹ��ָ�룮
	m_Row = pNMListView->iItem; //�����
	m_Col = pNMListView->iSubItem;//�����
	int i = m_ListCtrl.GetSelectionMark();//���ѡ���е��б�
	CString s2 = m_ListCtrl.GetItemText(i, 2); //i���У�j���С�m_list�Ǹ�list control ����
	CString s3 = m_ListCtrl.GetItemText(i, 3); //i���У�j���С�m_list�Ǹ�list control ����
	CString s4 = m_ListCtrl.GetItemText(i, 4); //i���У�j���С�m_list�Ǹ�list control ����
	CString s5 = m_ListCtrl.GetItemText(i, 5); //i���У�j���С�m_list�Ǹ�list control ����
	CString s6 = m_ListCtrl.GetItemText(i, 6); //i���У�j���С�m_list�Ǹ�list control ����
	CString s7 = m_ListCtrl.GetItemText(i, 7); //i���У�j���С�m_list�Ǹ�list control ����
	CString s8 = m_ListCtrl.GetItemText(i, 8); //i���У�j���С�m_list�Ǹ�list control ����
	CString s9 = m_ListCtrl.GetItemText(i, 9); //i���У�j���С�m_list�Ǹ�list control ����
	CString s10 = m_ListCtrl.GetItemText(i, 10); //i���У�j���С�m_list�Ǹ�list control ����


	if (pNMListView->iItem == -1 || pNMListView->iSubItem == 0)//������ǹ�������δ�½�������
	{
		//����Ϊ
	}
	if (pNMListView->iSubItem == 1 || pNMListView->iSubItem == 2 || pNMListView->iSubItem == 3 || pNMListView->iSubItem == 4 || pNMListView->iSubItem == 5 || pNMListView->iSubItem == 6 || pNMListView->iSubItem == 7 || pNMListView->iSubItem == 8 || pNMListView->iSubItem == 9 || pNMListView->iSubItem == 10 || pNMListView->iSubItem == 11)//�����23456789ѡ���Ҫ�ڸõ�Ԫ�������б��)//����Ǳ�ע��
	{
		if (haveccomboboxcreate == true)//���֮ǰ�����������б������ٵ�
		{
			distroyCcombobox(&m_ListCtrl, &m_comBox, e_Item, e_SubItem);
			haveccomboboxcreate = false;
		}
		if (haveeditcreate == true)//���֮ǰ�����˱༭��
		{
			if (!(e_Item == pNMListView->iItem && e_SubItem == pNMListView->iSubItem))//������еĵ�Ԫ����֮ǰ�����õģ��༭����������Ԫ��
			{
				distroyEdit(&m_ListCtrl, &m_Edit, e_Item, e_SubItem);//����
				haveeditcreate = false;
				//createEdit(pNMListView, &m_Edit, e_Item, e_SubItem, haveeditcreate);//�ڵ����λ�ô����µı༭��
				m_Edit.SetFocus();//����Ϊ���㣨���
			}
			else//���еĵ�Ԫ����֮ǰ�����õ�
			{
				m_Edit.SetFocus();//����Ϊ���㣨���
			}
		}
		else//Ŀǰʲô��û�д���
		{
			e_Item = pNMListView->iItem;//�����еĵ�Ԫ����и�ֵ�����ձ༭�����С��Ա���ڴ���
			e_SubItem = pNMListView->iSubItem;//�����еĵ�Ԫ����и�ֵ�����ձ༭�����С��Ա���ڴ���
			createEdit(pNMListView, &m_Edit, e_Item, e_SubItem, haveeditcreate);//�ڸ�λ�ô����༭��
		}
	}

	UpdateData(FALSE);
	*pResult = 0;
}

void CDiailogEditor::SetListCell(NM_LISTVIEW* pNMListView)//���õ�Ԫ������
{
	UpdateData(TRUE);
	m_Row = pNMListView->iItem; //�����
	m_Col = pNMListView->iSubItem;//�����
	int i = m_ListCtrl.GetSelectionMark();//���ѡ���е��б�
	CString s2 = m_ListCtrl.GetItemText(i, 2); //i���У�j���С�m_list�Ǹ�list control ����
	CString s3 = m_ListCtrl.GetItemText(i, 3); //i���У�j���С�m_list�Ǹ�list control ����
	CString s4 = m_ListCtrl.GetItemText(i, 4); //i���У�j���С�m_list�Ǹ�list control ����
	CString s5 = m_ListCtrl.GetItemText(i, 5); //i���У�j���С�m_list�Ǹ�list control ����
	CString s6 = m_ListCtrl.GetItemText(i, 6); //i���У�j���С�m_list�Ǹ�list control ����
	CString s7 = m_ListCtrl.GetItemText(i, 7); //i���У�j���С�m_list�Ǹ�list control ����
	CString s8 = m_ListCtrl.GetItemText(i, 8); //i���У�j���С�m_list�Ǹ�list control ����
	CString s9 = m_ListCtrl.GetItemText(i, 9); //i���У�j���С�m_list�Ǹ�list control ����
	//CString s10 = m_ListCtrl.GetItemText(i, 10); //i���У�j���С�m_list�Ǹ�list control ����
	if (pNMListView->iSubItem == 2)//-----------------------------7��ָ��
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
		m_comBox.SetCurSel(0);//Ĭ����ʾ��һ��

	}
	if (pNMListView->iSubItem == 3)
	{
		UpdateData(TRUE);
		if (s2 == "Common:")//--------------------------------8����ָ��
		{
			m_comBox.InsertString(0, L"IO");
			m_comBox.InsertString(1, L"AxisMove");
			m_comBox.InsertString(2, L"ForceControlAxisMove");//�����ᶯ
			m_comBox.InsertString(3, L"AxisSetTargetSpeed");//����Ŀ���ٶ�
			m_comBox.InsertString(4, L"AxisSetHomePosition");//����ԭ��
			m_comBox.InsertString(5, L"AxisGoHomePosition");//��ԭ��
			m_comBox.InsertString(6, L"AxisGoPositiveLimit");//�ظ���λ
			m_comBox.InsertString(7, L"AxisGoNegativeLimit");//������λ
			m_comBox.InsertString(8, L"AxisSMVR");//�����趨
			m_comBox.InsertString(9, L"ChangeMode");//�л�ģʽ���������
			m_comBox.SetCurSel(0);//Ĭ����ʾ��һ��
		}
		if (s2 == "Robot:")//----------------------------------2����ָ��
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
		if (s2 == "Inquiry:")//------------------------------4����ָ��
		{
			m_comBox.InsertString(0, L"Limit?");//��λ��ѯ
			m_comBox.InsertString(1, L"RelativePosition?");//���λ�ò�ѯ
			m_comBox.InsertString(2, L"AbsolutePosition?");//����λ�ò�ѯ
			m_comBox.InsertString(3, L"IO?");//��ѯIO״̬
			m_comBox.SetCurSel(0);
		}

		if (s2 == "LightAdjusting:")
		{
			m_comBox.InsertString(0, L"Channel=1");
			m_comBox.InsertString(1, L"Channel=2");
			m_comBox.SetCurSel(0);
		}
		if (s2 == "ImageProcessing:")//--------------------2����ָ��
		{
			m_comBox.InsertString(0, L"TemplateMatching");
			m_comBox.InsertString(1, L"CricleDetection");
			m_comBox.SetCurSel(0);
		}

		if (s2 == "OmissionDetection:")//--------------------2����ָ��
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
		int i = m_ListCtrl.GetSelectionMark();//���ѡ���е��б�
		CString s2 = m_ListCtrl.GetItemText(i, 2); //i���У�j���С�m_list�Ǹ�list control ����
		CString s3 = m_ListCtrl.GetItemText(i, 3); //i���У�j���С�m_list�Ǹ�list control ����
		CString s4 = m_ListCtrl.GetItemText(i, 4); //i���У�j���С�m_list�Ǹ�list control ����
		CString s5 = m_ListCtrl.GetItemText(i, 5); //i���У�j���С�m_list�Ǹ�list control ����
		CString s6 = m_ListCtrl.GetItemText(i, 6); //i���У�j���С�m_list�Ǹ�list control ����
		CString s7 = m_ListCtrl.GetItemText(i, 7); //i���У�j���С�m_list�Ǹ�list control ����
		CString s8 = m_ListCtrl.GetItemText(i, 8); //i���У�j���С�m_list�Ǹ�list control ����
		CString s9 = m_ListCtrl.GetItemText(i, 9); //i���У�j���С�m_list�Ǹ�list control ����
		//CString s10 = m_ListCtrl.GetItemText(i, 10); //i���У�j���С�m_list�Ǹ�list control ����
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
			if (haveccomboboxcreate == true)//���֮ǰ�����������б������ٵ�
			{
				distroyCcombobox(&m_ListCtrl, &m_comBox, e_Item, e_SubItem);
				haveccomboboxcreate = false;
			}
			if (haveeditcreate == true)//���֮ǰ�����˱༭��
			{
				if (!(e_Item == pNMListView->iItem && e_SubItem == pNMListView->iSubItem))//������еĵ�Ԫ����֮ǰ�����õģ��༭����������Ԫ��
				{
					distroyEdit(&m_ListCtrl, &m_Edit, e_Item, e_SubItem);//����
					haveeditcreate = false;
					createEdit(pNMListView, &m_Edit, e_Item, e_SubItem, haveeditcreate);//�ڵ����λ�ô����µı༭��
				}
				else//���еĵ�Ԫ����֮ǰ�����õ�
				{
					m_Edit.SetFocus();//����Ϊ���㣨���
				}
			}
			if (haveccomboboxcreate == false && haveeditcreate == false)//Ŀǰʲô��û�д���
			{
				e_Item = pNMListView->iItem;//�����еĵ�Ԫ����и�ֵ�����ձ༭�����С��Ա���ڴ���
				e_SubItem = pNMListView->iSubItem;//�����еĵ�Ԫ����и�ֵ�����ձ༭�����С��Ա���ڴ���
				createEdit(pNMListView, &m_Edit, e_Item, e_SubItem, haveeditcreate);//�ڸ�λ�ô����༭��				
				if (NULL == m_path)  // ���ָ�����m_create��ֵΪNULL����Ի���δ��������Ҫ��̬����   
				{
					m_path = new CDialogPath();   //��̬��������
					m_path->SetAsFolderSelector();
					m_path->Create(IDD_DIALOG_Path, this);
				}
				m_path->ShowWindow(SW_SHOW);  // ��ʾ��ģ̬�Ի���   
				m_path->SetWindowPos(NULL, 900, 300, 0, 0, SWP_NOSIZE);
				//SWP_NOSIZE���ֵ�ǰ�Ի����С����4��5����cx��cy�ᱻ���ԣ����÷�ģ̬�Ի����λ��

			}
		}

		if (s3 == "InquiryRobot")//----------------------2��������
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
			int i = m_ListCtrl.GetSelectionMark();//���ѡ���е��б�
			CString s2 = m_ListCtrl.GetItemText(i, 2); //i���У�j���С�m_list�Ǹ�list control ����
			CString s3 = m_ListCtrl.GetItemText(i, 3); //i���У�j���С�m_list�Ǹ�list control ����
			CString s4 = m_ListCtrl.GetItemText(i, 4); //i���У�j���С�m_list�Ǹ�list control ����
			CString s5 = m_ListCtrl.GetItemText(i, 5); //i���У�j���С�m_list�Ǹ�list control ����
			CString s6 = m_ListCtrl.GetItemText(i, 6); //i���У�j���С�m_list�Ǹ�list control ����
			CString s7 = m_ListCtrl.GetItemText(i, 7); //i���У�j���С�m_list�Ǹ�list control ����
			CString s8 = m_ListCtrl.GetItemText(i, 8); //i���У�j���С�m_list�Ǹ�list control ����
			CString s9 = m_ListCtrl.GetItemText(i, 9); //i���У�j���С�m_list�Ǹ�list control ����
			//CString s10 = m_ListCtrl.GetItemText(i, 10); //i���У�j���С�m_list�Ǹ�list control ����
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
				m_comBox.InsertString(0, L"Status=Busy");//��æ
				m_comBox.InsertString(1, L"Status=Waiting");//�Ⱥ�
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
			{//·��ѡ�񵯳�һ����ģ̬�Ի���ѡȡ·��������ñ༭��
				if (haveccomboboxcreate == true)//���֮ǰ�����������б������ٵ�
				{
					distroyCcombobox(&m_ListCtrl, &m_comBox, e_Item, e_SubItem);
					haveccomboboxcreate = false;
				}
				if (haveeditcreate == true)//���֮ǰ�����˱༭��
				{
					if (!(e_Item == pNMListView->iItem && e_SubItem == pNMListView->iSubItem))//������еĵ�Ԫ����֮ǰ�����õģ��༭����������Ԫ��
					{
						distroyEdit(&m_ListCtrl, &m_Edit, e_Item, e_SubItem);//����
						haveeditcreate = false;
						createEdit(pNMListView, &m_Edit, e_Item, e_SubItem, haveeditcreate);//�ڵ����λ�ô����µı༭��
					}
					else//���еĵ�Ԫ����֮ǰ�����õ�
					{
						m_Edit.SetFocus();//����Ϊ���㣨���
					}
				}
				if (haveccomboboxcreate == false && haveeditcreate == false)//Ŀǰʲô��û�д���
				{
					e_Item = pNMListView->iItem;//�����еĵ�Ԫ����и�ֵ�����ձ༭�����С��Ա���ڴ���
					e_SubItem = pNMListView->iSubItem;//�����еĵ�Ԫ����и�ֵ�����ձ༭�����С��Ա���ڴ���
					createEdit(pNMListView, &m_Edit, e_Item, e_SubItem, haveeditcreate);//�ڸ�λ�ô����༭��				
					if (NULL == m_path)  // ���ָ�����m_create��ֵΪNULL����Ի���δ��������Ҫ��̬����   
					{
						m_path = new CDialogPath();   //��̬��������
						m_path->Create(IDD_DIALOG_Path, this);
					}
					m_path->ShowWindow(SW_SHOW);  // ��ʾ��ģ̬�Ի���   
					m_path->SetWindowPos(NULL, 900, 300, 0, 0, SWP_NOSIZE);
					//SWP_NOSIZE���ֵ�ǰ�Ի����С����4��5����cx��cy�ᱻ���ԣ����÷�ģ̬�Ի����λ��

				}

			}
		}
		if (pNMListView->iSubItem == 6)
		{
			UpdateData(TRUE);
			int i = m_ListCtrl.GetSelectionMark();//���ѡ���е��б�
			CString s2 = m_ListCtrl.GetItemText(i, 2); //i���У�j���С�m_list�Ǹ�list control ����
			CString s3 = m_ListCtrl.GetItemText(i, 3); //i���У�j���С�m_list�Ǹ�list control ����
			CString s4 = m_ListCtrl.GetItemText(i, 4); //i���У�j���С�m_list�Ǹ�list control ����
			CString s5 = m_ListCtrl.GetItemText(i, 5); //i���У�j���С�m_list�Ǹ�list control ����
			CString s6 = m_ListCtrl.GetItemText(i, 6); //i���У�j���С�m_list�Ǹ�list control ����
			CString s7 = m_ListCtrl.GetItemText(i, 7); //i���У�j���С�m_list�Ǹ�list control ����
			CString s8 = m_ListCtrl.GetItemText(i, 8); //i���У�j���С�m_list�Ǹ�list control ����
			CString s9 = m_ListCtrl.GetItemText(i, 9); //i���У�j���С�m_list�Ǹ�list control ����
		//	CString s10 = m_ListCtrl.GetItemText(i, 10); //i���У�j���С�m_list�Ǹ�list control ����

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
				m_comBox.InsertString(0, L"Value=0");//0����������˶�
				m_comBox.InsertString(1, L"Value=1");//1�����������˶�
				m_comBox.InsertString(2, L"Value=2");//2���ջ�����˶�
				m_comBox.InsertString(3, L"Value=3");//3���ջ������˶�
				m_comBox.InsertString(4, L"Value=4");//4�������˶�
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
			int i = m_ListCtrl.GetSelectionMark();//���ѡ���е��б�
			CString s2 = m_ListCtrl.GetItemText(i, 2); //i���У�j���С�m_list�Ǹ�list control ����
			CString s3 = m_ListCtrl.GetItemText(i, 3); //i���У�j���С�m_list�Ǹ�list control ����
			CString s4 = m_ListCtrl.GetItemText(i, 4); //i���У�j���С�m_list�Ǹ�list control ����
			CString s5 = m_ListCtrl.GetItemText(i, 5); //i���У�j���С�m_list�Ǹ�list control ����
			CString s6 = m_ListCtrl.GetItemText(i, 6); //i���У�j���С�m_list�Ǹ�list control ����
			CString s7 = m_ListCtrl.GetItemText(i, 7); //i���У�j���С�m_list�Ǹ�list control ����
			CString s8 = m_ListCtrl.GetItemText(i, 8); //i���У�j���С�m_list�Ǹ�list control ����
			CString s9 = m_ListCtrl.GetItemText(i, 9); //i���У�j���С�m_list�Ǹ�list control ����
			//CString s10 = m_ListCtrl.GetItemText(i, 10); //i���У�j���С�m_list�Ǹ�list control ����
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
			int i = m_ListCtrl.GetSelectionMark();//���ѡ���е��б�
			CString s2 = m_ListCtrl.GetItemText(i, 2); //i���У�j���С�m_list�Ǹ�list control ����
			CString s3 = m_ListCtrl.GetItemText(i, 3); //i���У�j���С�m_list�Ǹ�list control ����
			CString s4 = m_ListCtrl.GetItemText(i, 4); //i���У�j���С�m_list�Ǹ�list control ����
			CString s5 = m_ListCtrl.GetItemText(i, 5); //i���У�j���С�m_list�Ǹ�list control ����
			CString s6 = m_ListCtrl.GetItemText(i, 6); //i���У�j���С�m_list�Ǹ�list control ����
			CString s7 = m_ListCtrl.GetItemText(i, 7); //i���У�j���С�m_list�Ǹ�list control ����
			CString s9 = m_ListCtrl.GetItemText(i, 9); //i���У�j���С�m_list�Ǹ�list control ����
			//CString s10 = m_ListCtrl.GetItemText(i, 10); //i���У�j���С�m_list�Ǹ�list control ����
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
			int i = m_ListCtrl.GetSelectionMark();//���ѡ���е��б�
			CString s2 = m_ListCtrl.GetItemText(i, 2); //i���У�j���С�m_list�Ǹ�list control ����
			CString s3 = m_ListCtrl.GetItemText(i, 3); //i���У�j���С�m_list�Ǹ�list control ����
			CString s4 = m_ListCtrl.GetItemText(i, 4); //i���У�j���С�m_list�Ǹ�list control ����
			CString s5 = m_ListCtrl.GetItemText(i, 5); //i���У�j���С�m_list�Ǹ�list control ����
			CString s6 = m_ListCtrl.GetItemText(i, 6); //i���У�j���С�m_list�Ǹ�list control ����
			CString s7 = m_ListCtrl.GetItemText(i, 7); //i���У�j���С�m_list�Ǹ�list control ����
			CString s8 = m_ListCtrl.GetItemText(i, 8); //i���У�j���С�m_list�Ǹ�list control ����
			CString s9 = m_ListCtrl.GetItemText(i, 9); //i���У�j���С�m_list�Ǹ�list control ����
			//CString s10 = m_ListCtrl.GetItemText(i, 10); //i���У�j���С�m_list�Ǹ�list control ����
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
			int i = m_ListCtrl.GetSelectionMark();//���ѡ���е��б�
			CString s2 = m_ListCtrl.GetItemText(i, 2); //i���У�j���С�m_list�Ǹ�list control ����
			CString s3 = m_ListCtrl.GetItemText(i, 3); //i���У�j���С�m_list�Ǹ�list control ����
			CString s4 = m_ListCtrl.GetItemText(i, 4); //i���У�j���С�m_list�Ǹ�list control ����
			CString s5 = m_ListCtrl.GetItemText(i, 5); //i���У�j���С�m_list�Ǹ�list control ����
			CString s6 = m_ListCtrl.GetItemText(i, 6); //i���У�j���С�m_list�Ǹ�list control ����
			CString s7 = m_ListCtrl.GetItemText(i, 7); //i���У�j���С�m_list�Ǹ�list control ����
			CString s8 = m_ListCtrl.GetItemText(i, 8); //i���У�j���С�m_list�Ǹ�list control ����
			CString s9 = m_ListCtrl.GetItemText(i, 9); //i���У�j���С�m_list�Ǹ�list control ����
			CString s10 = m_ListCtrl.GetItemText(i, 10); //i���У�j���С�m_list�Ǹ�list control ����
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
			int i = m_ListCtrl.GetSelectionMark();//���ѡ���е��б�
			CString s2 = m_ListCtrl.GetItemText(i, 2); //i���У�j���С�m_list�Ǹ�list control ����
			CString s3 = m_ListCtrl.GetItemText(i, 3); //i���У�j���С�m_list�Ǹ�list control ����
			CString s4 = m_ListCtrl.GetItemText(i, 4); //i���У�j���С�m_list�Ǹ�list control ����
			CString s5 = m_ListCtrl.GetItemText(i, 5); //i���У�j���С�m_list�Ǹ�list control ����
			CString s6 = m_ListCtrl.GetItemText(i, 6); //i���У�j���С�m_list�Ǹ�list control ����
			CString s7 = m_ListCtrl.GetItemText(i, 7); //i���У�j���С�m_list�Ǹ�list control ����
			CString s8 = m_ListCtrl.GetItemText(i, 8); //i���У�j���С�m_list�Ǹ�list control ����
			CString s9 = m_ListCtrl.GetItemText(i, 9); //i���У�j���С�m_list�Ǹ�list control ����
			CString s10 = m_ListCtrl.GetItemText(i, 10); //i���У�j���С�m_list�Ǹ�list control ����
			CString s11 = m_ListCtrl.GetItemText(i, 11); //i���У�j���С�m_list�Ǹ�list control ����

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
		m_comBox.ShowDropDown();//�Զ�����
	
}

void CDiailogEditor::OnPageup()//�����ƶ�һ��
{
	UpdateData(TRUE);

	if (haveeditcreate == true)//���֮ǰ�����˱༭������ٵ�
	{
		distroyEdit(&m_ListCtrl, &m_Edit, e_Item, e_SubItem);//���ٵ�Ԫ��༭�����
		haveeditcreate = false;
	}
	if (haveccomboboxcreate == true)//���֮ǰ�����������б������ٵ�
	{
		distroyCcombobox(&m_ListCtrl, &m_comBox, e_Item, e_SubItem);
		haveccomboboxcreate = false;
	}

	int nIdx = m_ListCtrl.GetSelectionMark();//��ȡ��ǰ�к�

	if (nIdx == 0)//�ж��Ƿ��ڵ�һ��
	{
		return;//����Ϊ
	}

	else//�ڷǵ�һ�е�ʱ��
	{// ��ȡ����   
		CString temp1[12];
		int i;
		for (i = 1; i < 13; i++)
			temp1[i - 1] = m_ListCtrl.GetItemText(nIdx, i);//���������ݴ�����

		CString temp2[12];
		int j;
		for (j = 1; j < 13; j++)
			temp2[j- 1] = m_ListCtrl.GetItemText(nIdx-1, j);//������һ�����ݴ�����
		// ɾ��   
		//m_ListCtrl.DeleteItem(nIdx);//ɾ������
		//m_ListCtrl.DeleteItem(nIdx-1);//ɾ����һ��
		// ��nItem-1λ�ô�����   
		for (i = 1; i < 13; i++)
			m_ListCtrl.SetItemText(nIdx - 1, i, temp1[i - 1]);//���˵�һ��������ⶼ�ƶ�
		//��nItemλ�ô�����
		for (j = 1; j < 13; j++)
			m_ListCtrl.SetItemText(nIdx, j, temp2[j - 1]);
		m_ListCtrl.SetItemState(nIdx-1, LVIS_FOCUSED | LVIS_SELECTED, LVIS_FOCUSED | LVIS_SELECTED);   //g����
		m_ListCtrl.SetSelectionMark(nIdx-1);//ѡ��		
	}
}

void CDiailogEditor::OnPagedown()//�����ƶ�һ��
{
	int nIdx = m_ListCtrl.GetSelectionMark();//��õ�ǰ�к�

	if (haveeditcreate == true)//���֮ǰ�����˱༭������ٵ�
	{
		distroyEdit(&m_ListCtrl, &m_Edit, e_Item, e_SubItem);//���ٵ�Ԫ��༭�����
		haveeditcreate = false;
	}
	if (haveccomboboxcreate == true)//���֮ǰ�����������б������ٵ�
	{
		distroyCcombobox(&m_ListCtrl, &m_comBox, e_Item, e_SubItem);
		haveccomboboxcreate = false;
	}

	if (nIdx == m_ListCtrl.GetItemCount() - 1)//�ж��Ƿ�λ�����һ��
	{
		return;//����Ϊ
	}
	else
	{
	// ��ȡ����   
		CString temp1[12];
		int i;
		for (i = 1; i<13; i++)
			temp1[i-1] = m_ListCtrl.GetItemText(nIdx, i);//���������ݴ洢
		CString temp2[12];
		int j;
		for (j= 1; j<13; j++)
			temp2[j - 1] = m_ListCtrl.GetItemText(nIdx+1, j);//����һ�����ݴ洢	
	// ɾ��   
	//m_ListCtrl.DeleteItem(nIdx);
	// ��nItem+1λ�ô�����   ���������ݣ�
		for (i = 1; i<13; i++)
			m_ListCtrl.SetItemText(nIdx + 1, i, temp1[i-1]);
		for (j = 1; j<13; j++)
			m_ListCtrl.SetItemText(nIdx, j, temp2[j - 1]);
	//������ʾ   
		m_ListCtrl.SetItemState(nIdx +1, LVIS_FOCUSED | LVIS_SELECTED, LVIS_FOCUSED | LVIS_SELECTED);   //g����
		m_ListCtrl.SetSelectionMark(nIdx + 1);//ѡ��
	}
}

void CDiailogEditor::OnBnClickedButton8()//����
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDiailogEditor::OnPageup();
}
void CDiailogEditor::OnBnClickedButton9()//����
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDiailogEditor::OnPagedown(); 
}

void CDiailogEditor::OnNMCustomdrawList4(NMHDR *pNMHDR, LRESULT *pResult)//��������listcontrol����ɫ
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
		//��ż�ж�
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
		//����ѡ�������ɫ
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
			//���ѡ��״̬�����������Ļ������ǻ���ʾ����ɫ�ĸ�����
			BOOL b = m_ListCtrl.SetItemState(pLVCD->nmcd.dwItemSpec, 0, LVIS_SELECTED);
			pLVCD->clrText = crText;
			pLVCD->clrTextBk = crBk;
			*pResult = CDRF_NEWFONT;
			return;
		}
		*pResult = CDRF_NEWFONT;
	}
}
void CDiailogEditor::OnBnClickedButton13()//�����ļ�����
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (haveeditcreate == true)//���֮ǰ�����˱༭������ٵ�
	{
		distroyEdit(&m_ListCtrl, &m_Edit, e_Item, e_SubItem);//���ٵ�Ԫ��༭�����
		haveeditcreate = false;
	}
	if (haveccomboboxcreate == true)//���֮ǰ�����������б������ٵ�
	{
		distroyCcombobox(&m_ListCtrl, &m_comBox, e_Item, e_SubItem);
		haveccomboboxcreate = false;
	}

	UpdateData(TRUE);
	CString strTemp;
	m_Row = m_ListCtrl.GetItemCount();//��ǰ������
	int nIdx = m_ListCtrl.GetSelectionMark();//���Ŀǰ��������к�
	CString content;//����һ���������ڽ��ն�ȡ��һ������
	int line = 0;//�����ı�������txt
	int nItem;//��������list
	int iSubItem;//���������
				 //�½�һ�пհ����ڵ�ǰ�е���һ��

				 //strTemp.Format(_T("%d"), nIdx + 2);
				 //m_ListCtrl.InsertItem(nIdx + nItem, strTemp);

	if (MessageBox(_T("�������������λ�ò���һ���ı�����"), _T("��ʾ "), MB_YESNO) == IDYES)
	{
		//ShellExecute(NULL,NULL,SW_SHOWNORMAL);
		//��ȡexe�ļ���·��

		//m_ListCtrl.DeleteAllItems(); // ȫ�����  
		CString path;
		GetModuleFileName(NULL, path.GetBufferSetLength(MAX_PATH + 1), MAX_PATH);
		path.ReleaseBuffer();
		int pos = path.ReverseFind('\\');
		path = path.Left(pos);
		path = path + _T("\\");

		CString   strFileName;
		CFileDialog   m_ldFile(TRUE);

		m_ldFile.m_ofn.lpstrFilter = _T("*.txt "); //Ҫѡ����ļ���׺
		m_ldFile.m_ofn.lpstrInitialDir = path;//Ĭ�ϵ��ļ�·��
		m_ldFile.m_ofn.lpstrDefExt = _T("txt");//Ĭ����չ��

		if (m_ldFile.DoModal() == IDOK)
		{
			strFileName = m_ldFile.GetPathName();       //������·�����ļ��� 
		}
		//ѡ���ļ�������	
		LPCTSTR pszFileName = strFileName.GetBufferSetLength(strFileName.GetLength());
		CStdioFile myFile;
		BOOL ret = myFile.Open(pszFileName, CFile::modeRead);
		CString FullName = myFile.GetFileTitle();
		int index = 0;
		index = FullName.Find('.');//��ָ��ĵ������ַ��в����Ƿ�����ַ���value,��0λ�ÿ�ʼ�飬���ص���λ��
		//m_ProcessName = FullName.Left(index);

		//SetDlgItemText(IDC_EDIT5, myFile.GetFileTitle());//���ļ�����д��ҳ����
		UpdateData(FALSE);
		if (!ret)
		{
			AfxMessageBox(_T("�����ļ�ʧ��"));
			return;
		}
		if (ret)//�ļ��򿪳ɹ�
		{

			char* old_locale = _strdup(setlocale(LC_CTYPE, NULL));
			setlocale(LC_CTYPE, "chs");
			while (myFile.ReadString(content) != FALSE)//һ���ж�
			{
				iSubItem = line % 13;//ȡ����
				nItem = line / 13;//ȡ��
				if (iSubItem == 0)//�����v                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              
				{

					m_ListCtrl.InsertItem(nItem + nIdx, _T(""));//InsertItem����ؼ�����һ����������,��סֻ������,��ô�������ݵĹ�������SetItemText��ʵ��
					m_ListCtrl.SetItemText(nItem + nIdx, iSubItem, content);//����ĵ�һ��
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
				if (iSubItem == 1)//��ע��
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

			//�ı���������е����
			int a;
			//��������+
			for (a = nIdx + nItem; a <= nItem + m_Row; a++)
			{
				strTemp.Format(_T("%d"), a + 1);
				m_ListCtrl.SetItemText(a, 0, strTemp);
			}
			//���ø���

			/*m_ListCtrl.SetItemState(nIdx + nItem, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);
			m_ListCtrl.EnsureVisible(m_Row, FALSE);*/


			CString temp;
			temp.Format(_T("%d"), nItem);//����ת�����ַ�

			CString str = _T("�Ѳ�������������") + temp;

			MessageBox(str, _T("��ʾ "), MB_YESNO);    //��ȡ���沢����

													 //myFile.GetFileName()   //�õ��������ļ�����������չ���磺test1.txt
													 //GetFileTitle()//����ļ����ƣ�������׺

			myFile.Close();
		}
	}
}
void CDiailogEditor::OnBnClickedButton10() //������·�����һ�п���
{

	if (haveeditcreate == true)//���֮ǰ�����˱༭������ٵ�
	{
		distroyEdit(&m_ListCtrl, &m_Edit, e_Item, e_SubItem);//���ٵ�Ԫ��༭�����
		haveeditcreate = false;
	}
	if (haveccomboboxcreate == true)//���֮ǰ�����������б������ٵ�
	{
		distroyCcombobox(&m_ListCtrl, &m_comBox, e_Item, e_SubItem);
		haveccomboboxcreate = false;
	}
	//ĩ�����½�һ��
	UpdateData(TRUE);
	CString strTemp;
	m_Row = m_ListCtrl.GetItemCount();//��ǰ����
	int nIdx = m_ListCtrl.GetSelectionMark();//���Ŀǰ��������к�
	
	//�½�һ�пհ����ڵ�ǰ�е���һ��
	
	strTemp.Format(_T("%d"), nIdx + 2);
	m_ListCtrl.InsertItem(nIdx + 1, strTemp);

	//m_ListCtrl.EnsureVisible(m_Row, FALSE);
	//�ı������е����
	int a;
	//��������+1
	

	for (a = m_Row+1; a > nIdx - 1; a--)
	{
		strTemp.Format(_T("%d"), a+1);
		m_ListCtrl.SetItemText(a, 0, strTemp);
	}
	//���ø���

	m_ListCtrl.SetItemState(nIdx + 1, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);
	

}


void CDiailogEditor::OnBnClickedButton11()//ɾ��һ��
{
	CString strTemp;

	if (haveeditcreate == true)//���֮ǰ�����˱༭������ٵ�
	{
		distroyEdit(&m_ListCtrl, &m_Edit, e_Item, e_SubItem);//���ٵ�Ԫ��༭�����
		haveeditcreate = false;
	}
	if (haveccomboboxcreate == true)//���֮ǰ�����������б������ٵ�
	{
		distroyCcombobox(&m_ListCtrl, &m_comBox, e_Item, e_SubItem);
		haveccomboboxcreate = false;
	}
	m_Row = m_ListCtrl.GetItemCount();//������
	int nIdx = m_ListCtrl.GetSelectionMark();//���Ŀǰ��������к�
	m_ListCtrl.DeleteItem(nIdx);
	int a;
	//��������-1
	for (a = m_Row ; a > nIdx-1; a--)
	{
		strTemp.Format(_T("%d"), a+1);
		m_ListCtrl.SetItemText(a,0, strTemp);
	}
}


void CDiailogEditor::OnBnClickedButton3()//�����ĵ�txt
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	//GetDlgItem(IDC_EDIT4)->SetFocus();�������뽹��
	if (haveeditcreate == true)//���֮ǰ�����˱༭������ٵ�
	{
		distroyEdit(&m_ListCtrl, &m_Edit, e_Item, e_SubItem);//���ٵ�Ԫ��༭�����
		haveeditcreate = false;
	}
	if (haveccomboboxcreate == true)//���֮ǰ�����������б������ٵ�
	{
		distroyCcombobox(&m_ListCtrl, &m_comBox, e_Item, e_SubItem);
		haveccomboboxcreate = false;
	}
	//��ȡexe�ļ���·��
	CString path;
	GetModuleFileName(NULL, path.GetBufferSetLength(MAX_PATH + 1), MAX_PATH);
	path.ReleaseBuffer();
	int pos = path.ReverseFind('\\');
	path = path.Left(pos);
	path = path + _T("\\");
	CString   strFileName;
	CFileDialog   m_ldFile(FALSE);
	m_ldFile.m_ofn.lpstrFilter = _T("*.txt "); //Ҫѡ����ļ���׺
	m_ldFile.m_ofn.lpstrInitialDir = path;//Ĭ�ϵ��ļ�·��
	m_ldFile.m_ofn.lpstrDefExt = _T("txt");//Ĭ����չ��
	LPWSTR  lpstr = (LPWSTR)(LPCWSTR)m_ProcessName;//����ת��
	CString imgName;
	imgName = m_ldFile.GetFileName();//��ȡ�ļ���

	if (m_ProcessName == "")//���δ��������
	{
		m_ldFile.DoModal();//ģ̬�Ի��򴴽����û���������
		strFileName = m_ldFile.GetPathName();//������·�����ļ���
	}
	//�����ļ�	
	if (m_ProcessName != "")//����Ѿ��������� ֱ�ӱ�����Ĭ��·��
	{
		m_ldFile.m_ofn.lpstrFile = lpstr;//����Ĭ���ļ���
		strFileName = path + m_ProcessName+_T(".txt");
	}  
	LPCTSTR pszFileName = strFileName.GetBufferSetLength(strFileName.GetLength());
	CStdioFile myFile;
	CFileException   fileException;
	if (true == (bool)PathFileExists(strFileName)) //�ж��Ƿ��Ѿ�����
	{
		if (MessageBox(_T("�Ѵ��ڣ��Ƿ񸲸ǣ� "), _T("��ʾ "), MB_YESNO) == IDYES)
		{
			BOOL ret = myFile.Open(pszFileName, CFile::modeCreate | CFile::modeWrite | CFile::typeText, &fileException);
			if (!ret)
			{
				AfxMessageBox(_T("����ʧ�ܣ������±��棡"));
				return;
			}
				//�ļ���д������ 
			SaveListCell(myFile);//�洢txt����
			//�Ƿ������鿴���ļ� 
			if (MessageBox(_T("�ѱ��棬Ҫ�鿴�� "), _T("��� "), MB_YESNO) == IDYES)
			{
				//ShellExecute(NULL,NULL,SW_SHOWNORMAL);
				ShellExecute(NULL, _T("open"), pszFileName, NULL, NULL, SW_SHOWNORMAL);//����������һ���ⲿ������±�
			}
			//�ر��ļ� 
			myFile.Close();		
		}
		else
		{
			MessageBox(_T("���޸��������±��� "), _T("��ʾ "), MB_YESNO);
		}
	}
	if (false == (bool)PathFileExists(strFileName))//������������
	{
		BOOL ret = myFile.Open(pszFileName, CFile::modeCreate | CFile::modeWrite | CFile::typeText, &fileException);
		if (!ret)
		{
			AfxMessageBox(_T("����ʧ�ܣ������±��棡"));
			return;
		}
		//�ļ���д������ 
		SaveListCell(myFile);
		//�Ƿ������鿴���ļ� 
		if (MessageBox(_T("�ѱ��棬Ҫ�鿴�� "), _T("��� "), MB_YESNO) == IDYES)
		{
			//ShellExecute(NULL,NULL,SW_SHOWNORMAL);
			ShellExecute(NULL, _T("open"), pszFileName, NULL, NULL, SW_SHOWNORMAL);//����������һ���ⲿ������±�
		}
		//�ر��ļ� 
		myFile.Close();
	}

}
void CDiailogEditor::SaveListCell(CStdioFile & File)
{
	int   iColSum = 12;       //List�е���������
	int   iCount = m_ListCtrl.GetItemCount();//����
	for (int iItem = 0; iItem < iCount; iItem++)
	{
		for (int iCol = 0; iCol < iColSum; iCol++)//ֻ�������5��
		{
			CString   strTemp = m_ListCtrl.GetItemText(iItem, iCol);
			if (iCol == 0 || iCol == 2 || iCol == 3 || iCol == 5 || iCol == 6 || iCol == 7 || iCol == 8||iCol == 1|| iCol == 4 || iCol == 9 || iCol == 10)
			{
				//lstrcat(strTemp.GetBuffer(strTemp.GetLength()), _T(")"));
				char* old_locale = _strdup(setlocale(LC_CTYPE, NULL));
				setlocale(LC_CTYPE, "chs");//�趨
				try
				{
					lstrcat(strTemp.GetBuffer(strTemp.GetLength()), _T("\n"));//����
					File.WriteString(strTemp.GetBuffer(strTemp.GetLength()));
				}
				catch (CException* e)
				{
					e->ReportError();
				}
				setlocale(LC_CTYPE, old_locale);
				free(old_locale);//��ԭ�����趨
			}
			if (iCol == 11)
			{
				//lstrcat(strTemp.GetBuffer(strTemp.GetLength()), _T(")"));
				char* old_locale = _strdup(setlocale(LC_CTYPE, NULL));
				setlocale(LC_CTYPE, "chs");//�趨
				try
				{
					lstrcat(strTemp.GetBuffer(strTemp.GetLength()), _T("\n\n"));//������
					File.WriteString(strTemp.GetBuffer(strTemp.GetLength()));
				}
				catch (CException* e)
				{
					e->ReportError();
				}
				setlocale(LC_CTYPE, old_locale);
				free(old_locale);//��ԭ�����趨
			}
			
		}
	}
}


void CDiailogEditor::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	CDialogEx::OnActivate(nState, pWndOther, bMinimized);

	// TODO: �ڴ˴������Ϣ����������
	UpdateData(FALSE);
}
LRESULT CDiailogEditor::OnMyMessage(WPARAM wParam, LPARAM lParam)
{
	//MessageBox("recv msg success");
	//����Լ�����Ϣ����
	m = pEdit->resultFileName;
	//m_comBox.InsertString(0, m);
	//m_comBox.SetCurSel(0);
	m_Edit.SetWindowText(m);///////m_edit2Ϊ�༭�����������ΪCedit

	UpdateData(FALSE);

		return 0;
}

void CDiailogEditor::OnBnClickedButton2()//����б�
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (MessageBox(_T("��ǰ���ݽ�����գ��Ƿ������"), _T("��ʾ "), MB_YESNO) == IDYES)
	{
		//ShellExecute(NULL,NULL,SW_SHOWNORMAL);
		//��ȡexe�ļ���·��
		m_ProcessName = _T("");
		UpdateData(FALSE);
		m_ListCtrl.DeleteAllItems(); // ȫ�����  
	}
}


void CDiailogEditor::OnBnClickedButton4()//ͳ������
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������


	int Num = m_ListCtrl.GetItemCount();

	CString temp;
	temp.Format(_T("%d"), Num);//����ת�����ַ�


	CString str = _T("��ǰ�����������ƣ�") + temp;

	MessageBox(str, _T("��ʾ "), MB_YESNO) == IDYES;
}


void CDiailogEditor::OnBnClickedButton12()
{
	MessageBox(_T("�����ȱ����ټ��"), _T("��ʾ "), MB_YESNO) == IDYES;
	//��TXT�ļ���
	CString path;
	GetModuleFileName(NULL, path.GetBufferSetLength(MAX_PATH + 1), MAX_PATH);
	path.ReleaseBuffer();
	int pos = path.ReverseFind('\\');
	path = path.Left(pos);
	path = path + _T("\\");

	CString   strFileName;
	CFileDialog   m_ldFile(TRUE);

	m_ldFile.m_ofn.lpstrFilter = _T("*.txt "); //Ҫѡ����ļ���׺
	m_ldFile.m_ofn.lpstrInitialDir = path;//Ĭ�ϵ��ļ�·��
	m_ldFile.m_ofn.lpstrDefExt = _T("txt");//Ĭ����չ��

	if (m_ldFile.DoModal() == IDOK)
	{
		strFileName = m_ldFile.GetPathName();       //������·�����ļ��� 
	}
	//ѡ���ļ�������	
	LPCTSTR pszFileName = strFileName.GetBufferSetLength(strFileName.GetLength());
	CStdioFile myFile;
	BOOL ret = myFile.Open(pszFileName, CFile::modeRead);
	m_ProcessName = myFile.GetFileTitle();
	//SetDlgItemText(IDC_EDIT5, myFile.GetFileTitle());//���ļ�����д��ҳ����
	UpdateData(FALSE);
	if (!ret)
	{
		AfxMessageBox(_T("���ļ�ʧ��"));
		return;
	}
	if (ret)//�ļ��򿪳ɹ�
	{
		beginExamination(myFile);//��ʼ���
	}
	CString m;
	m.Format(_T("%d"), m_commNum);//intת�����ַ�
	AddString(_T("һ�������") + m + _T("��ָ�"));
	AddString(_T(""));//��һ��
	myFile.Close();
}
void CDiailogEditor::beginExamination(CStdioFile&File)
{
	//�½�һ��ҳ������������
	if (NULL == m_exam)  // ���ָ�����m_create��ֵΪNULL����Ի���δ��������Ҫ��̬����   
	{
		m_exam = new CExamination();   //��̬��������
		m_exam->Create(IDD_DIALOG_Examination, this);
	}
	m_exam->ShowWindow(SW_SHOW);  // ��ʾ��ģ̬�Ի���   
	m_exam->SetWindowPos(NULL, 550, 250, 0, 0, SWP_NOSIZE);
	//SWP_NOSIZE���ֵ�ǰ�Ի����С����4��5����cx��cy�ᱻ���ԣ����÷�ģ̬�Ի����λ��

	m_commNum = pMainDlg->findCoronNum(&File);//ð�Ÿ�������ָ�������
	if (m_commNum == 0)
	{
		AddString(_T("�ű������κ�ָ�"));
	}
	else
	{
		CommandExamination(File);//ָ���⺯��
	}
}
void CDiailogEditor::AddString(CString msg)    //����־�б������־
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
	//�����־���б���	
	//����
	//UpdateData(FALSE);	
	//������������������
	pExam->m_ListResult.SetTopIndex(pExam->m_LogNum % 200000 - 1);
}
void CDiailogEditor::CommandExamination(CStdioFile&File)//8��ָ��Ĵ�����
{
	int i = 1;
	CString a;
	while (!feof(File.m_pStream))//feof����ĵ��Ƿ�ĩβ
	{

		m_fileComm = pMainDlg->findCoron(&File);//return str����ð�ź���ǰ����ַ����ݣ���ָ�����ƣ�����ð�ţ���//������˽�β����null��
		a.Format(_T("%d"), i);//intת�����ַ�
		if (m_fileComm == _T(":"))//���ָ�������ǿյģ�Ҳ���ǿ�ָ��
		{
			AddString(_T("ָ��") + a + _T("������ָ���"));
			i++;
			continue;
		}
		if (m_fileComm== _T("Common:"))//--------------------------------��ָͨ��1
		{
			AddString(_T("ָ��") + a + _T("��OK��"));
			examCommon(File, i);
			i++;
			continue;
		}
		if (m_fileComm==_T("Inquiry:"))
		{
			AddString(_T("ָ��") + a + _T("��OK��"));
			examInquiry(File, i);//---------------------------------------------------��ѯ����2
			i++;
			continue;
		}
		if (m_fileComm == _T("Robot:"))
		{
			AddString(_T("ָ��") + a + _T("��OK��"));
			examRobot(File, i);//---------------------------------------------------����������3
			i++;
			continue;
		}
		if (m_fileComm== _T("DelayTime:"))
		{
			AddString(_T("ָ��") + a + _T("��OK��"));
			examDelayTime(File, i);
			i++;
			continue;//--------------------------------------------------------��ʱ����4
		}
		if (m_fileComm== _T("ThreadInteraction:"))//---------------�߳̽�������5
		{
			AddString(_T("ָ��") + a + _T("��OK��"));
			examThreadInteraction(File, i);
			i++;
			continue;
		}
		if (m_fileComm == _T("ImageProcessing:"))
		{
			AddString(_T("ָ��") + a + _T("��OK��"));
			examImageProcessing(File, i);//------------------------------------ͼ��������6
			i++;
			continue;
		}
		if (m_fileComm == _T("LightAdjusting:"))
		{
			AddString(_T("ָ��") + a + _T("��OK��"));
			examLightAdjusting(File, i);//---------------------------------------��Դ��������7
			i++;
			continue;

		}
		if (m_fileComm == _T("AdjustingWithResult:"))
		{
			AddString(_T("ָ��") + a + _T("��OK��"));
			examAdjustingWithResult(File, i); //----------------------------------΢���豸����8
			i++;
			continue;
		}
		if (m_fileComm == "")//������ص���NULL
		{
			AddString(_T(""));
			AddString(_T("�����ϣ�"));
			break;
		}
		else
		{
			AddString(_T("ָ��") + a + _T("����δ���壡��"));
			i++;
			continue;
		}
	}
}
void CDiailogEditor::examCommon(CStdioFile&File, int i)//һ������
{
	CString comm[4];//�洢��ȡ����4������
	
					//file->ReadString(m_fileComm);
	CString MiddleComm;
	for (i = 0; i < 4; i++)
	{
		comm[i] = pMainDlg->ChineseTransformation(MiddleComm, &File);
	}
	CString a;
	a.Format(_T("%d"), i);//intת�����ַ�
	if (comm[0] == "")
	{
		AddString(_T("    ����1�����ղ�������"));
	}

	else if (comm[0] == "\r\nIO" || comm[0] == "\r\nAxisMove" || comm[0] == "\r\nAxisSetTargetSpeed")
	{
		AddString(_T("    ����1��"));
		examEmpty(1, 3, comm, a);
	}
	else if (comm[0] == "\r\nAxisSetHomePosition" || comm[0] == "\r\nAxisGoHomePosition" || comm[0] == "\r\nAxisGoPositiveLimit" || comm[0] == "\r\nAxisGoNegativeLimit" || comm[0] == "AxisSMVR")
	{
		AddString(_T("    ����1��"));
		examEmpty(1, 2, comm, a);
	}
	else
	{
		AddString(_T("    ����1����δ���壡��"));
	}
}
void CDiailogEditor::examInquiry(CStdioFile&File, int i)
{

	CString comm[4];//�洢��ȡ����4������
					//file->ReadString(m_fileComm);
	CString MiddleComm;
	for (i = 0; i < 4; i++)
	{
		comm[i] = pMainDlg->ChineseTransformation(MiddleComm, &File);
	}
	CString a;
	a.Format(_T("%d"), i);//intת�����ַ�
	examEmpty(0, 3, comm, a);

	if(comm[0]== "\r\nLimit?"&&comm[3]!="")
	{
		if (comm[3]!="\r\nValue=-1"&& comm[3] !="\r\nValue=1"&& comm[3] != "\r\nValue=0")
		{
			AddString(_T("    ��λ��ѯValueֵ����"));
		}
	}
}
void CDiailogEditor::examRobot(CStdioFile&File, int i)
{
	CString comm[7];//�洢��ȡ����4������
	//file->ReadString(m_fileComm);
	CString MiddleComm;
	for (i = 0; i < 7; i++)
	{
		comm[i] = pMainDlg->ChineseTransformation(MiddleComm, &File);
	}

	CString a;
	a.Format(_T("%d"), i);//intת�����ַ�
	if (comm[0] == "MoveRobot")
	{
		AddString(_T("    ����1��"));
		examEmpty(1, 6, comm, a);
	}
	else if (comm[0] == "InquiryRobot")
	{
		AddString(_T("    ����1��"));
		if (comm[1] == "RobotStatus?")
		{
			AddString(_T("    ����2��"));
			examEmpty(2, 2, comm, a);
		}
		else if (comm[1] == "RobotAbsolutePosition?")
		{
			AddString(_T("    ����2��"));
			examEmpty(2, 5, comm, a);
		}
		else if (comm[1] == "")
		{
			AddString(_T("    ����2�����ղ�������"));
		}
		else
		{
			AddString(_T("    ����2����δ���壡��"));
		}
	}
	else if (comm[0] == "")
	{
		AddString(_T("    ����1�����ղ�������"));
	}
	else
	{
		AddString(_T("    ����1����δ���壡��"));
	}

}
void CDiailogEditor::examDelayTime(CStdioFile&File, int i)
{
	CString comm[1];//�洢��ȡ����4������
					//file->ReadString(m_fileComm);
	CString MiddleComm;
	for (i = 0; i < 1; i++)
	{
		comm[i] = pMainDlg->ChineseTransformation(MiddleComm, &File);
	}
	CString a;
	a.Format(_T("%d"), i);//intת�����ַ�
	examEmpty(0, 0, comm, a);
}
void CDiailogEditor::examThreadInteraction(CStdioFile&File, int i)
{
	CString comm[3];//�洢��ȡ����4������
					//file->ReadString(m_fileComm);
	CString MiddleComm;
	for (i = 0; i < 4; i++)
	{
		comm[i] = pMainDlg->ChineseTransformation(MiddleComm, &File);
	}
	
	CString a;
	a.Format(_T("%d"), i);//intת�����ַ�
	examEmpty(0, 2, comm, a);
	if (comm[1].GetLength() != 0&& comm[2].GetLength() != 0)
	{

		int index = pMainDlg->findChar(comm[1], '=', 1);
		int SenderThreadNum = _ttoi(comm[1].Mid(index));
		index = pMainDlg->findChar(comm[2], '=', 1);
		int RecipientThreadNum = _ttoi(comm[2].Mid(index));
		if (SenderThreadNum-RecipientThreadNum==0)
		{
			AddString(_T("    �̵߳ķ��ͷ��ͽ��շ�������ͬ��"));
		}
	}
}
void CDiailogEditor::examLightAdjusting(CStdioFile&File, int i)
{
	CString comm[3];//�洢��ȡ����4������
					//file->ReadString(m_fileComm);
	File.ReadString(comm[0]);//����1
	File.ReadString(comm[1]);//����2
	File.ReadString(comm[2]);//����3
	CString a;
	a.Format(_T("%d"), i);//intת�����ַ�
	examEmpty(0, 2, comm, a);
}
void CDiailogEditor::examImageProcessing(CStdioFile&File, int i)
{
	CString comm[8];//�洢��ȡ����4������
					//file->ReadString(m_fileComm);
	CString MiddleComm;
	for (i = 0; i < 8; i++)
	{
		comm[i] = pMainDlg->ChineseTransformation(MiddleComm, &File);
	}
	
	CString a;
	a.Format(_T("%d"), i);//intת�����ַ�
	if (comm[0] == "\r\nTemplateMatching")
	{
		AddString(_T("    ����1��"));
		examEmpty(1, 6, comm, a);
	}
	else if (comm[0] == "\r\nCricleDetection")
	{
		AddString(_T("    ����1��"));
		examEmpty(1, 7, comm, a);
	}
	else
	{
		AddString(_T("    ����1����δ���壡��"));
	}
}
void CDiailogEditor::examAdjustingWithResult(CStdioFile&File, int i)
{
	CString comm[8];//�洢��ȡ����4������
					//file->ReadString(m_fileComm);
	CString MiddleComm;
	for (i = 0; i < 8; i++)
	{
		comm[i] = pMainDlg->ChineseTransformation(MiddleComm, &File);
	}

	CString a;
	a.Format(_T("%d"), i);//intת�����ַ�
	examEmpty(0, 7, comm, a);
}

void CDiailogEditor::examEmpty(int Min, int Max, CString comm[], CString a)
{
	int j = Min;
	CString b;
	while (j <= Max)
	{
		b.Format(_T("%d"), j + 1);//intת�����ַ�
		if (comm[j].GetLength() == 0)//��ָͨ��ĳЩ��������ȫ�ǿյ�
		{
			AddString(_T("    ����") + b + _T("�����ղ�������"));
		}
		else
		{
			AddString(_T("    ����") + b );
		}
		j++;
	}
}


void CDiailogEditor::OnBnClickedButton7()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnBnClickedButton3();//�����ĵ�txt
}


void CDiailogEditor::OnBnClickedButton6()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	//GetDlgItem(IDC_EDIT4)->SetFocus();�������뽹��
	if (haveeditcreate == true)//���֮ǰ�����˱༭������ٵ�
	{
		distroyEdit(&m_ListCtrl, &m_Edit, e_Item, e_SubItem);//���ٵ�Ԫ��༭�����
		haveeditcreate = false;
	}
	if (haveccomboboxcreate == true)//���֮ǰ�����������б������ٵ�
	{
		distroyCcombobox(&m_ListCtrl, &m_comBox, e_Item, e_SubItem);
		haveccomboboxcreate = false;
	}

	if(MessageBox(_T("�Ƿ��Ѿ����棿"), _T("��ʾ "), MB_YESNO) == IDYES)
	//��TXT�ļ���
	{
		CDialog::OnOK();
	}
}




BOOL CDiailogEditor::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	return CDialogEx::OnMouseWheel(nFlags, zDelta, pt);
}


void CDiailogEditor::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	SetFocus();
	CDialogEx::OnLButtonDown(nFlags, point);
}




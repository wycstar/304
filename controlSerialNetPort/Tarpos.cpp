// Tarpos.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "test3.h"
#include "Tarpos.h"
#include "afxdialogex.h"


// CTarpos �Ի���

IMPLEMENT_DYNAMIC(CTarpos, CDialogEx)

CTarpos::CTarpos(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTarpos::IDD, pParent)
	, m_Tap_edit1(0)
	, m_Tap_edit2(0)
	, m_Tap_edit3(0)
	, m_Tap_edit4(0)
	, m_Tap_edit5(0)
{

}

CTarpos::~CTarpos()
{
}

void CTarpos::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_Tap_edit1, m_Tap_edit1);
	DDX_Text(pDX, IDC_Tap_edit2, m_Tap_edit2);
	DDX_Text(pDX, IDC_Tap_edit3, m_Tap_edit3);
	DDX_Text(pDX, IDC_Tap_edit4, m_Tap_edit4);
	DDX_Text(pDX, IDC_Tap_edit5, m_Tap_edit5);
}


BEGIN_MESSAGE_MAP(CTarpos, CDialogEx)
	ON_BN_CLICKED(IDC_RADIO_MOVEJ, &CTarpos::OnBnClickedRadioMovej)
	ON_BN_CLICKED(IDC_RADIO_MOVEL, &CTarpos::OnBnClickedRadioMovel)
	ON_BN_CLICKED(IDC_RADIO_MOVEC, &CTarpos::OnBnClickedRadioMovec)
END_MESSAGE_MAP()


// CTarpos ��Ϣ�������
//ĩ��λ��ģʽ
void CTarpos::OnBnClickedRadioMovej()
{
	// �����涯
	Motionmode = 0;
}


void CTarpos::OnBnClickedRadioMovel()
{
	// ֱ���˶�
	Motionmode = 1;
}


void CTarpos::OnBnClickedRadioMovec()
{
	// Բ���˶�
	Motionmode = 2;
}


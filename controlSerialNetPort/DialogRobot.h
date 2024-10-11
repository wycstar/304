#pragma once


#include "TcAdsDef.h"
#include "TcAdsAPI.h"
#include <iostream>
#include "resource.h"		// ������
#include <conio.h>
#include "MMSystem.h"
#include "time.h"
#include <Windows.h>
#include <sapi.h>//TTS����ͷ�ļ�
#pragma comment(lib,"WinMM.Lib") 
#pragma comment(lib,"TcAdsDll.lib") 
//#include "TcAdsDef.h"
#include "Joivel.h"
#include "Joipos.h"
#include "Tarvel.h"
#include "Tarpos.h"
#include "Hancon.h"
#include "Autcon.h"
//#include "TcAdsDef.h"
//#include "joystickapi.h"
//#include "TcAdsAPI.h"   //������̬���ӿ��ͷ�ļ�
////#pragma  comment(lib,"TcAdsDll")   //��ʽ���ÿ��ļ�
// CDialogRobot �Ի���

class CDialogRobot : public CDialog
{
	DECLARE_DYNAMIC(CDialogRobot)

public:
	CDialogRobot(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDialogRobot();

	void InitADS(int portt);
	//====================ADS����
	//long	    lErr, lPort;
	//AmsAddr		Addr;
	//PAmsAddr    pAddr = &Addr;

	//====================�ռ�λ������;
	double ActualMotorPosition[5];
	double ActualSpacePosition[5];
	double TargetSpacePosition[5];
	double TargetMotorPosition[5];
	double q_Re[5];
	CString q_Re_Char[5];

	//==================== ʹ�ܼ�ģʽ����;
	int  Mode;
	int  ActualStatus;
	int  TerminalMode;

	//====================�շ���������;
	void SendData(int valName, bool data);
	void SendData(int valName, int data);
	void SendData(int valName, double data);
	void SendData(int valName, double data[], int size);

	void ReadData(int valName, bool &data);
	void ReadData(int valName, int &data);
	void ReadData(int valName, double &data);
	void ReadData(int valName, double data[], int size);

	CTabCtrl m_tab;
	CJoipos m_Joipos;
	CTarpos m_Tarpos;
	CHancon m_Hancon;
	CAutcon m_Autcon;
	JOYINFOEX JoyinfoEx;
	DWORD *dwpos[5];
	double gdwpos[5];
	CDialog* pDialog[6];

	//ʵ�ʵ��λ��
	double m_ActMotPos1;
	double m_ActMotPos2;
	double m_ActMotPos3;
	double m_ActMotPos4;
	double m_ActMotPos5;
	double *m_ActMotPos[6];

	//ʵ�ʿռ�λ��
	double m_ActSpaPos1;
	double m_ActSpaPos2;
	double m_ActSpaPos3;
	double m_ActSpaPos4;
	double *m_ActSpaPos[5];



	//�ֱ�����
	//======================double Xpos Ypos Zpos Rpos
	int JOY_BUTTON[13];
	afx_msg void OnBnClickedPower();
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedTcpsend();
	afx_msg void OnBnClickedCheckPower();
	afx_msg void OnBnClickedRadioTcplink();
	afx_msg void OnBnClickedRadioTcpdisc();
	afx_msg void TerminalJudge();
	int j;
	// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_Robot };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	void powerdo();
};

#pragma once


#include "TcAdsDef.h"
#include "TcAdsAPI.h"
#include <iostream>
#include "resource.h"		// 主符号
#include <conio.h>
#include "MMSystem.h"
#include "time.h"
#include <Windows.h>
#include <sapi.h>//TTS语音头文件
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
//#include "TcAdsAPI.h"   //包含静态链接库的头文件
////#pragma  comment(lib,"TcAdsDll")   //隐式调用库文件
// CDialogRobot 对话框

class CDialogRobot : public CDialog
{
	DECLARE_DYNAMIC(CDialogRobot)

public:
	CDialogRobot(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialogRobot();

	void InitADS(int portt);
	//====================ADS声明
	//long	    lErr, lPort;
	//AmsAddr		Addr;
	//PAmsAddr    pAddr = &Addr;

	//====================空间位置数组;
	double ActualMotorPosition[5];
	double ActualSpacePosition[5];
	double TargetSpacePosition[5];
	double TargetMotorPosition[5];
	double q_Re[5];
	CString q_Re_Char[5];

	//==================== 使能及模式变量;
	int  Mode;
	int  ActualStatus;
	int  TerminalMode;

	//====================收发函数变量;
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

	//实际电机位置
	double m_ActMotPos1;
	double m_ActMotPos2;
	double m_ActMotPos3;
	double m_ActMotPos4;
	double m_ActMotPos5;
	double *m_ActMotPos[6];

	//实际空间位置
	double m_ActSpaPos1;
	double m_ActSpaPos2;
	double m_ActSpaPos3;
	double m_ActSpaPos4;
	double *m_ActSpaPos[5];



	//手柄定义
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
	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_Robot };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	void powerdo();
};

// DialogRobot.cpp : 实现文件
//

#include "stdafx.h"
#include "controlSerialNetPort.h"
#include "controlSerialNetPortDlg.h"
#include "DialogRobot.h"
#include "afxdialogex.h"
//
//#include "TcAdsAPI.h"   //包含静态链接库的头文件
//
//#pragma  comment(lib,"TcAdsDll")   //隐式调用库文件

CDialogRobot * robot;//全局变量
int  Power_do;
double  Zeros_do[5] = { 0,1,1,0,1 };
long	    lErr, lPort;
AmsAddr		Addr;
PAmsAddr    pAddr = &Addr;

// CDialogRobot 对话框
extern CcontrolSerialNetPortDlg* mainDlg;
IMPLEMENT_DYNAMIC(CDialogRobot, CDialog)

enum VAL_NAME//变量枚举，为了表示方便，用枚举宏定义标记ADS通信的变量，宏定义的变量为自然数，其与对应位置的ADS通信变量意义相关
{
	//主界面
	POWER_DO,//值为0
			 //====================实际空间位置(1)
			 ACTUALSPACEPOSITION,
			 //====================实际关节位置(2)
			 ACTUALMOTORPOSITION,
			 //Mode1：关节位置模式
			 //====================目标关节位置(3)
			 TARGETMOTORPOSITION,
			 //Mode2：末端位置模式
			 //====================目标空间位置(4-6)
			 MOTIONMODE,
			 TARGETSPACEPOSITION,
			 TARGETMAXVELOCITY,
			 //Mode4：手柄控制模式(7-13)
			 KEY,
			 KEY12,
			 KEYTEMP,
			 AXIS_X,
			 AXIS_Y,
			 AXIS_Z,
			 AXIS_R,
			 //(14 - 16)
			 MODE,
			 ACTUALSTATUS,
			 ZEROS_DO,
			 TERMINALMODE,
			 VAL_END
};

#define VAL_NUM VAL_END
unsigned long valHandle[VAL_NUM];//

char strValName[VAL_NUM][50] = //ADS通信变量，在TWICAT中定义的相同名称相同数据类型的变量，前面加 “MAIN.  "
{

	//对应TWINCAT中的变量数组实际空间位置
	//主界面
	"MAIN.Power_do",
	//====================实际空间位置(1)
	"MAIN.ActualSpacePosition",
	//====================实际关节位置(2)
	"MAIN.ActualMotorPosition",
	//Mode1：关节位置模式
	//====================目标关节位置(3)
	"MAIN.TargetMotorPosition",
	//Mode3：末端位置模式
	//====================目标空间位置(4-6)
	"MAIN.MotionMode",
	"MAIN.TargetSpacePosition",
	"MAIN.TargetMaxVelocity",
	//Mode4：手柄模式(7-13)
	"MAIN.Key",
	"MAIN.Key12",
	"MAIN.KeyTemp",
	"MAIN.Axis_X",
	"MAIN.Axis_Y",
	"MAIN.Axis_Z",
	"MAIN.Axis_R",
	//(14-16)
	"MAIN.Mode",
	"MAIN.ActualStatus",
	"MAIN.Zeros_do",
	"MAIN.TerminalMode",
};

void CDialogRobot::InitADS(int portt)
{
	pAddr = &Addr;
	lPort = AdsPortOpen();
	lErr = AdsGetLocalAddress(pAddr);//自动读取本机AMS地址
									 //与其他机器通讯时取联机地址, 例如目标机器地址为172.18.137.70.1.1，AMS地址可在"About TWINCAT"信息中查看
									 /*pAddr->netId.b[0] = 172;
									 pAddr->netId.b[1] = 18;
									 pAddr->netId.b[2] = 137;
									 pAddr->netId.b[3] = 70;
									 pAddr->netId.b[4] = 1;
									 pAddr->netId.b[5] = 1;*/

	pAddr->port = portt;  //TwinCAT3的端口号一般均为851
						  //使能

}

void CDialogRobot::SendData(int valName, double data)
{
	lErr = AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(valHandle[valName]), &(valHandle[valName]), sizeof(strValName[valName]), strValName[valName]);
	lErr = AdsSyncWriteReq(pAddr, ADSIGRP_SYM_VALBYHND, valHandle[valName], sizeof(data), &data);
	lErr = AdsSyncWriteReq(pAddr, ADSIGRP_SYM_RELEASEHND, 0, sizeof(valHandle[valName]), &(valHandle[valName]));
}
void CDialogRobot::SendData(int valName, bool data)
{
	lErr = AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(valHandle[valName]), &(valHandle[valName]), sizeof(strValName[valName]), strValName[valName]);
	lErr = AdsSyncWriteReq(pAddr, ADSIGRP_SYM_VALBYHND, valHandle[valName], sizeof(data), &data);
	lErr = AdsSyncWriteReq(pAddr, ADSIGRP_SYM_RELEASEHND, 0, sizeof(valHandle[valName]), &(valHandle[valName]));
}
void CDialogRobot::SendData(int valName, int data)
{
	lErr = AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(valHandle[valName]), &(valHandle[valName]), sizeof(strValName[valName]), strValName[valName]);
	lErr = AdsSyncWriteReq(pAddr, ADSIGRP_SYM_VALBYHND, valHandle[valName], sizeof(data), &data);
	lErr = AdsSyncWriteReq(pAddr, ADSIGRP_SYM_RELEASEHND, 0, sizeof(valHandle[valName]), &(valHandle[valName]));

}
void CDialogRobot::SendData(int valName, double data[], int size)
{
	lErr = AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(valHandle[valName]), &(valHandle[valName]), sizeof(strValName[valName]), strValName[valName]);
	lErr = AdsSyncWriteReq(pAddr, ADSIGRP_SYM_VALBYHND, valHandle[valName], size, &data[0]);
	lErr = AdsSyncWriteReq(pAddr, ADSIGRP_SYM_RELEASEHND, 0, sizeof(valHandle[valName]), &(valHandle[valName]));
	mainDlg->AddString(_T("机器人发送") + CPublic::double2CString(data[1]) + _T(" ") + CPublic::double2CString(data[2]));
}

void CDialogRobot::ReadData(int valName, bool &data)
{
	lErr = AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(valHandle[valName]), &(valHandle[valName]), sizeof(strValName[valName]), strValName[valName]);
	lErr = AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, valHandle[valName], sizeof(data), &data);
	lErr = AdsSyncWriteReq(pAddr, ADSIGRP_SYM_RELEASEHND, 0, sizeof(valHandle[valName]), &(valHandle[valName]));
}

void CDialogRobot::ReadData(int valName, int &data)
{
	lErr = AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(valHandle[valName]), &(valHandle[valName]), sizeof(strValName[valName]), strValName[valName]);
	lErr = AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, valHandle[valName], sizeof(data), &data);
	lErr = AdsSyncWriteReq(pAddr, ADSIGRP_SYM_RELEASEHND, 0, sizeof(valHandle[valName]), &(valHandle[valName]));
}

void CDialogRobot::ReadData(int valName, double &data)
{
	lErr = AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(valHandle[valName]), &(valHandle[valName]), sizeof(strValName[valName]), strValName[valName]);
	lErr = AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, valHandle[valName], sizeof(data), &data);
	lErr = AdsSyncWriteReq(pAddr, ADSIGRP_SYM_RELEASEHND, 0, sizeof(valHandle[valName]), &(valHandle[valName]));
}

void CDialogRobot::ReadData(int valName, double data[], int size)
{
	lErr = AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(valHandle[valName]), &(valHandle[valName]), sizeof(strValName[valName]), strValName[valName]);
	lErr = AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, valHandle[valName], size, &data[0]);
	lErr = AdsSyncWriteReq(pAddr, ADSIGRP_SYM_RELEASEHND, 0, sizeof(valHandle[valName]), &(valHandle[valName]));
}


CDialogRobot::CDialogRobot(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_DIALOG_Robot, pParent)
{

}

CDialogRobot::~CDialogRobot()
{
}

void CDialogRobot::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDialogRobot, CDialog)
END_MESSAGE_MAP()


// CDialogRobot 消息处理程序


BOOL CDialogRobot::OnInitDialog()
{
	CDialog::OnInitDialog();

	robot = this;
	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CDialogRobot::powerdo()
{
	Power_do = 1;
	SendData(POWER_DO, Power_do);
	SendData(ZEROS_DO, Zeros_do, sizeof(Zeros_do));
}

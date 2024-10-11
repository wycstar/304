// DialogRobot.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "controlSerialNetPort.h"
#include "controlSerialNetPortDlg.h"
#include "DialogRobot.h"
#include "afxdialogex.h"
//
//#include "TcAdsAPI.h"   //������̬���ӿ��ͷ�ļ�
//
//#pragma  comment(lib,"TcAdsDll")   //��ʽ���ÿ��ļ�

CDialogRobot * robot;//ȫ�ֱ���
int  Power_do;
double  Zeros_do[5] = { 0,1,1,0,1 };
long	    lErr, lPort;
AmsAddr		Addr;
PAmsAddr    pAddr = &Addr;

// CDialogRobot �Ի���
extern CcontrolSerialNetPortDlg* mainDlg;
IMPLEMENT_DYNAMIC(CDialogRobot, CDialog)

enum VAL_NAME//����ö�٣�Ϊ�˱�ʾ���㣬��ö�ٺ궨����ADSͨ�ŵı������궨��ı���Ϊ��Ȼ���������Ӧλ�õ�ADSͨ�ű����������
{
	//������
	POWER_DO,//ֵΪ0
			 //====================ʵ�ʿռ�λ��(1)
			 ACTUALSPACEPOSITION,
			 //====================ʵ�ʹؽ�λ��(2)
			 ACTUALMOTORPOSITION,
			 //Mode1���ؽ�λ��ģʽ
			 //====================Ŀ��ؽ�λ��(3)
			 TARGETMOTORPOSITION,
			 //Mode2��ĩ��λ��ģʽ
			 //====================Ŀ��ռ�λ��(4-6)
			 MOTIONMODE,
			 TARGETSPACEPOSITION,
			 TARGETMAXVELOCITY,
			 //Mode4���ֱ�����ģʽ(7-13)
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

char strValName[VAL_NUM][50] = //ADSͨ�ű�������TWICAT�ж������ͬ������ͬ�������͵ı�����ǰ��� ��MAIN.  "
{

	//��ӦTWINCAT�еı�������ʵ�ʿռ�λ��
	//������
	"MAIN.Power_do",
	//====================ʵ�ʿռ�λ��(1)
	"MAIN.ActualSpacePosition",
	//====================ʵ�ʹؽ�λ��(2)
	"MAIN.ActualMotorPosition",
	//Mode1���ؽ�λ��ģʽ
	//====================Ŀ��ؽ�λ��(3)
	"MAIN.TargetMotorPosition",
	//Mode3��ĩ��λ��ģʽ
	//====================Ŀ��ռ�λ��(4-6)
	"MAIN.MotionMode",
	"MAIN.TargetSpacePosition",
	"MAIN.TargetMaxVelocity",
	//Mode4���ֱ�ģʽ(7-13)
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
	lErr = AdsGetLocalAddress(pAddr);//�Զ���ȡ����AMS��ַ
									 //����������ͨѶʱȡ������ַ, ����Ŀ�������ַΪ172.18.137.70.1.1��AMS��ַ����"About TWINCAT"��Ϣ�в鿴
									 /*pAddr->netId.b[0] = 172;
									 pAddr->netId.b[1] = 18;
									 pAddr->netId.b[2] = 137;
									 pAddr->netId.b[3] = 70;
									 pAddr->netId.b[4] = 1;
									 pAddr->netId.b[5] = 1;*/

	pAddr->port = portt;  //TwinCAT3�Ķ˿ں�һ���Ϊ851
						  //ʹ��

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
	mainDlg->AddString(_T("�����˷���") + CPublic::double2CString(data[1]) + _T(" ") + CPublic::double2CString(data[2]));
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


// CDialogRobot ��Ϣ�������


BOOL CDialogRobot::OnInitDialog()
{
	CDialog::OnInitDialog();

	robot = this;
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


void CDialogRobot::powerdo()
{
	Power_do = 1;
	SendData(POWER_DO, Power_do);
	SendData(ZEROS_DO, Zeros_do, sizeof(Zeros_do));
}

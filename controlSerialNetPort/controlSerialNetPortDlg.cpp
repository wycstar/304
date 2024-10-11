// controlSerialNetPortDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Dialoglogin.h"
#include<string>
#include "controlSerialNetPort.h"
#include "controlSerialNetPortDlg.h"
#include "DlgSerial1.h"
#include "DlgSerial2.h"
#include "DlgSerial3.h"
#include "DlgSerial4.h"
#include "DlgSerial5.h"
#include "DlgSerial6.h"
#include "AutoSettingDlg.h"
#include "IOControl.h"
#include"IO.h"
#include"io.h"
#include <math.h>
#include "DialogCreatProcess.h"
#include "DiailogEditor.h"
#include "DialogRobot.h"
#include "Public.h"


#include "conio.h"

#include "USB3200.h"
#include <iostream>
#include <fstream>
using namespace std;

F64 VoltBuffer[32768];

#undef UNICODE
#define _WIN32_WINNT 0x501
#define WIN32_LEAN_AND_MEAN

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")
// #pragma comment (lib, "Mswsock.lib")
#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "1500"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include "afxwin.h"

#include <atlconv.h>
#include "OPTErrorCode.h"
#pragma comment(lib, "OPTController.lib")



extern CDiailogEditor*pEditor;
extern CDialogRobot*robot;//调用其他类的全局变量
CcontrolSerialNetPortDlg* pMainDlg;
extern CDialoglogin* pDlg;
extern CDialogCreatProcess* pCreateProcess;
extern CFlowChart* pFlow;

USB3200_AI_PARAM AIParam;
USB3200_AI_STATUS AIStatus;
U32 nSizePoints = 4096, nRetPoints = 0;
U32 nReadableSegments = 0;
HANDLE hDevice = INVALID_HANDLE_VALUE;

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

/* User's processing and camera detect hook functions. */
//MIL_INT MFTYPE ProcessingFunction(MIL_INT HookType,
//								  MIL_ID HookId,
//								  void* HookDataPtr);
//MIL_INT MFTYPE CamPresentFunction(MIL_INT HookType,
//								  MIL_ID HookId,
//								  void* HookDataPtr);
//
//void MFTYPE bnProcess(MIL_ID iSystem, MIL_ID iImageBuffer, MIL_ID iOverlay, MIL_ID oImageBuffer);
//
//int SingleModelExample(MIL_ID MilSystem, MIL_ID MilImage, MIL_ID MilOverlayImage, int workNum, PositionInfo* output);
//int CircleFinderExample(MIL_ID MilSystem, MIL_ID MilImage, MIL_ID MilOverlayImage, int workNum, PositionInfo* output);


static UINT ThreadFun(LPVOID lParam);
static UINT ThreadFuninitial(LPVOID lParam);
static void autoWorkProcess(ThreadInfo* Thread_Info);
static void initialWorkProcess(ThreadInfo* Thread_Info);
CCriticalSection critical_section;
//CEvent cevent;

//typedef int(*singleModelMatch)(MIL_ID, MIL_ID, int, int, int, int, int, int, MIL_CONST_TEXT_PTR, double *, double *, double *);
//typedef  返回类型(*新类型)(参数表)  singleModelMatch类型的函数指针，该指针指向一个只带有3个MIL_ID类型、4个int类型、3个double*类型的形参，返回值为int*类型的函数
//typedef int(*CircleFinder)(MIL_ID, MIL_ID, int, int, int, int, int, int, double, double, double*, double *, double *);
//int g_milNum = 0;

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
ON_BN_CLICKED(IDC_BUTTON1, CcontrolSerialNetPortDlg::OnBnClickedLogin)//将第5步的函数与登录按钮ID绑定
END_MESSAGE_MAP()


// CcontrolSerialNetPortDlg 对话框

CcontrolSerialNetPortDlg* mainDlg;


CcontrolSerialNetPortDlg::CcontrolSerialNetPortDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CcontrolSerialNetPortDlg::IDD, pParent)
	,m_LogNum(0)
	, m_Name(_T(""))
	, m_ProcessName1(_T(""))
	, m_initTXT1(_T(""))
	, m_initTXT2(_T(""))
	, m_autoTXT1(_T(""))
	, m_autoTXT2(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_isAuto = true;
	m_settingDlg = NULL;
	m_createprocess = NULL;
	m_editor = NULL;
	m_flowchartdlg = NULL;
	io = NULL;
	m_MILforMatch = NULL;
	m_IOConnect = false;
	//在任何指针变量使用前都初始化，可以避免因误访问重要内存地址而破坏此地址的数据。将m_sensorValue后面3位数置为0
	memset(m_sensorValue, 0, 3);

	for (int i = 0; i < MAX_CAM; i++)
	{
		m_continue[i] = false;
		m_pThread[i] = NULL;
		m_bContinueGrab[i] = false;
		//m_threadInfo[i].robotFinishFlag = false;
	}

	SetAxisParameter();
	for (int i = 0; i < MAX_CAM; i++)
	{
		SetInitAutoParameter(i);
		m_commNum[i] = 0;
		//m_commCount[i] = 0;
		m_fileComm[i] = _T("");
	}

	for (int i = 0; i < portNum; i++)
	{
		//m_fileSteps[i] = 0;
		m_portNum[i] = 0;
	}
	m_LightPortState = false;
	memset(m_LightChannelState, false, LIGHT_CHANNEL_NUM);
	m_bConnect = false;
	SOCKET ListenSocket = INVALID_SOCKET;   //定义并初始化变量listensocket
	SOCKET ClientSocket = INVALID_SOCKET;	//定义并初始化变量clientsocket
	m_SocketState = false;
}


CcontrolSerialNetPortDlg::~CcontrolSerialNetPortDlg()
{
	MilDestroy();
	/*
WaitForSingleObject函数用来检测hHandle事件的信号状态，在某一线程中调用该函数时，线程暂时挂起，
如果在挂起的dwMilliseconds毫秒内，线程所等待的对象变为有信号状态，则该函数立即返回；如果时间已经到达dwMilliseconds毫秒，但hHandle所指向的对象还没有变成有信号状态，函数照样返回。
	*/
	for(int i = 0; i < MAX_CAM; i++)
		if (m_pThread[i] != NULL &&		//检查执行绪是否仍执行中
			::WaitForSingleObject(m_pThread[i]->m_hThread,0) == WAIT_TIMEOUT)
			TerminateThread(m_pThread[i]->m_hThread, 0);

	if (NULL != m_settingDlg)
	{
		delete m_settingDlg;
		m_settingDlg = NULL;
	}

	if (NULL != m_editor)
	{
		// 删除非模态对话框对象   
		delete m_editor;
		m_editor = NULL;
	}
	if (NULL != io)
	{
		// 删除非模态对话框对象   
		delete io;
		io = NULL;
	}
	
		if (NULL != m_MILforMatch)
		{
			// 删除非模态对话框对象   
			delete m_MILforMatch;
			m_MILforMatch = NULL;
		}
	/*if(NULL != m_createprocess)
	{
		delete m_createprocess;
		m_createprocess = NULL;
	}
	*/
}

void CcontrolSerialNetPortDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_light1, m_bstLight[0]);
	DDX_Control(pDX, IDC_BUTTON_light2, m_bstLight[1]);
	DDX_Control(pDX, IDC_BUTTON_light3, m_bstLight[2]);
	DDX_Control(pDX, IDC_BUTTON_light4, m_bstLight[3]);
	DDX_Control(pDX, IDC_BUTTON_light5, m_bstLight[4]);
	DDX_Control(pDX, IDC_BUTTON_light6, m_bstLight[5]);
	DDX_Control(pDX, IDC_BUTTON_light7, m_bstLight[6]);
	DDX_Control(pDX, IDC_BUTTON_light8, m_bstLight[7]);
	DDX_Control(pDX, IDC_BUTTON_light9, m_bstLight[8]);
	DDX_Control(pDX, IDC_BUTTON_light10, m_bstLight[9]);

	/*DDX_Control(pDX, IDC_BUTTON_material3, m_bstMaterial[2]);
	DDX_Control(pDX, IDC_BUTTON_position3, m_bstPostion[2]);
	DDX_Control(pDX, IDC_BUTTON_mirrorO3, m_bstMirrorO[2]);
	DDX_Control(pDX, IDC_BUTTON_lightO3, m_bstLightO[2]);
	DDX_Control(pDX, IDC_BUTTON_picture3, m_bstPicture[2]);
	DDX_Control(pDX, IDC_BUTTON_lightC3, m_bstLightC[2]);
	DDX_Control(pDX, IDC_BUTTON_mirrorC3, m_bstMirrorC[2]);
	DDX_Control(pDX, IDC_BUTTON_XYZposition3, m_bstXYZPostion[2]);
	DDX_Control(pDX, IDC_BUTTON_fit3, m_bstFit[2]);
	DDX_Control(pDX, IDC_BUTTON_dispenser3, m_bstDispenser[2]);*/

	DDX_Control(pDX, IDC_BUTTON_autostart, m_autoStart);
	DDX_Control(pDX, IDC_BUTTON_autostop, m_autoStop);
	DDX_Control(pDX, IDC_BUTTON_autohand, m_switch);
	DDX_Control(pDX, IDC_BUTTON_log, m_logo);
	DDX_Control(pDX, IDC_BUTTON_setting, m_autoSetting);


	DDX_Control(pDX, IDC_LIST_LOG, m_boxlog);

	DDX_Control(pDX, IDC_PROGRESS1, m_progress);
	//DDX_Control(pDX, IDC_PROGRESS2, m_progress[1]);
	DDX_Control(pDX, IDC_COMBO_PORT1, m_cmbPort[0]);
	DDX_Control(pDX, IDC_COMBO_PORT2, m_cmbPort[1]);
	DDX_Control(pDX, IDC_COMBO_PORT3, m_cmbPort[2]);

	DDX_Control(pDX, IDC_BUTTON_Suspend, m_suspend);
	DDX_Control(pDX, IDC_BUTTON_connect, m_bstport);
	DDX_Control(pDX, IDC_BUTTON_initialization, m_initial);
	DDX_Control(pDX, IDC_BUTTON_Continue, m_Continue);

	DDX_Control(pDX, IDC_BUTTON2, m_IOControl);
	//  DDX_Control(pDX, IDC_STATIC2, m_Name);
	//DDX_Control(pDX, IDC_STATIC2, m_Name);
	DDX_Text(pDX, IDC_STATIC2, m_Name);
	//DDX_Text(pDX, IDC_STATIC3, m_ProcessName1);
	//  DDX_Control(pDX, IDC_BUTTON_flowchart, m_flowchart);
	DDX_Control(pDX, IDC_BUTTON_flowchart, m_flowchart);
	//	DDX_Control(pDX, IDC_STATIC011, m_flowIcon11);
	//
	//DDX_Control(pDX, IDC_STATIC021, m_flowIcon21);
	DDX_Control(pDX, IDC_BUTTON_Editor, m_OpenEditor);
	DDX_Control(pDX, IDC_BUTTON_OpenDataBase, m_OpenDataBase);
	//  DDX_Control(pDX, IDC_STATIC_initTXT1, m_initTXT1);
	//  DDX_Control(pDX, IDC_STATIC_autoTXT1, m_autoTXT1);
	//  DDX_Control(pDX, IDC_STATIC_initTXT2, m_initTXT2);
	//  DDX_Control(pDX, IDC_STATIC_autoTXT2, m_autoTXT2);

	DDX_Control(pDX, IDC_BUTTON_light01, m_UnitLight[1]);
	DDX_Control(pDX, IDC_BUTTON_light02, m_UnitLight[2]);
	DDX_Control(pDX, IDC_BUTTON_light03, m_UnitLight[3]);
	DDX_Control(pDX, IDC_BUTTON_light04, m_UnitLight[4]);
	DDX_Control(pDX, IDC_BUTTON_light05, m_UnitLight[5]);
	DDX_Control(pDX, IDC_BUTTON_light06, m_UnitLight[6]);
	DDX_Control(pDX, IDC_BUTTON_light07, m_UnitLight[7]);
	DDX_Control(pDX, IDC_BUTTON_light08, m_UnitLight[8]);
	DDX_Control(pDX, IDC_BUTTON_light09, m_UnitLight[9]);
	DDX_Control(pDX, IDC_BUTTON_light010, m_UnitLight[10]);
	DDX_Control(pDX, IDC_STATIC01, m_UnitName[1]);
	DDX_Control(pDX, IDC_STATIC02, m_UnitName[2]);
	DDX_Control(pDX, IDC_STATIC03, m_UnitName[3]);
	DDX_Control(pDX, IDC_STATIC04, m_UnitName[4]);
	DDX_Control(pDX, IDC_STATIC05, m_UnitName[5]);
	DDX_Control(pDX, IDC_STATIC06, m_UnitName[6]);
	DDX_Control(pDX, IDC_STATIC07, m_UnitName[7]);
	DDX_Control(pDX, IDC_STATIC08, m_UnitName[8]);
	DDX_Control(pDX, IDC_STATIC09, m_UnitName[9]);
	DDX_Control(pDX, IDC_STATIC10, m_UnitName[10]);

	//  DDX_Control(pDX, IDC_BUTTON_light01, m_light01);
	//  DDX_Control(pDX, IDC_BUTTON_light02, m_light02);
	//  DDX_Control(pDX, IDC_BUTTON_light03, m_light03);
	//  DDX_Control(pDX, IDC_BUTTON_light04, m_light04);
	//  DDX_Control(pDX, IDC_BUTTON_light05, m_light05);
	DDX_Text(pDX, IDC_STATIC_initTXT1, m_initTXT1);
	DDX_Text(pDX, IDC_STATIC_initTXT2, m_initTXT2);
	DDX_Text(pDX, IDC_STATIC_autoTXT1, m_autoTXT1);
	DDX_Text(pDX, IDC_STATIC_autoTXT2, m_autoTXT2);
	DDX_Control(pDX, IDC_IPADDRESS2, m_localIP);
}

BEGIN_MESSAGE_MAP(CcontrolSerialNetPortDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_SERIAL1, &CcontrolSerialNetPortDlg::OnBnClickedButtonSerial1)
	ON_MESSAGE(WM_COMM_RXCHAR, OnCommunication)
	ON_MESSAGE(WMU_THREAD_EXIT, OnThreadExit)
	ON_BN_CLICKED(IDC_BUTTON_SERIAL2, &CcontrolSerialNetPortDlg::OnBnClickedButtonSerial2)
	ON_BN_CLICKED(IDC_BUTTON_SERIAL3, &CcontrolSerialNetPortDlg::OnBnClickedButtonSerial3)
	ON_BN_CLICKED(IDC_BUTTON_clear, &CcontrolSerialNetPortDlg::OnBnClickedButtonclear)
	ON_BN_CLICKED(IDC_BUTTON_save, &CcontrolSerialNetPortDlg::OnBnClickedButtonsave)
	ON_BN_CLICKED(IDC_BUTTON_autohand, &CcontrolSerialNetPortDlg::OnBnClickedButtonautohand)
//	ON_BN_CLICKED(IDC_BUTTON_onehand, &CcontrolSerialNetPortDlg::OnBnClickedButtononehand)
//	ON_BN_CLICKED(IDC_BUTTON_twohand, &CcontrolSerialNetPortDlg::OnBnClickedButtontwohand)
//	ON_BN_CLICKED(IDC_BUTTON_threehand, &CcontrolSerialNetPortDlg::OnBnClickedButtonthreehand)
	//ON_BN_CLICKED(IDC_BUTTON_start1, &CcontrolSerialNetPortDlg::OnBnClickedButtonstart1)
	//ON_BN_CLICKED(IDC_BUTTON_mainstop1, &CcontrolSerialNetPortDlg::OnBnClickedButtonmainstop1)
	ON_BN_CLICKED(IDC_BUTTON_start2, &CcontrolSerialNetPortDlg::OnBnClickedButtonstart2)
	//ON_BN_CLICKED(IDC_BUTTON_mainstop2, &CcontrolSerialNetPortDlg::OnBnClickedButtonmainstop2)
//	ON_BN_CLICKED(IDC_BUTTON_start3, &CcontrolSerialNetPortDlg::OnBnClickedButtonstart3)
//	ON_BN_CLICKED(IDC_BUTTON_mainstop3, &CcontrolSerialNetPortDlg::OnBnClickedButtonmainstop3)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON_SERIAL4, &CcontrolSerialNetPortDlg::OnBnClickedButtonSerial4)
	ON_BN_CLICKED(IDC_BUTTON_SERIAL5, &CcontrolSerialNetPortDlg::OnBnClickedButtonSerial5)
	ON_BN_CLICKED(IDC_BUTTON_SERIAL6, &CcontrolSerialNetPortDlg::OnBnClickedButtonSerial6)
//	ON_BN_CLICKED(IDC_BUTTON_SERIAL7, &CcontrolSerialNetPortDlg::OnBnClickedButtonSerial7)
//	ON_BN_CLICKED(IDC_BUTTON_SERIAL8, &CcontrolSerialNetPortDlg::OnBnClickedButtonSerial8)
//	ON_BN_CLICKED(IDC_BUTTON_SERIAL9, &CcontrolSerialNetPortDlg::OnBnClickedButtonSerial9)
	ON_BN_CLICKED(IDC_BUTTON_autostart, &CcontrolSerialNetPortDlg::OnBnClickedButtonautostart)
	ON_BN_CLICKED(IDC_BUTTON_autostop, &CcontrolSerialNetPortDlg::OnBnClickedButtonautostop)
//	ON_BN_CLICKED(IDC_BUTTON_threehand, &CcontrolSerialNetPortDlg::OnBnClickedButtonthreehand)
//ON_BN_CLICKED(IDC_BUTTON_threehand, &CcontrolSerialNetPortDlg::OnBnClickedButtonthreehand)
ON_BN_CLICKED(IDC_BUTTON_setting, &CcontrolSerialNetPortDlg::OnBnClickedButtonsetting)
//ON_CBN_SELCHANGE(IDC_COMBO_PORT1, &CcontrolSerialNetPortDlg::OnCbnSelchangeComboPort1)
//ON_CBN_SELCHANGE(IDC_COMBO_PORT1, &CcontrolSerialNetPortDlg::OnCbnSelchangeComboPort1)
//ON_CBN_SELCHANGE(IDC_COMBO_PORT2, &CcontrolSerialNetPortDlg::OnCbnSelchangeComboPort2)
//ON_BN_CLICKED(IDC_BUTTON1, &CcontrolSerialNetPortDlg::OnBnClickedButton1)
ON_BN_CLICKED(IDC_BUTTON_connect, &CcontrolSerialNetPortDlg::OnBnClickedButtonconnect)
//ON_BN_CLICKED(IDC_BUTTON_fit, &CcontrolSerialNetPortDlg::OnBnClickedButtonfit)
//ON_BN_CLICKED(IDC_BUTTON_dispenser, &CcontrolSerialNetPortDlg::OnBnClickedButtondispenser)
ON_BN_CLICKED(IDC_BUTTON2, &CcontrolSerialNetPortDlg::OnBnClickedButton2)
ON_COMMAND(ID_Fault, &CcontrolSerialNetPortDlg::OnFaultAnalysis)
ON_CBN_SELCHANGE(IDC_COMBO_PORT1, &CcontrolSerialNetPortDlg::OnCbnSelchangeComboPort1)
ON_BN_CLICKED(IDC_BUTTON3, &CcontrolSerialNetPortDlg::OnBnClickedButton3)
ON_STN_CLICKED(IDC_STATIC2, &CcontrolSerialNetPortDlg::OnStnClickedStatic2)
ON_BN_CLICKED(IDC_BUTTON_log, &CcontrolSerialNetPortDlg::OnBnClickedButtonlog)
ON_CBN_SELCHANGE(IDC_COMBO_PORT3, &CcontrolSerialNetPortDlg::OnCbnSelchangeComboPort3)
ON_CBN_SELCHANGE(IDC_COMBO_PORT2, &CcontrolSerialNetPortDlg::OnCbnSelchangeComboPort2)
ON_STN_CLICKED(IDC_DISP1, &CcontrolSerialNetPortDlg::OnStnClickedDisp1)
ON_STN_CLICKED(IDC_DISP2, &CcontrolSerialNetPortDlg::OnStnClickedDisp2)
ON_LBN_SELCHANGE(IDC_LIST_LOG, &CcontrolSerialNetPortDlg::OnLbnSelchangeListLog)
ON_BN_CLICKED(IDC_BUTTON4, &CcontrolSerialNetPortDlg::OnBnClickedButton4)
ON_BN_CLICKED(IDC_BUTTON5, &CcontrolSerialNetPortDlg::OnBnClickedButton5)
ON_BN_CLICKED(IDC_BUTTON8, &CcontrolSerialNetPortDlg::OnBnClickedButton8)
ON_BN_CLICKED(IDC_BUTTON7, &CcontrolSerialNetPortDlg::OnBnClickedButton7)
ON_BN_CLICKED(IDC_BUTTON12, &CcontrolSerialNetPortDlg::OnBnClickedButton12)
ON_COMMAND(ID_OpenData, &CcontrolSerialNetPortDlg::OnOpendata)
ON_COMMAND(ID_RobotTest, &CcontrolSerialNetPortDlg::OnRobottest)
ON_COMMAND(ID_Script, &CcontrolSerialNetPortDlg::OnScript)
ON_COMMAND(ID_Station1, &CcontrolSerialNetPortDlg::OnStation1)
ON_COMMAND(ID_Station2, &CcontrolSerialNetPortDlg::OnStation2)
ON_COMMAND(ID_VisionTest, &CcontrolSerialNetPortDlg::OnVisiontest)
ON_BN_CLICKED(IDC_BUTTON_flowchart, &CcontrolSerialNetPortDlg::OnBnClickedButtonflowchart)
ON_BN_CLICKED(IDC_BUTTON15, &CcontrolSerialNetPortDlg::OnBnClickedButton15)
ON_BN_CLICKED(IDC_BUTTON_Editor, &CcontrolSerialNetPortDlg::OnBnClickedButtonEditor)
ON_BN_CLICKED(IDC_BUTTON_OpenDataBase, &CcontrolSerialNetPortDlg::OnBnClickedButtonOpendatabase)
ON_BN_CLICKED(IDC_BUTTON_ChangeinitTXT1, &CcontrolSerialNetPortDlg::OnBnClickedButtonChangeinittxt1)
//ON_BN_CLICKED(IDC_BUTTON_ChangeTXT1, &CcontrolSerialNetPortDlg::OnBnClickedButtonChangetxt1)
ON_BN_CLICKED(IDC_BUTTON_ChangeinitTXT2, &CcontrolSerialNetPortDlg::OnBnClickedButtonChangeinittxt2)
//ON_BN_CLICKED(IDC_BUTTON_ChangeTXT2, &CcontrolSerialNetPortDlg::OnBnClickedButtonChangetxt2)
ON_BN_CLICKED(IDC_BUTTON_ChangeautoTXT1, &CcontrolSerialNetPortDlg::OnBnClickedButtonChangeautotxt1)
ON_BN_CLICKED(IDC_BUTTON_ChangeautoTXT2, &CcontrolSerialNetPortDlg::OnBnClickedButtonChangeautotxt2)
ON_STN_CLICKED(IDC_STATIC04, &CcontrolSerialNetPortDlg::OnStnClickedStatic04)
ON_BN_CLICKED(IDC_BUTTON_light06, &CcontrolSerialNetPortDlg::OnBnClickedButtonlight06)
ON_BN_CLICKED(IDC_BUTTON_Suspend, &CcontrolSerialNetPortDlg::OnBnClickedButtonSuspend)
ON_BN_CLICKED(IDC_BUTTON_initialization, &CcontrolSerialNetPortDlg::OnBnClickedButtoninitialization)
ON_BN_CLICKED(IDC_Forcecontrol, &CcontrolSerialNetPortDlg::OnBnClickedForcecontrol)
ON_BN_CLICKED(IDC_BUTTON_sc, &CcontrolSerialNetPortDlg::OnBnClickedButtonsc)
ON_BN_CLICKED(IDC_BUTTON_stopcatch, &CcontrolSerialNetPortDlg::OnBnClickedButtonstopcatch)
ON_NOTIFY(NM_CUSTOMDRAW, IDC_PROGRESS1, &CcontrolSerialNetPortDlg::OnCustomdrawProgress1)
ON_NOTIFY(NM_OUTOFMEMORY, IDC_PROGRESS1, &CcontrolSerialNetPortDlg::OnOutofmemoryProgress1)
ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_PROGRESS1, &CcontrolSerialNetPortDlg::OnReleasedcaptureProgress1)
ON_NOTIFY(NM_THEMECHANGED, IDC_PROGRESS1, &CcontrolSerialNetPortDlg::OnThemechangedProgress1)
ON_BN_CLICKED(IDC_BUTTON_ChangeautoTXT3, &CcontrolSerialNetPortDlg::OnBnClickedButtonChangeautotxt3)
ON_STN_CLICKED(IDC_STATIC_autoTXT3, &CcontrolSerialNetPortDlg::OnStnClickedStaticautotxt3)
END_MESSAGE_MAP()


// CcontrolSerialNetPortDlg 消息处理程序

BOOL CcontrolSerialNetPortDlg::OnInitDialog()//初始化函数
{
	CDialog::OnInitDialog();
	
	pMainDlg = this;
	m_initTXT1 = L"initWork1.txt";	//取文件名称。
	m_initTXT2 = L"initWork2.txt";	//取文件名称。
	m_autoTXT1 = L"autoWork1.txt";	//取文件名称。
	m_autoTXT2 = L"autoWork2.txt";	//取文件名称。
    UpdateData(FALSE);

	GetDlgItem(IDC_STATIC2)->SetWindowText(pDlg->m_name);

	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_bbtn.AutoLoad(IDC_BUTTON4, this);

	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	mainDlg = this;

	m_Menu.LoadMenuW(IDR_MENU1);
	SetMenu(&m_Menu);

	CRect rect;
	//GetDlgItem(IDC_OSCOPE)->GetWindowRect(rect);
	//ScreenToClient(rect);
	//m_OScopeCtrl.Create(WS_VISIBLE | WS_CHILD, rect, this);
	////customize the control
	//m_OScopeCtrl.SetRange(20.0, 100.0, 0.01);
	//m_OScopeCtrl.SetYUnits(_T("Force"));
	//m_OScopeCtrl.SetXUnits(_T("Samples (Windows Timer: 1 msec)"));
	//m_OScopeCtrl.SetBackgroundColor(RGB(180, 180, 180));
	//m_OScopeCtrl.SetGridColor(RGB(192, 192, 255));
	//m_OScopeCtrl.SetPlotColor(RGB(255, 255, 255));

	m_localIP.SetWindowText(_T("192.168.0.131"));//初始化ip


	if (io == NULL)//实例化类
	{
		io = new CIO();
	}
	if (m_MILforMatch == NULL)//实例化类
	{
		m_MILforMatch = new MILforMatch();
	}
	InitUI();//函数
	//InitWorkStation();
	
	//将控件上显示上的数据更新到关联变量
	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CcontrolSerialNetPortDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CcontrolSerialNetPortDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CcontrolSerialNetPortDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CcontrolSerialNetPortDlg::OnBnClickedButtonSerial1()
{
	int port = portNum3;
	int axises[] = {axis3, axis6};

	if (CPublic::portIsOpen[port - 1] == false)
	{
		CString str;
		str.Format(_T("串口%d 未打开!"), port);
		AfxMessageBox(str);
		return;
	}
	
	CDlgSerial1 m_DlgSerial1(NULL, &port, axises);
	INT_PTR nResponse = m_DlgSerial1.DoModal();

	if (nResponse == IDOK)
	{
	}
	else if (nResponse == IDCANCEL)
	{
	}

	UpdateData(TRUE);
}


int  CcontrolSerialNetPortDlg::GetPortIndex(int port)
{
	for (int i = 0; i < portNum; i++)
	{
		if (port == m_portNum[i])
		{
			return i;
		}
	}
	return -1;

}

LRESULT  CcontrolSerialNetPortDlg::OnCommunication(WPARAM ch, LPARAM port)
{
	UpdateData(true);
	int i = GetPortIndex(port);
	if (i == -1)
	{
		AddString(_T("无此串口？"));//AddString(LPCTSTR lpszString) 是在列表框的尾巴添加一条数据,参数为字符串. 
		return 0;
	}

	if (CPublic::startReceive[i] == false)
	{
		CPublic::receiveData[i] = _T("");
		memset(m_StopRec[i], 0, 6);
		CPublic::bfindTerminator[i] = false;
		CPublic::startReceive[i] = true;
	}


	CString temp = CPublic::char2CString((char*)&ch, 1);
	CPublic::receiveData[i] += temp;

	if (i == 2)
	{
		if (CPublic::receiveData[i] != _T(""))
		{
			AddString(_T("金丝球焊COM") + CPublic::int2CString(port) + _T(" receive: ") + CPublic::receiveData[i]);
			CPublic::bfindTerminator[i] = true;
			CPublic::startReceive[i] = false;	
		}
	}else
	{
		//find terminator	
		if(findTerminator(ch, m_StopRec[i]) == true)
		{
			CPublic::receiveData[i] = CPublic::receiveData[i].Mid(0, CPublic::receiveData[i].GetLength());
			AddString(_T("COM") + CPublic::int2CString(port) + _T(" receive: ") + CPublic::receiveData[i]);
			CPublic::bfindTerminator[i] = true;
			CPublic::startReceive[i] = false;	

		}	
	}

	//if (i == 0 || i == 1 || i == 6)
	//{
	//	//find terminator	
	//	if(findSpecialTerminator(ch, m_StopRec[i]) == true)
	//	{
	//		CPublic::receiveData[i] = CPublic::receiveData[i].Left(CPublic::receiveData[i].GetLength() - 6);
	//		AddString(CPublic::int2CString(port) + _T("receive: ") + CPublic::receiveData[i]);
	//		CPublic::bfindTerminator[i] = true;
	//		CPublic::startReceive[i] = false;

	//	}	
	//}else
	//{
	//	
	//}

	
	return 0;
}
void CcontrolSerialNetPortDlg::InitUI(void)//初始化函数
{
	//init port
	//initPort();//初始化串口函数
	//init indication button
	for (int i = 0; i < UILIGHT_NUM; i++)
		{
			m_bstLight[i].SetIcon(IDI_ICON_Cgrey24);
			m_bstLight[i].DrawBorder(FALSE);
		}
	for (int k = 0; k < UNITLIGHT_NUM; k++)
	{
		m_UnitLight[k].SetIcon(IDI_ICON_Cgrey24);
		m_UnitLight[k].DrawBorder(FALSE);
	}

	

	//m_bstMaterial[2].SetIcon(IDI_ICON_Cgrey24);
	//m_bstPostion[2].SetIcon(IDI_ICON_Cgrey24);
	//m_bstMirrorO[2].SetIcon(IDI_ICON_Cgrey24);
	//m_bstLightO[2].SetIcon(IDI_ICON_Cgrey24);
	//m_bstPicture[2].SetIcon(IDI_ICON_Cgrey24);
	//m_bstLightC[2].SetIcon(IDI_ICON_Cgrey24);
	//m_bstMirrorC[2].SetIcon(IDI_ICON_Cgrey24);
	//m_bstXYZPostion[2].SetIcon(IDI_ICON_Cgrey24);
	//m_bstFit[2].SetIcon(IDI_ICON_Cgrey24);
	//m_bstDispenser[2].SetIcon(IDI_ICON_Cgrey24);

	/*m_bstMaterial[2].DrawBorder(FALSE);
	m_bstPostion[2].DrawBorder(FALSE);
	m_bstMirrorO[2].DrawBorder(FALSE);
	m_bstLightO[2].DrawBorder(FALSE);
	m_bstPicture[2].DrawBorder(FALSE);
	m_bstLightC[2].DrawBorder(FALSE);
	m_bstMirrorC[2].DrawBorder(FALSE);
	m_bstXYZPostion[2].DrawBorder(FALSE);
	m_bstFit[2].DrawBorder(FALSE);
	m_bstDispenser[2].DrawBorder(FALSE);*/

	m_OpenEditor.SetIcon(IDI_ICON_Editor);
	m_OpenEditor.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_OpenEditor.SetTooltipText(_T("自动装配流程的智能编辑器"));

	m_OpenDataBase.SetIcon(IDI_ICON_OpenDataBase);
	m_OpenDataBase.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_OpenDataBase.SetTooltipText(_T("打开系统数据库"));


	m_flowchart.SetIcon(IDI_ICON_flowchart);
	m_flowchart.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_flowchart.SetTooltipText(_T("图形化仿真自动流程"));

	m_autoStart.SetIcon(IDI_ICON_startb);
	//m_autoStart.DrawBorder(FALSE);
	m_autoStart.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_autoStart.SetTooltipText(_T("启动自动装配流程"));

	//GetDlgItem(IDC_BUTTON_autostart)->EnableWindow(TRUE); 

	m_suspend.SetIcon(IDI_ICON_suspendgrey);
	//m_autoStop.DrawBorder(FALSE);
	m_suspend.SetAlign(CButtonST::ST_ALIGN_VERT);
	//GetDlgItem(IDC_BUTTON_autostop)->EnableWindow(FALSE); 
	m_suspend.SetTooltipText(_T("暂停自动装配流程"));

	m_Continue.SetIcon(IDI_ICON_Continuegrey);
	//m_autoStop.DrawBorder(FALSE);
	m_Continue.SetAlign(CButtonST::ST_ALIGN_VERT);
	//GetDlgItem(IDC_BUTTON_autostop)->EnableWindow(FALSE); 
	m_Continue.SetTooltipText(_T("继续进行自动装配"));



	m_initial.SetIcon(IDI_ICON_initialyellow);
	//m_autoStop.DrawBorder(FALSE);
	m_initial.SetAlign(CButtonST::ST_ALIGN_VERT);
	//GetDlgItem(IDC_BUTTON_autostop)->EnableWindow(FALSE); 
	m_initial.SetTooltipText(_T("初始化自动装配系统"));




	m_autoStop.SetIcon(IDI_ICON_stopg);
	//m_autoStop.DrawBorder(FALSE);
	m_autoStop.SetAlign(CButtonST::ST_ALIGN_VERT);
	//GetDlgItem(IDC_BUTTON_autostop)->EnableWindow(FALSE); 
	m_autoStop.SetTooltipText(_T("停止自动装配流程"));//鼠标移动至此便显示提示


	m_switch.SetIcon(IDI_ICON_switch);
	//m_switch.DrawBorder(FALSE);
	m_switch.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_switch.SetTooltipText(_T("工位自动手动设置切换"));

	m_IOControl.SetIcon(IDI_ICON_IOyellow);
	m_IOControl.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_IOControl.SetTooltipText(_T("IO参数设置"));

	m_autoSetting.SetIcon(IDI_ICON_setting);
	//m_switch.DrawBorder(FALSE);
	m_autoSetting.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_autoSetting.SetTooltipText(_T("自动装配流程参数设置"));

	m_bstport.SetFocus();
	m_bstport.SetIcon(IDI_ICON_DISCONNECT);
	//m_switch.DrawBorder(FALSE);
	m_bstport.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_bstport.SetTooltipText(_T("串口未打开，请打开串口"));//在控件上显示提示信息 

	m_logo.SetIcon(IDI_ICON_log48);
	m_logo.DrawBorder(FALSE);
	//m_logo.SetAlign(CButtonST::ST_ALIGN_VERT);

	//初始化日志显示
	m_boxlog.InitStorage(200000, 200000*1024);//日志列表关联的变量m_boxlog
	m_boxlog.SetHorizontalExtent(10000);

	//enable auto or hand
	if (m_isAuto == true)
	{
//		((CButton*)GetDlgItem(IDC_BUTTON_SERIAL1))->EnableWindow(FALSE);
//		((CButton*)GetDlgItem(IDC_BUTTON_SERIAL2))->EnableWindow(FALSE);
//		((CButton*)GetDlgItem(IDC_BUTTON_SERIAL3))->EnableWindow(FALSE);
	
//		((CButton*)GetDlgItem(IDC_BUTTON_SERIAL4))->EnableWindow(FALSE);
//		((CButton*)GetDlgItem(IDC_BUTTON_SERIAL5))->EnableWindow(FALSE);
//		((CButton*)GetDlgItem(IDC_BUTTON_SERIAL6))->EnableWindow(FALSE);
	
//		((CButton*)GetDlgItem(IDC_BUTTON_SERIAL7))->EnableWindow(FALSE);
//		((CButton*)GetDlgItem(IDC_BUTTON_SERIAL8))->EnableWindow(FALSE);
//		((CButton*)GetDlgItem(IDC_BUTTON_SERIAL9))->EnableWindow(FALSE);
	}

	//initial mil variantsM_DEFAULT
	//MappAlloc(M_DEFAULT, &MilApplication);		
	//MsysAlloc(M_SYSTEM_GIGE_VISION, M_DEFAULT, M_DEFAULT, &MilSystem);
	//MilCreate();//启动mil？？
	/* Register a hook function to the system's camera present event. */
	/* Used to:                                                        */
	/* 1- Allocate and start acquisition on a newly attached camera.   */
	/* 2- Stop acquisition on a camera that has been removed.          */
	/* 3- Resume acquisition on a camera that has been re-connected.   */
	//MsysHookFunction(MilSystem, M_CAMERA_PRESENT, CamPresentFunction, &SysUserHookData);


	//maximize dialog
	//ShowWindow(SW_SHOWMAXIMIZED);

	//init progress
	//for (int i = 0; i < MAX_CAM; i++)
	//{
		//m_progress[i].SetRange(0, m_commNum[i]);
		m_progress.SetPos(0);
		m_progress.SetStep(1);
	//}

		//initial mil variantsM_DEFAULT
	//MappAlloc(M_DEFAULT, &MilApplication);		
	//MsysAlloc(M_SYSTEM_GIGE_VISION, M_DEFAULT, M_DEFAULT, &MilSystem);
		MilCreate();
		/* Register a hook function to the system's camera present event. */
		/* Used to:                                                        */
		/* 1- Allocate and start acquisition on a newly attached camera.   */
		/* 2- Stop acquisition on a camera that has been removed.          */
		/* 3- Resume acquisition on a camera that has been re-connected.   */
		MsysHookFunction(MilSystem, M_CAMERA_PRESENT, CamPresentFunction, &SysUserHookData);

		//maximize dialog
		//ShowWindow(SW_SHOWMAXIMIZED);

}

void CcontrolSerialNetPortDlg::OnBnClickedButtonSerial2()
{
	int port[] = {portNum3, portNum1};
	int axises[] = {axis1, axis2, axis9};
	for (int i = 0; i < 2; i++)
	{
		if (CPublic::portIsOpen[port[i]-1] == false)
		{
			CString str = _T("串口") + CPublic::int2CString(port[i]) + _T("未打开！");
			AfxMessageBox(str);
			return;
		}
	}

	CDlgSerial2 m_DlgSerial2(NULL, port, axises);
	INT_PTR nResponse = m_DlgSerial2.DoModal();

	if (nResponse == IDOK)
	{
	}
	else if (nResponse == IDCANCEL)
	{
	}

	UpdateData(TRUE);
}

void CcontrolSerialNetPortDlg::OnBnClickedButtonSerial3()
{
	int axises[] = {axis4, axis5, axis7, axis8};
	int port = portNum3;

	if (CPublic::portIsOpen[port-1] == false)
	{
		CString str = _T("串口") + CPublic::int2CString(port) + _T("未打开！");
		AfxMessageBox(str);
		return;
	}


	CDlgSerial3 m_DlgSerial3(NULL, &port, axises);
	INT_PTR nResponse = m_DlgSerial3.DoModal();

	if (nResponse == IDOK)
	{
	}
	else if (nResponse == IDCANCEL)
	{
	}

	UpdateData(TRUE);
}

void CcontrolSerialNetPortDlg::sendComm(CString comm, int portIndex)//--------------------------------向端口发送指令的最底层函数，第一个参数是发送的指令，第二个参数是端口
{
	//UpdateData();
	/*if (port == portNum3)
	{
	}*/
	//critical_section.Lock();


	if ( CPublic::portIsOpen[portIndex] == false)//若端口已打开
	{
		AddString(_T("该串口未打开，请先打开串口！"));
		return;
	}

	comm.Replace(_T("--"), _T(""));//执行替换操作--换成空字符？？
	

	int len = comm.GetLength() + 2;
	char* commDate = new char[len];
	CPublic::CString2char(comm, commDate);
	commDate[len - 2] = 0x0D;
	commDate[len - 1] = 0x0A;

	CPublic::isSend[portIndex] = false;
	serialPort[portIndex].WriteToPort(commDate, len);

	AddString(CPublic::int2CString(m_portNum[portIndex]) + _T("send: ") + comm);
	delete[] commDate;

	//Sleep(initFindTime);
	/*if (port == portNum3)
	{
	}*/
	//critical_section.Unlock();


}

void CcontrolSerialNetPortDlg::sendComm(int devNum, CString comm, int portIndex)
{

	CString str = CPublic::int2CString(devNum) + _T("->");
	str = str + comm;

	sendComm(str, portIndex);
}

void CcontrolSerialNetPortDlg::sendComm(int devNum, CString comm, int axisNum, int portIndex)
{
	CString str = CPublic::int2CString(devNum) + _T("->");
	str = str + comm + _T(" ") + CPublic::int2CString(axisNum);
	sendComm(str, portIndex);
}

void CcontrolSerialNetPortDlg::sendSingleComm(CString comm, int portIndex)
{
	//do 
	//{
	//	sendComm(comm, port);
	//} while (CPublic::isSend[port - 1] == false || CPublic::receiveData[port - 1] != comm);

	int count = 0;

	do 
	{
		sendComm(comm, portIndex);
		Sleep(initFindTime);
		count++;
		if (count == 100)
		{
			AddString(_T("指令发送过去无返回数据？"));
			return;
		}
	} while (CPublic::receiveData[portIndex] != comm);

}

int CcontrolSerialNetPortDlg::sendAnySingleComm(int devNum, CString comm, int axisNum, int ivalue, bool existValue, int portIndex, bool* isContinue)
{
	CString str = CPublic::int2CString(devNum) + _T("->");
	str = str + comm + _T(" ") + CPublic::int2CString(axisNum);

	if (existValue)
	{
		str = str  + _T(" ") + CPublic::int2CString(ivalue);
	}
	int count = 0;
	do 
	{
		if (*isContinue == false)
			return 0;

		sendComm(str, portIndex);
		Sleep(initFindTime);

		count++;
		if (count == 100)
		{
			AddString(_T("指令发送过去无返回数据？"));
			return 0;
		}

	} while ((CPublic::bfindTerminator[portIndex] != true));
	return 1;
}

int CcontrolSerialNetPortDlg::sendAnySingleComm(int devNum, CString comm, int portIndex, bool* isContinue)
{
	CString str = CPublic::int2CString(devNum) + _T("->");
	str = str + comm;
	int count = 0;
	do 
	{
		if (*isContinue == false)
			return 0;

		sendComm(str, portIndex);
		Sleep(initFindTime);
		count++;
		if (count == 100)
		{
			AddString(_T("指令发送过去无返回数据？"));
			return 0;
		}

	} while ((CPublic::bfindTerminator[portIndex] != true));
	return 1;
}

int CcontrolSerialNetPortDlg::sendAnySingleComm(CString comm, int portIndex, bool* isContinue)//向端口发送指令函数（1.2.1.2.1.1）
{
	int count = 0;
	do 
	{
		if (*isContinue == false)
			return 0;

		sendComm(comm, portIndex);//发送指令，将第二行字符发送到相应的端口
		Sleep(initFindTime);
		count++;
		if (count == 100)//发一百次之后一直没有返回？？
		{
			AddString(_T("指令发送过去无返回数据？"));
			return 0;
		}
	} 
	while ((CPublic::bfindTerminator[portIndex] != true));

	return 1;

}




void CcontrolSerialNetPortDlg::AddString(CString msg)    //向日志列表添加日志
{
	CTime tt = CTime::GetCurrentTime();
	CString strTime2 = tt.Format("%H:%M:%S ");
	msg =  strTime2 + msg;
	if (msg.GetLength() > 10000)
	{
		//left函数
		//函数执行成功时返回string字符串左边n个字符，发生错误时返回空字符串（""）。如果任何参数的值为NULL，Left()函数返回NULL。
		//如果n的值大于string字符串的长度，那么Left()函数返回整个string字符串，但并不增加其它字符。
		if (m_boxlog.AddString(msg.Left(10000)) == LB_ERRSPACE)//列表框中字符串的基于零的索引。如果出错，则返回LB_ERR;如果没有足够的有效空间存储新字符串，则为LB_ERRSPACE。
		{
			m_boxlog.InsertString(m_LogNum % 200000, msg.Left(10000));
		}
	}
	else if(m_boxlog.AddString(msg) == LB_ERRSPACE)
	{
		m_boxlog.InsertString(m_LogNum % 200000, msg);
	}
	m_LogNum++;
	//添加日志到列表中	
	//更新
	//UpdateData(FALSE);	
	//将滚动条置于最下面
	m_boxlog.SetTopIndex(m_LogNum % 200000 - 1);
}

void CcontrolSerialNetPortDlg::OnBnClickedButtonclear()//清理日志列表
{
	//获取条目数量
	int count = m_boxlog.GetCount();
	//逐个删除
	for( int i = count -1; i>= 0; i -- )
	{
		m_boxlog.DeleteString(i);
	}
	m_LogNum = 0;
	//更新
	UpdateData(FALSE);
}

void CcontrolSerialNetPortDlg::OnBnClickedButtonsave()//保存日志列表
{
	CFileDialog dlg(FALSE, _T(".log"), _T("测试日志"),OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,_T("日志文件(*.log)|*.log||)"),NULL);
	if (dlg.DoModal() == IDOK)
	{
		CString szFileName = dlg.GetPathName();
		CStdioFile file;
		if (FALSE == file.Open( szFileName, CFile::modeCreate| CFile::modeWrite | CFile::typeText ))
			return;
		int Count = m_boxlog.GetCount();
		//逐行写入日志
		for(int i = 0; i < Count; i++)
		{
			CString line;
			m_boxlog.GetText(i, line);
			file.WriteString(line+_T("\r\n"));
		}
	}
}

void CcontrolSerialNetPortDlg::OnBnClickedButtonautohand()
{
	if (m_isAuto == true)
	{
		for (int i = 0; i < MAX_CAM; i++)
		{
			if (m_continue[i] == true)
			{
				AfxMessageBox(_T("请先停止自动流程后再切换手动"));
				return;
			}
		}
		//enablewindow允许接收键盘鼠标输入
		((CButton*)GetDlgItem(IDC_BUTTON_SERIAL1))->EnableWindow(TRUE);
		((CButton*)GetDlgItem(IDC_BUTTON_SERIAL2))->EnableWindow(TRUE);
		((CButton*)GetDlgItem(IDC_BUTTON_SERIAL3))->EnableWindow(TRUE);

		((CButton*)GetDlgItem(IDC_BUTTON_SERIAL4))->EnableWindow(TRUE);
		((CButton*)GetDlgItem(IDC_BUTTON_SERIAL5))->EnableWindow(TRUE);
		((CButton*)GetDlgItem(IDC_BUTTON_SERIAL6))->EnableWindow(TRUE);

//		((CButton*)GetDlgItem(IDC_BUTTON_SERIAL7))->EnableWindow(TRUE);
//		((CButton*)GetDlgItem(IDC_BUTTON_SERIAL8))->EnableWindow(TRUE);
//		((CButton*)GetDlgItem(IDC_BUTTON_SERIAL9))->EnableWindow(TRUE);

		/*m_autoStart.EnableWindow(FALSE);
		m_autoStop.EnableWindow(FALSE);*/
		m_autoStart.SetIcon(IDI_ICON_startg);
		m_autoStop.SetIcon(IDI_ICON_stopg);

		m_isAuto = false;

	}else
	{
		((CButton*)GetDlgItem(IDC_BUTTON_SERIAL1))->EnableWindow(FALSE);
		((CButton*)GetDlgItem(IDC_BUTTON_SERIAL2))->EnableWindow(FALSE);
		((CButton*)GetDlgItem(IDC_BUTTON_SERIAL3))->EnableWindow(FALSE);
		

		((CButton*)GetDlgItem(IDC_BUTTON_SERIAL4))->EnableWindow(FALSE);
		((CButton*)GetDlgItem(IDC_BUTTON_SERIAL5))->EnableWindow(FALSE);
		((CButton*)GetDlgItem(IDC_BUTTON_SERIAL6))->EnableWindow(FALSE);
		
//		((CButton*)GetDlgItem(IDC_BUTTON_SERIAL7))->EnableWindow(FALSE);
//		((CButton*)GetDlgItem(IDC_BUTTON_SERIAL8))->EnableWindow(FALSE);
//		((CButton*)GetDlgItem(IDC_BUTTON_SERIAL9))->EnableWindow(FALSE);


		/*m_autoStart.EnableWindow(TRUE);
		m_autoStop.EnableWindow(TRUE);*/
		m_autoStart.SetIcon(IDI_ICON_startb);
		m_autoStop.SetIcon(IDI_ICON_stopg);

		m_isAuto = true;
	}



}

//void CcontrolSerialNetPortDlg::OnBnClickedButtononehand()
//{
//	if (isAuto[0] == true)
//	{
//		((CButton*)GetDlgItem(IDC_BUTTON_SERIAL1))->EnableWindow(TRUE);
//		((CButton*)GetDlgItem(IDC_BUTTON_SERIAL2))->EnableWindow(TRUE);
//		((CButton*)GetDlgItem(IDC_BUTTON_SERIAL3))->EnableWindow(TRUE);
//		isAuto[0] = false;
//	}
//}

//void CcontrolSerialNetPortDlg::OnBnClickedButtontwohand()
//{
//	if (isAuto[1] == true)
//	{
//		((CButton*)GetDlgItem(IDC_BUTTON_SERIAL4))->EnableWindow(TRUE);
//		((CButton*)GetDlgItem(IDC_BUTTON_SERIAL5))->EnableWindow(TRUE);
//		((CButton*)GetDlgItem(IDC_BUTTON_SERIAL6))->EnableWindow(TRUE);
//		isAuto[1] = false;
//	}
//}

//void CcontrolSerialNetPortDlg::OnBnClickedButtonthreehand()
//{
//	if (isAuto[2] == true)
//	{
//		((CButton*)GetDlgItem(IDC_BUTTON_SERIAL7))->EnableWindow(TRUE);
//		((CButton*)GetDlgItem(IDC_BUTTON_SERIAL8))->EnableWindow(TRUE);
//		((CButton*)GetDlgItem(IDC_BUTTON_SERIAL9))->EnableWindow(TRUE);
//		isAuto[2] = false;
//	}
//}

bool CcontrolSerialNetPortDlg::findTerminator(char ch, char* stop)
{
	stop[0] = stop[1];
	stop[1] = ch;

	char term[2] = {0x0D, 0x0A};
	//memcmp把存储区 str1 和存储区 str2 的前 n 个字节进行比较
	/*
	如果返回值 < 0，则表示 str1 小于 str2。
	如果返回值 > 0，则表示 str2 小于 str1。
	如果返回值 = 0，则表示 str1 等于 str2。
	*/
	if (memcmp(stop, term, 2) == 0)
		return true;
	else
		return false;

}

bool CcontrolSerialNetPortDlg::findSpecialTerminator(char ch, char* stop)
{

	for (int i = 0; i < 5; i++)
	{
		stop[i] = stop[i+1];
	}
	stop[5] = ch;

	char term[] = {0x0D, 0x0A, 0x2D, 0x2D, 0x3E, 0x0A};

	if (memcmp(stop, term, 6) == 0)
		return true;
	else
		return false;

}

//void CcontrolSerialNetPortDlg::MilCreate()
//{	
//	MIL_INT BoardType, DevNb;
//
//	memset(&SysUserHookData, 0, sizeof(SysUserHookData));
//	memset(DigUserHookData, 0, sizeof(DigHookDataStruct)*MAX_CAM);
//
//	/* Allocate defaults. */
//	MappAlloc(M_DEFAULT, &MilApplication);		
//	MsysAlloc(M_SYSTEM_GIGE_VISION, M_DEFAULT, M_DEFAULT, &MilSystem);
//
//	SysUserHookData.MilSystem = MilSystem;
//	SysUserHookData.NbCameras = 0;
//	SysUserHookData.DigHookDataStrutPtr = DigUserHookData;
//
//	MsysInquire(MilSystem, M_BOARD_TYPE, &BoardType);
//
//	if(((BoardType & M_BOARD_TYPE_MASK) != M_GIGE_VISION))
//	{
//		AddString(_T("This example requires a M_GIGE_VISION system type."));
//		AddString(_T("Please change system type in milconfig."));
//		MappFreeDefault(MilApplication, MilSystem, M_NULL, M_NULL, M_NULL);
//		return;
//	}
//
//	/* Inquire the number of cameras attached. */
//	MsysInquire(MilSystem, M_NUM_CAMERA_PRESENT, &SysUserHookData.NbCameras);
//	if(SysUserHookData.NbCameras > MAX_CAM)
//		SysUserHookData.NbCameras = MAX_CAM;
//
//	/* Allocate and start acquisition on all cameras found at MsysAlloc time. */
//	if(SysUserHookData.NbCameras)
//	{
//		/* Allocate digitizers and other resources. */
//		for(DevNb = M_DEV0; DevNb < MAX_CAM; DevNb++)
//		{
//			if (DevNb == M_DEV0)
//				DigAllocResources(MilSystem, DevNb, IDC_DISP1, &DigUserHookData[DevNb], false);
//			else if (DevNb == M_DEV1)
//			{
//				DigAllocResources(MilSystem, DevNb, IDC_DISP2, &DigUserHookData[DevNb], false);
//			}
//			/*else if (DevNb == M_DEV2)
//			{
//				DigAllocResources(MilSystem, DevNb, IDC_DISP3, &DigUserHookData[DevNb], false);
//			}*/
//
//			
//			if(DigUserHookData[DevNb].MilDigitizer)
//				AddAdapterToList(&SysUserHookData, DigUserHookData[DevNb].pAdapterName);
//
//
//			if(DigUserHookData[DevNb].MilDisplay)
//			{
//				MdispControl(DigUserHookData[DevNb].MilDisplay, M_OVERLAY, M_ENABLE);               /*开启注释层*/				
//			}
//
//		}
//	}
//
//	
//
//
//}

/* Allocates digitizer plus all other resources needed for image acquisition and */
/* camera state changes.                                                         */
/* ------------------------------------------------------------------------------*/

//void CcontrolSerialNetPortDlg::DigAllocResources(MIL_ID MilSystem, MIL_INT DeviceNum, int WindowID, DigHookDataStruct* UserSt,
//					   bool PrintErrors)
//{
//	MIL_INT VendorStLen, ModelStLen, MacStLen;
//	MIL_INT64 PixFmt = 0;
//	MIL_INT SizeBand = 0, BufType = 0;
//	MIL_INT64 BufFormat = M_PROC;
//
//	/* In cases where the preferred method for device allocation requires allocating with     */
//	/* a user-defined name the following code can be used. "MyCameraName" must be replaced    */
//	/* with the actual camera name written in the camera.                                     */
//
//	/* MIL_TEXT_CHAR MyCameraName[64] = {'\0'};                                               */
//
//	/* MosSprintf(MyCameraName, 64, MIL_TEXT("MyCameraName%d"), DeviceNum);                   */
//	/* MdigAlloc(MilSystem, M_GC_CAMERA_ID(MIL_TEXT("MyCameraName")), MIL_TEXT("M_DEFAULT"),  */
//	/*    M_GC_DEVICE_USER_NAME, &MilDigitizer);                                              */
//
//	if(PrintErrors)
//		MdigAlloc(MilSystem, DeviceNum, MIL_TEXT("M_DEFAULT"), M_DEV_NUMBER,
//		&UserSt->MilDigitizer);
//	else
//	{
//		MappControl(M_DEFAULT, M_ERROR, M_PRINT_DISABLE);
//		MdigAlloc(MilSystem, DeviceNum, MIL_TEXT("M_DEFAULT"), M_DEV_NUMBER,
//			&UserSt->MilDigitizer);
//		MappControl(M_DEFAULT, M_ERROR, M_PRINT_ENABLE);
//	}
//
//	if(UserSt->MilDigitizer)
//	{
//		MIL_INT Len = 0;
//		UserSt->MilSystem = MilSystem;
//		UserSt->IsConnected = true;
//		UserSt->IsContinueGrab = false;
//
//		/* Disable MdigProcess grab monitor since disconnecting a camera will result in an  */
//		/* error message.                                                                   */
//		MdigControl(UserSt->MilDigitizer, M_PROCESS_GRAB_MONITOR, M_DISABLE);//MdigControl（）；改变指定的图采卡属性
//		/* Disable corrupted frame errors as they are handled from the MdigProcess hook     */
//		/* function.                                                                        */
//		MdigControl(UserSt->MilDigitizer, M_CORRUPTED_FRAME_ERROR, M_DISABLE);
//
//		/* Inquire information related to the camera being allocated. */
//		MdigInquire(UserSt->MilDigitizer, M_CAMERA_VENDOR_SIZE, &VendorStLen);//MdigInquire（）；获取指定的采集卡配置情况
//		MdigInquire(UserSt->MilDigitizer, M_CAMERA_MODEL_SIZE, &ModelStLen);
//		MdigInquire(UserSt->MilDigitizer, M_GC_PACKET_SIZE, &UserSt->PacketSize);
//		MdigInquire(UserSt->MilDigitizer, M_GC_INTERFACE_NAME_SIZE, &Len);
//		if(Len)
//		{
//			UserSt->pAdapterName = new MIL_TEXT_CHAR[Len];
//			MdigInquire(UserSt->MilDigitizer, M_GC_INTERFACE_NAME, UserSt->pAdapterName);
//		}
//
//		UserSt->CamVendor = new MIL_TEXT_CHAR[VendorStLen];
//		UserSt->CamModel = new MIL_TEXT_CHAR[ModelStLen];
//
//		MdigInquire(UserSt->MilDigitizer, M_CAMERA_VENDOR, UserSt->CamVendor);
//		MdigInquire(UserSt->MilDigitizer, M_CAMERA_MODEL, UserSt->CamModel);
//
//		MdigInquire(UserSt->MilDigitizer, M_GC_MAC_ADDRESS_STRING_SIZE, &MacStLen);
//		UserSt->CamMacAddress = new MIL_TEXT_CHAR[MacStLen];
//		MdigInquire(UserSt->MilDigitizer, M_GC_MAC_ADDRESS_STRING, UserSt->CamMacAddress);
//
//		/* Pop-up the MIL feature browser; exposes GigE device features.                */
//#if (USE_FEATURE_BROWSER == 1)
//		MdigControl(UserSt->MilDigitizer, M_GC_FEATURE_BROWSER, M_OPEN+M_ASYNCHRONOUS);
//#endif
//
//		/* Allocate displays and buffers; everything necessary to run MdigProcess. */
//		MdispAlloc(MilSystem, M_DEFAULT, MIL_TEXT("M_DEFAULT"), M_DEFAULT,
//			&UserSt->MilDisplay);
//		MdispControl(UserSt->MilDisplay, M_TITLE,
//			M_PTR_TO_DOUBLE(UserSt->CamModel));
//
//		/* Allocate a buffer format that matches the camera's pixel format. */
//		MdigInquireFeature(UserSt->MilDigitizer, M_FEATURE_VALUE, MIL_TEXT("PixelFormat"),
//			M_TYPE_ENUMERATION, &PixFmt);
//		GetMilBufferInfoFromPixelFormat(UserSt->MilDigitizer, PixFmt, SizeBand, BufType,
//			BufFormat);
//
//		MbufAllocColor(MilSystem,
//			SizeBand,
//			MdigInquire(UserSt->MilDigitizer, M_SIZE_X, M_NULL),
//			MdigInquire(UserSt->MilDigitizer, M_SIZE_Y, M_NULL),
//			BufType,
//			M_IMAGE+M_GRAB+M_DISP+M_PROC,
//			&UserSt->MilImageDisp);
//
//		/*MbufAllocColor(MilSystem,
//			SizeBand,
//			MdigInquire(UserSt->MilDigitizer, M_SIZE_X, M_NULL),
//			MdigInquire(UserSt->MilDigitizer, M_SIZE_Y, M_NULL),
//			BufType,
//			M_IMAGE+M_DISP+M_PROC,
//			&UserSt->MilOverlay);*/
//		MbufClear(UserSt->MilImageDisp, M_COLOR_BLACK);
//		MdispSelectWindow(UserSt->MilDisplay, UserSt->MilImageDisp,  GetDlgItem(WindowID)->GetSafeHwnd());
//
//		for(MIL_INT i = 0; i < BUFFERING_SIZE_MAX; i++)
//		{
//			MbufAllocColor(MilSystem,
//				SizeBand,
//				MdigInquire(UserSt->MilDigitizer, M_SIZE_X, M_NULL),
//				MdigInquire(UserSt->MilDigitizer, M_SIZE_Y, M_NULL),// MdigInquire（）；获取指定的采集卡配置情况
//				BufType,
//				M_GRAB+M_IMAGE+M_PROC,
//				&UserSt->MilGrabBufferList[i]);
//			if(UserSt->MilGrabBufferList[i])
//			{
//				UserSt->MilGrabBufferListSize++;
//				MbufClear(UserSt->MilGrabBufferList[i], 0);
//			}
//		}
//	}
//}
//
///* Get the MIL buffer attributes that match the camera's pixel format.   */
///* --------------------------------------------------------------------- */
//void CcontrolSerialNetPortDlg::GetMilBufferInfoFromPixelFormat(MIL_ID MilDigitizer, MIL_INT64 PixelFormat,
//									 MIL_INT& SizeBand, MIL_INT& BufType, MIL_INT64& Attribute)
//{
//	MIL_INT Conversion = 0;
//
//	switch(PixelFormat)
//	{
//	case PFNC_MONO8_ID:
//		SizeBand = 1;
//		BufType = 8+M_UNSIGNED;
//		Attribute = M_MONO8+M_PLANAR;
//		break;
//	case GEV_MONO10_PACKED_ID:
//	case GEV_MONO12_PACKED_ID:
//		SizeBand = 1;
//		BufType = 16+M_UNSIGNED;
//		Attribute = M_PLANAR;
//		break;
//	case PFNC_MONO10_ID:
//	case PFNC_MONO12_ID:
//	case PFNC_MONO14_ID:
//	case PFNC_MONO16_ID:
//		SizeBand = 1;
//		BufType = 16+M_UNSIGNED;
//		Attribute = M_PLANAR;
//		break;
//	case PFNC_RGB8_ID:
//		SizeBand = 3;
//		BufType = 8+M_UNSIGNED;
//		Attribute = M_RGB24+M_PACKED;
//		break;
//	case PFNC_BGR8_ID:
//		SizeBand = 3;
//		BufType = 8+M_UNSIGNED;
//		Attribute = M_BGR24+M_PACKED;
//		break;
//	case PFNC_BAYERGR8_ID:
//	case PFNC_BAYERRG8_ID:
//	case PFNC_BAYERGB8_ID:
//	case PFNC_BAYERBG8_ID:
//		MdigInquire(MilDigitizer, M_BAYER_CONVERSION, &Conversion);
//		if(Conversion == M_ENABLE)
//		{
//			SizeBand = 3;
//			BufType = 8+M_UNSIGNED;
//			Attribute = M_BGR32+M_PACKED;
//		}
//		else
//		{
//			SizeBand = 1;
//			BufType = 8+M_UNSIGNED;
//			Attribute = M_MONO8+M_PLANAR;
//		}
//		break;
//	case PFNC_BGRa8_ID:
//		SizeBand = 3;
//		BufType = 8+M_UNSIGNED;
//		Attribute = M_BGR32+M_PACKED;
//		break;
//	case PFNC_BAYERGR10_ID:
//	case PFNC_BAYERRG10_ID:
//	case PFNC_BAYERGB10_ID:
//	case PFNC_BAYERBG10_ID:
//	case PFNC_BAYERGR12_ID:
//	case PFNC_BAYERRG12_ID:
//	case PFNC_BAYERGB12_ID:
//	case PFNC_BAYERBG12_ID:
//	case PFNC_BAYERGR16_ID:
//	case PFNC_BAYERRG16_ID:
//	case PFNC_BAYERGB16_ID:
//	case PFNC_BAYERBG16_ID:
//	case GEV_BAYGR10_PACKED_ID:
//	case GEV_BAYRG10_PACKED_ID:
//	case GEV_BAYGB10_PACKED_ID:
//	case GEV_BAYBG10_PACKED_ID:
//	case GEV_BAYGR12_PACKED_ID:
//	case GEV_BAYRG12_PACKED_ID:
//	case GEV_BAYGB12_PACKED_ID:
//	case GEV_BAYBG12_PACKED_ID:
//		MdigInquire(MilDigitizer, M_BAYER_CONVERSION, &Conversion);
//		if(Conversion == M_ENABLE)
//		{
//			SizeBand = 3;
//			BufType = 16+M_UNSIGNED;
//			Attribute = M_RGB48+M_PACKED;
//		}
//		else
//		{
//			SizeBand = 1;
//			BufType = 16+M_UNSIGNED;
//			Attribute = M_PLANAR;
//		}
//		break;
//	case PFNC_RGB10_ID:
//	case PFNC_RGB12_ID:
//	case PFNC_BGR10_ID:
//	case PFNC_BGR12_ID:
//		SizeBand = 3;
//		BufType = 16+M_UNSIGNED;
//		Attribute = M_RGB48+M_PACKED;
//		break;
//	case PFNC_YUV422_8_UYVY_ID:
//		SizeBand = 3;
//		BufType = 8+M_UNSIGNED;
//		Attribute = M_YUV16_UYVY+M_PACKED;
//		break;
//	case PFNC_YUV422_8_ID:
//		SizeBand = 3;
//		BufType = 8+M_UNSIGNED;
//		Attribute = M_YUV16_YUYV+M_PACKED;
//		break;
//	default:
//		SizeBand = 0;
//		BufType = 0;
//		Attribute = 0;
//		break;
//	}
//}
//
//
//void CcontrolSerialNetPortDlg::AddAdapterToList(SysHookDataStruct* UserSt, MIL_TEXT_PTR AdapterName)
//{
//	/* Start by searching if adapter is already in list. */
//	for(MIL_INT i=0; i<MAX_ADAPTERS; i++)
//	{
//		if(MosStrcmp(UserSt->Adapters[i], AdapterName) == 0)
//			return;
//	}
//
//	/* Adapter is not in list; add it. */
//	for(MIL_INT i=0; i<MAX_ADAPTERS; i++)
//	{
//		if(UserSt->Adapters[i][0] == '\0')
//		{
//			MosStrcpy(UserSt->Adapters[i], MAX_ADAPTER_DESCRIPTION_LENGTH + 4, AdapterName);
//			return;
//		}
//	}
//}
//
//
//void CcontrolSerialNetPortDlg::DigStartAcquisition(DigHookDataStruct* UserSt, int flag)//----------------------------（1.2.1.5.1.1.1）启动模板匹配图像处理函数
//{
//	if(UserSt->MilDigitizer)//没满足条件
//	{
//		UserSt->GrabInProgress = M_TRUE;
//		MIL_INT64 oporation = (flag == 0) ? M_START : M_SEQUENCE+M_COUNT(1);
//		MdigProcess(UserSt->MilDigitizer, UserSt->MilGrabBufferList,            //MdigProcess采集的同时处理。
//			UserSt->MilGrabBufferListSize, oporation, M_DEFAULT,
//			ProcessingFunction, UserSt);//--------------------------------（1.2.1.5.1.1.1.1）模板匹配底层函数
//		MdigInquire(UserSt->MilDigitizer, M_GC_PAYLOAD_SIZE, &UserSt->PayloadSize);
//	}
//	else
//	{
//		AddString(_T("图相中断,可能原因：相机未连接！可能没插密码狗"));
//	}
//}
//
//void CcontrolSerialNetPortDlg::MilDestroy()
//{	
//
//	for(int DevNb = M_DEV0; DevNb < MAX_CAM; DevNb++)
//	{		
//		if ((DigUserHookData[DevNb].MilDisplay) && (DigUserHookData[DevNb].MilImageDisp))
//		{
//			MdispDeselect(DigUserHookData[DevNb].MilDisplay, DigUserHookData[DevNb].MilImageDisp);
//		}
//		DigFreeResources(&DigUserHookData[DevNb]);
//	}
//
//	MsysHookFunction(MilSystem, M_CAMERA_PRESENT+M_UNHOOK, CamPresentFunction,
//		&SysUserHookData);
//	MsysFree(MilSystem);
//	MappFree(MilApplication);
//}
//
//void CcontrolSerialNetPortDlg::DigStopAcquisition(DigHookDataStruct* UserSt)
//{
//	if(UserSt->GrabInProgress)
//	{
//		UserSt->GrabInProgress = M_FALSE;
//		MdigProcess(UserSt->MilDigitizer, UserSt->MilGrabBufferList,
//			UserSt->MilGrabBufferListSize, M_STOP+M_WAIT, M_DEFAULT,
//			ProcessingFunction, UserSt);
//	}
//}
//
///* Free digitizer and all other resources allocated.  */
///* -------------------------------------------------- */
//
//void CcontrolSerialNetPortDlg::DigFreeResources(DigHookDataStruct* UserSt)
//{
//	if(UserSt->MilDigitizer)
//	{
//		for(MIL_INT i = 0; i < UserSt->MilGrabBufferListSize; i++)
//			MbufFree(UserSt->MilGrabBufferList[i]);
//
//		MbufFree(UserSt->MilImageDisp);
//		MbufFree(UserSt->MilOverlay);
//		MdispFree(UserSt->MilDisplay);
//
//#if (USE_FEATURE_BROWSER == 1)
//		/* Close the MIL feature browser; exposes GigE device features.                */
//		MdigControl(UserSt->MilDigitizer, M_GC_FEATURE_BROWSER, M_CLOSE);
//#endif
//
//		MdigFree(UserSt->MilDigitizer);
//
//		delete [] UserSt->CamVendor;
//		delete [] UserSt->CamModel;
//		delete [] UserSt->CamMacAddress;
//		delete [] UserSt->pAdapterName;
//		memset(UserSt, 0, sizeof(DigHookDataStruct));
//	}
//}
//
//
//
//void CcontrolSerialNetPortDlg::OnBnClickedButtonstart1()
//{
//	// TODO: Add your control notification handler code here
//	GetDlgItem( IDC_BUTTON_start1)->EnableWindow(FALSE);
//	DigUserHookData[0].workNum = 0;
//	DigStartAcquisition(&DigUserHookData[0], 0);
//	DigUserHookData[0].IsContinueGrab = true;
//	
//	/* Register a hook function to the system's camera present event. */
//	/* Used to:                                                        */
//	/* 1- Allocate and start acquisition on a newly attached camera.   */
//	/* 2- Stop acquisition on a camera that has been removed.          */
//	/* 3- Resume acquisition on a camera that has been re-connected.   */
//	//MdigHookFunction(DigUserHookData[0].MilDigitizer, M_CAMERA_PRESENT, CamPresentFunction, &DigUserHookData[0]);
//}
//
//
//void CcontrolSerialNetPortDlg::OnBnClickedButtonmainstop1()
//{
//	// TODO: Add your control notification handler code here
//	DigStopAcquisition(&DigUserHookData[0]);
//	GetDlgItem( IDC_BUTTON_start1 )->EnableWindow(TRUE);
//	DigUserHookData[0].IsContinueGrab = false;
//
//}
//
void CcontrolSerialNetPortDlg::OnBnClickedButtonstart2()
{
	// TODO: Add your control notification handler code here
	GetDlgItem( IDC_BUTTON_start2)->EnableWindow(FALSE);
	//DigUserHookData[1].workNum = 1;
	//DigStartAcquisition(&DigUserHookData[1], 0);
	//DigUserHookData[1].IsContinueGrab = true;


}
//
//void CcontrolSerialNetPortDlg::OnBnClickedButtonmainstop2()
//{
//	// TODO: Add your control notification handler code here
//	DigStopAcquisition(&DigUserHookData[1]);
//	GetDlgItem( IDC_BUTTON_start2 )->EnableWindow(TRUE);
//	DigUserHookData[1].IsContinueGrab = false;
//
//
//}
//
////void CcontrolSerialNetPortDlg::OnBnClickedButtonstart3()
////{
////	// TODO: Add your control notification handler code here
////	GetDlgItem( IDC_BUTTON_start3)->EnableWindow(FALSE);
////	DigStartAcquisition(&DigUserHookData[2], 0);
////	DigUserHookData[2].IsContinueGrab = true;
////
////
////}
//
////void CcontrolSerialNetPortDlg::OnBnClickedButtonmainstop3()
////{
////	// TODO: Add your control notification handler code here
////	DigStopAcquisition(&DigUserHookData[2]);
////	GetDlgItem( IDC_BUTTON_start3 )->EnableWindow(TRUE);
////	DigUserHookData[2].IsContinueGrab = false;
////
////
////}
//
//void CcontrolSerialNetPortDlg::OnDestroy()
//{
//	CDialog::OnDestroy();
//
//	// TODO: Add your message handler code here
//	for(int DevNb = M_DEV0; DevNb < MAX_CAM; DevNb++)
//	{
//		if(DigUserHookData[DevNb].GrabInProgress == TRUE)
//			DigStopAcquisition(&DigUserHookData[DevNb]);
//	}
//
//	if (m_settingDlg != NULL)
//	{
//		m_settingDlg->DestroyWindow();
//		delete m_settingDlg;
//		m_settingDlg = NULL;
//	}
//
//	for (int i = 0; i < LIGHT_CHANNEL_NUM; i++)
//	{
//		if (m_LightChannelState[i] == true)
//		{
//			OPTController_TurnOffChannel(m_OPTControllerHanlde, i);
//		}
//	}
//
//	if (m_LightPortState == TRUE)
//	{
//		OPTController_ReleaseSerialPort(m_OPTControllerHanlde);
//	}
//
//}
//
//
//void MFTYPE bnProcess(MIL_ID iSystem, MIL_ID iImageBuffer, MIL_ID iOverlay, MIL_ID oImageBuffer)
//{
//
//   MIL_ID      MilEdgeContext,                         /* 边缘识别控制器ID*/ 
//               MilEdgeResult;                          /* 边缘识别结果储存器ID*/
//
//
//   /* 二值化，区域开闭预算*/
//   MimBinarize(iImageBuffer, iImageBuffer, M_BIMODAL  + M_LESS_OR_EQUAL, M_NULL, M_NULL);
//
//   MimMorphic(iImageBuffer, iImageBuffer, M_3X3_RECT , M_AREA_OPEN, 500, M_BINARY);
//   MimMorphic(iImageBuffer, oImageBuffer, M_3X3_RECT , M_AREA_CLOSE, 500, M_BINARY);
//
//
//   MedgeAlloc(iSystem, M_CONTOUR, M_DEFAULT, &MilEdgeContext); 
//
//   MedgeAllocResult(iSystem, M_DEFAULT, &MilEdgeResult);
//
//   MedgeControl(MilEdgeContext, M_THRESHOLD_MODE ,                  M_HIGH );
//   MedgeControl(MilEdgeContext, M_FILTER_SMOOTHNESS,               80.0);
//   MedgeControl(MilEdgeContext, M_EXTRACTION_SCALE,                0.2);
//
//   MedgeControl(MilEdgeContext, M_FILL_GAP_CANDIDATE,            M_DEFAULT);
//   MedgeControl(MilEdgeContext, M_FILL_GAP_DISTANCE,              50);
//   MedgeControl(MilEdgeContext, M_FILL_GAP_CONTINUITY,            100); 
//
//   MedgeCalculate(MilEdgeContext, oImageBuffer, M_NULL, M_NULL, M_NULL, MilEdgeResult, M_DEFAULT);
//
//   MgraColor(M_DEFAULT, M_COLOR_GREEN);
//   MedgeDraw(M_DEFAULT, MilEdgeResult, iOverlay, M_DRAW_EDGES, M_DEFAULT, M_DEFAULT);
//}
//
//
///* User's processing function called every time a grab buffer is modified. */
///* ----------------------------------------------------------------------- */
//
//MIL_INT MFTYPE ProcessingFunction(MIL_INT HookType,
//								  MIL_ID HookId,
//								  void* HookDataPtr)//------------------------------------（1.2.1.5.1.1.1.1）模板匹配函数底层函数
//{
//	DigHookDataStruct *UserHookDataPtr = (DigHookDataStruct *)HookDataPtr;
//	
//
//	if(UserHookDataPtr->GrabInProgress == M_TRUE)
//	{
//		MIL_ID ModifiedBufferId = 0, overlayBufferId = 0;
//		MIL_INT ResendRequests = 0, PacketsMissed = 0, IsCorrupt = 0;
//
//		/* Retrieve the MIL_ID of the grabbed buffer and camera statistics. */
//		MdigGetHookInfo(HookId, M_MODIFIED_BUFFER+M_BUFFER_ID, &ModifiedBufferId);//
//		MdigGetHookInfo(HookId, M_GC_PACKETS_RESENDS_NUM, &ResendRequests);
//		MdigGetHookInfo(HookId, M_GC_PACKETS_MISSED, &PacketsMissed);
//		MdigGetHookInfo(HookId, M_CORRUPTED_FRAME, &IsCorrupt);
//
//		UserHookDataPtr->ResendRequests += ResendRequests;
//		UserHookDataPtr->PacketsMissed += PacketsMissed;
//
//		/* Copy the grabbed frame to display. */
//		if(IsCorrupt)
//		{
//			UserHookDataPtr->CorruptImageCount++;
//			mainDlg->AddString(_T("采集图像帧错误？"));
//		}
//		else
//		{
//			UserHookDataPtr->ProcessedImageCount++;
//			if (UserHookDataPtr->IsContinueGrab == true)
//			{
//				MbufCopy(ModifiedBufferId, UserHookDataPtr->MilImageDisp);
//			}else
//			{
//				if(UserHookDataPtr->MilDisplay)
//				{
//					MdispControl(UserHookDataPtr->MilDisplay, M_FILL_DISPLAY, M_ENABLE);        /*图像填充显示窗口*///MdispControl（）；改变指定的显示属性
//					MdispControl(UserHookDataPtr->MilDisplay, M_OVERLAY_CLEAR, M_DEFAULT);        /*注释层初始化*/
//					MdispInquire(UserHookDataPtr->MilDisplay, M_OVERLAY_ID, &UserHookDataPtr->MilOverlay);    /*载入注释层*///MdispInquire（）；获取指定的显示配置情况
//				}
//
//				MbufCopy(ModifiedBufferId, UserHookDataPtr->MilImageDisp);//
//				Sleep(20);
//
//				int workNum = UserHookDataPtr->workNum;
//
//				if (CPublic::g_typeOfImagePro[workNum] == 0)
//				{
//					int count = 0;
//					do 
//					{
//						int state = SingleModelExample(UserHookDataPtr->MilSystem, ModifiedBufferId, UserHookDataPtr->MilOverlay, workNum, &CPublic::g_positionInfo[workNum]);
//						if (state == 1)
//						{
//							MbufCopy(ModifiedBufferId, UserHookDataPtr->MilImageDisp);
//							mainDlg->AddString(_T("模板匹配成功！"));
//							break;
//						}else
//						{
//							mainDlg->AddString(CPublic::int2CString(count+1)+_T("次模板匹配失败？"));
//							count++;					
//						}
//							
//					}while(count < 4);
//
//					if (count == 4)
//					{
//						mainDlg->m_continue[workNum] = false;
//					}
//				}
//				else if (CPublic::g_typeOfImagePro[workNum] == 1)
//				{
//					CircleFinderExample(UserHookDataPtr->MilSystem, ModifiedBufferId, UserHookDataPtr->MilOverlay, workNum, &CPublic::g_positionInfo[workNum]);
//					MbufCopy(ModifiedBufferId, UserHookDataPtr->MilImageDisp);
//				}
//			//bnProcess(mainDlg->SysUserHookData.MilSystem, ModifiedBufferId, UserHookDataPtr->MilOverlay, ModifiedBufferId);
//			}		
//		}
//	}	
//	return 0;
//}
//
//
///* User's camera present function called every time the camera connection state */
///* changes.                                                                   */
///* -------------------------------------------------------------------------- */
//
////MIL_INT MFTYPE CamPresentFunction(MIL_INT HookType,
////								  MIL_ID HookId,
////								  void* HookDataPtr)
////{
////	DigHookDataStruct *UserHookDataPtr = (DigHookDataStruct *)HookDataPtr;
////	MIL_INT IsCamPresent, Number;
////	MIL_ID digID;
////
////	/* Inquire the camera present state (present or not present). */
////	MdigGetHookInfo(UserHookDataPtr->MilDigitizer, M_CAMERA_PRESENT, IsCamPresent);
////	/* Inquire the camera's digitizer device number .CollapseOpen M_DIGITIZER_ID  */
////	MdigGetHookInfo(UserHookDataPtr->MilDigitizer, M_NUMBER, &Number);
////	/* Inquire the camera's digitizer id .  */
////	//MdigGetHookInfo(UserHookDataPtr->MilDigitizer, M_DIGITIZER_ID, &digID);
////
////
////	if (mainDlg->DigUserHookData[Number].MilDigitizer != UserHookDataPtr->MilDigitizer)
////	{
////		return 0;
////	}
////
////	if(IsCamPresent)
////	{		
////
////	
////		/* Camera is present. */
////		if(mainDlg->DigUserHookData[Number].MilDigitizer == 0)
////		{
////			/* Newly attached camera; allocate it. */
////			mainDlg->DigAllocResources(mainDlg->SysUserHookData.MilSystem, Number, IDC_DISP1 + Number,
////				&mainDlg->DigUserHookData[Number]);
////		}
////		
////
////		if(mainDlg->DigUserHookData[Number].MilDigitizer)
////		mainDlg->DigUserHookData[Number].IsConnected = true;
////		/* Start acquisition. */
////		mainDlg->DigStartAcquisition(&mainDlg->DigUserHookData[Number]);
////
////	}
////	else
////	{
////		/* Camera is not present. */
////		if(mainDlg->DigUserHookData[Number].MilDigitizer)
////		{
////			/* Stop acquisition. */
////			mainDlg->DigStopAcquisition(&mainDlg->DigUserHookData[Number]);
////		}
////
////		mainDlg->DigUserHookData[Number].IsConnected = false;
////	}
////
////	return 0;
////}
//
//
///* User's camera present function called every time a camera connection state */
///* changes.                                                                   */
///* -------------------------------------------------------------------------- */
//
//MIL_INT MFTYPE CamPresentFunction(MIL_INT HookType,
//                                  MIL_ID HookId,
//                                  void* HookDataPtr)
//   {
//   SysHookDataStruct *UserHookDataPtr = (SysHookDataStruct *)HookDataPtr;
//   MIL_INT IsCamPresent, Number;
//
//   /* Inquire the camera present state (present or not present). */
//   MsysGetHookInfo(UserHookDataPtr->MilSystem, HookId, M_CAMERA_PRESENT, &IsCamPresent);
//   /* Inquire the camera's digitizer device number . */
//   MsysGetHookInfo(UserHookDataPtr->MilSystem, HookId, M_NUMBER, &Number);
//   /* Update the number of camera present variable. */
//   MsysInquire(UserHookDataPtr->MilSystem, M_NUM_CAMERA_PRESENT,
//                                           &UserHookDataPtr->NbCameras);
//
//   if(IsCamPresent)
//      {
//      MIL_TEXT_CHAR* MacAddress = NULL;
//      MIL_INT Size = 0;
//
//      /* Inquire the camera's MAC address . */
//      MsysGetHookInfo(UserHookDataPtr->MilSystem, HookId, M_GC_MAC_ADDRESS_STRING_SIZE,
//                      &Size);
//      MacAddress = new MIL_TEXT_CHAR[Size];
//      MsysGetHookInfo(UserHookDataPtr->MilSystem, HookId, M_GC_MAC_ADDRESS_STRING,
//                      MacAddress);
//
//      /* Camera is present. */
//      if(UserHookDataPtr->DigHookDataStrutPtr[Number].MilDigitizer == 0)
//         {
//         /* Newly attached camera; allocate it. */
//         mainDlg->DigAllocResources(UserHookDataPtr->MilSystem, Number, IDC_DISP1 + Number,
//                           &UserHookDataPtr->DigHookDataStrutPtr[Number]);
//         }
//      else if(MosStrcmp(UserHookDataPtr->DigHookDataStrutPtr[Number].CamMacAddress,
//                        MacAddress) != 0)
//         {
//         /* New camera added in place of another one, free old dig */
//         mainDlg->DigFreeResources(&UserHookDataPtr->DigHookDataStrutPtr[Number]);
//
//         /* Find out if camera was previously allocated on a different device number. */
//         for(MIL_INT i = 0; i < MAX_CAM; i++)
//            if((i != Number) &&
//               (MosStrcmp(UserHookDataPtr->DigHookDataStrutPtr[Number].CamMacAddress,
//                        MacAddress) == 0))
//               mainDlg->DigFreeResources(&UserHookDataPtr->DigHookDataStrutPtr[i]);
//
//         /* Allocate resources. */
//         mainDlg->DigAllocResources(UserHookDataPtr->MilSystem, Number, IDC_DISP1 + Number,
//                           &UserHookDataPtr->DigHookDataStrutPtr[Number]);
//         }
//
//      if(UserHookDataPtr->DigHookDataStrutPtr[Number].MilDigitizer)
//         mainDlg->AddAdapterToList(UserHookDataPtr,
//                          UserHookDataPtr->DigHookDataStrutPtr[Number].pAdapterName);
//
//      UserHookDataPtr->DigHookDataStrutPtr[Number].IsConnected = true;
//      /* Start acquisition. */
//      mainDlg->DigStartAcquisition(&UserHookDataPtr->DigHookDataStrutPtr[Number], 0);
//
//      delete [] MacAddress;
//      }
//   else
//      {
//      /* Camera is not present. */
//      if(UserHookDataPtr->DigHookDataStrutPtr[Number].MilDigitizer)
//         {
//         /* Stop acquisition. */
//         mainDlg->DigStopAcquisition(&UserHookDataPtr->DigHookDataStrutPtr[Number]);
//         }
//
//      UserHookDataPtr->DigHookDataStrutPtr[Number].IsConnected = false;
//      }
//
//   return 0;
//   }



void CcontrolSerialNetPortDlg::OnBnClickedButtonSerial4()
{
	int axises[] = {axis3, axis6};

	CString dlgName = _T("工位2-装配机械手手动调整");

	int port = portNum4;
	if (CPublic::portIsOpen[port-1] == false)
	{
		CString str = _T("串口") + CPublic::int2CString(port) + _T("未打开！");
		AfxMessageBox(str);
		return;
	}

	
	CDlgSerial4 m_DlgSerial(NULL, port, axises, dlgName);
	INT_PTR nResponse = m_DlgSerial.DoModal();

	if (nResponse == IDOK)
	{
	}
	else if (nResponse == IDCANCEL)
	{
	}

	UpdateData(TRUE);
}

void CcontrolSerialNetPortDlg::OnBnClickedButtonSerial5()
{
	int axises[] = {axis1, axis2, axis9};
	int port[] = {portNum4, portNum1};

	CString dlgName = _T("工位2-微动平台手动调整");

	for (int i = 0; i < 2; i++)
	{
		if (CPublic::portIsOpen[port[i]-1] == false)
		{
			CString str = _T("串口") + CPublic::int2CString(port[i]) + _T("未打开！");
			AfxMessageBox(str);
			return;
		}
	}

	CDlgSerial5 m_DlgSerial(NULL, port, axises, dlgName);
	INT_PTR nResponse = m_DlgSerial.DoModal();

	if (nResponse == IDOK)
	{
	}
	else if (nResponse == IDCANCEL)
	{
	}

	UpdateData(TRUE);
}

void CcontrolSerialNetPortDlg::OnBnClickedButtonSerial6()
{
	int axises[] = {axis4, axis5, axis7, axis8};
	int port = portNum4;
	CString dlgName = _T("工位2-辅助部件手动调整");

	if (CPublic::portIsOpen[port-1] == false)
	{
		CString str = _T("串口") + CPublic::int2CString(port) + _T("未打开！");
		AfxMessageBox(str);
		return;
	}


	CDlgSerial6 m_DlgSerial(NULL, &port, axises, dlgName);
	INT_PTR nResponse = m_DlgSerial.DoModal();

	if (nResponse == IDOK)
	{
	}
	else if (nResponse == IDCANCEL)
	{
	}

	UpdateData(TRUE);
}

//void CcontrolSerialNetPortDlg::OnBnClickedButtonSerial7()
//{
//	int axises[] = {axis3, axis6};
//	int port = portNum5;
//	CString dlgName = _T("工位3-装配机械手手动调整");
//
//
//	CDlgSerial4 m_DlgSerial(NULL, port, axises, dlgName);
//	//m_DlgSerial.SetWindowText(_T("工位3-装配机械手手动调整"));
//
//	INT_PTR nResponse = m_DlgSerial.DoModal();
//
//	if (nResponse == IDOK)
//	{
//	}
//	else if (nResponse == IDCANCEL)
//	{
//	}
//
//	UpdateData(TRUE);
//}

//void CcontrolSerialNetPortDlg::OnBnClickedButtonSerial8()
//{
//	int axises[] = {axis1, axis2, axis9};
//	int port[] = {portNum5, portNum1};
//	CString dlgName = _T("工位3-微动平台手动调整");
//
//
//	CDlgSerial5 m_DlgSerial(NULL, port, axises, dlgName);
//	INT_PTR nResponse = m_DlgSerial.DoModal();
//
//	if (nResponse == IDOK)
//	{
//	}
//	else if (nResponse == IDCANCEL)
//	{
//	}
//
//	UpdateData(TRUE);
//}

//void CcontrolSerialNetPortDlg::OnBnClickedButtonSerial9()
//{
//	int axises[] = {axis4, axis5, axis7, axis8};
//	int port[] = {portNum5};
//	CString dlgName = _T("工位3-辅助部件手动调整");
//
//
//	CDlgSerial6 m_DlgSerial(NULL, port, axises, dlgName);
//	INT_PTR nResponse = m_DlgSerial.DoModal();
//
//	if (nResponse == IDOK)
//	{
//	}
//	else if (nResponse == IDCANCEL)
//	{
//	}
//
//	UpdateData(TRUE);
//}

//volatile bool g_robotingFlag[MAX_CAM] = {true};

int CcontrolSerialNetPortDlg::beginInitialProcess(void)//启动初始化函数
{
	UpdateData();	
	//robot->powerdo();
	for (int i = 0; i < MAX_CAM; i++)
	{
		m_threadInfo[i].dlg = this;
		m_threadInfo[i].Continue = &m_continue[i];	
		m_threadInfo[i].workNum = i;

		ThreadState[i] = 1;//设置初始化变量为1
		m_pThread[i] = AfxBeginThread(ThreadFuninitial, (LPVOID)&m_threadInfo[i]);

	}
	UpdateData();	
	return 0;
}
int CcontrolSerialNetPortDlg::beginAutoProcess(void)//启动线程函数----------------------------------------------------------------------1
{
	// TODO: Add your control notification handler code her
	UpdateData();	//将对话框中设定的数据交换至变量中

	//InitWorkStation();

	for (int i = 0; i < MAX_CAM; i++)//多线程：以前的单核多线程是并发，但是现在的超线程技术的应用，多线程是并行+并发。
	{//结构体内部参数规定
		m_threadInfo[i].dlg = this;	//主执行绪的视窗控件标ad头r 
		m_threadInfo[i].Continue = &m_continue[i];	//控制执行绪是否执行的旗标
		//m_threadInfo[i].sleepTime = m_sleepTime[i];	//执行绪停止的间隔
		m_threadInfo[i].workNum = i;

		ThreadState[i] = 1;//初始化线程状态变量
		//InitWorkStation(m_threadInfo[i].Continue, i);

		m_pThread[i] = AfxBeginThread(ThreadFun, (LPVOID)&m_threadInfo[i]);
		//开启第i个线程：线程是“一个进程内部的控制序列”
		//参数1  线程的入口函数,声明一定要如下: UINT MyThreadFunction( LPVOID IParam );
		//参数2 传递入线程的参数, 注意它的类型为:LPVOID, 所以我们可以传递一个结构体入线程.
		//参数3、4、5分别指定线程的优先级、堆栈大小、创建标识、安全属性，含义同用户界面线程。
	}

	//AddString(_T("自动流程并行开始...."));

	//m_start_button.SetWindowText("重设");	//将按钮的标签改为重设
	//m_start_button.SetDlgCtrlID(IDC_RESET_BUTTON);
	//将按钮的讯息代号改为IDC_RESET_BUTTON

	UpdateData();	//将数据由对话框的控件，更新至程序中

	/*for (int i = 0; i < MAX_CAM; i++)
	{
		m_pThread[i]->SetThreadPriority(THREAD_PRIORITY_HIGHEST - i);
	}*/

	//if(m_priority_check)	//检查IDC_PRIORITY_CHECK控件是否被选取
	//{	//将五个执行绪设成不同的执行优先权
		
		//m_pThread[1]->SetThreadPriority(THREAD_PRIORITY_ABOVE_NORMAL);
		//m_pThread[2]->SetThreadPriority(THREAD_PRIORITY_NORMAL);
		//m_pThread[3]->SetThreadPriority(THREAD_PRIORITY_BELOW_NORMAL);
		//m_pThread[4]->SetThreadPriority(THREAD_PRIORITY_LOWEST);
	//}
	return 0;
}
UINT ThreadFuninitial(LPVOID lParam)//---------------------------------------------------------------------------初始化入口函数（1）
{
	ThreadInfo * Thread_Info = (ThreadInfo *)lParam;	//传入Thread的参数
	int workNum = Thread_Info->workNum;//线程的序号
	CcontrolSerialNetPortDlg* pDlg = (CcontrolSerialNetPortDlg*)(Thread_Info->dlg);

	initialWorkProcess(Thread_Info);

	CString n;
	workNum = workNum + 1;
	n.Format(_T("%d"), workNum);//int转换成字符
	pDlg->AddString(_T("--------------线程") + n + _T(":初始化已完成--------------"));


	*(Thread_Info->Continue) = false;	//完成之后，设定执行绪不再继续执行
	::PostMessage(pDlg->m_hWnd, WMU_THREAD_EXIT, 0, 0);
	//AddString(_T("关闭所有的自动流程！"));

	//传出执行绪已完成执行的讯息
	return(0);
}

UINT ThreadFun(LPVOID lParam)//---------------------------------------------------------------------------自动流程线程入口函数（1）
{

	ThreadInfo * Thread_Info = (ThreadInfo *) lParam;	//传入Thread的参数
	int workNum = Thread_Info->workNum;//线程的序号
	CcontrolSerialNetPortDlg* pDlg = (CcontrolSerialNetPortDlg*)(Thread_Info->dlg);

	
	autoWorkProcess(Thread_Info);
   

	*(Thread_Info->Continue) = false;	//完成之后，设定执行绪不再继续执行
	::PostMessage(pDlg->m_hWnd, WMU_THREAD_EXIT, 0, 0);
	//AddString(_T("关闭所有的自动流程！"));

	//传出执行绪已完成执行的讯息
	return(0);
}
static void initialWorkProcess(ThreadInfo* Thread_Info)//--------------------------------------初始化运行函数
{
	int workNum = Thread_Info->workNum;//线程的序号
	CcontrolSerialNetPortDlg* pDlg = ((CcontrolSerialNetPortDlg*)(Thread_Info->dlg));

	if (pDlg->InitWorkStation(Thread_Info->Continue, workNum) == 0)//自动流程初始化函数（1.1）完成之后在进行autowork
	{
		return;
	}
	
	//pDlg->AddString(_T("初始化已完成"));
	return;
}


static void autoWorkProcess(ThreadInfo* Thread_Info)//----------------------------------------------------------自动运行函数①
{ 
	int workNum = Thread_Info->workNum;//线程的序号
	CcontrolSerialNetPortDlg* pDlg = ((CcontrolSerialNetPortDlg*)(Thread_Info->dlg));

	int num = 0;
	//while (*Thread_Info->Continue == true)
	//{
	if (pDlg->AutoWorkStation(Thread_Info->Continue, workNum) == 0)//自动流程函数（1.2）只运行一次
	{
		return;
	}
	//	num ++;
        CString n;
		workNum = workNum + 1;
		n.Format(_T("%d"), workNum);//int转换成字符
		//m.Format(_T("%d"), num);
		pDlg->AddString(_T("--------------线程") + n + _T(":自动流程已完成1次------------"));
}


LRESULT CcontrolSerialNetPortDlg::OnThreadExit(WPARAM WP, LPARAM LP)
{
	int StopThreadNum = 0;	//计算已经停止的子执行绪个数
	for(int i = 0; i < MAX_CAM; i++)
	{
		if(m_continue[i] == false)	//判断子执行绪是否仍执行中
			StopThreadNum++;	//计算执行中的子执行绪个数
	}

	if(StopThreadNum == MAX_CAM)	//判断已停止的子执行绪是否为5全部
	{
		m_autoStart.SetIcon(IDI_ICON_startb);
		m_autoStop.SetIcon(IDI_ICON_stopg);	

		//for (int i = 0; i < MAX_CAM; i++)
		//{
		//	if (m_pThread[i] != NULL &&		//检查执行绪是否仍执行中
		//		::WaitForSingleObject(m_pThread[i]->m_hThread,0) == WAIT_TIMEOUT)
		//	{
		//		TerminateThread(m_pThread[i]->m_hThread, 0);
		//	}
		//}

	}		

	return 0;
}
void CcontrolSerialNetPortDlg::OnBnClickedButtoninitialization()//初始化------------------------------------------------------------
{
	
	for (int i = 0; i < MAX_CAM; i++)//MAX_CAM什么意思，线程个数

	{
		/*if (CPublic::portIsOpen[i] == false)
		{
		CString str;
		str.Format(_T("COM %d 未打开\n"), m_portNum[i]);
		AddString(str);
		return;
		}*/

		if (m_continue[i] == false)//若未打开 m_continue[i]是什么两个线程？？
		{
			m_continue[i] = true;	//设定控制执行绪执行的旗标，正在运行是true，挂起是false？
		}
		else//m_continue[i] = true已经打开了
		{
			AfxMessageBox(_T("请先停止自动流程后再启动"));
			return;
		}
	}
	//g_robotingFlag[0] = true;

	m_initial.SetIcon(IDI_ICON_initialyellow);//更换图标样式
	
	beginInitialProcess();//-------------------------------------------1启动函数
}


void CcontrolSerialNetPortDlg::OnBnClickedButtonautostart()//自动启动按钮-----------------------------------------------------------------（一）
{
	//提示先初始化-确定

	if (MessageBox(_T("请先初始化，之后再运行自动流程！是否已经初始化？"), _T("提示 "), MB_YESNO) == IDYES)
	{

		for (int i = 0; i < MAX_CAM; i++)//MAX_CAM什么意思，线程个数

		{
			/*if (CPublic::portIsOpen[i] == false)
			{
				CString str;
				str.Format(_T("COM %d 未打开\n"), m_portNum[i]);
				AddString(str);
				return;
			}*/


			if (m_continue[i] == false)//若未打开 m_continue[i]是什么两个线程？？
			{
				m_continue[i] = true;	//设定控制执行绪执行的旗标，正在运行是true，挂起是false？
			}
			else//m_continue[i] = true已经打开了
			{
				AfxMessageBox(_T("请先停止自动流程后再启动"));
				return;
			}
		}
		//g_robotingFlag[0] = true;

		m_autoStart.SetIcon(IDI_ICON_startg);//更换图标样式
		m_autoStop.SetIcon(IDI_ICON_stopblue);

		beginAutoProcess();//-------------------------------------------1启动函数
	}
}

void CcontrolSerialNetPortDlg::OnBnClickedButtonautostop()
{
	m_autoStart.SetIcon(IDI_ICON_startb);//更换图标样式变成绿色
	m_autoStop.SetIcon(IDI_ICON_stopg);//变成灰色
   m_progress.SetPos(0);//进度条置为0

   switchLight(&m_bstLight[0], false);
   switchLight(&m_bstLight[1], false);
   switchLight(&m_bstLight[2], false);
   switchLight(&m_bstLight[3], false);
   switchLight(&m_bstLight[4], false);
   switchLight(&m_bstLight[5], false);
   switchLight(&m_bstLight[6], false);
   switchLight(&m_bstLight[7], false);
   switchLight(&m_bstLight[8], false);
   switchLight(&m_bstLight[9], false);

	//file.Close();加上

	for(int i = 0; i < MAX_CAM; i++)
	{
		m_continue[i] = false;//关闭线程
		 //!= NULL;
	}
	UpdateData(FALSE);
	
	CStdioFile file[MAX_CAM];//流程文档
	CString str;
	BOOL ret[MAX_CAM];
	int workNum[MAX_CAM];//设置流程个数
	CString filePath[MAX_CAM];//流程文件路径
	CString name[MAX_CAM];//流程名称
	//拿到完整详细路径
	CString path;
	GetModuleFileName(NULL, path.GetBufferSetLength(MAX_PATH + 1), MAX_PATH);//获取默认exe路径
	path.ReleaseBuffer();
	int pos = path.ReverseFind('\\');
	path = path.Left(pos);//去掉路径中的exe
	path = path + _T("\\");
	//

	name[0] = pMainDlg->m_autoTXT1;
	name[1] = pMainDlg->m_autoTXT2;
	for (int i = 0; i < MAX_CAM; i++)
	{
		workNum[i] = i;
		str.Format(_T("%d"), i + 1);
		filePath[i] = path + name[i];//完整路径
									 //LPCTSTR pszFileName[i] = filePath[i].GetBufferSetLength(filePath[i].GetLength());将CString转换成LPCTSTR
		
		file[i].Close();
		TerminateThread(m_pThread[i]->m_hThread, 0);//强制关闭线程
		//::TerminateThread(m_pThread[i], 0);//关闭线程
		//关闭文件
		
	}
	

	//if (m_SocketState == true)
	//{
	//	SocketShutdown();
	//}
}

int CcontrolSerialNetPortDlg::InitWorkStation(bool* Continue, int workNum)//--------------------------------------------自动流程初始化函数（1.1）
{
	int portIndex = workNum;//工位序号/线程序号
	CString fileData = _T("");//初始化？？
	CString name;//初始化流程文件名称
	CString filePath;//流程文件路径
	BOOL ret;
	CString path;
	GetModuleFileName(NULL, path.GetBufferSetLength(MAX_PATH + 1), MAX_PATH);//获取默认exe路径
	path.ReleaseBuffer();
	int pos = path.ReverseFind('\\');
	path = path.Left(pos);//去掉路径中的exe
	path = path + _T("\\");
	name = (workNum == 0)? m_initTXT1 : m_initTXT2;
	CStdioFile file;
 
	filePath = path + name;//完整路径
									 //LPCTSTR pszFileName[i] = filePath[i].GetBufferSetLength(filePath[i].GetLength());将CString转换成LPCTSTR
	if (ret = file.Open(filePath.GetBufferSetLength(filePath.GetLength()), CFile::modeRead) == FALSE)//打开文件
	{
		AddString(_T("文件打开失败？"));
		return 0;
	}
	m_commNum[workNum] = findCoronNum(&file);            //指令条数
	/*if (findCoronNum(&file, m_commNum[workNum]) == false)
	{
		AddString(_T("脚本中无任何指令？"));
		return 0;
	}*/
	m_progress.SetRange(0, m_commNum[0]+ m_commNum[1]);
	m_progress.SetPos(0);
	m_progress.SetStep(1);

	while (!feof(file.m_pStream))//feof（）输入输出函数，检查文件是否结束，如结束，则返回非零值，否则返回0 
	{
		m_fileComm[workNum] = findCoron(&file);         //在文件中进行  寻找“:”英文冒号/中文“：”，返回读取到的一行字符str
		/*if ( m_fileComm[workNum].IsEmpty())
		{
			AddString(_T("脚本中找不到冒号:？"));
			return 0;
		}
		*/
		if (m_fileComm[workNum] == _T(""))//如果str不是空的 则sendFileComm
		{
			continue;
		}
		if (sendFileComm(&file, workNum, portIndex, Continue) == 0)//8向串口发送指令函数
		{
			return 0;
		}
	}
	file.Close();
	return 1;
}



int CcontrolSerialNetPortDlg::sensorTest(CString reValue, int* sensorValue)
{
	int sum = 0;

	for (int i = 0; i < 2; i++)
	{
		sensorValue[i] = sensorValue[i+1];
	}
	sensorValue[2] = CPublic::explainIntPos(reValue);

	for (int i = 0; i < 3; i++)
	{
		sum += sensorValue[i];
	}

	return (int)(((double)sum) / 3);

}

int CcontrolSerialNetPortDlg::AutoWorkStation(bool* Continue, int workNum)//----------------------------------------------自动流程函数（1.2）
{
	int portIndex = workNum;

	//CPublic::g_workNum = workNum;
	//CPublic::g_roundNum = round;

	CString fileData = _T("");//有什么用？？
	CString name;//自动流程名称
	CString filePath;//流程文件路径
	BOOL ret;
	CString path;
	GetModuleFileName(NULL, path.GetBufferSetLength(MAX_PATH + 1), MAX_PATH);//获取默认exe路径
	path.ReleaseBuffer();
	int pos = path.ReverseFind('\\');
	path = path.Left(pos);//去掉路径中的exe
	path = path + _T("\\");
	name = (workNum == 0) ? m_autoTXT1 : m_autoTXT2;
	CStdioFile file;

	filePath = path + name;//完整路径
						   //LPCTSTR pszFileName[i] = filePath[i].GetBufferSetLength(filePath[i].GetLength());将CString转换成LPCTSTR
	if (ret = file.Open(filePath.GetBufferSetLength(filePath.GetLength()), CFile::modeRead) == FALSE)//打开文件
	{
		AddString(_T("文件打开失败？"));
		return 0;
	}

	//char* filePath = (workNum == 0) ? "autoWork1.txt" : "autoWork2.txt";//设为变量

	//CStdioFile file;
	//if (CPublic::openFile(&file, filePath) == FALSE)
	//	return 0;

	m_commNum[workNum] = findCoronNum(&file);//冒号个数，即指令的条数
	if(m_commNum[workNum] == 0)
	{
		AddString(_T("脚本中无任何指令？"));
		return 0;
	}
	/*if (findCoronNum(&file, m_commNum[workNum]) == false)
	{
		AddString(_T("脚本中无任何指令？"));
		return 0;
	}*/
	
	m_progress.SetRange(0, m_commNum[0]+ m_commNum[1]);//为进度条控件设置范围的最小值和最大值，
	m_progress.SetPos(0);//获取进度条的当前位置
	m_progress.SetStep(1);//设置进度条前进的步长

	while(!feof(file.m_pStream))//feof检查文档是否到末尾
	{
		m_fileComm[workNum] = findCoron(&file);//return str返回冒号和它前面的字符数据，即指令名称：

		if (m_fileComm[workNum] == _T(""))//如果是空的，也就是空指令，无冒号的一行就略过
		{
			continue;
		}
		
		if (sendFileComm(&file, workNum, portIndex, Continue) == 0)//(2.1.1)向端口发送指令函数
			return 0;
	}
	file.Close();
	return 1;
}



//int CcontrolSerialNetPortDlg::imageProcess(DigHookDataStruct* DigUserHookData, PositionInfo* proResult, int workNum)//-------- （1.2.1.5.1.1）获取图像处理结果函数，获取xya数值函数
//{
//
//	DigStartAcquisition(DigUserHookData, 1); //---未进入-----------------------------------------------------------------------------（1.2.1.5.1.1.1）启动模板匹配图像处理函数
//	proResult->x =CPublic::g_positionInfo[workNum].x;//存储位置结果
//	proResult->y =CPublic::g_positionInfo[workNum].y;
//	proResult->a =CPublic::g_positionInfo[workNum].a;
//	Sleep(500);
//	return 1;
//}



//// MilImage为当前软件实时显示的图像ImageBuffer, MilOverlayImage为当前相机显示中的注释层，result为输出的结果数组
//int SingleModelExample(MIL_ID MilSystem, MIL_ID MilImage, MIL_ID MilOverlayImage, int workNum, PositionInfo* output)
//{
//	//MIL_ID MilChild;                            /* 感兴趣区图像ID*/
//	//MIL_ID MilSearchContext,                    /*模板匹配控制器ID*/
//	//	   MilResult,                           /*结果缓存ID*/
//	//	   MilEdgeContext,                      /* 边缘识别控制器ID*/ 
//	//	   MilEdgeResult;                       /* 边缘识别结果储存器ID*/ 
//	MIL_DOUBLE ModelDrawColor = M_COLOR_RED;    /* 模板线框颜色*/
//	int proNum = CPublic::g_imagePara1[workNum].proNum;
//	int maxMatchNum = CPublic::g_imagePara1[workNum].maxMatchNum;
//	int matchNum = CPublic::g_imagePara1[workNum].matchNum;
//	int ROI_x = CPublic::g_imagePara1[workNum].ROI_x;
//	int ROI_y = CPublic::g_imagePara1[workNum].ROI_y;
//	int ROI_w = CPublic::g_imagePara1[workNum].ROI_w;
//	int ROI_h = CPublic::g_imagePara1[workNum].ROI_h;
//	int MORPHIC_iteration = CPublic::g_imagePara1[workNum].iterationNum;
//
//	/*新增变量*/
//	//变量均按照上述放在CPublic::g_imagePara[CPublic::g_workNum][CPublic::g_roundNum][CPublic::g_proNum]里
//	//模板识别方法选择标识
//	MIL_CONST_TEXT_PTR  modelFilePath = CPublic::g_imagePara1[workNum].modelFilePath;
//	int MethodFlag = CPublic::g_imagePara1[workNum].MethodFlag;
//	//新增模板识别方法中增加二值化、锐化、中值滤波标识
//	int ThresholdFlag = CPublic::g_imagePara1[workNum].ThresholdFlag;
//	int SharpenFlag = CPublic::g_imagePara1[workNum].SharpenFlag;
//	int MedianFlag = CPublic::g_imagePara1[workNum].MedianFlag;
//	//模板识别二值化阈值
//	int IMAGE_THRESHOLD_VALUE = CPublic::g_imagePara1[workNum].ThresholdValue;
//	//图像边缘平滑度
//	double FilterSmoothness = CPublic::g_imagePara1[workNum].FilterSmoothness;
//	//边缘提取比例
//	double ExtractionScale = CPublic::g_imagePara1[workNum].ExtractionScale;
//	//边缘闭口大小
//	double GapDistance = CPublic::g_imagePara1[workNum].GapDistance;
//	//边缘提取连续性
//	double GapContinuity = CPublic::g_imagePara1[workNum].GapContinuity;
//	//新增变量结束
//	//选取感兴趣区并显示
//	//MbufChild2d(MilImage, ROI_x, ROI_y, ROI_w, ROI_h, &MilChild);
//
//	HMODULE hModule = LoadLibrary(L"SingleModelMatch.dll");
//	if (!hModule)
//	{
//		mainDlg->AddString(_T("动态链接库SingleModelMatch.dll加载失败！"));
//		return 0;
//	}
//	else
//	{
//		mainDlg->AddString(_T("动态链接库SingleModelMatch.dll加载成功！"));
//		/*位置结果输出定义变量并初始化*/
//		double xx = 0, yy = 0, aa = 0;
//		double *x = &xx, *y = &yy, *a = &aa;
//		/*运行单模板匹配数*/
//		singleModelMatch sMMfun;//定义了singleModelMatch类型变量sMfun，此时就可以像使用形式*singleModelMatch一样使用这个变量了。
//		sMMfun = (singleModelMatch)GetProcAddress(hModule, "SingleModelMatch");//获取动态链接库中的SingleModelExample函数
//
//		//sMMfun(MilSystem, MilImage, workNum, ROI_x, ROI_y, ROI_w, ROI_h, proNum, modelFilePath, x, y, a);
//
//		if (sMMfun(MilSystem, MilImage, workNum, ROI_x, ROI_y, ROI_w, ROI_h, proNum, modelFilePath, x, y, a) == 1)
//		{
//			//得到位置结果x y a即可
//			output->x = *x;
//			output->y = *y;
//			output->a = *a;
//			//释放资源
//
//			mainDlg->AddString(_T("线程") + CPublic::int2CString(workNum) + _T("SingleModelExample处理结果X值：") + CPublic::double2CString(*x));
//			mainDlg->AddString(_T("线程") + CPublic::int2CString(workNum) + _T("SingleModelExample处理结果Y值：") + CPublic::double2CString(*y));
//			mainDlg->AddString(_T("线程") + CPublic::int2CString(workNum) + _T("SingleModelExample处理结果A值：") + CPublic::double2CString(*a));
//			FreeLibrary(hModule);
//			//MbufFree(MilChild);
//			//MmodFree(MilSearchContext);
//			//MmodFree(MilResult);
//			//MedgeFree(MilEdgeContext);
//			//MedgeFree(MilEdgeResult);
//			return 1;
//		}
//		else
//		{
//			mainDlg->AddString(_T("模板匹配图像处理singleModelMatch错误！"));
//			FreeLibrary(hModule);
//			//MbufFree(MilChild);
//			//MmodFree(MilSearchContext);
//			//MmodFree(MilResult);
//			//MedgeFree(MilEdgeContext);
//			//MedgeFree(MilEdgeResult);
//			return 0;
//		}
//	}
//}
//	/*
//	wchar_t wcstring[256];
//	MultiByteToWideChar(CP_ACP,0,CPublic::g_imagePara[CPublic::g_workNum][CPublic::g_roundNum].modelFilePath,-1,wcstring,256);
//
//	int SearchSpeed = CPublic::g_imagePara1[workNum].searchSpeed;
//	int smoothness = CPublic::g_imagePara1[workNum].smoothness;
//	
//	MIL_INT* Model = new MIL_INT[maxMatchNum];   // 模板编号（数组）
//	MIL_INT NumResults = 0L;                  //匹配结果数
//	MIL_DOUBLE* Score = new MIL_DOUBLE[maxMatchNum];     //匹配评估结果（数组）
//	MIL_DOUBLE* XPosition = new MIL_DOUBLE[maxMatchNum];     // 匹配评估结果（数组）
//	MIL_DOUBLE* YPosition = new MIL_DOUBLE[maxMatchNum];     // 匹配评估结果（数组）
//	MIL_DOUBLE* Angle = new MIL_DOUBLE[maxMatchNum];     //匹配评估结果（数组）
//	MIL_DOUBLE* Scale = new MIL_DOUBLE[maxMatchNum];     // 匹配评估结果（数组）
//	MIL_DOUBLE Time = 0.0;                       //所用时间 
//
//	选取感兴趣区并显示
//	MbufChild2d(MilImage, ROI_x, ROI_y, ROI_w, ROI_h, &MilChild);
//
//	分配边缘识别控制器 
//	MedgeAlloc(MilSystem, M_CONTOUR, M_DEFAULT, &MilEdgeContext);
//
//	 分配边缘识别结果储存器 
//	MedgeAllocResult(MilSystem, M_DEFAULT, &MilEdgeResult);
//
//
//	if (MethodFlag == 0)//老的模板识别方法，针对上下力矩座
//	{
//		预处理
//		MimMorphic(MilChild, MilChild, M_3X3_RECT, M_AREA_OPEN, MORPHIC_iteration, M_GRAYSCALE);
//		MimMorphic(MilChild, MilChild, M_3X3_RECT, M_AREA_CLOSE, MORPHIC_iteration, M_GRAYSCALE);
//
//		匹配环境设置
//		MmodAlloc(MilSystem, M_GEOMETRIC, M_DEFAULT, &MilSearchContext); //分配匹配控制器
//		MmodAllocResult(MilSystem, M_DEFAULT, &MilResult);//分配结果缓存 
//
//		定义模板
//
//		MmodDefineFromFile(MilSearchContext, M_DXF_FILE, CPublic::g_imagePara1[workNum].modelFilePath, M_DEFAULT); //从文件定义模板
//
//
//		设置匹配参数 
//		MmodControl(MilSearchContext, M_CONTEXT, M_SPEED, SearchSpeed);  //设置匹配速度 
//		MmodControl(MilSearchContext, M_CONTEXT, M_SMOOTHNESS, smoothness);      //设置匹配平滑度（对于识别到的边缘进行平滑处理）
//		MmodControl(MilSearchContext, M_DEFAULT, M_NUMBER, matchNum);          //匹配目标数 
//		MmodControl(MilResult, M_DEFAULT, M_DRAW_RELATIVE_ORIGIN_X, -ROI_x);
//		MmodControl(MilResult, M_DEFAULT, M_DRAW_RELATIVE_ORIGIN_Y, -ROI_y);
//
//		
//		匹配预处理 
//		MmodPreprocess(MilSearchContext, M_DEFAULT);
//
//		执行匹配
//		MappTimer(M_TIMER_RESET+M_SYNCHRONOUS, M_NULL);//启动计时器 
//		MmodFind(MilSearchContext, MilChild, MilResult);
//		MappTimer(M_TIMER_READ+M_SYNCHRONOUS, &Time);//读取时间 
//	}
//	else if (MethodFlag == 2)//新的处理方法（针对摆片组件）
//	{
//		预处理
//		if (SharpenFlag == 1)
//		{
//			MimConvolve(MilChild, MilChild, M_SHARPEN);	//	sharpen
//		}
//		if (ThresholdFlag == 1)
//		{
//			MimBinarize(MilChild, MilChild, M_LESS_OR_EQUAL, IMAGE_THRESHOLD_VALUE, M_NULL);	//二值化
//		}
//		if (MedianFlag == 1)
//		{
//			MimRank(MilChild, MilChild, M_3X3_RECT, M_MEDIAN, M_GRAYSCALE);//中值滤波
//		}
//		MimMorphic(MilChild, MilChild, M_3X3_RECT, M_AREA_OPEN, MORPHIC_iteration, M_GRAYSCALE);
//		MimMorphic(MilChild, MilChild, M_3X3_RECT, M_AREA_CLOSE, MORPHIC_iteration, M_GRAYSCALE);
//
//		MimConvolve(MilChild, MilChild, M_EDGE_DETECT);
//
//		边缘识别开始
//
//		 分配边缘识别控制器 
//		MedgeAlloc(MilSystem, M_CONTOUR, M_DEFAULT, &MilEdgeContext);
//
//		 分配边缘识别结果储存器 
//		MedgeAllocResult(MilSystem, M_DEFAULT, &MilEdgeResult);
//
//		 边缘识别控制：边缘强度设置；边缘平滑滤波；线条间隙填充，通过边缘进行模板匹配
//		MedgeControl(MilEdgeContext, M_THRESHOLD_MODE, M_HIGH);
//		MedgeControl(MilEdgeContext, M_FILTER_SMOOTHNESS, FilterSmoothness);
//		MedgeControl(MilEdgeContext, M_EXTRACTION_SCALE, FilterSmoothness);
//
//		MedgeControl(MilEdgeContext, M_FILL_GAP_CANDIDATE, M_DEFAULT);
//		MedgeControl(MilEdgeContext, M_FILL_GAP_DISTANCE, GapDistance);
//		MedgeControl(MilEdgeContext, M_FILL_GAP_CONTINUITY, GapContinuity);
//		MedgeControl(MilEdgeResult, M_MODEL_FINDER_COMPATIBLE, M_ENABLE);
//		边缘识别计算 
//		MedgeCalculate(MilEdgeContext, MilChild, M_NULL, M_NULL, M_NULL, MilEdgeResult, M_DEFAULT);
//
//		寻找边缘结束
//
//
//		匹配环境设置
//		MmodAlloc(MilSystem, M_GEOMETRIC, M_DEFAULT, &MilSearchContext); //分配匹配控制器
//		MmodAllocResult(MilSystem, M_DEFAULT, &MilResult);//分配结果缓存 
//
//		定义模板
//
//		MmodDefineFromFile(MilSearchContext, M_DXF_FILE, CPublic::g_imagePara1[workNum].modelFilePath, M_DEFAULT); //从文件定义模板
//
//
//		设置匹配参数 
//		MmodControl(MilSearchContext, M_CONTEXT, M_SPEED, SearchSpeed);  //设置匹配速度 
//		MmodControl(MilSearchContext, M_CONTEXT, M_SMOOTHNESS, smoothness);      //设置匹配平滑度（对于识别到的边缘进行平滑处理） 
//		MmodControl(MilSearchContext, M_DEFAULT, M_NUMBER, matchNum);          //匹配目标数 
//		MmodControl(MilResult, M_DEFAULT, M_DRAW_RELATIVE_ORIGIN_X, -ROI_x);
//		MmodControl(MilResult, M_DEFAULT, M_DRAW_RELATIVE_ORIGIN_Y, -ROI_y);
//
//
//		匹配预处理 
//		MmodPreprocess(MilSearchContext, M_DEFAULT);
//
//		执行匹配
//		MappTimer(M_TIMER_RESET+M_SYNCHRONOUS, M_NULL);启动计时器 
//		MmodFind(MilSearchContext, MilEdgeResult, MilResult);//在边缘结果进行识别
//		MappTimer(M_TIMER_READ+M_SYNCHRONOUS, &Time);读取时间 
//	}
//
//	读取匹配结果数
//	MmodGetResult(MilResult, M_DEFAULT, M_NUMBER + M_TYPE_MIL_INT, &NumResults);
//
//	读取打印结果 ，应该返回什么值？是这NumResults组数据的平均值吗？应返回XPosition，YPosition和angel吗？ 
//	依然返回XPosition[0], YPosition[0], Angle[0],在if括号里对多匹配的情况进行了平均处理。
//	if ((NumResults >= 1) && (NumResults <= maxMatchNum))
//	{
//		MmodGetResult(MilResult, M_DEFAULT, M_INDEX + M_TYPE_MIL_INT, Model);
//		MmodGetResult(MilResult, M_DEFAULT, M_POSITION_X, XPosition);
//		MmodGetResult(MilResult, M_DEFAULT, M_POSITION_Y, YPosition);
//		MmodGetResult(MilResult, M_DEFAULT, M_ANGLE, Angle);
//		MmodGetResult(MilResult, M_DEFAULT, M_SCALE, Scale);
//		MmodGetResult(MilResult, M_DEFAULT, M_SCORE, Score);
//
//		加入结果数量判断，若结果数量为2，取所得两个结果的均值
//
//		if (NumResults == 2)
//		{
//			XPosition[0] = (XPosition[0] + XPosition[1]) / 2;
//			YPosition[0] = (YPosition[0] + YPosition[1]) / 2;
//			Angle[0] = (Angle[0] + Angle[1]) / 2;
//		}
//
//		加入特征点位置调整
//		XPosition[0] = XPosition[0] + CPublic::g_imagePara1[workNum].modelDistance *cos(3.1415926 * Angle[0] / 180) + CPublic::g_imagePara1[workNum].ROI_x;
//		YPosition[0] = YPosition[0] - CPublic::g_imagePara1[workNum].modelDistance *sin(3.1415926 * Angle[0] / 180) + CPublic::g_imagePara1[workNum].ROI_y;
//
//
//		output->x = XPosition[0];
//		output->y = YPosition[0];
//		output->a = Angle[0];
//	
//		mainDlg->AddString(_T("工位") + CPublic::int2CString(workNum) + _T("single内部计算图像处理结果X值：") + CPublic::double2CString(XPosition[0]));
//		mainDlg->AddString(_T("工位") + CPublic::int2CString(workNum) + _T("single内部计算图像处理结果Y值：") +  CPublic::double2CString(YPosition[0]));
//		mainDlg->AddString(_T("工位") + CPublic::int2CString(workNum) + _T("single内部计算图像处理结果A值：") + CPublic::double2CString(Angle[0]));
//
//	}
//else
//	{
//		mainDlg->AddString(_T("匹配失败？"));
//		mainDlg->AddString(_T("工位") + CPublic::int2CString(workNum) + _T("single内部计算图像处理结果X值：") + CPublic::double2CString(XPosition[0]));
//		mainDlg->AddString(_T("工位") + CPublic::int2CString(workNum) + _T("single内部计算图像处理结果Y值：") +  CPublic::double2CString(YPosition[0]));
//		mainDlg->AddString(_T("工位") + CPublic::int2CString(workNum) + _T("single内部计算图像处理结果A值：") + CPublic::double2CString(Angle[0]));
//		MbufFree(MilChild);
//		MmodFree(MilSearchContext);
//		MmodFree(MilResult);
//		MedgeFree(MilEdgeContext);
//		MedgeFree(MilEdgeResult);
//		delete Model;
//		delete Score;
//		delete XPosition;
//		delete YPosition;
//		delete Angle;
//		delete Scale;
//		return 0;
//
//	}
//	
//*/	
//	/* 结束并释放资源*/
//    
//	/*delete Model;
//	delete Score;
//	delete XPosition;
//	delete YPosition;
//	delete Angle;
//	delete Scale;*/
//
////该模板识别程序用于13所工艺中模板识别函数2~4（用来进行焊接柱识别）


//int CircleFinderExample+(MIL_ID MilSystem, MIL_ID MilImage, MIL_ID MilOverlayImage, int workNum, PositionInfo* output)
//{
//	MIL_ID 
//		//播放窗口ID
//		MilChild,
//		MilEdgeContext,                         // 边缘识别控制器ID*/
//		MilEdgeResult;                          // 边缘识别结果储存器ID*/
//	MIL_DOUBLE  EdgeDrawColor = 30,             // 边缘注释颜色*/
//		LabelDrawColor = 30;           //标签注释颜色*/
//
//	MIL_DOUBLE Radius[1];                                  // 拟合圆直径*/
//	MIL_DOUBLE MeanCircleX[1];                             // 拟合圆心X坐标*/
//	MIL_DOUBLE MeanCircleY[1];                             // 拟合圆心Y坐标*/
//
//	MIL_INT NumResults = 1;                               //符合要求的圆的个数
//
//	//初始化应用环境
//	int proNum = CPublic::g_imagePara2[workNum].proNum;
//	int ROI_x = CPublic::g_imagePara2[workNum].ROI_x;
//	int ROI_y = CPublic::g_imagePara2[workNum].ROI_y;
//	int ROI_w = CPublic::g_imagePara2[workNum].ROI_w;
//	int ROI_h = CPublic::g_imagePara2[workNum].ROI_h;
//	int MORPHIC_iteration = CPublic::g_imagePara2[workNum].iterationNum;
//	//模板识别方法中增加二值化标识
//	int ThresholdFlag = CPublic::g_imagePara2[workNum].ThresholdFlag;
//	//模板识别二值化阈值
//	int IMAGE_THRESHOLD_VALUE = CPublic::g_imagePara2[workNum].ThresholdValue;
//	//图像边缘平滑度
//	double FilterSmoothness = CPublic::g_imagePara2[workNum].FilterSmoothness;
//	//边缘提取比例
//	double ExtractionScale = CPublic::g_imagePara2[workNum].ExtractionScale;
//	//边缘闭口大小
//	double GapDistance = CPublic::g_imagePara2[workNum].GapDistance;
//	//边缘提取连续性
//	double GapContinuity = CPublic::g_imagePara2[workNum].GapContinuity;
//	//圆检测半径下限、上限
//	double CricleRadius_Low = CPublic::g_imagePara2[workNum].CricleRadius_Low;
//	double CricleRadius_High = CPublic::g_imagePara2[workNum].CricleRadius_High;
//
//	// 载入原图像并显示 
//	//MbufRestore(M_INTERACTIVE, MilSystem, &MilImage);
//	MbufChild2d(MilImage, ROI_x, ROI_y, ROI_w, ROI_h, &MilChild);//13所
//	// 功能显示
//
//	HMODULE hModule = LoadLibrary(L"CircleFinder.dll");
//	if (!hModule)
//	{
//		mainDlg->AddString(_T("点匹配图像处理需要的动态链接库CircleFinder.dll加载失败！"));
//	}
//	/*位置结果输出定义变量并初始化*/
//	double xx = 0, yy = 0, aa = 0;
//	double *x = &xx, *y = &yy, *a = &aa;
//	//函数运行
//	CircleFinder CFfun;//定义了CircleFinder类型变量CFfun，此时就可以像使用形式*CircleFinder一样使用这个变量了。
//	CFfun = (CircleFinder)GetProcAddress(hModule, "CircleFinder");//获取动态链接库中的SingleModelExample函数
//
//	if (CFfun(MilSystem, MilImage, workNum, ROI_x, ROI_y, ROI_w, ROI_h, proNum, CricleRadius_Low, CricleRadius_High, x, y, a) == 1)
//	{
//		//得到位置结果x y a即可
//		output->x = *x;
//		output->y = *y;
//		output->a = *a;
//		//释放资源
//
//		mainDlg->AddString(_T("线程") + CPublic::int2CString(workNum) + _T("CircleFinder处理结果X值：") + CPublic::double2CString(*x));
//		mainDlg->AddString(_T("线程") + CPublic::int2CString(workNum) + _T("CircleFinder处理结果Y值：") + CPublic::double2CString(*y));
//		mainDlg->AddString(_T("线程") + CPublic::int2CString(workNum) + _T("CircleFinder处理结果A值：") + CPublic::double2CString(*a));
//		FreeLibrary(hModule);
//		MbufFree(MilChild);
//		MedgeFree(MilEdgeContext);
//		MedgeFree(MilEdgeResult);
//		return 1;
//	}
//	else
//	{
//		mainDlg->AddString(_T("图像处理模板匹配CircleFinder错误！"));
//		FreeLibrary(hModule);
//		MbufFree(MilChild);
//		MedgeFree(MilEdgeContext);
//		MedgeFree(MilEdgeResult);
//		return 0;
//	}
//
//	/*
//	// 二值化，区域开闭预算
//	if (ThresholdFlag == 1)
//	{
//		MimBinarize(MilChild, MilChild, M_LESS_OR_EQUAL, IMAGE_THRESHOLD_VALUE, M_NULL);
//	}
//	MimMorphic(MilChild, MilChild, M_3X3_RECT, M_AREA_OPEN, MORPHIC_iteration, M_GRAYSCALE);
//	MimMorphic(MilChild, MilChild, M_3X3_RECT, M_AREA_CLOSE, MORPHIC_iteration, M_GRAYSCALE);
//	// 分配边缘识别控制器 
//	MedgeAlloc(MilSystem, M_CONTOUR, M_DEFAULT, &MilEdgeContext);
//
//	// 分配边缘识别结果储存器
//	MedgeAllocResult(MilSystem, M_DEFAULT, &MilEdgeResult);
//
//	// 边缘识别控制：边缘强度设置；边缘平滑滤波；线条间隙填充；拟合圆检测 
//	MedgeControl(MilEdgeContext, M_THRESHOLD_MODE, M_HIGH);
//	MedgeControl(MilEdgeContext, M_FILTER_SMOOTHNESS, FilterSmoothness);
//	MedgeControl(MilEdgeContext, M_EXTRACTION_SCALE, ExtractionScale);
//
//	MedgeControl(MilEdgeContext, M_FILL_GAP_CANDIDATE, M_DEFAULT);
//	MedgeControl(MilEdgeContext, M_FILL_GAP_DISTANCE, GapDistance);
//	MedgeControl(MilEdgeContext, M_FILL_GAP_CONTINUITY, GapContinuity);
//
//	//寻找圆
//	MedgeControl(MilEdgeContext, M_CIRCLE_FIT_RADIUS, M_ENABLE);
//	MedgeControl(MilEdgeContext, M_CIRCLE_FIT_CENTER_X, M_ENABLE);
//	MedgeControl(MilEdgeContext, M_CIRCLE_FIT_CENTER_Y, M_ENABLE);
//
//	// 边缘识别计算 
//
//	MedgeCalculate(MilEdgeContext, MilChild, M_NULL, M_NULL, M_NULL, MilEdgeResult, M_DEFAULT);
//
//
//	MedgeSelect(MilEdgeResult, M_DELETE, M_CIRCLE_FIT_RADIUS, M_OUT_RANGE, CricleRadius_Low, CricleRadius_High);
//
//
//
//	//Pause to show the results.
//	MedgeGetResult(MilEdgeResult, M_DEFAULT, M_CIRCLE_FIT_RADIUS, Radius, M_NULL);
//	MedgeGetResult(MilEdgeResult, M_DEFAULT, M_CIRCLE_FIT_CENTER_X, MeanCircleX, M_NULL);
//	MedgeGetResult(MilEdgeResult, M_DEFAULT, M_CIRCLE_FIT_CENTER_Y, MeanCircleY, M_NULL);
//
//
//	output->x = MeanCircleX[0] + ROI_x;
//	output->y = MeanCircleY[0] + ROI_y;
//	output->a = Radius[0];
//
//	MbufFree(MilChild);
//	MedgeFree(MilEdgeContext);
//	MedgeFree(MilEdgeResult);
//
//	//MappFreeDefault(MilApplication, MilSystem, MilDisplay, M_NULL, M_NULL);
//
//	return 1;
//	*/
//}
//



void CcontrolSerialNetPortDlg::SetAxisParameter(void)
{

	CString szLabel;
	int ByteLen[2] = {0};

	//读取配置文件
	char szValue[MAX_PATH];
	//CString szValue;
	int len = MAX_PATH;
	CPublic::GetConfigString("Parameter", "Count", szValue, len);
	int iCount = atoi(szValue);
	//USES_CONVERSION;
	char charLabel[50];

	for ( int i = 0; i < iCount; i++ )
	{

		//获取运动模式
		szLabel.Format(_T("mode%d"), i+1);
		CPublic::CString2char(szLabel, charLabel);
		CPublic::GetConfigString("Parameter", (LPCSTR)(charLabel), szValue, len);
		CPublic::g_parameter[i].mode = atoi(szValue);

		//获取开始速度
		szLabel.Format(_T("startspeed%d"), i+1);
		CPublic::CString2char(szLabel, charLabel);
		CPublic::GetConfigString("Parameter", (LPCSTR)(charLabel), szValue, len);
		CPublic::g_parameter[i].startSpeed = atoi(szValue);


		//获取目标速度
		szLabel.Format(_T("targetspeed%d"), i+1);
		CPublic::CString2char(szLabel, charLabel);
		CPublic::GetConfigString("Parameter", (LPCSTR)(charLabel), szValue, len);
		CPublic::g_parameter[i].targetSpeed = atoi(szValue);

		//获取目标速度
		szLabel.Format(_T("accelspeed%d"), i+1);
		CPublic::CString2char(szLabel, charLabel);
		CPublic::GetConfigString("Parameter", (LPCSTR)(charLabel), szValue, len);
		CPublic::g_parameter[i].accelSpeed = atoi(szValue);

		//获取目标位置
		szLabel.Format(_T("targetsteps%d"), i+1);
		CPublic::CString2char(szLabel, charLabel);
		CPublic::GetConfigString("Parameter", (LPCSTR)(charLabel), szValue, len);
		CPublic::g_parameter[i].steps = atoi(szValue);


	}

}

void CcontrolSerialNetPortDlg::SetInitAutoParameter(int workNum)
{

	CString szLabel;
	int ByteLen[2] = {0};

	//读取配置文件
	char szValue[MAX_PATH];
	//CString szValue;
	int len = MAX_PATH;
	/*CPublic::GetConfigString("Parameter", "Count", szValue, len);
	int iCount = atoi(szValue);*/
	//USES_CONVERSION;
	char charLabel[50];
	char labelID[20];

	if (workNum == 0)
	{
		memcpy(labelID, "InitParameter1", sizeof("InitParameter1"));
	}else if ((workNum == 1))
	{
		memcpy(labelID, "InitParameter2", sizeof("InitParameter2"));
	}

	//for ( int i = 0; i < initStepNum - 1; i++ )
	//{
	//	//获取开始速度
	//	szLabel.Format(_T("startspeed%d"), i+1);
	//	CPublic::CString2char(szLabel, charLabel);
	//	CPublic::GetConfigString(labelID, (LPCSTR)(charLabel), szValue, len);
	//	CPublic::g_initParameter[workNum][i].startspeed = atoi(szValue);


	//	//获取目标速度
	//	szLabel.Format(_T("targetspeed%d"), i+1);
	//	CPublic::CString2char(szLabel, charLabel);
	//	CPublic::GetConfigString(labelID, (LPCSTR)(charLabel), szValue, len);
	//	CPublic::g_initParameter[workNum][i].targetspeed = atoi(szValue);

	//	//获取加速度
	//	szLabel.Format(_T("accelspeed%d"), i+1);
	//	CPublic::CString2char(szLabel, charLabel);
	//	CPublic::GetConfigString(labelID, (LPCSTR)(charLabel), szValue, len);
	//	CPublic::g_initParameter[workNum][i].accelspeed = atoi(szValue);

	//	//获取目标位置
	//	szLabel.Format(_T("targetsteps%d"), i+1);
	//	CPublic::CString2char(szLabel, charLabel);
	//	CPublic::GetConfigString(labelID, (LPCSTR)(charLabel), szValue, len);
	//	CPublic::g_initParameter[workNum][i].steps = atoi(szValue);
	//}

	/*memcpy(charLabel, "cameraSteps", sizeof("cameraSteps"));
	CPublic::GetConfigString(labelID, (LPCSTR)(charLabel), szValue, len);
	CPublic::g_newinitParameter[workNum].cameraSteps = atoi(szValue);

	memcpy(charLabel, "axisYSteps", sizeof("axisYSteps"));
	CPublic::GetConfigString(labelID, (LPCSTR)(charLabel), szValue, len);
	CPublic::g_newinitParameter[workNum].axisYSteps = atoi(szValue);

	memcpy(charLabel, "axisXSteps", sizeof("axisXSteps"));
	CPublic::GetConfigString(labelID, (LPCSTR)(charLabel), szValue, len);
	CPublic::g_newinitParameter[workNum].axisXSteps = atoi(szValue);

	memcpy(charLabel, "axis6Steps", sizeof("axis6Steps"));
	CPublic::GetConfigString(labelID, (LPCSTR)(charLabel), szValue, len);
	CPublic::g_newinitParameter[workNum].axis6Steps = atoi(szValue);

	memcpy(charLabel, "prismSteps", sizeof("prismSteps"));
	CPublic::GetConfigString(labelID, (LPCSTR)(charLabel), szValue, len);
	CPublic::g_newinitParameter[workNum].prismSteps = atoi(szValue);

	memcpy(charLabel, "axis3Steps", sizeof("axis3Steps"));
	CPublic::GetConfigString(labelID, (LPCSTR)(charLabel), szValue, len);
	CPublic::g_newinitParameter[workNum].axis3Steps = atoi(szValue);

	memcpy(charLabel, "axis8Steps", sizeof("axis8Steps"));
	CPublic::GetConfigString(labelID, (LPCSTR)(charLabel), szValue, len);
	CPublic::g_newinitParameter[workNum].axis8Steps = atoi(szValue);

	memcpy(charLabel, "axis9Steps", sizeof("axis9Steps"));
	CPublic::GetConfigString(labelID, (LPCSTR)(charLabel), szValue, len);
	CPublic::g_newinitParameter[workNum].axis9Steps = atoi(szValue);*/

	memcpy(charLabel, "angelErrorX", sizeof("angelErrorX"));
	CPublic::GetConfigString(labelID, (LPCSTR)(charLabel), szValue, len);
	CPublic::g_newinitParameter[workNum].angelErrorX = atof(szValue);

	memcpy(charLabel, "angelErrorY", sizeof("angelErrorY"));
	CPublic::GetConfigString(labelID, (LPCSTR)(charLabel), szValue, len);
	CPublic::g_newinitParameter[workNum].angelErrorY = atof(szValue);

	memcpy(charLabel, "ratioX", sizeof("ratioX"));
	CPublic::GetConfigString(labelID, (LPCSTR)(charLabel), szValue, len);
	CPublic::g_newinitParameter[workNum].ratioX = atof(szValue);


	memcpy(charLabel, "ratioY", sizeof("ratioY"));
	CPublic::GetConfigString(labelID, (LPCSTR)(charLabel), szValue, len);
	CPublic::g_newinitParameter[workNum].ratioY = atof(szValue);

	memcpy(charLabel, "ratioA", sizeof("ratioA"));
	CPublic::GetConfigString(labelID, (LPCSTR)(charLabel), szValue, len);
	CPublic::g_newinitParameter[workNum].ratioA = atof(szValue);


	for (int i = 0; i < CALIBRATION_NUM; i++)
	{
		szLabel.Format(_T("posX%d"), i+1);
		CPublic::CString2char(szLabel, charLabel);
		CPublic::GetConfigString(labelID, (LPCSTR)(charLabel), szValue, len);
		CPublic::g_newinitParameter[workNum].posX[i] = atof(szValue);

		szLabel.Format(_T("posY%d"), i+1);
		CPublic::CString2char(szLabel, charLabel);
		CPublic::GetConfigString(labelID, (LPCSTR)(charLabel), szValue, len);
		CPublic::g_newinitParameter[workNum].posY[i] = atof(szValue);

		szLabel.Format(_T("posA%d"), i+1);
		CPublic::CString2char(szLabel, charLabel);
		CPublic::GetConfigString(labelID, (LPCSTR)(charLabel), szValue, len);
		CPublic::g_newinitParameter[workNum].posA[i] = atof(szValue);
		
	}

	memcpy(labelID, "Error", sizeof("Error"));
	memcpy(charLabel, "stepsError", sizeof("stepsError"));
	CPublic::GetConfigString(labelID, (LPCSTR)(charLabel), szValue, len);
	CPublic::stepsError = atoi(szValue);

	memcpy(charLabel, "sensorError", sizeof("sensorError"));
	CPublic::GetConfigString(labelID, (LPCSTR)(charLabel), szValue, len);
	CPublic::sensorError = atof(szValue);

	//autoparameter
	//CString m_fileComm = _T("");
	//if (workNum == 0)
	//{
	//	memcpy(labelID, "AutoParameter1", sizeof("AutoParameter1"));
	//}else if ((workNum == 1))
	//{
	//	memcpy(labelID, "AutoParameter2", sizeof("AutoParameter2"));
	//}else
	//{
	//	memcpy(labelID, "AutoParameter3", sizeof("AutoParameter3"));
	//}

	//memcpy(charLabel, "delayTime2", sizeof("delayTime2"));
	//CPublic::GetConfigString(labelID, (LPCSTR)(charLabel), szValue, len);
	//CPublic::g_AutoParameter[workNum].delayTime2 = atoi(szValue);

	////memcpy(charLabel, "steps4", sizeof("steps4"));
	////CPublic::GetConfigString(labelID, (LPCSTR)(charLabel), szValue, len);
	////CPublic::g_AutoParameter[workNum].steps4 = atoi(szValue);

	//for (int i = 0; i < 6; i++)
	//{
	//	memcpy(charLabel, "steps4_", 7);
	//	itoa(i+1, charLabel+7, 10);
	//	charLabel[8] = '\0';
	//	CPublic::GetConfigString(labelID, (LPCSTR)(charLabel), szValue, len);
	//	CPublic::g_AutoParameter[workNum].steps4[i] = atoi(szValue);

	//}

	//memcpy(charLabel, "steps5_1", sizeof("steps5_1"));
	//CPublic::GetConfigString(labelID, (LPCSTR)(charLabel), szValue, len);
	//CPublic::g_AutoParameter[workNum].steps5_1 = atoi(szValue);

	//memcpy(charLabel, "steps5_2", sizeof("steps5_2"));
	//CPublic::GetConfigString(labelID, (LPCSTR)(charLabel), szValue, len);
	//CPublic::g_AutoParameter[workNum].steps5_2 = atoi(szValue);

	//memcpy(charLabel, "steps6", sizeof("steps6"));
	//CPublic::GetConfigString(labelID, (LPCSTR)(charLabel), szValue, len);
	//CPublic::g_AutoParameter[workNum].steps6 = atoi(szValue);

	//memcpy(charLabel, "delayTime7", sizeof("delayTime7"));
	//CPublic::GetConfigString(labelID, (LPCSTR)(charLabel), szValue, len);
	//CPublic::g_AutoParameter[workNum].delayTime7 = atoi(szValue);

	//memcpy(charLabel, "delayTime8", sizeof("delayTime8"));
	//CPublic::GetConfigString(labelID, (LPCSTR)(charLabel), szValue, len);
	//CPublic::g_AutoParameter[workNum].delayTime8 = atoi(szValue);


	//memcpy(charLabel, "steps9", sizeof("steps9"));
	//CPublic::GetConfigString(labelID, (LPCSTR)(charLabel), szValue, len);
	//CPublic::g_AutoParameter[workNum].steps9 = atoi(szValue);

	//memcpy(charLabel, "steps10_1", sizeof("steps10_1"));
	//CPublic::GetConfigString(labelID, (LPCSTR)(charLabel), szValue, len);
	//CPublic::g_AutoParameter[workNum].steps10_1 = atoi(szValue);


	//memcpy(charLabel, "steps10_2", sizeof("steps10_2"));
	//CPublic::GetConfigString(labelID, (LPCSTR)(charLabel), szValue, len);
	//CPublic::g_AutoParameter[workNum].steps10_2 = atoi(szValue);

	//memcpy(charLabel, "steps10_3", sizeof("steps10_3"));
	//CPublic::GetConfigString(labelID, (LPCSTR)(charLabel), szValue, len);
	//CPublic::g_AutoParameter[workNum].steps10_3 = atoi(szValue);

	//memcpy(charLabel, "delayTime10", sizeof("delayTime10"));
	//CPublic::GetConfigString(labelID, (LPCSTR)(charLabel), szValue, len);
	//CPublic::g_AutoParameter[workNum].delayTime10 = atoi(szValue);

	//memcpy(charLabel, "steps10_4", sizeof("steps10_4"));
	//CPublic::GetConfigString(labelID, (LPCSTR)(charLabel), szValue, len);
	//CPublic::g_AutoParameter[workNum].steps10_4 = atoi(szValue);


	//memcpy(charLabel, "steps10_5", sizeof("steps10_5"));
	//CPublic::GetConfigString(labelID, (LPCSTR)(charLabel), szValue, len);
	//CPublic::g_AutoParameter[workNum].steps10_5 = atoi(szValue);

	//memcpy(charLabel, "steps10_6", sizeof("steps10_6"));
	//CPublic::GetConfigString(labelID, (LPCSTR)(charLabel), szValue, len);
	//CPublic::g_AutoParameter[workNum].steps10_6 = atoi(szValue);

	//memcpy(charLabel, "steps11", sizeof("steps11"));
	//CPublic::GetConfigString(labelID, (LPCSTR)(charLabel), szValue, len);
	//CPublic::g_AutoParameter[workNum].steps11 = atoi(szValue);

	//memcpy(charLabel, "delayTime11", sizeof("delayTime11"));
	//CPublic::GetConfigString(labelID, (LPCSTR)(charLabel), szValue, len);
	//CPublic::g_AutoParameter[workNum].delayTime11 = atoi(szValue);


	//memcpy(charLabel, "dispense1", sizeof("dispense1"));
	//CPublic::GetConfigString(labelID, (LPCSTR)(charLabel), szValue, len);
	//CPublic::g_AutoParameter[workNum].dispense1 = atoi(szValue);

	//memcpy(charLabel, "dispense2", sizeof("dispense2"));
	//CPublic::GetConfigString(labelID, (LPCSTR)(charLabel), szValue, len);
	//CPublic::g_AutoParameter[workNum].dispense2 = atoi(szValue);

	//for (int i = 0; i < 6; i++)
	//{
	//	memcpy(charLabel, "dispenseA_", 10);
	//	itoa(i+1, charLabel+10, 10);
	//	charLabel[11] = '\0';
	//	CPublic::GetConfigString(labelID, (LPCSTR)(charLabel), szValue, len);
	//	CPublic::g_AutoParameter[workNum].dispenseA[i] = atoi(szValue);

	//}


	//memcpy(charLabel, "angelErrorX", sizeof("angelErrorX"));
	//CPublic::GetConfigString(labelID, (LPCSTR)(charLabel), szValue, len);
	//CPublic::g_AutoParameter[workNum].angErrorX = atof(szValue);

	//memcpy(charLabel, "angelErrorY", sizeof("angelErrorY"));
	//CPublic::GetConfigString(labelID, (LPCSTR)(charLabel), szValue, len);
	//CPublic::g_AutoParameter[workNum].angErrorY = atof(szValue);

	//memcpy(charLabel, "ratioX", sizeof("ratioX"));
	//CPublic::GetConfigString(labelID, (LPCSTR)(charLabel), szValue, len);
	//CPublic::g_AutoParameter[workNum].ratioX = atof(szValue);


	//memcpy(charLabel, "ratioY", sizeof("ratioY"));
	//CPublic::GetConfigString(labelID, (LPCSTR)(charLabel), szValue, len);
	//CPublic::g_AutoParameter[workNum].ratioY = atof(szValue);

	//memcpy(charLabel, "ratioA", sizeof("ratioA"));
	//CPublic::GetConfigString(labelID, (LPCSTR)(charLabel), szValue, len);
	//CPublic::g_AutoParameter[workNum].ratioA = atof(szValue);

	//for ( int i = 0; i < ROUND; i++ )
	//{
	//	for (int j = 0; j < PRONUM; j++)
	//	{
	//		//获取搜索速度模式
	//		szLabel.Format(_T("searchSpeedMode%d"), (i* PRONUM)+(j+1));
	//		CPublic::CString2char(szLabel, charLabel);
	//		CPublic::GetConfigString(labelID, (LPCSTR)(charLabel), szValue, len);
	//		CPublic::g_imagePara[workNum][i][j].searchSpeedMode = atoi(szValue);

	//		//最大匹配数
	//		szLabel.Format(_T("maxMatchNum%d"), (i* PRONUM)+(j+1));
	//		CPublic::CString2char(szLabel, charLabel);
	//		CPublic::GetConfigString(labelID, (LPCSTR)(charLabel), szValue, len);
	//		CPublic::g_imagePara[workNum][i][j].maxMatchNum = atoi(szValue);

	//		//匹配数
	//		szLabel.Format(_T("matchNum%d"), (i* PRONUM)+(j+1));
	//		CPublic::CString2char(szLabel, charLabel);
	//		CPublic::GetConfigString(labelID, (LPCSTR)(charLabel), szValue, len);
	//		CPublic::g_imagePara[workNum][i][j].matchNum = atoi(szValue);

	//		szLabel.Format(_T("modelFilePath%d"), (i* PRONUM)+(j+1));
	//		CPublic::CString2char(szLabel, charLabel);
	//		CPublic::GetConfigString(labelID, (LPCSTR)(charLabel), szValue, len);
	//		CPublic::g_imagePara[workNum][i][j].modelFilePath = CPublic::char2CString(szValue, strlen(szValue));

	//		szLabel.Format(_T("smoothness%d"), (i* PRONUM)+(j+1));
	//		CPublic::CString2char(szLabel, charLabel);
	//		CPublic::GetConfigString(labelID, (LPCSTR)(charLabel), szValue, len);
	//		CPublic::g_imagePara[workNum][i][j].smoothness = atoi(szValue);

	//		szLabel.Format(_T("iterationNum%d"), (i* PRONUM)+(j+1));
	//		CPublic::CString2char(szLabel, charLabel);
	//		CPublic::GetConfigString(labelID, (LPCSTR)(charLabel), szValue, len);
	//		CPublic::g_imagePara[workNum][i][j].iterationNum = atoi(szValue);

	//		szLabel.Format(_T("modelDistance%d"), (i* PRONUM)+(j+1));
	//		CPublic::CString2char(szLabel, charLabel);
	//		CPublic::GetConfigString(labelID, (LPCSTR)(charLabel), szValue, len);
	//		CPublic::g_imagePara[workNum][i][j].modelDistance = atoi(szValue);

	//		szLabel.Format(_T("ROI_x%d"), (i* PRONUM)+(j+1));
	//		CPublic::CString2char(szLabel, charLabel);
	//		CPublic::GetConfigString(labelID, (LPCSTR)(charLabel), szValue, len);
	//		CPublic::g_imagePara[workNum][i][j].ROI_x = atoi(szValue);

	//		szLabel.Format(_T("ROI_y%d"), (i* PRONUM)+(j+1));
	//		CPublic::CString2char(szLabel, charLabel);
	//		CPublic::GetConfigString(labelID, (LPCSTR)(charLabel), szValue, len);
	//		CPublic::g_imagePara[workNum][i][j].ROI_y = atoi(szValue);

	//		szLabel.Format(_T("ROI_w%d"), (i* PRONUM)+(j+1));
	//		CPublic::CString2char(szLabel, charLabel);
	//		CPublic::GetConfigString(labelID, (LPCSTR)(charLabel), szValue, len);
	//		CPublic::g_imagePara[workNum][i][j].ROI_w = atoi(szValue);

	//		szLabel.Format(_T("ROI_h%d"), (i* PRONUM)+(j+1));
	//		CPublic::CString2char(szLabel, charLabel);
	//		CPublic::GetConfigString(labelID, (LPCSTR)(charLabel), szValue, len);
	//		CPublic::g_imagePara[workNum][i][j].ROI_h = atoi(szValue);

	//	}
		
	//}




}


void CcontrolSerialNetPortDlg::updateAxisParameter2Value(AxisParameter* para, int* axis, int num, bool isSave)
{
	if (isSave == true)
	{
		for ( int i = 0; i < num; i++ )
		{
			CPublic::g_parameter[axis[i]].mode = para[i].mode;
			CPublic::g_parameter[axis[i]].startSpeed = para[i].startSpeed;
			CPublic::g_parameter[axis[i]].targetSpeed = para[i].targetSpeed;
			CPublic::g_parameter[axis[i]].accelSpeed = para[i].accelSpeed;
			CPublic::g_parameter[axis[i]].steps = para[i].steps;

		}
	}	
}

void CcontrolSerialNetPortDlg::updateValue2File(int* axis, int num, bool isSave)
{
	if (isSave == true)
	{
		CString szLabel, upvalue;
		USES_CONVERSION;

		for (int i = 0; i < num; i++ )
		{	
			szLabel.Format(_T("mode%d"), axis[i] + 1);
			upvalue = CPublic::int2CString(CPublic::g_parameter[axis[i]].mode);
			CPublic::SetConfigString("Parameter", (LPCSTR)T2A(szLabel), (LPCSTR)T2A(upvalue));
			upvalue.ReleaseBuffer();

			szLabel.Format(_T("startspeed%d"), axis[i] + 1);
			upvalue = CPublic::int2CString(CPublic::g_parameter[axis[i]].startSpeed);
			CPublic::SetConfigString("Parameter", (LPCSTR)T2A(szLabel), (LPCSTR)T2A(upvalue));
			upvalue.ReleaseBuffer();

			szLabel.Format(_T("targetspeed%d"), axis[i] + 1);
			upvalue = CPublic::int2CString(CPublic::g_parameter[axis[i]].targetSpeed);
			CPublic::SetConfigString("Parameter", (LPCSTR)T2A(szLabel), (LPCSTR)T2A(upvalue));
			upvalue.ReleaseBuffer();

			szLabel.Format(_T("accelspeed%d"), axis[i] + 1);
			upvalue = CPublic::int2CString(CPublic::g_parameter[axis[i]].accelSpeed);
			CPublic::SetConfigString("Parameter", (LPCSTR)T2A(szLabel), (LPCSTR)T2A(upvalue));
			upvalue.ReleaseBuffer();

			szLabel.Format(_T("targetsteps%d"), axis[i] + 1);
			upvalue = CPublic::int2CString(CPublic::g_parameter[axis[i]].steps);
			CPublic::SetConfigString("Parameter", (LPCSTR)T2A(szLabel), (LPCSTR)T2A(upvalue));
			upvalue.ReleaseBuffer();

			
		}
	}	
}

void CcontrolSerialNetPortDlg::updateInitValue2File(int workNum, bool isSave)
{
	if (isSave == true)
	{
		CString szLabel, upvalue;
		USES_CONVERSION;

		char labelID[20];
		if (workNum == 0)
		{
			memcpy(labelID, "InitParameter1", sizeof("InitParameter1"));
		}else if ((workNum == 1))
		{
			memcpy(labelID, "InitParameter2", sizeof("InitParameter2"));
		}

		/*for (int i = 0; i < initStepNum - 1; i++)
		{
			szLabel.Format(_T("startspeed%d"), i + 1);
			upvalue = CPublic::int2CString(CPublic::g_initParameter[workNum][i].startspeed);
			CPublic::SetConfigString(labelID, (LPCSTR)T2A(szLabel), (LPCSTR)T2A(upvalue));
			upvalue.ReleaseBuffer();

			szLabel.Format(_T("targetspeed%d"), i + 1);
			upvalue = CPublic::int2CString(CPublic::g_initParameter[workNum][i].targetspeed);
			CPublic::SetConfigString(labelID, (LPCSTR)T2A(szLabel), (LPCSTR)T2A(upvalue));
			upvalue.ReleaseBuffer();

			szLabel.Format(_T("accelspeed%d"), i + 1);
			upvalue = CPublic::int2CString(CPublic::g_initParameter[workNum][i].accelspeed);
			CPublic::SetConfigString(labelID, (LPCSTR)T2A(szLabel), (LPCSTR)T2A(upvalue));
			upvalue.ReleaseBuffer();

			szLabel.Format(_T("targetsteps%d"), i + 1);
			upvalue = CPublic::int2CString(CPublic::g_initParameter[workNum][i].steps);
			CPublic::SetConfigString(labelID, (LPCSTR)T2A(szLabel), (LPCSTR)T2A(upvalue));
			upvalue.ReleaseBuffer();
			
		}*/

		//szLabel = _T("cameraSteps");
		//upvalue = CPublic::int2CString(CPublic::g_newinitParameter[workNum].cameraSteps);
		//CPublic::SetConfigString(labelID, (LPCSTR)T2A(szLabel), (LPCSTR)T2A(upvalue));
		//upvalue.ReleaseBuffer();

		//szLabel = _T("axisYSteps");
		//upvalue = CPublic::int2CString(CPublic::g_newinitParameter[workNum].axisYSteps);
		//CPublic::SetConfigString(labelID, (LPCSTR)T2A(szLabel), (LPCSTR)T2A(upvalue));
		//upvalue.ReleaseBuffer();

		//szLabel = _T("axisXSteps");
		//upvalue = CPublic::int2CString(CPublic::g_newinitParameter[workNum].axisXSteps);
		//CPublic::SetConfigString(labelID, (LPCSTR)T2A(szLabel), (LPCSTR)T2A(upvalue));
		//upvalue.ReleaseBuffer();

		//szLabel = _T("axis6Steps");
		//upvalue = CPublic::int2CString(CPublic::g_newinitParameter[workNum].axis6Steps);
		//CPublic::SetConfigString(labelID, (LPCSTR)T2A(szLabel), (LPCSTR)T2A(upvalue));
		//upvalue.ReleaseBuffer();

		//szLabel = _T("prismSteps");
		//upvalue = CPublic::int2CString(CPublic::g_newinitParameter[workNum].prismSteps);
		//CPublic::SetConfigString(labelID, (LPCSTR)T2A(szLabel), (LPCSTR)T2A(upvalue));
		//upvalue.ReleaseBuffer();

		//szLabel = _T("axis3Steps");
		//upvalue = CPublic::int2CString(CPublic::g_newinitParameter[workNum].axis6Steps);
		//CPublic::SetConfigString(labelID, (LPCSTR)T2A(szLabel), (LPCSTR)T2A(upvalue));
		//upvalue.ReleaseBuffer();

		//szLabel = _T("axis8Steps");
		//upvalue = CPublic::int2CString(CPublic::g_newinitParameter[workNum].axis6Steps);
		//CPublic::SetConfigString(labelID, (LPCSTR)T2A(szLabel), (LPCSTR)T2A(upvalue));
		//upvalue.ReleaseBuffer();

		//szLabel = _T("axis9Steps");
		//upvalue = CPublic::int2CString(CPublic::g_newinitParameter[workNum].axis6Steps);
		//CPublic::SetConfigString(labelID, (LPCSTR)T2A(szLabel), (LPCSTR)T2A(upvalue));
		//upvalue.ReleaseBuffer();

		szLabel = _T("angelErrorX");
		upvalue = CPublic::double2CString(CPublic::g_newinitParameter[workNum].angelErrorX);
		CPublic::SetConfigString(labelID, (LPCSTR)T2A(szLabel), (LPCSTR)T2A(upvalue));
		upvalue.ReleaseBuffer();

		szLabel = _T("angelErrorY");
		upvalue = CPublic::double2CString(CPublic::g_newinitParameter[workNum].angelErrorY);
		CPublic::SetConfigString(labelID, (LPCSTR)T2A(szLabel), (LPCSTR)T2A(upvalue));
		upvalue.ReleaseBuffer();

		szLabel = _T("ratioX");
		upvalue = CPublic::double2CString(CPublic::g_newinitParameter[workNum].ratioX);
		CPublic::SetConfigString(labelID, (LPCSTR)T2A(szLabel), (LPCSTR)T2A(upvalue));
		upvalue.ReleaseBuffer();

		szLabel = _T("ratioY");
		upvalue = CPublic::double2CString(CPublic::g_newinitParameter[workNum].ratioY);
		CPublic::SetConfigString(labelID, (LPCSTR)T2A(szLabel), (LPCSTR)T2A(upvalue));
		upvalue.ReleaseBuffer();

		szLabel = _T("ratioA");
		upvalue = CPublic::double2CString(CPublic::g_newinitParameter[workNum].ratioA);
		CPublic::SetConfigString(labelID, (LPCSTR)T2A(szLabel), (LPCSTR)T2A(upvalue));
		upvalue.ReleaseBuffer();

		for (int i = 0; i < CALIBRATION_NUM; i++)
		{
			szLabel.Format(_T("posX%d"), i + 1);
			upvalue = CPublic::double2CString(CPublic::g_newinitParameter[workNum].posX[i]);
			CPublic::SetConfigString(labelID, (LPCSTR)T2A(szLabel), (LPCSTR)T2A(upvalue));
			upvalue.ReleaseBuffer();

			szLabel.Format(_T("posY%d"), i + 1);
			upvalue = CPublic::double2CString(CPublic::g_newinitParameter[workNum].posY[i]);
			CPublic::SetConfigString(labelID, (LPCSTR)T2A(szLabel), (LPCSTR)T2A(upvalue));
			upvalue.ReleaseBuffer();

			szLabel.Format(_T("posA%d"), i + 1);
			upvalue = CPublic::double2CString(CPublic::g_newinitParameter[workNum].posA[i]);
			CPublic::SetConfigString(labelID, (LPCSTR)T2A(szLabel), (LPCSTR)T2A(upvalue));
			upvalue.ReleaseBuffer();
		}


		


		memcpy(labelID, "Error", sizeof("Error"));

		szLabel = _T("stepsError");
		upvalue = CPublic::int2CString(CPublic::stepsError);
		CPublic::SetConfigString(labelID, (LPCSTR)T2A(szLabel), (LPCSTR)T2A(upvalue));
		upvalue.ReleaseBuffer();

		szLabel = _T("sensorError");
		upvalue.Format(_T("%f"), CPublic::sensorError);
		CPublic::SetConfigString(labelID, (LPCSTR)T2A(szLabel), (LPCSTR)T2A(upvalue));
		upvalue.ReleaseBuffer();



	}
}

//void CcontrolSerialNetPortDlg::updateAutoValue2File(int workNum, int roundNum, int proNum, bool isSave)
//{
//	if (isSave == true)
//	{
//		CString szLabel, upvalue;
//		USES_CONVERSION;
//
//		char labelID[20];
//		//autoparameter
//		if (workNum == 0)
//		{
//			memcpy(labelID, "AutoParameter1", sizeof("AutoParameter1"));
//		}else if ((workNum == 1))
//		{
//			memcpy(labelID, "AutoParameter2", sizeof("AutoParameter2"));
//		}else
//		{
//			memcpy(labelID, "AutoParameter3", sizeof("AutoParameter3"));
//		}
//
//
//
//		szLabel = _T("delayTime2");
//		upvalue = CPublic::int2CString(CPublic::g_AutoParameter[workNum].delayTime2);
//		CPublic::SetConfigString(labelID, (LPCSTR)T2A(szLabel), (LPCSTR)T2A(upvalue));
//		upvalue.ReleaseBuffer();
//
//		for (int i = 0; i < 6; i++)
//		{
//			szLabel = _T("steps4_") + CPublic::int2CString(i+1);
//			upvalue = CPublic::int2CString(CPublic::g_AutoParameter[workNum].steps4[i]);
//			CPublic::SetConfigString(labelID, (LPCSTR)T2A(szLabel), (LPCSTR)T2A(upvalue));
//			upvalue.ReleaseBuffer();
//		}
//
//
//		szLabel = _T("steps5_1");
//		upvalue = CPublic::int2CString(CPublic::g_AutoParameter[workNum].steps5_1);
//		CPublic::SetConfigString(labelID, (LPCSTR)T2A(szLabel), (LPCSTR)T2A(upvalue));
//		upvalue.ReleaseBuffer();
//
//		szLabel = _T("steps5_2");
//		upvalue = CPublic::int2CString(CPublic::g_AutoParameter[workNum].steps5_2);
//		CPublic::SetConfigString(labelID, (LPCSTR)T2A(szLabel), (LPCSTR)T2A(upvalue));
//		upvalue.ReleaseBuffer();
//
//
//		szLabel = _T("steps6");
//		upvalue = CPublic::int2CString(CPublic::g_AutoParameter[workNum].steps6);
//		CPublic::SetConfigString(labelID, (LPCSTR)T2A(szLabel), (LPCSTR)T2A(upvalue));
//		upvalue.ReleaseBuffer();
//
//
//		szLabel = _T("delayTime7");
//		upvalue = CPublic::int2CString(CPublic::g_AutoParameter[workNum].delayTime7);
//		CPublic::SetConfigString(labelID, (LPCSTR)T2A(szLabel), (LPCSTR)T2A(upvalue));
//		upvalue.ReleaseBuffer();
//
//		szLabel = _T("delayTime8");
//		upvalue = CPublic::int2CString(CPublic::g_AutoParameter[workNum].delayTime8);
//		CPublic::SetConfigString(labelID, (LPCSTR)T2A(szLabel), (LPCSTR)T2A(upvalue));
//		upvalue.ReleaseBuffer();
//
//		szLabel = _T("steps9");
//		upvalue = CPublic::int2CString(CPublic::g_AutoParameter[workNum].steps9);
//		CPublic::SetConfigString(labelID, (LPCSTR)T2A(szLabel), (LPCSTR)T2A(upvalue));
//		upvalue.ReleaseBuffer();
//
//		szLabel = _T("steps10_1");
//		upvalue = CPublic::int2CString(CPublic::g_AutoParameter[workNum].steps10_1);
//		CPublic::SetConfigString(labelID, (LPCSTR)T2A(szLabel), (LPCSTR)T2A(upvalue));
//		upvalue.ReleaseBuffer();
//
//		szLabel = _T("steps10_2");
//		upvalue = CPublic::int2CString(CPublic::g_AutoParameter[workNum].steps10_2);
//		CPublic::SetConfigString(labelID, (LPCSTR)T2A(szLabel), (LPCSTR)T2A(upvalue));
//		upvalue.ReleaseBuffer();
//
//		szLabel = _T("steps10_3");
//		upvalue = CPublic::int2CString(CPublic::g_AutoParameter[workNum].steps10_3);
//		CPublic::SetConfigString(labelID, (LPCSTR)T2A(szLabel), (LPCSTR)T2A(upvalue));
//		upvalue.ReleaseBuffer();
//
//		szLabel = _T("delayTime10");
//		upvalue = CPublic::int2CString(CPublic::g_AutoParameter[workNum].delayTime10);
//		CPublic::SetConfigString(labelID, (LPCSTR)T2A(szLabel), (LPCSTR)T2A(upvalue));
//		upvalue.ReleaseBuffer();
//
//		szLabel = _T("steps10_4");
//		upvalue = CPublic::int2CString(CPublic::g_AutoParameter[workNum].steps10_4);
//		CPublic::SetConfigString(labelID, (LPCSTR)T2A(szLabel), (LPCSTR)T2A(upvalue));
//		upvalue.ReleaseBuffer();
//
//		szLabel = _T("steps10_5");
//		upvalue = CPublic::int2CString(CPublic::g_AutoParameter[workNum].steps10_5);
//		CPublic::SetConfigString(labelID, (LPCSTR)T2A(szLabel), (LPCSTR)T2A(upvalue));
//		upvalue.ReleaseBuffer();
//
//		szLabel = _T("steps10_6");
//		upvalue = CPublic::int2CString(CPublic::g_AutoParameter[workNum].steps10_6);
//		CPublic::SetConfigString(labelID, (LPCSTR)T2A(szLabel), (LPCSTR)T2A(upvalue));
//		upvalue.ReleaseBuffer();
//
//		szLabel = _T("delayTime11");
//		upvalue = CPublic::int2CString(CPublic::g_AutoParameter[workNum].delayTime11);
//		CPublic::SetConfigString(labelID, (LPCSTR)T2A(szLabel), (LPCSTR)T2A(upvalue));
//		upvalue.ReleaseBuffer();
//
//		szLabel = _T("steps11");
//		upvalue = CPublic::int2CString(CPublic::g_AutoParameter[workNum].steps11);
//		CPublic::SetConfigString(labelID, (LPCSTR)T2A(szLabel), (LPCSTR)T2A(upvalue));
//		upvalue.ReleaseBuffer();
//
//
//		szLabel = _T("dispense1");
//		upvalue = CPublic::int2CString(CPublic::g_AutoParameter[workNum].dispense1);
//		CPublic::SetConfigString(labelID, (LPCSTR)T2A(szLabel), (LPCSTR)T2A(upvalue));
//		upvalue.ReleaseBuffer();
//
//		szLabel = _T("dispense2");
//		upvalue = CPublic::int2CString(CPublic::g_AutoParameter[workNum].dispense2);
//		CPublic::SetConfigString(labelID, (LPCSTR)T2A(szLabel), (LPCSTR)T2A(upvalue));
//		upvalue.ReleaseBuffer();
//
//
//		for (int i = 0; i < 6; i++)
//		{
//			szLabel = _T("dispenseA_") + CPublic::int2CString(i+1);
//			upvalue = CPublic::int2CString(CPublic::g_AutoParameter[workNum].dispenseA[i]);
//			CPublic::SetConfigString(labelID, (LPCSTR)T2A(szLabel), (LPCSTR)T2A(upvalue));
//			upvalue.ReleaseBuffer();
//		}
//
//		szLabel = _T("angelErrorX");
//		upvalue = CPublic::double2CString(CPublic::g_AutoParameter[workNum].angErrorX);
//		CPublic::SetConfigString(labelID, (LPCSTR)T2A(szLabel), (LPCSTR)T2A(upvalue));
//		upvalue.ReleaseBuffer();
//
//		szLabel = _T("angelErrorY");
//		upvalue = CPublic::double2CString(CPublic::g_AutoParameter[workNum].angErrorY);
//		CPublic::SetConfigString(labelID, (LPCSTR)T2A(szLabel), (LPCSTR)T2A(upvalue));
//		upvalue.ReleaseBuffer();
//
//		szLabel = _T("ratioX");
//		upvalue = CPublic::double2CString(CPublic::g_AutoParameter[workNum].ratioX);
//		CPublic::SetConfigString(labelID, (LPCSTR)T2A(szLabel), (LPCSTR)T2A(upvalue));
//		upvalue.ReleaseBuffer();
//
//		szLabel = _T("ratioY");
//		upvalue = CPublic::double2CString(CPublic::g_AutoParameter[workNum].ratioY);
//		CPublic::SetConfigString(labelID, (LPCSTR)T2A(szLabel), (LPCSTR)T2A(upvalue));
//		upvalue.ReleaseBuffer();
//
//		szLabel = _T("ratioA");
//		upvalue = CPublic::double2CString(CPublic::g_AutoParameter[workNum].ratioA);
//		CPublic::SetConfigString(labelID, (LPCSTR)T2A(szLabel), (LPCSTR)T2A(upvalue));
//		upvalue.ReleaseBuffer();
//
//
//
//		//iamge parameter
//		szLabel.Format(_T("searchSpeedMode%d"), (roundNum * PRONUM  + (proNum + 1)));
//		upvalue = CPublic::int2CString(CPublic::g_imagePara[workNum][roundNum][proNum].searchSpeedMode);
//		CPublic::SetConfigString(labelID, (LPCSTR)T2A(szLabel), (LPCSTR)T2A(upvalue));
//		upvalue.ReleaseBuffer();
//
//		szLabel.Format(_T("maxMatchNum%d"), (roundNum * PRONUM  + (proNum + 1)));
//		upvalue = CPublic::int2CString(CPublic::g_imagePara[workNum][roundNum][proNum].maxMatchNum);
//		CPublic::SetConfigString(labelID, (LPCSTR)T2A(szLabel), (LPCSTR)T2A(upvalue));
//		upvalue.ReleaseBuffer();
//
//		szLabel.Format(_T("matchNum%d"), (roundNum * PRONUM  + (proNum + 1)));
//		upvalue = CPublic::int2CString(CPublic::g_imagePara[workNum][roundNum][proNum].matchNum);
//		CPublic::SetConfigString(labelID, (LPCSTR)T2A(szLabel), (LPCSTR)T2A(upvalue));
//		upvalue.ReleaseBuffer();
//
//		szLabel.Format(_T("modelFilePath%d"), (roundNum * PRONUM  + (proNum + 1)));
//		upvalue = CPublic::g_imagePara[workNum][roundNum][proNum].modelFilePath;
//		CPublic::SetConfigString(labelID, (LPCSTR)T2A(szLabel), (LPCSTR)T2A(upvalue));
//		upvalue.ReleaseBuffer();
//
//		szLabel.Format(_T("smoothness%d"), (roundNum * PRONUM  + (proNum + 1)));
//		upvalue = CPublic::int2CString(CPublic::g_imagePara[workNum][roundNum][proNum].smoothness);
//		CPublic::SetConfigString(labelID, (LPCSTR)T2A(szLabel), (LPCSTR)T2A(upvalue));
//		upvalue.ReleaseBuffer();
//
//		szLabel.Format(_T("iterationNum%d"), (roundNum * PRONUM  + (proNum + 1)));
//		upvalue = CPublic::int2CString(CPublic::g_imagePara[workNum][roundNum][proNum].iterationNum);
//		CPublic::SetConfigString(labelID, (LPCSTR)T2A(szLabel), (LPCSTR)T2A(upvalue));
//		upvalue.ReleaseBuffer();
//
//		szLabel.Format(_T("modelDistance%d"), (roundNum * PRONUM  + (proNum + 1)));
//		upvalue = CPublic::int2CString(CPublic::g_imagePara[workNum][roundNum][proNum].modelDistance);
//		CPublic::SetConfigString(labelID, (LPCSTR)T2A(szLabel), (LPCSTR)T2A(upvalue));
//		upvalue.ReleaseBuffer();
//
//		szLabel.Format(_T("ROI_x%d"), (roundNum * PRONUM  + (proNum + 1)));
//		upvalue = CPublic::int2CString(CPublic::g_imagePara[workNum][roundNum][proNum].ROI_x);
//		CPublic::SetConfigString(labelID, (LPCSTR)T2A(szLabel), (LPCSTR)T2A(upvalue));
//		upvalue.ReleaseBuffer();
//
//		szLabel.Format(_T("ROI_y%d"), (roundNum * PRONUM  + (proNum + 1)));
//		upvalue = CPublic::int2CString(CPublic::g_imagePara[workNum][roundNum][proNum].ROI_y);
//		CPublic::SetConfigString(labelID, (LPCSTR)T2A(szLabel), (LPCSTR)T2A(upvalue));
//		upvalue.ReleaseBuffer();
//
//		szLabel.Format(_T("ROI_w%d"), (roundNum * PRONUM  + (proNum + 1)));
//		upvalue = CPublic::int2CString(CPublic::g_imagePara[workNum][roundNum][proNum].ROI_w);
//		CPublic::SetConfigString(labelID, (LPCSTR)T2A(szLabel), (LPCSTR)T2A(upvalue));
//		upvalue.ReleaseBuffer();
//
//		szLabel.Format(_T("ROI_h%d"), (roundNum * PRONUM  + (proNum + 1)));
//		upvalue = CPublic::int2CString(CPublic::g_imagePara[workNum][roundNum][proNum].ROI_h);
//		CPublic::SetConfigString(labelID, (LPCSTR)T2A(szLabel), (LPCSTR)T2A(upvalue));
//		upvalue.ReleaseBuffer();
//	}
//}

void CcontrolSerialNetPortDlg::OnBnClickedButtonsetting()
{

	if (!m_settingDlg->GetSafeHwnd())
	{
		m_settingDlg = new CAutoSettingDlg;
		m_settingDlg->Create(CAutoSettingDlg::IDD);
	}
	m_settingDlg->ShowWindow(SW_SHOW);

}



int CcontrolSerialNetPortDlg::switchLight(CButtonST* lightBst, bool isOpen)
{
	if (isOpen == true)
	{
		lightBst->SetIcon(IDI_ICON_green24);
	}else
		lightBst->SetIcon(IDI_ICON_Cgrey24);

	return 0;
}

int CcontrolSerialNetPortDlg::inquiryLim(int devNum, int axisNum, int portIndex, int limitType, bool* isContinue)
{
	CString strAxis = CPublic::int2CString(axisNum);
	CString strcomm = CPublic::int2CString(devNum) + _T("->") + _T("LIM? ") + strAxis;

	while(1)
	{
		if (*isContinue == false)
			return 0;

		//sendAnySingleComm(devNum, _T("LIM?"), axisNum, 0, false, port);

		sendComm(strcomm, portIndex);
		Sleep(initFindTime);
		if (CPublic::explainLim(CPublic::receiveData[portIndex], limitType) == 1)
		{
			return 1;
		}
	}
}

	
int CcontrolSerialNetPortDlg::inquiryPos(int devNum, int axisNum, int portIndex, int stepvalue, bool* isContinue)
{
	CString strAxis = CPublic::int2CString(axisNum);
	CString strcomm = CPublic::int2CString(devNum) + _T("->") + _T("POS? ") + strAxis;

	while(1)
	{
		if (*isContinue == false)
			return 0;

		//sendAnySingleComm(devNum, _T("LIM?"), axisNum, 0, false, port);

		sendComm(strcomm, portIndex);
		Sleep(initFindTime);
		if (abs(CPublic::explainIntPos(CPublic::receiveData[portIndex]) - stepvalue) < CPublic::stepsError)
			return 1;
	}		
}

int CcontrolSerialNetPortDlg::inquiry(CString command, int portIndex, int value, bool isPos, bool* isContinue)//---------------（1.2.1.2.1）发送查询指令函数
{
	while(1)
	{
		if (*isContinue == false)
			return 0;

		//sendAnySingleComm(devNum, _T("LIM?"), axisNum, 0, false, port);

		if (sendAnySingleComm(command, portIndex, isContinue) == 0)
		{
			AddString(_T("发送")+command+_T("指令无数据返回？"));
			return 0;
		}

		//Sleep(initFindTime);
		if (isPos == true)//非LIM查询
		{    
			int reValue = CPublic::explainIntPos(CPublic::receiveData[portIndex]);//接收到的数值？
			if (command.Find(_T("INP?")) != -1 || command.Find(_T("OUP?")) != -1 || command.Find(_T("ADR?")) != -1)//查到这三种指令标识
			{
				if (reValue == value)
					return 1;			
			}
			else if (command.Find(_T("MVR?")) != -1)//查询到MVR指令标识
			{
				if (abs(reValue - abs(value)) <= CPublic::stepsError)//abs求绝对值的函数
					return 1;
			}
			else//	POS查询
			{
				if (abs(reValue - value) <= CPublic::stepsError)
					return 1;
			}
		}else//LIM查询
		{
			if (CPublic::explainLim(CPublic::receiveData[portIndex], value) == 1)
				return 1;
		}
	}		
}


int CcontrolSerialNetPortDlg::switchInquiry(int* devNum, CString* comm, int portIndex, int* verValue, int commNum, bool* isContinue)
{
	CString* strComm = new CString[commNum];
	bool* flag = new bool[commNum];

	for (int i = 0; i < commNum; i++)
	{
		strComm[i] = CPublic::int2CString(devNum[i]) + _T("->") + comm[i];
		flag[i] = false;
	}

	int count = 0;

	while(1)
	{		

		for (int i = 0; i < commNum; i++)
		{
			if (*isContinue == false)
			{
				delete[] flag;
				delete[] strComm;
				return 0;
			}


			if (flag[i] == false )
			{
				sendComm(strComm[i], portIndex);
				Sleep(initFindTime);
				if ( _T("POS?") == (comm[i]).Left(4))
				{
					
					if (abs(CPublic::explainIntPos(CPublic::receiveData[portIndex]) - verValue[i]) < CPublic::stepsError)
					{
						flag[i] = true;
						count++;
					}
				}else if(comm[i].Left(4) == _T("LIM?"))
				{
					if (CPublic::explainLim(CPublic::receiveData[portIndex], verValue[i]))
					{
						flag[i] = true;
						count++;
					}

				}			

			}

			if (count == commNum)
			{
				delete[] flag;
				delete[] strComm;
				return 1;
			}
		}	
	}		
}


int CcontrolSerialNetPortDlg::switchInquiry( CString* comm, int portIndex, int* verValue, int commNum, bool* isContinue)
{
	//CString* strComm = new CString[commNum];
	bool* flag = new bool[commNum];
	//CString typeComm;
	//int index = 0;
	int* type = new int[commNum];
	int value = 0;

	for (int i = 0; i < commNum; i++)
	{
		flag[i] = false;
		if (comm[i].Find(_T("LIM?")) >= 0)
			type[i] = 0;
		else if (comm[i].Find(_T("POS?")) >= 0)
			type[i] = 1;
		else if (comm[i].Find(_T("INP?")) >= 0 || comm[i].Find(_T("OUP?")) >= 0  || comm[i].Find(_T("ADR?")) >= 0)
			type[i] = 2;
		else if (comm[i].Find(_T("MVR?")) >= 0)
			type[i] = 3;

	}

	int count = 0;

	while(1)
	{		

		for (int i = 0; i < commNum; i++)
		{
			if (*isContinue == false)
			{
				delete[] flag;
				delete[] type;
				return 0;
			}


			if (flag[i] == false )
			{
				if (sendAnySingleComm(comm[i], portIndex, isContinue) == 0)
				{
					AddString(_T("发送") + comm[i] + _T("指令无数据返回？"));
					return 0;
				}
	
				if (CPublic::explainInquiry(CPublic::receiveData[portIndex], verValue[i], type[i]) == 1)
				{
					flag[i] = true;
					count++;
				}				

			}

			if (count == commNum)
			{
				delete[] flag;
				delete[] type;
				return 1;
			}
		}	
	}
}

 int CcontrolSerialNetPortDlg::Robot(CString data, int Num, bool* isContinue)
{
	
	return 1;

}

int CcontrolSerialNetPortDlg::sendFileComm(CStdioFile* file, int workNum, int portIndex, bool* isContinue)  //------------------（1.2.1）向串口发送指令函数
{
	//CString comm;
	//read the title
	//for (int i = 0; i < lineNum; i++)
	//file->ReadString(comm);
	int res = 0;
	if (m_fileComm[workNum].Left(6) == _T("Common"))
	{
		switchLight(&m_bstLight[4], true);
		res = explainCommon(file, workNum, portIndex, isContinue);//------------------------------(1.2.1.1)普通指令解析函数（完成）
		switchLight(&m_bstLight[4], false);
		return res;
	}
	else if (m_fileComm[workNum].Left(7) == _T("Inquiry"))
	{
		switchLight(&m_bstLight[1], true);
		res = explainInquiry(file, workNum, portIndex, isContinue);//-----------------------------（1.2.1.2）查询解析函数（完成）
		switchLight(&m_bstLight[1], false);
		return res;
	}
	else if (m_fileComm[workNum].Left(5) == _T("Robot"))
	{
		//switchLight(&m_bstLight[0], true);
		//res = explainRobot(file, workNum, isContinue);//-------------------------------------（1.2.1.3）机器人解析函数
		//switchLight(&m_bstLight[0], false);
		// 没有用到机器人，注释掉
		return res;
	}	

	else if (m_fileComm[workNum].Left(9) == _T("DelayTime"))
	{		
		switchLight(&m_bstLight[9], true); 
		res = explainDelayTime(file, workNum);//------------------------------------------------（1.2.1.4）延时解析函数（完成）
		switchLight(&m_bstLight[9], false);
		return res;
	}
	//else if (m_fileComm[workNum].Left(24) == _T("WaitRobotFinishOtherWork"))
	//{		
	//	return explainDelayTime(file, workNum);
	//}
	else if (m_fileComm[workNum].Left(15) == _T("ImageProcessing"))
	{
		switchLight(&m_bstLight[2], true);
		res = explainImageProcessing(file, workNum, isContinue);//-------------------------------（1.2.1.5）图像处理解析函数
		switchLight(&m_bstLight[2], false);
		return res;

	}
	//else if (m_fileComm[workNum].Left(13) == _T("ImageProcess2"))
	//{
	//	switchLight(&m_bstLight[workNum][2], true);
	//	res = explainImageProcess2(file, workNum, isContinue);
	//	switchLight(&m_bstLight[workNum][2], false);
	//	return res;
	//}
	else if (m_fileComm[workNum].Left(14) == _T("LightAdjusting"))
	{
		switchLight(&m_bstLight[3], true);
		res = explainLight(file, workNum, isContinue);//----------------------------------------（1.2.1.6）光源解析函数（）
		switchLight(&m_bstLight[3], false);
		return res;

	}
	//else if (m_fileComm[workNum].Left(13) == _T("SwitchInquiry"))
	//{
	//	switchLight(&m_bstLight[workNum][1], true);
	//	res = explainSwitchInquiry(file, workNum, portIndex, isContinue);
	//	switchLight(&m_bstLight[workNum][1], false);
	//	return res;
	//}
	else if (m_fileComm[workNum].Left(19) == _T("AdjustingWithResult"))
	{
		switchLight(&m_bstLight[7], true);
		res = explainResultOfImagePro(file, workNum, portIndex, isContinue); //---------------（1.2.1.7）微调设备解析函数
		switchLight(&m_bstLight[7], false);
		return res;
	}
	//else if (m_fileComm[workNum].Left(29) == _T("MoveWithResultOfImageProcess2"))
	//{
	//	switchLight(&m_bstLight[workNum][2], true);
	//	res = explainResultOfImagePro2(file, workNum, portIndex, isContinue);
	//	switchLight(&m_bstLight[workNum][2], false);
	//	return res;
	//}
	//else if (m_fileComm[workNum].Left(15) == _T("GoldBallBonding"))
	//{
	//	switchLight(&m_bstLight[workNum][5], true);
	//	res = explainGoldBallBonding(file,  workNum, 2, isContinue);
	//	switchLight(&m_bstLight[workNum][5], false);
	//	return res;
	//}
	else if (m_fileComm[workNum].Left(17) == _T("ThreadInteraction"))
	{
		switchLight(&m_bstLight[8], true);
		res = explainThreadInteraction(file, workNum, portIndex, isContinue); //---------------（1.2.1.8）线程交互解析函数
		switchLight(&m_bstLight[8], false);
		return res;
	}
	else if (m_fileComm[workNum].Left(4) == _T("Unit"))//装配单元起始标记 命令
	{
		switchLight(&m_bstLight[8], true);
		res = explainUnit(file, workNum, portIndex, isContinue);//-----------------------------（1.2.1.9）单元起始解析函数
		return res;
	}
	else if (m_fileComm[workNum].Left(10) == _T("ControlDev"))//装配单元起始标记 命令
	{
		switchLight(&m_bstLight[4], true);
		res = explainControlDev(file, workNum, portIndex, isContinue);//------------------------------(1.2.1.1)IO/轴控指令解析函数（完成）
		switchLight(&m_bstLight[4], false);
		return res;
	}
	else if (m_fileComm[workNum].Left(17) == _T("OmissionDetection"))
	{
		switchLight(&m_bstLight[0], true);
		res = explainOmissionDetection(file, workNum, isContinue);
		switchLight(&m_bstLight[0], false);
		return res;
	}
}


int CcontrolSerialNetPortDlg::explainThreadInteraction(CStdioFile* file, int workNum, int portIndex, bool* Continue)//-------------（1.2.1.8）线程交互解析函数
{
	if (Continue == false)
		return 0;
	int index = 0;
	CString comm[3];
	CString MiddleComm;
	comm[0] = ChineseTransformation(MiddleComm, file);
	comm[1] = ChineseTransformation(MiddleComm, file);
	comm[2] = ChineseTransformation(MiddleComm, file);
	
	int SenderThreadNum = _ttoi(explainParameter(_T("Sender"), comm[1]));
	int RecipientThreadNum = _ttoi(explainParameter(_T("Recipient"), comm[2]));
	CString m,n;
	m.Format(_T("%d"), SenderThreadNum);//int转换成字符
	n.Format(_T("%d"), RecipientThreadNum);
	if (comm[0] == "\r\nWaitUntil")//发送方暂停
	{
		if (ThreadState[SenderThreadNum - 1] == 1)
		{
			ThreadState[SenderThreadNum - 1] = 0;//设置状态变量为暂停
			AddString(_T("线程") + m + _T("已挂起等待"));
			m_pThread[SenderThreadNum - 1]->SuspendThread();
			m_progress.OffsetPos(1);
			return 1;
		}
		else
		{
			//AddString(_T("线程") + m + _T("挂起等待失败！"));
			AddString(_T("线程") + m + _T("挂起等待error"));
			return 0;
		}
	}
	if (comm[0] == "\r\nOrderContinue")//接受方继续运行
	{
		while (1)
		{
			if (ThreadState[RecipientThreadNum - 1] == 0)
			{
				//先查询接受方的线程是否挂起。再发送
				m_pThread[RecipientThreadNum - 1]->ResumeThread();
				ThreadState[RecipientThreadNum - 1] = 1;//设置接受方状态变量为1
				AddString(_T("线程") + n + _T("已恢复运行"));
				m_progress.OffsetPos(1);
				return 1;
				break;
			}
			else
			{
				continue;
			}
		}
	}
	else
	{
		AddString(_T("脚本线程交互二级命令错误？"));
		return 0;
	}
}

int CcontrolSerialNetPortDlg::findChar(CString comm, char value, int number)//----------------------------查找value函数
{
	int index = 0;
	for (int i = 0; i < number; i++)
	{
		index = comm.Find(value, index);//在指令的第三行字符中查找是否包含字符：value,从0位置开始查，返回的是位置
		if (index == -1)
			return -1;
		index++;
	}
	return index;
}

CString CcontrolSerialNetPortDlg::findCoron(CStdioFile* file)           //------------------------------------寻找冒号函数
{
	if (feof(file->m_pStream))
	{
		AddString(_T("脚本文件已到结尾？"));//MFC中的列表框等控件具有此成员函数，用来向列表中添加字符串的。
		return NULL;
	}

	CString str;
	CString coron1 = _T("：");
	int len = coron1.GetLength();

	int i = 0;
	while (i < 100)
	{
		file->ReadString(str);//ReadString一次读取一行
		if (str.Right(1) == _T(":") || str.Right(len) == coron1)//从右边向左读取第一个字符是中文：或者英文:
		{
			return str;//返回读取到的字符，包括冒号
		}
		i++;
	}
	return NULL;

}
CString CcontrolSerialNetPortDlg::explainParameter(CString ParameterName, CString Sentence)
{
	int index;
	index = findChar(Sentence, '=', 1);
	if (index == -1)
	{
		AddString(_T("脚本的") + ParameterName + _T("错误？"));
		return 0;
	}
	return ParameterName = Sentence.Mid(index);
}

BOOL CcontrolSerialNetPortDlg::ReadStringToUnicode(CString &str)
{
	char *szBuf = new char[str.GetLength() + 1]; //数量要加1
	for (int i = 0; i < str.GetLength(); i++)
	{
		szBuf[i] = (CHAR)str.GetAt(i);
	}
	szBuf[str.GetLength()] = '\0'; //这里，必须要加上，否则会在结尾片显示一个"铪"字。
									 // USES_CONVERSION;
									 //char * sz=W2A(str.GetBuffer()); ?//这些方法我都试过，不行的。
	BOOL bok = CharToUnicode(szBuf, &str);
	delete[]szBuf;
	return bok;
}
int CcontrolSerialNetPortDlg::CharToUnicode(char *pchIn, CString *pstrOut)
{
	int nLen;
	WCHAR *ptch;

	if (pchIn == NULL)
	{
		return 0;
	}
	nLen = MultiByteToWideChar(CP_ACP, 0, pchIn, -1, NULL, 0);//取得所需缓存的多少
	ptch = new WCHAR[nLen];//申请缓存空间
	MultiByteToWideChar(CP_ACP, 0, pchIn, -1, ptch, nLen);//转码
	pstrOut->Format(_T("%s"), ptch);
	delete[] ptch;
	return nLen;
}
CString CcontrolSerialNetPortDlg::ChineseTransformation(CString str, CStdioFile* file)
{
	CString comm = _T("");
	file->ReadString(str);
	ReadStringToUnicode(str);//这里要处理下，不然汉字无法正常显示。函数见下面
	comm = comm + _T("\r\n") + str;
	return comm;
}


int CcontrolSerialNetPortDlg::explainUnit(CStdioFile* file, int workNum, int portIndex, bool* Continue)
{
	if (Continue == false)
		return 0;
	int index = 0;
	CString comm[3];
	CString MiddleComm; 
	comm[0] = ChineseTransformation(MiddleComm, file);
	comm[1] = ChineseTransformation(MiddleComm, file);
	comm[2] = ChineseTransformation(MiddleComm, file);
	CString UnitName = explainParameter(_T("UnitName"), comm[1]);//获取名称
	int Sequence = _ttoi(explainParameter(_T("Sequence"), comm[2]));//获取序号
	CString m;
	m.Format(_T("%d"), Sequence);//int转换成字符
	if (comm[0] == "\r\nUnitStart")
	{
		switchLight(&m_UnitLight[Sequence], true);
		m_UnitName[Sequence].SetWindowText(UnitName);//设置显示文字
		AddString(_T("-----------第")+ m +_T("个零件开始装配:")+ UnitName +_T("------------"));
		m_progress.OffsetPos(1);
		return 1;
	}
	else if (comm[0] == "\r\nUnitEnd")
	{
		switchLight(&m_UnitLight[Sequence], false);
		AddString(_T("-----------第") + m + _T("个零件装配完成:")+ UnitName+_T("------------"));
		m_progress.OffsetPos(1);
		return 1;
	}
}


int CcontrolSerialNetPortDlg::explainRobot(CStdioFile* file, int workNum, bool* isContinue)//-----------------------（1.2.1.3）机器人解析函数
{
	if (*isContinue == false)
		return 0;
	double index = 0, res, speed;
	int	   ActualStatus, ActualStatusOld, Mode, route;
	double TargetSpacePosition[5];//存放目标空间坐标值
	double TargetMotorPosition[5];//存放目标关节坐标值
	CString comm[9];//存放读取到的字符
	CString MiddleComm;

	comm[0] = ChineseTransformation(MiddleComm, file);
	comm[1] = ChineseTransformation(MiddleComm, file);
	comm[2] = ChineseTransformation(MiddleComm, file);
	comm[3] = ChineseTransformation(MiddleComm, file);
	comm[4] = ChineseTransformation(MiddleComm, file);
	comm[5] = ChineseTransformation(MiddleComm, file);
	comm[6] = ChineseTransformation(MiddleComm, file);
	comm[7] = ChineseTransformation(MiddleComm, file);
	comm[8] = ChineseTransformation(MiddleComm, file);

	if (comm[0] == "\r\nMoveRobot")
	{
		speed = _ttof(explainParameter(_T("Speed"), comm[1]));
		CString Coordinate = explainParameter(_T("Coordinate"), comm[2]);
		CString Route = explainParameter(_T("Route"), comm[3]);
		if (Route == "MoveJ")
		{
			route = 0;
		}
		else
		{
			if (Route = "MoveL")
			{
				route = 1;
			}
			else
			{
				AddString(_T("脚本机器人运动指令的运动方式错误？"));
				return 0;
			}
		}
		if (Coordinate == "Cartesian")//笛卡尔坐标模式
		{
			Mode = 1;
			TargetSpacePosition[0] = _ttof(explainParameter(_T("X"), comm[4]));
			TargetSpacePosition[1] = _ttof(explainParameter(_T("Y"), comm[5]));
			TargetSpacePosition[2] = _ttof(explainParameter(_T("Z"), comm[6]));
			TargetSpacePosition[3] = _ttof(explainParameter(_T("R"), comm[7]));
			TargetSpacePosition[4] = _ttof(explainParameter(_T("G"), comm[8]));

			//向机器人函数传值
			robot->SendData(14, Mode);//发送运动模式 
			robot->SendData(4, route);//发送末端位置模式下运动模式 
			robot->SendData(5, TargetSpacePosition, sizeof(TargetSpacePosition));
			robot->SendData(6, speed);//发送速度
			m_progress.SetStep(1);//设置进度条前进的步长
			return 1;
		}
		if (Coordinate == "Joint")//关节角度模式
		{
			Mode = 0;
			TargetMotorPosition[0] = _ttof(explainParameter(_T("Axis1"), comm[3]));
			TargetMotorPosition[1] = _ttof(explainParameter(_T("Axis2"), comm[4]));
			TargetMotorPosition[2] = _ttof(explainParameter(_T("Axis3"), comm[5]));
			TargetMotorPosition[3] = _ttof(explainParameter(_T("Axis4"), comm[6]));
			TargetMotorPosition[4] = _ttof(explainParameter(_T("Axis5"), comm[7]));

			robot->SendData(14, Mode);//发送运动模式 
			robot->SendData(3, TargetMotorPosition, sizeof(TargetMotorPosition));
			robot->SendData(6, speed);//发送速度
			m_progress.SetStep(1);//设置进度条前进的步长
			return 1;
		}
	}
	if (comm[0] == "\r\nInquiryRobot")
	{
		if (comm[1] == "\r\nRobotStatus?")
		{
			//	CString Status = explainParameter(_T("Status"), comm[2]);
			while (1)
			{
				robot->ReadData(15, ActualStatus);//读取模式
				if ((ActualStatus - ActualStatusOld) != 0)
					if ((ActualStatus - ActualStatusOld) == -1)
					{
						ActualStatusOld = ActualStatus;
						m_progress.SetStep(1);//设置进度条前进的步长
						return 1;	//满足查询条件返回1
						break;
					}
					else
						ActualStatusOld = ActualStatus;
			}
			//if (ActualStatus == 0)
			//{
			//	m_progress.SetStep(1);//设置进度条前进的步长
			//	return 1;//满足查询条件返回1
			//}
			//if (Status = "Buzy")
			//{

			//	while (1)//一直查下去
			//	{
			//		if (ActualStatus == 1)
			//		{
			//			m_progress.SetStep(1);//设置进度条前进的步长
			//			break;
			//			return 1;//满足查询条件返回1
			//		}
			//	}

			//}
			//if (Status == "Waiting")
			//{
			//	while (1)//一直查下去
			//	{
			//		if (robot->ActualStatus == 0)
			//		{
			//			m_progress.SetStep(1);//设置进度条前进的步长
			//			break;
			//			return 1;//满足查询条件返回1
			//		}
			//	}
			//}
			//else
			//{
			//	AddString(_T("脚本机器人状态查询指令的参数错误？"));
			//	return 0;
			//}
		}
		if (comm[1] == "\r\nRobotAbsolutePosition?")
		{
			double ActualJointPosition[5];//存放五个实际关节坐标
			double ActualSpacePosition[4];//存放四个实际笛卡尔坐标
			CString Coordinate = explainParameter(_T("Coordinate"), comm[2]);//坐标方式
			if (Coordinate == "Cartesian")//笛卡尔坐标模式
			{
				TargetSpacePosition[0] = _ttof(explainParameter(_T("X"), comm[3]));
				TargetSpacePosition[1] = _ttof(explainParameter(_T("Y"), comm[4]));
				TargetSpacePosition[2] = _ttof(explainParameter(_T("Z"), comm[5]));
				TargetSpacePosition[3] = _ttof(explainParameter(_T("R"), comm[6]));

				robot->ReadData(1, ActualSpacePosition, sizeof(ActualSpacePosition));

				//while (1)//一直查下去
				//{
				//	if (abs(ActualCartesianPosition[0] - position[0]) < CPublic::stepsError&& abs(ActualCartesianPosition[1] - position[1]) < CPublic::stepsError&& abs(ActualCartesianPosition[2] - position[2]) < CPublic::stepsError&& abs(ActualCartesianPosition[3] - position[3]) < CPublic::stepsError)
				//	{
				//		m_progress.SetStep(1);//设置进度条前进的步长
				//		break;
				//		return 1;//四个参数在误差范围内
				//	}
				//}
			}
			if (Coordinate == "Joint")//关节角度模式
			{

				TargetMotorPosition[0] = _ttof(explainParameter(_T("Axis1"), comm[3]));
				TargetMotorPosition[1] = _ttof(explainParameter(_T("Axis2"), comm[4]));
				TargetMotorPosition[2] = _ttof(explainParameter(_T("Axis3"), comm[5]));
				TargetMotorPosition[3] = _ttof(explainParameter(_T("Axis4"), comm[6]));
				TargetMotorPosition[4] = _ttof(explainParameter(_T("Axis5"), comm[7]));

				robot->ReadData(2, ActualJointPosition, sizeof(ActualJointPosition));
				//while (1)//一直查下去
				//{
				//	if (abs(ActualJointPosition[0] - position[0]) < CPublic::stepsError&& abs(ActualJointPosition[1] - position[1]) < CPublic::stepsError&& abs(ActualJointPosition[2] - position[2]) < CPublic::stepsError&& abs(ActualJointPosition[3] - position[3]) < CPublic::stepsError&&abs(ActualJointPosition[4] - position[4]) < CPublic::stepsError)
				//	{
				//		m_progress.SetStep(1);//设置进度条前进的步长
				//		break;
				//		return 1;//五个参数在误差范围内
				//	}
				//}
			}
		}
		else
		{
			AddString(_T("脚本机器人查询指令的三级指令错误？"));
			return 0;
		}
	}
	else
	{
		AddString(_T("脚本机器人指令的二级指令错误？"));
		return 0;
	}


	/*
	int count = 0, index = 0, state = 0, res = 0;
	CString Comm = _T("");
	CString strValue = _T("");
	index = findChar(comm[0], '=', 1);
	if (index == -1)
	{
	AddString(_T("脚本机器人的MoveState错误？"));
	return 0;
	}
	state = _ttoi(strValue.Mid(index));

	if (state == 2)
	{
	critical_section.Lock();
	res = SocketConnection();
	if (res == 1)
	{
	AddString(_T("创建SOCKET成功！"));
	}
	critical_section.Unlock();
	}else
	{
	file->ReadString(strValue);
	index = findChar(strValue, '=', 1);
	if (index == -1)
	{
	AddString(_T("脚本机器人的Comm错误？"));//返回日志？？
	return 0;
	}
	Comm = strValue.Mid(index);

	if (state == 0)
	{
	file->ReadString(strValue);
	index = findChar(strValue, '=', 1);
	if (index == -1)
	{
	AddString(_T("脚本机器人的InquiryNum错误？"));
	return 0;
	}
	count = _ttoi(strValue.Mid(index));

	critical_section.Lock();
	res = SocketRecieveData(Comm, count, isContinue);
	critical_section.Unlock();


	}
	else if (state == 1)
	{
	critical_section.Lock();
	res = SocketSendData(Comm, isContinue);
	critical_section.Unlock();
	}

	}
	*/

}
int CcontrolSerialNetPortDlg::explainDelayTime(CStdioFile* file, int workNum)//----------------------------------（1.2.1.4）延时解析函数
{

	CString comm;
	CString MiddleComm;
	comm = ChineseTransformation(MiddleComm, file);//读取的第二行直接是延时的数值,存入strcomm
	if (comm.GetLength() == 0)//指令内容是空的
	{
		AddString(_T("脚本中该行无指令"));
		return 0;
	}
	CString time = explainParameter(_T("Time"), comm);//Mid从左边第 index+1个字符开始,获取后面所有的字符，也就是获取了等号后面的数字
	int value = _ttoi(time);//字符转换成整形
	if (value <= 0)
	{
		AddString(_T("延时Time错误"));
		return 0;
	}
	Sleep(value);//使线程休眠一段时间

	CString m,n; 
	m.Format(_T("%d"), workNum+1);
	n.Format(_T("%d"), value);//int转换成字符
	AddString(_T("线程") + m +_T("已经延时") + n + _T("ms"));
	m_progress.OffsetPos(1);//进度条前进1
	return 1;
}

int CcontrolSerialNetPortDlg::explainCommon(CStdioFile* file, int workNum, int portIndex, bool* isContinue)//---------------------------（1.2.1.1）普通指令解析函数
{
	//CString comm[6];//存储读取到的4行数据
	//				//file->ReadString(m_fileComm);
	//CString MiddleComm;
	//comm[0] = ChineseTransformation(MiddleComm, file);
	//comm[1] = ChineseTransformation(MiddleComm, file);
	//comm[2] = ChineseTransformation(MiddleComm, file);
	//comm[3] = ChineseTransformation(MiddleComm, file);
	//comm[4] = ChineseTransformation(MiddleComm, file);
	//comm[5] = ChineseTransformation(MiddleComm, file);
	//
	//if (comm[0].GetLength() == 0 && comm[1].GetLength() == 0 && comm[2].GetLength() == 0 && comm[3].GetLength() == 0 )//普通指令内容全是空的
	//{
	//	AddString(_T("脚本中该行无指令"));
	//	return 0;
	//}
	if (*isContinue == false)
		return 0;
	int port[3];
	CString comm[9];
	CString type, route, DevIP, MiddleComm, speed, value[3], Command[3], AxisNum[6];
	for (int i = 0; i < 9; i++)
	{
		comm[i] = ChineseTransformation(MiddleComm, file);
	}

	if (comm[0].GetLength() == 0)//二级指令为空
	{
		AddString(_T("线程") + CPublic::int2CString(workNum + 1) + _T("Common指令错误！"));
		return 0;
	}
	else//9种普通指令
	{
		if (comm[0] == "\r\nIO")
		{
			DevIP = explainParameter(_T("IP"), comm[1]);
			value[0] = explainParameter(_T("Value"), comm[2]);
			Command[0] = _T("OUP X") + value[0];//生成完整的指令，待发送到相应的控制器
			if (io->sendComm(DevIP, Command[0]) == -1)
			{
				AddString(_T("线程") + CPublic::int2CString(workNum + 1) + _T("IO_Control指令“") + Command[0] + _T("”失败？"));
				return 0;
			}
			AddString(_T("线程") + CPublic::int2CString(workNum + 1) + _T("IO_Control指令“") + Command[0] + _T("”成功"));
			return 1;//发送成功
		}
		else if (comm[0] == "\r\nForceControlAxisMove")
		{
			
				return 0;
		}
		else if (comm[0] == "\r\nAxisMove")
		{
		
			DevIP = explainParameter(_T("IP"), comm[1]);

			AxisNum[0] = explainParameter(_T("AxisNum"), comm[2]);
			value[0] = explainParameter(_T("Value"), comm[3]);
			Command[0] = _T("MOV ") + AxisNum[0] + value[0];//生成完整的指令，待发送到相应的控制器
			if (io->sendComm(DevIP, Command[0]) == -1)
			{
				AddString(_T("线程") + CPublic::int2CString(workNum + 1) + _T("AxisMove指令“") + Command[0] + _T("”失败？"));
				return 0;
			}
			AddString(_T("线程") + CPublic::int2CString(workNum + 1) + _T("AxisMove指令“") + Command[0] + _T("”成功"));
			return 1;//发送成功
		}
		else if (comm[0] == "\r\nAxisSetTargetSpeed")
		{
		
			DevIP = explainParameter(_T("IP"), comm[1]);

			AxisNum[0] = explainParameter(_T("AxisNum"), comm[2]);
			value[0] = explainParameter(_T("Value"), comm[3]);
			Command[0] = _T("SVL ") + AxisNum[0] + value[0];//生成完整的指令，待发送到相应的控制器
			if (io->sendComm(DevIP, Command[0]) == -1)
			{
				AddString(_T("线程") + CPublic::int2CString(workNum + 1) + _T("AxisSetTargetSpeed指令“") + Command[0] + _T("”失败？"));
				return 0;
			}
			AddString(_T("线程") + CPublic::int2CString(workNum + 1) + _T("AxisSetTargetSpeed指令“") + Command[0] + _T("”成功"));
			return 1;//发送成功
		}
		else if (comm[0] == "\r\nChangeMode")
		{
		DevIP = explainParameter(_T("IP"), comm[1]);

		AxisNum[0] = explainParameter(_T("AxisNum"), comm[2]);
		value[0] = explainParameter(_T("Value"), comm[3]);
		Command[0] = _T("MOD ") + AxisNum[0] + value[0];//生成完整的指令，待发送到相应的控制器
		if (io->sendComm(DevIP, Command[0]) == -1)
		{
			AddString(_T("线程") + CPublic::int2CString(workNum + 1) + _T("ChangeMode指令“") + Command[0] + _T("”失败？"));
			return 0;
		}
		else
		{
			if (value[0]=="0")
			{
				AddString(_T("线程") + CPublic::int2CString(workNum + 1) + AxisNum[0]+_T("轴")+ _T("设置开环相对运动模式成功"));
			}
			if (value[0] == "1")
			{
				AddString(_T("线程") + CPublic::int2CString(workNum + 1) + AxisNum[0] + _T("轴") + _T("设置开环绝对运动模式成功"));
			}
			if (value[0] == "2")
			{
				AddString(_T("线程") + CPublic::int2CString(workNum + 1) + AxisNum[0] + _T("轴") + _T("设置闭环相对运动模式成功"));
			}
			if (value[0] == "3")
			{
				AddString(_T("线程") + CPublic::int2CString(workNum + 1) + AxisNum[0] + _T("轴") + _T("设置闭环绝对运动模式成功"));
			}
			if (value[0] == "4")
			{
				AddString(_T("线程") + CPublic::int2CString(workNum + 1) + AxisNum[0] + _T("轴") + _T("设置速率运动模式成功"));
			}
			AddString(_T("线程") + CPublic::int2CString(workNum + 1) + _T("ChangeMode指令“") + Command[0] + _T("”成功"));
		}
		
		return 1;//发送成功
		}
		else if (comm[0] == "\r\nAxisSetHomePosition")
		{
			//CString Command = explainAxisCommandNoValue(comm[1], comm[2], _T("AxisSetHomePosition"), _T("DHOM"), portIndex, isContinue);
			//m_progress.OffsetPos(1);//进度条前进1
			//if (sendAnySingleComm(Command, portIndex, isContinue) == 0)
			//{
			//	AddString(_T("发送") + Command + _T("指令无数据返回？"));
			//	return 0;
			//}
			//return 1;//发送成功
			DevIP = explainParameter(_T("IP"), comm[1]);

			AxisNum[0] = explainParameter(_T("AxisNum"), comm[2]);
			//value[0] = explainParameter(_T("Value"), comm[3]);
			Command[0] = _T("DHM ") + AxisNum[0];//生成完整的指令，待发送到相应的控制器
			if (io->sendComm(DevIP, Command[0]) == -1)
			{
				AddString(_T("线程") + CPublic::int2CString(workNum + 1) + _T("AxisSetHomePosition指令“") + Command[0] + _T("”失败？"));
				return 0;
			}
			AddString(_T("线程") + CPublic::int2CString(workNum + 1) + _T("AxisSetHomePosition指令“") + Command[0] + _T("”成功"));
			return 1;//发送成功
		}
		else if (comm[0] == "\r\nAxisGoHomePosition")
		{
			//CString Command = explainAxisCommandNoValue(comm[1], comm[2], _T("AxisGoHomePosition"), _T("GHOM"), portIndex, isContinue);
			//m_progress.OffsetPos(1);//进度条前进1
			//if (sendAnySingleComm(Command, portIndex, isContinue) == 0)
			//{
			//	AddString(_T("发送") + Command + _T("指令无数据返回？"));
			//	return 0;
			//}
			//return 1;//发送成功
			DevIP = explainParameter(_T("IP"), comm[1]);

			AxisNum[0] = explainParameter(_T("AxisNum"), comm[2]);
			//value[0] = explainParameter(_T("Value"), comm[3]);
			Command[0] = _T("GHM ") + AxisNum[0];//生成完整的指令，待发送到相应的控制器
			if (io->sendComm(DevIP, Command[0]) == -1)
			{
				AddString(_T("线程") + CPublic::int2CString(workNum + 1) + _T("AxisGoHomePosition指令“") + Command[0] + _T("”失败？"));
				return 0;
			}
			AddString(_T("线程") + CPublic::int2CString(workNum + 1) + _T("AxisGoHomePosition指令“") + Command[0] + _T("”成功"));
			return 1;//发送成功
		}
		else if (comm[0] == "\r\nAxisGoNegativeLimit")
		{
			CString Command = explainAxisCommandNoValue(comm[1], comm[2], _T("AxisGoNegativeLimit"), _T("FFNL"), portIndex, isContinue);
			m_progress.OffsetPos(1);//进度条前进1
			if (sendAnySingleComm(Command, portIndex, isContinue) == 0)
			{
				AddString(_T("发送") + Command + _T("指令无数据返回？"));
				return 0;
			}
			return 1;//发送成功
		}
		else if (comm[0] == "\r\nAxisGoPositiveLimit")
		{
			CString Command = explainAxisCommandNoValue(comm[1], comm[2], _T("AxisGoPostiveLimit"), _T("FFPL"), portIndex, isContinue);
			m_progress.OffsetPos(1);//进度条前进1
			if (sendAnySingleComm(Command, portIndex, isContinue) == 0)
			{
				AddString(_T("发送") + Command + _T("指令无数据返回？"));
				return 0;
			}
			return 1;//发送成功
		}
		else if (comm[0] == "\r\nAxisSMVR")
		{
			CString Box = explainParameter(_T("Box"), comm[1]);//Mid从左边第 index+1个字符开始,获取后面所有的字符，也就是获取了等号后面的数字		
			CString Port = explainParameter(_T("Port"), comm[2]);//Mid从左边第 index+1个字符开始,获取后面所有的字符，也就是获取了等号后面的数字
			CString Value = explainParameter(_T("Value"), comm[3]);//Mid从左边第 index+1个字符开始,获取后面所有的字符，也就是获取了等号后面的数字
			if (*isContinue == false)
				return 0;
			CString Command = Box + _T("->SMVR ") + Port + " " + Value;//生成完整的指令，待发送到相应的控制器
			//CString Command = explainAxisCommandNoValue(comm[1], comm[2], _T("AxisSMVR"), _T("SMVR"), portIndex, isContinue);
			m_progress.OffsetPos(1);//进度条前进1
			if (sendAnySingleComm(Command, portIndex, isContinue) == 0)//未发送成
			{
				AddString(_T("发送") + Command + _T("指令无数据返回？"));
				return 0;
			}
			return 1;//发送成功
		}
	}
}

int CcontrolSerialNetPortDlg::explainControlDev(CStdioFile* file, int workNum, int portIndex, bool* isContinue)
{
	//CString comm[6];//存储读取到的4行数据
	//			//file->ReadString(m_fileComm);
	//CString MiddleComm;
	//comm[0] = ChineseTransformation(MiddleComm, file);
	//comm[1] = ChineseTransformation(MiddleComm, file);
	//comm[2] = ChineseTransformation(MiddleComm, file);
	//comm[3] = ChineseTransformation(MiddleComm, file);
	//comm[4] = ChineseTransformation(MiddleComm, file);
	//comm[5] = ChineseTransformation(MiddleComm, file);

	//if (comm[0].GetLength() == 0 && comm[1].GetLength() == 0 && comm[2].GetLength() == 0 && comm[3].GetLength() == 0)//普通指令内容全是空的
	//{
	//	AddString(_T("脚本中该行无指令"));
	//	return 0;
	//}
	if (*isContinue == false)
		return 0;
	int port[3];
	CString comm[9];
	CString type, route, DevIP, MiddleComm, speed, value[3], Command[3],AxisNum[6];
	for (int i = 0; i < 9; i++)
	{
		comm[i] = ChineseTransformation(MiddleComm, file);
	}

	if (comm[0].GetLength() == 0)//二级指令为空
	{
		AddString(_T("线程") + CPublic::int2CString(workNum + 1) + _T("ControlDev指令错误！"));
		return 0;
	}
	if (comm[0] == "\r\nIO_Control")
	{
		DevIP = explainParameter(_T("IP"), comm[1]);
		value[0] = explainParameter(_T("Value"), comm[2]);
		Command[0] = _T("OUP X") + value[0];//生成完整的指令，待发送到相应的控制器
		if (io->sendComm(DevIP, Command[0]) == -1)
		{
			AddString(_T("线程") + CPublic::int2CString(workNum + 1) + _T("IO_Control指令“") + Command[0] + _T("”失败？"));
			return 0;
		}
		AddString(_T("线程") + CPublic::int2CString(workNum + 1) + _T("IO_Control指令“") + Command[0] + _T("”成功"));
		return 1;//发送成功
	}
	else if (comm[0] == "\r\nAxis_Control")
	{
		DevIP = explainParameter(_T("IP"), comm[1]);
		
		AxisNum[0]= explainParameter(_T("AxisNum"), comm[2]);
		value[0] = explainParameter(_T("Value"), comm[3]);
		Command[0] = _T("MOV ") +AxisNum[0] + value[0];//生成完整的指令，待发送到相应的控制器
		if (io->sendComm(DevIP, Command[0]) == -1)
		{
			AddString(_T("线程") + CPublic::int2CString(workNum + 1) + _T("Axis_Control指令“") + Command[0] + _T("”失败？"));
			return 0;
		}
		AddString(_T("线程") + CPublic::int2CString(workNum + 1) + _T("IO_Control指令“") + Command[0] + _T("”成功"));
		return 1;//发送成功

	}

	else if (comm[0] == "\r\nAxisSetTargetSpeed")
	{
		
	}
	else if (comm[0] == "\r\nAxisGoHomePosition")
	{

	}
}

CString CcontrolSerialNetPortDlg::explainAxisCommandNoValue(CString comm1, CString comm2, CString commClass, CString commandName, int portIndex, bool*isContinue)
{
	int index = findChar(comm1, '=', 1);//查找字符“=”函数，找不到则返回-1。
	if (index == -1)
	{
		AddString(_T("脚本中") + commClass + _T("命令的Box错误？"));
		return 0;
	}
	CString Box = comm1.Mid(index);//Mid从左边第 index+1个字符开始,获取后面所有的字符，也就是获取了等号后面的数字
	index = findChar(comm2, '=', 1);//查找字符“=”函数，找不到则返回-1。
	if (index == -1)
	{
		AddString(_T("脚本中") + commClass + _T("命令的Port错误？"));
		return 0;
	}
	CString Port = comm2.Mid(index);//Mid从左边第 index+1个字符开始,获取后面所有的字符，也就是获取了等号后面的数字
	if (*isContinue == false)
		return 0;

	CString Command = Box + "->" + commandName + " " + Port;//生成完整的指令，待发送到相应的控制器
	return Command;
}

CString CcontrolSerialNetPortDlg::explainAxisCommand(CString comm1, CString comm2, CString comm3,CString commClass, CString commandName, int portIndex, bool*isContinue)
{
	int index = findChar(comm1, '=', 1);//查找字符“=”函数，找不到则返回-1。
	if (index == -1)
	{
		AddString(_T("脚本中")+commClass+_T("命令的Box错误？"));
		return 0;
	}
	CString Box = comm1.Mid(index);//Mid从左边第 index+1个字符开始,获取后面所有的字符，也就是获取了等号后面的数字
	index = findChar(comm2, '=', 1);//查找字符“=”函数，找不到则返回-1。
	if (index == -1)
	{
		AddString(_T("脚本中") + commClass + _T("命令的Port错误？"));
		return 0;
	}
	CString Port = comm2.Mid(index);//Mid从左边第 index+1个字符开始,获取后面所有的字符，也就是获取了等号后面的数字
	index = findChar(comm3, '=', 1);//查找字符“=”函数，找不到则返回-1。
	if (index == -1)
	{
		AddString(_T("脚本中") + commClass + _T("命令的Value错误？"));
		return 0;
	}
	CString Value = comm3.Mid(index);//Mid从左边第 index+1个字符开始,获取后面所有的字符，也就是获取了等号后面的数字
	if (*isContinue == false)
		return 0;

	 CString Command = Box + "->"+commandName + " " + Port + " " + Value;//生成完整的指令，待发送到相应的控制器
	 return Command;
}



int CcontrolSerialNetPortDlg::explainInquiry(CStdioFile* file, int workNum, int portIndex, bool* Continue)//----------------------（1.2.1.2）查询解析函数
{
	CString comm[4];//存储读取到的4行数据
	CString command;
	//CString MiddleComm;
	//CString comm[9];//存储读取到的11行数据
	CString DevIP, MiddleComm, value[3], Command[3], type, route;
	int port[3];
	CString Valua;
	bool Valu;
	int Value;
	int res = 0;
	comm[0] = ChineseTransformation(MiddleComm, file);
	comm[1] = ChineseTransformation(MiddleComm, file);
	comm[2] = ChineseTransformation(MiddleComm, file);
	comm[3] = ChineseTransformation(MiddleComm, file);
	if (comm[0].GetLength() == 0 && comm[1].GetLength() == 0 && comm[2].GetLength() == 0 && comm[3].GetLength() == 0)//指令内容全是空的
	{
		AddString(_T("脚本中该行无指令"));
		return 0;
	}
	else//4种查询指令
	{
		if (comm[0] == "\r\nIO?")
		{
			DevIP = explainParameter(_T("IP"), comm[1]);
			//port[0] = _ttof(explainParameter(_T("Port"), comm[2]));
			//Valu = (explainParameter(_T("Value"), comm[2]) == 1) ? true : false;
			Valua = explainParameter(_T("Value"), comm[2]);

			Command[0] = _T("IN?");//生成完整的指令，待发送到相应的控制器
			bool IOBitValues[16] = {};
			//bool IOBitValues[16]; // 假设有一个包含16个bool值的数组

			/*int decimalValue = 0;

			for (int i = 0; i < 16; i++) {
				decimalValue += (IOBitValues[i] ? 1 : 0) << i;
			}*/
			if (io->inquiryIO(DevIP, Command[0], IOBitValues) == false)
			{
				AddString(_T("线程") + CPublic::int2CString(workNum + 1) + _T("发送IO查询指令“") + Command[0] + _T("”失败？"));
				return 0;
			}
			//int data[6] = { 0 };
			//for (int i = 0; i < 16; i++)
			//{
			//	IOBitValues[i] = ((data[0] & (0x01 << i)) == 0) ? false : true;   //0x01<<i表示将0x01左移i位
			//}
			//int qwe = boolArrayToInt(IOBitValues,16);
			int qqq = 0;
			for (int i = 0; i < 16; i++)
			{
				qqq |= (IOBitValues[i] ? 1 : 0) << i;
			}
			CString asdf;
			asdf.Format(_T("%d"), qqq);
			while (1) //需要设置定时器
			{
				io->inquiryIO(DevIP, Command[0], IOBitValues);
				int qq = 0;
				for (int i = 0; i < 16; i++)
				{
					qq |= (IOBitValues[i] ? 1 : 0) << i;
				}
				CString asd;
				asd.Format(_T("%d"), qq);
				if (asd == Valua)
				{

					res = 1;
					AddString(_T("线程") + CPublic::int2CString(workNum + 1) + _T("发送IO查询指令“") + Command[0] + _T("”成功"));
					break;

				}
				else continue;
			}
			return res;
		}
		else if (comm[0] == "\r\nLimit?")
		{

			AddString(_T("线程") + CPublic::int2CString(workNum + 1) + _T("无此指令") + Command[0]);
		}
		else if (comm[0] == "\r\nRelativePosition?")
		{
			//command = explainAxisCommand(comm[1], comm[2], comm[3], _T("RelativePosition?"), _T("MVR?"), portIndex, Continue);
			DevIP = explainParameter(_T("IP"), comm[1]);
			port[0] = _ttof(explainParameter(_T("Port"), comm[2]));
			Valu = (explainParameter(_T("Value"), comm[3]) == 1) ? true : false;

			Command[0] = _T("TR?");//生成完整的指令，待发送到相应的控制器
			int IOBitValues[6] = {};
			if (io->inquiryAxisPOS(DevIP, Command[0], IOBitValues) == false)
			{
				AddString(_T("线程") + CPublic::int2CString(workNum + 1) + _T("发送RelativePosition查询指令“") + Command[0] + _T("”失败？"));
				return 0;
			}
			while (1) //需要设置定时器
			{
				if (IOBitValues[port[0] - 1] == Valu)
				{
					res = 1;
					break;
				}
				else continue;
			}
			return res;
		}
		else if (comm[0] == "\r\nAbsolutePosition?")
		{
			//command = explainAxisCommand(comm[1], comm[2], comm[3], _T("AbsolutePosition?"), _T("POS?"), portIndex, Continue);
			DevIP = explainParameter(_T("IP"), comm[1]);
			port[0] = _ttof(explainParameter(_T("Port"), comm[2]));
			Value = _ttof(explainParameter(_T("Value"), comm[3]));
			//Value = (explainParameter(_T("Value"), comm[3]) == 1) ? true : false;

			Command[0] = _T("IN?");//生成完整的指令，待发送到相应的控制器
			int AxisBitValues[6] = {};
			if (io->inquiryAxisPOS(DevIP, Command[0], AxisBitValues) == false)
			{
				AddString(_T("线程") + CPublic::int2CString(workNum + 1) + _T("发送RelativePosition查询指令“") + Command[0] + _T("”失败？"));
				return 0;
			}
			while (1) //需要设置定时器
			{
				CString aaa;
				aaa.Format(_T("%d"), AxisBitValues[port[0] - 1]);
				CString bbb;
				bbb.Format(_T("%d"), Value);
				//AddString(_T("线程") + CPublic::int2CString(workNum + 1) + _T("查询值为：“") + aaa+ _T("”"));
				AddString(_T("线程") + CPublic::int2CString(workNum + 1) + _T("查询值为：“") + aaa + _T("”"));
				io->inquiryAxisPOS(DevIP, Command[0], AxisBitValues);
				CString inquiryresultvalue[6];
				for (int i = 0; i < 6; i++)
				{
					inquiryresultvalue[i].Format(_T("%d"), AxisBitValues[i]);
				}
				AddString(_T("---------线程") + CPublic::int2CString(workNum + 1) + _T("目标值为：“") + bbb + _T("”")); //inquiryresultvalue[2]
				if (AxisBitValues[port[0] - 1] == Value)
				{
					res = 1;
					break;
				}

				else continue;
			}
			return res;
		}

		int index = findChar(comm[3], '=', 1);//查找字符“=”函数
		if (index == -1 || comm[0] != "\r\nIO?")
		{
			AddString(_T("脚本中查询命令的Value错误？"));
			return 0;
		}
		//	int Value = _ttoi(comm[3].Mid(index));//String 型转化成 int 型　，Mid从左边第 index+1个字符开始,获取后面所有的字符，也就是获取了等号后面的数字
		//	bool isPos = (comm[0].Find(_T("Limit?")) != -1) ? false : true;
		//	m_progress.OffsetPos(1);//移动进度条一段距离
		//	return inquiry(command, portIndex, Value, isPos, Continue);//转发送查询指令函数（1.2.1.2.1）
	}
}





//
//int CcontrolSerialNetPortDlg::explainInquiry(CStdioFile* file, int workNum, int portIndex, bool* Continue)//----------------------（1.2.1.2）查询解析函数
//{
//	CString comm[4];//存储读取到的4行数据
//	CString command;
//	//CString MiddleComm;
//	//CString comm[9];//存储读取到的11行数据
//	CString DevIP, MiddleComm, value[3], Command[3], type, route;
//	int port[3];
//	bool Valu;
//	int Value;
//	int res = 0;
//	comm[0] = ChineseTransformation(MiddleComm, file);
//	comm[1] = ChineseTransformation(MiddleComm, file);
//	comm[2] = ChineseTransformation(MiddleComm, file);
//	comm[3] = ChineseTransformation(MiddleComm, file);
//	if (comm[0].GetLength() == 0 && comm[1].GetLength() == 0 && comm[2].GetLength() == 0 && comm[3].GetLength() == 0)//指令内容全是空的
//	{
//		AddString(_T("脚本中该行无指令"));
//		return 0;
//	}
//	else//4种查询指令
//	{
//		if (comm[0]== "\r\nIO?")
//		{
//			DevIP = explainParameter(_T("IP"), comm[1]);
//			//port[0] = _ttof(explainParameter(_T("Port"), comm[2]));
//			Valu = (explainParameter(_T("Value"), comm[2]) == 1) ? true : false;
//
//			Command[0] = _T("IN?");//生成完整的指令，待发送到相应的控制器
//			bool IOBitValues[16] = {};
//			//bool IOBitValues[16]; // 假设有一个包含16个bool值的数组
//
//			int decimalValue = 0;
//
//			for (int i = 0; i < 16; i++) {
//				decimalValue += (IOBitValues[i] ? 1 : 0) << i;
//			}
//			if (io->inquiryIO(DevIP, Command[0], IOBitValues) == false)
//			{
//				AddString(_T("线程") + CPublic::int2CString(workNum + 1) + _T("发送IO查询指令“") + Command[0] + _T("”失败？"));
//				return 0;
//			}
//			while (1) //需要设置定时器
//			{
//				if (decimalValue == Valu)
//				{
//					res = 1;
//					break;
//				}
//				else continue;
//			}
//			return res;
//		}
//		else if(comm[0]=="\r\nLimit?")
//		{
//			//command = explainAxisCommand(comm[1], comm[2], comm[3], _T("Limit?"), _T("LIM?"), portIndex, Continue);
//			//DevIP = explainParameter(_T("IP"), comm[1]);
//			//port[0] = _ttof(explainParameter(_T("Port"), comm[2]));
//			//Valu = (explainParameter(_T("Value"), comm[3]) == 1) ? true : false;
//
//			//Command[0] = _T("IN?");//生成完整的指令，待发送到相应的控制器
//			//bool IOBitValues[16] = {};
//			//if (io->inquiryIO(DevIP, Command[0], IOBitValues) == false)
//			//{
//			//	AddString(_T("线程") + CPublic::int2CString(workNum + 1) + _T("发送IO查询指令“") + Command[0] + _T("”失败？"));
//			//	return 0;
//			//}
//			//while (1) //需要设置定时器
//			//{
//			//	if (IOBitValues[port[0] - 1] == Valu)
//			//	{
//			//		res = 1;
//			//		break;
//			//	}
//			//	else continue;
//			//}
//			//return res;
//			AddString(_T("线程") + CPublic::int2CString(workNum + 1) + _T("无此指令") + Command[0]);
//		}
//		else if (comm[0] == "\r\nRelativePosition?")
//		{
//			//command = explainAxisCommand(comm[1], comm[2], comm[3], _T("RelativePosition?"), _T("MVR?"), portIndex, Continue);
//			DevIP = explainParameter(_T("IP"), comm[1]);
//			port[0] = _ttof(explainParameter(_T("Port"), comm[2]));
//			Valu = (explainParameter(_T("Value"), comm[3]) == 1) ? true : false;
//
//			Command[0] = _T("TR?");//生成完整的指令，待发送到相应的控制器
//			int IOBitValues[6] = {};
//			if (io->inquiryAxisPOS(DevIP, Command[0], IOBitValues) == false)
//			{
//				AddString(_T("线程") + CPublic::int2CString(workNum + 1) + _T("发送RelativePosition查询指令“") + Command[0] + _T("”失败？"));
//				return 0;
//			}
//			while (1) //需要设置定时器
//			{
//				if (IOBitValues[port[0] - 1] == Valu)
//				{
//					res = 1;
//					break;
//				}
//				else continue;
//			}
//			return res;
//		}
//		else if (comm[0] == "\r\nAbsolutePosition?")
//		{
//			//command = explainAxisCommand(comm[1], comm[2], comm[3], _T("AbsolutePosition?"), _T("POS?"), portIndex, Continue);
//			DevIP = explainParameter(_T("IP"), comm[1]);
//			port[0] = _ttof(explainParameter(_T("Port"), comm[2]));
//			Value = _ttof(explainParameter(_T("Value"), comm[3]));
//			//Value = (explainParameter(_T("Value"), comm[3]) == 1) ? true : false;
//
//			Command[0] = _T("GS?");//生成完整的指令，待发送到相应的控制器
//			int AxisBitValues[6] = {};
//			if (io->inquiryAxisPOS(DevIP, Command[0],AxisBitValues) == false)
//			{
//				AddString(_T("线程") + CPublic::int2CString(workNum + 1) + _T("发送RelativePosition查询指令“") + Command[0] + _T("”失败？"));
//				return 0;
//			}
//			while (1) //需要设置定时器
//			{
//				CString aaa;
//				aaa.Format(_T("%d"), AxisBitValues[port[0] - 1]);
//				//AddString(_T("线程") + CPublic::int2CString(workNum + 1) + _T("查询值为：“") + aaa+ _T("”"));
//				AddString(_T("线程") + CPublic::int2CString(workNum + 1) + _T("查询值为：“") + aaa + _T("”"));
//				io->inquiryAxisPOS(DevIP, Command[0], AxisBitValues);
//				CString inquiryresultvalue[6];
//				for (int i = 0; i < 6; i++)
//				{
//					inquiryresultvalue[i].Format(_T("%d"), AxisBitValues[i]);
//				}
//				AddString(_T("---------线程") + CPublic::int2CString(workNum + 1) + _T("查询值为：“") + inquiryresultvalue[2] + _T("”"));
//				if (AxisBitValues[port[0] - 1] == Value)
//				{
//					res = 1;
//					break;
//				}
//					
//				else continue;
//			}
//			return res;
//		}
//
//		int index = findChar(comm[3], '=', 1);//查找字符“=”函数
//		if (index == -1|| comm[0]!= "\r\nIO?")
//		{
//			AddString(_T("脚本中查询命令的Value错误？"));
//			return 0;
//		}
//	//	int Value = _ttoi(comm[3].Mid(index));//String 型转化成 int 型　，Mid从左边第 index+1个字符开始,获取后面所有的字符，也就是获取了等号后面的数字
//	//	bool isPos = (comm[0].Find(_T("Limit?")) != -1) ? false : true;
//	//	m_progress.OffsetPos(1);//移动进度条一段距离
//	//	return inquiry(command, portIndex, Value, isPos, Continue);//转发送查询指令函数（1.2.1.2.1）
//	}
//}


int CcontrolSerialNetPortDlg::explainImageErrorAndRatio(CStdioFile* file, int workNum)
{

	CString comm;
	//file->ReadString(m_fileComm);
	CString MiddleComm;
	comm = ChineseTransformation(MiddleComm, file);
	int index = findChar(comm, '=', 1);
	if (index == -1)
	{
		//AddString(_T("延时时间错误"));
		return 0;		
	}

	CPublic::g_newinitParameter[workNum].angelErrorX = _wtof(comm.Mid(index));

	comm = ChineseTransformation(MiddleComm, file);
	index = findChar(comm, '=', 1);
	if (index == -1)
		return 0;		
	CPublic::g_newinitParameter[workNum].angelErrorY = _wtof(comm.Mid(index));

	comm = ChineseTransformation(MiddleComm, file);
	index = findChar(comm, '=', 1);
	if (index == -1)
		return 0;		
	CPublic::g_newinitParameter[workNum].ratioA = _wtof(comm.Mid(index));

	comm = ChineseTransformation(MiddleComm, file);
	index = findChar(comm, '=', 1);
	if (index == -1)
		return 0;		
	CPublic::g_newinitParameter[workNum].ratioX = _wtof(comm.Mid(index));

	comm = ChineseTransformation(MiddleComm, file);
	index = findChar(comm, '=', 1);
	if (index == -1)
		return 0;		
	CPublic::g_newinitParameter[workNum].ratioY = _wtof(comm.Mid(index));

	return 1;
}


int CcontrolSerialNetPortDlg::explainOmissionDetection(CStdioFile* file, int workNum, bool* Continue)
{
	OutputDebugString(L"Explain Omission");
	return 0;
}


int CcontrolSerialNetPortDlg::explainImageProcessing(CStdioFile* file, int workNum, bool* Continue)//------------------------- （1.2.1.5）图像处理解析函数
{
	if (*Continue == false)
		return 0;
	CString comm;
	file->ReadString(comm);
	if (comm == L"TemplateMatching")
	{
		explainImageProcessing1(file, workNum, Continue);//模板匹配
	}
	else if (comm == L"CricleDetection")
	{
		explainImageProcessing2(file, workNum, Continue);//圆点匹配
	}
}


int CcontrolSerialNetPortDlg::explainImageProcessing1(CStdioFile* file, int workNum, bool* Continue)//---------------------------（1.2.1.5.1）模板匹配图像处理解析函数
{
	if (*Continue == false)
		return 0;

	CString comm[8];
	CString MiddleComm;
	comm[0] = ChineseTransformation(MiddleComm, file);

	CString number = explainParameter(_T("Number"), comm[0]);
	/*if (comm[0].Left(6) == _T("\r\nNumber"))
	{
		int index = findChar(comm[0], '=', 1);
		if (index == -1)
		{
			AddString(_T("图像处理模板识别中的Number行错误？"));
			return 0;
		}*/
		//_ttoi字符型转换成int
	CPublic::g_imagePara1[workNum].proNum = _ttoi(number);//将图像处理次数序号存入结构体
	//继续往下面读取
	for (int i = 1; i < 8; i++)
	{
		comm[i] = ChineseTransformation(MiddleComm, file);//读取5行存放在数组中
	}
	CString ROIX = explainParameter(_T("模式识别中的ROIX"), comm[2]);
	int x = _ttoi(ROIX);//字符转换成整形
	CPublic::g_imagePara1[workNum].ROI_x = x;

	CString ROIY = explainParameter(_T("模式识别中的ROIY"), comm[3]);
	int y = _ttoi(ROIY);//字符转换成整形
	CPublic::g_imagePara1[workNum].ROI_y = y;

	CString ROIWidth = explainParameter(_T("模式识别中的ROIWidth"), comm[4]);
	int width = _ttoi(ROIWidth);//字符转换成整形
	CPublic::g_imagePara1[workNum].ROI_w =width;

	CString ROIHight = explainParameter(_T("模式识别中的ROIHight"), comm[5]);
	int hight = _ttoi(ROIHight);//字符转换成整形
	CPublic::g_imagePara1[workNum].ROI_h = hight;

	//新增参数：形态学区域面积
	CString IterationNum = explainParameter(_T("模式识别中的iteration"), comm[6]);
	int iterationNum = _ttoi(IterationNum);//字符转换成整形
	CPublic::g_imagePara1[workNum].iterationNum = iterationNum;

	//新增参数：匹配平滑度
	CString Smoothness = explainParameter(_T("模式识别中的smooth"), comm[7]);
	int smoothness = _ttoi(Smoothness);//字符转换成整形
	CPublic::g_imagePara1[workNum].smoothness = smoothness;




	CString Path = explainParameter(_T("模式识别中的Path"), comm[1]);
	CPublic::g_imagePara1[workNum].modelFilePath = CPublic::pathSwitch(Path);//路径转换

	//
	CPublic::g_typeOfImagePro[workNum] = 0;

	int res = imageProcess(&DigUserHookData[workNum], &CPublic::g_imagePosInfo1[workNum][(CPublic::g_imagePara1[workNum].proNum - 1) % PRONUM1], workNum);//---------------（1.2.1.5.1.1）获取图像处理结果函数


	AddString(_T("线程") + CPublic::int2CString(workNum+1) + _T("第")+CPublic::int2CString(CPublic::g_imagePara1[workNum].proNum) + _T("次图像处理结果X值：") + CPublic::double2CString(CPublic::g_imagePosInfo1[workNum][(CPublic::g_imagePara1[workNum].proNum - 1) % PRONUM1].x));
	AddString(_T("线程") + CPublic::int2CString(workNum+1) + _T("第")+CPublic::int2CString(CPublic::g_imagePara1[workNum].proNum) + _T("次图像处理结果Y值：") + CPublic::double2CString(CPublic::g_imagePosInfo1[workNum][(CPublic::g_imagePara1[workNum].proNum - 1) % PRONUM1].y));
	AddString(_T("线程") + CPublic::int2CString(workNum+1) + _T("第")+CPublic::int2CString(CPublic::g_imagePara1[workNum].proNum) + _T("次图像处理结果A值：") + CPublic::double2CString(CPublic::g_imagePosInfo1[workNum][(CPublic::g_imagePara1[workNum].proNum - 1) % PRONUM1].a));
	m_progress.OffsetPos(1);//进度条
	//return res;
	/*
		if (comm.Left(11) == _T("SearchSpeed"))
		{
			int index = findChar(comm, '=', 1);
			if (index == -1)
			{
				AddString(_T("模板识别中的SearchSpeed行错误？"));
				return 0;
			}
			CPublic::g_imagePara1[workNum].searchSpeed = _ttoi(comm.Mid(index));
		}
		else if (comm.Left(11) == _T("MaxMatchNum"))
		{
			int index = findChar(comm, '=', 1);
			if (index == -1)
			{
				AddString(_T("模板识别中的MaxMatchNum行错误？"));
				return 0;
			}		
			CPublic::g_imagePara1[workNum].maxMatchNum = _ttoi(comm.Mid(index));
		}
		else if (comm.Left(8) == _T("MatchNum"))
		{
			int index = findChar(comm, '=', 1);
			if (index == -1)
			{
				AddString(_T("模板识别中的MatchNum行错误？"));
				return 0;
			}			
			CPublic::g_imagePara1[workNum].matchNum = _ttoi(comm.Mid(index));
		}
		else if (comm.Left(13) == _T("ModelFilePath"))
		{
			int index = findChar(comm, '=', 1);
			if (index == -1)
			{
				AddString(_T("模板识别中的ModelFilePath行错误？"));
				return 0;
			}	
			CPublic::g_imagePara1[workNum].modelFilePath = CPublic::pathSwitch(comm.Mid(index));
		}
		else if (comm.Left(10) == _T("Smoothness"))
		{
			int index = findChar(comm, '=', 1);
			if (index == -1)
			{
				AddString(_T("模板识别中的Smoothness行错误？"));
				return 0;
			}	
			CPublic::g_imagePara1[workNum].smoothness = _ttoi(comm.Mid(index));
		}
		else if (comm.Left(12) == _T("IterationNum"))
		{
			int index = findChar(comm, '=', 1);
			if (index == -1)
			{
				AddString(_T("模板识别中的IterationNum行错误？"));
				return 0;
			}		
			CPublic::g_imagePara1[workNum].iterationNum = _ttoi(comm.Mid(index));
		}		
		else if (comm.Left(5) == _T("ROI_x"))
		{
			int index = findChar(comm, '=', 1);
			if (index == -1)
			{
				AddString(_T("模板识别中的ROI_x行错误？"));
				return 0;
			}			
			CPublic::g_imagePara1[workNum].ROI_x = _ttoi(comm.Mid(index));
		}
		else if (comm.Left(5) == _T("ROI_y"))
		{
			int index = findChar(comm, '=', 1);
			if (index == -1)
			{
				AddString(_T("模板识别中的ROI_y行错误？"));
				return 0;
			}		
			CPublic::g_imagePara1[workNum].ROI_y = _ttoi(comm.Mid(index));
		}
		else if (comm.Left(5) == _T("ROI_w"))
		{
			int index = findChar(comm, '=', 1);
			if (index == -1)
			{
				AddString(_T("模板识别中的ROI_w行错误？"));
				return 0;
			}		
			CPublic::g_imagePara1[workNum].ROI_w = _ttoi(comm.Mid(index));
		}
		else if (comm.Left(5) == _T("ROI_h"))
		{
			int index = findChar(comm, '=', 1);
			if (index == -1)
			{
				AddString(_T("模板识别中的ROI_h行错误？"));
				return 0;
			}	
			CPublic::g_imagePara1[workNum].ROI_h = _ttoi(comm.Mid(index));
		}
		else if (comm.Left(13) == _T("ModelDistance"))
		{
			int index = findChar(comm, '=', 1);
			if (index == -1)
			{
				AddString(_T("模板识别中的ModelDistance行错误？"));
				return 0;
			}		
			CPublic::g_imagePara1[workNum].modelDistance = _ttoi(comm.Mid(index));
		}
		else if (comm.Left(10) == _T("MethodFlag"))
		{
			int index = findChar(comm, '=', 1);
			if (index == -1)
			{
				AddString(_T("模板识别中的MethodFlag行错误？"));
				return 0;
			}		
			CPublic::g_imagePara1[workNum].MethodFlag = _ttoi(comm.Mid(index));
		}
		else if (comm.Left(13) == _T("ThresholdFlag"))
		{
			int index = findChar(comm, '=', 1);
			if (index == -1)
			{
				AddString(_T("模板识别中的ThresholdFlag行错误？"));
				return 0;
			}			
			CPublic::g_imagePara1[workNum].ThresholdFlag = _ttoi(comm.Mid(index));
		}
		else if (comm.Left(14) == _T("ThresholdValue"))
		{
			int index = findChar(comm, '=', 1);
			if (index == -1)
			{
				AddString(_T("模板识别中的ThresholdValue行错误？"));
				return 0;
			}		
			CPublic::g_imagePara1[workNum].ThresholdValue = _ttoi(comm.Mid(index));
		}
		else if (comm.Left(11) == _T("SharpenFlag"))
		{
			int index = findChar(comm, '=', 1);
			if (index == -1)
			{
				AddString(_T("模板识别中的SharpenFlag行错误？"));
				return 0;
			}			
			CPublic::g_imagePara1[workNum].SharpenFlag = _ttoi(comm.Mid(index));
		}
		else if (comm.Left(10) == _T("MedianFlag"))
		{
			int index = findChar(comm, '=', 1);
			if (index == -1)
				return 0;		
			CPublic::g_imagePara1[workNum].MedianFlag = _ttoi(comm.Mid(index));
		}
		else if (comm.Left(16) == _T("FilterSmoothness"))
		{
			int index = findChar(comm, '=', 1);
			if (index == -1)
			{
				AddString(_T("模板识别中的FilterSmoothness行错误？"));
				return 0;
			}		
			CPublic::g_imagePara1[workNum].FilterSmoothness = _wtof(comm.Mid(index));
		}
		else if (comm.Left(15) == _T("ExtractionScale"))
		{
			int index = findChar(comm, '=', 1);
			if (index == -1)
			{
				AddString(_T("模板识别中的ExtractionScale行错误？"));
				return 0;
			}			
			CPublic::g_imagePara1[workNum].ExtractionScale = _wtof(comm.Mid(index));
		}
		else if (comm.Left(11) == _T("GapDistance"))
		{
			int index = findChar(comm, '=', 1);
			if (index == -1)
			{
				AddString(_T("模板识别中的GapDistance行错误？"));
				return 0;
			}			
			CPublic::g_imagePara1[workNum].GapDistance = _wtof(comm.Mid(index));
		}
		else if (comm.Left(13) == _T("GapContinuity"))
		{
			int index = findChar(comm, '=', 1);
			if (index == -1)
			{
				AddString(_T("模板识别中的GapContinuity行错误？"));
				return 0;
			}			
			CPublic::g_imagePara1[workNum].GapContinuity = _wtof(comm.Mid(index));
		}
		else
		{
			AddString(_T("模板识别中的无此命令行？"));
			return 0;
		}
	
	}

	m_progress[workNum].OffsetPos(1);//进度条

	CPublic::g_typeOfImagePro[workNum] = 0;
	int res = imageProcess(&DigUserHookData[workNum], &CPublic::g_imagePosInfo1[workNum][(proNum - 1) % PRONUM1], workNum);

	AddString(_T("工位") + CPublic::int2CString(workNum) + CPublic::int2CString(proNum) + _T("次图像处理结果X值：") + CPublic::double2CString(CPublic::g_imagePosInfo1[workNum][(proNum - 1) % PRONUM1].x));
	AddString(_T("工位") + CPublic::int2CString(workNum) + CPublic::int2CString(proNum) + _T("次图像处理结果Y值：") +  CPublic::double2CString(CPublic::g_imagePosInfo1[workNum][(proNum - 1) % PRONUM1].y));
	AddString(_T("工位") + CPublic::int2CString(workNum) + CPublic::int2CString(proNum) + _T("次图像处理结果A值：") + CPublic::double2CString(CPublic::g_imagePosInfo1[workNum][(proNum - 1) % PRONUM1].a));
	return res;
	*/
	/*if (proNum  % PRONUM1 == 2)
		CPublic::angcalc(&CPublic::g_imagePosInfo1[workNum][0], &CPublic::g_imagePosInfo1[workNum][1], &CPublic::g_imagePosInfo1[workNum][1]);
	else if (proNum  % PRONUM1 == 0)
		CPublic::poscalc(&CPublic::g_imagePosInfo1[workNum][0], &CPublic::g_imagePosInfo1[workNum][2], &CPublic::g_imagePosInfo1[workNum][2]);
	*/
}

int CcontrolSerialNetPortDlg::imageProcess(DigHookDataStruct* DigUserHookData, PositionInfo* proResult, int workNum)
{

	DigStartAcquisition(DigUserHookData, 1);
	proResult->x = CPublic::g_positionInfo[workNum].x;
	proResult->y = CPublic::g_positionInfo[workNum].y;
	proResult->a = CPublic::g_positionInfo[workNum].a;

	Sleep(500);

	return 1;

}


int CcontrolSerialNetPortDlg::explainImageProcessing2(CStdioFile* file, int workNum, bool* Continue)//---------------------------（1.2.1.5.2）点搜索图像处理解析函数
{
	if (*Continue == false)
		return 0;
	CString comm[7];
	CString MiddleComm;
	comm[0] = ChineseTransformation(MiddleComm, file);
	
	if (comm[0].Left(6) == _T("\r\nNumber"))
	{
		int index = findChar(comm[0], '=', 1);
		if (index == -1)
		{
			AddString(_T("图像处理模板识别中的Number行错误？"));
			return 0;
		}
		CPublic::g_imagePara1[workNum].proNum = _ttoi(comm[0].Mid(index));//将图像处理次数序号存入结构体
	}
	else
		return 0;
	//继续往下面读取
	for (int i = 1; i < 7; i++)
	{
		comm[i] = ChineseTransformation(MiddleComm, file);;//读取5行存放在数组中
	}
	CString ROIX = explainParameter(_T("圆点识别中的ROIX"), comm[1]);//Mid从左边第 index+1个字符开始,获取后面所有的字符，也就是获取了等号后面的数字
	int x = _ttoi(ROIX);//字符转换成整形
	CPublic::g_imagePara2[workNum].ROI_x = x;

	CString ROIY = explainParameter(_T("圆点识别中的ROIY"), comm[2]);//Mid从左边第 index+1个字符开始,获取后面所有的字符，也就是获取了等号后面的数字
	int y = _ttoi(ROIY);//字符转换成整形
	CPublic::g_imagePara2[workNum].ROI_y = y;

	CString ROIWidth = explainParameter(_T("圆点识别中的ROIWidth"), comm[3]);//Mid从左边第 index+1个字符开始,获取后面所有的字符，也就是获取了等号后面的数字
	int width = _ttoi(ROIWidth);//字符转换成整形
	CPublic::g_imagePara2[workNum].ROI_w = width;

	CString ROIHight = explainParameter(_T("圆点识别中的ROIHight"), comm[4]);//Mid从左边第 index+1个字符开始,获取后面所有的字符，也就是获取了等号后面的数字
	int hight = _ttoi(ROIHight);//字符转换成整形
	CPublic::g_imagePara2[workNum].ROI_h = hight;


	CString CricleRadiusLow = explainParameter(_T("圆点识别中的CricleRadiusLow"), comm[5]);//Mid从左边第 index+1个字符开始,获取后面所有的字符，也就是获取了等号后面的数字
	double Rlow = _wtof(CricleRadiusLow);
	CPublic::g_imagePara2[workNum].CricleRadius_Low = Rlow;//将字符串转浮点数

	CString CricleRadiusHigh = explainParameter(_T("圆点识别中的CricleRadiusHigh"), comm[6]);
	double Rhigh = _wtof(CricleRadiusHigh);
	CPublic::g_imagePara2[workNum].CricleRadius_High = Rhigh;

	CPublic::g_typeOfImagePro[workNum] = 1;
	//DigUserHookData[workNum].workNum = workNum;

	//int res =imageProcess(&DigUserHookData[workNum], &CPublic::g_imagePosInfo2[workNum][(CPublic::g_imagePara1[workNum].proNum - 1) % PRONUM2], workNum);

	AddString(_T("线程") + CPublic::int2CString(workNum) + _T("第") + CPublic::int2CString(CPublic::g_imagePara1[workNum].proNum) + _T("次图像处理结果X值：") + CPublic::double2CString(CPublic::g_imagePosInfo1[workNum][(CPublic::g_imagePara1[workNum].proNum - 1) % PRONUM1].x));
	AddString(_T("线程") + CPublic::int2CString(workNum) + _T("第") + CPublic::int2CString(CPublic::g_imagePara1[workNum].proNum) + _T("次图像处理结果Y值：") + CPublic::double2CString(CPublic::g_imagePosInfo1[workNum][(CPublic::g_imagePara1[workNum].proNum - 1) % PRONUM1].y));
	AddString(_T("线程") + CPublic::int2CString(workNum) + _T("第") + CPublic::int2CString(CPublic::g_imagePara1[workNum].proNum) + _T("次图像处理结果A值：") + CPublic::double2CString(CPublic::g_imagePosInfo1[workNum][(CPublic::g_imagePara1[workNum].proNum - 1) % PRONUM1].a));
	m_progress.OffsetPos(1);//进度条
	//return res;
	/*
	if (*Continue == false)
		return 0;

	CString comm;
	int proNum;

	file->ReadString(comm);
	if (comm.Left(5) == _T("Count"))
	{
		int index = findChar(comm, '=', 1);
		if (index == -1)
		{
			AddString(_T("焊接柱图像识别中的Count行错误？"));
			return 0;
		}			
		proNum = _ttoi(comm.Mid(index));

	}else
		return 0;
	//file->ReadString(m_fileComm);
	for (int i = 0; i < 13; i++)
	{		
		file->ReadString(comm);
		if (comm.Left(12) == _T("IterationNum"))
		{
			int index = findChar(comm, '=', 1);
			if (index == -1)
			{
				AddString(_T("焊接柱图像识别中的IterationNum行错误？"));
				return 0;
			}	
			CPublic::g_imagePara2[workNum].iterationNum = _ttoi(comm.Mid(index));
		}	
		else if (comm.Left(5) == _T("ROI_x"))
		{
			int index = findChar(comm, '=', 1);
			if (index == -1)
			{
				AddString(_T("焊接柱图像识别中的ROI_x行错误？"));
				return 0;
			}		
			CPublic::g_imagePara2[workNum].ROI_x = _ttoi(comm.Mid(index));
		}
		else if (comm.Left(5) == _T("ROI_y"))
		{
			int index = findChar(comm, '=', 1);
			if (index == -1)
			{
				AddString(_T("焊接柱图像识别中的ROI_y行错误？"));
				return 0;
			}		
			CPublic::g_imagePara2[workNum].ROI_y = _ttoi(comm.Mid(index));
		}
		else if (comm.Left(5) == _T("ROI_w"))
		{
			int index = findChar(comm, '=', 1);
			if (index == -1)
			{
				AddString(_T("焊接柱图像识别中的ROI_w行错误？"));
				return 0;
			}	
			CPublic::g_imagePara2[workNum].ROI_w = _ttoi(comm.Mid(index));
		}
		else if (comm.Left(5) == _T("ROI_h"))
		{
			int index = findChar(comm, '=', 1);
			if (index == -1)
			{
				AddString(_T("焊接柱图像识别中的ROI_h行错误？"));
				return 0;
			}		
			CPublic::g_imagePara2[workNum].ROI_h = _ttoi(comm.Mid(index));
		}	
		else if (comm.Left(13) == _T("ThresholdFlag"))
		{
			int index = findChar(comm, '=', 1);
			if (index == -1)
			{
				AddString(_T("焊接柱图像识别中的ThresholdFlag行错误？"));
				return 0;
			}		
			CPublic::g_imagePara2[workNum].ThresholdFlag = _ttoi(comm.Mid(index));
		}
		else if (comm.Left(14) == _T("ThresholdValue"))
		{
			int index = findChar(comm, '=', 1);
			if (index == -1)
			{
				AddString(_T("焊接柱图像识别中的ThresholdValue行错误？"));
				return 0;
			}		
			CPublic::g_imagePara2[workNum].ThresholdValue = _ttoi(comm.Mid(index));
		}
		else if (comm.Left(16) == _T("FilterSmoothness"))
		{
			int index = findChar(comm, '=', 1);
			if (index == -1)
			{
				AddString(_T("焊接柱图像识别中的FilterSmoothness行错误？"));
				return 0;
			}		
			CPublic::g_imagePara2[workNum].FilterSmoothness = _wtof(comm.Mid(index));
		}
		else if (comm.Left(15) == _T("ExtractionScale"))
		{
			int index = findChar(comm, '=', 1);
			if (index == -1)
			{
				AddString(_T("焊接柱图像识别中的ExtractionScale行错误？"));
				return 0;
			}		
			CPublic::g_imagePara2[workNum].ExtractionScale = _wtof(comm.Mid(index));
		}
		else if (comm.Left(11) == _T("GapDistance"))
		{
			int index = findChar(comm, '=', 1);
			if (index == -1)
			{
				AddString(_T("焊接柱图像识别中的GapDistance行错误？"));
				return 0;
			}	
			CPublic::g_imagePara2[workNum].GapDistance = _wtof(comm.Mid(index));
		}
		else if (comm.Left(13) == _T("GapContinuity"))
		{
			int index = findChar(comm, '=', 1);
			if (index == -1)
			{
				AddString(_T("焊接柱图像识别中的GapContinuity行错误？"));
				return 0;
			}		
			CPublic::g_imagePara2[workNum].GapContinuity = _wtof(comm.Mid(index));
		}
		else if (comm.Left(16) == _T("CricleRadius_Low"))
		{
			int index = findChar(comm, '=', 1);
			if (index == -1)
			{
				AddString(_T("焊接柱图像识别中的CricleRadius_Low行错误？"));
				return 0;
			}		
			CPublic::g_imagePara2[workNum].CricleRadius_Low = _wtof(comm.Mid(index));
		}
		else if (comm.Left(17) == _T("CricleRadius_High"))
		{
			int index = findChar(comm, '=', 1);
			if (index == -1)
			{
				AddString(_T("焊接柱图像识别中的CricleRadius_High行错误？"));
				return 0;
			}		
			CPublic::g_imagePara2[workNum].CricleRadius_High = _wtof(comm.Mid(index));
		}else
		{
			AddString(_T("焊接柱图像识别中的无此命令行？"));
			return 0;
		}
	}
	m_progress[workNum].OffsetPos(1);//进度条

	CPublic::g_typeOfImagePro[workNum] = 1;
	DigUserHookData[workNum].workNum = workNum;
	return imageProcess(&DigUserHookData[workNum], &CPublic::g_imagePosInfo2[workNum][(proNum - 1) % PRONUM2], workNum);
	*/
	/*if (proNum  % 3 == 2)
		CPublic::angcalc(&CPublic::g_imagePosInfo1[workNum][0], &CPublic::g_imagePosInfo1[workNum][1], &CPublic::g_imagePosInfo1[workNum][1]);
	else if (proNum  % 3 == 0)
		CPublic::poscalc(&CPublic::g_imagePosInfo1[workNum][0], &CPublic::g_imagePosInfo1[workNum][2], &CPublic::g_imagePosInfo1[workNum][2]);*/
}

int CcontrolSerialNetPortDlg::OpenLight(int channelIndex,int intensity, int port)
{
	//0表示打开成功

	if (m_LightPortState == false)
	{
		CString strCOMName;
		strCOMName.Format(_T("COM%d"), port);  //光源的串口号
		USES_CONVERSION;
		if (OPTController_InitSerialPort(W2A(strCOMName.GetBuffer(0)), &m_OPTControllerHanlde) != OPT_SUCCEED)
		{
			AddString(_T("打开光源串口失败？"));
			return 0;
		}

		m_LightPortState = true;
		m_portNum[3] = port;

	}
	
	if (m_LightChannelState[channelIndex] == false)
	{
		if (OPTController_TurnOnChannel(m_OPTControllerHanlde, channelIndex) != OPT_SUCCEED)
		{
			AddString(_T("打开光源通道失败？"));
			return 0;
		}

		m_LightChannelState[channelIndex] = true;		
	}

	//intensity = 255;    //设置光源亮度
	if (OPT_SUCCEED != OPTController_SetIntensity(m_OPTControllerHanlde, channelIndex, intensity))
	{
		AddString(_T("设置光源亮度失败？"));
		return 0;
	}
	else
		return 1;
}

int CcontrolSerialNetPortDlg::explainLight(CStdioFile* file, int workNum, bool* Continue)//----------------------------（1.2.1.6）光源解析函数
{
	if (*Continue == false)
		return 0;

	CString comm[3];
	CString MiddleComm;
	int channel, intensity, port;

	for (int i = 0; i < 3; i++)//解析3个参数，判断三次
	{
		//file->ReadString(comm[i]);
		comm[i] = ChineseTransformation(MiddleComm, file);
	}

	channel = _ttoi(explainParameter(_T("Channel"), comm[0]));
	intensity = _ttoi(explainParameter(_T("Intensity"), comm[1]));
	port = _ttoi(explainParameter(_T("Port"), comm[2]));
	for (int j = 0; j < MAX_CAM + 1; j++)//判断和其他串口是不是重复
	{
		if (port == m_portNum[j])
		{		
			AddString(_T("光源串口与工位串口相同，请修改！"));			
			return 0;
		}
    }
	//if (comm[0].Left(7) == _T("\r\nChannel"))
	//{
	//	int index = findChar(comm[0], '=', 1);
	//	if (index == -1)
	//	{
	//		AddString(_T("脚本光源调节指令的Channel行错误？"));
	//		return 0;	
	//	}
	//	channel = _ttoi(comm[0].Mid(index));
	//}	

	//if (comm[1].Left(9) == _T("\r\nIntensity"))
	//{
	//	int index = findChar(comm[1], '=', 1);
	//	if (index == -1)
	//	{
	//		AddString(_T("脚本光源调节指令的Intensity行错误？"));
	//		return 0;		
	//	}
	//	intensity = _ttoi(comm[1].Mid(index));
	//}	

	//if (comm[2].Left(4) == _T("\r\nPort"))
	//{
	//	int index = findChar(comm[2], '=', 1);
	//	if (index == -1)
	//	{
	//		AddString(_T("脚本光源调节指令的Port行错误？"));
	//		return 0;		
	//	}		
	//	port = _ttoi(comm[2].Mid(index));
	//	for (int j = 0; j < MAX_CAM+1; j++)//判断和其他串口是不是重复
	//	{
	//		if (port == m_portNum[j])
	//		{
	//			AddString(_T("光源串口与工位串口相同，请修改！"));
	//			return 0;
	//		}
	//	}
 //	}	
	//}

	m_progress.OffsetPos(1);

	critical_section.Lock();
	int res =  OpenLight(channel, intensity, port);
	critical_section.Unlock();
	return res;
}

int CcontrolSerialNetPortDlg::explainSwitchInquiry(CStdioFile* file, int workNum, int portIndex, bool* Continue)
{
	CString comm;
	int num = 0;
	CString MiddleComm;
	comm = ChineseTransformation(MiddleComm, file);
	int index = findChar(comm, '=', 1);
	if (index == -1)
	{
		AddString(_T("脚本切换查询的命令数行错误？"));
		return 0;		
	}		
	num = _ttoi(comm.Mid(index));

	CString* strComm = new CString[num];
	int* value = new int[num];

	int i = 0, j = 0;
	while ( (i < num) || (j < num))
	{
		comm = ChineseTransformation(MiddleComm, file);
		if (comm.Left(4) == _T("\r\nComm"))
		{
			if (i == num)
			{
				delete[] strComm; 
				delete[] value; 
				AddString(_T("脚本切换查询的命令行超出命令数？"));
				return 0;	
			}	

			int index = findChar(comm, '=', 1);
			if (index == -1)
			{
				delete[] strComm; 
				delete[] value; 
				AddString(_T("脚本切换查询的命令行错误？"));
				return 0;	
			}		
			strComm[i] = comm.Mid(index);
			i++;
		}
		else if (comm.Left(5) == _T("\r\nValue"))
		{
			if (j == num)
			{
				delete[] strComm; 
				delete[] value;
				AddString(_T("脚本切换查询的阈值超出命令数？"));
				return 0;	
			}
			int index = findChar(comm, '=', 1);
			if (index == -1)
			{
				delete[] strComm; 
				delete[] value; 
				AddString(_T("脚本切换查询的阈值行错误？"));
				return 0;	
			}
			value[j] = _ttoi(comm.Mid(index));
			j++;

		}		
	}

	int res = switchInquiry(strComm, portIndex, value, num, Continue);
	delete[] strComm; 
	delete[] value; 
	m_progress.OffsetPos(1);

	return res;

}
int CcontrolSerialNetPortDlg::explainResultOfImagePro(CStdioFile* file, int workNum, int portIndex, bool* Continue)//--------------------（1.2.1.7）微调设备解析函数
{
	if (*Continue == false)
		return 0;
	CString comm;
	CString MiddleComm;
	comm = ChineseTransformation(MiddleComm, file);
	
	if (comm == L"\r\nTemplateMatching")
	{
		explainResultOfImagePro1(file, workNum, portIndex, Continue);//模板匹配微调设备
	}
	else if (comm == L"CricleDetection")
	{
		explainResultOfImagePro2(file, workNum, portIndex, Continue);//圆点匹配微调设备
	}

}
int CcontrolSerialNetPortDlg::explainResultOfImagePro1(CStdioFile* file, int workNum, int portIndex, bool* Continue)//--------------------（1.2.1.7）微调设备解析函数
{
	if (*Continue == false)
		return 0;
	CString comm[7];
	CString MiddleComm;
	int commNum;
	bool isAngel = false;
	PositionInfo resinfo;
	CString Command[4];
	int Value[2];
	CString value[2];

	//file->ReadString(m_fileComm);
	for (int i = 0; i < 7; i++)
	{
		comm[i] = ChineseTransformation(MiddleComm, file);

	}
	CString Algorithm = explainParameter(_T("模式识别微调设备的Algorithm"), comm[0]);//Mid从左边第 index+1个字符开始,获取后面所有的字符，也就是获取了等号后面的数字
	CString Result1 = explainParameter(_T("模式识别微调设备的Result1"), comm[1]);//Mid从左边第 index+1个字符开始,获取后面所有的字符，也就是获取了等号后面的数字
	int result1 = _ttoi(Result1);//字符转换成整形
	CString Result2 = explainParameter(_T("模式识别微调设备的Result2"), comm[2]);//Mid从左边第 index+1个字符开始,获取后面所有的字符，也就是获取了等号后面的数字
	int result2 = _ttoi(Result2);//字符转换成整形
	
	AddString(_T("工位") + CPublic::int2CString(workNum) + _T("Position1-X值：") + CPublic::double2CString(CPublic::g_imagePosInfo1[workNum][result1 - 1].x));
	AddString(_T("工位") + CPublic::int2CString(workNum) + _T("Position1-Y值：") + CPublic::double2CString(CPublic::g_imagePosInfo1[workNum][result1 - 1].y));
	AddString(_T("工位") + CPublic::int2CString(workNum) + _T("Position1-A值：") + CPublic::double2CString(CPublic::g_imagePosInfo1[workNum][result1 - 1].a));

	AddString(_T("工位") + CPublic::int2CString(workNum) + _T("Position2-X值：") + CPublic::double2CString(CPublic::g_imagePosInfo1[workNum][result2 - 1].x));
	AddString(_T("工位") + CPublic::int2CString(workNum) + _T("Position2-Y值：") + CPublic::double2CString(CPublic::g_imagePosInfo1[workNum][result2 - 1].y));
	AddString(_T("工位") + CPublic::int2CString(workNum) + _T("Position2-A值：") + CPublic::double2CString(CPublic::g_imagePosInfo1[workNum][result2 - 1].a));

	if (Algorithm == _T("Angcalc"))
	{
		isAngel = true;
		
		CPublic::angcalc(&(CPublic::g_imagePosInfo1[workNum][result1 - 1]), &(CPublic::g_imagePosInfo1[workNum][result2 - 1]), workNum, &resinfo);
		CString R_IP = explainParameter(_T("模式识别微调设备的R_IP"), comm[3]);
		//int Rbox = _ttoi(RBox);//字符转换成整形
		CString RPort = explainParameter(_T("模式识别微调设备的RPort"), comm[4]);
		int Rport = _ttoi(RPort);//字符转换成整形
		Value[0] = resinfo.a;
		if (Value[0] >= 180)
		{
			Value[0] = Value[0] - 360;
		}
		if (autoRelSMOV(Rport, R_IP, workNum, Value[0], Continue))
		{
			AddString(_T("工位") + CPublic::int2CString(workNum+1) + _T("R向伺服调整运动成功"));
		}
		else
		{
			AddString(_T("工位") + CPublic::int2CString(workNum+1) + _T("R向伺服调整运动失败"));
			return 0;
		}
		
		//value[0].Format(_T("%d"), Value[0]);
		//Command[0] = RBox + _T("->SMVR") + _T(" ") + RPort + _T(" ") + value[0];
		//Command[1] = RBox + _T("->MVR?") + _T(" ") + RPort;
		//for (int i = 0; i < 1; i++)
		//{
		//	if (sendAnySingleComm(Command[i], portIndex, Continue) == 0)
		//	{
		//		return 0;
		//	}
		//}
		//for (int i = 1; i < 2; i++)//查询指令
		//{
		//	if (sendAnySingleComm(Command[i], portIndex, Continue) == 0)
		//	{
		//		return 0;
		//	}
		//	int reValue = CPublic::explainIntPos(CPublic::receiveData[portIndex]);//接收到的数值
		//	if (abs(reValue - abs(Value[i])) < CPublic::stepsError)//abs求绝对值的函数
		//	{
		//		return 1;
		//	}
		//}
		m_progress.OffsetPos(1);
	}

	else if (Algorithm == _T("Poscalc"))
	{
		isAngel = false;

		CPublic::poscalc(&(CPublic::g_imagePosInfo1[workNum][result1 - 1]), &(CPublic::g_imagePosInfo1[workNum][result2 - 1]), workNum, &resinfo);
		CString X_IP = explainParameter(_T("模式识别微调设备的X_IP"), comm[3]);
		int Xbox = _ttoi(X_IP);//字符转换成整形
		CString XPort = explainParameter(_T("模式识别微调设备的XPort"), comm[4]);
		int Xport = _ttoi(XPort);//字符转换成整形
		CString Y_IP = explainParameter(_T("模式识别微调设备的Y_IP"), comm[5]);
		int Ybox = _ttoi(Y_IP);//字符转换成整形
		CString YPort = explainParameter(_T("模式识别微调设备的YPort"), comm[6]);
		int Yport = _ttoi(YPort);//字符转换成整形
		Value[0] = resinfo.x;
		Value[1] = resinfo.y;
		if (autoRelSMOV(Xport, X_IP, workNum, Value[0], Continue)&& autoRelSMOV(Yport, Y_IP, workNum, Value[1], Continue))
		{
			AddString(_T("工位") + CPublic::int2CString(workNum+1) + _T("XY向伺服调整运动成功"));
		}
		else
		{
			AddString(_T("工位") + CPublic::int2CString(workNum+1) + _T("XY向伺服调整运动失败"));
			return 0;
		}
		//value[0].Format(_T("%d"), Value[0]);
		//value[1].Format(_T("%d"), Value[1]);
		//Command[0] = XBox + _T("->SMVR") + _T(" ") + XPort + _T(" ") + value[0];
		//Command[1] = YBox + _T("->SMVR") + _T(" ") + YPort + _T(" ") + value[1];
		//Command[2] = XBox + _T("->MVR?") + _T(" ") + XPort;
		//Command[3] = XBox + _T("->MVR?") + _T(" ") + YPort;

		//for (int i = 0; i < 2; i++)//轴动指令
		//{
		//	if (sendAnySingleComm(Command[i], portIndex, Continue) == 0)
		//	{
		//		return 0;
		//	}
		//}
		//for (int i = 2; i < 4; i++)//查询指令
		//{
		//	if (sendAnySingleComm(Command[i], portIndex, Continue) == 0)
		//	{
		//		return 0;
		//	}
		//	int reValue = CPublic::explainIntPos(CPublic::receiveData[portIndex]);//接收到的数值
		//	if (abs(reValue - abs(Value[i])) < CPublic::stepsError)//abs求绝对值的函数
		//	{
		//		return 1;
		//	}
		//}
		m_progress.OffsetPos(1);
	}

	/*
	for (int i = 1; i < 7; i++)
	{
		file->ReadString(comm);

		int index = findChar(comm, '=', 1);

		if (index == -1)
		{
			AddString(_T("脚本调用图像处理结果调整设备的位置、算法或命令数行错误？"));
			return 0;	
		}

		if (comm.Left(9) == _T("Position1"))
		{
			index1 = _ttoi(comm.Mid(index));

		}
		else if  (comm.Left(9) == _T("Position2"))
		{
			index2 = _ttoi(comm.Mid(index));
		}
		else if  (comm.Left(9) == _T("Algorithm"))
		{
			if (comm.Mid(index) == _T("angcalc"))
			{
				isAngel = true;
			}else if (comm.Mid(index) == _T("poscalc"))
			{
				isAngel = false;
			}
		}
		else if (comm.Left(12) == _T("NumberOfComm"))
		{
			commNum = _ttoi(comm.Mid(index));
			if (commNum % 2 != 0)
			{
				AddString(_T("脚本调用图像处理结果调整设备的命令数为奇数？"));
				return 0;
			}
		}else
		{
			AddString(_T("脚本调用图像处理结果调整设备的无此命令行？"));
			return 0;
		}
	}
	AddString(_T("工位") + CPublic::int2CString(workNum) + _T("Position1-X值：") + CPublic::double2CString(CPublic::g_imagePosInfo1[workNum][index1 - 1].x));
	AddString(_T("工位") + CPublic::int2CString(workNum) + _T("Position1-Y值：") +  CPublic::double2CString(CPublic::g_imagePosInfo1[workNum][index1 - 1].y));
	AddString(_T("工位") + CPublic::int2CString(workNum) + _T("Position1-A值：") + CPublic::double2CString(CPublic::g_imagePosInfo1[workNum][index1 - 1].a));
	AddString(_T("工位") + CPublic::int2CString(workNum) + _T("Position2-X值：") + CPublic::double2CString(CPublic::g_imagePosInfo1[workNum][index2 - 1].x));
	AddString(_T("工位") + CPublic::int2CString(workNum) + _T("Position2-Y值：") +  CPublic::double2CString(CPublic::g_imagePosInfo1[workNum][index2 - 1].y));
	AddString(_T("工位") + CPublic::int2CString(workNum) + _T("Position2-A值：") + CPublic::double2CString(CPublic::g_imagePosInfo1[workNum][index2 - 1].a));
	if (isAngel == true)
		CPublic::angcalc(&(CPublic::g_imagePosInfo1[workNum][index1 - 1]), &(CPublic::g_imagePosInfo1[workNum][index2 - 1]), workNum, &resinfo);
	else
		CPublic::poscalc(&(CPublic::g_imagePosInfo1[workNum][index1 - 1]), &(CPublic::g_imagePosInfo1[workNum][index2 - 1]), workNum, &resinfo);
	int len = commNum / 2;
	CString* commands = new CString[len];
	int* value= new int[len];
	for (int i = 0; i < len; i++)
	{	
		file->ReadString(comm);
		int index = findChar(comm, '=', 1);
		if (index == -1)
		{
			delete[] commands;
			delete[] value;
			AddString(_T("脚本调用图像处理结果调整设备的位移命令行错误？"));
			return 0;	
		}
		
		if (comm.Left(4) == _T("Comm"))
			commands[i] = comm.Mid(index);

		if (commands[i].Right(1) == _T("x") || commands[i].Right(1) == _T("X"))
			value[i] = resinfo.x;
		else if (commands[i].Right(1) == _T("y") || commands[i].Right(1) == _T("Y"))
			value[i] = resinfo.y;
		else if (commands[i].Right(1) == _T("a") || commands[i].Right(1) == _T("A"))
			value[i] = resinfo.a;	
		else
		{
			delete[] commands;
			delete[] value;
			AddString(_T("脚本调用图像处理结果调整设备的查询命令行中的x,y或a错误？"));
			return 0;
		}
		if (sendAnySingleComm(commands[i].Left(commands[i].GetLength() - 1) + CPublic::int2CString(value[i]), portIndex, Continue) == 0)
		{
			delete[] commands;
			delete[] value;
			return 0;
		}
	}
	for (int i = 0; i < len; i++)
	{	
		file->ReadString(comm);
		int index = findChar(comm, '=', 1);
		if (index == -1)
		{
			delete[] commands;
			delete[] value;
			AddString(_T("脚本调用图像处理结果调整设备的查询命令行错误？"));
			return 0;	
		}
		if (comm.Left(4) == _T("Comm"))
			commands[i] = comm.Mid(index);
	}
	int res = switchInquiry(commands, portIndex, value, len, Continue);
	delete[] commands;
	delete[] value;
	m_progress[workNum].OffsetPos(1); 
	return res;
	*/
}

int CcontrolSerialNetPortDlg::autoRelSMOV(int axisNum, CString IP, int workNum, int relPos, bool* isContinue)
{
	CString strAxisNum = CPublic::int2CString(axisNum);
	//int absPos = 186230; //must setting
	CString relpos = CPublic::int2CString(relPos);

	CString axisnum;
	if (axisNum==1)
	{
		axisnum = _T("X");
	}
	if (axisNum == 2)
	{
		axisnum = _T("Y");
	}
	if (axisNum == 3)
	{
		axisnum = _T("Z");
	}
	if (axisNum == 4)
	{
		axisnum = _T("A");
	}
	if (axisNum == 5)
	{
		axisnum = _T("B");
	}
	if (axisNum == 6)
	{
		axisnum = _T("C");
	}
	//发送轴控指令，根据视觉处理结果进行相对运动
	//sendSingleComm(_T("SMVR ") + strAxisNum + _T(" ") + CPublic::int2CString(relPos), port);
	//Command[0] = _T("SVL ") + AxisNum[0] + value[0];//生成完整的指令，待发送到相应的控制器
	//if (io->sendComm(DevIP, Command[0]) == -1)

	//实时查询，直至运动至调整结果再退出
	//do
	//{
	//	//sendComm(_T("MVR? ") + strAxisNum, port);
	//	io->sendComm(IP, _T("IN? ") + strAxisNum + _T(" ") + CPublic::int2CString(relPos));
	//} while (abs(CPublic::explainIntPos(CPublic::receiveData[port - 1]) - abs(relPos)) > CPublic::stepsError && *isContinue == true);

	//Command[0] = _T("IN?");//生成完整的指令，待发送到相应的控制器
	int AxisBitValues[6] = {};
	int Value= relPos;
	if (io->inquiryAxisPOS(IP, _T("IN? "), AxisBitValues) == false)
	{
		AddString(_T("线程") + CPublic::int2CString(workNum + 1) + _T("伺服调整发送RelativePosition查询指令“") + _T("IN? ") + _T("”失败？"));
		return 0;
	}

	//查询并计算新的绝对位置坐标
	CString inquiryresultvalue[6];
	for (int i = 0; i < 6; i++)
	{
		inquiryresultvalue[i].Format(_T("%d"), AxisBitValues[i]);
	}
	int absvalue = AxisBitValues[axisNum - 1] + Value;
	
	//执行运动
	CString commr;
	commr = _T("MOD ") + axisnum + _T("0");//改为相对运动模式
	io->sendComm(IP, commr);
	CString commrr;
	commrr = _T("MOV ") + axisnum + relpos;
	io->sendComm(IP, commrr);


	//判断是否达到了位置点
	while (1) //需要设置定时器
	{
		CString aaa;
		aaa.Format(_T("%d"), AxisBitValues[axisNum - 1]);
		// AddString(_T("线程") + CPublic::int2CString(workNum + 1) + _T("查询值为：“") + aaa+ _T("”"));
		AddString(_T("线程") + CPublic::int2CString(workNum + 1) + _T("查询值为：“") + aaa + _T("”"));
		io->inquiryAxisPOS(IP, _T("IN? "), AxisBitValues);
		// CString inquiryresultvalue[6];
		for (int i = 0; i < 6; i++)
		{
			inquiryresultvalue[i].Format(_T("%d"), AxisBitValues[i]);
		}
		AddString(_T("---------线程") + CPublic::int2CString(workNum + 1) + _T("查询值为：“") + inquiryresultvalue[2] + _T("”"));
		if (AxisBitValues[axisNum - 1] == absvalue)
		{
			int res = 1;
			break;
		}

		else continue;
	}

	commr = _T("MOD ") + axisnum + _T("1");//改回绝对运动模式
	io->sendComm(IP, commr);

	return 1;
}




int CcontrolSerialNetPortDlg::getPosition(CStdioFile* file, int workNum,CString comm,PositionInfo* value)
{
	int index = findChar(comm, '=', 1);
	if (index == -1)
	{
		return -1;	
	}

	CString str = _T("Result");
	if (comm.Left(str.GetLength()) != str)
	{
		//AddString(_T("图像处理的Position错误？"));上一层函数输出
		return -1;
	}
	else
	{
		int i = _ttoi(comm.Right(1)) - 1;

		if (comm.Mid(index, 6) == _T("Preset"))//之前设置的
		{
			
			value->x = CPublic::g_newinitParameter[workNum].posX[i];
			value->y = CPublic::g_newinitParameter[workNum].posY[i];
			value->a = CPublic::g_newinitParameter[workNum].posA[i];
		}else//调用图像处理结果
		{
			value->x = CPublic::g_imagePosInfo2[workNum][i].x;
			value->y = CPublic::g_imagePosInfo2[workNum][i].y;
			value->a = CPublic::g_imagePosInfo2[workNum][i].a;
		}
		return i+1;
	}

}

int CcontrolSerialNetPortDlg::explainResultOfImagePro2(CStdioFile* file, int workNum, int portIndex, bool* Continue)
{
	if (*Continue == false)
		return 0;
	CString comm[7];
	CString MiddleComm;
	int commNum;
	bool isAngel = false;
	PositionInfo resinfo;
	PositionInfo info1, info2;
	CString Command[4];
	int Value[2];
	CString value[2];

	//file->ReadString(m_fileComm);
	for (int i = 1; i < 7; i++)
	{
		comm[i] = ChineseTransformation(MiddleComm, file);
	}
	CString Algorithm = explainParameter(_T("点搜索微调设备的Algorithm"), comm[1]);
	//读取位置1
	if (getPosition(file, workNum,comm[2], &info1) == -1)
	{
		AddString(_T("用于点搜索微调设备的图像处理Result1错误？"));
		return 0;
	}

	AddString(_T("线程") + CPublic::int2CString(workNum) + _T("Result1-X值：") + CPublic::double2CString(info1.x));
	AddString(_T("线程") + CPublic::int2CString(workNum) + _T("Result1-Y值：") + CPublic::double2CString(info1.y));
	AddString(_T("线程") + CPublic::int2CString(workNum) + _T("Result1-A值：") + CPublic::double2CString(info1.a));

	//读取位置2
	if (getPosition(file, workNum, comm[3], &info2) == -1)
	{
		AddString(_T("用于点搜素微调设备的图像处理的Result2错误？"));
		return 0;
	}

	AddString(_T("线程") + CPublic::int2CString(workNum) + _T("Result2-X值：") + CPublic::double2CString(info2.x));
	AddString(_T("线程") + CPublic::int2CString(workNum) + _T("Result2-Y值：") + CPublic::double2CString(info2.y));
	AddString(_T("线程") + CPublic::int2CString(workNum) + _T("Result2-A值：") + CPublic::double2CString(info2.a));

	//Mid从左边第 index+1个字符开始,获取后面所有的字符，也就是获取了等号后面的数字
	//CString Result1 = explainParameter(_T("点匹配微调设备的Result1"), comm[2]);//Mid从左边第 index+1个字符开始,获取后面所有的字符，也就是获取了等号后面的数字
	//int result1 = _ttoi(Result1);//字符转换成整形
	//CString Result2 = explainParameter(_T("点匹配微调设备的Result2"), comm[3]);//Mid从左边第 index+1个字符开始,获取后面所有的字符，也就是获取了等号后面的数字
	//int result2 = _ttoi(Result2);//字符转换成整形

	//AddString(_T("工位") + CPublic::int2CString(workNum) + _T("Position1-X值：") + CPublic::double2CString(CPublic::g_imagePosInfo1[workNum][result1 - 1].x));
	//AddString(_T("工位") + CPublic::int2CString(workNum) + _T("Position1-Y值：") + CPublic::double2CString(CPublic::g_imagePosInfo1[workNum][result1 - 1].y));
	//AddString(_T("工位") + CPublic::int2CString(workNum) + _T("Position1-A值：") + CPublic::double2CString(CPublic::g_imagePosInfo1[workNum][result1 - 1].a));

	//AddString(_T("工位") + CPublic::int2CString(workNum) + _T("Position2-X值：") + CPublic::double2CString(CPublic::g_imagePosInfo1[workNum][result2 - 1].x));
	//AddString(_T("工位") + CPublic::int2CString(workNum) + _T("Position2-Y值：") + CPublic::double2CString(CPublic::g_imagePosInfo1[workNum][result2 - 1].y));
	//AddString(_T("工位") + CPublic::int2CString(workNum) + _T("Position2-A值：") + CPublic::double2CString(CPublic::g_imagePosInfo1[workNum][result2 - 1].a));

	if (Algorithm == _T("Angcalc"))
	{
		isAngel = true;
		CPublic::angcalc(&info1, &info2, workNum, &resinfo);
		//CPublic::angcalc(&(CPublic::g_imagePosInfo1[workNum][result1 - 1]), &(CPublic::g_imagePosInfo1[workNum][result2 - 1]), workNum, &resinfo);

		CString RBox = explainParameter(_T("点搜索微调设备的RBox"), comm[4]);
		int Rbox = _ttoi(RBox);//字符转换成整形
		CString RPort = explainParameter(_T("点搜索微调设备的RPort"), comm[5]);
		int Rport = _ttoi(RPort);//字符转换成整形
		Value[0] = resinfo.a;
		value[0].Format(_T("%d"), Value[0]);
		Command[0] = RBox + _T("->SMVR") + _T(" ") + RPort + _T(" ") + value[0];
		Command[1] = RBox + _T("->MVR?") + _T(" ") + RPort;
		for (int i = 0; i < 1; i++)
		{
			if (sendAnySingleComm(Command[i], portIndex, Continue) == 0)
			{
				return 0;
			}
		}
		for (int i = 1; i < 2; i++)//查询指令
		{
			if (sendAnySingleComm(Command[i], portIndex, Continue) == 0)
			{
				return 0;
			}
			int reValue = CPublic::explainIntPos(CPublic::receiveData[portIndex]);//接收到的数值
			if (abs(reValue - abs(Value[i])) < CPublic::stepsError)//abs求绝对值的函数
			{
				return 1;
			}
		}
		m_progress.OffsetPos(1);
	}

	else if (Algorithm == _T("Poscalc"))
	{
		isAngel = false;
		CPublic::poscalc(&info1, &info2, workNum, &resinfo);
		//CPublic::poscalc(&(CPublic::g_imagePosInfo1[workNum][result1 - 1]), &(CPublic::g_imagePosInfo1[workNum][result2 - 1]), workNum, &resinfo);

		CString XBox = explainParameter(_T("模式识别微调设备的XBox"), comm[4]);
		int Xbox = _ttoi(XBox);//字符转换成整形
		CString XPort = explainParameter(_T("模式识别微调设备的XPort"), comm[5]);
		int Xport = _ttoi(XPort);//字符转换成整形
		CString YBox = explainParameter(_T("模式识别微调设备的YBox"), comm[4]);
		int Ybox = _ttoi(YBox);//字符转换成整形
		CString YPort = explainParameter(_T("模式识别微调设备的YPort"), comm[5]);
		int Yport = _ttoi(YPort);//字符转换成整形
		Value[0] = resinfo.x;
		Value[1] = resinfo.y;
		value[0].Format(_T("%d"), Value[0]);
		value[1].Format(_T("%d"), Value[1]);
		Command[0] = XBox + _T("->SMVR") + _T(" ") + XPort + _T(" ") + value[0];
		Command[1] = YBox + _T("->SMVR") + _T(" ") + YPort + _T(" ") + value[1];
		Command[2] = XBox + _T("->MVR?") + _T(" ") + XPort;
		Command[3] = XBox + _T("->MVR?") + _T(" ") + XPort;

		for (int i = 0; i < 2; i++)//轴动指令
		{
			if (sendAnySingleComm(Command[i], portIndex, Continue) == 0)
			{
				return 0;
			}
		}
		for (int i = 2; i < 4; i++)//查询指令
		{
			if (sendAnySingleComm(Command[i], portIndex, Continue) == 0)
			{
				return 0;
			}
			int reValue = CPublic::explainIntPos(CPublic::receiveData[portIndex]);//接收到的数值
			if (abs(reValue - abs(Value[i])) < CPublic::stepsError)//abs求绝对值的函数
			{
				return 1;
			}
		}
		m_progress.OffsetPos(1);
	}
	/*
	if (*Continue == false)
		return 0;

	CString comm;
	int type, commNum;
	bool isAngel = false;
	PositionInfo resinfo;


	//读取type
	file->ReadString(comm);
	int index = findChar(comm, '=', 1);
	if (index == -1)
	{
		AddString(_T("脚本调用图像处理结果type错误？"));
		return 0;	
	}

	if (comm.Left(4) == _T("Type"))
		type = _ttoi(comm.Mid(index));

	if (type == 1)
	{
		//读取位置
		if (getPosition(file, workNum, &resinfo) == -1)
		{
			AddString(_T("图像处理的Position1错误？"));
			return 0;
		}
		AddString(_T("工位") + CPublic::int2CString(workNum) + _T("Position1-X值：") + CPublic::double2CString(resinfo.x));
		AddString(_T("工位") + CPublic::int2CString(workNum) + _T("Position1-Y值：") +  CPublic::double2CString(resinfo.y));
		AddString(_T("工位") + CPublic::int2CString(workNum) + _T("Position1-A值：") + CPublic::double2CString(resinfo.a));

	}else//type=2
	{
		PositionInfo info1, info2;
		//读取位置1
		if (getPosition(file, workNum, &info1) == -1)
		{
			AddString(_T("图像处理的Position1错误？"));
			return 0;
		}

		AddString(_T("工位") + CPublic::int2CString(workNum) + _T("Position1-X值：") + CPublic::double2CString(info1.x));
		AddString(_T("工位") + CPublic::int2CString(workNum) + _T("Position1-Y值：") +  CPublic::double2CString(info1.y));
		AddString(_T("工位") + CPublic::int2CString(workNum) + _T("Position1-A值：") + CPublic::double2CString(info1.a));

		//读取位置2
		if (getPosition(file, workNum, &info2) == -1)
		{
			AddString(_T("图像处理的Position2错误？"));
			return 0;
		}

		AddString(_T("工位") + CPublic::int2CString(workNum) + _T("Position2-X值：") + CPublic::double2CString(info2.x));
		AddString(_T("工位") + CPublic::int2CString(workNum) + _T("Position2-Y值：") +  CPublic::double2CString(info2.y));
		AddString(_T("工位") + CPublic::int2CString(workNum) + _T("Position2-A值：") + CPublic::double2CString(info2.a));


		//读取算法
		file->ReadString(comm);
		index = findChar(comm, '=', 1);
		if (index == -1)
		{
			AddString(_T("图像处理的算法错误？"));
			return 0;	
		}

		if  (comm.Left(9) == _T("Algorithm"))
		{
			if (comm.Mid(index) == _T("angcalc"))
			{
				isAngel = true;
			}else if (comm.Mid(index) == _T("poscalc"))
			{
				isAngel = false;
			}
		}

		if (isAngel == true)
			CPublic::angcalc(&info1, &info2, workNum, &resinfo);
		else
			CPublic::poscalc(&info1, &info2, workNum, &resinfo);

	}

	//读取命令数
	file->ReadString(comm);
	index = findChar(comm, '=', 1);
	if (index == -1)
	{
		AddString(_T("脚本调用图像处理结果调整设备的命令数行错误？"));
		return 0;	
	}
	if (comm.Left(12) == _T("NumberOfComm"))
	{
		commNum = _ttoi(comm.Mid(index));
		if (commNum % 2 != 0)
		{
			AddString(_T("脚本调用图像处理结果调整设备的命令数为奇数？"));
			return 0;
		}
	}else
	{
		AddString(_T("脚本调用图像处理结果调整设备的无此命令行？"));
		return 0;
	}


	int len = commNum / 2;
	CString* commands = new CString[len];
	int* value= new int[len];
	for (int i = 0; i < len; i++)
	{	

		file->ReadString(comm);
		index = findChar(comm, '=', 1);
		if (index == -1)
		{
			delete[] commands;
			delete[] value;
			AddString(_T("脚本调用图像处理结果调整设备的位移命令行错误？"));
			return 0;	
		}

		if (comm.Left(4) == _T("Comm"))
			commands[i] = comm.Mid(index);

		if (commands[i].Right(1) == _T("x") || commands[i].Right(1) == _T("X"))
			value[i] = resinfo.x;
		else if (commands[i].Right(1) == _T("y") || commands[i].Right(1) == _T("Y"))
			value[i] = resinfo.y;
		else if (commands[i].Right(1) == _T("a") || commands[i].Right(1) == _T("A"))
			value[i] = resinfo.a;	
		else
		{
			delete[] commands;
			delete[] value;
			AddString(_T("脚本调用图像处理结果调整设备的查询命令行中的x,y或a错误？"));
			return 0;
		}

		if (sendAnySingleComm(commands[i].Left(commands[i].GetLength() - 1) + CPublic::int2CString(value[i]), portIndex, Continue) == 0)
		{
			delete[] commands;
			delete[] value;
			return 0;
		}

	}

	for (int i = 0; i < len; i++)
	{	

		file->ReadString(comm);
		index = findChar(comm, '=', 1);
		if (index == -1)
		{
			delete[] commands;
			delete[] value;
			AddString(_T("脚本调用图像处理结果调整设备的查询命令行错误？"));
			return 0;	
		}

		if (comm.Left(4) == _T("Comm"))
			commands[i] = comm.Mid(index);
	}

	int res = switchInquiry(commands, portIndex, value, len, Continue);
	delete[] commands;
	delete[] value;

	m_progress[workNum].OffsetPos(1); 
	return res;
	*/
}


int CcontrolSerialNetPortDlg::explainGoldBallBonding(CStdioFile* file, int workNum, int portIndex, bool* Continue)//金丝球焊
{
	if (*Continue == false)
		return 0;

	CString comm = _T("");
	int commNum = 0;
	int count = 0;
	CString MiddleComm;
	comm = ChineseTransformation(MiddleComm, file);
	
	if (comm.Left(12) == _T("\r\nNumberOfComm"))
	{
		int index = findChar(comm, '=', 1);
		if (index == -1)
		{
			AddString(_T("脚本金丝球焊接中的NumberOfComm错误？"));
			return 0;
		}			
		commNum = _ttoi(comm.Mid(index));
	}else
	{
		AddString(_T("脚本金丝球焊接中的NumberOfComm错误？"));
		return 0;
	}

	for (int i = 0; i < commNum; i++)
	{	
		comm = ChineseTransformation(MiddleComm, file);

		if (comm == _T(""))
		{
			AddString(_T("脚本金丝球焊接中的NumberOfComm错误？"));
			return 0;
		}

		count = 0;
		do
		{
			if (*Continue == false)
				return 0;

			sendGoldComm(comm, portIndex);
			count++;
			Sleep(3000);
			if (count == 10)
			{
				AddString(_T("发送金丝球焊接指令无返回数据？？"));
				return 0;
			}

		}while ((CPublic::bfindTerminator[portIndex] != true));
	}


	m_progress.OffsetPos(1); 
	return 1;
}

void CcontrolSerialNetPortDlg::initPort(void)//
{
	//显示串口设置
	CString temp;
	for(int i = 1; i<= MaxSerialPortNum-1; i++)
	{
		if(serialPort[0].InitPort(this, i, 115200))
		{
			temp.Format(_T("COM %d"), i);		
			m_cmbPort[0].AddString((LPCTSTR)temp);
			m_cmbPort[1].AddString((LPCTSTR)temp);
			m_cmbPort[2].AddString((LPCTSTR)temp);
		}
	}

	if(m_cmbPort[0].GetCount())
	{
		serialPort[0].InitPort(this,MaxSerialPortNum);
		serialPort[1].InitPort(this,MaxSerialPortNum);
		serialPort[2].InitPort(this,MaxSerialPortNum);
		m_cmbPort[0].SetCurSel(8);//设置默认端口
		m_cmbPort[1].SetCurSel(7);
		m_cmbPort[2].SetCurSel(1);
	}else
	{
		//MessageBox(_T("无可连接的串口！"));
	}
}





//void CcontrolSerialNetPortDlg::OnCbnSelchangeComboPort1()
//{
//	
//}

//void CcontrolSerialNetPortDlg::OnCbnSelchangeComboPort2()
//{
//	CString temp;
//	// TODO: Add your control notification handler code here
//	if( m_cmbPort[1].GetCount())
//	{	
//		m_cmbPort[1].GetLBText(m_cmbPort[0].GetCurSel(), temp);
//		temp.Delete(0,3);
//		m_workPortNum[1] = _ttoi(temp);
//	}
//}

//void CcontrolSerialNetPortDlg::OnBnClickedButton1()
//{
//	// TODO: Add your control notification handler code here
//}

void CcontrolSerialNetPortDlg::OnBnClickedButtonconnect()//串口连接按钮
{
	
	if (IOConnect() == false)//IO控制器连接是否成功
	{
		return;
	}

}

int CcontrolSerialNetPortDlg::findCoronNum(CStdioFile* file)//和下面的函数类似？参数不同             
{                                                             //功能是 返回冒号的个数
	int count = 0;

	while(!feof(file->m_pStream))//feof检查文档是否到末尾
	{
		if (findCoron(file).IsEmpty() == false)
		{
			count++;
		}
	}
	file->SeekToBegin();
	return count;

}

bool CcontrolSerialNetPortDlg::IOConnect()
{
	CString IPaddr;//连接时，是本地IP？
	CString Port;
	//m_IOIP.GetWindowText(IPaddr);
	m_localIP.GetWindowText(IPaddr);
	//IPaddr = _T("192.168.0.131");

	if (io == NULL)
	{
		io = new CIO();//？//实例化类
	}

	if (m_IOConnect == false)
	{
		if (!io->openPort(IPaddr, m_IOPort))          //连接成功返回1,否则返回0
		{
			AfxMessageBox(_T("打开IO网口失败！"));
			return false;
		}

		AddString(_T("IO网口已成功连接！"));
		//AddString(_T("已检测到关键装配位置：TH-JB, HZHK-TH, ZX-JB, GLB-ZX，该零件装配合格"));
		m_IOConnect = true;
		return true;
	}
	else
	{
		AfxMessageBox(_T("IO设处于连接状态，请先关闭！"));
		return false;
	}
}

bool CcontrolSerialNetPortDlg::findCoronNum(CStdioFile* file, int& num)
{
	num = 0;

	while(!feof(file->m_pStream))//检测流上的文件结束符的函数,
	{
		if (findCoron(file).IsEmpty() == false)//未发现冒号
		{
			num++;
		}
	}
	file->SeekToBegin();//将文件指针的值设置为文件的开头。
	if (num == 0)
	{
		return false;
	}else 
		return true;

}

int CcontrolSerialNetPortDlg::explainGoldComm(CString comm, char* byteComm)//金丝球焊机指令解析
{
	int len = 0;
	
	if (comm.Left(4) == _T("PING"))
	{
		byteComm[0] = PING;
		len = 4;
	}
	else if (comm.Left(10) == _T("BONDER_CFG"))
	{
		byteComm[0] = BONDER_CFG;
		len = 10;

	}
	else if (comm.Left(8) == _T("BUMP_PEG"))
	{
		byteComm[0] = BUMP_PEG;
		len = 8;

	}
	else if (comm.Left(10)  == _T("BALL_WEDGE"))
	{
		byteComm[0] = BALL_WEDGE;
		len = 10;
	}
	else if (comm.Left(8)  == _T("RUN_MODE"))
	{
		byteComm[0] = RUN_MODE;
		len = 8;

	}
	else if (comm.Left(15) == _T("FEAT_SETUP_MODE"))
	{
		byteComm[0] = FEAT_SETUP_MODE;
		len = 15;

	}
	else if (comm.Left(3) == _T("YES"))
	{
		byteComm[0] = YES;
		len = 3;
	}
	else if (comm.Left(2) == _T("NO"))
	{
		byteComm[0] = NO;
		len = 2;
	}
	else if (comm.Left(9) == _T("NO_STITCH"))
	{
		len = 9;
		byteComm[0] = NO_STITCH;
	}
	else if (comm.Left(11) == _T("AUTO_STITCH"))
	{
		len = 11;
		byteComm[0] = AUTO_STITCH;
	}
	else if (comm.Left(13) == _T("MANUAL_STITCH"))
	{
		len = 13;
		byteComm[0] = MANUAL_STITCH;
	}
	else if (comm.Left(9) == _T("AUTO_MODE"))
	{
		len = 9;
		byteComm[0] = AUTO_MODE;
	}
	else if (comm.Left(11) == _T("MANUAL_MODE"))
	{
		len = 11;
		byteComm[0] = MANUAL_MODE;
	}
	else if (comm.Left(12) == _T("BONDER_RESET"))
	{
		len = 12;
		byteComm[0] = BONDER_RESET;
	}
	else if (comm.Left(7) == _T("BOND_GO"))
	{
		len = 7;
		byteComm[0] = BOND_GO;
	}
	else if (comm.Left(7) == _T("MM_LOCK"))
	{
		len = 7;
		byteComm[0] = MM_LOCK;
	}
	else if (comm.Left(9) == _T("BOND_DONE"))
	{
		len = 9;
		byteComm[0] = BOND_DONE;
	}
	else if (comm.Left(15) == _T("BOND_CYCLE_DONE"))
	{
		len = 15;
		byteComm[0] = BOND_CYCLE_DONE;
	}
	else if (comm.Left(6) == _T("MOVE_Z"))
	{
		len = 6;
		byteComm[0] = MOVE_Z;
	}
	else if (comm.Left(9) == _T("MOVE_Z_UP"))
	{
		len = 9;
		byteComm[0] = MOVE_Z_UP;
	}
	else if (comm.Left(11) == _T("MOVE_Z_DOWN"))
	{
		byteComm[0] = MOVE_Z_DOWN;
		len = 11;
	}
	else if (comm.Left(11) == _T("MOVE_Z_FAST"))
	{
		len = 11;
		byteComm[0] = MOVE_Z_FAST;
	}
	else if (comm.Left(11) == _T("MOVE_Z_SLOW"))
	{
		len = 11;
		byteComm[0] = MOVE_Z_SLOW;
	}
	else
	{
		CPublic::CString2char(comm, byteComm);
		return comm.GetLength() + 1;

	}

	CPublic::CString2char(comm.Mid(len), byteComm + 1);
	return (comm.Mid(len)).GetLength() + 2;


}


void CcontrolSerialNetPortDlg::sendGoldComm(CString comm, int portIndex)
{
	if ( CPublic::portIsOpen[portIndex] == false)
	{
		AddString(_T("该串口未打开，请先打开串口！"));
		return;
	}

	int len = comm.GetLength();
	char* byteComm = new char[comm.GetLength() + 1];
	CPublic::CString2char(comm, byteComm);

	//int len = explainGoldComm(comm, byteComm);

	serialPort[portIndex].WriteToPort(byteComm, len);

	AddString(_T("金丝球COM") + CPublic::int2CString(m_portNum[portIndex]) + _T(" send: ") + comm);
	delete[] byteComm;

}

//////////////////建立网口连接////////////////////////////
int CcontrolSerialNetPortDlg::SocketConnection()
{
	// TODO: 在此添加控件通知处理程序代码
	struct addrinfo *result = NULL;	        //本函数通过result指针参数返回一个指向addrinfo结构体链表的指针。
	struct addrinfo hints;					//可以是一个空指针，也可以是一个指向某个addrinfo结构体的指针，调用者在这个结构中填入关于期望返回的信息类型的暗示。
	WSADATA wsaData;
	int Rst;


	Rst = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (Rst != 0) {
		CString str;
		str.Format(_T("WSAStartup failed with error: %d\n"), Rst);
		AddString(str);
		return 0;
	}

	ZeroMemory(&hints, sizeof(hints));					            //清零、填写过滤信息到hints中
	hints.ai_family = AF_INET;							            //AF_INET 用于指定 IPv4 地址族
	hints.ai_socktype = SOCK_STREAM;					            //SOCK_STREAM 用于指定流套接字
	hints.ai_protocol = IPPROTO_TCP;					            //用于指定 TCP 协议
	hints.ai_flags = AI_PASSIVE;						            //表明调用方打算使用 bind 函数调用中返回的套接字地址结构。
	Rst = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);	        //返回值：0成功，非0出错
	if (Rst != 0) {
		CString str;
		str.Format(_T("getaddrinfo failed with error: %d\n"), Rst);
		WSACleanup();
		AddString(str);
		return 0;
	}
	
	ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);//调用socket函数，并将其值返回到 ListenSocket变量中。
	if (ListenSocket == INVALID_SOCKET) {
		CString str;
		str.Format(_T("socket failed with error: %ld\n"), WSAGetLastError());
		freeaddrinfo(result);
		WSACleanup();
		return 0;
	}
	
	Rst = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);  //调用 bind 函数，服务端将socket与地址关联
	if (Rst == SOCKET_ERROR) {
		CString str;
		str.Format(_T("bind failed with error: %ld\n"), WSAGetLastError());
		freeaddrinfo(result);
		closesocket(ListenSocket);
		WSACleanup();
		return 0;
	}

	freeaddrinfo(result);	                                        //调用freeaddrinfo函数释放 getaddrinfo 函数为地址信息分配的内存。
	Rst = listen(ListenSocket, SOMAXCONN);                          //调用listen函数，服务端网络监听。
	if (Rst == SOCKET_ERROR) {
		CString str;
		str.Format(_T("listen failed with error: %d\n"), WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
		return 0;
	}

	
	ClientSocket = accept(ListenSocket, NULL, NULL);	            //创建一个临时的套接字对象称为ClientSocket变量接受来自客户端的连接。
	if (ClientSocket == INVALID_SOCKET) {
		CString str;
		str.Format(_T("accept failed with error: %d\n"), WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
		return 0;
	}
	
	m_SocketState = true;
	return 1;
}

void CcontrolSerialNetPortDlg::SocketShutdown()
{
	//WSACleanup();
	closesocket(ListenSocket);
	closesocket(ClientSocket);
	WSACleanup();
	m_SocketState = false;
}

/////////////服务器发送数据//////////////////
int CcontrolSerialNetPortDlg::SocketSendData(CString data, bool* Continue)
{
	if (*Continue == false)
	{
		return 0;
	}

	if (m_SocketState == false)
	{
		AddString(_T("与机器人无连接？"));
		return 0;
	}

	char charStr[10];
	CPublic::CString2char(data, charStr);
	
	if (send(ClientSocket, charStr, strlen(charStr), 0) == SOCKET_ERROR)
	{
		AddString(_T("发送机器人执行指令到socket失败？"));
		return 0;
	}else
		return 1;

}

/////////////////////////接收返回值/////////////////////////
//int CcontrolSerialNetPortDlg::SocketRecieveData(CString data, int count, bool* Continue)
//{
//	char r[20];
//	char s[] = "pose?";  //发送pose？查询动作是否完成
//	if (m_SocketState == false)
//	{
//		AddString(_T("与机器人无连接？"));
//		return 0;
//	}
//
//	if (send(ClientSocket, s, strlen(s), 0) == SOCKET_ERROR)
//	{
//		AddString(_T("发送查询指令到SOCKET失败？"));
//		return 0;
//	}
//	Sleep(100);
//
//	int i = 0;
//	CString str = data + _T("S");
//	CPublic::CString2char(str, s);
//	int res = 0;
//
//	int timeout = 100;
//	setsockopt(ClientSocket, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(timeout));
//
//
//	do
//	{
//		if (*Continue == false)
//			return 0;
//
//		i++;
//		res = recv(ClientSocket, r, 20, MSG_WAITALL);
//
//		if(res == SOCKET_ERROR)  
//		{ 
//			int r = WSAGetLastError();  
//			if (i == count)
//			{
//				AddString(CPublic::int2CString(count)+ _T("次")+CPublic::int2CString(100*count)+_T("ms接收机器人错误：") + CPublic::int2CString(r));
//
//			}
//
//			if(errno == EAGAIN || errno == WSAEWOULDBLOCK || errno == EINTR) //这几种错误码，认为连接是正常的，继续接收
//			{
//				continue;//继续接收数据
//			}			
//			else if(r == WSAENETDOWN)  
//			{  				
//				return 0;  
//			}  
//		}  
//		else if ( res > 0 )
//		{
//			if (memcmp(r, s, res) == 0)
//			{
//				return 1;
//			}else
//			{
//				AddString(_T("机器人返回的数据错误？"));
//				return 0;
//			}
//		}
//		else if ( res == 0 )
//		{
//			AddString(_T("机器人网络连接关闭？"));
//			return 0;
//		}
//
//	}while(i < count);
//
//	return 0;
//
//}

///////////////////////接收返回值/////////////////////////
int CcontrolSerialNetPortDlg::SocketRecieveData(CString data, int count, bool* Continue)
{
	char r[20];
	char s[] = "pose?";  //发送pose？查询动作是否完成
	if (m_SocketState == false)
	{
		AddString(_T("与机器人无连接？"));
		return 0;
	}

	if (send(ClientSocket, s, strlen(s), 0) == SOCKET_ERROR)
	{
		AddString(_T("发送查询指令到SOCKET失败？"));
		return 0;
	}
	Sleep(100);

	int i = 0;
	CString str = data + _T("S");
	CPublic::CString2char(str, s);
	int res = 0;

	/*int timeout = count;
	setsockopt(ClientSocket, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(timeout));*/


	if (*Continue == false)
		return 0;

	res = recv(ClientSocket, r, 20, MSG_WAITALL);

	if(res == SOCKET_ERROR)  
	{ 
		int r = WSAGetLastError();  
		AddString(_T("接收机器人错误：") + CPublic::int2CString(r));


		if(errno == EAGAIN || errno == WSAEWOULDBLOCK || errno == EINTR) //这几种错误码，认为连接是正常的，继续接收
		{
			return 1;
		}			
		else if(r == WSAENETDOWN)  
		{  				
			return 0;  
		}  
	}  
	else if ( res > 0 )
	{
		if (memcmp(r, s, res) == 0)
		{
			return 1;
		}else
		{
			AddString(_T("机器人返回的数据错误？"));
			return 0;
		}
	}
	else if ( res == 0 )
	{
		AddString(_T("机器人网络连接关闭？"));
		return 0;
	}
	return 0;

}

void CcontrolSerialNetPortDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	CIOControl mydlg;
	mydlg.DoModal();
}


void CcontrolSerialNetPortDlg::OnFaultAnalysis()
{
	// TODO: 在此添加命令处理程序代码
}


void CcontrolSerialNetPortDlg::OnCbnSelchangeComboPort1()
{
	// TODO: 在此添加控件通知处理程序代码
}
void CcontrolSerialNetPortDlg::OnBnClickedLogin()//登陆界面判断函数
{
	CDialoglogin login;//登陆对话框对象
	bool islogin = false;//判断登陆是否成功的布尔变量
	while (!islogin)
	{
		int nlogin;
		nlogin = login.DoModal();//模态对话框
		if (nlogin == IDC_BUTTON1)
		{
			CString str_User = login.m_name;
			CString str_Password = login.m_password;
			if (str_User == "MMT" && str_Password == "123") //判断用户名和密码是否正确
			{
				islogin = true;
			}
			else
			{
				MessageBox(_T("账号密码有误，请重新输入！"), _T("温馨提示："), MB_OK | MB_ICONINFORMATION);
			}
		}
		else if (nlogin == IDC_BUTTON7)//取消是登陆
		{
			islogin = false;
			break;
		}
	}
}

void CcontrolSerialNetPortDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	int result = MessageBox(_T("你确定要退出?"), _T("温馨提示:"), MB_YESNO | MB_ICONINFORMATION);
	switch (result)
	{
	case IDYES:
		SendMessage(WM_CLOSE, 0, 0);
		break;
	case IDNO:
		break;
	}
}


void CcontrolSerialNetPortDlg::OnStnClickedStatic2()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CcontrolSerialNetPortDlg::OnBnClickedButtonlog()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CcontrolSerialNetPortDlg::OnCbnSelchangeComboPort3()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CcontrolSerialNetPortDlg::OnCbnSelchangeComboPort2()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CcontrolSerialNetPortDlg::OnStnClickedDisp1()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CcontrolSerialNetPortDlg::OnStnClickedDisp2()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CcontrolSerialNetPortDlg::OnLbnSelchangeListLog()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CcontrolSerialNetPortDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	
}


void CcontrolSerialNetPortDlg::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码

	GetDlgItem(IDC_BUTTON5)->EnableWindow(FALSE);
	DigStartAcquisition(&DigUserHookData[0], 0);
	DigUserHookData[0].IsContinueGrab = true;
	DigStartAcquisition(&DigUserHookData[1], 0);
	DigUserHookData[1].IsContinueGrab = true;
	DigStartAcquisition(&DigUserHookData[2], 0);
	DigUserHookData[2].IsContinueGrab = true;


	//if(NULL == m_createprocess)//// 如果指针变量m_pTipDlg的值为NULL，则对话框还未创建，需要动态创建   
	//{
	//	m_createprocess = new CDialogCreatProcess(); //动态创建对象
	//	m_createprocess->Create(IDD_DIALOG_CreateProcess,this);
	//}
	//m_createprocess->ShowWindow(SW_SHOW); // 显示非模态对话框  
	//m_createprocess->SetWindowPos(NULL, 800, 250, 0, 0, SWP_NOSIZE);//SWP_NOSIZE保持当前大小（cx和cy会被忽略）设置非模态对话框位置

	//UpdateData(TRUE);// 将各控件中的数据保存到相应的变量 


	//UpdateData(FALSE);
}


void CcontrolSerialNetPortDlg::OnBnClickedButton8()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_STATIC3)->SetWindowText(pCreateProcess->m_ProcessName);//将流程名称显示到静态控件中
}


void CcontrolSerialNetPortDlg::OnBnClickedButton7()
{
	// TODO: 在此添加控件通知处理程序代码



}


void CcontrolSerialNetPortDlg::OnBnClickedButton12()//智能编辑器
{
	
}

void CcontrolSerialNetPortDlg::OnOpendata()
{
	ShellExecute(NULL, _T("open"), _T("http://127.0.0.1:8000/login.html"), NULL, NULL, SW_SHOW);
}


void CcontrolSerialNetPortDlg::OnRobottest()
{
	ShellExecute(this->m_hWnd, _T("open"), _T("test3.exe"), _T(""), _T("D:\\项目文件\\212\\controlSerialNetPort_v6.4\\x64\\Release"), SW_SHOW);
}

int CcontrolSerialNetPortDlg::VoiceAlarm(int lt)
{
	int Ct;
	Ct = 1000 * lt;
	//	Beep(523, Ct);
	Beep(578, Ct);
	//	Beep(659, Ct);
	return 0;
}

void CcontrolSerialNetPortDlg::OnScript()
{
	ShellExecute(NULL, _T("open"), _T("D:\\项目文件\\212\\controlSerialNetPort_v6.4\\x64\\Release\\v4.docx"), NULL, NULL, SW_SHOW);
}


void CcontrolSerialNetPortDlg::OnStation1()
{
	int axises[] = { axis4, axis5, axis7, axis8 };
	int port = portNum3;

	if (CPublic::portIsOpen[port - 1] == false)
	{
		CString str = _T("串口") + CPublic::int2CString(port) + _T("未打开！");
		AfxMessageBox(str);
		VoiceAlarm(1);
		//		return;
	}


	CDlgSerial3 m_DlgSerial3(NULL, &port, axises);
	INT_PTR nResponse = m_DlgSerial3.DoModal();//打开轴调试窗口

	if (nResponse == IDOK)
	{
	}
	else if (nResponse == IDCANCEL)
	{
	}

	UpdateData(TRUE);
}


void CcontrolSerialNetPortDlg::OnStation2()
{
	int axises[] = { axis4, axis5, axis7, axis8 };
	int port = portNum4;
	CString dlgName = _T("工位2-手动调整");

	if (CPublic::portIsOpen[port - 1] == false)
	{
		CString str = _T("串口") + CPublic::int2CString(port) + _T("未打开！");
		VoiceAlarm(1);
		AfxMessageBox(str);
		//		return;
	}


	CDlgSerial6 m_DlgSerial(NULL, &port, axises, dlgName);
	INT_PTR nResponse = m_DlgSerial.DoModal();

	if (nResponse == IDOK)
	{
	}
	else if (nResponse == IDCANCEL)
	{
	}

	UpdateData(TRUE);
}


void CcontrolSerialNetPortDlg::OnVisiontest()
{
	int port = portNum3;
	int axises[] = { axis3, axis6 };

	if (CPublic::portIsOpen[port - 1] == false)
	{
		CString str;
		str.Format(_T("串口%d 未打开!"), port);
		AfxMessageBox(str);
		VoiceAlarm(1);
		//		return;
	}

	CDlgSerial1 m_DlgSerial1(NULL, &port, axises);
	//	INT_PTR nResponse = m_DlgSerial1.DoModal();

	CDlgSerial1* dlg;
	dlg = new CDlgSerial1;
	dlg->Create(IDD_DIALOG_SERIAL1); //非模态对话框ID号
	dlg->ShowWindow(SW_SHOW);
	//if (nResponse == IDOK)
	//{
	//}
	//else if (nResponse == IDCANCEL)
	//{
	//}

	UpdateData(TRUE);
}
void CcontrolSerialNetPortDlg::DrawArrow(CPoint p1, CPoint p2, double theta, int length)//绘制直线函数
{
	theta = 3.1415926*theta / 180;//转换为弧度
	double Px, Py, P1x, P1y, P2x, P2y;
	//以P2为原点得到向量P2P1（P）
	Px = p1.x - p2.x;
	Py = p1.y - p2.y;
	//向量P旋转theta角得到向量P1
	P1x = Px*cos(theta) - Py*sin(theta);
	P1y = Px*sin(theta) + Py*cos(theta);
	//向量P旋转-theta角得到向量P2
	P2x = Px*cos(-theta) - Py*sin(-theta);
	P2y = Px*sin(-theta) + Py*cos(-theta);
	//伸缩向量至制定长度
	double x1, x2;
	x1 = sqrt(P1x*P1x + P1y*P1y);
	P1x = P1x*length / x1;
	P1y = P1y*length / x1;
	x2 = sqrt(P2x*P2x + P2y*P2y);
	P2x = P2x*length / x2;
	P2y = P2y*length / x2;
	//平移变量到直线的末端
	P1x = P1x + p2.x;
	P1y = P1y + p2.y;
	P2x = P2x + p2.x;
	P2y = P2y + p2.y;
	CClientDC dc(this);//获取客户窗口DC
	CPen pen, pen1, *oldpen;
	pen.CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	pen1.CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	oldpen = dc.SelectObject(&pen);
	dc.MoveTo(p1.x, p1.y);
	dc.LineTo(p2.x, p2.y);
	dc.SelectObject(&pen1);
	dc.MoveTo(p2.x, p2.y);
	dc.LineTo(P1x, P1y);
	dc.MoveTo(p2.x, p2.y);
	dc.LineTo(P2x, P2y);
	dc.SelectObject(oldpen);
}
void CcontrolSerialNetPortDlg::DrawLine(CPoint p1, CPoint p2)//带箭头
{
	CClientDC dc(this);//获取DC
	CPen pen, pen1, *oldpen;
	int PenLineWidth = 2;//为了根据线条宽度设置箭头的大小
	pen.CreatePen(PS_SOLID, PenLineWidth, RGB(80, 80, 80));
	pen1.CreatePen(PS_SOLID, PenLineWidth, RGB(80, 80, 80));
	oldpen = dc.SelectObject(&pen);

	double theta = 3.1415926 / 15 * PenLineWidth;//转换为弧度
	double Px, Py, P1x, P1y, P2x, P2y;
	//以P2为原点得到向量P2P1（P）
	Px = p1.x - p2.x;
	Py = p1.y - p2.y;
	//向量P旋转theta角得到向量P1
	P1x = Px*cos(theta) - Py*sin(theta);
	P1y = Px*sin(theta) + Py*cos(theta);
	//向量P旋转-theta角得到向量P2
	P2x = Px*cos(-theta) - Py*sin(-theta);
	P2y = Px*sin(-theta) + Py*cos(-theta);
	//伸缩向量至制定长度
	double x1, x2;
	int length = 10;
	x1 = sqrt(P1x*P1x + P1y*P1y);
	P1x = P1x*length / x1;
	P1y = P1y*length / x1;
	x2 = sqrt(P2x*P2x + P2y*P2y);
	P2x = P2x*length / x2;
	P2y = P2y*length / x2;
	//平移变量到直线的末端
	P1x = P1x + p2.x;
	P1y = P1y + p2.y;
	P2x = P2x + p2.x;
	P2y = P2y + p2.y;
	dc.MoveTo(p1.x, p1.y);//移动画笔到第一个点
	dc.LineTo(p2.x, p2.y);//划线
	dc.SelectObject(&pen1);
	dc.MoveTo(p2.x, p2.y);//移动到第二个点
	dc.LineTo(P1x, P1y);//划线到第三个点
	dc.MoveTo(p2.x, p2.y);//移动到第二个点
	dc.LineTo(P2x, P2y);//划线到第四个点
	dc.MoveTo(P1x, P1y);//移动到第三个点
	dc.LineTo(P2x, P2y);//划线到第四个点
	
	//填充三角形区域
	CPoint ptVertex[3];
	ptVertex[0].x = p2.x;
	ptVertex[0].y = p2.y;
	ptVertex[1].x = P1x;
	ptVertex[1].y = P1y;
	ptVertex[2].x = P2x;
	ptVertex[2].y = P2y;
	CBrush br(RGB(80, 80, 80));
	CRgn rgn;
	rgn.CreatePolygonRgn(ptVertex, 3, ALTERNATE);//可以创建一个由一系列点围成的区域。
	dc.FillRgn(&rgn, &br);//指定刷子填充指定区域

	dc.SelectObject(oldpen);

	br.DeleteObject();
	rgn.DeleteObject();
}

//加载icon图标的函数
void CcontrolSerialNetPortDlg::LoadFlowchart(UINT ID,CStatic*m_mm)//加载icon函数
{
	CBitmap bitmap;  // CBitmap对象，用于加载位图   
	HBITMAP hBmp;    // 保存CBitmap加载的位图的句柄   

	bitmap.LoadBitmap(ID);  // 将位图IDB_BITMAP1加载到bitmap   
	hBmp = (HBITMAP)bitmap.GetSafeHandle();  // 获取bitmap加载位图的句柄  
	(*m_mm).SetBitmap(hBmp);    // 设置图片控件m_jzmPicture的位图图片为IDB_BITMAP1  
}

void CcontrolSerialNetPortDlg::OnBnClickedButtonflowchart()//绘制流程图
{
	// TODO: 在此添加控件通知处理程序代码
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	if (NULL == m_flowchartdlg)  // 如果指针变量m_create的值为NULL，则对话框还未创建，需要动态创建   
	{
		m_flowchartdlg = new CFlowChart();   //动态创建对象
		m_flowchartdlg->Create(IDD_DIALOG_FlowChart, this);
	}
	m_flowchartdlg->ShowWindow(SW_SHOW);  // 显示非模态对话框   
	m_flowchartdlg->SetWindowPos(NULL, 450, 120, 0, 0, SWP_NOSIZE);
	//SWP_NOSIZE保持当前对话框大小（第4、5参数cx和cy会被忽略）设置非模态对话框的位置

	//pFlow->flowchart();

}



void CcontrolSerialNetPortDlg::OnBnClickedButton15()
{
	
}



void CcontrolSerialNetPortDlg::OnBnClickedButtonEditor()
{
	// TODO: 在此添加控件通知处理程序代码
	if (NULL == m_editor)  // 如果指针变量m_create的值为NULL，则对话框还未创建，需要动态创建   
	{
		m_editor = new CDiailogEditor();   //动态创建对象
		m_editor->Create(IDD_DIALOG_Editor, this);
	}
	m_editor->ShowWindow(SW_SHOW);  // 显示非模态对话框   
	m_editor->SetWindowPos(NULL, 40, 220, 0, 0, SWP_NOSIZE);
	//SWP_NOSIZE保持当前对话框大小（第4、5参数cx和cy会被忽略）设置非模态对话框的位置// TODO: 在此添加控件通知处理程序代码
}


void CcontrolSerialNetPortDlg::OnBnClickedButtonOpendatabase()
{
	// TODO: 在此添加控件通知处理程序代码
	ShellExecute(NULL, _T("open"), _T("http://127.0.0.1:8000/login.html"), NULL, NULL, SW_SHOW);
}


void CcontrolSerialNetPortDlg::OnBnClickedButtonChangeinittxt1()
{
	CFileDialog dlg(TRUE, _T("Text Files"), _T("*.txt"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,//模板的文件类型？？
		_T("text Files(*.txt)|All Files(*.*)|*.*||"));
	if (dlg.DoModal() != IDOK)
	{
		return;
	}
	//CPublic::initFileName1 =	//取文件名称。
	m_initTXT1=dlg.GetFileName();	//显示文件名称
	UpdateData(FALSE);
}


void CcontrolSerialNetPortDlg::OnBnClickedButtonChangeinittxt2()
{
	// TODO: 在此添加控件通知处理程序代码
	CFileDialog dlg(TRUE, _T("Text Files"), _T("*.txt"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,//模板的文件类型？？
		_T("text Files(*.txt)|All Files(*.*)|*.*||"));
	if (dlg.DoModal() != IDOK)
	{
		return;
	}
	//取文件名称。
	m_initTXT2=dlg.GetFileName();	//显示文件名称
	UpdateData(FALSE);
}



void CcontrolSerialNetPortDlg::OnBnClickedButtonChangeautotxt1()
{
	// TODO: 在此添加控件通知处理程序代码
	// TODO: 在此添加控件通知处理程序代码
	CFileDialog dlg(TRUE, _T("Text Files"), _T("*.txt"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,//模板的文件类型？？
		_T("text Files(*.txt)|All Files(*.*)|*.*||"));
	if (dlg.DoModal() != IDOK)
	{
		return;
	}
	//取文件名称。
	m_autoTXT1=dlg.GetFileName();	//显示文件名称
	UpdateData(FALSE);
}


void CcontrolSerialNetPortDlg::OnBnClickedButtonChangeautotxt2()
{
	// TODO: 在此添加控件通知处理程序代码
	CFileDialog dlg(TRUE, _T("Text Files"), _T("*.txt"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,//模板的文件类型？？
		_T("text Files(*.txt)|All Files(*.*)|*.*||"));
	if (dlg.DoModal() != IDOK)
	{
		return;
	}
		//取文件名称。
	m_autoTXT2=dlg.GetFileName();	//显示文件名称
	UpdateData(FALSE);
}


void CcontrolSerialNetPortDlg::OnStnClickedStatic04()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CcontrolSerialNetPortDlg::OnBnClickedButtonlight06()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CcontrolSerialNetPortDlg::OnBnClickedButtonSuspend()
{
	// TODO: 在此添加控件通知处理程序代码
}




void CcontrolSerialNetPortDlg::OnBnClickedForcecontrol()
{
/*	USB3200_AI_PARAM AIParam;
	USB3200_AI_STATUS AIStatus;
	U32 nSizePoints = 4096, nRetPoints = 0;
	U32 nReadableSegments = 0;
	HANDLE hDevice = INVALID_HANDLE_VALUE;

	// 第一步 创建设备对象
	hDevice = USB3200_DEV_Create(0, 0);
	if (hDevice == INVALID_HANDLE_VALUE)
	{
//		printf("DEV_Create Error\n");
		getch();
	}

	U32 nSpeed = 0;
	if (USB3200_DEV_GetSpeed(hDevice, &nSpeed))
	{
		if (nSpeed < 2)
		{
			printf("This device is USB1.0, Press any key to continue...\n");
			getch();
		}
	}

	memset(&AIParam, 0, sizeof(USB3200_AI_PARAM));
	AIParam.nSampleMode = USB3200_AI_SAMPMODE_CONTINUOUS;// 采样模式, 0=单点采样(按需)， 1=连续采样
	AIParam.nPointsPerChan = 4096;// 每个通道采样点数(也是每通道待读取点数),取值范围为[256, 8192],它与nChannelCount的乘积不能大于65536
	AIParam.fSampleRate = 125000.0;//采样频率，单位为sps，取值范围为[1sps, 500000sps],它是每个采样通道的采样速率
	AIParam.nSampChanCount = 4;// 采样通道总数[1, 8]
	AIParam.nReserved0 = 0;

	AIParam.CHParam[0].nChannel = 0;// 通道号[0, 7]，分别表示物理通道号AI0－AI7
	AIParam.CHParam[0].nSampleGain = USB3200_AI_SAMPGAIN_1MULT;// 采样增益，1倍
	AIParam.CHParam[0].nRefGround = USB3200_AI_REFGND_RSE;// 地参考方式
	AIParam.CHParam[0].nReserved0 = 0;

	AIParam.CHParam[1].nChannel = 1;
	AIParam.CHParam[1].nSampleGain = USB3200_AI_SAMPGAIN_1MULT;
	AIParam.CHParam[1].nRefGround = USB3200_AI_REFGND_RSE;
	AIParam.CHParam[1].nReserved0 = 0;

	AIParam.CHParam[2].nChannel = 2;
	AIParam.CHParam[2].nSampleGain = USB3200_AI_SAMPGAIN_1MULT;
	AIParam.CHParam[2].nRefGround = USB3200_AI_REFGND_RSE;
	AIParam.CHParam[2].nReserved0 = 0;

	AIParam.CHParam[3].nChannel = 3;
	AIParam.CHParam[3].nSampleGain = USB3200_AI_SAMPGAIN_1MULT;
	AIParam.CHParam[3].nRefGround = USB3200_AI_REFGND_RSE;
	AIParam.CHParam[3].nReserved0 = 0;

	AIParam.nGroupLoops = 1;// 组内首末通道循环次数[1, 65535]
	AIParam.nGroupInterval = 1;// 组与组之间的时间间隔, 单位：微秒，取值范围[0, 107374182], 等于0时表示等间隔采样

	AIParam.bDTriggerEn = TRUE;
	AIParam.nDTriggerType = USB3200_AI_TRIGTYPE_EDGE;
	AIParam.nDTriggerDir = USB3200_AI_TRIGDIR_FALLING;

	AIParam.bATriggerEn = TRUE;// 模拟数字触发ATR允许
	AIParam.nATriggerType = USB3200_AI_TRIGTYPE_EDGE;// 边沿触发
	AIParam.nATriggerDir = USB3200_AI_TRIGDIR_FALLING;// 下降沿/低电平
	AIParam.nATrigChannel = 0;// 触发通道
	AIParam.fTriggerLevel = 0.0;// 触发电平
	AIParam.nTriggerSens = 5;

	AIParam.nSampleRange = USB3200_AI_SAMPRANGE_N10_P10V;// ±10V
	AIParam.nClockSource = USB3200_AI_CLKSRC_LOCAL;// 本地时钟
	AIParam.bClockOutput = FALSE;

	AIParam.nReserved1 = 0;
	AIParam.nReserved2 = 0;
	AIParam.nReserved3 = 0;

	if (!USB3200_AI_VerifyParam(hDevice, &AIParam))
	{
//		printf("参数有错，已被调整为合法值，请注意查看日志文件USB3200.log, 按任意键继续...\n");
		getch();
	}

	// 第二步 初始化AI参数
	if (!USB3200_AI_InitParam(hDevice, &AIParam, NULL))
	{
//		printf("AI_InitParam Error\n");
		getch();
	}

	// 第三步 启动AI采样
	if (!USB3200_AI_Start(hDevice))
	{
//		printf("AI_Start Error\n");
		getch();
	}

	// 第四步 设置强制触发(硬件触发时不需要)
	if (!USB3200_AI_SetForceTrig(hDevice))
	{
//		printf("AI_SetForceTrig Error\n");
		getch();
	}

	// 第五步 循环读取AI数据
	while (!kbhit())       //kbhit()检查当前是否有键盘输入，若有则返回一个非1值，否则返回0
	{
		printf("Wait...");
		while (1)
		{
			if (kbhit()) goto Exit;
			if (!USB3200_AI_GetStatus(hDevice, &AIStatus))
			{
				printf("AI_GetStatus Error\n");
				getch();
				goto Exit;
			}

			if (AIStatus.nReadableSegments > 0)// 可读段数，只有它大于0时才能调用AI_ContReadChannels()读取采样段数据
			{
				break;
			}

			if (AIStatus.nSampTaskState == 0)// 采样任务状态, =1:正常, 其它值表示有异常情况
			{
				printf("nSampleTaskState Error\n");
				getch();
				goto Exit;
			}

			printf(".");
		}
		printf("\n");

		do {
			nReadableSegments = USB3200_AI_ContReadChannelsV(hDevice, VoltBuffer, nSizePoints, &nRetPoints);
			if (nRetPoints == 0)
			{
				DWORD dwErrorCode = GetLastError();
				if (dwErrorCode == ERROR_SAMPLE_TASK_FAIL)
				{
					printf("采样任务失败\n");
					getch();//getch()从控制台读取一个字符，但不显示在屏幕上
					goto Exit;
				}
			}

			for (U32 nIndex = 0; nIndex<64; nIndex++)
			{
				printf("nRetPoints=%d  ", nRetPoints);
				for (int nChannel = 0; nChannel<4; nChannel++)
				{
					printf("AI%02d=%6.4fV  ", nChannel, VoltBuffer[nChannel + nIndex * 4]);
				}
				printf("\n");
			}
			if (kbhit()) goto Exit;

		} while (nReadableSegments > 0);
	}

	// 第六步 停止AI采样
	if (!USB3200_AI_Stop(hDevice))
	{
		printf("AI_Stop Error\n");
		getch();
	}

Exit:

	printf("\nPress any key to quit...\n");
	getch();

	// 第七步 释放AI资源
	if (!USB3200_AI_Release(hDevice))
	{
		printf("AI_Release Error\n");
		getch();
	}

	// 第八步 释放设备对象
	if (!USB3200_DEV_Release(hDevice))
	{
		printf("DEV_Release Error\n");
		getch();
	}
	*/
}


void CcontrolSerialNetPortDlg::OnCustomdrawProgress1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}


void CcontrolSerialNetPortDlg::OnOutofmemoryProgress1(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}


void CcontrolSerialNetPortDlg::OnReleasedcaptureProgress1(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}


void CcontrolSerialNetPortDlg::OnThemechangedProgress1(NMHDR* pNMHDR, LRESULT* pResult)
{
	// 该功能要求使用 Windows XP 或更高版本。
	// 符号 _WIN32_WINNT 必须 >= 0x0501。
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}


void CcontrolSerialNetPortDlg::OnBnClickedButtonChangeautotxt3()
{
	// TODO: 在此添加控件通知处理程序代码
	// TODO: 在此添加控件通知处理程序代码


	//CFileDialog dlg(TRUE, _T("Text Files"), _T("*.txt"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,//模板的文件类型？？
	//	_T("text Files(*.txt)|All Files(*.*)|*.*||"));
	//if (dlg.DoModal() != IDOK)
	//{
	//	return;
	//}
	////取文件名称。
	//m_autoTXT3 = dlg.GetFileName();	//显示文件名称
	//UpdateData(FALSE);
}


void CcontrolSerialNetPortDlg::OnStnClickedStaticautotxt3()
{
	// TODO: 在此添加控件通知处理程序代码
}



//void CcontrolSerialNetPortDlg::DigStartAcquisition(DigHookDataStruct* UserSt, int flag)
//{
//	if (UserSt->MilDigitizer)
//	{
//		UserSt->GrabInProgress = M_TRUE;
//
//		MIL_INT64 oporation = (flag == 0) ? M_START : M_SEQUENCE + M_COUNT(1);
//		MdigProcess(UserSt->MilDigitizer, UserSt->MilGrabBufferList,
//			UserSt->MilGrabBufferListSize, oporation, M_DEFAULT,
//			ProcessingFunction, UserSt);
//
//
//		MdigInquire(UserSt->MilDigitizer, M_GC_PAYLOAD_SIZE, &UserSt->PayloadSize);
//	}
//}

MIL_INT MFTYPE ProcessingFunction(MIL_INT HookType,
	MIL_ID HookId,
	void* HookDataPtr)
{
	DigHookDataStruct* UserHookDataPtr = (DigHookDataStruct*)HookDataPtr;

	if (UserHookDataPtr->GrabInProgress == M_TRUE)
	{
		MIL_ID ModifiedBufferId = 0, overlayBufferId = 0;
		MIL_INT ResendRequests = 0, PacketsMissed = 0, IsCorrupt = 0;

		/* Retrieve the MIL_ID of the grabbed buffer and camera statistics. */
		MdigGetHookInfo(HookId, M_MODIFIED_BUFFER + M_BUFFER_ID, &ModifiedBufferId);
		MdigGetHookInfo(HookId, M_GC_PACKETS_RESENDS_NUM, &ResendRequests);
		MdigGetHookInfo(HookId, M_GC_PACKETS_MISSED, &PacketsMissed);
		MdigGetHookInfo(HookId, M_CORRUPTED_FRAME, &IsCorrupt);

		UserHookDataPtr->ResendRequests += ResendRequests;
		UserHookDataPtr->PacketsMissed += PacketsMissed;

		/* Copy the grabbed frame to display. */
		if (IsCorrupt)
		{
			UserHookDataPtr->CorruptImageCount++;
			mainDlg->AddString(_T("采集图像帧错误？"));
		}
			
		else
		{
			UserHookDataPtr->ProcessedImageCount++;
			if (UserHookDataPtr->IsContinueGrab == true)
			{
				MbufCopy(ModifiedBufferId, UserHookDataPtr->MilImageDisp);
			}
			else
			{
				if (UserHookDataPtr->MilDisplay)
				{
					MdispControl(UserHookDataPtr->MilDisplay, M_FILL_DISPLAY, M_ENABLE);        /*图像填充显示窗口*/
					MdispControl(UserHookDataPtr->MilDisplay, M_OVERLAY_CLEAR, M_DEFAULT);        /*注释层初始化*/
					MdispInquire(UserHookDataPtr->MilDisplay, M_OVERLAY_ID, &UserHookDataPtr->MilOverlay);    /*载入注释层*/
				}

				MbufCopy(ModifiedBufferId, UserHookDataPtr->MilImageDisp);
				Sleep(20);
				int workNum = UserHookDataPtr->workNum;
				int count = 0;
				do
				{
					int state = SingleModelExample304(UserHookDataPtr->MilSystem, ModifiedBufferId, UserHookDataPtr->MilOverlay, workNum, &CPublic::g_positionInfo[workNum]);
					if (state == 1)
					{
						MbufCopy(ModifiedBufferId, UserHookDataPtr->MilImageDisp);
						mainDlg->AddString(_T("模板匹配成功！"));
						break;
					}
					else
					{
						mainDlg->AddString(CPublic::int2CString(count + 1) + _T("次模板匹配失败？"));
						count++;
					}

				} while (count < 4);

				if (count == 4)
				{
					mainDlg->m_continue[workNum] = false;
				}
				//bnProcess(mainDlg->SysUserHookData.MilSystem, ModifiedBufferId, UserHookDataPtr->MilOverlay, ModifiedBufferId);

			}


		}

	}



	return 0;
}

// MilImage为当前软件实时显示的图像ImageBuffer, MilOverlayImage为当前相机显示中的注释层，result为输出的结果数组
int SingleModelExample304(MIL_ID MilSystem, MIL_ID MilImage, MIL_ID MilOverlayImage, int workNum, PositionInfo* output)
{
	MIL_ID MilChild;                         /* 感兴趣区图像ID*/
	MIL_ID MilSearchContext,                 /*模板匹配控制器ID*/
		MilResult;                        /*结果缓存ID*/
	MIL_DOUBLE ModelDrawColor = M_COLOR_RED;     /* 模板线框颜色*/
	int proNum = CPublic::g_imagePara1[workNum].proNum;
	int maxMatchNum = CPublic::g_imagePara1[workNum].maxMatchNum;
	maxMatchNum = 2L;
	int matchNum = CPublic::g_imagePara1[workNum].matchNum;
	matchNum = 1;
	int ROI_x = CPublic::g_imagePara1[workNum].ROI_x;
	int ROI_y = CPublic::g_imagePara1[workNum].ROI_y;
	int ROI_w = CPublic::g_imagePara1[workNum].ROI_w;
	int ROI_h = CPublic::g_imagePara1[workNum].ROI_h;
	int MORPHIC_iteration = CPublic::g_imagePara1[workNum].iterationNum;



	//wchar_t wcstring[256];
	//MultiByteToWideChar(CP_ACP,0,CPublic::g_imagePara[CPublic::g_workNum][CPublic::g_roundNum].modelFilePath,-1,wcstring,256);

	int SearchSpeed = (CPublic::g_imagePara1[workNum].searchSpeedMode == 0) ? 1 : 3;
	int smoothness = CPublic::g_imagePara1[workNum].smoothness;

	MIL_INT* Model = new MIL_INT[maxMatchNum];   /* 模板编号（数组）*/
	MIL_INT NumResults = 0L;                  /* 匹配结果数*/
	//MIL_DOUBLE* Score = new MIL_DOUBLE[maxMatchNum];     /* 匹配评估结果（数组）*/
	MIL_DOUBLE* XPosition = new MIL_DOUBLE[maxMatchNum];     /* 匹配评估结果（数组）*/
	MIL_DOUBLE* YPosition = new MIL_DOUBLE[maxMatchNum];     /* 匹配评估结果（数组）*/
	MIL_DOUBLE* Angle = new MIL_DOUBLE[maxMatchNum];     /* 匹配评估结果（数组）*/
	MIL_DOUBLE* Scale = new MIL_DOUBLE[maxMatchNum];     /* 匹配评估结果（数组）*/
	MIL_DOUBLE* Score = new MIL_DOUBLE[maxMatchNum];     /* 匹配评估结果（数组）*/
	MIL_DOUBLE Time = 0.0;                       /* 所用时间 */

	/*选取感兴趣区并显示*/
	MbufChild2d(MilImage, ROI_x, ROI_y, ROI_w, ROI_h, &MilChild);
	//MbufSave(MIL_TEXT("G:\\visual studio\\2024\\MILBUFSAVE\\1.bmp"), MilImage);
	//注释层设置//
	/*MgraAllocList(MilSystem, M_DEFAULT, &MilOverlayImage);
	MdispControl(MilDisplay, M_ASSOCIATED_GRAPHIC_LIST_ID, MilOverlayImage);*/

	// MORPHIC_iteration = 1600;
	SearchSpeed = 1L;
	//smoothness = 100;
	/*预处理*/
	MimMorphic(MilChild, MilChild, M_3X3_RECT, M_AREA_OPEN, MORPHIC_iteration, M_GRAYSCALE);
	MimMorphic(MilChild, MilChild, M_3X3_RECT, M_AREA_CLOSE, MORPHIC_iteration, M_GRAYSCALE);

	/*匹配环境设置*/
	MmodAlloc(MilSystem, M_GEOMETRIC, M_DEFAULT, &MilSearchContext); /*分配匹配控制器*/
	MmodAllocResult(MilSystem, M_DEFAULT, &MilResult);/*分配结果缓存 */

	/*定义模板*/

	MmodDefineFromFile(MilSearchContext, M_DXF_FILE, CPublic::g_imagePara1[workNum].modelFilePath, M_DEFAULT); /*从文件定义模板*/


	/*设置匹配参数 */
	MmodControl(MilSearchContext, M_CONTEXT, M_SPEED, M_LOW);  /*设置匹配速度 */
	MmodControl(MilSearchContext, M_CONTEXT, M_SMOOTHNESS, smoothness);      /*设置匹配平滑度（对于识别到的边缘进行平滑处理） */
	MmodControl(MilSearchContext, M_DEFAULT, M_NUMBER, matchNum);          /*匹配目标数 */
	//MmodControl(MilResult, M_DEFAULT, M_DRAW_RELATIVE_ORIGIN_X, -ROI_x);
	//MmodControl(MilResult, M_DEFAULT, M_DRAW_RELATIVE_ORIGIN_Y, -ROI_y);


	/*匹配预处理 */
	MmodPreprocess(MilSearchContext, M_DEFAULT);

	/*执行匹配*/
	//MappTimer(M_TIMER_RESET+M_SYNCHRONOUS, M_NULL);/*启动计时器 */
	MmodFind(MilSearchContext, MilChild, MilResult);
	//MappTimer(M_TIMER_READ+M_SYNCHRONOUS, &Time);/*读取时间 */

	/*读取匹配结果数 */
	MmodGetResult(MilResult, M_DEFAULT, M_NUMBER + M_TYPE_MIL_INT, &NumResults);

	/* 读取打印结果 ，应该返回什么值？是这NumResults组数据的平均值吗？应返回XPosition，YPosition和angel吗？ */
	if ((NumResults >= 1) && (NumResults <= maxMatchNum))
	{
		MmodGetResult(MilResult, M_DEFAULT, M_INDEX + M_TYPE_MIL_INT, Model);
		MmodGetResult(MilResult, M_DEFAULT, M_POSITION_X, XPosition);
		MmodGetResult(MilResult, M_DEFAULT, M_POSITION_Y, YPosition);
		MmodGetResult(MilResult, M_DEFAULT, M_ANGLE, Angle);
		MmodGetResult(MilResult, M_DEFAULT, M_SCALE, Scale);
		MmodGetResult(MilResult, M_DEFAULT, M_SCORE, Score);

		/*加入结果数量判断，若结果数量为2，取所得两个结果的均值*/

		if (NumResults == 2)
		{
			XPosition[0] = (XPosition[0] + XPosition[1]) / 2;
			YPosition[0] = (YPosition[0] + YPosition[1]) / 2;
			Angle[0] = (Angle[0] + Angle[1]) / 2;
		}

		/*加入特征点位置调整*/
		XPosition[0] = XPosition[0] + CPublic::g_imagePara1[workNum].modelDistance * cos(3.1415926 * Angle[0] / 180) + CPublic::g_imagePara1[workNum].ROI_x;
		YPosition[0] = YPosition[0] - CPublic::g_imagePara1[workNum].modelDistance * sin(3.1415926 * Angle[0] / 180) + CPublic::g_imagePara1[workNum].ROI_y;


		output->x = XPosition[0];
		output->y = YPosition[0];
		output->a = Angle[0];

		//该部分是否是在图片上画出边缘和直线？若是的话自动流程中无需显示	
		for (int i = 0; i < NumResults; i++)
		{
			MgraColor(M_DEFAULT, ModelDrawColor);
			MmodDraw(M_DEFAULT, MilResult, MilOverlayImage, M_DRAW_EDGES + M_DRAW_POSITION, i, M_DEFAULT);
		}

	}
	else
	{
		MbufFree(MilChild);
		MmodFree(MilSearchContext);
		MmodFree(MilResult);
		return 0;
	}

	/* 结束并释放资源*/
	MbufFree(MilChild);
	MmodFree(MilSearchContext);
	MmodFree(MilResult);
	return 1;
}



void CcontrolSerialNetPortDlg::MilCreate()
{
	MIL_INT BoardType, DevNb;

	memset(&SysUserHookData, 0, sizeof(SysUserHookData));
	memset(DigUserHookData, 0, sizeof(DigHookDataStruct) * MAX_CAM);

	/* Allocate defaults. */
	MappAlloc(M_DEFAULT, &MilApplication);
	MsysAlloc(M_SYSTEM_GIGE_VISION, M_DEFAULT, M_DEFAULT, &MilSystem);

	SysUserHookData.MilSystem = MilSystem;
	SysUserHookData.NbCameras = 0;
	SysUserHookData.DigHookDataStrutPtr = DigUserHookData;

	MsysInquire(MilSystem, M_BOARD_TYPE, &BoardType);

	if (((BoardType & M_BOARD_TYPE_MASK) != M_GIGE_VISION))
	{
		AddString(_T("This example requires a M_GIGE_VISION system type."));
		AddString(_T("Please change system type in milconfig."));
		MappFreeDefault(MilApplication, MilSystem, M_NULL, M_NULL, M_NULL);
		return;
	}

	/* Inquire the number of cameras attached. */
	MsysInquire(MilSystem, M_NUM_CAMERA_PRESENT, &SysUserHookData.NbCameras);
	if (SysUserHookData.NbCameras > MAX_CAM)
		SysUserHookData.NbCameras = MAX_CAM;

	/* Allocate and start acquisition on all cameras found at MsysAlloc time. */
	if (SysUserHookData.NbCameras)
	{
		/* Allocate digitizers and other resources. */
		for (DevNb = M_DEV0; DevNb < MAX_CAM; DevNb++)
		{
			if (DevNb == M_DEV0)
				DigAllocResources(MilSystem, DevNb, IDC_DISP1, &DigUserHookData[DevNb], false);
			else if (DevNb == M_DEV1)
			{
				DigAllocResources(MilSystem, DevNb, IDC_DISP2, &DigUserHookData[DevNb], false);
			}
			else if (DevNb == M_DEV2)
			{
				DigAllocResources(MilSystem, DevNb, IDC_DISP3, &DigUserHookData[DevNb], false);
			}

			if (DigUserHookData[DevNb].MilDigitizer)
				AddAdapterToList(&SysUserHookData, DigUserHookData[DevNb].pAdapterName);


			if (DigUserHookData[DevNb].MilDisplay)
			{
				MdispControl(DigUserHookData[DevNb].MilDisplay, M_OVERLAY, M_ENABLE);               /*开启注释层*/
			}

		}
	}




}

/* Allocates digitizer plus all other resources needed for image acquisition and */
/* camera state changes.                                                         */
/* ------------------------------------------------------------------------------*/

void CcontrolSerialNetPortDlg::DigAllocResources(MIL_ID MilSystem, MIL_INT DeviceNum, int WindowID, DigHookDataStruct* UserSt,
	bool PrintErrors)
{
	MIL_INT VendorStLen, ModelStLen, MacStLen;
	MIL_INT64 PixFmt = 0;
	MIL_INT SizeBand = 0, BufType = 0;
	MIL_INT64 BufFormat = M_PROC;

	/* In cases where the preferred method for device allocation requires allocating with     */
	/* a user-defined name the following code can be used. "MyCameraName" must be replaced    */
	/* with the actual camera name written in the camera.                                     */

	/* MIL_TEXT_CHAR MyCameraName[64] = {'\0'};                                               */

	/* MosSprintf(MyCameraName, 64, MIL_TEXT("MyCameraName%d"), DeviceNum);                   */
	/* MdigAlloc(MilSystem, M_GC_CAMERA_ID(MIL_TEXT("MyCameraName")), MIL_TEXT("M_DEFAULT"),  */
	/*    M_GC_DEVICE_USER_NAME, &MilDigitizer);                                              */

	if (PrintErrors)
		MdigAlloc(MilSystem, DeviceNum, MIL_TEXT("M_DEFAULT"), M_DEV_NUMBER,
			&UserSt->MilDigitizer);
	else
	{
		MappControl(M_DEFAULT, M_ERROR, M_PRINT_DISABLE);
		MdigAlloc(MilSystem, DeviceNum, MIL_TEXT("M_DEFAULT"), M_DEV_NUMBER,
			&UserSt->MilDigitizer);
		MappControl(M_DEFAULT, M_ERROR, M_PRINT_ENABLE);
	}

	if (UserSt->MilDigitizer)
	{
		MIL_INT Len = 0;
		UserSt->MilSystem = MilSystem;
		UserSt->IsConnected = true;
		UserSt->IsContinueGrab = false;

		/* Disable MdigProcess grab monitor since disconnecting a camera will result in an  */
		/* error message.                                                                   */
		MdigControl(UserSt->MilDigitizer, M_PROCESS_GRAB_MONITOR, M_DISABLE);
		/* Disable corrupted frame errors as they are handled from the MdigProcess hook     */
		/* function.                                                                        */
		MdigControl(UserSt->MilDigitizer, M_CORRUPTED_FRAME_ERROR, M_DISABLE);

		/* Inquire information related to the camera being allocated. */
		MdigInquire(UserSt->MilDigitizer, M_CAMERA_VENDOR_SIZE, &VendorStLen);
		MdigInquire(UserSt->MilDigitizer, M_CAMERA_MODEL_SIZE, &ModelStLen);
		MdigInquire(UserSt->MilDigitizer, M_GC_PACKET_SIZE, &UserSt->PacketSize);
		MdigInquire(UserSt->MilDigitizer, M_GC_INTERFACE_NAME_SIZE, &Len);
		if (Len)
		{
			UserSt->pAdapterName = new MIL_TEXT_CHAR[Len];
			MdigInquire(UserSt->MilDigitizer, M_GC_INTERFACE_NAME, UserSt->pAdapterName);
		}

		UserSt->CamVendor = new MIL_TEXT_CHAR[VendorStLen];
		UserSt->CamModel = new MIL_TEXT_CHAR[ModelStLen];

		MdigInquire(UserSt->MilDigitizer, M_CAMERA_VENDOR, UserSt->CamVendor);
		MdigInquire(UserSt->MilDigitizer, M_CAMERA_MODEL, UserSt->CamModel);

		MdigInquire(UserSt->MilDigitizer, M_GC_MAC_ADDRESS_STRING_SIZE, &MacStLen);
		UserSt->CamMacAddress = new MIL_TEXT_CHAR[MacStLen];
		MdigInquire(UserSt->MilDigitizer, M_GC_MAC_ADDRESS_STRING, UserSt->CamMacAddress);

		/* Pop-up the MIL feature browser; exposes GigE device features.                */
#if (USE_FEATURE_BROWSER == 1)
		MdigControl(UserSt->MilDigitizer, M_GC_FEATURE_BROWSER, M_OPEN + M_ASYNCHRONOUS);
#endif

		/* Allocate displays and buffers; everything necessary to run MdigProcess. */
		MdispAlloc(MilSystem, M_DEFAULT, MIL_TEXT("M_DEFAULT"), M_DEFAULT,
			&UserSt->MilDisplay);
		MdispControl(UserSt->MilDisplay, M_TITLE,
			M_PTR_TO_DOUBLE(UserSt->CamModel));

		/* Allocate a buffer format that matches the camera's pixel format. */
		MdigInquireFeature(UserSt->MilDigitizer, M_FEATURE_VALUE, MIL_TEXT("PixelFormat"),
			M_TYPE_ENUMERATION, &PixFmt);
		GetMilBufferInfoFromPixelFormat(UserSt->MilDigitizer, PixFmt, SizeBand, BufType,
			BufFormat);

		MbufAllocColor(MilSystem,
			SizeBand,
			MdigInquire(UserSt->MilDigitizer, M_SIZE_X, M_NULL),
			MdigInquire(UserSt->MilDigitizer, M_SIZE_Y, M_NULL),
			BufType,
			M_IMAGE + M_GRAB + M_DISP + M_PROC,
			&UserSt->MilImageDisp);

		/*MbufAllocColor(MilSystem,
			SizeBand,
			MdigInquire(UserSt->MilDigitizer, M_SIZE_X, M_NULL),
			MdigInquire(UserSt->MilDigitizer, M_SIZE_Y, M_NULL),
			BufType,
			M_IMAGE+M_DISP+M_PROC,
			&UserSt->MilOverlay);*/
		MbufClear(UserSt->MilImageDisp, M_COLOR_BLACK);
		MdispSelectWindow(UserSt->MilDisplay, UserSt->MilImageDisp, GetDlgItem(WindowID)->GetSafeHwnd());

		for (MIL_INT i = 0; i < BUFFERING_SIZE_MAX; i++)
		{
			MbufAllocColor(MilSystem,
				SizeBand,
				MdigInquire(UserSt->MilDigitizer, M_SIZE_X, M_NULL),
				MdigInquire(UserSt->MilDigitizer, M_SIZE_Y, M_NULL),
				BufType,
				M_GRAB + M_IMAGE + M_PROC,
				&UserSt->MilGrabBufferList[i]);
			if (UserSt->MilGrabBufferList[i])
			{
				UserSt->MilGrabBufferListSize++;
				MbufClear(UserSt->MilGrabBufferList[i], 0);
			}
		}
	}
}

/* Get the MIL buffer attributes that match the camera's pixel format.   */
/* --------------------------------------------------------------------- */
void CcontrolSerialNetPortDlg::GetMilBufferInfoFromPixelFormat(MIL_ID MilDigitizer, MIL_INT64 PixelFormat,
	MIL_INT& SizeBand, MIL_INT& BufType, MIL_INT64& Attribute)
{
	MIL_INT Conversion = 0;

	switch (PixelFormat)
	{
	case PFNC_MONO8_ID:
		SizeBand = 1;
		BufType = 8 + M_UNSIGNED;
		Attribute = M_MONO8 + M_PLANAR;
		break;
	case GEV_MONO10_PACKED_ID:
	case GEV_MONO12_PACKED_ID:
		SizeBand = 1;
		BufType = 16 + M_UNSIGNED;
		Attribute = M_PLANAR;
		break;
	case PFNC_MONO10_ID:
	case PFNC_MONO12_ID:
	case PFNC_MONO14_ID:
	case PFNC_MONO16_ID:
		SizeBand = 1;
		BufType = 16 + M_UNSIGNED;
		Attribute = M_PLANAR;
		break;
	case PFNC_RGB8_ID:
		SizeBand = 3;
		BufType = 8 + M_UNSIGNED;
		Attribute = M_RGB24 + M_PACKED;
		break;
	case PFNC_BGR8_ID:
		SizeBand = 3;
		BufType = 8 + M_UNSIGNED;
		Attribute = M_BGR24 + M_PACKED;
		break;
	case PFNC_BAYERGR8_ID:
	case PFNC_BAYERRG8_ID:
	case PFNC_BAYERGB8_ID:
	case PFNC_BAYERBG8_ID:
		MdigInquire(MilDigitizer, M_BAYER_CONVERSION, &Conversion);
		if (Conversion == M_ENABLE)
		{
			SizeBand = 3;
			BufType = 8 + M_UNSIGNED;
			Attribute = M_BGR32 + M_PACKED;
		}
		else
		{
			SizeBand = 1;
			BufType = 8 + M_UNSIGNED;
			Attribute = M_MONO8 + M_PLANAR;
		}
		break;
	case PFNC_BGRa8_ID:
		SizeBand = 3;
		BufType = 8 + M_UNSIGNED;
		Attribute = M_BGR32 + M_PACKED;
		break;
	case PFNC_BAYERGR10_ID:
	case PFNC_BAYERRG10_ID:
	case PFNC_BAYERGB10_ID:
	case PFNC_BAYERBG10_ID:
	case PFNC_BAYERGR12_ID:
	case PFNC_BAYERRG12_ID:
	case PFNC_BAYERGB12_ID:
	case PFNC_BAYERBG12_ID:
	case PFNC_BAYERGR16_ID:
	case PFNC_BAYERRG16_ID:
	case PFNC_BAYERGB16_ID:
	case PFNC_BAYERBG16_ID:
	case GEV_BAYGR10_PACKED_ID:
	case GEV_BAYRG10_PACKED_ID:
	case GEV_BAYGB10_PACKED_ID:
	case GEV_BAYBG10_PACKED_ID:
	case GEV_BAYGR12_PACKED_ID:
	case GEV_BAYRG12_PACKED_ID:
	case GEV_BAYGB12_PACKED_ID:
	case GEV_BAYBG12_PACKED_ID:
		MdigInquire(MilDigitizer, M_BAYER_CONVERSION, &Conversion);
		if (Conversion == M_ENABLE)
		{
			SizeBand = 3;
			BufType = 16 + M_UNSIGNED;
			Attribute = M_RGB48 + M_PACKED;
		}
		else
		{
			SizeBand = 1;
			BufType = 16 + M_UNSIGNED;
			Attribute = M_PLANAR;
		}
		break;
	case PFNC_RGB10_ID:
	case PFNC_RGB12_ID:
	case PFNC_BGR10_ID:
	case PFNC_BGR12_ID:
		SizeBand = 3;
		BufType = 16 + M_UNSIGNED;
		Attribute = M_RGB48 + M_PACKED;
		break;
	case PFNC_YUV422_8_UYVY_ID:
		SizeBand = 3;
		BufType = 8 + M_UNSIGNED;
		Attribute = M_YUV16_UYVY + M_PACKED;
		break;
	case PFNC_YUV422_8_ID:
		SizeBand = 3;
		BufType = 8 + M_UNSIGNED;
		Attribute = M_YUV16_YUYV + M_PACKED;
		break;
	default:
		SizeBand = 0;
		BufType = 0;
		Attribute = 0;
		break;
	}
}


void CcontrolSerialNetPortDlg::AddAdapterToList(SysHookDataStruct* UserSt, MIL_TEXT_PTR AdapterName)
{
	/* Start by searching if adapter is already in list. */
	for (MIL_INT i = 0; i < MAX_ADAPTERS; i++)
	{
		if (MosStrcmp(UserSt->Adapters[i], AdapterName) == 0)
			return;
	}

	/* Adapter is not in list; add it. */
	for (MIL_INT i = 0; i < MAX_ADAPTERS; i++)
	{
		if (UserSt->Adapters[i][0] == '\0')
		{
			MosStrcpy(UserSt->Adapters[i], MAX_ADAPTER_DESCRIPTION_LENGTH + 4, AdapterName);
			return;
		}
	}
}


void CcontrolSerialNetPortDlg::DigStartAcquisition(DigHookDataStruct* UserSt, int flag)
{
	if (UserSt->MilDigitizer)
	{
		UserSt->GrabInProgress = M_TRUE;

		MIL_INT64 oporation = (flag == 0) ? M_START : M_SEQUENCE + M_COUNT(1);
		MdigProcess(UserSt->MilDigitizer, UserSt->MilGrabBufferList,
			UserSt->MilGrabBufferListSize, oporation, M_DEFAULT,
			ProcessingFunction, UserSt);


		MdigInquire(UserSt->MilDigitizer, M_GC_PAYLOAD_SIZE, &UserSt->PayloadSize);
	}
	else
	{
		AddString(_T("图相中断,可能原因：相机未连接！可能没插密码狗"));
	}
}

void CcontrolSerialNetPortDlg::MilDestroy()
{

	for (int DevNb = M_DEV0; DevNb < MAX_CAM; DevNb++)
	{
		if ((DigUserHookData[DevNb].MilDisplay) && (DigUserHookData[DevNb].MilImageDisp))
		{
			MdispDeselect(DigUserHookData[DevNb].MilDisplay, DigUserHookData[DevNb].MilImageDisp);
		}
		DigFreeResources(&DigUserHookData[DevNb]);
	}

	MsysHookFunction(MilSystem, M_CAMERA_PRESENT + M_UNHOOK, CamPresentFunction,
		&SysUserHookData);
	MsysFree(MilSystem);
	MappFree(MilApplication);
}

void CcontrolSerialNetPortDlg::DigStopAcquisition(DigHookDataStruct* UserSt)
{
	if (UserSt->GrabInProgress)
	{
		UserSt->GrabInProgress = M_FALSE;
		MdigProcess(UserSt->MilDigitizer, UserSt->MilGrabBufferList,
			UserSt->MilGrabBufferListSize, M_STOP + M_WAIT, M_DEFAULT,
			ProcessingFunction, UserSt);

	}
}

/* Free digitizer and all other resources allocated.  */
/* -------------------------------------------------- */

void CcontrolSerialNetPortDlg::DigFreeResources(DigHookDataStruct* UserSt)
{
	if (UserSt->MilDigitizer)
	{
		for (MIL_INT i = 0; i < UserSt->MilGrabBufferListSize; i++)
			MbufFree(UserSt->MilGrabBufferList[i]);

		MbufFree(UserSt->MilImageDisp);
		MbufFree(UserSt->MilOverlay);
		MdispFree(UserSt->MilDisplay);

#if (USE_FEATURE_BROWSER == 1)
		/* Close the MIL feature browser; exposes GigE device features.                */
		MdigControl(UserSt->MilDigitizer, M_GC_FEATURE_BROWSER, M_CLOSE);
#endif

		MdigFree(UserSt->MilDigitizer);

		delete[] UserSt->CamVendor;
		delete[] UserSt->CamModel;
		delete[] UserSt->CamMacAddress;
		delete[] UserSt->pAdapterName;
		memset(UserSt, 0, sizeof(DigHookDataStruct));
	}
}


MIL_INT MFTYPE CamPresentFunction(MIL_INT HookType,
	MIL_ID HookId,
	void* HookDataPtr)
{
	SysHookDataStruct* UserHookDataPtr = (SysHookDataStruct*)HookDataPtr;
	MIL_INT IsCamPresent, Number;

	/* Inquire the camera present state (present or not present). */
	MsysGetHookInfo(UserHookDataPtr->MilSystem, HookId, M_CAMERA_PRESENT, &IsCamPresent);
	/* Inquire the camera's digitizer device number . */
	MsysGetHookInfo(UserHookDataPtr->MilSystem, HookId, M_NUMBER, &Number);
	/* Update the number of camera present variable. */
	MsysInquire(UserHookDataPtr->MilSystem, M_NUM_CAMERA_PRESENT,
		&UserHookDataPtr->NbCameras);

	if (IsCamPresent)
	{
		MIL_TEXT_CHAR* MacAddress = NULL;
		MIL_INT Size = 0;

		/* Inquire the camera's MAC address . */
		MsysGetHookInfo(UserHookDataPtr->MilSystem, HookId, M_GC_MAC_ADDRESS_STRING_SIZE,
			&Size);
		MacAddress = new MIL_TEXT_CHAR[Size];
		MsysGetHookInfo(UserHookDataPtr->MilSystem, HookId, M_GC_MAC_ADDRESS_STRING,
			MacAddress);

		/* Camera is present. */
		if (UserHookDataPtr->DigHookDataStrutPtr[Number].MilDigitizer == 0)
		{
			/* Newly attached camera; allocate it. */
			mainDlg->DigAllocResources(UserHookDataPtr->MilSystem, Number, IDC_DISP1 + Number,
				&UserHookDataPtr->DigHookDataStrutPtr[Number]);
		}
		else if (MosStrcmp(UserHookDataPtr->DigHookDataStrutPtr[Number].CamMacAddress,
			MacAddress) != 0)
		{
			/* New camera added in place of another one, free old dig */
			mainDlg->DigFreeResources(&UserHookDataPtr->DigHookDataStrutPtr[Number]);

			/* Find out if camera was previously allocated on a different device number. */
			for (MIL_INT i = 0; i < MAX_CAM; i++)
				if ((i != Number) &&
					(MosStrcmp(UserHookDataPtr->DigHookDataStrutPtr[Number].CamMacAddress,
						MacAddress) == 0))
					mainDlg->DigFreeResources(&UserHookDataPtr->DigHookDataStrutPtr[i]);

			/* Allocate resources. */
			mainDlg->DigAllocResources(UserHookDataPtr->MilSystem, Number, IDC_DISP1 + Number,
				&UserHookDataPtr->DigHookDataStrutPtr[Number]);
		}

		if (UserHookDataPtr->DigHookDataStrutPtr[Number].MilDigitizer)
			mainDlg->AddAdapterToList(UserHookDataPtr,
				UserHookDataPtr->DigHookDataStrutPtr[Number].pAdapterName);

		UserHookDataPtr->DigHookDataStrutPtr[Number].IsConnected = true;
		/* Start acquisition. */
		mainDlg->DigStartAcquisition(&UserHookDataPtr->DigHookDataStrutPtr[Number], 0);

		delete[] MacAddress;
	}
	else
	{
		/* Camera is not present. */
		if (UserHookDataPtr->DigHookDataStrutPtr[Number].MilDigitizer)
		{
			/* Stop acquisition. */
			mainDlg->DigStopAcquisition(&UserHookDataPtr->DigHookDataStrutPtr[Number]);
		}

		UserHookDataPtr->DigHookDataStrutPtr[Number].IsConnected = false;
	}

	return 0;
}





void CcontrolSerialNetPortDlg::OnBnClickedButtonstopcatch()
{
	// TODO: 在此添加控件通知处理程序代码

}


void CcontrolSerialNetPortDlg::OnBnClickedButtonsc()
{
	// TODO: 在此添加控件通知处理程序代码
	DigStopAcquisition(&DigUserHookData[2]);
	GetDlgItem(IDC_BUTTON5)->EnableWindow(TRUE);
	DigUserHookData[2].IsContinueGrab = false;
	DigStopAcquisition(&DigUserHookData[1]);
	DigUserHookData[1].IsContinueGrab = false;
	DigStopAcquisition(&DigUserHookData[0]);
	DigUserHookData[0].IsContinueGrab = false;
}

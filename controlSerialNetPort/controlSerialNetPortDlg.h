// controlSerialNetPortDlg.h : 头文件
//


#pragma once

#include "SerialPort.h"
#include "btnst.h"
#include "Public.h"
//#include "mil.h"
#include "afxmt.h"
#include "AutoSettingDlg.h"
#include "OPTController.h"
#include "OScopeCtrl.h"
#include "afxcmn.h"
#include "afxwin.h"
#include "DialogCreatProcess.h"
#include "DiailogEditor.h"
#include "FlowChart.h"
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include"IO.h"
#include"MILforMatch.h"


//#include "Thread.h"

// CcontrolSerialNetPortDlg 对话框


#define WINDOW_TITLE          MIL_TEXT("Camera: ")
#define MAX_ADAPTERS          16
#define BUFFERING_SIZE_MAX    3
#define STRING_LENGTH_MAX     128
#define STRING_POS_X          20
#define STRING_POS_Y          20
#define STATS_PRINT_PERIOD    1000
#define USE_FEATURE_BROWSER   0
#define WMU_THREAD_EXIT       WM_USER + 20	//自行定义之讯息

#define SINGLE_MODEL_SEARCH_SPEED   M_LOW                          /*设置匹配搜索速度*/
#define MODEL_MAX_OCCURRENCES       16L                            /*设置最大匹配目标数*/
#define MODEL_OCCURRENCES           1L                             /*设置匹配目标数*/
#define MODEL_FILE                  MIL_TEXT("D:\\MOBAN\\1.dxf")   /*设置模板文件路径*/
#define MODEL_SMOOTHNESS            70                             /*设置处理平滑度*/
#define MORPHIC_ITERATION           200                            /*滤波运算迭代次数*/
#define ROI_X                       900                            /*设置感兴趣区位置x */
#define ROI_Y                       900                            /*设置感兴趣区位置y */
#define ROI_W                       800                            /*设置感兴趣区宽度 */
#define ROI_H                       800                            /*设置感兴趣区高度 */




/* User's processing function and camera detect hook data structure. */
//typedef struct
//{
//	MIL_ID MilSystem;
//	MIL_ID MilDigitizer;
//	MIL_ID MilDisplay;
//	MIL_ID MilImageDisp;
//	MIL_ID MilGrabBufferList[BUFFERING_SIZE_MAX];
//	MIL_INT MilGrabBufferListSize;
//	MIL_INT ProcessedImageCount;
//	MIL_DOUBLE FrameRate;
//	MIL_INT ResendRequests;
//	MIL_INT PacketSize;
//	MIL_INT PacketsMissed;
//	MIL_INT CorruptImageCount;
//	MIL_INT GrabInProgress;
//	MIL_INT PayloadSize;
//	MIL_TEXT_PTR CamVendor;
//	MIL_TEXT_PTR CamModel;
//	MIL_TEXT_PTR CamMacAddress;
//	MIL_TEXT_PTR pAdapterName;
//	bool IsConnected;
//	MIL_ID MilOverlay;	
//	bool IsContinueGrab;
//	int workNum;
//} DigHookDataStruct;
//
///* User's system camera detect hook data structure. */
//#define MAX_ADAPTER_DESCRIPTION_LENGTH  512
//typedef struct
//{
//	MIL_ID MilSystem;
//	MIL_INT NbCameras;
//	DigHookDataStruct* DigHookDataStrutPtr;
//	bool PrintAdapterInfo;
//	MIL_TEXT_CHAR Adapters[MAX_ADAPTERS][MAX_ADAPTER_DESCRIPTION_LENGTH + 4];
//} SysHookDataStruct;

typedef struct//结构体类型
{
	bool* Continue;	//是否继续执行
	int workNum;	//执行绪控制的slider控件的代号
	CWnd* dlg;	//产生执行绪的视窗控件
	//int sleepTime;
	// volatile是一个特征修饰符（type specifier）.volatile的作用是作为指令关键字，确保本条指令不会因编译器的优化而省略，且要求每次直接读值。
	//volatile的变量是说这变量可能会被意想不到地改变，这样，编译器就不会去假设这个变量的值了。
	//volatile bool robotFinishFlag;
} ThreadInfo;


/* User's processing function and camera detect hook data structure. */
typedef struct
{
	MIL_ID MilSystem;
	MIL_ID MilDigitizer;
	MIL_ID MilDisplay;
	MIL_ID MilImageDisp;
	MIL_ID MilGrabBufferList[BUFFERING_SIZE_MAX];
	MIL_INT MilGrabBufferListSize;
	MIL_INT ProcessedImageCount;
	MIL_DOUBLE FrameRate;
	MIL_INT ResendRequests;
	MIL_INT PacketSize;
	MIL_INT PacketsMissed;
	MIL_INT CorruptImageCount;
	MIL_INT GrabInProgress;
	MIL_INT PayloadSize;
	MIL_TEXT_PTR CamVendor;
	MIL_TEXT_PTR CamModel;
	MIL_TEXT_PTR CamMacAddress;
	MIL_TEXT_PTR pAdapterName;
	bool IsConnected;
	MIL_ID MilOverlay;
	bool IsContinueGrab;
	int workNum;
} DigHookDataStruct;

#define MAX_ADAPTER_DESCRIPTION_LENGTH  512
typedef struct
{
	MIL_ID MilSystem;
	MIL_INT NbCameras;
	DigHookDataStruct* DigHookDataStrutPtr;
	bool PrintAdapterInfo;
	MIL_TEXT_CHAR Adapters[MAX_ADAPTERS][MAX_ADAPTER_DESCRIPTION_LENGTH + 4];
} SysHookDataStruct;

extern  class CDialoglogin;

MIL_INT MFTYPE ProcessingFunction(MIL_INT HookType, MIL_ID HookId, void* HookDataPtr);
MIL_INT MFTYPE CamPresentFunction(MIL_INT HookType,MIL_ID HookId,void* HookDataPtr);
int SingleModelExample304(MIL_ID MilSystem, MIL_ID MilImage, MIL_ID MilOverlayImage, int workNum, PositionInfo* output);
//DigHookDataStruct DigUserHookData[MAX_CAM];





class CcontrolSerialNetPortDlg : public CDialog
{
// 构造
public:
	CcontrolSerialNetPortDlg(CWnd* pParent = NULL);	// 标准构造函数
	~CcontrolSerialNetPortDlg();	// 析构函数
	CSerialPort serialPort[portNum];
// 对话框数据
	enum { IDD = IDD_CONTROLSERIALNETPORT_DIALOG };
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
	CMenu m_Menu;
// 实现
protected:
	HICON m_hIcon;
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//{{AFX_MSG(CcontrolSerialNetPortDlg) 
	afx_msg LRESULT OnCommunication(WPARAM ch, LPARAM port);
	//{{AFX_MSG(CcontrolSerialNetPortDlg) 
	DECLARE_MESSAGE_MAP()
private:
	CDialogCreatProcess* m_createprocess;//定义CTipDlg类型的指针变量.以前的指针大都是 int *pt1等  int为一种类型。这里CTipDlg为一种类，指向类的指针。
	CDiailogEditor* m_editor;
	CFlowChart* m_flowchartdlg;
public:
	afx_msg void OnBnClickedButtonSerial1();
	CButtonST m_bstLight[UILIGHT_NUM];
	CButtonST m_UnitLight[UNITLIGHT_NUM];
	CStatic m_UnitName[UNITNAME_NUM];

	void LoadFlowchart(UINT ID,CStatic*m_mm);
	CBitmapButton m_bbtn;
//	CButton m_flowchart;
	CButtonST m_autoStart;
	CButtonST m_autoStop;
	CButtonST m_switch;
	CButtonST m_logo;
	CButtonST m_autoSetting;
	CButtonST m_IOControl;
	CButtonST m_OpenEditor;
	CButtonST m_suspend;
	CButtonST m_Continue;
	CButtonST m_initial;
	//CIPAddressCtrl m_localIP;
	//CIPAddressCtrl m_axisIP;
	//CIPAddressCtrl m_IOIP;
	//CIPAddressCtrl m_robotIP[ROBOT_NUM];

	MIL_ID MilApplication;
	MIL_ID MilSystem;
	SysHookDataStruct SysUserHookData;
	DigHookDataStruct DigUserHookData[MAX_CAM];


	void MilCreate();
	void DigAllocResources(MIL_ID MilSystem, MIL_INT DeviceNum, int windowID,
		DigHookDataStruct* UserSt,
		bool PrintErrors = true);
	void GetMilBufferInfoFromPixelFormat(MIL_ID MilDigitizer, MIL_INT64 PixelFormat,
		MIL_INT& SizeBand, MIL_INT& BufType,
		MIL_INT64& Attribute);
	void AddAdapterToList(SysHookDataStruct* UserSt, MIL_TEXT_PTR AdapterName);
	void DigStartAcquisition(DigHookDataStruct* UserSt, int flag);
	void DigStopAcquisition(DigHookDataStruct* UserSt);
	void DigFreeResources(DigHookDataStruct* UserSt);
	int imageProcess(DigHookDataStruct* DigUserHookData, PositionInfo* proResult, int work);
	//void bnProcess(MIL_ID iImageBuffer, MIL_ID oImageBuffer);

	int autoRelSMOV(int axisNum, CString IP, int workNum, int relPos, bool* isContinue);

	void MilDestroy();

	CIO *io;
	MILforMatch* m_MILforMatch;

	bool m_IOConnect ;//IO连接状态
	int m_IOPort;

	posinf *posi;

	void DrawLine(CPoint p1, CPoint p2);
	void DrawArrow(CPoint p1, CPoint p2, double theta, int length);//绘制箭头直线
	void InitUI(void);
	afx_msg void OnBnClickedLogin();
	afx_msg void OnBnClickedButtonSerial2();
	afx_msg void OnBnClickedButtonSerial3();
	void sendComm(CString comm, int portIndex);
	//void sendComm(CString comm1, int axisNum, CString comm2, int port);


	CListBox m_boxlog;
	int m_LogNum;

	void AddString(CString msg);
	afx_msg void OnBnClickedButtonclear();
	afx_msg void OnBnClickedButtonsave();
	afx_msg void OnBnClickedButtonautohand();
	bool IOConnect();

	bool m_isAuto;
//	afx_msg void OnBnClickedButtononehand();
//	afx_msg void OnBnClickedButtontwohand();
//	afx_msg void OnBnClickedButtonthreehand();
	char m_StopRec[portNum][6];
	bool findTerminator(char ch, char* stop);
	bool findSpecialTerminator(char ch, char* stop);
	//bool m_bfindTerminator[portNum];


	/*MIL_ID MilApplication;
	MIL_ID MilSystem;
	SysHookDataStruct SysUserHookData;
	DigHookDataStruct DigUserHookData[MAX_CAM];
	
	void MilCreate();
	void DigAllocResources(MIL_ID MilSystem, MIL_INT DeviceNum, int windowID, 
		DigHookDataStruct* UserSt,
		bool PrintErrors = true);
	void GetMilBufferInfoFromPixelFormat(MIL_ID MilDigitizer, MIL_INT64 PixelFormat,
		MIL_INT& SizeBand, MIL_INT& BufType,
		MIL_INT64& Attribute);
	void AddAdapterToList(SysHookDataStruct* UserSt, MIL_TEXT_PTR AdapterName);*/
	/*void DigStartAcquisition(DigHookDataStruct* UserSt, int flag);
	void DigStopAcquisition(DigHookDataStruct* UserSt);
	void DigFreeResources(DigHookDataStruct* UserSt);*/
	//void bnProcess(MIL_ID iImageBuffer, MIL_ID oImageBuffer);

	//void MilDestroy();
	//afx_msg void OnBnClickedButtonstart1();
	//MIL_INT MFTYPE ProcessingFunction(MIL_INT HookType, MIL_ID HookId, void MPTYPE *HookDataPtr);
	//MIL_INT MFTYPE ProcessingFunction(MIL_INT HookType,MIL_ID HookId,void* HookDataPtr);
	//afx_msg void OnBnClickedButtonmainstop1();
	afx_msg void OnBnClickedButtonstart2();
	afx_msg void OnBnClickedButtonmainstop2();
	afx_msg void OnBnClickedButtonstart3();
//	afx_msg void OnBnClickedButtonmainstop3();
	//afx_msg void OnDestroy();

	afx_msg void OnBnClickedButtonSerial4();
	afx_msg void OnBnClickedButtonSerial5();
	afx_msg void OnBnClickedButtonSerial6();
//	afx_msg void OnBnClickedButtonSerial7();
//	afx_msg void OnBnClickedButtonSerial8();
//	afx_msg void OnBnClickedButtonSerial9();

	//multi-thread
	ThreadInfo m_threadInfo[MAX_CAM];//threadinfo结构体
	CWinThread* m_pThread[MAX_CAM];//CWinThread类是MFC用来封装线程的
	bool m_continue[MAX_CAM];//线程的状态
	int m_sleepTime[MAX_CAM];
	 

	//void autoWorkProcess(int workNum, bool* isWork);
	int beginAutoProcess(void);
	int beginInitialProcess(void);
	//static UINT ThreadFun(LPVOID lParam);
	LRESULT OnThreadExit(WPARAM WP, LPARAM LP);	//WMU_THREAD_EXIT讯息的函数


	afx_msg void OnBnClickedButtonautostart();
	afx_msg void OnBnClickedButtonautostop();

	//initial works
	int InitWorkStation(bool* Continue, int workNum);
	int AutoWorkStation(bool* Continue, int workNum);
	/*int init1(int port, int workNum, bool* isContinue);
	int init2(int port, int workNum, bool* isContinue);
	int init3(int axisNum, int port, int workNum, bool* isContinue);
	int init4(int axisNum, int port, int workNum, bool* isContinue);
	int init5(int port, int workNum, bool* isContinue);
	int init6(int axisNum, int port, int workNum, bool* isContinue);
	int init7(int axisNum, int port, int workNum, bool* isContinue);
	int init8(int axisNum, int port, int workNum, bool* isContinue);
	int init9(int axisNum, int port, int workNum, bool* isContinue);
	int init10(int axisNum, int port, int workNum, bool* isContinue);
	int IOInit(int axisNum, int port, int workNum, bool* isContinue);*/

	//int autoRobot(int upOrDown, int port, int workNum, bool* isContinue);
	//int auto2(int axisNum, int port, int workNum, bool* isContinue, int round);
	//int auto3(int axisNum, int port, int workNum, bool* isContinue, int round);
	//int auto5(int axisNum, int port, int workNum, bool* isContinue);

	//int auto7(int axisNum, int port, int workNum, bool* isContinue, int round);
	//int auto8(int axisNum, int port, int workNum, bool* isContinue, int round);
	//int auto9(int axisNum, int port, int workNum, bool* isContinue, int round);

	//int auto10(int port, int workNum, bool* isContinue);
	//int auto11(int axisNum, int port, int workNum, bool* isContinue);

	//int autoGHOM(int axisNum, int port, int workNum, bool* isContinue);
	//	;
	//int auto12(int port, int workNum, bool* isContinue, int round);
	////int auto14(int axisNum, int port, int workNum, bool* isContinue);
	//

	//int autoSMOV(int axisNum, int port, int workNum, int absPos, bool* isContinue);
	//int autoTwoSMOV(int* axisNum, int port, int workNum, int* absPos, bool* isContinue);

	//int autoRelSMOV(int axisNum, int port, int workNum, int absPos, bool* isContinue);
	//int autoFFNL(int axisNum, int port, int workNum, bool* isContinue);

	//int autoSMOV456(int port, int workNum, bool* isContinue, int round);



	//auto process works
	//int init9(int axisNum, int port, int work);
	//int maniIsLoad(int axisNum, int port, int work);

	//int init10(int axisNum, int port, int work);
	int sensorTest(CString reValue, int* sensorValue);
	int m_sensorValue[3];

	//int openVoidAbsorb(int axisNum, int port, int work);
	//int mani6Down(int axisNum, int port, int work);
	//int mani3SpinDownAbsorb(int axisNum, int port, int work);
	//int prism4Extend(int axisNum, int port, int work);
	//int openUpLight(int axisNum, int port, int work);
	//int openDownLight(int axisNum, int port, int work);
	//int closeDownLight(int axisNum, int port, int work);
	//int prism4Leave(int axisNum, int port, int work);
	//int microXAdjust(int axisNum, int port, int work);
	//int microYAdjust(int axisNum, int port, int work);
	//int microSpecialAdjust(int pluseNum, int port, int workNum);
	//int imageProcess(DigHookDataStruct* DigUserHookData, PositionInfo* proResult, int work);


	//image process
	//int SingleModelExample(MIL_ID MilSystem, MIL_ID MilImage, MIL_ID MilOverlayImage, double* output);

//afx_msg void OnBnClickedButtonthreehand();
//afx_msg void OnBnClickedButtonthreehand();
	void SetAxisParameter(void);
	void updateAxisParameter2Value(AxisParameter* para, int* axis, int num, bool isSave);
	void updateValue2File(int* axis, int num, bool isSave);
	afx_msg void OnBnClickedButtonsetting();
	
	CAutoSettingDlg* m_settingDlg;
	void updateInitValue2File(int workNum, bool isSave);
	void SetInitAutoParameter(int workNum);
	void updateAutoValue2File(int workNum, int roundNum, int proNum, bool isSave);

	void sendSingleComm(CString comm, int portIndex);
	//void sendAnySingleComm(int devNum, CString comm, int port);

	int m_bContinueGrab[MAX_CAM];
	int switchLight(CButtonST* lightBst, bool isOpen);
	CString explainAxisCommand(CString comm1, CString comm2, CString comm3,CString commClass, CString commandName, int portIndex, bool*isContinue);
	CString explainAxisCommandNoValue(CString comm1, CString comm2, CString commClass, CString commandName, int portIndex, bool*isContinue);
	void sendComm(int devNum, CString comm, int portIndex);
	void sendComm(int devNum, CString comm, int axisNum, int portIndex);
	int sendAnySingleComm(int devNum, CString comm, int axisNum, int ivalue, bool existValue, int portIndex, bool* isContinue);
	int sendAnySingleComm(int devNum, CString comm, int portIndex, bool* isContinue);
	int sendAnySingleComm(CString comm, int portIndex, bool* isContinue);
	int GetPortIndex(int port);
	CString explainParameter(CString ParameterName, CString Sentence);
	int inquiryLim(int devNum, int axisNum, int portIndex, int limitType, bool* isContinue);
	int inquiryPos(int devNum, int axisNum, int portIndex, int stepvalue, bool* isContinue);
	int switchInquiry(int* devNum, CString* comm, int portIndex, int* verValue, int commNum, bool* isContinue);
	
	int inquiry(CString comm, int portIndex, int value, bool isPos, bool* isContinue);
	//int inquiry(CString comm, int portIndex, int value, bool isPos, bool* isContinue);
	int switchInquiry( CString* comm, int portIndex, int* verValue, int commNum, bool* isContinue);


	int Robot(CString data, int Num, bool* isContinue);
	int sendFileComm(CStdioFile* file, int workNum, int portIndex, bool* isContinue);
	int findChar(CString comm, char value, int number);
	int explainRobot(CStdioFile* file, int workNum, bool* isContinue);
	int explainInquiry(CStdioFile* file, int workNum, int portIndex, bool* Continue);
	int explainDelayTime(CStdioFile* file, int workNum);
	int explainImageErrorAndRatio(CStdioFile* file, int workNum);
	int explainOmissionDetection(CStdioFile* file, int workNum, bool* Continue);
	int explainImageProcessing(CStdioFile* file, int workNum, bool* Continue);
	int explainImageProcessing1(CStdioFile* file, int workNum, bool* Continue);
	int explainImageProcessing2(CStdioFile* file, int workNum, bool* Continue);
	int explainUnit(CStdioFile* file, int workNum, int portIndex, bool* Continue);
	//int OpenLight(int channelIndex,int intensity, int port);
	int explainLight(CStdioFile* file, int workNum, bool* Continue);
	int explainCommon(CStdioFile* file, int workNum, int portIndex, bool* isContinue);
	int explainSwitchInquiry(CStdioFile* file, int workNum, int portIndex, bool* Continue);
	int explainThreadInteraction(CStdioFile* file, int workNum, int portIndex, bool* Continue);
	int explainResultOfImagePro(CStdioFile* file, int workNum, int portIndex, bool* Continue);
	int explainResultOfImagePro1(CStdioFile* file, int workNum, int portIndex, bool* Continue);
	int explainResultOfImagePro2(CStdioFile* file, int workNum, int portIndex, bool* Continue);
	int explainControlDev(CStdioFile* file, int workNum, int portIndex, bool* Continue);
	int getPosition(CStdioFile* file, int workNum, CString comm, PositionInfo* value);

	
	int explainGoldBallBonding(CStdioFile* file, int workNum, int portIndex, bool* Continue);

	CString findCoron(CStdioFile* file);
	int findCoronNum(CStdioFile* file);
	bool findCoronNum(CStdioFile* file, int& num);
	bool ThreadState[MAX_CAM];
	int OpenLight(int channelIndex,int intensity, int port);

	CString m_fileComm[MAX_CAM];
	//int m_fileSteps[MAX_CAM];
	//int m_robotPara[MAX_CAM][3];

	bool m_LightPortState;
	bool m_LightChannelState[LIGHT_CHANNEL_NUM];
	OPTController_Handle m_OPTControllerHanlde;


	//read auto command

	COScopeCtrl m_OScopeCtrl;
	CProgressCtrl m_progress;
	CComboBox m_cmbPort[MAX_CAM+1];
	int m_portNum[portNum];
	int m_lightPort;
	CButtonST m_bstport;
	int m_commNum[MAX_CAM];
	//int m_commCount[MAX_CAM];
	//int m_robotPort;
	bool m_bConnect;

	void initPort(void);
//	afx_msg void OnCbnSelchangeComboPort1();
//	afx_msg void OnCbnSelchangeComboPort1();
//	afx_msg void OnCbnSelchangeComboPort2();
//	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButtonconnect();

	void sendGoldComm(CString comm, int portIndex);
	int explainGoldComm(CString comm, char* byteComm);

	SOCKET ListenSocket, ClientSocket;   
	bool m_SocketState;

	int SocketConnection();
	void SocketShutdown();
	int SocketSendData(CString data, bool* Continue);
	int SocketRecieveData(CString data, int count, bool* Continue);
	//void DigStartAcquisition(DigHookDataStruct* UserSt, int flag);


//	afx_msg void OnBnClickedButtonfit();
//	afx_msg void OnBnClickedButtondispenser();

	afx_msg void OnBnClickedButton2();
	afx_msg void OnFaultAnalysis();
	afx_msg void OnCbnSelchangeComboPort1();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnStnClickedStatic2();
//	CStatic m_Name;
//	CString m_Name;
	CString m_Name;
	afx_msg void OnBnClickedButtonlog();
	afx_msg void OnCbnSelchangeComboPort3();
	afx_msg void OnCbnSelchangeComboPort2();
	afx_msg void OnStnClickedDisp1();
	afx_msg void OnStnClickedDisp2();
	afx_msg void OnLbnSelchangeListLog();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();

	CString m_ProcessName1;
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton12();
	afx_msg void OnOpendata();
	int VoiceAlarm(int lt);
	afx_msg void OnRobottest();
	afx_msg void OnScript();
	afx_msg void OnStation1();
	afx_msg void OnStation2();
	afx_msg void OnVisiontest();
	
	CButtonST m_flowchart;
//	CStatic m_flowIcon11;
//	CStatic m_flowIcon21;
	afx_msg void OnBnClickedButtonflowchart();
	afx_msg void OnBnClickedButton15();

	afx_msg void OnBnClickedButtonEditor();
	CButtonST m_OpenDataBase;
	afx_msg void OnBnClickedButtonOpendatabase();

//	CStatic m_initTXT1;
//	CStatic m_autoTXT1;
//	CStatic m_initTXT2;
//	CStatic m_autoTXT2;
	//afx_msg void OnBnClickedButtonChangetxt1();
	afx_msg void OnBnClickedButtonChangeinittxt1();
	afx_msg void OnBnClickedButtonChangeinittxt2();
	//afx_msg void OnBnClickedButtonChangetxt2();
	afx_msg void OnBnClickedButtonChangeautotxt1();
	afx_msg void OnBnClickedButtonChangeautotxt2();
	
	afx_msg void OnStnClickedStatic04();
//	CButtonST m_light01;
//	CButtonST m_light02;
//	CButtonST m_light03;
//	CButtonST m_light04;
//	CButtonST m_light05;
	CString m_initTXT1;
	CString m_initTXT2;
	CString m_autoTXT1;
	CString m_autoTXT2;
	afx_msg void OnBnClickedButtonlight06();
	afx_msg void OnBnClickedButtonSuspend();

	BOOL ReadStringToUnicode(CString &str);
	int CharToUnicode(char *pchIn, CString *pstrOut);
	CString ChineseTransformation(CString str, CStdioFile* file);
	afx_msg void OnBnClickedButtoninitialization();
	afx_msg void OnBnClickedForcecontrol();
	afx_msg void OnCustomdrawProgress1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnOutofmemoryProgress1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnReleasedcaptureProgress1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnThemechangedProgress1(NMHDR* pNMHDR, LRESULT* pResult);
	//CIPAddressCtrl m_IOIP;
	//CIPAddressCtrl m_localIP;
	//CIPAddressCtrl m_IP1;
	CIPAddressCtrl mmmm;
	CIPAddressCtrl m_mineIP;
	CEdit m_answer;
	CIPAddressCtrl m_localIP;
	afx_msg void OnBnClickedButtonChangeautotxt3();
	afx_msg void OnStnClickedStaticautotxt3();
	
	afx_msg void OnBnClickedButtonstopcatch();
	afx_msg void OnBnClickedButtonsc();
};

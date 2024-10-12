#pragma once
#include "SerialPort.h"
#include "BtnST.h"

#define portNum 5
#define axisSum 27


#define axis1 1
#define axis2 2


#define axis3 3
#define axis4 4
#define axis5 5

#define axis6 6
#define axis7 7
#define axis8 8
#define axis9 9
#define axis10 10

#define portNum1 1  //control only 1 axis of work1 
#define portNum2 2  //control only 1 axis of work2
#define portNum3 3  //control  8 axises of work1 
#define portNum4 4  //control  8 axises of work2 
#define portNum5 5  //control  8 axises of work3 
#define portNum6 6  //control  only 1 axis of work3 
#define portNum7 7  //control  only 1 axis of work3 

#define	GRAB_NUM 10
#define MAX_CAM  3
//#define ROUND 7
#define PRONUM1 18
#define PRONUM2 8
#define CALIBRATION_NUM 5 
#define LIGHT_CHANNEL_NUM 5
#define UILIGHT_NUM 10
#define UNITLIGHT_NUM 11
#define UNITNAME_NUM 11
#define initStepNum 11


#define ERRO1 _T("返回数据错误")
#define loopTime 250
#define myStartTime 100
#define initFindTime 30

//角度补偿量、像素脉冲比例系数
#define ANG_ERROR         0.0
#define RATIO_X           1.0
#define RATIO_Y           1.0
#define RATIO_A           1.0


#define PING 'P'
#define BONDER_CFG 'C'
#define BUMP_PEG ('B'+'P') // 66 + 80 = 146 = 0x92
#define BALL_WEDGE ('B'+'W') // 66 + 87 = 153 = 0x99
#define RUN_MODE ('R'+'M') // 82 + 77 = 159 = 0x9F
#define FEAT_SETUP_MODE ('F'+'M') // 70 + 77 = 147 = 0x93
#define YES 'Y'
//#define NO 'N'
#define NO_STITCH ('N'+'S') // 78 + 83 = 161 = 0xA1
#define AUTO_STITCH ('A'+'S') // 65 + 83 = 148 = 0x94
#define MANUAL_STITCH ('M'+'S') // 77 + 83 = 160 = 0xA0
#define AUTO_MODE ('A'+'M') // 65 + 77 = 142 = 0x8E
#define MANUAL_MODE ('M'+'M') // 77 + 77 = 154 = 0x9A
#define BONDER_RESET 'R'
#define BOND_GO 'G'
#define MM_LOCK 'L'
#define BOND_DONE 'D'
#define BOND_CYCLE_DONE ('C'+'D') // 67 + 68 = 135 = 0x87
#define MOVE_Z 'Z'
#define MOVE_Z_UP '+'
#define MOVE_Z_DOWN '-'
#define MOVE_Z_FAST 'F'
#define MOVE_Z_SLOW 'S'


typedef struct
{
	int startSpeed;
	int targetSpeed;
	int accelSpeed;
	int steps;
	int mode;
} AxisParameter;

typedef struct
{
	int startspeed;
	int targetspeed;
	int accelspeed;
	int steps;
} AutoInitParameter;

typedef struct
{
	//int cameraSteps;
	//int axisYSteps;
	//int axisXSteps;
	//int axis6Steps;
	//int prismSteps;
	//int axis3Steps;
	//int axis8Steps;
	//int axis9Steps;

	double angelErrorX;
	double angelErrorY;
	double ratioX;
	double ratioY;
	double ratioA;
	
	double posX[CALIBRATION_NUM];
	double posY[CALIBRATION_NUM];
	double posA[CALIBRATION_NUM];

} InitParameter;

//typedef struct
//{
//
//	double angErrorX;
//	double angErrorY;
//	double ratioA;
//	double ratioX;
//	double ratioY;
//
//
//} AutoParameter;


typedef struct
{
	int proNum;//图像处理次数序号
	int searchSpeed;
	int searchSpeedMode;
	int maxMatchNum;
	int matchNum;
	CString modelFilePath;
	CString ImgSaveSeq;
	CString OMModelName;
	int smoothness;
	int iterationNum;
	int ROI_x;
	int ROI_y;
	int ROI_w;
	int ROI_h;
	int modelDistance;
	int MethodFlag;
	int ThresholdFlag;
	int SharpenFlag;
	int MedianFlag;
	int ThresholdValue;
	double FilterSmoothness;
	double ExtractionScale;
	double GapDistance;
	double GapContinuity;

} imageProcessPara1;

typedef struct
{
	int proNum;
	int ROI_x;
	int ROI_y;
	int ROI_w;
	int ROI_h;
	int iterationNum;
	int ThresholdFlag;
	int ThresholdValue;
	double FilterSmoothness;
	double ExtractionScale;
	double GapDistance;
	double GapContinuity;
	double CricleRadius_Low;
	double CricleRadius_High;

} imageProcessPara2;

typedef struct 
{
	double x; 
	double y; 
	double a;
} PositionInfo;

//typedef struct 
//{
//	int material;
//	int position;
//	int mirrorO;
//	int lightO;
//	int picture;
//	int lightC;
//	int mirrorC;
//	int XYZposition;
//	int fit;
//	int dispenser;
//} LightID;

typedef struct
{
	CButtonST material;
	CButtonST position;
	CButtonST mirrorO;
	CButtonST lightO;
	CButtonST picture;
	CButtonST lightC;
	CButtonST mirrorC;
	CButtonST XYZposition;
	CButtonST fit;
	CButtonST dispenser;
} LightCButtonST;


class CPublic
{
public:
	CPublic(void);
	~CPublic(void);

	static bool portIsOpen[portNum];
	static bool startReceive[portNum];
	static bool isSend[portNum];
	static CString receiveData[portNum];
	static int receiveCount[portNum];
	static int sendCount[portNum];
	static AxisParameter g_parameter[axisSum];
	//static LightID g_lightID[MAX_CAM];

	static bool bfindTerminator[portNum];

	static int commCount;



	//static CSerialPort serialPort[portNum];

	static void CString2char(CString str, char* charstr);
	static CString int2CString(int data);
	static CString double2CString(double data);

	static CString char2CString(char charByte);
	static CString char2CString(char* charByte, int charLen);
	static int explainLim(CString respond, int index);
	static CString explainStrPos(CString respond);
	static int explainIntPos(CString respond);
	static int explainInquiry(CString respond, int value, int type);
	static int explainRobot(CString respond, int index);

	static DWORD GetConfigString(LPCSTR lpSectionName, LPCSTR lpValueName, char *pszName, int nSize);
	static DWORD SetConfigString(LPCSTR lpSectionName, LPCSTR lpValueName, LPCSTR lpValue);

	//AUTO setting 
	static int stepsError;
	static double sensorError;
	static AutoInitParameter g_initParameter[MAX_CAM][initStepNum - 1];
	//static AutoParameter g_AutoParameter[MAX_CAM];
	static InitParameter g_newinitParameter[MAX_CAM];
	static int g_initIOPara[MAX_CAM];
	//static LightCButtonST g_lightBst[MAX_CAM];


	static imageProcessPara1 g_imagePara1[MAX_CAM];
	static imageProcessPara2 g_imagePara2[MAX_CAM];
	static PositionInfo g_imagePosInfo1[MAX_CAM][PRONUM1];
	static PositionInfo g_imagePosInfo2[MAX_CAM][PRONUM2];
	static int g_workNum;
	static int g_typeOfImagePro[MAX_CAM];
	//static int g_proNum;


	static bool g_buplight;
	static bool g_bdownlight;
	static int g_iLight;
	static bool g_bInhale1;
	static bool g_bInhale2;
	static int g_iInhale;
	static PositionInfo g_positionInfo[MAX_CAM];

	static void poscalc( PositionInfo* pic2, PositionInfo* pic3, int workNum, PositionInfo* result);
	static void angcalc(PositionInfo* pic1, PositionInfo* pic2, int workNum, PositionInfo* result);

	static BOOL openFile(CStdioFile* file, char* fileName);
	static CString pathSwitch(CString strPath);

	static CString initFileName1;//脚本文档名称
	static CString autoFileName1;
	static CString initFileName2;
	static CString autoFileName2;

};

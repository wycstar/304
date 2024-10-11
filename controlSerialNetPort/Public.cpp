#include "StdAfx.h"
#include "Public.h"
#include <math.h>


bool CPublic::portIsOpen[portNum] = {false};
bool CPublic::startReceive[portNum] = {false};
bool CPublic::bfindTerminator[portNum] = {false};
bool CPublic::isSend[portNum] = {false};
CString CPublic::receiveData[portNum] = {_T(""), _T("")};
int CPublic::receiveCount[portNum] = {0};
int CPublic::sendCount[portNum] = {0};
int CPublic::commCount = 0;
AxisParameter CPublic::g_parameter[axisSum] = {{0,0,0,0,0}};
//int CPublic::g_workNum = 0;
PositionInfo CPublic::g_positionInfo[MAX_CAM] = {{0,0,0}};
//PositionInfo CPublic::g_positionInfo = { 0,0,0 };


int CPublic::stepsError = 0;
double CPublic::sensorError = 0;

AutoInitParameter CPublic::g_initParameter[MAX_CAM][initStepNum - 1] = {{{0,0,0,0}}};
int CPublic::g_initIOPara[MAX_CAM] = {0};
//AutoParameter CPublic::g_AutoParameter[MAX_CAM] = {{0}};
InitParameter CPublic::g_newinitParameter[MAX_CAM] = {{0}};


imageProcessPara1 CPublic::g_imagePara1[MAX_CAM] = {{0}};//存储脚本信息参数的数组结构体变量
imageProcessPara2 CPublic::g_imagePara2[MAX_CAM] = {{0}};
PositionInfo CPublic::g_imagePosInfo1[MAX_CAM][PRONUM1] = { {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17},{0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17} };//存储结果的二维数组结构体变量
PositionInfo CPublic::g_imagePosInfo2[MAX_CAM][PRONUM2] = {{{0}}};
//LightCButtonST CPublic::g_lightBst[MAX_CAM] ={{NULL}};

bool CPublic::g_buplight = false;
bool CPublic::g_bdownlight = false;
int CPublic::g_iLight = 0;
bool CPublic::g_bInhale1 = false;
bool CPublic::g_bInhale2 = false;
int CPublic::g_iInhale = 0;
//double CPublic::imageProcessResult[3] = {0.0};

int CPublic::g_workNum = 0;
int CPublic::g_typeOfImagePro[MAX_CAM] ={0};
//int CPublic::g_proNum = 0;




//CSerialPort CPublic::serialPort[portNum] = {CSerialPort()};



CPublic::CPublic(void)
{
}

CPublic::~CPublic(void)
{
}

void CPublic::CString2char(CString str, char* charstr)
{

	int nLength = str.GetLength();
	int nBytes = WideCharToMultiByte(CP_ACP, 0, str, nLength, NULL, 0, NULL, NULL);
	//charstr = new char[ nBytes + 1];
	memset(charstr,0, nLength + 1);
	WideCharToMultiByte(CP_OEMCP, 0, str, nLength, charstr, nBytes, NULL, NULL);
	charstr[nBytes] = 0;

}
CString CPublic::int2CString(int data)
{
	CString a;
	a.Format(_T("%d"), data);
	return a;
}

CString CPublic::double2CString(double data)
{
	CString a;
	a.Format(_T("%.3f"), data);
	return a;
}

CString CPublic::char2CString(char charByte)
{
	CString str;
	str.Format(_T("%x"), (unsigned char)charByte);

	//temp = _T("ch");
	if (str.GetLength() != 2)
	{
		str = _T("0") + str;
	}
	return str;
}

CString CPublic::char2CString(char* charByte, int charLen)
{
	//将char数组转换为wchar_t数组  
	//int charLen = strlen(charByte); //计算pChar所指向的字符串大小，以字节为单位，一个汉字占两个字节  
	int len = MultiByteToWideChar(CP_ACP, 0, charByte, charLen, NULL, 0); //计算多字节字符的大小，按字符计算  
	wchar_t *pWChar = new wchar_t[len + 1]; //为宽字节字符数申请空间，  
	MultiByteToWideChar(CP_ACP, 0, charByte, charLen, pWChar, len); //多字节编码转换成宽字节编码  
	pWChar[len] = '\0';  

	//将wchar_t数组转换为CString  
	CString str;  
	str.Append(pWChar);  

	delete[] pWChar;  
	return str;  
}

/* index = -1 return negative position, 1 return positive position, 
0 return zero position, 2 return axis number */
//int CPublic::explainLim(CString respond, int index)
//{
//	CString subStr =_T("");
//
//	if (index == 2)
//	{		
//		AfxExtractSubString (subStr, (LPCTSTR)respond, 0, '=');
//		return _ttoi(subStr);
//	}
//
//	AfxExtractSubString (subStr, (LPCTSTR)respond, 1, '=');
//
//	if (index == 1)
//	{
//		return _ttoi(subStr.Left(1));
//	}	
//	if (index == 0)
//	{
//		return _ttoi(subStr.Mid(1,1));
//	}
//	if (index == -1)
//	{
//		return _ttoi(subStr.Right(1));
//	}
//
//	return -1;
//
//
//}


/* index = -1 return negative position, 1 return positive position, 
0 return zero position, 2 return axis number, 3 return the value */
int CPublic::explainLim(CString respond, int index)//-------------------------------lim查询处理函数
{

	int equal = respond.Find('='); 
	if (equal == -1 || respond.GetLength() == (equal+1))
	{
		return -1;
	}

	CString subStr = respond.Mid(equal + 1);

	int bitFlag = _ttoi(subStr);


	if (index == 1)     //positive position，the2th bit
	{
		return (bitFlag >> 2) & 0x01;
	}	
	else if (index == 0)   //zero position，the 1th bit
	{
		return (bitFlag >> 1) & 0x01;
	}
	else if (index == -1)   //negative position, the 0th bit
	{
		return bitFlag & 0x01;
	}else if (index == 2)
	{
		return _ttoi(respond.Left(equal)); //return axis number
	}
	else
	{
		return bitFlag;  //return the value
	}

}

int CPublic::explainInquiry(CString respond, int value, int type)
{
	int inquiryValue = 0;
	if (type == 0)
	{
		return explainLim(respond, value);
	}else
	{
		inquiryValue = explainIntPos(respond);
		if (inquiryValue == -1)
			return -1;

		if (type == 1)
		{
			if (abs(inquiryValue - value) < CPublic::stepsError)
				return 1;
			else
				return 0;
		}else if (type == 2)
		{
			if (inquiryValue == value)
				return 1;
			else
				return 0;
		}else if (type == 3)
		{
			if (abs(inquiryValue - abs(value)) < CPublic::stepsError)
				return 1;
			else
				return 0;
		}
		else
			return 0;
	
	}


}


CString CPublic::explainStrPos(CString respond)
{
	int index = respond.Find('='); 
	if (index == -1)
	{
		return _T("");
	}
	return respond.Mid(index + 1);
}

int CPublic::explainIntPos(CString respond)//接收到的数值
{
	int index = respond.Find('='); 
	if (index == -1)
	{
		return -1;
	}
	return _ttoi(respond.Mid(index + 1));
}


int CPublic::explainRobot(CString respond, int bitNum)
{
	int revalue = _ttoi(respond);
	
	return (revalue >> (bitNum - 1)) & 0x01;

}



DWORD CPublic::GetConfigString(LPCSTR lpSectionName, LPCSTR lpValueName, char *pszName, int nSize)
{
	char szPath[MAX_PATH];
	char *szTmp = NULL;

	HMODULE hMod = GetModuleHandle(NULL);

	memset(szPath, 0, MAX_PATH);
	if(hMod)
	{
		if(GetModuleFileNameA(hMod, szPath, MAX_PATH) > 0)
		{
			szTmp = strrchr(szPath, TEXT('\\'));
			*(szTmp + 1) = 0;
			//strcat(szPath, CONFIGFOLDER);
			strcat(szPath, "AxisParameter.ini");
		}
	}
	if(strlen(szPath) == 0)
	{
		//strcpy(szPath, CONFIGFOLDER);
		strcat(szPath, "AxisParameter.ini");
	}

	return GetPrivateProfileStringA(lpSectionName, lpValueName, "", pszName, nSize, szPath);
}


DWORD CPublic::SetConfigString(LPCSTR lpSectionName, LPCSTR lpValueName, LPCSTR lpValue)
{
	char szPath[MAX_PATH];
	char *szTmp = NULL;

	HMODULE hMod = GetModuleHandle(NULL);

	memset(szPath, 0, MAX_PATH);
	if(hMod)
	{
		if(GetModuleFileNameA(hMod, szPath, MAX_PATH) > 0)
		{
			szTmp = strrchr(szPath, TEXT('\\'));
			*(szTmp + 1) = 0;
			//strcat(szPath, CONFIGFOLDER);
			strcat(szPath, "AxisParameter.ini");
		}
	}
	if(strlen(szPath) == 0)
	{
		//strcpy(szPath, CONFIGFOLDER);
		strcat(szPath, "AxisParameter.ini");
	}

	return WritePrivateProfileStringA(lpSectionName, lpValueName, lpValue, szPath);

}




//角度调整计算函数定义，结果储存于posinf结构体result的a中
void CPublic::angcalc(PositionInfo* pic1, PositionInfo* pic2, int workNum, PositionInfo* result)

{
	double a1,a2,da;
	a1=pic1->a;
	a2=pic2->a;
	//a1= (a1>180) ? (a1-360): a1;
	//a2= (a2>180) ? (a2-360): a2;
	da=a1-a2;
	if (fabs(da) > 180)///////////////////
	{
		da = (da > 0) ? da - 360 : da + 360;
	}
	result->a=da*CPublic::g_newinitParameter[workNum].ratioA;
}

//位置调整计算函数定义，结果储存于posinf结构体result的x、y中
void CPublic::poscalc( PositionInfo* pic2, PositionInfo* pic3, int workNum, PositionInfo* result)

{
	double dx1,dy1,dx2,dy2;
	dx1=pic2->x - pic3->x;
	dy1=pic3->y - pic2->y;

	double angelErrorX = CPublic::g_newinitParameter[workNum].angelErrorX;
	double angelErrorY = CPublic::g_newinitParameter[workNum].angelErrorY;

	dx2=(dx1*cos(angelErrorX))-(dy1*sin(angelErrorX));
	dy2=(dx1*sin(angelErrorX))+(dy1*cos(angelErrorY));


	double ratiox = CPublic::g_newinitParameter[workNum].ratioX;
	double ratioy = CPublic::g_newinitParameter[workNum].ratioY;
	result->x=dx2 * ratiox;
	result->y=dy2 * ratioy;

}

BOOL CPublic::openFile(CStdioFile* file, char* fileName)
{
	char szPath[MAX_PATH];
	char *szTmp = NULL;


	HMODULE hMod = GetModuleHandle(NULL);

	memset(szPath, 0, MAX_PATH);
	if(hMod)
	{
		if(GetModuleFileNameA(hMod, szPath, MAX_PATH) > 0)
		{
			szTmp = strrchr(szPath, TEXT('\\'));
			*(szTmp + 1) = 0;
			//strcat(szPath, CONFIGFOLDER);
			strcat(szPath, fileName);
		}
	}
	if(strlen(szPath) == 0)
	{
		//strcpy(szPath, CONFIGFOLDER);
		strcat(szPath, fileName);
	}

	return file->Open((LPCTSTR)CPublic::char2CString(szPath, strlen(szPath)), CFile::modeRead);

	//file.SeekToEnd();

	//return WritePrivateProfileStringA(lpSectionName, lpValueName, lpValue, szPath);

}

CString CPublic::pathSwitch(CString strPath)//由于对路径的保存有转意字符'\'的问题，必须用'\\'。所以从界面上获取的路径，在进行保存的时候会有问题，需要添加一个'\'。
{
	int index = 0;
	int pos = 0;
	//CString strNewPath = strPath;
	while(1)
	{
		pos = strPath.Find('\\', index);

		if (pos == -1)
			break;
		strPath.Insert(pos, '\\');
		index = pos + 2;

	}

	return strPath;

}



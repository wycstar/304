#include "stdafx.h"
#include "IO.h"
//#include"IOControl.h"
//#include "Public.h"



#define MAX_RECLEN 100

#ifdef UNICODE
#define LoadLibrary LoadLibraryW
#else
#define LoadLibrary LoadLibraryA
#endif

CIO::CIO(void)
{
	m_dllStance = NULL;
	isConnect = false;
	isContinueReceive = false;
}


CIO::~CIO(void)
{
	if (isConnect)
		closePort();

}

void CIO::FreeLibraryDLL()
{
	if (m_dllStance != NULL)
	{
		FreeLibrary(m_dllStance);
		m_dllStance = NULL;
	}
}

int CIO::LoadLibraryDLL(CString strDLLPath)
{
	m_dllStance = LoadLibrary((strDLLPath));
	if ((m_dllStance) != NULL)
	{
		OpenNetPort = (pOpenNetPort)GetProcAddress(m_dllStance, "openNetPort");
		if (OpenNetPort == NULL)
		{
			AfxMessageBox(_T("OpenNetPort���ش���"));
			goto HP;
		}


		CloseNetPort = (pCloseNetPort)GetProcAddress(m_dllStance, "closeNetPort");
		if (CloseNetPort == NULL)
		{
			AfxMessageBox(_T("closeNetPort���ش���"));
			goto HP;
		}

		SendCommand = (pSendCommand)GetProcAddress(m_dllStance, "sendCommand");
		if (SendCommand == NULL)
		{
			AfxMessageBox(_T("sendCommand���ش���"));
			goto HP;
		}

		Set_NetIPAddress = (pSet_NetIPAddress)GetProcAddress(m_dllStance, "Set_NetIPAddress");
		if (Set_NetIPAddress == NULL)
		{
			AfxMessageBox(_T("Set_NetIPAddress���ش���"));
			goto HP;
		}

		Set_NetPort = (pSet_NetPort)GetProcAddress(m_dllStance, "Set_NetPort");
		if (Set_NetPort == NULL)
		{
			AfxMessageBox(_T("Set_NetIPAddress���ش���"));
			goto HP;
		}

		ReceiveComm = (pReceiveComm)GetProcAddress(m_dllStance, "receiveComm");
		if (ReceiveComm == NULL)
		{
			AfxMessageBox(_T("receiveComm���ش���"));
			goto HP;
		}

		GET_DevIP = (pGET_DevIP)GetProcAddress(m_dllStance, "GET_DevIP");
		if (GET_DevIP == NULL)
		{
			AfxMessageBox(_T("GET_DevIP���ش���"));
			goto HP;
		}

		GET_POS = (pGET_POS)GetProcAddress(m_dllStance, "GET_POS");
		if (GET_POS == NULL)
		{
			AfxMessageBox(_T("GET_POS���ش���"));
			goto HP;
		}

		GET_INP = (pGET_INP)GetProcAddress(m_dllStance, "GET_INP");
		if (GET_INP == NULL)
		{
			AfxMessageBox(_T("GET_INP���ش���"));
			goto HP;
		}

		GET_OUP = (pGET_OUP)GetProcAddress(m_dllStance, "GET_OUP");
		if (GET_OUP == NULL)
		{
			AfxMessageBox(_T("GET_OUP���ش���"));
			goto HP;
		}



		GET_SVL = (pGET_SVL)GetProcAddress(m_dllStance, "GET_SVL");
		if (GET_SVL == NULL)
		{
			AfxMessageBox(_T("GET_SVL���ش���"));
			goto HP;
		}



		GET_SVL = (pGET_SVL)GetProcAddress(m_dllStance, "GET_SVL");
		if (GET_SVL == NULL)
		{
			AfxMessageBox(_T("GET_SVL���ش���"));
			goto HP;
		}

		GET_TVL = (pGET_TVL)GetProcAddress(m_dllStance, "GET_TVL");
		if (GET_TVL == NULL)
		{
			AfxMessageBox(_T("GET_TVL���ش���"));
			goto HP;
		}

		GET_ACC = (pGET_ACC)GetProcAddress(m_dllStance, "GET_ACC");
		if (GET_ACC == NULL)
		{
			AfxMessageBox(_T("GET_ACC���ش���"));
			goto HP;
		}

		GET_ECO = (pGET_ECO)GetProcAddress(m_dllStance, "GET_ECO");
		if (GET_ECO == NULL)
		{
			AfxMessageBox(_T("GET_ECO���ش���"));
			goto HP;
		}

		GET_PKP = (pGET_PKP)GetProcAddress(m_dllStance, "GET_PKP");
		if (GET_PKP == NULL)
		{
			AfxMessageBox(_T("GET_PKP���ش���"));
			goto HP;
		}

		GET_PKD = (pGET_PKD)GetProcAddress(m_dllStance, "GET_PKD");
		if (GET_PKD == NULL)
		{
			AfxMessageBox(_T("GET_PKD���ش���"));
			goto HP;
		}

		GET_CVL = (pGET_CVL)GetProcAddress(m_dllStance, "GET_CVL");
		if (GET_CVL == NULL)
		{
			AfxMessageBox(_T("GET_CVL���ش���"));
			goto HP;
		}

		GET_PER = (pGET_PER)GetProcAddress(m_dllStance, "GET_PER");
		if (GET_PER == NULL)
		{
			AfxMessageBox(_T("GET_PER���ش���"));
			goto HP;
		}

		GET_TPS = (pGET_TPS)GetProcAddress(m_dllStance, "GET_TPS");
		if (GET_TPS == NULL)
		{
			AfxMessageBox(_T("GET_TPS���ش���"));
			goto HP;
		}

		GET_PEL = (pGET_PEL)GetProcAddress(m_dllStance, "GET_PEL");
		if (GET_PEL == NULL)
		{
			AfxMessageBox(_T("GET_PEL���ش���"));
			goto HP;
		}

		GET_STA = (pGET_STA)GetProcAddress(m_dllStance, "GET_STA");
		if (GET_STA == NULL)
		{
			AfxMessageBox(_T("GET_STA���ش���"));
			goto HP;
		}

		GET_SYS = (pGET_SYS)GetProcAddress(m_dllStance, "GET_SYS");
		if (GET_SYS == NULL)
		{
			AfxMessageBox(_T("GET_SYS���ش���"));
			goto HP;
		}

		GET_CardType = (pGET_CardType)GetProcAddress(m_dllStance, "GET_CardType");
		if (GET_CardType == NULL)
		{
			AfxMessageBox(_T("GET_CardType���ش���"));
			goto HP;
		}


		//AfxMessageBox("Load Library successfully!");
	}
	else
	{
	HP:
		AfxMessageBox(_T("Load Library Failed!")/*, "Error", MB_ICONERROR*/);
		return 0;
	}

	return 1;
}

void CIO::CString2char(CString str, char* charstr)
{

	int nLength = str.GetLength();
	int nBytes = WideCharToMultiByte(CP_ACP, 0, str, nLength, NULL, 0, NULL, NULL);
	//charstr = new char[ nBytes + 1];
	memset(charstr, 0, nLength + 1);
	WideCharToMultiByte(CP_OEMCP, 0, str, nLength, charstr, nBytes, NULL, NULL);
	charstr[nBytes] = 0;

}

CString CIO::int2CString(int data)
{
	CString a;
	a.Format(_T("%d"), data);
	return a;
}

CString CIO::char2CString(char charByte)
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

CString CIO::char2CString(char* charByte, int charLen)
{
	//��char����ת��Ϊwchar_t����  
	//int charLen = strlen(charByte); //����pChar��ָ����ַ�����С�����ֽ�Ϊ��λ��һ������ռ�����ֽ�  
	int len = MultiByteToWideChar(CP_ACP, 0, charByte, charLen, NULL, 0); //������ֽ��ַ��Ĵ�С�����ַ�����  
	wchar_t* pWChar = new wchar_t[len + 1]; //Ϊ���ֽ��ַ�������ռ䣬  
	MultiByteToWideChar(CP_ACP, 0, charByte, charLen, pWChar, len); //���ֽڱ���ת���ɿ��ֽڱ���  
	pWChar[len] = '\0';

	//��wchar_t����ת��ΪCString  
	CString str;
	str.Append(pWChar);

	delete[] pWChar;
	return str;
}

int CIO::LoadLibraryDLL()
{
	m_dllStance = LoadLibrary(_T("controlDevDll.dll"));
	int n = GetLastError();
	if ((m_dllStance) != NULL)
	{
		OpenNetPort = (pOpenNetPort)GetProcAddress(m_dllStance, "openNetPort");
		if (OpenNetPort == NULL)
		{
			AfxMessageBox(_T("OpenNetPort���ش���"));
			goto HP;
		}


		CloseNetPort = (pCloseNetPort)GetProcAddress(m_dllStance, "closeNetPort");
		if (CloseNetPort == NULL)
		{
			AfxMessageBox(_T("closeNetPort���ش���"));
			goto HP;
		}

		SendCommand = (pSendCommand)GetProcAddress(m_dllStance, "sendCommand");
		if (SendCommand == NULL)
		{
			AfxMessageBox(_T("sendCommand���ش���"));
			goto HP;
		}

		Set_NetIPAddress = (pSet_NetIPAddress)GetProcAddress(m_dllStance, "Set_NetIPAddress");
		if (Set_NetIPAddress == NULL)
		{
			AfxMessageBox(_T("Set_NetIPAddress���ش���"));
			goto HP;
		}

		Set_NetPort = (pSet_NetPort)GetProcAddress(m_dllStance, "Set_NetPort");
		if (Set_NetPort == NULL)
		{
			AfxMessageBox(_T("Set_NetIPAddress���ش���"));
			goto HP;
		}

		ReceiveComm = (pReceiveComm)GetProcAddress(m_dllStance, "receiveComm");
		if (ReceiveComm == NULL)
		{
			AfxMessageBox(_T("receiveComm���ش���"));
			goto HP;
		}

		GET_DevIP = (pGET_DevIP)GetProcAddress(m_dllStance, "GET_DevIP");
		if (GET_DevIP == NULL)
		{
			AfxMessageBox(_T("GET_DevIP���ش���"));
			goto HP;
		}

		GET_POS = (pGET_POS)GetProcAddress(m_dllStance, "GET_POS");
		if (GET_POS == NULL)
		{
			AfxMessageBox(_T("GET_POS���ش���"));
			goto HP;
		}



		GET_SVL = (pGET_SVL)GetProcAddress(m_dllStance, "GET_SVL");
		if (GET_SVL == NULL)
		{
			AfxMessageBox(_T("GET_SVL���ش���"));
			goto HP;
		}

		GET_TVL = (pGET_TVL)GetProcAddress(m_dllStance, "GET_TVL");
		if (GET_TVL == NULL)
		{
			AfxMessageBox(_T("GET_TVL���ش���"));
			goto HP;
		}

		GET_ACC = (pGET_ACC)GetProcAddress(m_dllStance, "GET_ACC");
		if (GET_ACC == NULL)
		{
			AfxMessageBox(_T("GET_ACC���ش���"));
			goto HP;
		}

		GET_ECO = (pGET_ECO)GetProcAddress(m_dllStance, "GET_ECO");
		if (GET_ECO == NULL)
		{
			AfxMessageBox(_T("GET_ECO���ش���"));
			goto HP;
		}

		GET_PKP = (pGET_PKP)GetProcAddress(m_dllStance, "GET_PKP");
		if (GET_PKP == NULL)
		{
			AfxMessageBox(_T("GET_PKP���ش���"));
			goto HP;
		}

		GET_PFF = (pGET_PFF)GetProcAddress(m_dllStance, "GET_PFF");
		if (GET_PFF == NULL)
		{
			AfxMessageBox(_T("GET_PFF���ش���"));
			goto HP;
		}

		GET_PKD = (pGET_PKD)GetProcAddress(m_dllStance, "GET_PKD");
		if (GET_PKD == NULL)
		{
			AfxMessageBox(_T("GET_PKD���ش���"));
			goto HP;
		}

		GET_CVL = (pGET_CVL)GetProcAddress(m_dllStance, "GET_CVL");
		if (GET_CVL == NULL)
		{
			AfxMessageBox(_T("GET_CVL���ش���"));
			goto HP;
		}

		GET_PER = (pGET_PER)GetProcAddress(m_dllStance, "GET_PER");
		if (GET_PER == NULL)
		{
			AfxMessageBox(_T("GET_PER���ش���"));
			goto HP;
		}

		GET_TPS = (pGET_TPS)GetProcAddress(m_dllStance, "GET_TPS");
		if (GET_TPS == NULL)
		{
			AfxMessageBox(_T("GET_TPS���ش���"));
			goto HP;
		}

		GET_PEL = (pGET_PEL)GetProcAddress(m_dllStance, "GET_PEL");
		if (GET_PEL == NULL)
		{
			AfxMessageBox(_T("GET_PEL���ش���"));
			goto HP;
		}

		GET_STA = (pGET_STA)GetProcAddress(m_dllStance, "GET_STA");
		if (GET_STA == NULL)
		{
			AfxMessageBox(_T("GET_STA���ش���"));
			goto HP;
		}

		GET_SYS = (pGET_SYS)GetProcAddress(m_dllStance, "GET_SYS");
		if (GET_SYS == NULL)
		{
			AfxMessageBox(_T("GET_SYS���ش���"));
			goto HP;
		}

		GET_CardType = (pGET_CardType)GetProcAddress(m_dllStance, "GET_CardType");
		if (GET_CardType == NULL)
		{
			AfxMessageBox(_T("GET_CardType���ش���"));
			goto HP;
		}


		//AfxMessageBox("Load Library successfully!");
	}
	else
	{
	HP:
		AfxMessageBox(_T("Load Library Failed!")/*, "Error", MB_ICONERROR*/);
		return 0;
	}

	return 1;
}

int CIO::sendComm(CString strDevIP, CString comm)
{
	char* charIP = new char[strDevIP.GetLength() + 1];
	char* charComm = new char[comm.GetLength() + 1];

	CString2char(strDevIP, charIP);
	CString2char(comm, charComm);

	int len = SendCommand(charIP, charComm);
	delete charIP;
	delete charComm;
	return len;
}

int CIO::openPort(CString strLocalIP, int port)
{
	if (!LoadLibraryDLL(_T("controlDevDll.dll")))
		return 0;

	char* charIP = new char[strLocalIP.GetLength() + 1];

	CString2char(strLocalIP, charIP);


	int len = OpenNetPort(charIP, port);

	if (len)
	{
		isConnect = true;
		isContinueReceive = true;
		::AfxBeginThread(_RecThread, (LPVOID)this);

	}
	delete charIP;


	//�򿪽����߳�
	return len;
}



static UINT _RecThread(LPVOID lparam)	/////UDP������Ϣ�߳̿�ʼ
{

	CIO* recSocket = (CIO*)lparam;


	//char buff[1000] = { 0 };
	int ret = 0;

	while ((recSocket->isContinueReceive) && (recSocket->m_dllStance != NULL))
	{
		int len = recSocket->ReceiveComm();
		if (len == 0)
		{
			continue;
		}

		Sleep(15);

	}
	return 0;
}

static UINT _RecThread2(LPVOID lparam)	/////UDP������Ϣ�߳̿�ʼ
{

	CIO* recSocket = (CIO*)lparam;


	//char buff[1000] = { 0 };
	int ret = 0;

	while ((recSocket->isContinueReceive) && (recSocket->m_dllStance != NULL))
	{
		int len = recSocket->ReceiveComm();
		if (len == 0)
		{
			continue;
		}

		Sleep(15);

	}
	return 0;
}

static UINT _RecThread3(LPVOID lparam)	/////UDP������Ϣ�߳̿�ʼ
{

	CIO* recSocket1 = (CIO*)lparam;


	//char buff[1000] = { 0 };
	int ret = 0;

	while ((recSocket1->isContinueReceive) && (recSocket1->m_dllStance != NULL))
	{
		int len = recSocket1->ReceiveComm();
		if (len == 0)
		{
			continue;
		}
		else
		{
			CString message;
			message.Format(_T("%d"), len);
			AfxMessageBox(message);
		}


		Sleep(15);

	}
	return 0;
}

void CIO::closePort()
{
	if (isConnect == true)
		CloseNetPort();

	isContinueReceive = false;
	isConnect = false;
	FreeLibraryDLL();



}

void CIO::setNetIPAddress(CString IPAddr)
{
	char* charIP = new char[IPAddr.GetLength() + 1];
	CString2char(IPAddr, charIP);
	Set_NetIPAddress(charIP);
	delete charIP;
}

CString CIO::getDevIP()
{
	char charIP[20];
	int len = GET_DevIP(charIP);
	if (len == 0)
		return _T("");
	else
		return char2CString(charIP, len);

}

//���룺strDevIP comm
//�����16���ȵ�bool����IOBitValues����0�������Ӧio�ĵ�1���أ���1��ʼ��
//����ֵ����ѯ�Ƿ�ɹ�
bool CIO::inquiryIO(CString strDevIP, CString comm, bool* IOBitValues)
{
	if (sendComm(strDevIP, comm) == -1)
		return false;

	Sleep(50);

	int data[6] = { 0 };
	if (comm == "IN?")
	{
		if (GET_INP(data, 6) == 0)
			return false;

	}
	else if (comm == "OP?")
	{
		if (GET_OUP(data, 6) == 0)
			return false;
	}

	for (int i = 0; i < 16; i++)
	{
		IOBitValues[i] = ((data[0] & (0x01 << i)) == 0) ? false : true;   //0x01<<i��ʾ��0x01����iλ
	}

	return true;

}

bool CIO::inquiryAxisPOS(CString strDevIP, CString comm, int* IOBitValues)
{
	if (sendComm(strDevIP, comm) == -1)
		return false;

	Sleep(50);

	int data[6] = { 0 };
	if (comm == "TR?")//��ѯĿ��λ��
	{
		if (GET_TPS(data, 6) == 0)
			return false;

	}
	else if (comm == "GS?")//������ѯλ��,��ѯ������������λ״̬
	{
		if (GET_STA(data, 6) == 0)
			return false;
	}

	else
	{
		if (GET_POS(data, 6) == 0)//��ѯ��ǰλ��
			return false;
	}

	for (int i = 0; i < 6; i++)
	{
		IOBitValues[i] = data[i];   //0x01<<i��ʾ��0x01����iλ
	}

	return true;

}


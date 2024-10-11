#pragma once


static UINT _RecThread(LPVOID lparam);

class CIO
{

public:
	CIO(void);
	~CIO(void);

	HINSTANCE m_dllStance;
	bool isConnect;
	bool isContinueReceive;

	int LoadLibraryDLL(CString strDLLPath);
	int LoadLibraryDLL();
	void FreeLibraryDLL();

	//º”Ω‚√‹
	typedef int	(CALLBACK* pOpenNetPort)(char* localIPAddr, int localPort);
	typedef void (CALLBACK* pCloseNetPort)();
	typedef int (CALLBACK* pSendCommand)(char* devIPAddr, char* Comm);
	typedef int (CALLBACK* pReceiveComm)();

	typedef void (CALLBACK* pSet_NetIPAddress)(char* IPAddr);
	typedef void (CALLBACK* pSet_NetPort)(int port);
	typedef int (CALLBACK* pGET_DevIP)(char* devIPAddress);
	typedef int (CALLBACK* pGET_POS)(int data[], int dataLength);
	typedef int (CALLBACK* pGET_INP)(int data[], int dataLength);
	typedef int (CALLBACK* pGET_OUP)(int data[], int dataLength);

	typedef int (CALLBACK* pGET_SVL)(int data[], int dataLength);
	typedef int (CALLBACK* pGET_TVL)(int data[], int dataLength);
	typedef int (CALLBACK* pGET_ACC)(int data[], int dataLength);
	typedef int (CALLBACK* pGET_ECO)(int data[], int dataLength);
	typedef int (CALLBACK* pGET_PKP)(int data[], int dataLength);
	typedef int (CALLBACK* pGET_PFF)(int data[], int dataLength);
	typedef int (CALLBACK* pGET_PKD)(int data[], int dataLength);
	typedef int (CALLBACK* pGET_CVL)(int data[], int dataLength);
	typedef int (CALLBACK* pGET_PER)(int data[], int dataLength);
	typedef int (CALLBACK* pGET_TPS)(int data[], int dataLength);
	typedef int (CALLBACK* pGET_PEL)(int data[], int dataLength);
	typedef int (CALLBACK* pGET_STA)(int data[], int dataLength);
	typedef int (CALLBACK* pGET_SYS)();
	typedef int (CALLBACK* pGET_CardType)();


public:

	//int InitLoadDll(CString AlgID);
	pOpenNetPort OpenNetPort;
	pCloseNetPort CloseNetPort;
	pSendCommand SendCommand;
	pSet_NetIPAddress Set_NetIPAddress;
	pSet_NetPort Set_NetPort;
	pReceiveComm ReceiveComm;

	pGET_DevIP GET_DevIP;
	pGET_POS GET_POS;
	pGET_INP GET_INP;
	pGET_OUP GET_OUP;

	pGET_SVL GET_SVL;
	pGET_TVL GET_TVL;
	pGET_ACC GET_ACC;
	pGET_ECO GET_ECO;
	pGET_PKP GET_PKP;
	pGET_PFF GET_PFF;
	pGET_PKD GET_PKD;
	pGET_CVL GET_CVL;
	pGET_PER GET_PER;
	pGET_TPS GET_TPS;
	pGET_PEL GET_PEL;
	pGET_STA GET_STA;
	pGET_SYS GET_SYS;
	pGET_CardType GET_CardType;

	int openPort(CString strLocalIP, int port);
	void closePort();
	int sendComm(CString strDevIP, CString comm);
	int sendCommAxis(CString strDevIP, CString comm);
	void setNetIPAddress(CString IPAddr);
	CString getDevIP();

	void CString2char(CString str, char* charstr);
	CString int2CString(int data);
	CString char2CString(char charByte);
	CString char2CString(char* charByte, int charLen);


	bool inquiryIO(CString strDevIP, CString comm, bool* IOBitValues);
	bool inquiryAxisPOS(CString strDevIP, CString comm, int* IOBitValues);

};


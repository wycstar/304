#ifndef _USB3200_DEVICE_
#define _USB3200_DEVICE_

#include "windows.h"

// #################### ���Ի����������Ͷ��� #####################
// Humanized data types definition
typedef char				I8;		// 8λ�з�����������
typedef unsigned char		U8;		// 8λ�޷�����������
typedef short				I16;	// 16λ�з�����������
typedef unsigned short		U16;	// 16λ�޷�����������
typedef long				I32;	// 32λ�з�����������
typedef unsigned long		U32;	// 32λ�޷�����������
typedef __int64				I64;	// 64λ�з�����������
typedef unsigned __int64	U64;	// 64λ�޷�����������
typedef float				F32;	// 32λ��������(�����ȣ�ͬΪlabVIEW�е�SGL)
typedef double				F64;	// 64λ��������(˫���ȣ�ͬΪlabVIEW�е�DBL)

// ########################## �豸����ָ�� ########################
#define USB3200_MAX_AI_CHANNELS	8 // �������֧��8��ģ��������ͨ��
#define USB3200_MAX_DIO_CHANNELS 4 // �������֧��4��������˫��ͨ��

// ############# AI���������ṹ��USB3200_AI_PARAM���� #############
typedef struct _USB3200_AI_CH_PARAM // AIͨ�������ṹ��
{
	U32 nChannel;			// ͨ����[0, 7]���ֱ��ʾ����ͨ����AI0��AI7
	U32 nSampleGain;		// �������棬����Ŵ�����ο����泣������
	U32 nRefGround;			// �زο���ʽ
	U32 nReserved0;			// ����(δ��)
} USB3200_AI_CH_PARAM, *PUSB3200_AI_CH_PARAM;

// AIӲ��ͨ������USB3200_AI_CH_PARAM�е�nSampleGainģ��������Ŵ�����ʹ�õ�ѡ��
#define USB3200_AI_SAMPGAIN_1MULT			0 // 1������
#define USB3200_AI_SAMPGAIN_2MULT			1 // 2������
#define USB3200_AI_SAMPGAIN_4MULT			2 // 4������
#define USB3200_AI_SAMPGAIN_8MULT			3 // 8������

// AIӲ��ͨ�������ṹ��USB3200_AI_CH_PARAM�е�nRefGround������ʹ�õĵزο�ѡ��
#define USB3200_AI_REFGND_RSE			0 // �ӵزο�����(Referenced Single Endpoint)
#define USB3200_AI_REFGND_NRSE			1 // �ǲο�����(Non Referenced Single Endpoint)
#define USB3200_AI_REFGND_DIFF			2 // ���(Differential)

typedef struct _USB3200_AI_PARAM // ������AI�йص�Ӳ����������(���AI��������)
{
	U32 nSampleMode;		// ����ģʽ, 0=�������(����)�� 1=��������
	U32 nPointsPerChan;		// ÿ��ͨ����������(Ҳ��ÿͨ������ȡ����),ȡֵ��ΧΪ[256, 8192],����nChannelCount�ĳ˻����ܴ���65536
	F64 fSampleRate;		// ��������(Sample Rate), ��λΪsps��ȡֵ��ΧΪ[1sps, 500000sps],����ÿ������ͨ���Ĳ�������, ����nChannelCount�ĳ˻����ܴ���500000sps
	U32 nSampChanCount;     // ����ͨ������[1, 8](�˲����ڵ��������Ч��δ��ע���Ĳ������ڵ������ģʽ����Ч)
	U32 nReserved0;			// �����ֶ�(��δ����)
	USB3200_AI_CH_PARAM CHParam[8]; // ͨ����������(�˲����ڵ��������Ч��δ��ע���Ĳ������ڵ������ģʽ����Ч)
	U32 nGroupLoops;		// ������ĩͨ��ѭ������[1, 65535]
	U32 nGroupInterval;     // ������֮���ʱ����, ��λ��΢�룬ȡֵ��Χ[0, 107374182], ����0ʱ��ʾ�ȼ������(������,��ʱnGroupLoopsӦ����1)

	U32 bDTriggerEn;		// ���ִ���DTR����(Digital Trigger Enable), =FALSE:��ʾ��ֹ; =TRUE:��ʾ����,�����ź���������CN2�ϵ�DIO1�������룬��˳�ʼ��ʱ�ὫDIO1�ķ���ǿ����Ϊ����
	U32 nDTriggerType;	    // ���ִ�������(Digital Trigger Type)
	U32 nDTriggerDir;	    // ���ִ�������(Digital Trigger Direction)

	U32 bATriggerEn;		// ģ�����ִ���ATR����(Analog Trigger Enable), =TRUE:��ʾ����, =FALSE:��ʾ��ֹ
	U32 nATriggerType;		// ģ�ⴥ������(Analog Trigger Type)
	U32 nATriggerDir;		// ģ�ⴥ������(Analog Trigger Direction)
	U32 nATrigChannel;		// ����ͨ��(Analog Trigger Channel)
	F32 fTriggerLevel;		// ������ƽ(Trigger Level)
	U32 nTriggerSens;		// ����������(Trigger Sensitive for Digital and Analog trigger),��λ��΢��(uS)��ȡֵ��Χ[0, 1638]

	U32 nSampleRange;		// ������Χ(Sample Range), ��������泣��������(�˲����ڵ��������Ч��δ��ע���Ĳ������ڵ������ģʽ����Ч)
	U32 nClockSource;		// ʱ��Դѡ��, =0:��ʱ��OSCCLK; =1:��ʱ��CLKIN,��������CN2�ϵ�DIO2/CLKIN�������룬��˳�ʼ��ʱ�ὫDIO2�ķ���ǿ����Ϊ����
	U32 bClockOutput;		// ����ʱ���������, =0:��ʾ��ֹ; =1:��ʾ����,��������CN2��DIO3/CLKOUT�����������˳�ʼ��ʱ�ὫDIO3�ķ���ǿ����Ϊ���

	U32 nReserved1;			// �����ֶ�(��δ����)
	U32 nReserved2;			// �����ֶ�(��δ����)
	U32 nReserved3;			// �����ֶ�(��δ����)
	U32 nReserved4;			// �����ֶ�(��δ����)
} USB3200_AI_PARAM, *PUSB3200_AI_PARAM;

// AIӲ�������ṹ��USB3200_AI_PARAM�е�nSampleMode����ģʽ��ʹ�õ�ѡ��
#define USB3200_AI_SAMPMODE_ONE_DEMAND	0 // �������(����)
#define USB3200_AI_SAMPMODE_CONTINUOUS	1 // ��������

// AIӲ�������ṹ��USB3200_AI_PARAM�е�nATriggerType/nDTriggerType����������ʹ�õ�ѡ��
#define USB3200_AI_TRIGTYPE_EDGE		0 // ���ش���
#define USB3200_AI_TRIGTYPE_LEVEL		1 // ��ƽ����

// AIӲ�������ṹ��USB3200_AI_PARAM�е�nDTriggerDir����������ʹ�õ�ѡ��
#define USB3200_AI_TRIGDIR_FALLING		0 // �½���/�͵�ƽ
#define USB3200_AI_TRIGDIR_RISING		1 // ������/�ߵ�ƽ
#define USB3200_AI_TRIGDIR_CHANGE		2 // �仯(�����±���/�ߵ͵�ƽ����Ч)

// AIӲ�������ṹ��USB3200_AI_PARAM�е�nSampleRange������ʹ�õ�ģ�������������Χѡ��
#define USB3200_AI_SAMPRANGE_N10_P10V		0 // ��10V
#define USB3200_AI_SAMPRANGE_N5_P5V			1 // ��5V
#define USB3200_AI_SAMPRANGE_N2D5_P2D5V		2 // ��2.5V
#define USB3200_AI_SAMPRANGE_0_P10V			3 // 0-10V

// AIӲ�������ṹ��USB3200_AI_PARAM�е�nClockSourceʱ��Դ��ʹ�õ�ѡ��
#define USB3200_AI_CLKSRC_LOCAL			0 // ����ʱ��(ͨ��Ϊ���ؾ���ʱ��OSCCLK),Ҳ���ڲ�ʱ��
#define USB3200_AI_CLKSRC_CLKIN			1 // �ⲿʱ��(��������CN2�ϵ�DIO2/CLKIN��������)

// #################### AI����״̬�ṹ��USB3200_AI_STATUS���� #####################
typedef struct _USB3200_AI_STATUS
{
	U32 bSampling;				// ������־, =TRUE:��ʾ���ڲ���, =FALSE:��ʾ��������(��δ����)
	U32 bTriggered;				// ������־, =TRUE:��ʾ�ѱ�����, =FALSE:��ʾδ������(�����ȴ�����)

	U32 nSampTaskState;			// ��������״̬, =1:����, ����ֵ��ʾ���쳣���
	U32 nReadableSegments;		// �ɶ�������ֻ��������0ʱ���ܵ���AI_ContReadChannels()��ȡ����������
	U32 nMaxReadableSegs;		// ��AI_Start()����ֹ������ɶ�������״ֵ̬��Χ[0, nUsableSegments],����Ϊ������Ĳɼ�������ܶ��ṩ�������ֵԽ������1�����ʾ��ζ������Խ�ߣ�Խ���׳����������Ŀ���
	U32 nSampledSegments;		// �Ѳ�������(������AI_Start()֮���������Ķ���)�����ֻ�Ǹ��û���ͳ������
	U32 nUsableSegments;		// ϵͳ֧�ֵĿ��ö���,ȡֵһ��Ϊ16��32��64�ȡ�

	U32 nHardOverflowCnt;		// Ӳ���������(�ڲ��������º����0)
	U32 nSoftOverflowCnt;		// ����������(�ڲ��������º����0)
	U32 nTransRate;				// ��������(����AI��������), ��ÿ�봫�����(sps)����ΪUSB��Ӧ������������ܵļ����Ϣ

	U32 nReserved0;				// �����ֶ�(��δ����)
	U32 nReserved1;				// �����ֶ�(��δ����)
} USB3200_AI_STATUS, *PUSB3200_AI_STATUS;

// #################### AI��Ҫ��Ϣ�ṹ��(USB3200_AI_MAIN_INFO) #######################
typedef struct _USB3200_AI_MAIN_INFO
{
	U32 nChannelCount;		// AIͨ������
	U32 nSampRangeCount;	// AI������Χ��λ����
	U32 nSampGainCount;		// AI�������浲λ����
	U32 nCouplingCount;		// AI��ϵ�λ����
	U32 nImpedanceCount;	// AI�迹�ĵ�λ����
	U32 nDepthOfMemory;		// AI���ش洢�����(����)
	U32 nSampResolution;	// AI�����ֱ���(��=8��ʾ8Bit; =12��ʾ12Bit; =14��ʾ14Bit; =16��ʾ16Bit)
	U32 nSampCodeCount;		// AI������������(��256, 4096, 16384, 65536)
	U32 nTrigLvlResolution;	// ������ƽ�ֱ���(��=8��ʾ8Bit; =12��ʾ12Bit; =16��ʾ16Bit)
	U32 nTrigLvlCodeCount;	// ������ƽ��������(��256, 4096)

	U32 nReserved0;			// �����ֶ�(��δ����)
	U32 nReserved1;			// �����ֶ�(��δ����)
} USB3200_AI_MAIN_INFO, *PUSB3200_AI_MAIN_INFO;

// #################### AI������Χ��Ϣ�ṹ��(USB3200_AI_SAMP_RANGE_INFO) #######################
typedef struct _USB3200_AI_SAMP_RANGE_INFO
{
	U32 nSampleRange;		// ��ǰ������Χ��λ��
	U32 nReserved0;			// �����ֶ�(��δ����)
	F64 fMaxVolt;			// ������Χ������ѹֵ,��λ:��(V)
	F64 fMinVolt;			// ������Χ����С��ѹֵ,��λ:��(V)
	F64 fAmplitude;			// ������Χ����,��λ:��(V)
	F64 fHalfOfAmp;			// ������Χ���ȵĶ���֮һ,��λ:��(V)
	F64 fCodeWidth;			// ������,��λ:��(V), ��ÿ����λ��ֵ������ĵ�ѹֵ
	U32 nPolarity;			// ������Χ�ļ���(0=˫����BiPolar, 1=������UniPolar)
	
	U32 nReserved1;			// �����ֶ�(��δ����)
} USB3200_AI_SAMP_RANGE_INFO, *PUSB3200_AI_SAMP_RANGE_INFO;

// �ṹ��AI_RANGE_INFO�����ݳ�ԱPolarity���õ����뼫��ѡ��
#define USB3200_AI_POLAR_BIPOLAR	0 // ˫����
#define USB3200_AI_POLAR_UNIPOLAR	1 // ������

// #################### AI����������Ϣ�ṹ��(USB3200_AI_SAMP_GAIN_INFO) #######################
typedef struct _USB3200_AI_SAMP_GAIN_INFO
{
	U32 nSampleGain;		// ��ǰ�������浲λ��
	U32 nReserved0;			// �����ֶ�(��δ����)
	F64 fAmpFactor;			// �Ŵ���(Amplification Factor)

	U32 nReserved1;			// �����ֶ�(��δ����)
	U32 nReserved2;			// �����ֶ�(��δ����)
} USB3200_AI_SAMP_GAIN_INFO, *PUSB3200_AI_SAMP_GAIN_INFO;

// #################### AI����������Ϣ�ṹ��(USB3200_AI_SAMP_RATE_INFO) #######################
typedef struct _USB3200_AI_SAMP_RATE_INFO
{
	F64 fMaxRate;		// ��ͨ������������(sps)����ͨ��ʱ��ͨ��ƽ����������
	F64 fMinRate;		// ��ͨ����С��������(sps)����ͨ��ʱ��ͨ��ƽ����С������
	F64 fTimerBase;		// ʱ�ӻ�׼�������ؾ���Ƶ�ʣ���λ��Hz
	U32 nDivideMode;	// ��Ƶģʽ��0=������Ƶ(INTDIV), 1=DDS��Ƶ(DDSDIV)

	U32 nReserved0;		// �����ֶ�(��δ����)
	U32 nReserved1;		// �����ֶ�(��δ����)
	U32 nReserved2;		// �����ֶ�(��δ����)
} USB3200_AI_SAMP_RATE_INFO, *PUSB3200_AI_SAMP_RATE_INFO;

// ###################### CTR���������ṹ��(USB3200_CTR_PARAM) #######################
typedef struct _USB3200_CTR_PARAM // ������CTR�йص�Ӳ����������(���CTR��������)
{
	U32 nPulseDir;		// ���巽��(0=�½���,1=������, 2=˫����)
	U32 bInitReset;		// �Ƿ��ڳ�ʼ��ʱ��λ��������0��=TRUE:��ʼ��ʱ���������, =FALSE:��ʼ���ǲ���
	U32 bFullReset;		// �Ƿ������ʱ�Զ���λ��������0��=TRUE:���ʱ�Զ���λ��0, =FALSE:�����ʱ��ס��ǰ��������

	U32 nReserved0;		// �����ֶ�(��δ����)
	U32 nReserved1;		// �����ֶ�(��δ����)
	U32 nReserved2;		// �����ֶ�(��δ����)
} USB3200_CTR_PARAM, *PUSB3200_CTR_PARAM;

// CTRӲ�������ṹ��USB3200_CTR_PARAM�е�nPulseDir���巽����ʹ�õ�ѡ��
#define USB3200_CTR_PULSEDIR_FALLING	0 // �±���
#define USB3200_CTR_PULSEDIR_RISING		1 // �ϱ���
#define USB3200_CTR_PULSEDIR_CHANGE		2 // �仯(���±��ؾ���Ч)

// #################### DIO��Ҫ��Ϣ�ṹ��(USB3200_DIO_PARAM) #######################
typedef struct _USB3200_DIO_PARAM // ������DIO�йص�Ӳ����������(���DIO��������)
{
	U8 bOutputEn[4];	// �����������(Output Enable),bOutputEn[n]=0:�����ֹ(��Ϊ����)��=1:�������(��������Ч)��(Ĭ�Ϸ���Ϊ����)
						// �����临�õ�CTRSRC,DTR,CLKIN,CLKOUT��Чʱ����������Ӧ��DIO��������Զ�ʧЧ
	
	U32 nReserved0;		// �����ֶ�(��δ����)
	U32 nReserved1;		// �����ֶ�(��δ����)
	U32 nReserved2;		// �����ֶ�(��δ����)
} USB3200_DIO_PARAM, *PUSB3200_DIO_PARAM;

// ################################ ����������Ϣ ################################
#define ERROR_NO_READABLE_SEGMENTS (0xE0000000+1) // �޿ɶ���
#define ERROR_SAMPLE_TASK_FAIL	(0xE0000000+2) // ��������ʧ��
#define ERROR_RATE_OVER_RANGE	(0xE0000000+3) // �������ʳ���

// ################################ �豸�����ӿ����� ################################
#ifndef _USB3200_DRIVER_
#define DEVLIB __declspec(dllimport)
#else
#define DEVLIB __declspec(dllexport)
#endif

#ifdef __cplusplus
extern "C" {
#endif
	// ################################ DEV�豸��������� ################################
	HANDLE DEVLIB WINAPI USB3200_DEV_Create(					// �����豸������(hDevice), �ɹ�����ʵ�ʾ��,ʧ���򷵻�INVALID_HANDLE_VALUE(-1),�ɵ���GetLastError()��������ԭ��
										U32 nDeviceIdx,			// �豸���(�߼���Ż��������, ����ʹ����������ɲ���bUsePhysIdx����)
										BOOL bUsePhysIdx);		// �Ƿ�ʹ���������, =TRUE:ʹ���������, =FALSE:ʹ���߼����										

	U32 DEVLIB WINAPI USB3200_DEV_GetCount(void);				// ȡ�ø��豸��̨��,�ɹ�����ֵ>0, ʧ�ܷ���0(�ɵ���GetLastError()��������ԭ��)

	BOOL DEVLIB WINAPI USB3200_DEV_GetSpeed(					// ��ȡ�豸���ӵ�USB�˿��ٶ�, 
										HANDLE hDevice,			// �豸������,����DEV_Create()��������
										U32* pSpeed);			// USB�ӿ��ٶȣ�=1:USB1.0, =2:USB2.0, =3:USB3.0

	BOOL DEVLIB WINAPI USB3200_DEV_GetCurrentIdx(				// ���ָ���豸�е��߼���ź��������
										HANDLE hDevice,			// �豸������,����DEV_Create()��������
										U32* pLgcIdx,			// ���ص��߼����
										U32* pPhysIdx);			// ���ص��������

	BOOL DEVLIB WINAPI USB3200_DEV_Release(HANDLE hDevice);		// �ͷ��豸����(�ؼ�����)

	// ################################ AIģ��������ʵ�ֺ��� ################################
	BOOL DEVLIB WINAPI USB3200_AI_InitParam(				// ��ʼ��AI��������(Initialize Parameter)
									HANDLE hDevice,			// �豸������,����DEV_Create()��������
									PUSB3200_AI_PARAM pAIParam, // AI��������, �����ڴ˺����о���Ӳ����ʼ״̬�͸�����ģʽ,����������AI_VerifyParam()���в���У��
									HANDLE hEvent);			// �¼�������,����EVENT_Create()�������������豸�г��ֿɶ����ݶ�ʱ�ᴥ�����¼�

    BOOL DEVLIB WINAPI USB3200_AI_Start(					// ����AI�ɼ� 
									HANDLE hDevice);		// �豸������,����DEV_Create()��������

    BOOL DEVLIB WINAPI USB3200_AI_SetForceTrig(				// ����ǿ�ƴ����¼�(Set Force Trigger)
									HANDLE hDevice);		// �豸������,����DEV_Create()��������

	BOOL DEVLIB WINAPI USB3200_AI_GetStatus(HANDLE hDevice, PUSB3200_AI_STATUS pAIStatus);   // ȡ��AI����״̬

	BOOL DEVLIB WINAPI USB3200_AI_ClearBuffer(HANDLE hDevice);	//  ������������ݣ������ݶζ�ָ�븴λ����0,����ʹAI_ContReadChannelsV��AI_ContReadChannels����̵ĵȴ�ʱ���ȡ���µ����ݶ�

	U32 DEVLIB WINAPI USB3200_AI_ContReadChannelsV(			// ������ȡָ��ͨ�����������(��ѹ��������)(Continuous Read All Channels for Voltage),�������µĿɶ�����
									HANDLE hDevice,			// �豸������,����DEV_Create()��������
									F64* pVoltBuffer,		// ��ѹ������,���ڷ��ز����ĵ�ѹ���ݣ�ȡֵ�����ɸ�ͨ������ʱ�Ĳ�����Χ����(��λ:V)
									U32 nSizePoints,		// ��������ݵ㳤��(��λ����)
									U32* pRetPoints);		// ����ʵ�ʶ�ȡ�ĵ���

	U32 DEVLIB WINAPI USB3200_AI_ContReadChannels(			// ������ȡָ��ͨ�����������(ԭ����������)(Continuous Read All Channels for Code),�������µĿɶ�����
									HANDLE hDevice,			// �豸������,����DEV_Create()��������
									U16* pCodeBuffer,		// ԭ�뻺����,���ڷ��ز�����ԭ�����ݣ�ȡֵ����Ϊ[0, 4095]
									U32 nSizePoints,		// ��������ݵ㳤��(��λ����)
									U32* pRetPoints);		// ����ʵ�ʶ�ȡ�ĵ���

	BOOL DEVLIB WINAPI USB3200_AI_OneReadChannelsV(			// �����ȡָ��ͨ�����������(��ѹ��������)(One Demand Read All Channels for Voltage)
									HANDLE hDevice,			// �豸������,����DEV_Create()��������
									F64* pVoltBuffer,		// ��ѹ������,���ڷ��ز����ĵ�ѹ���ݣ�ȡֵ�����ɸ�ͨ������ʱ�Ĳ�����Χ����(��λ:V)
									U32 nSizePoints,		// ��������ݵ㳤��(��λ����)
									U32* pRetPoints);		// ����ʵ�ʶ����ĵ���

	BOOL DEVLIB WINAPI USB3200_AI_OneReadChannels(			// �����ȡָ��ͨ�����������(ԭ����������)(One Demand Read All Channels for Code)
									HANDLE hDevice,			// �豸������,����DEV_Create()��������
									U16* pCodeBuffer,		// ԭ�뻺����,���ڷ��ز�����ԭ�����ݣ�ȡֵ����Ϊ[0, 4095]
									U32 nSizePoints,		// ��������ݵ㳤��(��λ����)
									U32* pRetPoints);		// ����ʵ�ʶ����ĵ���

	BOOL DEVLIB WINAPI USB3200_AI_Stop(HANDLE hDevice);		// ֹͣAI�ɼ�

	BOOL DEVLIB WINAPI USB3200_AI_Release(HANDLE hDevice); 	 // �ͷ���AI_InitParam()������ʼ����ռ�õĸ�����Դ

	BOOL DEVLIB WINAPI USB3200_AI_SOneReadChannelsV(		// �򵥶�ȡ����ͨ����������(��ѹ��������)(Simple One Read All Channels for Voltage),������������ʼ���������ȶ�����ֱ�ӵ������Ϳ��Զ�ȡ�������(���Ƕ�AI_OneReadChannelsV�ļ򻯰�װ)
									HANDLE hDevice,			// �豸������,����DEV_Create()��������
									F64* pVoltBuffer,		// ��ѹ������,���ڷ��ز����ĵ�ѹ���ݣ�ȡֵ�����ɸ�ͨ������ʱ�Ĳ�����Χ����(��λ:V)
									U32 nSizePoints,		// ��������ݵ㳤��(��λ����)
									U32* pRetPoints);		// ����ʵ�ʶ����ĵ���

	// ========================= AI������������ =========================
	BOOL DEVLIB WINAPI USB3200_AI_VoltScale(				// ����ָ��������Χ������ԭ�����������ɵ�ѹ����,����ʵ�������ĵ���
									HANDLE hDevice,			// �豸������,����DEV_Create()��������
									U32 nSampleRange,		// ������Χ[0, 3]�����������ĳ�������
									U32 nSampleGain,		// ��������[0, 3]�����������ĳ�������
									F64* pVoltBuffer,		// ��ѹ������,���ڷ���������ĵ�ѹ����,��λV
									U16* pCodeBuffer,		// ԭ�뻺����,���ڴ����������ԭ�����ݣ�ȡֵ����Ϊ[0, 4095], (��ָĳ��ͨ������������)
									U32 nSizePoints,		// ���������ĵ���
									U32* pRetPoints);		// ����ʵ�������ĵ���

	BOOL DEVLIB WINAPI USB3200_AI_GetMainInfo(				// ���AI����Ҫ��Ϣ
									HANDLE hDevice,			// �豸������,����DEV_Create()��������
									PUSB3200_AI_MAIN_INFO pMainInfo); // ���AI��Ҫ��Ϣ

	BOOL DEVLIB WINAPI USB3200_AI_GetRangeInfo(				// ��ò�����Χ�ĸ�����Ϣ(���ȡ��ֱ��ʡ�����)
									HANDLE hDevice,			// �豸������,����DEV_Create()��������
									U32 nChannel,			// AI����ͨ����(���ڱ��豸����ͨ������һ��������Χѡ��,�ʺ����0)
									U32 nSampleRange,		// ������Χ[0, 3]
									PUSB3200_AI_SAMP_RANGE_INFO pRangeInfo); // ������Χ��Ϣ

	BOOL DEVLIB WINAPI USB3200_AI_GetGainInfo(				// �������ĸ�����Ϣ(���ȡ��ֱ��ʡ�����)
									HANDLE hDevice,			// �豸������,����DEV_Create()��������
									U32 nChannel,			// AI����ͨ����[0, 7]
									U32 nSampleGain,		// ��������[0, 3]
									PUSB3200_AI_SAMP_GAIN_INFO pGainInfo); // ������Ϣ

	BOOL DEVLIB WINAPI USB3200_AI_GetRateInfo(				// ��ò���������Ϣ
									HANDLE hDevice,			// �豸������,����DEV_Create()��������
									PUSB3200_AI_SAMP_RATE_INFO pRateInfo); // ����������Ϣ

 	BOOL DEVLIB WINAPI USB3200_AI_VerifyParam(					// У��AI��������(Verify Parameter),�����ڳ�ʼ��AI����ǰ���ô˺���У��������Ϸ���
									HANDLE hDevice,				// �豸������,����DEV_Create()��������
									PUSB3200_AI_PARAM pAIParam);// ��У���AI��������

	BOOL DEVLIB WINAPI USB3200_AI_LoadParam(HANDLE hDevice, PUSB3200_AI_PARAM pAIParam); // ��USB3200.ini�м���AI����
	BOOL DEVLIB WINAPI USB3200_AI_SaveParam(HANDLE hDevice, PUSB3200_AI_PARAM pAIParam); // ����AI������USB3200.ini
	BOOL DEVLIB WINAPI USB3200_AI_ResetParam(HANDLE hDevice, PUSB3200_AI_PARAM pAIParam); // ����ǰAI������λ������ֵ

	// ############################ CTR���������� ############################
	BOOL DEVLIB WINAPI USB3200_CTR_InitParam(			// ���ü���������
									HANDLE hDevice,		// �豸������,����DEV_Create()��������
									U32 nChannel,		// ͨ����(���豸����1��ͨ��,�����0)
									PUSB3200_CTR_PARAM pCTRParam); // ��������

	BOOL DEVLIB WINAPI USB3200_CTR_Start(				// ����������(��������ԴCTRSRC��������CN2�ϵ�DIO0�������룬���������ʱ���ὫDIO0�ķ���ǿ����Ϊ����)
									HANDLE hDevice,		// �豸������,����DEV_Create()��������
									U32 nChannel);		// ͨ����(���豸����1��ͨ��,�����0)

    BOOL DEVLIB WINAPI USB3200_CTR_ReadChannel(			// ��ȡ�������ĵ�ǰ����ֵ
									HANDLE hDevice,		// �豸������,����DEV_Create()��������
									U32 nChannel,		// ͨ����(���豸����1��ͨ��,�����0)
									U32* pCountVal);	// ����ֵ

	BOOL DEVLIB WINAPI USB3200_CTR_Stop(				// ֹͣ(����ͣ)������
									HANDLE hDevice,		// �豸������,����DEV_Create()��������
									U32 nChannel);		// ͨ����(���豸����1��ͨ��,�����0)

	BOOL DEVLIB WINAPI USB3200_CTR_Release(				// �ͷż�������Դ
									HANDLE hDevice,		// �豸������,����DEV_Create()��������
									U32 nChannel);		// ͨ����(���豸����1��ͨ��,�����0)

	// ############################ DI��DO�������������ʵ�ֺ��� ############################
	BOOL DEVLIB WINAPI USB3200_DIO_InitParam(			// ����DIOӲ������
									HANDLE hDevice,		// �豸������,����DEV_Create()��������
									U32 nPort,			// �˿ں�(���豸����1���˿�,�����0)
									PUSB3200_DIO_PARAM pDIOParam); // ��������

	BOOL DEVLIB WINAPI USB3200_DIO_GetParam(			// ��ȡDIOӲ������
									HANDLE hDevice,		// �豸������,����DEV_Create()��������
									U32 nPort,			// �˿ں�(���豸����1���˿�,�����0)
									PUSB3200_DIO_PARAM pDIOParam);	// ���������������ֵ

	BOOL DEVLIB WINAPI USB3200_DIO_ReadPort(			// ���˿�ֵ
									HANDLE hDevice,		// �豸������,����DEV_Create()��������
									U32 nPort,			// �˿ں�(���豸����1���˿�,�����0)
									U32* pPortData,		// ���صĶ˿�����, ��ЧλBit[3:0]
									U8 bLineDataBuf[4]);// �����ݻ�����, ͬʱ���ض˿��и��ߵ�״ֵ̬bLineBuffer[n]=0:��ʾ��(���)״̬, =1��ʾ��(���)״̬

    BOOL DEVLIB WINAPI USB3200_DIO_WritePort(			// д�˿�ֵ
									HANDLE hDevice,		// �豸������,����DEV_Create()��������
									U32 nPort,			// �˿ں�(���豸����1���˿�,�����0)
									U32 nPortData,		// �˿�����, ��ЧλBit[3:0], ���bLineBuffer=NULL,��˲�����Ч,������Ч
									U8 bLineDataBuf[4]);// �����ݻ�����, �˿��и��ߵ�״ֵ̬bLineBuffer[n]=0:��ʾ��(���)״̬, =1��ʾ��(���)״̬

    BOOL DEVLIB WINAPI USB3200_DIO_ReadLine(			// ����ֵ
									HANDLE hDevice,		// �豸������,����DEV_Create()��������
									U32 nPort,			// �˿ں�(���豸����1���˿�,�����0)
									U32 nLine,			// �ߺ�[0, 3]
									U8* pLineData);		// ������, ȡֵ0��1 

    BOOL DEVLIB WINAPI USB3200_DIO_WriteLine(			// д��ֵ
									HANDLE hDevice,		// �豸������,����DEV_Create()��������
									U32 nPort,			// �˿ں�(���豸����1���˿�,�����0)
									U32 nLine,			// �ߺ�[0, 3]
									U8 bLineData);			// ��ֵ,ȡֵ0��1

	BOOL DEVLIB WINAPI USB3200_DIO_Release(				// �ͷż�������Դ
									U32 nPort,			// �˿ں�(���豸����1���˿�,�����0)
									HANDLE hDevice);	// �豸������,����DEV_Create()��������

	// ################################ EVENT�¼����� ################################
	HANDLE DEVLIB WINAPI USB3200_EVENT_Create(void);	// �����¼����
	BOOL DEVLIB WINAPI USB3200_EVENT_Release(HANDLE hEvent); // �ͷ��¼����

#ifdef __cplusplus
}
#endif

#ifndef _CVIDEF_H
	// �Զ������������������
	#ifndef _USB3200_DRIVER_
		#ifndef LOAD_USB3200_LIB // ���û�м���LIB��
		#define LOAD_USB3200_LIB
			#ifndef _WIN64
				#pragma comment(lib, "USB3200.lib")
				#pragma message("======== Welcome to use our art company's products!")
				#pragma message("======== Automatically linking with USB3200.dll...")
				#pragma message("======== Successfully linked with USB3200.dll")
			#else
				#pragma comment(lib, "USB3200_64.lib")
				#pragma message("======== Welcome to use our art company's products!")
				#pragma message("======== Automatically linking with USB3200_64.dll...")
				#pragma message("======== Successfully linked with USB3200_64.dll")
			#endif
		#endif // LOAD_USB3200_LIB
	#endif // _USB3200_DRIVER_
#endif // _CVIDEF_H

#endif // _USB3200_DEVICE_
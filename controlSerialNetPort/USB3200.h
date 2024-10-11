#ifndef _USB3200_DEVICE_
#define _USB3200_DEVICE_

#include "windows.h"

// #################### 人性化的数据类型定义 #####################
// Humanized data types definition
typedef char				I8;		// 8位有符号整型数据
typedef unsigned char		U8;		// 8位无符号整型数据
typedef short				I16;	// 16位有符号整型数据
typedef unsigned short		U16;	// 16位无符号整型数据
typedef long				I32;	// 32位有符号整型数据
typedef unsigned long		U32;	// 32位无符号整型数据
typedef __int64				I64;	// 64位有符号整型数据
typedef unsigned __int64	U64;	// 64位无符号整型数据
typedef float				F32;	// 32位浮点数据(单精度，同为labVIEW中的SGL)
typedef double				F64;	// 64位浮点数据(双精度，同为labVIEW中的DBL)

// ########################## 设备功能指标 ########################
#define USB3200_MAX_AI_CHANNELS	8 // 本卡最多支持8个模拟量输入通道
#define USB3200_MAX_DIO_CHANNELS 4 // 本卡最多支持4个数字量双向通道

// ############# AI工作参数结构体USB3200_AI_PARAM描述 #############
typedef struct _USB3200_AI_CH_PARAM // AI通道参数结构体
{
	U32 nChannel;			// 通道号[0, 7]，分别表示物理通道号AI0－AI7
	U32 nSampleGain;		// 采样增益，具体放大倍数请参考下面常量定义
	U32 nRefGround;			// 地参考方式
	U32 nReserved0;			// 保留(未用)
} USB3200_AI_CH_PARAM, *PUSB3200_AI_CH_PARAM;

// AI硬件通道参数USB3200_AI_CH_PARAM中的nSampleGain模拟量增益放大倍数所使用的选项
#define USB3200_AI_SAMPGAIN_1MULT			0 // 1倍增益
#define USB3200_AI_SAMPGAIN_2MULT			1 // 2倍增益
#define USB3200_AI_SAMPGAIN_4MULT			2 // 4倍增益
#define USB3200_AI_SAMPGAIN_8MULT			3 // 8倍增益

// AI硬件通道参数结构体USB3200_AI_CH_PARAM中的nRefGround参数所使用的地参考选项
#define USB3200_AI_REFGND_RSE			0 // 接地参考单端(Referenced Single Endpoint)
#define USB3200_AI_REFGND_NRSE			1 // 非参考单端(Non Referenced Single Endpoint)
#define USB3200_AI_REFGND_DIFF			2 // 差分(Differential)

typedef struct _USB3200_AI_PARAM // 跟整个AI有关的硬件工作参数(简称AI工作参数)
{
	U32 nSampleMode;		// 采样模式, 0=单点采样(按需)， 1=连续采样
	U32 nPointsPerChan;		// 每个通道采样点数(也是每通道待读取点数),取值范围为[256, 8192],它与nChannelCount的乘积不能大于65536
	F64 fSampleRate;		// 采样速率(Sample Rate), 单位为sps，取值范围为[1sps, 500000sps],它是每个采样通道的采样速率, 它与nChannelCount的乘积不能大于500000sps
	U32 nSampChanCount;     // 采样通道总数[1, 8](此参数在单点采样有效，未此注明的参数则在单点采样模式中无效)
	U32 nReserved0;			// 保留字段(暂未定义)
	USB3200_AI_CH_PARAM CHParam[8]; // 通道参数配置(此参数在单点采样有效，未此注明的参数则在单点采样模式中无效)
	U32 nGroupLoops;		// 组内首末通道循环次数[1, 65535]
	U32 nGroupInterval;     // 组与组之间的时间间隔, 单位：微秒，取值范围[0, 107374182], 等于0时表示等间隔采样(不分组,此时nGroupLoops应等于1)

	U32 bDTriggerEn;		// 数字触发DTR允许(Digital Trigger Enable), =FALSE:表示禁止; =TRUE:表示允许,触发信号由连接器CN2上的DIO1复用输入，因此初始化时会将DIO1的方向强制置为输入
	U32 nDTriggerType;	    // 数字触发类型(Digital Trigger Type)
	U32 nDTriggerDir;	    // 数字触发方向(Digital Trigger Direction)

	U32 bATriggerEn;		// 模拟数字触发ATR允许(Analog Trigger Enable), =TRUE:表示允许, =FALSE:表示禁止
	U32 nATriggerType;		// 模拟触发类型(Analog Trigger Type)
	U32 nATriggerDir;		// 模拟触发方向(Analog Trigger Direction)
	U32 nATrigChannel;		// 触发通道(Analog Trigger Channel)
	F32 fTriggerLevel;		// 触发电平(Trigger Level)
	U32 nTriggerSens;		// 触发灵敏度(Trigger Sensitive for Digital and Analog trigger),单位：微秒(uS)，取值范围[0, 1638]

	U32 nSampleRange;		// 采样范围(Sample Range), 具体见下面常量名定义(此参数在单点采样有效，未此注明的参数则在单点采样模式中无效)
	U32 nClockSource;		// 时钟源选择, =0:内时钟OSCCLK; =1:外时钟CLKIN,由连接器CN2上的DIO2/CLKIN复用输入，因此初始化时会将DIO2的方向强制置为输入
	U32 bClockOutput;		// 采样时钟输出允许, =0:表示禁止; =1:表示允许,由连接器CN2的DIO3/CLKOUT复用输出，因此初始化时会将DIO3的方向强制置为输出

	U32 nReserved1;			// 保留字段(暂未定义)
	U32 nReserved2;			// 保留字段(暂未定义)
	U32 nReserved3;			// 保留字段(暂未定义)
	U32 nReserved4;			// 保留字段(暂未定义)
} USB3200_AI_PARAM, *PUSB3200_AI_PARAM;

// AI硬件参数结构体USB3200_AI_PARAM中的nSampleMode采样模式所使用的选项
#define USB3200_AI_SAMPMODE_ONE_DEMAND	0 // 单点采样(按需)
#define USB3200_AI_SAMPMODE_CONTINUOUS	1 // 连续采样

// AI硬件参数结构体USB3200_AI_PARAM中的nATriggerType/nDTriggerType触发类型所使用的选项
#define USB3200_AI_TRIGTYPE_EDGE		0 // 边沿触发
#define USB3200_AI_TRIGTYPE_LEVEL		1 // 电平触发

// AI硬件参数结构体USB3200_AI_PARAM中的nDTriggerDir触发方向所使用的选项
#define USB3200_AI_TRIGDIR_FALLING		0 // 下降沿/低电平
#define USB3200_AI_TRIGDIR_RISING		1 // 上升沿/高电平
#define USB3200_AI_TRIGDIR_CHANGE		2 // 变化(即上下边沿/高低电平均有效)

// AI硬件参数结构体USB3200_AI_PARAM中的nSampleRange参数所使用的模拟量输入采样范围选项
#define USB3200_AI_SAMPRANGE_N10_P10V		0 // ±10V
#define USB3200_AI_SAMPRANGE_N5_P5V			1 // ±5V
#define USB3200_AI_SAMPRANGE_N2D5_P2D5V		2 // ±2.5V
#define USB3200_AI_SAMPRANGE_0_P10V			3 // 0-10V

// AI硬件参数结构体USB3200_AI_PARAM中的nClockSource时钟源所使用的选项
#define USB3200_AI_CLKSRC_LOCAL			0 // 本地时钟(通常为本地晶振时钟OSCCLK),也叫内部时钟
#define USB3200_AI_CLKSRC_CLKIN			1 // 外部时钟(由连接器CN2上的DIO2/CLKIN复用输入)

// #################### AI工作状态结构体USB3200_AI_STATUS描述 #####################
typedef struct _USB3200_AI_STATUS
{
	U32 bSampling;				// 采样标志, =TRUE:表示正在采样, =FALSE:表示采样结束(或未采样)
	U32 bTriggered;				// 触发标志, =TRUE:表示已被触发, =FALSE:表示未被触发(即正等待触发)

	U32 nSampTaskState;			// 采样任务状态, =1:正常, 其它值表示有异常情况
	U32 nReadableSegments;		// 可读段数，只有它大于0时才能调用AI_ContReadChannels()读取采样段数据
	U32 nMaxReadableSegs;		// 自AI_Start()后出现过的最大可读段数，状态值范围[0, nUsableSegments],它是为监测您的采集软件性能而提供，如果此值越趋近于1，则表示意味着性能越高，越不易出现溢出丢点的可能
	U32 nSampledSegments;		// 已采样段数(自启动AI_Start()之后所采样的段数)，这个只是给用户的统计数据
	U32 nUsableSegments;		// 系统支持的可用段数,取值一般为16，32，64等。

	U32 nHardOverflowCnt;		// 硬件溢出计数(在不溢出情况下恒等于0)
	U32 nSoftOverflowCnt;		// 软件溢出计数(在不溢出情况下恒等于0)
	U32 nTransRate;				// 传输速率(传输AI采样数据), 即每秒传输点数(sps)，作为USB及应用软件传输性能的监测信息

	U32 nReserved0;				// 保留字段(暂未定义)
	U32 nReserved1;				// 保留字段(暂未定义)
} USB3200_AI_STATUS, *PUSB3200_AI_STATUS;

// #################### AI主要信息结构体(USB3200_AI_MAIN_INFO) #######################
typedef struct _USB3200_AI_MAIN_INFO
{
	U32 nChannelCount;		// AI通道数量
	U32 nSampRangeCount;	// AI采样范围挡位数量
	U32 nSampGainCount;		// AI采样增益挡位数量
	U32 nCouplingCount;		// AI耦合挡位数量
	U32 nImpedanceCount;	// AI阻抗的挡位数量
	U32 nDepthOfMemory;		// AI板载存储器深度(点数)
	U32 nSampResolution;	// AI采样分辨率(如=8表示8Bit; =12表示12Bit; =14表示14Bit; =16表示16Bit)
	U32 nSampCodeCount;		// AI采样编码数量(如256, 4096, 16384, 65536)
	U32 nTrigLvlResolution;	// 触发电平分辨率(如=8表示8Bit; =12表示12Bit; =16表示16Bit)
	U32 nTrigLvlCodeCount;	// 触发电平编码数量(如256, 4096)

	U32 nReserved0;			// 保留字段(暂未定义)
	U32 nReserved1;			// 保留字段(暂未定义)
} USB3200_AI_MAIN_INFO, *PUSB3200_AI_MAIN_INFO;

// #################### AI采样范围信息结构体(USB3200_AI_SAMP_RANGE_INFO) #######################
typedef struct _USB3200_AI_SAMP_RANGE_INFO
{
	U32 nSampleRange;		// 当前采样范围挡位号
	U32 nReserved0;			// 保留字段(暂未定义)
	F64 fMaxVolt;			// 采样范围的最大电压值,单位:伏(V)
	F64 fMinVolt;			// 采样范围的最小电压值,单位:伏(V)
	F64 fAmplitude;			// 采样范围幅度,单位:伏(V)
	F64 fHalfOfAmp;			// 采样范围幅度的二分之一,单位:伏(V)
	F64 fCodeWidth;			// 编码宽度,单位:伏(V), 即每个单位码值所分配的电压值
	U32 nPolarity;			// 采样范围的极性(0=双极性BiPolar, 1=单极性UniPolar)
	
	U32 nReserved1;			// 保留字段(暂未定义)
} USB3200_AI_SAMP_RANGE_INFO, *PUSB3200_AI_SAMP_RANGE_INFO;

// 结构体AI_RANGE_INFO的数据成员Polarity所用的输入极性选项
#define USB3200_AI_POLAR_BIPOLAR	0 // 双极性
#define USB3200_AI_POLAR_UNIPOLAR	1 // 单极性

// #################### AI采样增益信息结构体(USB3200_AI_SAMP_GAIN_INFO) #######################
typedef struct _USB3200_AI_SAMP_GAIN_INFO
{
	U32 nSampleGain;		// 当前采样增益挡位号
	U32 nReserved0;			// 保留字段(暂未定义)
	F64 fAmpFactor;			// 放大倍数(Amplification Factor)

	U32 nReserved1;			// 保留字段(暂未定义)
	U32 nReserved2;			// 保留字段(暂未定义)
} USB3200_AI_SAMP_GAIN_INFO, *PUSB3200_AI_SAMP_GAIN_INFO;

// #################### AI采样速率信息结构体(USB3200_AI_SAMP_RATE_INFO) #######################
typedef struct _USB3200_AI_SAMP_RATE_INFO
{
	F64 fMaxRate;		// 单通道最大采样速率(sps)，多通道时各通道平分最大采样率
	F64 fMinRate;		// 单通道最小采样速率(sps)，多通道时各通道平分最小采样率
	F64 fTimerBase;		// 时钟基准（即板载晶振频率）单位：Hz
	U32 nDivideMode;	// 分频模式，0=整数分频(INTDIV), 1=DDS分频(DDSDIV)

	U32 nReserved0;		// 保留字段(暂未定义)
	U32 nReserved1;		// 保留字段(暂未定义)
	U32 nReserved2;		// 保留字段(暂未定义)
} USB3200_AI_SAMP_RATE_INFO, *PUSB3200_AI_SAMP_RATE_INFO;

// ###################### CTR工作参数结构体(USB3200_CTR_PARAM) #######################
typedef struct _USB3200_CTR_PARAM // 跟整个CTR有关的硬件工作参数(简称CTR工作参数)
{
	U32 nPulseDir;		// 脉冲方向(0=下降沿,1=上升沿, 2=双边沿)
	U32 bInitReset;		// 是否在初始化时复位计数器至0，=TRUE:初始化时清零计数器, =FALSE:初始化是不清
	U32 bFullReset;		// 是否在溢出时自动复位计数器至0，=TRUE:溢出时自动复位至0, =FALSE:在溢出时锁住当前计数不变

	U32 nReserved0;		// 保留字段(暂未定义)
	U32 nReserved1;		// 保留字段(暂未定义)
	U32 nReserved2;		// 保留字段(暂未定义)
} USB3200_CTR_PARAM, *PUSB3200_CTR_PARAM;

// CTR硬件参数结构体USB3200_CTR_PARAM中的nPulseDir脉冲方向所使用的选项
#define USB3200_CTR_PULSEDIR_FALLING	0 // 下边沿
#define USB3200_CTR_PULSEDIR_RISING		1 // 上边沿
#define USB3200_CTR_PULSEDIR_CHANGE		2 // 变化(上下边沿均有效)

// #################### DIO主要信息结构体(USB3200_DIO_PARAM) #######################
typedef struct _USB3200_DIO_PARAM // 跟整个DIO有关的硬件工作参数(简称DIO工作参数)
{
	U8 bOutputEn[4];	// 输出方向允许(Output Enable),bOutputEn[n]=0:输出禁止(即为输入)，=1:输出允许(即输入无效)。(默认方向为输入)
						// 但与其复用的CTRSRC,DTR,CLKIN,CLKOUT有效时，则与其相应的DIO方向控制自动失效
	
	U32 nReserved0;		// 保留字段(暂未定义)
	U32 nReserved1;		// 保留字段(暂未定义)
	U32 nReserved2;		// 保留字段(暂未定义)
} USB3200_DIO_PARAM, *PUSB3200_DIO_PARAM;

// ################################ 函数错误信息 ################################
#define ERROR_NO_READABLE_SEGMENTS (0xE0000000+1) // 无可读段
#define ERROR_SAMPLE_TASK_FAIL	(0xE0000000+2) // 采样任务失败
#define ERROR_RATE_OVER_RANGE	(0xE0000000+3) // 采样速率超限

// ################################ 设备驱动接口申明 ################################
#ifndef _USB3200_DRIVER_
#define DEVLIB __declspec(dllimport)
#else
#define DEVLIB __declspec(dllexport)
#endif

#ifdef __cplusplus
extern "C" {
#endif
	// ################################ DEV设备对象管理函数 ################################
	HANDLE DEVLIB WINAPI USB3200_DEV_Create(					// 创建设备对象句柄(hDevice), 成功返回实际句柄,失败则返回INVALID_HANDLE_VALUE(-1),可调用GetLastError()分析错误原因
										U32 nDeviceIdx,			// 设备序号(逻辑序号或物理序号, 具体使用哪种序号由参数bUsePhysIdx决定)
										BOOL bUsePhysIdx);		// 是否使用物理序号, =TRUE:使用物理序号, =FALSE:使用逻辑序号										

	U32 DEVLIB WINAPI USB3200_DEV_GetCount(void);				// 取得该设备总台数,成功返回值>0, 失败返回0(可调用GetLastError()分析错误原因)

	BOOL DEVLIB WINAPI USB3200_DEV_GetSpeed(					// 读取设备连接的USB端口速度, 
										HANDLE hDevice,			// 设备对象句柄,它由DEV_Create()函数创建
										U32* pSpeed);			// USB接口速度，=1:USB1.0, =2:USB2.0, =3:USB3.0

	BOOL DEVLIB WINAPI USB3200_DEV_GetCurrentIdx(				// 获得指定设备中的逻辑序号和物理序号
										HANDLE hDevice,			// 设备对象句柄,它由DEV_Create()函数创建
										U32* pLgcIdx,			// 返回的逻辑序号
										U32* pPhysIdx);			// 返回的物理序号

	BOOL DEVLIB WINAPI USB3200_DEV_Release(HANDLE hDevice);		// 释放设备对象(关键函数)

	// ################################ AI模拟量输入实现函数 ################################
	BOOL DEVLIB WINAPI USB3200_AI_InitParam(				// 初始化AI工作参数(Initialize Parameter)
									HANDLE hDevice,			// 设备对象句柄,它由DEV_Create()函数创建
									PUSB3200_AI_PARAM pAIParam, // AI工作参数, 它仅在此函数中决定硬件初始状态和各工作模式,可以事先由AI_VerifyParam()进行参数校验
									HANDLE hEvent);			// 事件对象句柄,它由EVENT_Create()函数创建，当设备中出现可读数据段时会触发此事件

    BOOL DEVLIB WINAPI USB3200_AI_Start(					// 启动AI采集 
									HANDLE hDevice);		// 设备对象句柄,它由DEV_Create()函数创建

    BOOL DEVLIB WINAPI USB3200_AI_SetForceTrig(				// 发生强制触发事件(Set Force Trigger)
									HANDLE hDevice);		// 设备对象句柄,它由DEV_Create()函数创建

	BOOL DEVLIB WINAPI USB3200_AI_GetStatus(HANDLE hDevice, PUSB3200_AI_STATUS pAIStatus);   // 取得AI各种状态

	BOOL DEVLIB WINAPI USB3200_AI_ClearBuffer(HANDLE hDevice);	//  清除缓冲区数据，将数据段读指针复位至段0,可以使AI_ContReadChannelsV或AI_ContReadChannels以最短的等待时间读取最新的数据段

	U32 DEVLIB WINAPI USB3200_AI_ContReadChannelsV(			// 连续读取指定通道组采样数据(电压数据序列)(Continuous Read All Channels for Voltage),返回余下的可读段数
									HANDLE hDevice,			// 设备对象句柄,它由DEV_Create()函数创建
									F64* pVoltBuffer,		// 电压缓冲区,用于返回采样的电压数据，取值区间由各通道采样时的采样范围决定(单位:V)
									U32 nSizePoints,		// 读入的数据点长度(单位：点)
									U32* pRetPoints);		// 返回实际读取的点数

	U32 DEVLIB WINAPI USB3200_AI_ContReadChannels(			// 连续读取指定通道组采样数据(原码数据序列)(Continuous Read All Channels for Code),返回余下的可读段数
									HANDLE hDevice,			// 设备对象句柄,它由DEV_Create()函数创建
									U16* pCodeBuffer,		// 原码缓冲区,用于返回采样的原码数据，取值区间为[0, 4095]
									U32 nSizePoints,		// 读入的数据点长度(单位：点)
									U32* pRetPoints);		// 返回实际读取的点数

	BOOL DEVLIB WINAPI USB3200_AI_OneReadChannelsV(			// 单点读取指定通道组采样数据(电压数据序列)(One Demand Read All Channels for Voltage)
									HANDLE hDevice,			// 设备对象句柄,它由DEV_Create()函数创建
									F64* pVoltBuffer,		// 电压缓冲区,用于返回采样的电压数据，取值区间由各通道采样时的采样范围决定(单位:V)
									U32 nSizePoints,		// 读入的数据点长度(单位：点)
									U32* pRetPoints);		// 返回实际读到的点数

	BOOL DEVLIB WINAPI USB3200_AI_OneReadChannels(			// 单点读取指定通道组采样数据(原码数据序列)(One Demand Read All Channels for Code)
									HANDLE hDevice,			// 设备对象句柄,它由DEV_Create()函数创建
									U16* pCodeBuffer,		// 原码缓冲区,用于返回采样的原码数据，取值区间为[0, 4095]
									U32 nSizePoints,		// 读入的数据点长度(单位：点)
									U32* pRetPoints);		// 返回实际读到的点数

	BOOL DEVLIB WINAPI USB3200_AI_Stop(HANDLE hDevice);		// 停止AI采集

	BOOL DEVLIB WINAPI USB3200_AI_Release(HANDLE hDevice); 	 // 释放由AI_InitParam()函数初始化并占用的各种资源

	BOOL DEVLIB WINAPI USB3200_AI_SOneReadChannelsV(		// 简单读取所有通道采样数据(电压数据序列)(Simple One Read All Channels for Voltage),不经过参数初始化，启动等动作，直接调用它就可以读取采样结果(它是对AI_OneReadChannelsV的简化包装)
									HANDLE hDevice,			// 设备对象句柄,它由DEV_Create()函数创建
									F64* pVoltBuffer,		// 电压缓冲区,用于返回采样的电压数据，取值区间由各通道采样时的采样范围决定(单位:V)
									U32 nSizePoints,		// 读入的数据点长度(单位：点)
									U32* pRetPoints);		// 返回实际读到的点数

	// ========================= AI辅助操作函数 =========================
	BOOL DEVLIB WINAPI USB3200_AI_VoltScale(				// 根据指定采样范围将采样原码数据量化成电压数据,返回实际量化的点数
									HANDLE hDevice,			// 设备对象句柄,它由DEV_Create()函数创建
									U32 nSampleRange,		// 采样范围[0, 3]，详情见上面的常量定义
									U32 nSampleGain,		// 采样增益[0, 3]，详情见上面的常量定义
									F64* pVoltBuffer,		// 电压缓冲区,用于返回量化后的电压数据,单位V
									U16* pCodeBuffer,		// 原码缓冲区,用于传入待量化的原码数据，取值区间为[0, 4095], (单指某个通道的连续数据)
									U32 nSizePoints,		// 请求量化的点数
									U32* pRetPoints);		// 返回实际量化的点数

	BOOL DEVLIB WINAPI USB3200_AI_GetMainInfo(				// 获得AI的主要信息
									HANDLE hDevice,			// 设备对象句柄,它由DEV_Create()函数创建
									PUSB3200_AI_MAIN_INFO pMainInfo); // 获得AI主要信息

	BOOL DEVLIB WINAPI USB3200_AI_GetRangeInfo(				// 获得采样范围的各种信息(幅度、分辨率、极性)
									HANDLE hDevice,			// 设备对象句柄,它由DEV_Create()函数创建
									U32 nChannel,			// AI物理通道号(由于本设备所有通道共享一个采样范围选择,故恒等于0)
									U32 nSampleRange,		// 采样范围[0, 3]
									PUSB3200_AI_SAMP_RANGE_INFO pRangeInfo); // 采样范围信息

	BOOL DEVLIB WINAPI USB3200_AI_GetGainInfo(				// 获得增益的各种信息(幅度、分辨率、极性)
									HANDLE hDevice,			// 设备对象句柄,它由DEV_Create()函数创建
									U32 nChannel,			// AI物理通道号[0, 7]
									U32 nSampleGain,		// 采样增益[0, 3]
									PUSB3200_AI_SAMP_GAIN_INFO pGainInfo); // 增益信息

	BOOL DEVLIB WINAPI USB3200_AI_GetRateInfo(				// 获得采样速率信息
									HANDLE hDevice,			// 设备对象句柄,它由DEV_Create()函数创建
									PUSB3200_AI_SAMP_RATE_INFO pRateInfo); // 采样速率信息

 	BOOL DEVLIB WINAPI USB3200_AI_VerifyParam(					// 校验AI工作参数(Verify Parameter),建议在初始化AI参数前调用此函数校验各参数合法性
									HANDLE hDevice,				// 设备对象句柄,它由DEV_Create()函数创建
									PUSB3200_AI_PARAM pAIParam);// 待校验的AI工作参数

	BOOL DEVLIB WINAPI USB3200_AI_LoadParam(HANDLE hDevice, PUSB3200_AI_PARAM pAIParam); // 从USB3200.ini中加载AI参数
	BOOL DEVLIB WINAPI USB3200_AI_SaveParam(HANDLE hDevice, PUSB3200_AI_PARAM pAIParam); // 保存AI参数至USB3200.ini
	BOOL DEVLIB WINAPI USB3200_AI_ResetParam(HANDLE hDevice, PUSB3200_AI_PARAM pAIParam); // 将当前AI参数复位至出厂值

	// ############################ CTR计数器函数 ############################
	BOOL DEVLIB WINAPI USB3200_CTR_InitParam(			// 设置计数器参数
									HANDLE hDevice,		// 设备对象句柄,它由DEV_Create()函数创建
									U32 nChannel,		// 通道号(本设备仅有1个通道,恒等于0)
									PUSB3200_CTR_PARAM pCTRParam); // 工作参数

	BOOL DEVLIB WINAPI USB3200_CTR_Start(				// 启动计数器(由于脉冲源CTRSRC与连接器CN2上的DIO0复用输入，因此在启动时它会将DIO0的方向强制置为输入)
									HANDLE hDevice,		// 设备对象句柄,它由DEV_Create()函数创建
									U32 nChannel);		// 通道号(本设备仅有1个通道,恒等于0)

    BOOL DEVLIB WINAPI USB3200_CTR_ReadChannel(			// 读取计数器的当前计数值
									HANDLE hDevice,		// 设备对象句柄,它由DEV_Create()函数创建
									U32 nChannel,		// 通道号(本设备仅有1个通道,恒等于0)
									U32* pCountVal);	// 计数值

	BOOL DEVLIB WINAPI USB3200_CTR_Stop(				// 停止(或暂停)计数器
									HANDLE hDevice,		// 设备对象句柄,它由DEV_Create()函数创建
									U32 nChannel);		// 通道号(本设备仅有1个通道,恒等于0)

	BOOL DEVLIB WINAPI USB3200_CTR_Release(				// 释放计数器资源
									HANDLE hDevice,		// 设备对象句柄,它由DEV_Create()函数创建
									U32 nChannel);		// 通道号(本设备仅有1个通道,恒等于0)

	// ############################ DI、DO数字量输入输出实现函数 ############################
	BOOL DEVLIB WINAPI USB3200_DIO_InitParam(			// 设置DIO硬件参数
									HANDLE hDevice,		// 设备对象句柄,它由DEV_Create()函数创建
									U32 nPort,			// 端口号(本设备仅有1个端口,恒等于0)
									PUSB3200_DIO_PARAM pDIOParam); // 工作参数

	BOOL DEVLIB WINAPI USB3200_DIO_GetParam(			// 获取DIO硬件参数
									HANDLE hDevice,		// 设备对象句柄,它由DEV_Create()函数创建
									U32 nPort,			// 端口号(本设备仅有1个端口,恒等于0)
									PUSB3200_DIO_PARAM pDIOParam);	// 返回输出工作参数值

	BOOL DEVLIB WINAPI USB3200_DIO_ReadPort(			// 读端口值
									HANDLE hDevice,		// 设备对象句柄,它由DEV_Create()函数创建
									U32 nPort,			// 端口号(本设备仅有1个端口,恒等于0)
									U32* pPortData,		// 返回的端口数据, 有效位Bit[3:0]
									U8 bLineDataBuf[4]);// 线数据缓冲区, 同时返回端口中各线的状态值bLineBuffer[n]=0:表示关(或低)状态, =1表示开(或高)状态

    BOOL DEVLIB WINAPI USB3200_DIO_WritePort(			// 写端口值
									HANDLE hDevice,		// 设备对象句柄,它由DEV_Create()函数创建
									U32 nPort,			// 端口号(本设备仅有1个端口,恒等于0)
									U32 nPortData,		// 端口数据, 有效位Bit[3:0], 如果bLineBuffer=NULL,则此参数有效,否则无效
									U8 bLineDataBuf[4]);// 线数据缓冲区, 端口中各线的状态值bLineBuffer[n]=0:表示关(或低)状态, =1表示开(或高)状态

    BOOL DEVLIB WINAPI USB3200_DIO_ReadLine(			// 读线值
									HANDLE hDevice,		// 设备对象句柄,它由DEV_Create()函数创建
									U32 nPort,			// 端口号(本设备仅有1个端口,恒等于0)
									U32 nLine,			// 线号[0, 3]
									U8* pLineData);		// 线数据, 取值0或1 

    BOOL DEVLIB WINAPI USB3200_DIO_WriteLine(			// 写线值
									HANDLE hDevice,		// 设备对象句柄,它由DEV_Create()函数创建
									U32 nPort,			// 端口号(本设备仅有1个端口,恒等于0)
									U32 nLine,			// 线号[0, 3]
									U8 bLineData);			// 线值,取值0或1

	BOOL DEVLIB WINAPI USB3200_DIO_Release(				// 释放计数器资源
									U32 nPort,			// 端口号(本设备仅有1个端口,恒等于0)
									HANDLE hDevice);	// 设备对象句柄,它由DEV_Create()函数创建

	// ################################ EVENT事件函数 ################################
	HANDLE DEVLIB WINAPI USB3200_EVENT_Create(void);	// 创建事件句柄
	BOOL DEVLIB WINAPI USB3200_EVENT_Release(HANDLE hEvent); // 释放事件句柄

#ifdef __cplusplus
}
#endif

#ifndef _CVIDEF_H
	// 自动包含驱动函数导入库
	#ifndef _USB3200_DRIVER_
		#ifndef LOAD_USB3200_LIB // 如果没有加载LIB库
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
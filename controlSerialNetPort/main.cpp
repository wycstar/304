#include "stdafx.h"
#include <windows.h>
#include <iostream>
//#include <mil.h>

using namespace std;


//typedef int*(*singleModelMatch)(MIL_ID, MIL_ID, int,int, int, int, int, int, MIL_CONST_TEXT_PTR, double *, double *, double *);
//typedef  返回类型(*新类型)(参数表)  singleModelMatch类型的函数指针，该指针指向一个只带有3个MIL_ID类型、4个int类型、3个double*类型的形参，返回值为int*类型的函数


int main() {
	//printf("hello world");
	////加载动态链接库hModule是模块句柄
	/*HMODULE hModule = LoadLibrary(L"SingleModelMatch.dll");

	if (!hModule)
	{
		cout << "Error!" << endl;
	}*/
	////获取函数 GetMaxNumber 的地址
	//pGetMaxN pgetm = (pGetMaxN)GetProcAddress(hModule, "GetMaxNumber");
	//cout << pgetm(10, 5) << endl;

	////获取函数 ShowMsg 的地址
	//pShowMsg pshowm = (pShowMsg)GetProcAddress(hModule, "ShowMsg");
	//pshowm("内容", "标题");

	//MIL_ID MilApplication,     /* 应用ID*/
	//	MilSystem,          /* 系统ID */
	//	MilDisplay,         /* 播放窗口ID*/
	//	MilImage1,          /* 图像1缓存ID*/
	//	MilImage2;          /* 图像2缓存ID*/

	//						/* 初始化应用环境 */
	//MappAllocDefault(M_DEFAULT, &MilApplication, &MilSystem, &MilDisplay, M_NULL, M_NULL);

	///*将图像载入图像缓冲区*/
	///* Restore source image into image buffer. */
	//MbufRestore(M_INTERACTIVE, MilSystem, &MilImage1);

	//MbufRestore(M_INTERACTIVE, MilSystem, &MilImage2);
	//MbufRestore(SINGLE_MODEL_IMAGE1, MilSystem, &MilImage1);
	//MbufRestore(SINGLE_MODEL_IMAGE2, MilSystem, &MilImage2);

	/*定义控制参数*/
	//int cx1=900,cy1=800,w1=900,h1=500;
	//int cx2=800,cy2=800,w2=900,h2=900;
	//int cx1 = 0, cy1 = 0, w1 = 1626, h1 = 1236;//脚本读取
	//int cx2 = 0, cy2 = 0, w2 = 1626, h2 = 1236;

	/*位置结果输出定义变量并初始化*/
	/*double x = 0, y = 0, a = 0;
	double *x1 = &x, *y1 = &y, *a1 = &a;

	double xx = 0, yy = 0, aa = 0;
	double *x2 = &xx, *y2 = &yy, *a2 = &aa;*/

	/*运行单模板匹配数*/
	//singleModelMatch sMfun;//定义了singleModelMatch类型变量sMfun，此时就可以像使用形式*singleModelMatch一样使用这个变量了。
	//sMfun = (singleModelMatch)GetProcAddress(hModule, "SingleModelExample");//获取动态链接库中的SingleModelExample函数
	
	//sMfun(MilSystem, MilDisplay, MilImage1, cx1, cy1, w1, h1, x1, y1, a1);

	//sMfun(MilSystem, MilDisplay, MilImage2, cx2, cy2, w2, h2, x2, y2, a2);
	//得到位置结果x1 y1 a1即可


	//-------------------------------------------------------------------------------------------
	/*计算偏差量及调整量*///微调设备模块的工作
	//double dx = 0, dy = 0, da = 0;

	//dx = *x1 - *x2;
	//dy = *y1 - *y2;
	//da = *a1 - *a2;

	///*打印结果*/
	//printf("%-15.2f %-15.2f %-15.2f\n", dx, dy, da);


	/* 释放资源 */
	/*MosGetch();
	MbufFree(MilImage1);
	MbufFree(MilImage2);
	MappFreeDefault(MilApplication, MilSystem, MilDisplay, M_NULL, M_NULL);*/

	return 0;


	//释放
	//FreeLibrary(hModule);
}

//end test of dll




////程序整体测试
///*图片来源目录*/
//#define SINGLE_MODEL_IMAGE1           MIL_TEXT("27.bmp")
//#define SINGLE_MODEL_IMAGE2           MIL_TEXT("23.bmp")
//
//#define NUM_MOUSE_GRAB 3
//
//int grabNum = NUM_MOUSE_GRAB;
//
//struct Position {
//	double px;
//	double py;
//};
//
//Position Point3[3] = { { 0,0 },{ 0,0 },{ 0,0 }
//};
//Position *pPoitnt3 = Point3;
//
///*单独模板匹配函数声明*/
//void SingleModelExample(MIL_ID MilSystem, MIL_ID MilDisplay, MIL_ID MilImage,
//	int cx, int cy, int w, int h,
//	double *x, double *y, double *a);
//
//void GrabPosition(MIL_ID MilDisplay, Position* DataPtr);	/*抓取函数定义*/
//MIL_INT MFTYPE MouseFct(MIL_INT HookType, MIL_ID EventID, void* UserDataPtr);  /*回调函数定义*/
//
//
//
//																			   /*****************************************************************************/
//
//int MosMain(void)
//{
//	MIL_ID MilApplication,     /* 应用ID*/
//		MilSystem,          /* 系统ID */
//		MilDisplay,         /* 播放窗口ID*/
//		MilImage1,          /* 图像1缓存ID*/
//		MilImage2;          /* 图像2缓存ID*/
//
//							/* 初始化应用环境 */
//	MappAllocDefault(M_DEFAULT, &MilApplication, &MilSystem, &MilDisplay, M_NULL, M_NULL);
//
//	/*载入图像*/
//
//	MbufRestore(M_INTERACTIVE, MilSystem, &MilImage1);
//	MbufRestore(M_INTERACTIVE, MilSystem, &MilImage2);
//	//MbufRestore(SINGLE_MODEL_IMAGE1, MilSystem, &MilImage1);
//	//MbufRestore(SINGLE_MODEL_IMAGE2, MilSystem, &MilImage2);
//
//	/*定义控制参数*/
//	//int cx1=900,cy1=800,w1=900,h1=500;
//	//int cx2=800,cy2=800,w2=900,h2=900;
//	int cx1 = 0, cy1 = 0, w1 = 1626, h1 = 1236;
//	int cx2 = 0, cy2 = 0, w2 = 1626, h2 = 1236;
//
//	/*位置结果输出*/
//	double x = 0, y = 0, a = 0;
//	double *x1 = &x, *y1 = &y, *a1 = &a;
//
//	double xx = 0, yy = 0, aa = 0;
//	double *x2 = &xx, *y2 = &yy, *a2 = &aa;
//
//	/*运行单模板匹配数*/
//	SingleModelExample(MilSystem, MilDisplay, MilImage1, cx1, cy1, w1, h1, x1, y1, a1);
//	SingleModelExample(MilSystem, MilDisplay, MilImage2, cx2, cy2, w2, h2, x2, y2, a2);
//
//	/*计算偏差量及调整量*/
//	double dx = 0, dy = 0, da = 0;
//
//	dx = *x1 - *x2;
//	dy = *y1 - *y2;
//	da = *a1 - *a2;
//
//	/*打印结果*/
//	printf("%-15.2f %-15.2f %-15.2f\n", dx, dy, da);
//
//
//	/* 释放资源 */
//	MosGetch();
//	MbufFree(MilImage1);
//	MbufFree(MilImage2);
//	MappFreeDefault(MilApplication, MilSystem, MilDisplay, M_NULL, M_NULL);
//
//	return 0;
//}
//
///*****************************************************************************/
//
///* 单模板匹配函数定义*/
//#define SINGLE_MODEL_SEARCH_SPEED   M_LOW        /*设置匹配搜索速度*/
//#define MODEL_MAX_OCCURRENCES       2L          /* 最大匹配结果数 */
//
//
//void SingleModelExample(MIL_ID MilSystem, MIL_ID MilDisplay, MIL_ID MilImage,
//	int cx, int cy, int w, int h,
//	double *x, double *y, double *a)
//{
//	MIL_ID      MilOverlayImage,                  /* 注释层ID*/
//		MilChild;                         /* 感兴趣区图像ID*/
//	MIL_ID      MilSearchContext,                 /* 模板匹配控制器ID*/
//		MilResult;                        /* 边缘识别结果缓存ID*/
//	MIL_DOUBLE  ModelDrawColor = M_COLOR_RED;     /* 模板线框颜色*/
//	MIL_INT     Model[MODEL_MAX_OCCURRENCES],     /* 模板编号（数组）*/
//		NumResults = 0L;                 /* 匹配结果数*/
//	MIL_DOUBLE  Score[MODEL_MAX_OCCURRENCES],     /* 匹配评估结果（数组）*/
//		XPosition[MODEL_MAX_OCCURRENCES], /* 目标位置X(数组)*/
//		YPosition[MODEL_MAX_OCCURRENCES], /* 目标位置Y(数组) */
//		Angle[MODEL_MAX_OCCURRENCES],     /* 目标角度位置（数组）*/
//		Scale[MODEL_MAX_OCCURRENCES],     /* 目标缩放值（数组）*/
//		Time = 0.0;                       /* 所用时间 */
//	int         i;                                /* 整形变量 */
//
//
//												  /*图片显示*/
//	MdispSelect(MilDisplay, MilImage);
//
//	/*选定ROI并显示*/
//	MosGetch();
//	MbufChild2d(MilImage, cx, cy, w, h, &MilChild);
//	MdispSelect(MilDisplay, MilChild);
//
//	//尝试鼠标Hook
//	//Position curPosition = {0,0};
//
//	//Position * pcurPositioon = &curPosition;
//	//MosPrintf(MIL_TEXT("Prepare to Hook\n"));
//	//MdispHookFunction(MilDisplay, M_MOUSE_LEFT_BUTTON_DOWN, MouseFct, pcurPositioon);
//
//	////鼠标Hook结束，准备print
//	//MosPrintf(MIL_TEXT("Prepare to print Hooked\n"));
//	//MosPrintf(MIL_TEXT("%-9f%-9f%\n"), curPosition.px, curPosition.py);
//
//	/*GrabPosition(MilDisplay, pPoitnt3);
//
//	getchar();
//	MosPrintf(MIL_TEXT("Print in Main\n\n"));
//	cout << Point3[0].px << Point3[0].py << endl;
//	cout << Point3[1].px << Point3[1].py << endl;
//	cout << Point3[2].px << Point3[2].py << endl;*/
//
//	/*注释设置*/
//	MdispControl(MilDisplay, M_OVERLAY, M_ENABLE);               /*开启注释层*/
//	MdispControl(MilDisplay, M_OVERLAY_CLEAR, M_DEFAULT);        /*注释层初始化*/
//	MdispInquire(MilDisplay, M_OVERLAY_ID, &MilOverlayImage);    /*载入注释层*/
//
//																 /*预处理，二值化、开闭运算*/
//	MosGetch();
//	MimMorphic(MilChild, MilChild, M_3X3_RECT, M_AREA_OPEN, 200, M_GRAYSCALE);
//	MimMorphic(MilChild, MilChild, M_3X3_RECT, M_AREA_CLOSE, 200, M_GRAYSCALE);
//	//MimBinarize(MilChild, MilChild,  M_BIMODAL+M_LESS_OR_EQUAL, M_NULL, M_NULL);
//	//MimMorphic(MilChild, MilChild, M_3X3_RECT , M_AREA_OPEN, 300, M_BINARY);
//	//MimMorphic(MilChild, MilChild, M_3X3_RECT , M_AREA_CLOSE,300, M_BINARY);
//	//MimConvolve(MilChild,MilChild,M_EDGE_DETECT);
//
//	/*匹配环境设置*/
//	MosGetch();
//	MmodAlloc(MilSystem, M_GEOMETRIC, M_DEFAULT, &MilSearchContext); /*分配匹配控制器*/
//	MmodAllocResult(MilSystem, M_DEFAULT, &MilResult);/*分配结果缓存 */
//
//													  /*定义模板*/
//	MosGetch();
//	//MmodDefine(MilSearchContext, M_RECTANGLE,M_FOREGROUND_BLACK ,98, 40, M_DEFAULT, M_DEFAULT); /*画图定义模板*/ 
//	//MmodDefineFromFile(MilSearchContext,M_DXF_FILE ,MIL_TEXT("D:\\MOBAN\\JIABN-GEBAO8.dxf") ,M_DEFAULT ); /*从文件定义模板*/  
//	MmodDefineFromFile(MilSearchContext, M_DXF_FILE, M_INTERACTIVE, M_DEFAULT); /*从文件定义模板*/
//
//
//																				/*设置匹配参数 */
//	MmodControl(MilSearchContext, M_CONTEXT, M_SPEED, SINGLE_MODEL_SEARCH_SPEED);  /*设置匹配速度 */
//	MmodControl(MilSearchContext, M_CONTEXT, M_SMOOTHNESS, 70);                    /*设置匹配平滑度（对于识别到的边缘进行平滑处理） */
//	MmodControl(MilSearchContext, M_DEFAULT, M_NUMBER, 1);                         /*匹配目标数 */
//																				   //MmodControl(MilSearchContext, M_ALL, M_CORNER_RADIUS ,6.0);                    /*画图定义模板的圆角*/
//
//																				   /*匹配预处理 */
//	MmodPreprocess(MilSearchContext, M_DEFAULT);
//
//	/*清空注释层*/
//	MdispControl(MilDisplay, M_OVERLAY_CLEAR, M_DEFAULT);
//
//	/*执行匹配*/
//	//MosGetch();
//	MappTimer(M_TIMER_RESET + M_SYNCHRONOUS, M_NULL);/*启动计时器 */
//	MmodFind(MilSearchContext, MilChild, MilResult);
//	MappTimer(M_TIMER_READ + M_SYNCHRONOUS, &Time);/*读取时间 */
//
//												   /*读取匹配结果数 */
//	MmodGetResult(MilResult, M_DEFAULT, M_NUMBER + M_TYPE_MIL_INT, &NumResults);
//
//
//	if ((NumResults >= 1) && (NumResults <= MODEL_MAX_OCCURRENCES))
//	{
//		/*读取*/
//		MmodGetResult(MilResult, M_DEFAULT, M_INDEX + M_TYPE_MIL_INT, Model);
//		MmodGetResult(MilResult, M_DEFAULT, M_POSITION_X, XPosition);
//		MmodGetResult(MilResult, M_DEFAULT, M_POSITION_Y, YPosition);
//		MmodGetResult(MilResult, M_DEFAULT, M_ANGLE, Angle);
//		MmodGetResult(MilResult, M_DEFAULT, M_SCALE, Scale);
//		MmodGetResult(MilResult, M_DEFAULT, M_SCORE, Score);
//
//		/*打印*/
//		MosPrintf(MIL_TEXT("The model was found in the target image:\n\n"));
//		MosPrintf(MIL_TEXT("Result   Model   X Position   Y Position   ") MIL_TEXT("Angle   Scale   Score\n\n"));
//		for (i = 0; i<NumResults; i++)
//		{
//			MosPrintf(MIL_TEXT("%-9d%-8d%-13.2f%-13.2f%-8.2f%-8.2f%-5.2f%%\n"),
//				i, Model[i], XPosition[i], YPosition[i], Angle[i], Scale[i],
//				Score[i]);
//
//			/*结果传递*/
//			*x = XPosition[i];
//			*y = YPosition[i];
//			*a = Angle[i];
//		}
//
//		/*显示用时*/
//		MosPrintf(MIL_TEXT("\nThe search time is %.1f ms\n\n"), Time*1000.0);
//
//		/* 显示匹配结果位置，包括线框+坐标系 */
//		for (i = 0; i<NumResults; i++)
//		{
//			MgraColor(M_DEFAULT, ModelDrawColor);
//			MmodDraw(M_DEFAULT, MilResult, MilOverlayImage, M_DRAW_EDGES + M_DRAW_POSITION, i, M_DEFAULT);
//		}
//	}
//	else
//	{
//		MosPrintf(MIL_TEXT("result error !\n\n"));
//	}
//
//
//	/* 结束并释放资源*/
//	MosPrintf(MIL_TEXT("Press <Enter> to end.\n\n"));
//
//	MosGetch();
//	MdispControl(MilDisplay, M_OVERLAY_CLEAR, M_DEFAULT);
//	MbufFree(MilChild);
//	MmodFree(MilSearchContext);
//	MmodFree(MilResult);
//}
//
////定义抓取函数
//void GrabPosition(MIL_ID MilDisplay, Position* DataPtr)
//{
//	Position * pcurPositioon = DataPtr;
//	MosPrintf(MIL_TEXT("Hook in grab\n"));
//	MdispHookFunction(MilDisplay, M_MOUSE_LEFT_BUTTON_DOWN, MouseFct, pcurPositioon);
//	//鼠标Hook结束，准备print
//	MosPrintf(MIL_TEXT("print in Grab\n"));
//	MosPrintf(MIL_TEXT("%-9f%-9f%\n"), pcurPositioon->px, pcurPositioon->py);
//	pcurPositioon++;
//}
//
//MIL_INT MFTYPE MouseFct(MIL_INT HookType, MIL_ID EventID, void* UserDataPtr)  /*回调函数定义*/
//{
//	Position * MousePosition = (Position *)UserDataPtr;	/*建立MousePosition存储结构体*/
//	if (MousePosition)
//	{
//		if (grabNum > 0)
//		{
//			MdispGetHookInfo(EventID, M_MOUSE_POSITION_BUFFER_X, &(MousePosition->px));
//			MdispGetHookInfo(EventID, M_MOUSE_POSITION_BUFFER_Y, &(MousePosition->py));	/*将结果存储进入结构体*/
//			MosPrintf(MIL_TEXT("print in MouseFct\n"));
//			MosPrintf(MIL_TEXT("%-9f%-9f%\n"), MousePosition->px, MousePosition->py);
//			grabNum--;
//			pPoitnt3++;
//		}
//	}
//	return 0;
//}
////程序整体测试完成

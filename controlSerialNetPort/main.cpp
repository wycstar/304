#include "stdafx.h"
#include <windows.h>
#include <iostream>
//#include <mil.h>

using namespace std;


//typedef int*(*singleModelMatch)(MIL_ID, MIL_ID, int,int, int, int, int, int, MIL_CONST_TEXT_PTR, double *, double *, double *);
//typedef  ��������(*������)(������)  singleModelMatch���͵ĺ���ָ�룬��ָ��ָ��һ��ֻ����3��MIL_ID���͡�4��int���͡�3��double*���͵��βΣ�����ֵΪint*���͵ĺ���


int main() {
	//printf("hello world");
	////���ض�̬���ӿ�hModule��ģ����
	/*HMODULE hModule = LoadLibrary(L"SingleModelMatch.dll");

	if (!hModule)
	{
		cout << "Error!" << endl;
	}*/
	////��ȡ���� GetMaxNumber �ĵ�ַ
	//pGetMaxN pgetm = (pGetMaxN)GetProcAddress(hModule, "GetMaxNumber");
	//cout << pgetm(10, 5) << endl;

	////��ȡ���� ShowMsg �ĵ�ַ
	//pShowMsg pshowm = (pShowMsg)GetProcAddress(hModule, "ShowMsg");
	//pshowm("����", "����");

	//MIL_ID MilApplication,     /* Ӧ��ID*/
	//	MilSystem,          /* ϵͳID */
	//	MilDisplay,         /* ���Ŵ���ID*/
	//	MilImage1,          /* ͼ��1����ID*/
	//	MilImage2;          /* ͼ��2����ID*/

	//						/* ��ʼ��Ӧ�û��� */
	//MappAllocDefault(M_DEFAULT, &MilApplication, &MilSystem, &MilDisplay, M_NULL, M_NULL);

	///*��ͼ������ͼ�񻺳���*/
	///* Restore source image into image buffer. */
	//MbufRestore(M_INTERACTIVE, MilSystem, &MilImage1);

	//MbufRestore(M_INTERACTIVE, MilSystem, &MilImage2);
	//MbufRestore(SINGLE_MODEL_IMAGE1, MilSystem, &MilImage1);
	//MbufRestore(SINGLE_MODEL_IMAGE2, MilSystem, &MilImage2);

	/*������Ʋ���*/
	//int cx1=900,cy1=800,w1=900,h1=500;
	//int cx2=800,cy2=800,w2=900,h2=900;
	//int cx1 = 0, cy1 = 0, w1 = 1626, h1 = 1236;//�ű���ȡ
	//int cx2 = 0, cy2 = 0, w2 = 1626, h2 = 1236;

	/*λ�ý����������������ʼ��*/
	/*double x = 0, y = 0, a = 0;
	double *x1 = &x, *y1 = &y, *a1 = &a;

	double xx = 0, yy = 0, aa = 0;
	double *x2 = &xx, *y2 = &yy, *a2 = &aa;*/

	/*���е�ģ��ƥ����*/
	//singleModelMatch sMfun;//������singleModelMatch���ͱ���sMfun����ʱ�Ϳ�����ʹ����ʽ*singleModelMatchһ��ʹ����������ˡ�
	//sMfun = (singleModelMatch)GetProcAddress(hModule, "SingleModelExample");//��ȡ��̬���ӿ��е�SingleModelExample����
	
	//sMfun(MilSystem, MilDisplay, MilImage1, cx1, cy1, w1, h1, x1, y1, a1);

	//sMfun(MilSystem, MilDisplay, MilImage2, cx2, cy2, w2, h2, x2, y2, a2);
	//�õ�λ�ý��x1 y1 a1����


	//-------------------------------------------------------------------------------------------
	/*����ƫ������������*///΢���豸ģ��Ĺ���
	//double dx = 0, dy = 0, da = 0;

	//dx = *x1 - *x2;
	//dy = *y1 - *y2;
	//da = *a1 - *a2;

	///*��ӡ���*/
	//printf("%-15.2f %-15.2f %-15.2f\n", dx, dy, da);


	/* �ͷ���Դ */
	/*MosGetch();
	MbufFree(MilImage1);
	MbufFree(MilImage2);
	MappFreeDefault(MilApplication, MilSystem, MilDisplay, M_NULL, M_NULL);*/

	return 0;


	//�ͷ�
	//FreeLibrary(hModule);
}

//end test of dll




////�����������
///*ͼƬ��ԴĿ¼*/
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
///*����ģ��ƥ�亯������*/
//void SingleModelExample(MIL_ID MilSystem, MIL_ID MilDisplay, MIL_ID MilImage,
//	int cx, int cy, int w, int h,
//	double *x, double *y, double *a);
//
//void GrabPosition(MIL_ID MilDisplay, Position* DataPtr);	/*ץȡ��������*/
//MIL_INT MFTYPE MouseFct(MIL_INT HookType, MIL_ID EventID, void* UserDataPtr);  /*�ص���������*/
//
//
//
//																			   /*****************************************************************************/
//
//int MosMain(void)
//{
//	MIL_ID MilApplication,     /* Ӧ��ID*/
//		MilSystem,          /* ϵͳID */
//		MilDisplay,         /* ���Ŵ���ID*/
//		MilImage1,          /* ͼ��1����ID*/
//		MilImage2;          /* ͼ��2����ID*/
//
//							/* ��ʼ��Ӧ�û��� */
//	MappAllocDefault(M_DEFAULT, &MilApplication, &MilSystem, &MilDisplay, M_NULL, M_NULL);
//
//	/*����ͼ��*/
//
//	MbufRestore(M_INTERACTIVE, MilSystem, &MilImage1);
//	MbufRestore(M_INTERACTIVE, MilSystem, &MilImage2);
//	//MbufRestore(SINGLE_MODEL_IMAGE1, MilSystem, &MilImage1);
//	//MbufRestore(SINGLE_MODEL_IMAGE2, MilSystem, &MilImage2);
//
//	/*������Ʋ���*/
//	//int cx1=900,cy1=800,w1=900,h1=500;
//	//int cx2=800,cy2=800,w2=900,h2=900;
//	int cx1 = 0, cy1 = 0, w1 = 1626, h1 = 1236;
//	int cx2 = 0, cy2 = 0, w2 = 1626, h2 = 1236;
//
//	/*λ�ý�����*/
//	double x = 0, y = 0, a = 0;
//	double *x1 = &x, *y1 = &y, *a1 = &a;
//
//	double xx = 0, yy = 0, aa = 0;
//	double *x2 = &xx, *y2 = &yy, *a2 = &aa;
//
//	/*���е�ģ��ƥ����*/
//	SingleModelExample(MilSystem, MilDisplay, MilImage1, cx1, cy1, w1, h1, x1, y1, a1);
//	SingleModelExample(MilSystem, MilDisplay, MilImage2, cx2, cy2, w2, h2, x2, y2, a2);
//
//	/*����ƫ������������*/
//	double dx = 0, dy = 0, da = 0;
//
//	dx = *x1 - *x2;
//	dy = *y1 - *y2;
//	da = *a1 - *a2;
//
//	/*��ӡ���*/
//	printf("%-15.2f %-15.2f %-15.2f\n", dx, dy, da);
//
//
//	/* �ͷ���Դ */
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
///* ��ģ��ƥ�亯������*/
//#define SINGLE_MODEL_SEARCH_SPEED   M_LOW        /*����ƥ�������ٶ�*/
//#define MODEL_MAX_OCCURRENCES       2L          /* ���ƥ������ */
//
//
//void SingleModelExample(MIL_ID MilSystem, MIL_ID MilDisplay, MIL_ID MilImage,
//	int cx, int cy, int w, int h,
//	double *x, double *y, double *a)
//{
//	MIL_ID      MilOverlayImage,                  /* ע�Ͳ�ID*/
//		MilChild;                         /* ����Ȥ��ͼ��ID*/
//	MIL_ID      MilSearchContext,                 /* ģ��ƥ�������ID*/
//		MilResult;                        /* ��Եʶ��������ID*/
//	MIL_DOUBLE  ModelDrawColor = M_COLOR_RED;     /* ģ���߿���ɫ*/
//	MIL_INT     Model[MODEL_MAX_OCCURRENCES],     /* ģ���ţ����飩*/
//		NumResults = 0L;                 /* ƥ������*/
//	MIL_DOUBLE  Score[MODEL_MAX_OCCURRENCES],     /* ƥ��������������飩*/
//		XPosition[MODEL_MAX_OCCURRENCES], /* Ŀ��λ��X(����)*/
//		YPosition[MODEL_MAX_OCCURRENCES], /* Ŀ��λ��Y(����) */
//		Angle[MODEL_MAX_OCCURRENCES],     /* Ŀ��Ƕ�λ�ã����飩*/
//		Scale[MODEL_MAX_OCCURRENCES],     /* Ŀ������ֵ�����飩*/
//		Time = 0.0;                       /* ����ʱ�� */
//	int         i;                                /* ���α��� */
//
//
//												  /*ͼƬ��ʾ*/
//	MdispSelect(MilDisplay, MilImage);
//
//	/*ѡ��ROI����ʾ*/
//	MosGetch();
//	MbufChild2d(MilImage, cx, cy, w, h, &MilChild);
//	MdispSelect(MilDisplay, MilChild);
//
//	//�������Hook
//	//Position curPosition = {0,0};
//
//	//Position * pcurPositioon = &curPosition;
//	//MosPrintf(MIL_TEXT("Prepare to Hook\n"));
//	//MdispHookFunction(MilDisplay, M_MOUSE_LEFT_BUTTON_DOWN, MouseFct, pcurPositioon);
//
//	////���Hook������׼��print
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
//	/*ע������*/
//	MdispControl(MilDisplay, M_OVERLAY, M_ENABLE);               /*����ע�Ͳ�*/
//	MdispControl(MilDisplay, M_OVERLAY_CLEAR, M_DEFAULT);        /*ע�Ͳ��ʼ��*/
//	MdispInquire(MilDisplay, M_OVERLAY_ID, &MilOverlayImage);    /*����ע�Ͳ�*/
//
//																 /*Ԥ������ֵ������������*/
//	MosGetch();
//	MimMorphic(MilChild, MilChild, M_3X3_RECT, M_AREA_OPEN, 200, M_GRAYSCALE);
//	MimMorphic(MilChild, MilChild, M_3X3_RECT, M_AREA_CLOSE, 200, M_GRAYSCALE);
//	//MimBinarize(MilChild, MilChild,  M_BIMODAL+M_LESS_OR_EQUAL, M_NULL, M_NULL);
//	//MimMorphic(MilChild, MilChild, M_3X3_RECT , M_AREA_OPEN, 300, M_BINARY);
//	//MimMorphic(MilChild, MilChild, M_3X3_RECT , M_AREA_CLOSE,300, M_BINARY);
//	//MimConvolve(MilChild,MilChild,M_EDGE_DETECT);
//
//	/*ƥ�价������*/
//	MosGetch();
//	MmodAlloc(MilSystem, M_GEOMETRIC, M_DEFAULT, &MilSearchContext); /*����ƥ�������*/
//	MmodAllocResult(MilSystem, M_DEFAULT, &MilResult);/*���������� */
//
//													  /*����ģ��*/
//	MosGetch();
//	//MmodDefine(MilSearchContext, M_RECTANGLE,M_FOREGROUND_BLACK ,98, 40, M_DEFAULT, M_DEFAULT); /*��ͼ����ģ��*/ 
//	//MmodDefineFromFile(MilSearchContext,M_DXF_FILE ,MIL_TEXT("D:\\MOBAN\\JIABN-GEBAO8.dxf") ,M_DEFAULT ); /*���ļ�����ģ��*/  
//	MmodDefineFromFile(MilSearchContext, M_DXF_FILE, M_INTERACTIVE, M_DEFAULT); /*���ļ�����ģ��*/
//
//
//																				/*����ƥ����� */
//	MmodControl(MilSearchContext, M_CONTEXT, M_SPEED, SINGLE_MODEL_SEARCH_SPEED);  /*����ƥ���ٶ� */
//	MmodControl(MilSearchContext, M_CONTEXT, M_SMOOTHNESS, 70);                    /*����ƥ��ƽ���ȣ�����ʶ�𵽵ı�Ե����ƽ������ */
//	MmodControl(MilSearchContext, M_DEFAULT, M_NUMBER, 1);                         /*ƥ��Ŀ���� */
//																				   //MmodControl(MilSearchContext, M_ALL, M_CORNER_RADIUS ,6.0);                    /*��ͼ����ģ���Բ��*/
//
//																				   /*ƥ��Ԥ���� */
//	MmodPreprocess(MilSearchContext, M_DEFAULT);
//
//	/*���ע�Ͳ�*/
//	MdispControl(MilDisplay, M_OVERLAY_CLEAR, M_DEFAULT);
//
//	/*ִ��ƥ��*/
//	//MosGetch();
//	MappTimer(M_TIMER_RESET + M_SYNCHRONOUS, M_NULL);/*������ʱ�� */
//	MmodFind(MilSearchContext, MilChild, MilResult);
//	MappTimer(M_TIMER_READ + M_SYNCHRONOUS, &Time);/*��ȡʱ�� */
//
//												   /*��ȡƥ������ */
//	MmodGetResult(MilResult, M_DEFAULT, M_NUMBER + M_TYPE_MIL_INT, &NumResults);
//
//
//	if ((NumResults >= 1) && (NumResults <= MODEL_MAX_OCCURRENCES))
//	{
//		/*��ȡ*/
//		MmodGetResult(MilResult, M_DEFAULT, M_INDEX + M_TYPE_MIL_INT, Model);
//		MmodGetResult(MilResult, M_DEFAULT, M_POSITION_X, XPosition);
//		MmodGetResult(MilResult, M_DEFAULT, M_POSITION_Y, YPosition);
//		MmodGetResult(MilResult, M_DEFAULT, M_ANGLE, Angle);
//		MmodGetResult(MilResult, M_DEFAULT, M_SCALE, Scale);
//		MmodGetResult(MilResult, M_DEFAULT, M_SCORE, Score);
//
//		/*��ӡ*/
//		MosPrintf(MIL_TEXT("The model was found in the target image:\n\n"));
//		MosPrintf(MIL_TEXT("Result   Model   X Position   Y Position   ") MIL_TEXT("Angle   Scale   Score\n\n"));
//		for (i = 0; i<NumResults; i++)
//		{
//			MosPrintf(MIL_TEXT("%-9d%-8d%-13.2f%-13.2f%-8.2f%-8.2f%-5.2f%%\n"),
//				i, Model[i], XPosition[i], YPosition[i], Angle[i], Scale[i],
//				Score[i]);
//
//			/*�������*/
//			*x = XPosition[i];
//			*y = YPosition[i];
//			*a = Angle[i];
//		}
//
//		/*��ʾ��ʱ*/
//		MosPrintf(MIL_TEXT("\nThe search time is %.1f ms\n\n"), Time*1000.0);
//
//		/* ��ʾƥ����λ�ã������߿�+����ϵ */
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
//	/* �������ͷ���Դ*/
//	MosPrintf(MIL_TEXT("Press <Enter> to end.\n\n"));
//
//	MosGetch();
//	MdispControl(MilDisplay, M_OVERLAY_CLEAR, M_DEFAULT);
//	MbufFree(MilChild);
//	MmodFree(MilSearchContext);
//	MmodFree(MilResult);
//}
//
////����ץȡ����
//void GrabPosition(MIL_ID MilDisplay, Position* DataPtr)
//{
//	Position * pcurPositioon = DataPtr;
//	MosPrintf(MIL_TEXT("Hook in grab\n"));
//	MdispHookFunction(MilDisplay, M_MOUSE_LEFT_BUTTON_DOWN, MouseFct, pcurPositioon);
//	//���Hook������׼��print
//	MosPrintf(MIL_TEXT("print in Grab\n"));
//	MosPrintf(MIL_TEXT("%-9f%-9f%\n"), pcurPositioon->px, pcurPositioon->py);
//	pcurPositioon++;
//}
//
//MIL_INT MFTYPE MouseFct(MIL_INT HookType, MIL_ID EventID, void* UserDataPtr)  /*�ص���������*/
//{
//	Position * MousePosition = (Position *)UserDataPtr;	/*����MousePosition�洢�ṹ��*/
//	if (MousePosition)
//	{
//		if (grabNum > 0)
//		{
//			MdispGetHookInfo(EventID, M_MOUSE_POSITION_BUFFER_X, &(MousePosition->px));
//			MdispGetHookInfo(EventID, M_MOUSE_POSITION_BUFFER_Y, &(MousePosition->py));	/*������洢����ṹ��*/
//			MosPrintf(MIL_TEXT("print in MouseFct\n"));
//			MosPrintf(MIL_TEXT("%-9f%-9f%\n"), MousePosition->px, MousePosition->py);
//			grabNum--;
//			pPoitnt3++;
//		}
//	}
//	return 0;
//}
////��������������

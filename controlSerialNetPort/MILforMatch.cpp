#include"stdafx.h"
#include"MILforMatch.h"

//#include <mil.h>
//#include <iostream>
//using namespace std;


MILforMatch::MILforMatch()
{
}

MILforMatch::~MILforMatch()
{
}


//������
int MILforMatch::mainMIL()
{
    MIL_ID      MilApplication,             /* Ӧ��ID.  */
        MilSystem,                  /* ϵͳID.  */
        MilDisplay,                 /* ��ʾID.  */
        MilImage1, MilImage2;                   /* ͼ��ID.  */

    //��ʼ��Ӧ��//
    MappAllocDefault(M_DEFAULT, &MilApplication, &MilSystem, &MilDisplay, M_NULL, M_NULL);
    /*������Ʋ���*/
    int cx1, cy1, w1, h1;
    int cx2, cy2, w2, h2;

    /*λ�ý�����*/
    double x = 0, y = 0, a = 0;
    double* x1 = &x, * y1 = &y, * a1 = &a;

    double xx = 0, yy = 0, aa = 0;
    double* x2 = &xx, * y2 = &yy, * a2 = &aa;

    /*����ͼ�����е�ģ��ƥ����*/
    //printf("ѡ��Ŀ�����ͼ��\n");
    posinf *p1, *p2;
   

    MbufRestore(M_INTERACTIVE, MilSystem, &MilImage1);
    SingleModelExample(MilSystem, MilDisplay, MilImage1, cx1, cy1, w1, h1, p1);
   // printf("ѡ��������ͼ��\n");
    MbufRestore(M_INTERACTIVE, MilSystem, &MilImage2);
    SingleModelExample(MilSystem, MilDisplay, MilImage2, cx2, cy2, w2, h2, p2);

    /*����ƫ������������*/
    double tx1 = 0, ty1 = 0, tx2 = 0, ty2 = 0, tx3 = 0, ty3 = 0;
    double dx = 0, dy = 0, da = 0, px = 0, py = 0, pa = 0;

    tx1 = *x1 + cx1;
    ty1 = *x2 + cx2;
    tx2 = *y1 + cy1;
    ty2 = *y2 + cy2;

    da = *a1 - *a2;

    tx3 = (tx2 - RATIO_X) * cos(da) + (ty2 - RATIO_Y) * sin(da) + tx2;
    ty3 = -(tx2 - RATIO_X) * sin(da) + (ty2 - RATIO_Y) * cos(da) + ty2;

    dx = tx1 - tx3;
    dy = ty1 - ty3;

    px = (dx * cos(ANG_ERROR_X)) - (dy * sin(ANG_ERROR_X));
    py = (dx * sin(ANG_ERROR_Y)) + (dy * cos(ANG_ERROR_Y));
    pa = da;

    /*��ӡ���*/
   // printf("���壺Xλ����       Yλ����       ANGLE��ת��\n");
    //printf("%-15.2f %-15.2f %-15.2f\n", px, py, pa);

    /*�ͷ���Դ*/
    MbufFree(MilImage1);
    MbufFree(MilImage2);
    MappFreeDefault(MilApplication, MilSystem, MilDisplay, M_NULL, M_NULL);
    return 0;
}


//��Ŀ��ģ��ƥ�亯������
void MILforMatch::SingleModelExample(MIL_ID MilSystem, MIL_ID MilDisplay, MIL_ID MilImage,
    int ROIX, int ROIY, int ROIWidth, int ROIHight,
    posinf* p)
{
    MIL_ID      MilOverlayImage,            /* ע�Ͳ�ID*/
        MilChild;                   /* ����Ȥ��ͼ��ID*/

    MIL_ID      MilSearchContext,                 /*ģ��ƥ�������ID*/
        MilResult;                        /*�������ID*/

    MIL_DOUBLE  ModelDrawColor = M_COLOR_RED;     /* ģ���߿���ɫ*/
    MIL_INT     Model[MODEL_MAX_OCCURRENCES],     /* ģ���ţ����飩*/
        NumResults = 0L;                  /* ƥ������*/

    MIL_DOUBLE  Score[MODEL_MAX_OCCURRENCES],     /* ƥ��������������飩*/
        XPosition[MODEL_MAX_OCCURRENCES], /* Ŀ��λ��X(����)*/
        YPosition[MODEL_MAX_OCCURRENCES], /* Ŀ��λ��Y(����) */
        Angle[MODEL_MAX_OCCURRENCES],     /* Ŀ��Ƕ�λ�ã����飩*/
        Scale[MODEL_MAX_OCCURRENCES],     /* Ŀ������ֵ�����飩*/
        Time = 0.0;                       /* ����ʱ�� */

    int         i;                                /* ���α��� */


    //��ʾԭͼ��//
    //printf("��<space>����ʾԭͼ��\n");
    //MosGetch();
    //MdispSelect(MilDisplay, MilImage); //��ʾͼ��

    //��ʾ������ͼ��
    //printf("��<space>����ʾ������ͼ��\n");
    //MosGetch();
    MbufChild2d(MilImage, ROIX, ROIY, ROIWidth, ROIHight, &MilChild);
    //MdispSelect(MilDisplay, MilChild);


    //ע�Ͳ�����//
    MgraAllocList(MilSystem, M_DEFAULT, &MilOverlayImage);
    MdispControl(MilDisplay, M_ASSOCIATED_GRAPHIC_LIST_ID, MilOverlayImage);

    //��̬ѧ�˲�����//
    //printf("��<space>����ʼ��̬ѧ����\n");
    //MosGetch();
    int MORPHIC_iteration = 800;
    MimMorphic(MilChild, MilChild, M_3X3_RECT, M_AREA_OPEN, MORPHIC_iteration, M_GRAYSCALE);
    MimMorphic(MilChild, MilChild, M_3X3_RECT, M_AREA_CLOSE, MORPHIC_iteration, M_GRAYSCALE);

    //MbufExport(MIL_TEXT("G:\\visual studio\\project\\MILFILTER\\after-gray.png"), M_PNG, MilChild);//����ͼ��

    /*ƥ�价�����ó�ʼ��*/
    MmodAlloc(MilSystem, M_GEOMETRIC, M_DEFAULT, &MilSearchContext); /*����ƥ�������*/
    MmodAllocResult(MilSystem, M_DEFAULT, &MilResult);/*���������� */

    /*���ļ�����ģ��*/
    //printf("��<space>����ʼѡ��ģ��\n");
    //MosGetch();
    MmodDefineFromFile(MilSearchContext, M_DXF_FILE, M_INTERACTIVE, M_DEFAULT);

    /*����ƥ����� */
    MmodControl(MilSearchContext, M_CONTEXT, M_SPEED, SINGLE_MODEL_SEARCH_SPEED);  /*����ƥ���ٶ� */
    MmodControl(MilSearchContext, M_CONTEXT, M_SMOOTHNESS, 100);      /*����ƥ��ƽ���ȣ�����ʶ�𵽵ı�Ե����ƽ������ */
    MmodControl(MilSearchContext, M_DEFAULT, M_NUMBER, 1);          /*ƥ��Ŀ���� */

    /*ƥ��Ԥ���� */
    MmodPreprocess(MilSearchContext, M_DEFAULT);

    /*ִ��ƥ��*/
    MappTimer(M_TIMER_RESET + M_SYNCHRONOUS, M_NULL);
    MmodFind(MilSearchContext, MilChild, MilResult);
    MappTimer(M_TIMER_READ + M_SYNCHRONOUS, &Time);

    /*��ȡƥ������ */
    MmodGetResult(MilResult, M_DEFAULT, M_NUMBER + M_TYPE_MIL_INT, &NumResults);

    if ((NumResults >= 1) && (NumResults <= MODEL_MAX_OCCURRENCES))
    {
        /*��ȡ*/
        MmodGetResult(MilResult, M_DEFAULT, M_INDEX + M_TYPE_MIL_INT, Model);
        MmodGetResult(MilResult, M_DEFAULT, M_POSITION_X, XPosition);
        MmodGetResult(MilResult, M_DEFAULT, M_POSITION_Y, YPosition);
        MmodGetResult(MilResult, M_DEFAULT, M_ANGLE, Angle);
        MmodGetResult(MilResult, M_DEFAULT, M_SCALE, Scale);
        MmodGetResult(MilResult, M_DEFAULT, M_SCORE, Score);

        /*��ӡ*/
       // MosPrintf(MIL_TEXT("The model was found in the target image:\n\n"));
       // MosPrintf(MIL_TEXT("Result   Model   X Position   Y Position   ") MIL_TEXT("Angle   Scale   Score\n\n"));
        for (i = 0; i < NumResults; i++)
        {
           // MosPrintf(MIL_TEXT("%-9d%-8d%-13.2f%-13.2f%-8.2f%-8.2f%-5.2f%%\n"),
              //  i, Model[i], XPosition[i], YPosition[i], Angle[i], Scale[i],
               // Score[i]);
            /*�������*/
            p->stuct_x = XPosition[i];
            p->stuct_y = YPosition[i];
            p->stuct_angle = Angle[i];
        }

        /*��ʾ��ʱ*/
       // MosPrintf(MIL_TEXT("\nThe search time is %.1f ms\n\n"), Time * 1000.0);

        /* ��ʾƥ����λ�ã������߿�+����ϵ */
        for (i = 0; i < NumResults; i++)
        {
            MgraColor(M_DEFAULT, ModelDrawColor);
            MmodDraw(M_DEFAULT, MilResult, MilOverlayImage, M_DRAW_EDGES + M_DRAW_POSITION, i, M_DEFAULT);
            MosGetch();
        }
    }
    else
    {
        MosPrintf(MIL_TEXT("result error !\n\n"));
    }

    //�ͷ�������Դ//
    MbufFree(MilChild);
    MgraFree(MilOverlayImage);
    MmodFree(MilSearchContext);
    MmodFree(MilResult);

}

//�Ƕȱ任����
void MILforMatch::angcalc(posinf* pic1, posinf* pic2, posinf* result)
{
    double a1, a2, da;
    a1 = pic1->stuct_angle;
    a2 = pic2->stuct_angle;
    //a1= (a1>180) ? (a1-180): a1;
    //a2= (a2>180) ? (a2-180): a2;
    da = a1 - a2;
    result->stuct_angle = da * RATIO_A;
}

//λ���ƶ�����
void MILforMatch::poscalc(posinf* pic1, posinf* pic2, posinf* result)
{
    double dx1, dy1, dx2, dy2;
    dx1 = pic1->stuct_x - pic2->stuct_x;
    dy1 = -(pic1->stuct_y - pic2->stuct_y);

    dx2 = (dx1 * cos(ANG_ERROR_X)) - (dy1 * sin(ANG_ERROR_X));
    dy2 = (dx1 * sin(ANG_ERROR_Y)) + (dy1 * cos(ANG_ERROR_Y));

    result->stuct_x = dx2 * RATIO_X;
    result->stuct_y = dy2 * RATIO_Y;

}

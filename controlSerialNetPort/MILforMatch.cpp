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


//主函数
int MILforMatch::mainMIL()
{
    MIL_ID      MilApplication,             /* 应用ID.  */
        MilSystem,                  /* 系统ID.  */
        MilDisplay,                 /* 显示ID.  */
        MilImage1, MilImage2;                   /* 图像ID.  */

    //初始化应用//
    MappAllocDefault(M_DEFAULT, &MilApplication, &MilSystem, &MilDisplay, M_NULL, M_NULL);
    /*定义控制参数*/
    int cx1, cy1, w1, h1;
    int cx2, cy2, w2, h2;

    /*位置结果输出*/
    double x = 0, y = 0, a = 0;
    double* x1 = &x, * y1 = &y, * a1 = &a;

    double xx = 0, yy = 0, aa = 0;
    double* x2 = &xx, * y2 = &yy, * a2 = &aa;

    /*载入图像并运行单模板匹配数*/
    //printf("选择目标零件图像\n");
    posinf *p1, *p2;
   

    MbufRestore(M_INTERACTIVE, MilSystem, &MilImage1);
    SingleModelExample(MilSystem, MilDisplay, MilImage1, cx1, cy1, w1, h1, p1);
   // printf("选择基体零件图像\n");
    MbufRestore(M_INTERACTIVE, MilSystem, &MilImage2);
    SingleModelExample(MilSystem, MilDisplay, MilImage2, cx2, cy2, w2, h2, p2);

    /*计算偏差量及调整量*/
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

    /*打印结果*/
   // printf("脉冲：X位移量       Y位移量       ANGLE旋转量\n");
    //printf("%-15.2f %-15.2f %-15.2f\n", px, py, pa);

    /*释放资源*/
    MbufFree(MilImage1);
    MbufFree(MilImage2);
    MappFreeDefault(MilApplication, MilSystem, MilDisplay, M_NULL, M_NULL);
    return 0;
}


//单目标模板匹配函数定义
void MILforMatch::SingleModelExample(MIL_ID MilSystem, MIL_ID MilDisplay, MIL_ID MilImage,
    int ROIX, int ROIY, int ROIWidth, int ROIHight,
    posinf* p)
{
    MIL_ID      MilOverlayImage,            /* 注释层ID*/
        MilChild;                   /* 感兴趣区图像ID*/

    MIL_ID      MilSearchContext,                 /*模板匹配控制器ID*/
        MilResult;                        /*结果缓存ID*/

    MIL_DOUBLE  ModelDrawColor = M_COLOR_RED;     /* 模板线框颜色*/
    MIL_INT     Model[MODEL_MAX_OCCURRENCES],     /* 模板编号（数组）*/
        NumResults = 0L;                  /* 匹配结果数*/

    MIL_DOUBLE  Score[MODEL_MAX_OCCURRENCES],     /* 匹配评估结果（数组）*/
        XPosition[MODEL_MAX_OCCURRENCES], /* 目标位置X(数组)*/
        YPosition[MODEL_MAX_OCCURRENCES], /* 目标位置Y(数组) */
        Angle[MODEL_MAX_OCCURRENCES],     /* 目标角度位置（数组）*/
        Scale[MODEL_MAX_OCCURRENCES],     /* 目标缩放值（数组）*/
        Time = 0.0;                       /* 所用时间 */

    int         i;                                /* 整形变量 */


    //显示原图像//
    //printf("按<space>键显示原图像\n");
    //MosGetch();
    //MdispSelect(MilDisplay, MilImage); //显示图像

    //显示子区域图像
    //printf("按<space>键显示子区域图像\n");
    //MosGetch();
    MbufChild2d(MilImage, ROIX, ROIY, ROIWidth, ROIHight, &MilChild);
    //MdispSelect(MilDisplay, MilChild);


    //注释层设置//
    MgraAllocList(MilSystem, M_DEFAULT, &MilOverlayImage);
    MdispControl(MilDisplay, M_ASSOCIATED_GRAPHIC_LIST_ID, MilOverlayImage);

    //形态学滤波处理//
    //printf("按<space>键开始形态学处理\n");
    //MosGetch();
    int MORPHIC_iteration = 800;
    MimMorphic(MilChild, MilChild, M_3X3_RECT, M_AREA_OPEN, MORPHIC_iteration, M_GRAYSCALE);
    MimMorphic(MilChild, MilChild, M_3X3_RECT, M_AREA_CLOSE, MORPHIC_iteration, M_GRAYSCALE);

    //MbufExport(MIL_TEXT("G:\\visual studio\\project\\MILFILTER\\after-gray.png"), M_PNG, MilChild);//保存图像

    /*匹配环境设置初始化*/
    MmodAlloc(MilSystem, M_GEOMETRIC, M_DEFAULT, &MilSearchContext); /*分配匹配控制器*/
    MmodAllocResult(MilSystem, M_DEFAULT, &MilResult);/*分配结果缓存 */

    /*从文件定义模板*/
    //printf("按<space>键开始选择模板\n");
    //MosGetch();
    MmodDefineFromFile(MilSearchContext, M_DXF_FILE, M_INTERACTIVE, M_DEFAULT);

    /*设置匹配参数 */
    MmodControl(MilSearchContext, M_CONTEXT, M_SPEED, SINGLE_MODEL_SEARCH_SPEED);  /*设置匹配速度 */
    MmodControl(MilSearchContext, M_CONTEXT, M_SMOOTHNESS, 100);      /*设置匹配平滑度（对于识别到的边缘进行平滑处理） */
    MmodControl(MilSearchContext, M_DEFAULT, M_NUMBER, 1);          /*匹配目标数 */

    /*匹配预处理 */
    MmodPreprocess(MilSearchContext, M_DEFAULT);

    /*执行匹配*/
    MappTimer(M_TIMER_RESET + M_SYNCHRONOUS, M_NULL);
    MmodFind(MilSearchContext, MilChild, MilResult);
    MappTimer(M_TIMER_READ + M_SYNCHRONOUS, &Time);

    /*读取匹配结果数 */
    MmodGetResult(MilResult, M_DEFAULT, M_NUMBER + M_TYPE_MIL_INT, &NumResults);

    if ((NumResults >= 1) && (NumResults <= MODEL_MAX_OCCURRENCES))
    {
        /*读取*/
        MmodGetResult(MilResult, M_DEFAULT, M_INDEX + M_TYPE_MIL_INT, Model);
        MmodGetResult(MilResult, M_DEFAULT, M_POSITION_X, XPosition);
        MmodGetResult(MilResult, M_DEFAULT, M_POSITION_Y, YPosition);
        MmodGetResult(MilResult, M_DEFAULT, M_ANGLE, Angle);
        MmodGetResult(MilResult, M_DEFAULT, M_SCALE, Scale);
        MmodGetResult(MilResult, M_DEFAULT, M_SCORE, Score);

        /*打印*/
       // MosPrintf(MIL_TEXT("The model was found in the target image:\n\n"));
       // MosPrintf(MIL_TEXT("Result   Model   X Position   Y Position   ") MIL_TEXT("Angle   Scale   Score\n\n"));
        for (i = 0; i < NumResults; i++)
        {
           // MosPrintf(MIL_TEXT("%-9d%-8d%-13.2f%-13.2f%-8.2f%-8.2f%-5.2f%%\n"),
              //  i, Model[i], XPosition[i], YPosition[i], Angle[i], Scale[i],
               // Score[i]);
            /*结果传递*/
            p->stuct_x = XPosition[i];
            p->stuct_y = YPosition[i];
            p->stuct_angle = Angle[i];
        }

        /*显示用时*/
       // MosPrintf(MIL_TEXT("\nThe search time is %.1f ms\n\n"), Time * 1000.0);

        /* 显示匹配结果位置，包括线框+坐标系 */
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

    //释放所有资源//
    MbufFree(MilChild);
    MgraFree(MilOverlayImage);
    MmodFree(MilSearchContext);
    MmodFree(MilResult);

}

//角度变换函数
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

//位移移动函数
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

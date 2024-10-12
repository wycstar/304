#pragma once
#include <mil.h>
#include <iostream>
//using namespace std;

//轴运动角度误差
#define ANG_ERROR_X        -0.032  //G1
#define ANG_ERROR_Y        -0.033 //G1
//回转中心坐标
#define RATIO_X            0   //G1
#define RATIO_Y            0   //G1
#define RATIO_A            0//标定得到的结果

#define SINGLE_MODEL_SEARCH_SPEED   M_LOW       /*设置匹配搜索速度*/
#define MODEL_MAX_OCCURRENCES       2L          /* 最大匹配结果数 */


typedef struct
{
    double stuct_angle;
    double stuct_x;
    double stuct_y;

} posinf;


class MILforMatch
{
public:
	MILforMatch();
	~MILforMatch();

private:

public:
    //单目标模板匹配函数声明
    void SingleModelExample(MIL_ID MilSystem, MIL_ID MilDisplay, MIL_ID MilImage,
        int ROIX, int ROIY, int ROIWidth, int ROIHight,
        posinf* p);

    //角度调整函数声明
    void angcalc(posinf* pic1, posinf* pic2, posinf* result);
    //位置调整函数声明
    void poscalc(posinf* pic1, posinf* pic2, posinf* result);

    //主函数
    int mainMIL();


    //单目标模板匹配函数定义
 /*   void SingleModelExample(MIL_ID MilSystem, MIL_ID MilDisplay, MIL_ID MilImage,
        int cx, int cy, int w, int h,
        double* x, double* y, double* a);*/

    //角度变换函数
    //void angcalc(posinf* pic1, posinf* pic2, posinf* result);

    //位移移动函数
    //void poscalc(posinf* pic1, posinf* pic2, posinf* result);

};


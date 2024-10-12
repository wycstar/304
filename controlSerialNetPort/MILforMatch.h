#pragma once
#include <mil.h>
#include <iostream>
//using namespace std;

//���˶��Ƕ����
#define ANG_ERROR_X        -0.032  //G1
#define ANG_ERROR_Y        -0.033 //G1
//��ת��������
#define RATIO_X            0   //G1
#define RATIO_Y            0   //G1
#define RATIO_A            0//�궨�õ��Ľ��

#define SINGLE_MODEL_SEARCH_SPEED   M_LOW       /*����ƥ�������ٶ�*/
#define MODEL_MAX_OCCURRENCES       2L          /* ���ƥ������ */


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
    //��Ŀ��ģ��ƥ�亯������
    void SingleModelExample(MIL_ID MilSystem, MIL_ID MilDisplay, MIL_ID MilImage,
        int ROIX, int ROIY, int ROIWidth, int ROIHight,
        posinf* p);

    //�Ƕȵ�����������
    void angcalc(posinf* pic1, posinf* pic2, posinf* result);
    //λ�õ�����������
    void poscalc(posinf* pic1, posinf* pic2, posinf* result);

    //������
    int mainMIL();


    //��Ŀ��ģ��ƥ�亯������
 /*   void SingleModelExample(MIL_ID MilSystem, MIL_ID MilDisplay, MIL_ID MilImage,
        int cx, int cy, int w, int h,
        double* x, double* y, double* a);*/

    //�Ƕȱ任����
    //void angcalc(posinf* pic1, posinf* pic2, posinf* result);

    //λ���ƶ�����
    //void poscalc(posinf* pic1, posinf* pic2, posinf* result);

};


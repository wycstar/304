// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� MYDLL_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// MYDLL_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#include <mil.h>
#include <iostream>


#ifdef MYDLL_EXPORTS
#define MYDLL_API __declspec(dllexport)
#else
#define MYDLL_API __declspec(dllimport)
#endif

//extern "C" MYDLL_API  int GetMaxNumber(int, int);
//extern "C" MYDLL_API void ShowMsg(char *, char*);

extern "C" MYDLL_API void SingleModelExample(MIL_ID MilSystem, MIL_ID MilDisplay, MIL_ID MilImage,
	int cx, int cy, int w, int h,
	double *x, double *y, double *a);

// �����Ǵ� myDLL.dll ������


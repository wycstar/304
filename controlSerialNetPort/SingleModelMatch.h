#pragma once
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

//ģ��ƥ�亯������
extern "C" MYDLL_API int SingleModelMatch(MIL_ID MilSystem, MIL_ID MilImage,
	int workNum, int cx, int cy, int w, int h, int processStep, MIL_CONST_TEXT_PTR  modelFilePath,
	double *x, double *y, double *a);

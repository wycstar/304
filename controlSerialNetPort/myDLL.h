// 下列 ifdef 块是创建使从 DLL 导出更简单的
// 宏的标准方法。此 DLL 中的所有文件都是用命令行上定义的 MYDLL_EXPORTS
// 符号编译的。在使用此 DLL 的
// 任何其他项目上不应定义此符号。这样，源文件中包含此文件的任何其他项目都会将
// MYDLL_API 函数视为是从 DLL 导入的，而此 DLL 则将用此宏定义的
// 符号视为是被导出的。
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

// 此类是从 myDLL.dll 导出的


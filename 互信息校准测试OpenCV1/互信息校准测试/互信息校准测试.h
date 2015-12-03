
// 互信息校准测试.h : PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号


// C互信息校准测试App: 
// 有关此类的实现，请参阅 互信息校准测试.cpp
//

class C互信息校准测试App : public CWinApp
{
public:
	C互信息校准测试App();

// 重写
public:
	virtual BOOL InitInstance();

// 实现

	DECLARE_MESSAGE_MAP()
};

extern C互信息校准测试App theApp;
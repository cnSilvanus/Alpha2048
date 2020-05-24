﻿
// Alpha2048.h: PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含 'pch.h' 以生成 PCH"
#endif

#include "resource.h"		// 主符号


// CAlpha2048App:
// 有关此类的实现，请参阅 Alpha2048.cpp
//

class CAlpha2048App : public CWinApp
{
public:
	// 内部变量
	CString nType;
	CString nScore;
	bool nMax;
	bool IsGameOver;
	bool IRON;
	bool TRAN;
	bool DISS;
	bool BACK;
	CAlpha2048App();

// 重写
public:
	virtual BOOL InitInstance();

// 实现

	DECLARE_MESSAGE_MAP()
};

extern CAlpha2048App theApp;

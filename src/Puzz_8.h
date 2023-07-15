
// Puzz_8.h : main header file for the application
//

#pragma once

#ifndef __AFXWIN_H__
#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h" // main symbols

// CPuzz_8App:
// See Puzz_8.cpp for the implementation of this class
//

class CPuzz_8App : public CWinApp
{
public:
	CPuzz_8App();

	// Overrides
public:
	virtual BOOL InitInstance();

	// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CPuzz_8App theApp;

// Data_Manager.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CData_ManagerApp:
// �� Ŭ������ ������ ���ؼ��� Data_Manager.cpp�� �����Ͻʽÿ�.
//

class CData_ManagerApp : public CWinApp
{
public:
	CData_ManagerApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CData_ManagerApp theApp;
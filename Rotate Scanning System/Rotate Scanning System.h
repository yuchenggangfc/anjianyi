
// Rotate Scanning System.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CRotateScanningSystemApp: 
// �йش����ʵ�֣������ Rotate Scanning System.cpp
//

class CRotateScanningSystemApp : public CWinApp
{
public:
	CRotateScanningSystemApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};
extern CString TcpIp;
extern CString TcpPort;
extern CString UdpM_uLocalPort;
extern CString UdpOtherIp;
extern CString UdpOtherPort;
extern CString UdpLocalIp;
extern CString UdpLocalPort;
extern CRotateScanningSystemApp theApp;

// Rotate Scanning System.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "Rotate Scanning System.h"
#include "Rotate Scanning SystemDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
CString TcpIp;
CString TcpPort;
CString UdpM_uLocalPort;
CString UdpOtherIp;
CString UdpOtherPort;
CString UdpLocalIp;
CString UdpLocalPort;
// CLoginDlg 对话框
CStringArray settings;

// CRotateScanningSystemApp

BEGIN_MESSAGE_MAP(CRotateScanningSystemApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CRotateScanningSystemApp 构造

CRotateScanningSystemApp::CRotateScanningSystemApp()
{
	// 支持重新启动管理器
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;
	CFileFind finder;
	::GetPrivateProfileStringW(_T("settings"), _T("TCP_IP"), _T("没找到TCP_IP信息"), TcpIp.GetBuffer(MAX_PATH), MAX_PATH, _T("C:\\settings.ini"));
	::GetPrivateProfileStringW(_T("settings"), _T("TCP_Port"), _T("没找到TCP_Port信息"), TcpPort.GetBuffer(MAX_PATH), MAX_PATH, _T("C:\\settings.ini"));
	::GetPrivateProfileStringW(_T("settings"), _T("UDP_m_uLocalPort"), _T("没找到UDP_m_uLocalPort信息"), UdpM_uLocalPort.GetBuffer(MAX_PATH), MAX_PATH, _T("C:\\settings.ini"));
	::GetPrivateProfileStringW(_T("settings"), _T("UDP_otherIP"), _T("没找到UDP_otherIP信息"), UdpOtherIp.GetBuffer(MAX_PATH), MAX_PATH, _T("C:\\settings.ini"));
	::GetPrivateProfileStringW(_T("settings"), _T("UDP_otherPort"), _T("没找到UDP_otherPort信息"), UdpOtherPort.GetBuffer(MAX_PATH), MAX_PATH, _T("C:\\settings.ini"));
	::GetPrivateProfileStringW(_T("settings"), _T("UDP_localIP"), _T("没找到UDP_localIP信息"), UdpLocalIp.GetBuffer(MAX_PATH), MAX_PATH, _T("C:\\settings.ini"));
	::GetPrivateProfileStringW(_T("settings"), _T("UDP_localPORT"), _T("没找到UDP_localPORT信息"), UdpLocalPort.GetBuffer(MAX_PATH), MAX_PATH, _T("C:\\settings.ini"));
	TcpIp.ReleaseBuffer();
	TcpPort.ReleaseBuffer();
	UdpM_uLocalPort.ReleaseBuffer();
	UdpOtherIp.ReleaseBuffer();
	UdpOtherPort.ReleaseBuffer();
	UdpLocalIp.ReleaseBuffer();
	UdpLocalPort.ReleaseBuffer();
	
	//CString strFileName;
	//strFileName = "C:\\settings.ini";
	//CStdioFile file;
	//BOOL ret = file.Open(strFileName, CFile::modeRead | CFile::shareDenyNone);
	//file.SeekToBegin();
	//CString cstrLine;
	//while (file.ReadString(cstrLine))
	//{
	//	int nPos = cstrLine.Find(':');
	//	CString sSubStr = cstrLine.Right(cstrLine.GetLength() - nPos - 1);
	//	settings.Add(sSubStr);
	//}
	//TcpIp = settings[0];
	//TcpPort = settings[1];
	//UdpM_uLocalPort = settings[2];
	//UdpOtherIp = settings[3];
	//UdpOtherPort = settings[4];
	//UdpLocalIp = settings[5];
	//UdpLocalPort = settings[6];
	//// 关闭文件
	//file.Close();


	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 CRotateScanningSystemApp 对象

CRotateScanningSystemApp theApp;


// CRotateScanningSystemApp 初始化

BOOL CRotateScanningSystemApp::InitInstance()
{
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。  否则，将无法创建窗口。

	
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}


	AfxEnableControlContainer();

	// 创建 shell 管理器，以防对话框包含
	// 任何 shell 树视图控件或 shell 列表视图控件。
	CShellManager *pShellManager = new CShellManager;

	// 激活“Windows Native”视觉管理器，以便在 MFC 控件中启用主题
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));

	CRotateScanningSystemDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: 在此放置处理何时用
		//  “确定”来关闭对话框的代码
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: 在此放置处理何时用
		//  “取消”来关闭对话框的代码
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "警告: 对话框创建失败，应用程序将意外终止。\n");
		TRACE(traceAppMsg, 0, "警告: 如果您在对话框上使用 MFC 控件，则无法 #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS。\n");
	}

	// 删除上面创建的 shell 管理器。
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
	//  而不是启动应用程序的消息泵。
	return FALSE;
}



// Rotate Scanning System.cpp : ����Ӧ�ó��������Ϊ��
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
// CLoginDlg �Ի���
CStringArray settings;

// CRotateScanningSystemApp

BEGIN_MESSAGE_MAP(CRotateScanningSystemApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CRotateScanningSystemApp ����

CRotateScanningSystemApp::CRotateScanningSystemApp()
{
	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;
	CFileFind finder;
	::GetPrivateProfileStringW(_T("settings"), _T("TCP_IP"), _T("û�ҵ�TCP_IP��Ϣ"), TcpIp.GetBuffer(MAX_PATH), MAX_PATH, _T("C:\\settings.ini"));
	::GetPrivateProfileStringW(_T("settings"), _T("TCP_Port"), _T("û�ҵ�TCP_Port��Ϣ"), TcpPort.GetBuffer(MAX_PATH), MAX_PATH, _T("C:\\settings.ini"));
	::GetPrivateProfileStringW(_T("settings"), _T("UDP_m_uLocalPort"), _T("û�ҵ�UDP_m_uLocalPort��Ϣ"), UdpM_uLocalPort.GetBuffer(MAX_PATH), MAX_PATH, _T("C:\\settings.ini"));
	::GetPrivateProfileStringW(_T("settings"), _T("UDP_otherIP"), _T("û�ҵ�UDP_otherIP��Ϣ"), UdpOtherIp.GetBuffer(MAX_PATH), MAX_PATH, _T("C:\\settings.ini"));
	::GetPrivateProfileStringW(_T("settings"), _T("UDP_otherPort"), _T("û�ҵ�UDP_otherPort��Ϣ"), UdpOtherPort.GetBuffer(MAX_PATH), MAX_PATH, _T("C:\\settings.ini"));
	::GetPrivateProfileStringW(_T("settings"), _T("UDP_localIP"), _T("û�ҵ�UDP_localIP��Ϣ"), UdpLocalIp.GetBuffer(MAX_PATH), MAX_PATH, _T("C:\\settings.ini"));
	::GetPrivateProfileStringW(_T("settings"), _T("UDP_localPORT"), _T("û�ҵ�UDP_localPORT��Ϣ"), UdpLocalPort.GetBuffer(MAX_PATH), MAX_PATH, _T("C:\\settings.ini"));
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
	//// �ر��ļ�
	//file.Close();


	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CRotateScanningSystemApp ����

CRotateScanningSystemApp theApp;


// CRotateScanningSystemApp ��ʼ��

BOOL CRotateScanningSystemApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()��  ���򣬽��޷��������ڡ�

	
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}


	AfxEnableControlContainer();

	// ���� shell ���������Է��Ի������
	// �κ� shell ����ͼ�ؼ��� shell �б���ͼ�ؼ���
	CShellManager *pShellManager = new CShellManager;

	// ���Windows Native���Ӿ����������Ա��� MFC �ؼ�����������
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

	CRotateScanningSystemDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȷ�������رնԻ���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȡ�������رնԻ���Ĵ���
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "����: �Ի��򴴽�ʧ�ܣ�Ӧ�ó���������ֹ��\n");
		TRACE(traceAppMsg, 0, "����: ������ڶԻ�����ʹ�� MFC �ؼ������޷� #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS��\n");
	}

	// ɾ�����洴���� shell ��������
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}


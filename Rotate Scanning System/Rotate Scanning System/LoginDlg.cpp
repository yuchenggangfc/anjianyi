// LoginDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"

#include "LoginDlg.h"
#include "afxdialogex.h"

BOOL CLoginDlg::OnInitDialog()
{
	//��ʼ���Ի���
	CDialogEx::OnInitDialog();

	CRect rect;
	GetClientRect(&rect);     //ȡ�ͻ�����С    
	old.x = rect.right - rect.left;
	old.y = rect.bottom - rect.top;
	int cx = GetSystemMetrics(SM_CXFULLSCREEN);
	int cy = GetSystemMetrics(SM_CYFULLSCREEN);
	CRect rt;
	SystemParametersInfo(SPI_GETWORKAREA, 0, &rt, 0);
	cy = rt.bottom;
	MoveWindow((int)cx / 3, (int)cy / 3, (int)cx / 3, (int)cy / 3);

	m_workmode.SetCurSel(0);
	//�������壬ͼ����ɫ��
	l_font.CreatePointFont(150, _T("����"));
	log_bar.SetBackColor(RGB(200,0,0));
	main_bar.SetBackColor(RGB(255, 255, 255));//
	main_bar.SetFont(&l_font);
	combo_user.SetCurSel(0);
	e_password.SetPasswordChar('*');
	e_password.SetFocus();
	return true;

}

IMPLEMENT_DYNAMIC(CLoginDlg, CDialogEx)

CLoginDlg::CLoginDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_LOGIN, pParent)
{

}

CLoginDlg::~CLoginDlg()
{
}


void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_WorkMode, m_workmode);
	DDX_Control(pDX, IDC_STATIC_Bar, log_bar);

	DDX_Control(pDX, IDC_COMBO_User, combo_user);
	DDX_Control(pDX, IDC_PassWord, e_password);
	DDX_Control(pDX, IDC_STATIC_Main, main_bar);
}


BEGIN_MESSAGE_MAP(CLoginDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CLoginDlg::OnBnClickedOk)
	ON_CBN_SELCHANGE(IDC_WorkMode, &CLoginDlg::OnCbnSelchangeWorkmode)
	ON_WM_SIZE()
END_MESSAGE_MAP()


void CLoginDlg::OnBnClickedOk()
{
	//��½
	CString pwd;
	int index;
	index = combo_user.GetCurSel();
	GetDlgItem(IDC_PassWord)->GetWindowTextW(pwd);
	if (index == 0 && pwd != _T("1"))
	{
		MessageBox(_T("�������"), _T("����"));
	}

	else
	{
		wm = m_workmode.GetCurSel();
		combo_user.GetLBText(combo_user.GetCurSel(),user);
		OnOK();
	}
}


void CLoginDlg::OnCbnSelchangeWorkmode()
{

	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

void CLoginDlg::ReSize(void)
{
	float fsp[2];
	POINT Newp; //��ȡ���ڶԻ���Ĵ�С  
	CRect recta;
	GetClientRect(&recta);     //ȡ�ͻ�����С    
	Newp.x = recta.right - recta.left;
	Newp.y = recta.bottom - recta.top;
	fsp[0] = (float)Newp.x / old.x;
	fsp[1] = (float)Newp.y / old.y;
	CRect Rect;
	int woc, mainid;
	CPoint OldTLPoint, TLPoint; //���Ͻ�  
	CPoint OldBRPoint, BRPoint; //���½�  
	HWND  hwndChild = ::GetWindow(m_hWnd, GW_CHILD);  //�г����пؼ� 


	while (hwndChild)
	{
		woc = ::GetDlgCtrlID(hwndChild);//ȡ��ID
		GetDlgItem(woc)->GetWindowRect(Rect);
		ScreenToClient(Rect);
		OldTLPoint = Rect.TopLeft();
		TLPoint.x = long(OldTLPoint.x*fsp[0]);
		TLPoint.y = long(OldTLPoint.y*fsp[1]);
		OldBRPoint = Rect.BottomRight();
		BRPoint.x = long(OldBRPoint.x *fsp[0]);
		BRPoint.y = long(OldBRPoint.y *fsp[1]);
		Rect.SetRect(TLPoint, BRPoint);
		GetDlgItem(woc)->MoveWindow(Rect, TRUE);
		hwndChild = ::GetWindow(hwndChild, GW_HWNDNEXT);
	}
	old = Newp;
}

void CLoginDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	CDialogEx::OnSize(nType, cx, cy);
	ReSize();
}


// Rotate Scanning SystemDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Rotate Scanning System.h"
#include "Rotate Scanning SystemDlg.h"
#include "afxdialogex.h"
#include "TCPClient.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���
volatile bool save_ok;

CString s_results[25];
int a, b;
int d_results[25];
int motor_stop;


class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CRotateScanningSystemDlg �Ի���



CRotateScanningSystemDlg::CRotateScanningSystemDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_ROTATESCANNINGSYSTEM_DIALOG, pParent)
	, s_encoder_pos(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	memset(m_nzValues, 0, sizeof(int) * POINT_COUNT);
}

void CRotateScanningSystemDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_WAVE_DRAW, m_picDraw);
	DDX_Control(pDX, IDC_STATIC1, stc_title);
	DDX_Control(pDX, IDC_STATIC_Mainbar, main_bar);
	DDX_Control(pDX, IDC_EDIT_User, e_user);
	DDX_Control(pDX, IDC_STATIC_State, plc_state);
	DDX_Control(pDX, IDC_COMBO_Wm, c_workmode);
	DDX_Control(pDX, IDC_EDIT_Recv1, e_errorcode);
	DDX_Control(pDX, IDC_EDIT_MPos, motor_pos);
	DDX_Control(pDX, IDC_EDIT_EPos, encoder_pos);
	DDX_Text(pDX, IDC_EDIT_EPos, s_encoder_pos);
	DDX_Control(pDX, IDC_STATIC_State2, d_state);
	DDX_Control(pDX, IDC_STATIC_State3, fpga_state);
	DDX_Control(pDX, IDC_Loop, loop_check);
	DDX_Control(pDX, IDC_Trig, trig_out);
	DDX_Control(pDX, IDC_EDIT_Speed, scan_speed);
	DDX_Control(pDX, IDC_Save, save_check);
	DDX_Control(pDX, IDC_Info, system_info);
}

BEGIN_MESSAGE_MAP(CRotateScanningSystemDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CRotateScanningSystemDlg::OnBnClickedOk)
	ON_WM_TIMER()
	ON_COMMAND(ID_32772, &CRotateScanningSystemDlg::OnCommSet)
	ON_COMMAND(ID_32774, &CRotateScanningSystemDlg::OnMotionSet)
	ON_COMMAND(ID_32773, &CRotateScanningSystemDlg::OnParaSet)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_Reset, &CRotateScanningSystemDlg::OnBnClickedReset)
	ON_BN_CLICKED(IDC_Stop, &CRotateScanningSystemDlg::OnBnClickedStop)

	ON_MESSAGE(WM_DISPLAY_CHANGE, OnDisplayChange)

	ON_BN_CLICKED(IDC_Start, &CRotateScanningSystemDlg::OnBnClickedStart)
	ON_BN_CLICKED(IDC_Exit, &CRotateScanningSystemDlg::OnBnClickedExit)
	ON_BN_CLICKED(IDC_Loop, &CRotateScanningSystemDlg::OnBnClickedLoop)
	ON_BN_CLICKED(IDC_Trig, &CRotateScanningSystemDlg::OnBnClickedTrig)
	ON_BN_CLICKED(IDC_BUTTON3, &CRotateScanningSystemDlg::OnBnClickedButton3)
	//ON_STN_CLICKED(IDC_WAVE_DRAW, &CRotateScanningSystemDlg::OnStnClickedWaveDraw)
	ON_BN_CLICKED(IDC_Save, &CRotateScanningSystemDlg::OnBnClickedSave)
	ON_WM_SIZE()
END_MESSAGE_MAP()

// CRotateScanningSystemDlg ��Ϣ�������

BOOL CRotateScanningSystemDlg::OnInitDialog()
{
	//��ʼ��
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
	MoveWindow((int)cx / 8, (int)cy / 8, (int)cx * 3 / 4, (int)cy * 3 / 4);

	if (m_loginDlg.DoModal() != IDOK)
	{
		OnOK();
	}
	//����ģʽ���û����ӵ�½���洫��������
	CString workmode,username;
	c_workmode.SetCurSel(m_loginDlg.wm);
	username = m_loginDlg.user;
	e_user.SetWindowTextW(username);
	// ��������...���˵�����ӵ�ϵͳ�˵��С�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
	

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�ִ�д˲���

	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	//���ò˵�
	pMenu = new CMenu();
	pMenu->LoadMenu(IDR_MENU1);
	SetMenu(pMenu);
	//��������
	m_font.CreatePointFont(250, _T("����"));
	stc_title.SetFont(&m_font);
	stc_title.SetBackColor(RGB(255, 255, 255));
	main_bar.SetBackColor(RGB(200,0,0));
	plc_state.SetBackColor(RGB(0, 220, 0));
	plc_state.SetWindowTextW(_T("PLC OK"));
	d_state.SetBackColor(RGB(0, 220, 0));
	d_state.SetWindowTextW(_T("Motor OK"));

	GetDlgItem(IDC_STC_Ver)->SetWindowTextW(_T("2.1.0"));

	//��ȡ��ǰ·��
	TCHAR buf[1024];
	GetCurrentDirectory(sizeof(buf), buf);
	path = buf;
	path = path + _T("\\Config");

	//�������
	int pos = 0;            //��ǰλ��
	int pos_before = 0;     //�ϴζ�ȡ��λ��
	long secstop = 0;       //ֹͣʱ��
	long secstart = 0;      //��ʼʱ��
	bool running = false;   //����״̬
	save_ok = false;

	//�ж�FPGAģ��ͨ���Ƿ�����
	if (fpga.UDPConnect())
	{
		fpga_state.SetBackColor(RGB(0, 200, 0));
		fpga_state.SetWindowTextW(_T("FPGA OK"));
	}
	else
	{
		fpga_state.SetBackColor(RGB(200, 0, 0));
		fpga_state.SetWindowTextW(_T("FPGA Error"));
		MessageBox(_T("FPGAģ������ʧ�ܣ�������������г���"), _T("����"));
		PostQuitMessage(0);
		return false;
	}

	//�ж�PLCͨ���Ƿ�����
	if (tcp.TCP_Connect())
	{
		plc_state.SetBackColor(RGB(0, 200, 0));
		plc_state.SetWindowTextW(_T("PLC OK"));
	}
	else
	{
		MessageBox(_T("PLC����ʧ�ܣ�����������������г���"), _T("����"));
		plc_state.SetBackColor(RGB(200, 0, 0));
		plc_state.SetWindowTextW(_T("PLC Error"));
		PostQuitMessage(0);
		return false;
	}

	// ������ʱ����IDΪ1����ʱʱ��Ϊ200ms���Ըü��ѭ����ȡPLC����  
	SetTimer(1, 50, NULL);

	hThread = CreateThread(NULL,
	0,
	(LPTHREAD_START_ROUTINE)ReadAllParas,
	NULL,
	0,
	&ThreadID);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CRotateScanningSystemDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

HCURSOR CRotateScanningSystemDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CRotateScanningSystemDlg::OnBnClickedOk()

{
		
}

void CRotateScanningSystemDlg::OnTimer(UINT_PTR nIDEvent)
{
	//��ȡ������λ��
	double epos = fpga.GetCurrentPos();
	//if (epos > 300)
		//epos = epos - 360;
	epos = 203.515 - epos;

	CString s_epos;
	s_epos.Format(_T("%3f"), epos);
	encoder_pos.SetWindowTextW(s_epos);
	//������ѭ�����Ե�ǰ����
	CString looptime = s_results[23];
	if (loop_check.GetCheck() == true)
		system_info.SetWindowTextW(looptime);
	//���������˶��ٶ�
	scan_speed.SetWindowTextW(tcp.AddPoint(s_results[15]));
	////��ȡ�˶�����
	//int a = tcp.ReadM(121) / 16;
	//int b = tcp.ReadM(123) / 16;
	/*if (a == 1)
	{
		GetDlgItem(IDC_EDIT_Dir)->SetWindowTextW(_T("�����˶�"));
	}
	else if (b == 1)
	{
		GetDlgItem(IDC_EDIT_Dir)->SetWindowTextW(_T("�����˶�"));
	}
	else
	{
		GetDlgItem(IDC_EDIT_Dir)->SetWindowTextW(_T("���ֹͣ"));
	}*/



	if (motor_stop == 16)
	{
		GetDlgItem(IDC_Start)->EnableWindow(true);
		GetDlgItem(IDC_Reset)->EnableWindow(true);
		GetDlgItem(IDC_EDIT_Dir)->SetWindowTextW(_T("���ֹͣ"));
	}
	else
	{
		//GetDlgItem(IDC_Start)->EnableWindow(false);
		//GetDlgItem(IDC_Reset)->EnableWindow(false);
		GetDlgItem(IDC_EDIT_Dir)->SetWindowTextW(_T("�������"));
		//��ʾ����ʱ��
		CString testtime;
		testtime.Format(_T("%d"), d_results[24]);
		GetDlgItem(IDC_EDIT_Ttime)->SetWindowTextW(testtime+_T("ms"));
	}

	//��ʾ�ٶ�
	CString testv;
	testv.Format(_T("%d"), d_results[16] / 100);
	GetDlgItem(IDC_EDIT_Speed)->SetWindowTextW(testv);

	CRect rectPicture;

	//�������е�����Ԫ��ǰ��һ����λ����һ��Ԫ�ض���   
	for (int i = 0; i < POINT_COUNT - 1; i++)
	{
		m_nzValues[i] = m_nzValues[i + 1];
	}
	//������ǰλ��
	CString s_pos;
	pos = d_results[10];
	if (pos < 0)
	{
		pos = 0;
	}

	CTime time = CTime::GetCurrentTime();	
	CString m_strTime = time.Format("%Y-%m-%d %H:%M:%S");
	GetDlgItem(IDC_STATIC_Time)->SetWindowTextW(m_strTime);

	//����ÿ��ɨ���ʱ�䲢��ʾ
	secstop = GetTickCount();

	if (pos == pos_before && running == true && motor_stop == 16)
	{
		//����ɨ�����������ɨ��ʱ�䣬��ȡ�����Ƕ�,����ʱ�����Ϣ
		//CString scan_time;
		//scan_time.Format(_T("%d"),secstop - secstart);
		//GetDlgItem(IDC_EDIT_Ttime)->SetWindowTextW(s_results[23]+_T("ms"));
		if (loop_check.GetCheck() == false)
			//running = false;

		//��ȡFPGA�����Ƕȼ�ʱ����Ϣ�����浽csv�ļ���
		if (loop_check.GetCheck() == false && save_check.GetCheck() == true)
		{
			Sleep(100);
			SaveWave();
			running = false;
		}
	}

	pos_before = pos;
	s_pos.Format(_T("%d"), pos);
	s_pos = tcp.AddPoint(s_pos); 
	float f_pos = (float)pos / 100.0;

	motor_pos.SetWindowTextW(s_pos);

	//�����������
	int err = d_results[20];
	CString s_err;
	while (err != 0)
	{
		if (err % 2 == 0)
			s_err = _T("0") + s_err;
		else
			s_err = _T("1") + s_err;
		err = err / 2;
	}
	CString e_value, e_code, e_info, e_infoall;
	for (int i = 0; i < s_err.GetLength(); i++)
	{
		e_value = s_err.GetAt(s_err.GetLength() - i - 1);
		e_code.Format(_T("%d"), (i + 1));
		if (e_value == _T("1"))
		{
			//�������ļ��ж�ȡ��������Ӧ�Ĵ�����Ϣ
			GetPrivateProfileString(_T("errorcode"), e_code, _T("0"), e_info.GetBuffer(50), 50, path + _T("\\config.ini"));
			e_info.ReleaseBuffer();
			e_infoall = e_infoall + e_info + _T("\r\n");
		}
	}
	
	//�ж��Ƿ���ʾʣ�����
	/*if (loop_check.GetCheck() == true)
	{
		e_infoall = _T("��ǰѭ��������") + looptime + _T("\r\n") + e_infoall;
		if (looptime == _T("9"))
		{
			running = false;
		}
	}*/
	//��ʾ������Ϣ
	e_errorcode.SetWindowTextW(e_infoall);
	CDialogEx::OnTimer(nIDEvent);
}

UINT CRotateScanningSystemDlg::SaveWave()
{
	//��ȡFPGA�����Ƕȼ�ʱ����Ϣ�����浽csv�ļ���
	bool ret1, ret2;
	ret1 = fpga.GetAngleArr();
	Sleep(100);
	ret2 = fpga.GetTimeArr();
	ret1 = fpga.GetAngleArr();
	ret2 = fpga.GetTimeArr();
	save_ok = true;
	return 0;
}

//ˢ�½���
LRESULT CRotateScanningSystemDlg::OnDisplayChange(WPARAM wParam, LPARAM lParam)
{
	//����Edit  
	CString str;
	str = (LPCTSTR)lParam;
	encoder_pos.SetWindowTextW(str.Left(25).Right(7));
	return 0;
}


void CRotateScanningSystemDlg::ReadAllParas()
{
	while (true)
	{
		//��ȡPLC����	
		static CString str;

		//ʵʱ��ȡPLC��Ϣ��ʾ������������룩
		int* d_result;
		
		d_result = tcp.ReadAllPara(200);     //��ȡPLC����

		for (int i = 0; i < 25; i++)
		{
			d_results[i] = d_result[i];
			s_results[i].Format(_T("%d"), d_results[i]);
		}
		//��ȡ�˶�����
		int a = tcp.ReadM(121)/16;
		int b = tcp.ReadM(123)/16;
		motor_stop = tcp.ReadM(122);

		Sleep(50);
	}
}

void CRotateScanningSystemDlg::OnCommSet()
{
	//�򿪴�����Ϣ��ʾ����
	CommSetDlg comm;
	comm.DoModal();
}


void CRotateScanningSystemDlg::OnMotionSet()
{
	//���˶����ƽ���
	MotionSetDlg motion;
	motion.DoModal();
}

void CRotateScanningSystemDlg::OnParaSet()
{
	// �򿪲������ý���
	CSetting para;
	para.DoModal();
}


void CRotateScanningSystemDlg::OnClose()
{
	// �رճ���ʱ���еĴ���
	//com.write_serial(_T("11StopTrigger"));   //ֹͣ����
	fpga.DisableTrigger();
	//tcp.WriteM(124, 0);                      //�ر��ϻ�����
	tcp.TCP_Close();                         //�ر�TCP����
	//com.close_serial();                      //�رմ�������
	CDialogEx::OnClose();                    //�رմ���

}

void CRotateScanningSystemDlg::OnBnClickedReset()
{
	// ��λת��
	tcp.WriteM(100, 1);
}


void CRotateScanningSystemDlg::OnBnClickedStop()
{
	//ֹͣ��ת
	tcp.WriteM(104, 1);
}


void CRotateScanningSystemDlg::OnBnClickedStart()
{
	//��ʼɨ��
	//com.write_serial(_T("14ClearAngleWave"));      //���FPGAģ�鴥���Ƕ���Ϣ
	//Sleep(200);
	//com.write_serial(_T("13ClearTimeWave"));       //���FPGAģ�鴥��ʱ����Ϣ
	//Sleep(200);
	bool ret1, ret2;
	ret1 = fpga.DisableTrigger();
	Sleep(100);
	ret2 = fpga.EnableTrigger();
	if (ret1&&ret2)
		system_info.SetWindowTextW(_T("���������ɹ���"));
	else
		system_info.SetWindowTextW(_T("��������ʧ�ܣ�"));
	secstart = GetTickCount();                     //��ȡ��ʼʱ��
	
	if (c_workmode.GetCurSel() == 0)               //����ģʽ
	{
		tcp.WriteM(116, 1);
	}
	else                                           //��ͣģʽ
	{
		tcp.WriteM(115, 1);
	}
	Sleep(100);
	running = true;
}


void CRotateScanningSystemDlg::OnBnClickedExit()
{
	//�˳�����
	OnClose();
}


void CRotateScanningSystemDlg::OnBnClickedLoop()
{
	//ʹ���ϻ�����ѡ���ʱ�ٰ���ʼ��ť������ʼ�ϻ�����
	if (loop_check.GetCheck() == true)
	{
		tcp.WriteM(124, 1);
	}
	else
	{
		tcp.WriteM(124, 0);
	}
}


void CRotateScanningSystemDlg::OnBnClickedTrig()
{
	bool ret;
	if (trig_out.GetCheck() == true)                       //�򿪴����ź�
	{		
		ret = fpga.EnableTrigger();
		if (ret)
			system_info.SetWindowTextW(_T("���������ɹ�"));
		else
			system_info.SetWindowTextW(_T("��������ʧ��"));
	}
	else                                                   //�رմ����ź�
	{		
		ret = fpga.DisableTrigger();
		if (ret)
			system_info.SetWindowTextW(_T("�رմ����ɹ�"));
		else
			system_info.SetWindowTextW(_T("�رմ���ʧ��"));
	}
}


void CRotateScanningSystemDlg::OnBnClickedButton3()
{
	// TODO: Add your control notification handler code here

	double encoder_pos;
	encoder_pos = fpga.GetCurrentPos();
}


void CRotateScanningSystemDlg::OnStnClickedWaveDraw()
{
	// TODO: Add your control notification handler code here
}


void CRotateScanningSystemDlg::OnBnClickedSave()
{
	// TODO: Add your control notification handler code here
}


void CRotateScanningSystemDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	CDialogEx::OnSize(nType, cx, cy);
	//ReSize();
}

void CRotateScanningSystemDlg::ReSize(void)
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
	int id;
	id = GetDlgItem(IDC_EDIT_User)->GetDlgCtrlID();

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
		//�û���y��������
		//if (woc == id)
			//BRPoint.y = long(TLPoint.y + (OldBRPoint.y - OldTLPoint.y));
		Rect.SetRect(TLPoint, BRPoint);
		GetDlgItem(woc)->MoveWindow(Rect, TRUE);
		hwndChild = ::GetWindow(hwndChild, GW_HWNDNEXT);
	}
	old = Newp;
}
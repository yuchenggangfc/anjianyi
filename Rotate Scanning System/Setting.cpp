// Setting.cpp : implementation file
//

#include "stdafx.h"
#include "Rotate Scanning System.h"

#include "Setting.h"
#include "afxdialogex.h"


BOOL CSetting::OnInitDialog()
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
	MoveWindow((int)cx / 6, (int)cy / 6, (int)cx * 2 / 3, (int)cy * 2 / 3);

	//�������壬��ɫ
	l_font.CreatePointFont(150, _T("����"));
	s_title.SetBackColor(RGB(255, 255, 255));//
	s_title.SetFont(&l_font);
	//���ö�ʱ��
	SetTimer(1, 200, NULL);

	return true;
}

IMPLEMENT_DYNAMIC(CSetting, CDialogEx)

CSetting::CSetting(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSetting::IDD, pParent)
	, test(0)
{
	
}

CSetting::~CSetting()
{
}

void CSetting::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_Title, s_title);
	DDX_Control(pDX, IDC_ZeroVR, r_edit1);
	DDX_Control(pDX, IDC_CrawlVR, r_edit2);
	DDX_Control(pDX, IDC_ATR, r_edit3);
	DDX_Control(pDX, IDC_DTR, r_edit4);
	DDX_Control(pDX, IDC_ZeroPR, r_edit5);
	DDX_Control(pDX, IDC_MaxR, r_edit6);
	DDX_Control(pDX, IDC_MannualVR, r_edit7);
	DDX_Control(pDX, IDC_InterTR, r_edit8);
	DDX_Control(pDX, IDC_InterVR, r_edit9);
	DDX_Control(pDX, IDC_InterAR, r_edit10);
	DDX_Control(pDX, IDC_InterDR, r_edit11);
	DDX_Control(pDX, IDC_ContiVR, r_edit12);
	DDX_Control(pDX, IDC_ZeroVW, w_edit1);
	DDX_Control(pDX, IDC_CrawlVW, w_edit2);
	DDX_Control(pDX, IDC_ATW, w_edit3);
	DDX_Control(pDX, IDC_DTW, w_edit4);
	DDX_Control(pDX, IDC_ZeroPW, w_edit5);
	DDX_Control(pDX, IDC_MaxW, w_edit6);
	DDX_Control(pDX, IDC_MannualVW, w_edit7);
	DDX_Control(pDX, IDC_InterTW, w_edit8);
	DDX_Control(pDX, IDC_InterVW, w_edit9);
	DDX_Control(pDX, IDC_InterAW, w_edit10);
	DDX_Control(pDX, IDC_InterDW, w_edit11);
	DDX_Control(pDX, IDC_ContiVW, w_edit12);
	DDX_Text(pDX, IDC_ZeroVW, test);
	DDV_MinMaxDouble(pDX, test, 0, 80);
	DDX_Control(pDX, IDC_ConTW, w_edit14);
	DDX_Control(pDX, IDC_ConTR, r_edit14);
	DDX_Control(pDX, IDC_TimeW, w_edit13);
	DDX_Control(pDX, IDC_TimesR, r_edit13);
	DDX_Control(pDX, IDC_Rangle, r_edit0);
	DDX_Control(pDX, IDC_TriggerInter, w_edit0);
}


BEGIN_MESSAGE_MAP(CSetting, CDialogEx)
	ON_WM_TIMER()
	ON_BN_CLICKED(ID_ZeroV, &CSetting::OnBnClickedZerov)
	ON_BN_CLICKED(ID_CrawlV, &CSetting::OnBnClickedCrawlv)
	ON_BN_CLICKED(ID_AT, &CSetting::OnBnClickedAt)
	ON_BN_CLICKED(ID_DT, &CSetting::OnBnClickedDt)
	ON_BN_CLICKED(ID_ZeroP, &CSetting::OnBnClickedZerop)
	ON_BN_CLICKED(ID_Max, &CSetting::OnBnClickedMax)
	ON_BN_CLICKED(ID_Mannual, &CSetting::OnBnClickedMannual)
	ON_BN_CLICKED(ID_InterT, &CSetting::OnBnClickedIntert)
	ON_BN_CLICKED(ID_InterV, &CSetting::OnBnClickedInterv)
	ON_BN_CLICKED(ID_InterA, &CSetting::OnBnClickedIntera)
	ON_BN_CLICKED(ID_InterD, &CSetting::OnBnClickedInterd)
	ON_BN_CLICKED(ID_ContiV, &CSetting::OnBnClickedContiv)
	ON_BN_CLICKED(ID_ConT, &CSetting::OnBnClickedCont)
	ON_BN_CLICKED(ID_Times, &CSetting::OnBnClickedTimes)
	ON_BN_CLICKED(ID_Triger, &CSetting::OnBnClickedTriger)
	ON_WM_SIZE()
END_MESSAGE_MAP()

void CSetting::OnTimer(UINT_PTR nIDEvent)
{
	//��ȡPLC��������ʾ������
	//int* d_result;
	//int d_results[22];
	CString s_result[22];
	//d_result = tcp.ReadAllPara(200);
	for (int i = 0; i < 22; i++)
	{
		s_result[i].Format(_T("%d"), d_results[i]);
	}

	r_edit1.SetWindowTextW(tcp.AddPoint(s_result[2]));
	r_edit2.SetWindowTextW(tcp.AddPoint(s_result[3]));
	r_edit3.SetWindowTextW(s_result[4]);
	r_edit4.SetWindowTextW(s_result[5]);
	r_edit5.SetWindowTextW(tcp.AddPoint(s_result[8]));
	r_edit6.SetWindowTextW(tcp.AddPoint(s_result[9]));
	r_edit7.SetWindowTextW(tcp.AddPoint(s_result[11]));
	r_edit8.SetWindowTextW(tcp.AddPoint(s_result[12]));
	r_edit9.SetWindowTextW(tcp.AddPoint(s_result[13]));
	r_edit10.SetWindowTextW(tcp.AddPoint(s_result[14]));
	r_edit11.SetWindowTextW(tcp.AddPoint(s_result[15]));
	r_edit12.SetWindowTextW(tcp.AddPoint(s_result[16]));
	r_edit14.SetWindowTextW(tcp.AddPoint(s_result[17]));
	r_edit0.SetWindowTextW(tcp.AddPoint(s_result[10]));
	r_edit13.SetWindowTextW(s_result[21]);
	CDialogEx::OnTimer(nIDEvent);
}

int CSetting::CstringToInt(CString s_data)
{
	//CStringתint
	int data;
	int a = s_data.Find('.');
	if (s_data.Find('.') == -1)
	{
		s_data = s_data + _T(".00");
	}	
	else
	{
		//ֻ��һλС��
		if (s_data.GetLength() - s_data.Find('.') < 3)
		{
			s_data = s_data + _T("0");
		}
		//������λС��ȡǰ��λ
		if (s_data.GetLength() - s_data.Find('.') > 3)
		{
			s_data = s_data.Left(s_data.Find('.') + 3);
		}
	}
	s_data.Remove('.');
	data = _ttoi(s_data);
	return data;	
}

void CSetting::OnBnClickedZerov()
{
	//���û�ԭ���ٶ�
	CString s_data;
	w_edit1.GetWindowText(s_data);
	int data = CstringToInt(s_data);
	if (data>=0&&data<100000)
	{
		tcp.WriteD(204, data);
	}
	else
	{
		MessageBox(_T("�����������!"), _T("Warning"), MB_OK);
	}
	
}


void CSetting::OnBnClickedCrawlv()
{
	//���������ٶ�
	CString s_data;
	w_edit2.GetWindowText(s_data);
	int data = CstringToInt(s_data);
	if (data>=0 && data<100000)
	{
		tcp.WriteD(206, data);
	}
	else
	{
		MessageBox(_T("�����������!"), _T("Warning"), MB_OK);
	}

}


void CSetting::OnBnClickedAt()
{
	//���ü���ʱ��
	CString s_data;
	w_edit3.GetWindowText(s_data);
	int data = _ttoi(s_data);
	if (data>=100 && data<10000)
	{
		tcp.WriteD(208, data);
	}
	else
	{
		MessageBox(_T("�����������!"), _T("Warning"), MB_OK);
	}
}


void CSetting::OnBnClickedDt()
{
	//���ü���ʱ��
	CString s_data;
	w_edit4.GetWindowText(s_data);
	int data = _ttoi(s_data);
	if (data>=100 && data<10000)
	{
		tcp.WriteD(210, data);
	}
	else
	{
		MessageBox(_T("�����������!"), _T("Warning"), MB_OK);
	}

}


void CSetting::OnBnClickedZerop()
{
	//�������λ��
	CString s_data;
	w_edit5.GetWindowText(s_data);
	int data = CstringToInt(s_data);
	if (data>=0 && data<100000)
	{
		tcp.WriteD(216, data);
	}
	else
	{
		MessageBox(_T("�����������!"), _T("Warning"), MB_OK);
	}

}


void CSetting::OnBnClickedMax()
{
	//��������г�
	CString s_data;
	w_edit6.GetWindowText(s_data);
	int data = CstringToInt(s_data);
	if (data>=0 && data<100000)
	{
		tcp.WriteD(218, data);
	}
	else
	{
		MessageBox(_T("�����������!"), _T("Warning"), MB_OK);
	}

}


void CSetting::OnBnClickedMannual()
{
	//�����ֶ��ٶ�
	CString s_data;
	w_edit7.GetWindowText(s_data);
	int data = CstringToInt(s_data);
	if (data>=0 && data<100000)
	{
		tcp.WriteD(222, data);
	}
	else
	{
		MessageBox(_T("�����������!"), _T("Warning"), MB_OK);
	}

}


void CSetting::OnBnClickedIntert()
{
	//������ͣģʽ����ͣͣ��ʱ��
	CString s_data;
	w_edit8.GetWindowText(s_data);
	int data = CstringToInt(s_data);
	if (data>=0 && data<100000)
	{
		tcp.WriteD(224, data);
	}
	else
	{
		MessageBox(_T("�����������!"), _T("Warning"), MB_OK);
	}

}


void CSetting::OnBnClickedInterv()
{
	//������ͣģʽ�ٶ�
	CString s_data;
	w_edit9.GetWindowText(s_data);
	int data = CstringToInt(s_data);
	if (data>=0 && data<100000)
	{
		tcp.WriteD(226, data);
	}
	else
	{
		MessageBox(_T("�����������!"), _T("Warning"), MB_OK);
	}

}


void CSetting::OnBnClickedIntera()
{
	//������ͣģʽ��ÿ����ͣ�Ƕ�
	CString s_data;
	w_edit10.GetWindowText(s_data);
	int data = CstringToInt(s_data);
	if (data>=0 && data<100000)
	{
		tcp.WriteD(228, data);
	}
	else
	{
		MessageBox(_T("�����������!"), _T("Warning"), MB_OK);
	}

}


void CSetting::OnBnClickedInterd()
{
	//������ͣģʽ���յ�λ��
	CString s_data;
	w_edit11.GetWindowText(s_data);
	int data = CstringToInt(s_data);
	if (data>=0 && data<100000)
	{
		tcp.WriteD(230, data);
	}
	else
	{
		MessageBox(_T("�����������!"), _T("Warning"), MB_OK);
	}

}


void CSetting::OnBnClickedContiv()
{
	//���������˶�ģʽ�������ٶ�
	CString s_data;
	w_edit12.GetWindowText(s_data);
	int data = CstringToInt(s_data);
	if (data>=0 && data<100000)
	{
		tcp.WriteD(232, data);
	}
	else
	{
		MessageBox(_T("�����������!"), _T("Warning"), MB_OK);
	}

}


void CSetting::OnBnClickedCont()
{
	//���������˶��յ�λ��
	CString s_data;
	w_edit14.GetWindowText(s_data);
	int data = CstringToInt(s_data);
	if (data>=0 && data<100000)
	{
		tcp.WriteD(234, data);
	}
	else
	{
		MessageBox(_T("�����������!"), _T("Warning"), MB_OK);
	}
}


void CSetting::OnBnClickedTimes()
{
	//����ѭ������
	CString s_data;
	w_edit13.GetWindowText(s_data);
	//int data = CstringToInt(s_data);
	int data = _ttoi(s_data);
	if (data>=0 && data<30001)
	{
		tcp.WriteD(242, data);
	}
	else
	{
		MessageBox(_T("�����������!"), _T("Warning"), MB_OK);
	}
}


void CSetting::OnBnClickedTriger()
{
	//���ô������
	CString s_data;
	w_edit0.GetWindowText(s_data);
	//int data = CstringToInt(s_data);
	double data = 0;
	data = _wtof(s_data.GetBuffer(s_data.GetLength()));

	if (data >= 0.1 && data <= 10)
	{
		bool ret = fpga.SetTriggerAngle(data);
		if (ret == true)
		{
			MessageBox(_T("���óɹ�!"), _T("Warning"), MB_OK);
		}
		//CString result;
		//result.Format(_T("%f"),data);
		//w_edit0.SetWindowTextW(result);
	}
	else
	{
		MessageBox(_T("�����������!"), _T("Warning"), MB_OK);
	}
}

void CSetting::ReSize(void)
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

void CSetting::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	CDialogEx::OnSize(nType, cx, cy);
	ReSize();
}

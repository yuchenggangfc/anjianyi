#include "stdafx.h"
#include "Serial.h"
#include<string>


Serial::Serial()
{
	
}


Serial::~Serial()
{
}

Serial com;
bool Serial::open_serial()
{
	//�򿪴���
	hCom = CreateFile(_T("COM5"),//�˿ں�  
	
	GENERIC_READ | GENERIC_WRITE, //�������д  
	0, //��ռ��ʽ  
	NULL,
	OPEN_EXISTING, //�򿪶����Ǵ���  
	0, //ͬ����ʽ  
	NULL);
	if (hCom == (HANDLE)-1)
	{
		//MessageBox(NULL,_T("�򿪴���ʧ��!"),_T("Warning"),MB_OK);
		return FALSE;
	}
	return TRUE;
}

void Serial::setup_serial()
{

	//���ô���
	SetupComm(hCom, 254, 254); //���뻺����������������Ĵ�С����254

	COMMTIMEOUTS TimeOuts; 
	//�趨����ʱ 
	TimeOuts.ReadIntervalTimeout = 0;
	TimeOuts.ReadTotalTimeoutMultiplier = 0;
	TimeOuts.ReadTotalTimeoutConstant = 50;
	//�趨д��ʱ 
	TimeOuts.WriteTotalTimeoutMultiplier = 0;
	TimeOuts.WriteTotalTimeoutConstant = 50;
	SetCommTimeouts(hCom, &TimeOuts);

	DCB dcb;
	GetCommState(hCom, &dcb);
	dcb.BaudRate = 115200; //������Ϊ115200
	dcb.ByteSize = 8; //ÿ���ֽ���8λ 
	dcb.Parity = NOPARITY; //����żУ��λ 
	dcb.StopBits = ONESTOPBIT; //1��ֹͣλ 
	SetCommState(hCom, &dcb);
	PurgeComm(hCom, PURGE_TXCLEAR | PURGE_RXCLEAR); //�ڶ�д����֮ǰ����Ҫ��PurgeComm()������ջ�����
}

CString Serial::read_serial()
{
	//ͬ�������� 
	PurgeComm(hCom, PURGE_TXCLEAR | PURGE_RXCLEAR);
	char str[80] = {0};
	DWORD wCount;//��ȡ���ֽ��� 
	BOOL bReadStat; 
	bReadStat = ReadFile(hCom, str, 80, &wCount, NULL);
	CString s_data;
	s_data = str;
	if(!bReadStat) 
	{ 
		return _T(""); 
	} 
	return s_data;
}

bool Serial::write_serial(CString data)
{
	//ͬ��д���� 
	CString add(_T("\r\n"));
	CString result;
	result =data+add;
	CStringA a_data;
	a_data = result;
	char InData[50];
	DWORD dwBytesWrite = a_data.GetLength();

	COMSTAT ComStat; 
	DWORD dwErrorFlags; 
	BOOL bWriteStat; 
	ClearCommError(hCom,&dwErrorFlags,&ComStat); 

	memset(InData, 0x00, 50);
	memcpy(InData, a_data, a_data.GetLength());

	bWriteStat=WriteFile(hCom, InData,dwBytesWrite,& dwBytesWrite,NULL);
	if(!bWriteStat) 
	{ 
		return false;
	}
	return true;
}

void Serial::close_serial()
{
	//�رմ���
	CloseHandle(hCom);
}

CString Serial::ReadAngleWave()
{
	//��ȡ�����Ƕ���Ϣ

	write_serial(_T("12GetAngleWave"));                        //���������FPGAģ�飬���󴥷��Ƕ���Ϣ

	//ͬ�������� 
	PurgeComm(hCom, PURGE_TXCLEAR | PURGE_RXCLEAR);
	char str[4096] = { 0 };                                    //��ȡ4096���ַ�
	DWORD wCount;                                              //��ȡ���ֽ��� 
	BOOL bReadStat;
	Sleep(500);
	bReadStat = ReadFile(hCom, str, 4096, &wCount, NULL);
	CString s_data1;
	s_data1 = str;
	if (!bReadStat)
	{
		return _T("");
	}
	//�������������Ƕ���Ϣ
	write_serial(_T("14ClearAngleWave"));
	Sleep(200);
	CString s_data2;
	s_data2 = read_serial();
	CString s_data;
	s_data = s_data1 + s_data2;
	return s_data;
}

CString Serial::ReadTimeWave()
{
	//��ȡ����ʱ����Ϣ
	write_serial(_T("11GetTimeWave"));                       //���������FPGAģ�飬���󴥷�ʱ����Ϣ
	//ͬ�������� 
	PurgeComm(hCom, PURGE_TXCLEAR | PURGE_RXCLEAR);
	char str[4096] = { 0 };                                  //��ȡ4096���ַ�
	DWORD wCount;                                            //��ȡ���ֽ��� 
	BOOL bReadStat;
	Sleep(500);
	bReadStat = ReadFile(hCom, str, 4096, &wCount, NULL);
	CString s_data1;
	s_data1 = str;
	if (!bReadStat)
	{
		return _T("");
	}
	//������������ʱ����Ϣ
	write_serial(_T("13ClearTimeWave"));
	Sleep(200);
	CString s_data2;
	s_data2 = read_serial();
	CString s_data;
	s_data = s_data1 + s_data2;
	return s_data;
}

void Serial::WriteCSV(CString str)
{
	//дcsv�ļ�
	//��ʱ�������ļ�
	COleDateTime time;
	time = COleDateTime::GetCurrentTime();
	CString curTime = time.Format(_T("%Y-%m-%d:%H:%M:%S"));
	CStdioFile file;

	TCHAR buf[200];
	GetCurrentDirectory(sizeof(buf), buf);
	CString path = buf;
	path = path;

	CString filePath = path + _T("\\TriggerInfo.csv");
	str.Replace('*', ',');
	str = curTime + _T(",") + str;

	CFileException fileException;
	if (CFileFind().FindFile(filePath))
	{
		file.Open(filePath, CFile::typeText | CFile::modeReadWrite), &fileException;
	}
	else
	{
		file.Open(filePath, CFile::typeText | CFile::modeCreate | CFile::modeReadWrite), &fileException;
	}

	file.SeekToEnd();
	file.WriteString(str);
	file.WriteString(_T("\n"));
}

void Serial::ReadCSV(CListBox* pListBox)
{
	//��csv�ļ�
	pListBox->ResetContent();
	CStdioFile file;
	TCHAR buf[200];
	GetCurrentDirectory(sizeof(buf), buf);
	CString path = buf;
	path = path;

	CString filePath = path + _T("\\TriggerInfo.csv");
	CString str = _T("0");
	if (file.Open(filePath, CFile::modeRead))
	{
		while (str != _T(""))
		{
			file.ReadString(str);
			str.Replace(_T(","), _T("   "));
			pListBox->AddString(str);
		}
		file.Close();
	}
}




 



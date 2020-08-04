
// BurnProcessDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "BurnProcess.h"
#include "BurnProcessDlg.h"
#include "afxdialogex.h"
#include "MESconnet.h"
#include "password.h"
#include "WindowPrompts.h"
#include "NoConnectMax.h"
#include <string>
#include "login.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace std;

CString PATH;
MESconnet MesDlg;
login loginDlg;
password passwordDlg;
WindowPrompts WindowPromptsDlg;
NoConnectMax NoConnectMaxDlg;

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CBurnProcessDlg 对话框



CBurnProcessDlg::CBurnProcessDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_BURNPROCESS_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBurnProcessDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_edit1);
	DDX_Control(pDX, IDC_EDIT2, m_edit2);
	DDX_Control(pDX, IDC_EDIT3, m_edit3);
	DDX_Control(pDX, IDC_RADIO1, m_radio1);
	DDX_Control(pDX, IDC_RADIO2, m_radio2);
	DDX_Control(pDX, IDC_EDIT4, m_edit_site);
	DDX_Control(pDX, IDC_EDIT5, m_edit_user);
	DDX_Control(pDX, IDC_EDIT6, m_edit_number);
	DDX_Control(pDX, IDC_EDIT7, m_edit_equip);
	DDX_Control(pDX, IDC_EDIT8, m_edit_mes);
	DDX_Control(pDX, IDC_EDIT9, m_edit_macmax);
	DDX_Control(pDX, IDC_EDIT10, m_edit_devmax);
}

BEGIN_MESSAGE_MAP(CBurnProcessDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CBurnProcessDlg::OnBnClickedButton1)
	ON_WM_TIMER()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_RADIO1, &CBurnProcessDlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CBurnProcessDlg::OnBnClickedRadio2)
END_MESSAGE_MAP()


// CBurnProcessDlg 消息处理程序

BOOL CBurnProcessDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	TCHAR path[MAX_PATH] = { 0 };
	GetModuleFileName(NULL, path, MAX_PATH);
	(_tcsrchr(path, _T('\\')))[1] = 0;
	PATH = path;


	font.DeleteObject();
	font.CreatePointFont(300, L"微软雅黑");//代表15号字体，华文行楷
	m_edit3.SetFont(&font);

	//设置radio初始状态
	CButton* radio = (CButton*)GetDlgItem(IDC_RADIO2);
	radio->SetCheck(0);
	GetDlgItem(IDC_EDIT2)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT1)->EnableWindow(FALSE);


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CBurnProcessDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CBurnProcessDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CBurnProcessDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CBurnProcessDlg::CharToUTF8(CString &str)
{
	char *szBuf = new char[str.GetLength() + 1];//注意“+1”，char字符要求结束符，而CString没有
	memset(szBuf, '\0', str.GetLength());


	int i;
	for (i = 0; i < str.GetLength(); i++)
	{
		szBuf[i] = (char)str.GetAt(i);
	}
	szBuf[i] = '\0';//结束符。否则会在末尾产生乱码。

	int nLen;
	WCHAR *ptch;
	CString strOut;
	if (szBuf == NULL)
	{
		return;
	}
	nLen = MultiByteToWideChar(CP_UTF8, 0, szBuf, -1, NULL, 0);//获得需要的宽字符字节数
	ptch = new WCHAR[nLen];
	memset(ptch, '\0', nLen);
	MultiByteToWideChar(CP_UTF8, 0, szBuf, -1, ptch, nLen);
	//str.Format(_T("%s"), ptch);
	str = ptch;
	if (NULL != ptch)
		delete[] ptch;
	ptch = NULL;

	if (NULL != szBuf)
		delete[]szBuf;
	szBuf = NULL;
	return;
}

//获取文件行数
int CBurnProcessDlg::GetFileLine(CString road)
{
	CStdioFile myFile;
	CFileException fileException;
	if (myFile.Open(road, CFile::modeCreate | CFile::modeNoTruncate | CFile::typeText | CFile::modeReadWrite), &fileException)
	{
		CString strContent;
		int order = 0;
		while (myFile.ReadString(strContent))
		{
			order++;
		}
		myFile.Close();
		return order;
	}
	else
	{
		myFile.Close();
		return 0;
	}
}

//读取整个文件
CString CBurnProcessDlg::ReadFileALL(CString path)
{
	CStdioFile file;
	CString arry[1000];
	CString data;
	CString all_result;
	CString result;
	int line = GetFileLine(path);
	if (file.Open(path, CFile::modeRead))
	{
		for (int i = 0; i < line; i++)
		{
			file.ReadString(arry[i]);
			all_result += arry[i] + L"\n";
			//	all_result.Replace(L" ", L"");
		}
		file.Close();
		return all_result;
	}
	else
	{
		file.Close();
		//AfxMessageBox(L"all.文件不存在");
		return CString(_T("all.文件不存在"));
	}
}


//读取第一行 规定第一行为程序最终结果
CString CBurnProcessDlg::ReadFileFirstLine(CString path)
{
	CStdioFile file;
	CString line_result;

	if (file.Open(path, CFile::modeRead))
	{
		file.ReadString(line_result);
		//CharToUTF8(line_result);
		file.Close();			//不能写反，先关闭后return
		return line_result;
	}
	else
	{
		//AfxMessageBox(L"Error:文件不存在\n1、模块程序路径不一致导致\n2、result.log文件不存在");
		GetDlgItem(IDC_EDIT2)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT2)->SetWindowText(L"");
		GetDlgItem(IDC_EDIT2)->SetFocus();
		return CString(_T("NULL"));
	}

}

void CBurnProcessDlg::OnWriteFileLine(CString path, CString str)
{
	USES_CONVERSION;
	CStdioFile file;
	CString str1;
	char * pFileName = T2A(str);
	file.Open(path, CFile::modeNoTruncate | CFile::modeCreate | CFile::modeWrite);
	file.SeekToEnd();
	file.Write(pFileName, strlen(pFileName));
	file.Flush();
	file.Close();
	pFileName = NULL;
}

void DoEvent()
{
	MSG msg;
	if (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		::TranslateMessage(&msg);
		::DispatchMessage(&msg);
	}
}
void TheadWait(HANDLE m_hThread)
{
	DWORD dwRet;
	DoEvent();
	do
	{
		dwRet = MsgWaitForMultipleObjects(1, &m_hThread, FALSE, INFINITE, QS_ALLINPUT);
		if (dwRet != WAIT_OBJECT_0)
		{
			DoEvent();
		}
	} while ((dwRet != WAIT_OBJECT_0) && (dwRet != WAIT_FAILED));
}

void CBurnProcessDlg::OnRunExe(CString path, CString Param, CString dest)
{
	SHELLEXECUTEINFO ShExecInfo = { 0 };
	ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
	ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
	ShExecInfo.hwnd = NULL;
	ShExecInfo.lpVerb = NULL;
	ShExecInfo.lpFile = path;
	ShExecInfo.lpParameters = Param;
	ShExecInfo.lpDirectory = dest;
	ShExecInfo.nShow = SW_HIDE;
	ShExecInfo.hInstApp = NULL;
	ShellExecuteEx(&ShExecInfo);
	TheadWait(ShExecInfo.hProcess);
}

void CBurnProcessDlg::ReplaceFuncMAC(CString pszSrc, CString pszDes2)
{
	CStdioFile file;
	CString Burn = _T("Burn\\");
	CString pszFile = PATH + Burn + _T("EEPROM.dat");
	file.Open(pszFile, CFile::modeRead);
	CString strText;
	DWORD dwPos = 0;
	CString pszDes1 = _T("\"");
	CString pszDes3 = _T("\"");
	CString pszDes4 = _T("                       // Current MAC address\n");
	CString pszDes = pszDes1 + pszDes2 + pszDes3 + pszDes4;


	while (file.ReadString(strText))
	{
		if (strText == pszSrc)
		{
			dwPos = (DWORD)file.GetPosition() - (_tcslen(pszSrc) + _tcslen(_T("\r\n")));
			break;
		}
	}
	file.Close();
	file.Open(pszFile, CFile::modeWrite);
	file.Seek(dwPos, CFile::begin);
	file.WriteString(pszDes);
	file.Close();

}

void CBurnProcessDlg::ReplaceFuncDEV(CString DeviceSrc, CString Device2)
{
	CStdioFile file;
	CString Burn = _T("Burn\\");
	CString pszFile = PATH + Burn + _T("EEPROM.dat");
	file.Open(pszFile, CFile::modeRead);
	CString strText;
	DWORD dwPos = 0;
	CString Device1 = _T("\"");
	CString Device3 = _T("\"");
	CString Device4 = _T("                     // Current serial number\n");
	CString Device = Device1 + Device2 + Device3 + Device4;

	while (file.ReadString(strText))
	{
		if (strText == DeviceSrc)
		{
			//len = strText.GetLength();
			dwPos = (DWORD)file.GetPosition() - (_tcslen(DeviceSrc) + _tcslen(_T("\r\n")));
			break;
		}
	}
	file.Close();
	file.Open(pszFile, CFile::modeWrite);
	file.Seek(dwPos, CFile::begin);
	file.WriteString(Device);
	file.Close();
}

void CBurnProcessDlg::ReplaceFuncMACMAX(CString pszSrc, CString pszDes2)
{
	CStdioFile file;
	CString Burn = _T("Burn\\");
	CString pszFile = PATH + Burn + _T("EEPROM.dat");
	file.Open(pszFile, CFile::modeRead);
	CString strText;
	DWORD dwPos = 0;
	CString pszDes1 = _T("\"");
	CString pszDes3 = _T("\"");
	CString pszDes4 = _T("                       // Maximum MAC address\n");
	CString pszDes = pszDes1 + pszDes2 + pszDes3 + pszDes4;


	while (file.ReadString(strText))
	{
		if (strText == pszSrc)
		{
			dwPos = (DWORD)file.GetPosition() - (_tcslen(pszSrc) + _tcslen(_T("\r\n")));
			break;
		}
	}
	file.Close();
	file.Open(pszFile, CFile::modeWrite);
	file.Seek(dwPos, CFile::begin);
	file.WriteString(pszDes);
	file.Close();

}

void CBurnProcessDlg::ReplaceFuncDEVMAX(CString DeviceSrc, CString Device2)
{
	CStdioFile file;
	CString Burn = _T("Burn\\");
	CString pszFile = PATH + Burn + _T("EEPROM.dat");
	file.Open(pszFile, CFile::modeRead);
	CString strText;
	DWORD dwPos = 0;
	CString Device1 = _T("\"");
	CString Device3 = _T("\"");
	CString Device4 = _T("                     // Maximum serial number\n");
	CString Device = Device1 + Device2 + Device3 + Device4;

	while (file.ReadString(strText))
	{
		if (strText == DeviceSrc)
		{
			dwPos = (DWORD)file.GetPosition() - (_tcslen(DeviceSrc) + _tcslen(_T("\r\n")));
			break;
		}
	}
	file.Close();
	file.Open(pszFile, CFile::modeWrite);
	file.Seek(dwPos, CFile::begin);
	file.WriteString(Device);
	file.Close();
}

void CBurnProcessDlg::ButtonFunc()
{
	Sleep(300);
	HWND hWnd,hWnd3;

	hWnd = ::FindWindow(NULL, L"AX88179_178A_Srom for IO DATA v1.0.1");
	hWnd3 = ::FindWindowEx(hWnd, NULL, _T("Button"), _T("Program"));

	if (hWnd != NULL)
	{
		if (hWnd3 != NULL)
		{
			DWORD ID = ::GetDlgCtrlID(hWnd3);	//句柄换ID
			::PostMessage(hWnd, WM_COMMAND, MAKEWPARAM(ID, BN_CLICKED), (LPARAM)hWnd3);
			Sleep(200);
			::SendMessage(hWnd, WM_CLOSE, 0, 0);
			run = L"T";
		}
		else
		{
			AfxMessageBox(L"Button fail");
			DisplayResult(L"fail");
			run = L"F";
		}
	}
	else
	{
		AfxMessageBox(L"fail\n没有找到AX88179_178A_Srom for IO DATA v1.0.1");
		DisplayResult(L"fail");
		run = L"F";
	}
}


void CBurnProcessDlg::BurnProcess()
{
	CString Config = _T("Config.ini");
	CString ConfigPath = PATH + Config;
	CString BurnProcess;
	GetPrivateProfileString(_T("COM"), _T("BurnProcess"), CString("NULL"), BurnProcess.GetBuffer(MAX_PATH), MAX_PATH, ConfigPath);
	BurnProcess.ReleaseBuffer();
	
}


void CBurnProcessDlg::CheckFunc()
{
	//Sleep(200);
	CString Config = _T("Config.ini");
	CString ConfigPath = PATH + Config;
	CString Check;
	CString VID;
	CString PID;
	GetPrivateProfileString(_T("COM"), _T("Check"), CString("NULL"), Check.GetBuffer(MAX_PATH), MAX_PATH, ConfigPath);
	Check.ReleaseBuffer();
	GetPrivateProfileString(_T("VID&&PID"), _T("VID"), CString("NULL"), VID.GetBuffer(MAX_PATH), MAX_PATH, ConfigPath);
	VID.ReleaseBuffer();
	GetPrivateProfileString(_T("VID&&PID"), _T("PID"), CString("NULL"), PID.GetBuffer(MAX_PATH), MAX_PATH, ConfigPath);
	PID.ReleaseBuffer();

	CString devcon = _T("devcon\\");
	CString param1 = _T("/C ipconfig /all > ipconfig.txt");
	CString param2 = _T("/C devcon.exe disable *VID_") + VID + _T("*");
	CString param3 = _T("/C devcon.exe enable *VID_") + VID + _T("*");
//	CString param4 = _T("/C devcon.exe find usb* > log.txt");


	OnRunExe(_T("cmd.exe"), param2, PATH + devcon);
	
	OnRunExe(_T("cmd.exe"), param3, PATH + devcon);
	//校验烧录后的MAC  确认是否烧录成功
	OnRunExe(_T("cmd.exe"), param1, PATH);


}

void CBurnProcessDlg::OnTimer(UINT_PTR nIDEvent)
{

	CDialogEx::OnTimer(nIDEvent);
}

void CBurnProcessDlg::DisplayResult(CString Result)
{
	if ((Result.Mid(0, 4)) == "pass")
	{
		m_edit3.SetWindowTextW(_T("Pass"));
		EndResult_textColor = RGB(0, 0, 0);
		EndResult_backColor = RGB(0, 255, 0);
	}
	else if (Result.Mid(0, 4) == "fail")
	{
		m_edit3.SetWindowTextW(_T("Fail"));
		EndResult_textColor = RGB(0, 0, 0);
		EndResult_backColor = RGB(255, 0, 0);
	}
	else //if (Result.Mid(0, 4) == "WAIT")
	{
		m_edit3.SetWindowTextW(_T("Wait"));
		EndResult_textColor = RGB(0, 0, 0);
		EndResult_backColor = RGB(255, 255, 0);
	}
	EndResult_backBrush.DeleteObject();
	EndResult_backBrush.CreateSolidBrush(EndResult_backColor);		//创建画刷
	GetDlgItem(IDC_EDIT3)->Invalidate();
}

void CBurnProcessDlg::DisplayMESconnet(CString Result)
{
	if ((Result.Mid(0, 4)) == "pass")
	{
		m_edit_mes.SetWindowTextW(_T("Pass"));
		EndResult_textColor_mes = RGB(0, 0, 0);
		EndResult_backColor_mes = RGB(0, 255, 0);
	}
	else if (Result.Mid(0, 4) == "fail")
	{
		m_edit_mes.SetWindowTextW(_T("Fail"));
		EndResult_textColor_mes = RGB(0, 0, 0);
		EndResult_backColor_mes = RGB(255, 0, 0);
	}
	else //if (Result.Mid(0, 4) == "WAIT")
	{
		m_edit_mes.SetWindowTextW(_T("Wait"));
		EndResult_textColor_mes = RGB(0, 0, 0);
		EndResult_backColor_mes = RGB(255, 255, 0);
	}
	EndResult_backBrush_mes.DeleteObject();
	EndResult_backBrush_mes.CreateSolidBrush(EndResult_backColor_mes);		//创建画刷
	GetDlgItem(IDC_EDIT8)->Invalidate();
}

void CBurnProcessDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CString Result = _T("Result.log");
	CString ResultPath = PATH + Result;

	CString Burn = _T("Burn\\");
	CString exeName = _T("/C AX88179_178A_Srom.exe");
	CString exePath = PATH + Burn + exeName;
	CString EXEPATH = PATH + Burn + _T("AX88179_178A_Srom.exe");
	CString EEPROMPATH = PATH + Burn + _T("EEPROM.dat");
	
	CString SerialMAC = _TEXT("Serial-MAC.log");
	CString SerialMACPath = PATH + Burn + SerialMAC;
	CString SerialMACResult;
	DeleteFile(SerialMACPath);
	CString ipconfig_txt = _T("ipconfig.txt");
	CString ipconfig_path = PATH + ipconfig_txt;
	CString result_ip, str_ip;

	DeleteFile(ipconfig_path);		//删除ipconfig.txt
	CString str1, str2;
	CString value, SN, SN1, SN2;
	CString ImageCode;
	CString sym = L"-";
	CString MacAddress;
	int x = 0;
	CString Config = _T("Config.ini");
	CString ConfigPath = PATH + Config;
	CString PreFix, PrefixNum;
	CString BurnProcess;
	CString Check;
	CString PCB;
	GetPrivateProfileString(_T("PreFix"), _T("Set"), CString("NULL"), PreFix.GetBuffer(MAX_PATH), MAX_PATH, ConfigPath);
	PreFix.ReleaseBuffer();
	GetPrivateProfileString(_T("PrefixNum"), _T("Set"), CString("NULL"), PrefixNum.GetBuffer(MAX_PATH), MAX_PATH, ConfigPath);
	PrefixNum.ReleaseBuffer();
	GetPrivateProfileString(_T("COM"), _T("BurnProcess"), CString("NULL"), BurnProcess.GetBuffer(MAX_PATH), MAX_PATH, ConfigPath);
	BurnProcess.ReleaseBuffer();
	GetPrivateProfileString(_T("COM"), _T("Check"), CString("NULL"), Check.GetBuffer(MAX_PATH), MAX_PATH, ConfigPath);
	Check.ReleaseBuffer();
	//str1->MAC
	//str2->Device Path/Current serial number
	m_edit_site.GetWindowText(site);
	m_edit_user.GetWindowText(user);
	m_edit_number.GetWindowText(number);
	m_edit_equip.GetWindowText(equip);
	m_edit1.GetWindowText(ImageCode);
	m_edit2.GetWindowText(PCB);

	//MAC
	value = ImageCode.Right(12);
	//SN
	SN1 = ImageCode.Left(ImageCode.Find(PreFix));
	SN2 = ImageCode.Right(ImageCode.GetLength() - SN1.GetLength());
	SN = SN2.Mid(0, 12);

	for (int i = 0; i < 6; i++)
	{
		MacAddress += value.Mid(x, 2) + sym;
		x += 2;
	}
	MacAddress = MacAddress.Left(MacAddress.GetLength() - 1);

	str2 = PrefixNum + value;
	CStdioFile file_mac, file_dev, file_mac_max, file_dev_max, file_ip;
	CString strMac, strDev, strMacMax, strDevMax;
	CString  resultMac, resultDev, resultMacMax, resultDevMax;
	CString Mstr;
	CString Dstr;
	m_edit_macmax.GetWindowText(Mstr);
	m_edit_devmax.GetWindowText(Dstr);
//	CString Dstr2 = PrefixNum + Dstr;
	int line = GetFileLine(EEPROMPATH);

	CString Check_SerialMAC_log;
	CFileFind finder;
	DisplayResult(_T("wait"));
	if (((CButton *)GetDlgItem(IDC_RADIO1))->GetCheck())		//radio1 MES上传
	{
		//检测PCB是否存在、是不是当前站别等...
		CString PCBResult = MesDlg.CheckPCB(site, PCB);
		string mes_pcb_result = (LPCSTR)(CStringA)(PCBResult);
		if (mes_pcb_result == "T")
		{
			//工单检测
			CString PCBdata = MesDlg.GetPCBdata(site, PCB);
			CString CheckNumberResult = PCBdata.Left(PCBdata.Find(_T(",")));
			if (CheckNumberResult == number)
			{
				GetDlgItem(IDC_EDIT1)->SetFocus();
				if (value.GetLength() == 12)
				{
					file_mac.Open(EEPROMPATH, CFile::modeRead);
					for (int i = 0; i < line; i++)
					{
						file_mac.ReadString(strMac);
						if (line = 4)
						{
							resultMac = strMac;
						}
					}
					file_mac.Close();
					ReplaceFuncMAC(resultMac, value);

					Sleep(200);
					file_mac_max.Open(EEPROMPATH, CFile::modeRead);
					for (int i = 0; i < line; i++)
					{
						file_mac_max.ReadString(strMacMax);
						if (line = 5)
						{
							resultMacMax = strMacMax;
						}
					}
					file_mac_max.Close();
					ReplaceFuncMACMAX(resultMacMax, Mstr);

					Sleep(200);
					file_dev.Open(EEPROMPATH, CFile::modeRead);
					for (int j = 0; j < line; j++)
					{
						file_dev.ReadString(strDev);
						if (line = 7)
						{
							resultDev = strDev;
						}
					}
					file_dev.Close();
					ReplaceFuncDEV(resultDev, str2);

					Sleep(200);
					file_dev_max.Open(EEPROMPATH, CFile::modeRead);
					for (int j = 0; j < line; j++)
					{
						file_dev_max.ReadString(strDevMax);
						if (line = 8)
						{
							resultDevMax = strDevMax;
						}
					}
					file_dev_max.Close();
					ReplaceFuncDEVMAX(resultDevMax, Dstr);

					ShellExecute(NULL, _T("open"), _T("cmd.exe"), exeName, PATH + Burn, SW_HIDE);
					//Sleep(300);
					ButtonFunc();
					Sleep(200);
					BOOL ifFind = finder.FindFile(SerialMACPath);
					if (ifFind)
					{
						finder.Close();
						//Check_SerialMAC_log = ReadFileFirstLine(SerialMACPath);  //read AB.txt
						goto loop2;
					}
					else
					{
						Check_SerialMAC_log = L"not found SerialMAC_log";
						OnWriteFileLine(ResultPath, L"FAIL\r\n");
						OnWriteFileLine(ResultPath, L"fail," + DB1404 + s + Function + s + Check_SerialMAC_log);
						DisplayResult(L"fail");
						goto loop1;
					}
					Sleep(200);

					loop2:
					if (run == L"T")
					{
						if (Check == _T("1"))
						{
							CheckFunc();
							Sleep(300);
							int lineip = GetFileLine(ipconfig_path);
							file_ip.Open(ipconfig_path, CFile::modeRead);
							for (int y = 0; y < lineip; y++)
							{
								file_ip.ReadString(str_ip);
								result_ip += str_ip;
								//CharToUTF8(result);
							}
							file_ip.Close();

							if (result_ip.Find(MacAddress) > 0)
							{
								//DisplayResult(L"pass");
								OnWriteFileLine(ResultPath, L"PASS\r\n");
								OnWriteFileLine(ResultPath, L"pass," + T + s + Function + s + _T("Scan Mac:") + value + s + _T("Dev Mac:") + MacAddress + s + _T("Dev Path:") + str2 + s + _T("SN:") + SN);
							}
							else
							{
								//DisplayResult(L"fail");
								OnWriteFileLine(ResultPath, L"FAIL\r\n");
								OnWriteFileLine(ResultPath, L"fail," + DB1404 + s + Function + s + _T("Scan Mac:") + value + s + _T("Dev Mac:") + _T("1.MacAddressNotFound") + s + _T("Dev Path:") + _T("1.MacAddressNotFound") + s + _T("SN:") + SN);
							}
						}
						else
						{
							//Check=0 
							//DisplayResult(L"pass");
							OnWriteFileLine(ResultPath, L"PASS\r\n");
							OnWriteFileLine(ResultPath, L"pass," + T + s + Function + s + _T("Scan Mac:") + value + s + _T("Dev Mac:") + MacAddress + s + _T("Dev Path:") + str2 + s + _T("SN:") + SN);
						}
					}
					else
					{
						//DisplayResult(L"fail");
						OnWriteFileLine(ResultPath, L"FAIL\r\n");
						OnWriteFileLine(ResultPath, L"fail," + DB1404 + s + Function + s + _T("Scan Mac:") + value + s + _T("Dev Mac:") + _T("2.MacBurnFail") + s + _T("Dev Path:") + _T("2.MacBurnFail") + s + _T("SN:") + SN);
					}
				}
				else
				{
					AfxMessageBox(L"长度不是12位");
					//DisplayResult(L"fail");
					OnWriteFileLine(ResultPath, L"FAIL\r\n");
					OnWriteFileLine(ResultPath, L"fail," + DB1404 + s + Function + s + _T("Scan Mac:") + value + s + _T("Dev Mac:") + _T("3.NULL") + s + _T("Dev Path:") + _T("3.NULL") + s + _T("SN:") + SN);
				}
				loop1:
				//MES 上传
				CString cc;
				int ccnum;
				GetPrivateProfileStringW(_T("WindowPrompts"), _T("Set"), CString("NULL"), cc.GetBuffer(MAX_PATH), MAX_PATH, ConfigPath);
				ccnum = _ttoi(cc);
				CString ColorResultX;
				ColorResultX = ReadFileFirstLine(ResultPath);

				CString upload_pass;
				CStdioFile MesFile;
				CString MesNull = _T("");
				CString MesStr;
				CString MesResult;
				int MesLine;
				MesLine = GetFileLine(ResultPath);
				MesFile.Open(ResultPath, CFile::modeRead);
				MesFile.ReadString(MesNull);
				for (int i = 0; i < MesLine; i++)
				{
					MesFile.ReadString(MesStr);
					MesResult += MesStr;
				}
				MesFile.Close();

				if ((ccnum == 1) && ((ColorResultX.Mid(0, 4) == "FAIL")))		//Config.ini [WindowPrompts] Set=1 过站提醒 Set=0 不提醒
				{
					//弹窗提醒
					WindowPromptsDlg.DoModal();
					if (WP == 1)
					{
						SetDlgItemText(IDC_EDIT8, _T("数据上传中..."));
						upload_pass = MesDlg.ResultToMES(site, user, PCB, equip, DB1404, MesResult);

						string up_pass = (LPCSTR)(CStringA)(upload_pass);
						if (up_pass == "T")
						{
							SetDlgItemText(IDC_EDIT8, L"f.上传MES成功");
							DisplayResult(_T("fail"));//因为是错误 结果上传 所以要保持一致fail
						}
						else
						{
							SetDlgItemText(IDC_EDIT8, L"f.上传MES失败");
							DisplayResult(_T("fail"));
						}
						GetDlgItem(IDC_EDIT2)->EnableWindow(TRUE);
						GetDlgItem(IDC_EDIT2)->SetWindowText(L"");
						GetDlgItem(IDC_EDIT1)->EnableWindow(TRUE);
						GetDlgItem(IDC_EDIT1)->SetWindowText(L"");
						GetDlgItem(IDC_EDIT2)->SetFocus();
						DeleteFile(ResultPath);
					}
					else
					{
						if (ColorResultX.Mid(0, 4) == "PASS")
						{
							DisplayResult(_T("fail"));
						}
						else if (ColorResultX.Mid(0, 4) == "FAIL")
						{
							DisplayResult(_T("fail"));
						}
						SetDlgItemText(IDC_EDIT8, L"选择不上传重新测试");
						GetDlgItem(IDC_EDIT2)->EnableWindow(TRUE);
						GetDlgItem(IDC_EDIT2)->SetWindowText(L"");
						GetDlgItem(IDC_EDIT1)->EnableWindow(TRUE);
						GetDlgItem(IDC_EDIT1)->SetWindowText(L"");
						GetDlgItem(IDC_EDIT2)->SetFocus();
						DisplayResult(_T("wait"));
						DeleteFile(ResultPath);
					}
				}
				else
				{
					SetDlgItemText(IDC_EDIT8, _T("数据上传中..."));
					upload_pass = MesDlg.ResultToMES(site, user, PCB, equip, _T(""), MesResult);
					//AfxMessageBox(upload_pass);
					string up_pass = (LPCSTR)(CStringA)(upload_pass);
					if (up_pass == "T")
					{
						SetDlgItemText(IDC_EDIT8, L"p.上传MES成功");
						DisplayResult(_T("pass"));
					}
					else
					{
						SetDlgItemText(IDC_EDIT8, L"p.上传MES失败");
						DisplayResult(_T("fail"));
					}
					GetDlgItem(IDC_EDIT2)->EnableWindow(TRUE);
					GetDlgItem(IDC_EDIT2)->SetWindowText(L"");
					GetDlgItem(IDC_EDIT1)->EnableWindow(TRUE);
					GetDlgItem(IDC_EDIT1)->SetWindowText(L"");
					GetDlgItem(IDC_EDIT2)->SetFocus();
					DeleteFile(ResultPath);
				}
			}
			else
			{
				//工单不一致 界面控件重置
				AfxMessageBox(L"ERROR\n" + L"工单不一致\n" + L"当前工单：" + number + L"\n" + L"输入PCB工单：" + CheckNumberResult);
				GetDlgItem(IDC_EDIT2)->EnableWindow(TRUE);
				GetDlgItem(IDC_EDIT2)->SetWindowText(L"");
				GetDlgItem(IDC_EDIT1)->EnableWindow(TRUE);
				GetDlgItem(IDC_EDIT1)->SetWindowText(L"");
				GetDlgItem(IDC_EDIT2)->SetFocus();
				SetDlgItemText(IDC_EDIT8, L"工单错误");
			}
		}
		else
		{
			//PCB不存在或者不在当站 界面控件重置
			AfxMessageBox(PCBResult);
			GetDlgItem(IDC_EDIT2)->EnableWindow(TRUE);
			GetDlgItem(IDC_EDIT2)->SetWindowText(L"");
			GetDlgItem(IDC_EDIT1)->EnableWindow(TRUE);
			GetDlgItem(IDC_EDIT1)->SetWindowText(L"");
			GetDlgItem(IDC_EDIT2)->SetFocus();
			SetDlgItemText(IDC_EDIT8, L"PCB错误");
		}

	}
	else
	{
		//不连接MES测试
		GetDlgItem(IDC_EDIT1)->SetFocus();
		if (value.GetLength() == 12)
		{
			file_mac.Open(EEPROMPATH, CFile::modeRead);
			for (int i = 0; i < line; i++)
			{
				file_mac.ReadString(strMac);
				if (line = 4)
				{
					resultMac = strMac;
				}
			}
			file_mac.Close();
			ReplaceFuncMAC(resultMac, value);

			Sleep(100);
			file_mac_max.Open(EEPROMPATH, CFile::modeRead);
			for (int i = 0; i < line; i++)
			{
				file_mac_max.ReadString(strMacMax);
				if (line = 5)
				{
					resultMacMax = strMacMax;
				}
			}
			file_mac_max.Close();
			ReplaceFuncMACMAX(resultMacMax, Mstr);

			Sleep(100);
			file_dev.Open(EEPROMPATH, CFile::modeRead);
			for (int j = 0; j < line; j++)
			{
				file_dev.ReadString(strDev);
				if (line = 7)
				{
					resultDev = strDev;
				}
			}
			file_dev.Close();
			ReplaceFuncDEV(resultDev, str2);

			Sleep(100);
			file_dev_max.Open(EEPROMPATH, CFile::modeRead);
			for (int j = 0; j < line; j++)
			{
				file_dev_max.ReadString(strDevMax);
				if (line = 8)
				{
					resultDevMax = strDevMax;
				}
			}
			file_dev_max.Close();
			ReplaceFuncDEVMAX(resultDevMax, Dstr);

			ShellExecute(NULL, _T("open"), _T("cmd.exe"), exeName, PATH + Burn, SW_HIDE);
			//Sleep(200);
			ButtonFunc();
			Sleep(200);
			BOOL ifFind = finder.FindFile(SerialMACPath);
			if (ifFind)
			{
				finder.Close();
				//Check_SerialMAC_log = ReadFileFirstLine(SerialMACPath);  //read AB.txt
				goto loop22;
			}
			else
			{
				Check_SerialMAC_log = L"not found SerialMAC_log";
				OnWriteFileLine(ResultPath, L"FAIL\r\n");
				OnWriteFileLine(ResultPath, L"fail," + DB1404 + s + Function + s + Check_SerialMAC_log);
				DisplayResult(L"fail");
			}
			Sleep(200);

			loop22:
			if (run == L"T")
			{
				if (Check == _T("1"))
				{
					CheckFunc();
					Sleep(300);
					int lineip = GetFileLine(ipconfig_path);
					file_ip.Open(ipconfig_path, CFile::modeRead);
					for (int y = 0; y < lineip; y++)
					{
						file_ip.ReadString(str_ip);					
						result_ip += str_ip;
						CharToUTF8(result_ip);
					}
					file_ip.Close();
				//	AfxMessageBox(result_ip);

					if (result_ip.Find(MacAddress) > 0)
					{
						//DisplayResult(L"pass");
						OnWriteFileLine(ResultPath, L"PASS\r\n");
						OnWriteFileLine(ResultPath, L"pass," + T + s + Function + s + _T("Scan Mac:") + value + s + _T("Dev Mac:") + MacAddress + s + _T("Dev Path:") + str2 + s + _T("SN:") + SN);
					}
					else
					{
						//DisplayResult(L"fail");
						OnWriteFileLine(ResultPath, L"FAIL\r\n");
						OnWriteFileLine(ResultPath, L"fail," + DB1404 + s + Function + s + _T("Scan Mac:") + value + s + _T("Dev Mac:") + _T("1.MacAddressNotFound") + s + _T("Dev Path:") + _T("1.MacAddressNotFound") + s + _T("SN:") + SN);
					}
				}
				else
				{
					//Check=0 
					//DisplayResult(L"pass");
					OnWriteFileLine(ResultPath, L"PASS\r\n");
					OnWriteFileLine(ResultPath, L"pass," + T + s + Function + s + _T("Scan Mac:") + value + s + _T("Dev Mac:") + MacAddress + s + _T("Dev Path:") + str2 + s + _T("SN:") + SN);
				}
			}
			else
			{
				//DisplayResult(L"fail");
				OnWriteFileLine(ResultPath, L"FAIL\r\n");
				OnWriteFileLine(ResultPath, L"fail," + DB1404 + s + Function + s + _T("Scan Mac:") + value + s + _T("Dev Mac:") + _T("2.MacBurnFail") + s + _T("Dev Path:") + _T("2.MacBurnFail") + s + _T("SN:") + SN);
			}
		}
		else
		{
			AfxMessageBox(L"长度不是12位");
			//DisplayResult(L"fail");
			OnWriteFileLine(ResultPath, L"FAIL\r\n");
			OnWriteFileLine(ResultPath, L"fail," + DB1404 + s + Function + s + _T("Scan Mac:") + value + s + _T("Dev Mac:") + _T("3.NULL") + s + _T("Dev Path:") + _T("3.NULL") + s + _T("SN:") + SN);
		}

		CString ColorResultX;
		ColorResultX = ReadFileFirstLine(ResultPath);
		if (ColorResultX.Mid(0, 4) == "PASS")
		{
			DisplayResult(_T("pass"));
		}
		else if (ColorResultX.Mid(0, 4) == "FAIL")
		{
			DisplayResult(_T("fail"));
		}
		GetDlgItem(IDC_EDIT2)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT2)->SetWindowText(L"");
		GetDlgItem(IDC_EDIT1)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT1)->SetWindowText(L"");
		GetDlgItem(IDC_EDIT2)->SetFocus();
		DeleteFile(ResultPath);
		
	}
	
}


HBRUSH CBurnProcessDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	if (pWnd->GetDlgCtrlID() == IDC_EDIT3)//如果是静态编辑框
	{
		//pDC->SetTextColor(RGB(0, 0, 0));//修改字体的颜色
		//pDC->SetBkMode(TRANSPARENT);//把字体的背景变成透明的
		pDC->SetTextColor(EndResult_textColor);
		pDC->SetBkColor(EndResult_backColor);

		hbr = (HBRUSH)EndResult_backBrush.GetSafeHandle();  //功能：适应static大小的背景颜色
		//return m_brush;//返回背景色
	}
	else if (pWnd->GetDlgCtrlID() == IDC_EDIT8)//如果是静态编辑框
	{
		//pDC->SetTextColor(RGB(0, 0, 0));//修改字体的颜色
		//pDC->SetBkMode(TRANSPARENT);//把字体的背景变成透明的
		pDC->SetTextColor(EndResult_textColor_mes);
		pDC->SetBkColor(EndResult_backColor_mes);

		hbr = (HBRUSH)EndResult_backBrush_mes.GetSafeHandle();  //功能：适应static大小的背景颜色
		//return m_brush;//返回背景色
	}

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}


BOOL CBurnProcessDlg::PreTranslateMessage(MSG* pMsg)
{
	CString PCB;
	m_edit2.GetWindowText(PCB);
	//m_edit_site.GetWindowText(site);

	//CString PCBResult = MesDlg.CheckPCB(site, PCB);
	//string mes_pcb_result = (LPCSTR)(CStringA)(PCBResult);
	if (WM_KEYDOWN == pMsg->message && VK_RETURN == pMsg->wParam)
	{
		if (GetFocus() == GetDlgItem(IDC_EDIT2))
		{
			if (PCB.GetLength() == 9)
			{

				GetDlgItem(IDC_EDIT1)->SetFocus();
				
			}
			else
			{
				AfxMessageBox(L"PCB长度不一致");
				m_edit2.SetWindowText(_TEXT(""));
				GetDlgItem(IDC_EDIT2)->SetFocus();
			}
		}
		else if (GetFocus() == GetDlgItem(IDC_EDIT1))
		{
			OnBnClickedButton1();
		}
		return true;
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


void CBurnProcessDlg::OnBnClickedRadio1()
{
	// TODO: 在此添加控件通知处理程序代码
	CString Config = _T("Config.ini");
	CString ConfigPath = PATH + Config;
	CString PrefixNum;
	GetPrivateProfileString(_T("PrefixNum"), _T("Set"), CString("NULL"), PrefixNum.GetBuffer(MAX_PATH), MAX_PATH, ConfigPath);
	PrefixNum.ReleaseBuffer();
	CString MES_SITE;
	MES_SITE = MesDlg.CheckSite(_T(""));

	string login_site = (LPCSTR)(CStringA)(MES_SITE);
	UpdateData(TRUE);
	RadioState_Yes = ((CButton *)GetDlgItem(IDC_RADIO1))->GetCheck();
	if ((RadioState_Yes == 1) && (MES_SITE == "T"))
	{
		GetDlgItem(IDC_EDIT2)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT1)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT2)->SetFocus();

		loginDlg.DoModal();
		m_edit_site.SetWindowText(loginDlg.Site);
		m_edit_user.SetWindowText(loginDlg.User);
		m_edit_equip.SetWindowText(loginDlg.Equip);
		m_edit_number.SetWindowText(loginDlg.Number);
		m_edit_macmax.SetWindowText(loginDlg.MacMax);
		m_edit_devmax.SetWindowText(PrefixNum + loginDlg.MacMax);
		SetDlgItemText(IDC_EDIT8, L"MES连接成功");
		//DisplayMESconnet(_T("pass"));
		if (loginclose == 0)
		{
			GetDlgItem(IDC_EDIT2)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT1)->EnableWindow(FALSE);
			((CButton *)GetDlgItem(IDC_RADIO1))->SetCheck(0);
			m_edit_devmax.SetWindowText(L"");
			SetDlgItemText(IDC_EDIT8, L"MES连接失败");
			//DisplayMESconnet(_T("fail"));
		}

	}
	else if ((RadioState_Yes == 1) && (MES_SITE != "T"))
	{
		GetDlgItem(IDC_EDIT2)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT1)->EnableWindow(FALSE);
		//SetDlgItemText(IDC_EDIT1, L"连接MES失败");
		AfxMessageBox(_T("连接失败或者没有连接到MES专用网络"));
		((CButton *)GetDlgItem(IDC_RADIO1))->SetCheck(0);
		//DisplayMESconnet(_T("fail"));
	}
}


void CBurnProcessDlg::OnBnClickedRadio2()
{
	// TODO: 在此添加控件通知处理程序代码
	CString Config = _T("Config.ini");
	CString ConfigPath = PATH + Config;
	CString PrefixNum;
	GetPrivateProfileString(_T("PrefixNum"), _T("Set"), CString("NULL"), PrefixNum.GetBuffer(MAX_PATH), MAX_PATH, ConfigPath);
	PrefixNum.ReleaseBuffer();

	UpdateData(TRUE);
	passwordDlg.DoModal();
	if (mespasswordflag == 1)
	{
		GetDlgItem(IDC_EDIT2)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT1)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT2)->SetFocus();
		SetDlgItemText(IDC_EDIT8, L"MES不连接");
		//不连接解锁成功后，弹窗扫码两次MAX
		NoConnectMaxDlg.DoModal();
		m_edit_macmax.SetWindowText(NoConnectMaxDlg.macmax);
		m_edit_devmax.SetWindowText(PrefixNum + NoConnectMaxDlg.macmax);
		if (loginclose == 0)
		{
			GetDlgItem(IDC_EDIT2)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT1)->EnableWindow(FALSE);
			((CButton *)GetDlgItem(IDC_RADIO2))->SetCheck(0);
			m_edit_devmax.SetWindowText(L"");
			SetDlgItemText(IDC_EDIT8, L"MacMax错误");
			//DisplayMESconnet(_T("fail"));
		}

		
	}
	else if (mespasswordflag == 0)
	{
		((CButton *)GetDlgItem(IDC_RADIO2))->SetCheck(FALSE);
		GetDlgItem(IDC_EDIT2)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT1)->EnableWindow(FALSE);
		SetDlgItemText(IDC_EDIT8, L"解锁失败");
		//DisplayMESconnet(_T("fail"));
	}

}

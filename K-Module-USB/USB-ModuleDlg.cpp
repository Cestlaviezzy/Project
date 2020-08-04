
// USB-ModuleDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "USB-Module.h"
#include "USB-ModuleDlg.h"
#include "afxdialogex.h"
#include <string>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace std;


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框
CString PATH;
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


// CUSBModuleDlg 对话框



CUSBModuleDlg::CUSBModuleDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_USBMODULE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CUSBModuleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CUSBModuleDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CUSBModuleDlg::OnBnClickedButton1)
	ON_WM_WINDOWPOSCHANGING()
END_MESSAGE_MAP()


// CUSBModuleDlg 消息处理程序

BOOL CUSBModuleDlg::OnInitDialog()
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

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CUSBModuleDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CUSBModuleDlg::OnPaint()
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
HCURSOR CUSBModuleDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

CString CUSBModuleDlg::ReadFileFirstLine(CString path)
{
	CStdioFile file;
	CString line_result;

	if (file.Open(path, CFile::modeRead))
	{
		file.ReadString(line_result);
		file.Close();			//不能写反，先关闭后return
		return line_result;
	}
	else
	{
		//AfxMessageBox(_TEXT("USB没有获取到AB.TXT文件"));
		return ResultNULL;
	}

}

void CUSBModuleDlg::OnWriteFileLine(CString path, CString str)
{
	USES_CONVERSION;
	CStdioFile file;
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
	if (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))//取消息，检索应用程序的消息队列，   PM_REMOVE取过之后从消息队列中移除  
	{
		//发消息  
		::TranslateMessage(&msg);
		::DispatchMessage(&msg);
	}
}
void TheadWait(HANDLE m_hThread)
{
	//HANDLE DoEvent();//线程事件
	////等待线程完成函数/////
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

void CUSBModuleDlg::OnRunExe(CString path, CString Param)
{
	SHELLEXECUTEINFO ShExecInfo = { 0 };
	ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
	ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
	ShExecInfo.hwnd = NULL;
	ShExecInfo.lpVerb = NULL;
	ShExecInfo.lpFile = path;
	ShExecInfo.lpParameters = Param;
	ShExecInfo.lpDirectory = NULL;
	ShExecInfo.nShow = SW_HIDE;
	ShExecInfo.hInstApp = NULL;
	ShellExecuteEx(&ShExecInfo);
	TheadWait(ShExecInfo.hProcess);
}

void CUSBModuleDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CString USB = _TEXT("USB\\");
	CString UsbExe = _TEXT("USB3014TB.exe");
	CString UsbExePath = PATH + USB + UsbExe;
	CString ResultTXT = _TEXT("Result.txt");
	CString ResultPath = PATH + +USB + ResultTXT;
	DeleteFile(ResultPath);
	CString USBTesterINI = _TEXT("USB3014Tester.ini");
	CString USBTesterINIPath = PATH + USB + USBTesterINI;
	BOOL ifFindresult = finderResult.FindFile(ResultPath);
	BOOL ifFindtxt = finderTXT.FindFile(AB_TXT);
	CString PortNum;
	int PortNumInt;
	//USB2.0  USB3.0变量
	CString USB2Read, USB2Write;
	CString USB3Read, USB3Write;
	CString MinVoltage, MaxVoltage;

	CStdioFile file;
	CString arry[1024];
	CString LineRsult;
	int len;
	CString res;//接收Result.txt第一行数据做判断
	CString dest;//接收产生的log
	CString Count;//记录port个数



	//RUN exe
	OnRunExe(UsbExePath, NULL);

	//获取标准值read/write/Voltage/
	//USB 2.0 read/write
	GetPrivateProfileString(_T("SpeedMode"), _T("HighSpeedRead"), CString("0"), USB2Read.GetBuffer(MAX_PATH), MAX_PATH, USBTesterINIPath);
	USB2Read.ReleaseBuffer();
	GetPrivateProfileString(_T("SpeedMode"), _T("HighSpeedWrite"), CString("0"), USB2Write.GetBuffer(MAX_PATH), MAX_PATH, USBTesterINIPath);
	USB2Write.ReleaseBuffer();
	//USB 3.0 read/write
	GetPrivateProfileString(_T("SpeedMode"), _T("SuperSpeedRead"), CString("0"), USB3Read.GetBuffer(MAX_PATH), MAX_PATH, USBTesterINIPath);
	USB3Read.ReleaseBuffer();
	GetPrivateProfileString(_T("SpeedMode"), _T("SuperSpeedWrite"), CString("0"), USB3Write.GetBuffer(MAX_PATH), MAX_PATH, USBTesterINIPath);
	USB3Write.ReleaseBuffer();
	//USB Voltage Min/Max
	GetPrivateProfileString(_T("PowerManagement"), _T("MinVoltage"), CString("0"), MinVoltage.GetBuffer(MAX_PATH), MAX_PATH, USBTesterINIPath);
	MinVoltage.ReleaseBuffer();
	GetPrivateProfileString(_T("PowerManagement"), _T("MaxVoltage"), CString("0"), MaxVoltage.GetBuffer(MAX_PATH), MAX_PATH, USBTesterINIPath);
	MaxVoltage.ReleaseBuffer();

	//获取运行日志数据
	GetPrivateProfileString(_T("BindID"), _T("PORT_NUM"), CString("NULL"), PortNum.GetBuffer(MAX_PATH), MAX_PATH, USBTesterINIPath);
	PortNumInt = _ttoi(PortNum);
	
	res = ReadFileFirstLine(ResultPath);
	if (res == _TEXT("PASS"))
	{
		OnWriteFileLine(PATH + L"result.log", PASS + L"\n");
	}
	else if (res == _TEXT("FAIL"))
	{
		OnWriteFileLine(PATH + L"result.log", FAIL + L"\n");
	}
	else
	{
		OnWriteFileLine(PATH + L"result.log", FAIL + L"\n");
		//OnWriteFileLine(PATH + L"result.log", L"fail" + s + DB1300 + s + AB + s + USB32+L"\n");
	}

	
	for (int i = 1; i <= PortNumInt; i++)
	{
		Count.Format(_TEXT("%d"), i);
		if (file.Open(ResultPath, CFile::modeRead))
		{
			//finderResult.Close();
			for (int j = 1; j < 2 + i * 26; j++)
			{
				file.ReadString(arry[j]);
				//LineRsult += arry[j] + _TEXT("\r\n");
				arry[j].MakeLower();
				//USB3.0
				if (j == 3 + (i - 1) * 26)
				{
					len = arry[j].Find(_TEXT(":"));
					CONNResult3 = arry[j].Right(arry[j].GetLength() - len - 2);
				}
				if (j == 4 + (i - 1) * 26)
				{
					len = arry[j].Find(_TEXT(":"));
					SHORTResult3 = arry[j].Right(arry[j].GetLength() - len - 2);
				}
				if (j == 5 + (i - 1) * 26)
				{
					len = arry[j].Find(_TEXT(":"));
					ISOResult3 = arry[j].Right(arry[j].GetLength() - len - 2);
				}
				if (j == 6 + (i - 1) * 26)
				{
					len = arry[j].Find(_TEXT(":"));
					INTResult3 = arry[j].Right(arry[j].GetLength() - len - 2);
				}
				if (j == 7 + (i - 1) * 26)
				{
					len = arry[j].Find(_TEXT(":"));
					CTRLResult3 = arry[j].Right(arry[j].GetLength() - len - 2);
				}
				if (j == 8 + (i - 1) * 26)
				{
					len = arry[j].Find(_TEXT(":"));
					VBUSResult3 = arry[j].Right(arry[j].GetLength() - len - 2);
				}
				if (j == 9 + (i - 1) * 26)
				{
					len = arry[j].Find(_TEXT(":"));
					BC1_2Result3 = arry[j].Right(arry[j].GetLength() - len - 2);
				}
				if (j == 10 + (i - 1) * 26)
				{
					len = arry[j].Find(_TEXT(":"));
					LOADResult3 = arry[j].Right(arry[j].GetLength() - len - 2);
				}
				if (j == 11 + (i - 1) * 26)
				{
					len = arry[j].Find(_TEXT(":"));
					BULKResult3 = arry[j].Right(arry[j].GetLength() - len - 2);
				}
				if (j == 12 + (i - 1) * 26)
				{
					len = arry[j].Find(_TEXT(":"));
					FSResult3 = arry[j].Right(arry[j].GetLength() - len - 2);
				}
				if (j == 13 + (i - 1) * 26)
				{
					len = arry[j].Find(_TEXT(":"));
					HSResult3 = arry[j].Right(arry[j].GetLength() - len - 2);
				}
				if (j == 14 + (i - 1) * 26)
				{
					len = arry[j].Find(_TEXT(":"));
					SSResult3 = arry[j].Right(arry[j].GetLength() - len - 2);
				}

				//USB2.0
				if (j == 15 + (i - 1) * 26)
				{
					len = arry[j].Find(_TEXT(":"));
					CONNResult2 = arry[j].Right(arry[j].GetLength() - len - 2);
				}
				if (j == 16 + (i - 1) * 26)
				{
					len = arry[j].Find(_TEXT(":"));
					SHORTResult2 = arry[j].Right(arry[j].GetLength() - len - 2);
				}
				if (j == 17 + (i - 1) * 26)
				{
					len = arry[j].Find(_TEXT(":"));
					ISOResult2 = arry[j].Right(arry[j].GetLength() - len - 2);
				}
				if (j == 18 + (i - 1) * 26)
				{
					len = arry[j].Find(_TEXT(":"));
					INTResult2 = arry[j].Right(arry[j].GetLength() - len - 2);
				}
				if (j == 19 + (i - 1) * 26)
				{
					len = arry[j].Find(_TEXT(":"));
					CTRLResult2 = arry[j].Right(arry[j].GetLength() - len - 2);
				}
				if (j == 20 + (i - 1) * 26)
				{
					len = arry[j].Find(_TEXT(":"));
					VBUSResult2 = arry[j].Right(arry[j].GetLength() - len - 2);
				}
				if (j == 21 + (i - 1) * 26)
				{
					len = arry[j].Find(_TEXT(":"));
					BC1_2Result2 = arry[j].Right(arry[j].GetLength() - len - 2);
				}
				if (j == 22 + (i - 1) * 26)
				{
					len = arry[j].Find(_TEXT(":"));
					LOADResult2 = arry[j].Right(arry[j].GetLength() - len - 2);
				}
				if (j == 23 + (i - 1) * 26)
				{
					len = arry[j].Find(_TEXT(":"));
					BULKResult2 = arry[j].Right(arry[j].GetLength() - len - 2);
				}
				if (j == 24 + (i - 1) * 26)
				{
					len = arry[j].Find(_TEXT(":"));
					FSResult2 = arry[j].Right(arry[j].GetLength() - len - 2);
				}
				if (j == 25 + (i - 1) * 26)
				{
					len = arry[j].Find(_TEXT(":"));
					HSResult2 = arry[j].Right(arry[j].GetLength() - len - 2);
				}
				if (j == 26 + (i - 1) * 26)
				{
					len = arry[j].Find(_TEXT(":"));
					SSResult2 = arry[j].Right(arry[j].GetLength() - len - 2);
				}
				if (j == 27 + (i - 1) * 26)
				{
					len = arry[j].Find(_TEXT(":"));
					PortResult = arry[j].Right(arry[j].GetLength() - len - 2);
				}
			}
			file.Close();
		}
		else
		{
			//Result.txt不存在
			//没有连接USB，设备检测不到，不会生成Result.txt  这里要注意
			//OnWriteFileLine(PATH + L"result.log", FAIL + L"\n");
			ResultNULL = _TEXT("could not found Result.txt");
		}

		//CString::MakeLower
		//CString::MakeUpper
		//CONNResult2.MakeLower();
		/****************数据组装***********************/

		//获取正反面文件
		if (ifFindtxt)
		{
			finderTXT.Close();
			AB = ReadFileFirstLine(AB_TXT);  //read AB.txt
		}
		else
		{
			AB = L"M";
		}

		if (PortResult == _TEXT("pass"))
		{
			OnWriteFileLine(PATH + L"result.log", PortResult + s + L"T" + s + AB + s + USB32 + L"-" + p + Count
				+ s + SS + L":" + SSResult3 + s + L"R" + USB3Read + L"W" + USB3Write
				+ s + LOAD + L":" + LOADResult3 + s + L"Min" + MinVoltage + L"-" + L"Max" + MaxVoltage
				+ s + CONN + L":" + CONNResult3
				+ s + SHORT + L":" + SHORTResult3
				+ s + ISO + L":" + ISOResult3
				+ s + INT + L":" + INTResult3
				+ s + CTRL + L":" + CTRLResult3
				+ s + VBUS + L":" + VBUSResult3
				+ s + BC1_2 + L":" + BC1_2Result3
				+ s + BULK + L":" + BULKResult3
				+ s + FS + L":" + FSResult3
				+ s + HS + L":" + HSResult3
				+ s + HS + L":" + HSResult2 + s + L"R" + USB2Read + L"W" + USB2Write
				+ s + LOAD + L":" + LOADResult2 + s + L"Min" + MinVoltage + L"-" + L"Max" + MaxVoltage
				+ s + CONN + L":" + CONNResult2 
				+ s + SHORT + L":" + SHORTResult2 
				+ s + ISO + L":" + ISOResult2 
				+ s + INT + L":" + INTResult2 
				+ s + CTRL + L":" + CTRLResult2 
				+ s + VBUS + L":" + VBUSResult2
				+ s + BC1_2 + L":" + BC1_2Result2 
				+ s + BULK + L":" + BULKResult2 
				+ s + FS + L":" + FSResult2 
				+ s + SS + L":" + SSResult2 
				+ L"\n");
		}
		else if (PortResult == _TEXT("fail"))
		{
			OnWriteFileLine(PATH + L"result.log", PortResult + s + DB1300 + s + AB + s + USB32 + L"-" + p + Count
				+ s + SS + L":" + SSResult3 + s + L"R" + USB3Read + L"W" + USB3Write
				+ s + LOAD + L":" + LOADResult3 + s + L"Min" + MinVoltage + L"-" + L"Max" + MaxVoltage
				+ s + CONN + L":" + CONNResult3
				+ s + SHORT + L":" + SHORTResult3
				+ s + ISO + L":" + ISOResult3
				+ s + INT + L":" + INTResult3
				+ s + CTRL + L":" + CTRLResult3
				+ s + VBUS + L":" + VBUSResult3
				+ s + BC1_2 + L":" + BC1_2Result3
				+ s + BULK + L":" + BULKResult3
				+ s + FS + L":" + FSResult3
				+ s + HS + L":" + HSResult3
				+ s + HS + L":" + HSResult2 + s + L"R" + USB2Read + L"W" + USB2Write
				+ s + LOAD + L":" + LOADResult2 + s + L"Min" + MinVoltage + L"-" + L"Max" + MaxVoltage
				+ s + CONN + L":" + CONNResult2
				+ s + SHORT + L":" + SHORTResult2
				+ s + ISO + L":" + ISOResult2
				+ s + INT + L":" + INTResult2
				+ s + CTRL + L":" + CTRLResult2
				+ s + VBUS + L":" + VBUSResult2
				+ s + BC1_2 + L":" + BC1_2Result2
				+ s + BULK + L":" + BULKResult2
				+ s + FS + L":" + FSResult2
				+ s + SS + L":" + SSResult2
				+ L"\n");
		}
		else
		{
			OnWriteFileLine(PATH + L"result.log", L"fail" + s + DB1300 + s + AB + s + USB32 + L"-" + p + Count + ResultNULL + L"\n");
		}

	}

}


void CUSBModuleDlg::OnAuToFunc()
{
	CString USB = _TEXT("USB\\");
	CString UsbExe = _TEXT("USB3014TB.exe");
	CString UsbExePath = PATH + USB + UsbExe;
	CString ResultTXT = _TEXT("Result.txt");
	CString ResultPath = PATH + +USB + ResultTXT;
	DeleteFile(ResultPath);
	CString USBTesterINI = _TEXT("USB3014Tester.ini");
	CString USBTesterINIPath = PATH + USB + USBTesterINI;
	BOOL ifFindresult = finderResult.FindFile(ResultPath);
	BOOL ifFindtxt = finderTXT.FindFile(AB_TXT);
	CString PortNum;
	int PortNumInt;
	//USB2.0  USB3.0变量
	CString USB2Read, USB2Write;
	CString USB3Read, USB3Write;
	CString MinVoltage, MaxVoltage;

	CStdioFile file;
	CString arry[1024];
	CString LineRsult;
	int len;
	CString res;//接收Result.txt第一行数据做判断
	CString dest;//接收产生的log
	CString Count;//记录port个数



	//RUN exe
	OnRunExe(UsbExePath, NULL);

	//获取标准值read/write/Voltage/
	//USB 2.0 read/write
	GetPrivateProfileString(_T("SpeedMode"), _T("HighSpeedRead"), CString("0"), USB2Read.GetBuffer(MAX_PATH), MAX_PATH, USBTesterINIPath);
	USB2Read.ReleaseBuffer();
	GetPrivateProfileString(_T("SpeedMode"), _T("HighSpeedWrite"), CString("0"), USB2Write.GetBuffer(MAX_PATH), MAX_PATH, USBTesterINIPath);
	USB2Write.ReleaseBuffer();
	//USB 3.0 read/write
	GetPrivateProfileString(_T("SpeedMode"), _T("SuperSpeedRead"), CString("0"), USB3Read.GetBuffer(MAX_PATH), MAX_PATH, USBTesterINIPath);
	USB3Read.ReleaseBuffer();
	GetPrivateProfileString(_T("SpeedMode"), _T("SuperSpeedWrite"), CString("0"), USB3Write.GetBuffer(MAX_PATH), MAX_PATH, USBTesterINIPath);
	USB3Write.ReleaseBuffer();
	//USB Voltage Min/Max
	GetPrivateProfileString(_T("PowerManagement"), _T("MinVoltage"), CString("0"), MinVoltage.GetBuffer(MAX_PATH), MAX_PATH, USBTesterINIPath);
	MinVoltage.ReleaseBuffer();
	GetPrivateProfileString(_T("PowerManagement"), _T("MaxVoltage"), CString("0"), MaxVoltage.GetBuffer(MAX_PATH), MAX_PATH, USBTesterINIPath);
	MaxVoltage.ReleaseBuffer();

	//获取运行日志数据
	GetPrivateProfileString(_T("BindID"), _T("PORT_NUM"), CString("NULL"), PortNum.GetBuffer(MAX_PATH), MAX_PATH, USBTesterINIPath);
	PortNumInt = _ttoi(PortNum);

	res = ReadFileFirstLine(ResultPath);
	if (res == _TEXT("PASS"))
	{
		OnWriteFileLine(PATH + L"result.log", PASS + L"\n");
	}
	else if (res == _TEXT("FAIL"))
	{
		OnWriteFileLine(PATH + L"result.log", FAIL + L"\n");
	}
	else
	{
		OnWriteFileLine(PATH + L"result.log", FAIL + L"\n");
	}


	for (int i = 1; i <= PortNumInt; i++)
	{
		Count.Format(_TEXT("%d"), i);
		if (file.Open(ResultPath, CFile::modeRead))
		{
			//finderResult.Close();
			for (int j = 1; j < 2 + i * 26; j++)
			{
				file.ReadString(arry[j]);
				//LineRsult += arry[j] + _TEXT("\r\n");
				arry[j].MakeLower();
				//USB3.0
				if (j == 3 + (i - 1) * 26)
				{
					len = arry[j].Find(_TEXT(":"));
					CONNResult3 = arry[j].Right(arry[j].GetLength() - len - 2);
				}
				if (j == 4 + (i - 1) * 26)
				{
					len = arry[j].Find(_TEXT(":"));
					SHORTResult3 = arry[j].Right(arry[j].GetLength() - len - 2);
				}
				if (j == 5 + (i - 1) * 26)
				{
					len = arry[j].Find(_TEXT(":"));
					ISOResult3 = arry[j].Right(arry[j].GetLength() - len - 2);
				}
				if (j == 6 + (i - 1) * 26)
				{
					len = arry[j].Find(_TEXT(":"));
					INTResult3 = arry[j].Right(arry[j].GetLength() - len - 2);
				}
				if (j == 7 + (i - 1) * 26)
				{
					len = arry[j].Find(_TEXT(":"));
					CTRLResult3 = arry[j].Right(arry[j].GetLength() - len - 2);
				}
				if (j == 8 + (i - 1) * 26)
				{
					len = arry[j].Find(_TEXT(":"));
					VBUSResult3 = arry[j].Right(arry[j].GetLength() - len - 2);
				}
				if (j == 9 + (i - 1) * 26)
				{
					len = arry[j].Find(_TEXT(":"));
					BC1_2Result3 = arry[j].Right(arry[j].GetLength() - len - 2);
				}
				if (j == 10 + (i - 1) * 26)
				{
					len = arry[j].Find(_TEXT(":"));
					LOADResult3 = arry[j].Right(arry[j].GetLength() - len - 2);
				}
				if (j == 11 + (i - 1) * 26)
				{
					len = arry[j].Find(_TEXT(":"));
					BULKResult3 = arry[j].Right(arry[j].GetLength() - len - 2);
				}
				if (j == 12 + (i - 1) * 26)
				{
					len = arry[j].Find(_TEXT(":"));
					FSResult3 = arry[j].Right(arry[j].GetLength() - len - 2);
				}
				if (j == 13 + (i - 1) * 26)
				{
					len = arry[j].Find(_TEXT(":"));
					HSResult3 = arry[j].Right(arry[j].GetLength() - len - 2);
				}
				if (j == 14 + (i - 1) * 26)
				{
					len = arry[j].Find(_TEXT(":"));
					SSResult3 = arry[j].Right(arry[j].GetLength() - len - 2);
				}

				//USB2.0
				if (j == 15 + (i - 1) * 26)
				{
					len = arry[j].Find(_TEXT(":"));
					CONNResult2 = arry[j].Right(arry[j].GetLength() - len - 2);
				}
				if (j == 16 + (i - 1) * 26)
				{
					len = arry[j].Find(_TEXT(":"));
					SHORTResult2 = arry[j].Right(arry[j].GetLength() - len - 2);
				}
				if (j == 17 + (i - 1) * 26)
				{
					len = arry[j].Find(_TEXT(":"));
					ISOResult2 = arry[j].Right(arry[j].GetLength() - len - 2);
				}
				if (j == 18 + (i - 1) * 26)
				{
					len = arry[j].Find(_TEXT(":"));
					INTResult2 = arry[j].Right(arry[j].GetLength() - len - 2);
				}
				if (j == 19 + (i - 1) * 26)
				{
					len = arry[j].Find(_TEXT(":"));
					CTRLResult2 = arry[j].Right(arry[j].GetLength() - len - 2);
				}
				if (j == 20 + (i - 1) * 26)
				{
					len = arry[j].Find(_TEXT(":"));
					VBUSResult2 = arry[j].Right(arry[j].GetLength() - len - 2);
				}
				if (j == 21 + (i - 1) * 26)
				{
					len = arry[j].Find(_TEXT(":"));
					BC1_2Result2 = arry[j].Right(arry[j].GetLength() - len - 2);
				}
				if (j == 22 + (i - 1) * 26)
				{
					len = arry[j].Find(_TEXT(":"));
					LOADResult2 = arry[j].Right(arry[j].GetLength() - len - 2);
				}
				if (j == 23 + (i - 1) * 26)
				{
					len = arry[j].Find(_TEXT(":"));
					BULKResult2 = arry[j].Right(arry[j].GetLength() - len - 2);
				}
				if (j == 24 + (i - 1) * 26)
				{
					len = arry[j].Find(_TEXT(":"));
					FSResult2 = arry[j].Right(arry[j].GetLength() - len - 2);
				}
				if (j == 25 + (i - 1) * 26)
				{
					len = arry[j].Find(_TEXT(":"));
					HSResult2 = arry[j].Right(arry[j].GetLength() - len - 2);
				}
				if (j == 26 + (i - 1) * 26)
				{
					len = arry[j].Find(_TEXT(":"));
					SSResult2 = arry[j].Right(arry[j].GetLength() - len - 2);
				}
				if (j == 27 + (i - 1) * 26)
				{
					len = arry[j].Find(_TEXT(":"));
					PortResult = arry[j].Right(arry[j].GetLength() - len - 2);
				}
			}
			file.Close();
		}
		else
		{
			//Result.txt不存在
			//没有连接USB，设备检测不到，不会生成Result.txt  这里要注意
			//OnWriteFileLine(PATH + L"result.log", FAIL + L"\n");
			ResultNULL = _TEXT("could not found Result.txt");
		}

		//CString::MakeLower
		//CString::MakeUpper
		//CONNResult2.MakeLower();
		/****************数据组装***********************/

		//获取正反面文件
		if (ifFindtxt)
		{
			finderTXT.Close();
			AB = ReadFileFirstLine(AB_TXT);  //read AB.txt
		}
		else
		{
			AB = L"M";
		}

		if (PortResult == _TEXT("pass"))
		{
			OnWriteFileLine(PATH + L"result.log", PortResult + s + L"T" + s + AB + s + USB32 + L"-" + p + Count
				+ s + SS + L":" + SSResult3 + s + L"R" + USB3Read + L"W" + USB3Write
				+ s + LOAD + L":" + LOADResult3 + s + L"Min" + MinVoltage + L"-" + L"Max" + MaxVoltage
				+ s + CONN + L":" + CONNResult3
				+ s + SHORT + L":" + SHORTResult3
				+ s + ISO + L":" + ISOResult3
				+ s + INT + L":" + INTResult3
				+ s + CTRL + L":" + CTRLResult3
				+ s + VBUS + L":" + VBUSResult3
				+ s + BC1_2 + L":" + BC1_2Result3
				+ s + BULK + L":" + BULKResult3
				+ s + FS + L":" + FSResult3
				+ s + HS + L":" + HSResult3
				+ s + HS + L":" + HSResult2 + s + L"R" + USB2Read + L"W" + USB2Write
				+ s + LOAD + L":" + LOADResult2 + s + L"Min" + MinVoltage + L"-" + L"Max" + MaxVoltage
				+ s + CONN + L":" + CONNResult2
				+ s + SHORT + L":" + SHORTResult2
				+ s + ISO + L":" + ISOResult2
				+ s + INT + L":" + INTResult2
				+ s + CTRL + L":" + CTRLResult2
				+ s + VBUS + L":" + VBUSResult2
				+ s + BC1_2 + L":" + BC1_2Result2
				+ s + BULK + L":" + BULKResult2
				+ s + FS + L":" + FSResult2
				+ s + SS + L":" + SSResult2
				+ L"\n");
		}
		else if (PortResult == _TEXT("fail"))
		{
			OnWriteFileLine(PATH + L"result.log", PortResult + s + DB1300 + s + AB + s + USB32 + L"-" + p + Count
				+ s + SS + L":" + SSResult3 + s + L"R" + USB3Read + L"W" + USB3Write
				+ s + LOAD + L":" + LOADResult3 + s + L"Min" + MinVoltage + L"-" + L"Max" + MaxVoltage
				+ s + CONN + L":" + CONNResult3
				+ s + SHORT + L":" + SHORTResult3
				+ s + ISO + L":" + ISOResult3
				+ s + INT + L":" + INTResult3
				+ s + CTRL + L":" + CTRLResult3
				+ s + VBUS + L":" + VBUSResult3
				+ s + BC1_2 + L":" + BC1_2Result3
				+ s + BULK + L":" + BULKResult3
				+ s + FS + L":" + FSResult3
				+ s + HS + L":" + HSResult3
				+ s + HS + L":" + HSResult2 + s + L"R" + USB2Read + L"W" + USB2Write
				+ s + LOAD + L":" + LOADResult2 + s + L"Min" + MinVoltage + L"-" + L"Max" + MaxVoltage
				+ s + CONN + L":" + CONNResult2
				+ s + SHORT + L":" + SHORTResult2
				+ s + ISO + L":" + ISOResult2
				+ s + INT + L":" + INTResult2
				+ s + CTRL + L":" + CTRLResult2
				+ s + VBUS + L":" + VBUSResult2
				+ s + BC1_2 + L":" + BC1_2Result2
				+ s + BULK + L":" + BULKResult2
				+ s + FS + L":" + FSResult2
				+ s + SS + L":" + SSResult2
				+ L"\n");
		}
		else
		{
			OnWriteFileLine(PATH + L"result.log", L"fail" + s + DB1300 + s + AB + s + USB32 + L"-" + p + Count + ResultNULL + L"\n");
		}

	}
}



void CUSBModuleDlg::OnWindowPosChanging(WINDOWPOS* lpwndpos)
{
	CString USBConfig = L"USBConfig.ini";
	CString config = PATH + USBConfig;
	CString autotest;
	//CString USB = L"USB\\";

	GetPrivateProfileString(_T("AUTO"), _T("AUTOTESTYN"), CString("NULL"), autotest.GetBuffer(MAX_PATH), MAX_PATH, config);
	string at = (LPCSTR)(CStringA)(autotest);

	if (at == "Y")
	{
		SetWindowPos(&CWnd::wndNoTopMost, 0, 0, 0, 0, SWP_HIDEWINDOW);
		ModifyStyleEx(WS_EX_APPWINDOW, WS_EX_TOOLWINDOW);
		OnAuToFunc();
		exit(1);
	}

	CDialog::OnWindowPosChanging(lpwndpos);
}

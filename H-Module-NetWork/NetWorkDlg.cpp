
// NetWorkDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "NetWork.h"
#include "NetWorkDlg.h"
#include "afxdialogex.h"
#include <string>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace std;

CString PATH;
CTime tm;
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


// CNetWorkDlg 对话框



CNetWorkDlg::CNetWorkDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_NETWORK_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CNetWorkDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_edit1);
	DDX_Control(pDX, IDC_EDIT2, m_edit2);
	DDX_Control(pDX, IDC_EDIT3, m_edit3);
	DDX_Control(pDX, IDC_EDIT4, m_edit4);
	DDX_Control(pDX, IDC_EDIT5, m_edit5);
	DDX_Control(pDX, IDC_EDIT6, m_edit6);
	DDX_Control(pDX, IDC_STATIC_LOCAL, m_local);
	DDX_Control(pDX, IDC_STATIC_SERVER, m_server);
	DDX_Control(pDX, IDC_STATIC_SPEED, m_speed);
	DDX_Control(pDX, IDC_STATIC_PING, m_pingresult);
	DDX_Control(pDX, IDC_STATIC_SPEEDRESULT, m_speedresult);
	DDX_Control(pDX, IDC_STATIC_FINALRESULT, m_finalresult);
	DDX_Control(pDX, IDC_BUTTON1, m_start);
}

BEGIN_MESSAGE_MAP(CNetWorkDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CNetWorkDlg::OnBnClickedButton1)
	ON_WM_CTLCOLOR()
	ON_WM_WINDOWPOSCHANGING()
END_MESSAGE_MAP()


// CNetWorkDlg 消息处理程序

BOOL CNetWorkDlg::OnInitDialog()
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

	//设置字体
	font.DeleteObject();
	font.CreatePointFont(300, L"微软雅黑");
	m_edit4.SetFont(&font);
	m_edit5.SetFont(&font);
	m_edit6.SetFont(&font);

	m_font.DeleteObject();
	m_font.CreatePointFont(100, L"微软雅黑");
	m_local.SetFont(&m_font);
	m_server.SetFont(&m_font);
	m_speed.SetFont(&m_font);
	m_pingresult.SetFont(&m_font);
	m_speedresult.SetFont(&m_font);
	m_finalresult.SetFont(&m_font);
	m_start.SetFont(&m_font);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CNetWorkDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CNetWorkDlg::OnPaint()
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
HCURSOR CNetWorkDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
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

void CNetWorkDlg::OnRunExe(CString path, CString Param)
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

//获取文件行数
int CNetWorkDlg::GetFileLine(CString road)
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

CString CNetWorkDlg::ReadFileFirstLine(CString path)
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
		AfxMessageBox(L"2.文件不存在");
	}

}


void CNetWorkDlg::OnWriteFileLine(CString path, CString str)
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

HBRUSH CNetWorkDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	if (pWnd->GetDlgCtrlID() == IDC_EDIT4)//如果是静态编辑框
	{
		//pDC->SetTextColor(RGB(0, 0, 0));//修改字体的颜色
		//pDC->SetBkMode(TRANSPARENT);//把字体的背景变成透明的
		pDC->SetTextColor(EndResult_textColor4);
		pDC->SetBkColor(EndResult_backColor4);

		hbr = (HBRUSH)EndResult_backBrush4.GetSafeHandle();  //功能：适应static大小的背景颜色
		//return m_brush;//返回背景色
	}
	else if (pWnd->GetDlgCtrlID() == IDC_EDIT5)//如果是静态编辑框
	{
		//pDC->SetTextColor(RGB(0, 0, 0));//修改字体的颜色
		//pDC->SetBkMode(TRANSPARENT);//把字体的背景变成透明的
		pDC->SetTextColor(EndResult_textColor5);
		pDC->SetBkColor(EndResult_backColor5);

		hbr = (HBRUSH)EndResult_backBrush5.GetSafeHandle();  //功能：适应static大小的背景颜色
		//return m_brush;//返回背景色
	}
	else if (pWnd->GetDlgCtrlID() == IDC_EDIT6)//如果是静态编辑框
	{
		//pDC->SetTextColor(RGB(0, 0, 0));//修改字体的颜色
		//pDC->SetBkMode(TRANSPARENT);//把字体的背景变成透明的
		pDC->SetTextColor(EndResult_textColor6);
		pDC->SetBkColor(EndResult_backColor6);

		hbr = (HBRUSH)EndResult_backBrush6.GetSafeHandle();  //功能：适应static大小的背景颜色
		//return m_brush;//返回背景色
	}
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}

void CNetWorkDlg::DisplayResultIP(CString Result)
{
	if ((Result.Mid(0, 4)) == "pass")
	{
		m_edit4.SetWindowTextW(_T("Pass"));
		EndResult_textColor4 = RGB(0, 0, 0);
		EndResult_backColor4 = RGB(0, 255, 0);
	}
	else if (Result.Mid(0, 4) == "fail")
	{
		m_edit4.SetWindowTextW(_T("Fail"));
		EndResult_textColor4 = RGB(0, 0, 0);
		EndResult_backColor4 = RGB(255, 0, 0);
	}
	EndResult_backBrush4.DeleteObject();
	EndResult_backBrush4.CreateSolidBrush(EndResult_backColor4);		//创建画刷
	GetDlgItem(IDC_EDIT4)->Invalidate();
}
void CNetWorkDlg::DisplayResultSpeed(CString Result)
{
	if ((Result.Mid(0, 4)) == "pass")
	{
		m_edit5.SetWindowTextW(_T("Pass"));
		EndResult_textColor5 = RGB(0, 0, 0);
		EndResult_backColor5 = RGB(0, 255, 0);
	}
	else if (Result.Mid(0, 4) == "fail")
	{
		m_edit5.SetWindowTextW(_T("Fail"));
		EndResult_textColor5 = RGB(0, 0, 0);
		EndResult_backColor5 = RGB(255, 0, 0);
	}
	EndResult_backBrush5.DeleteObject();
	EndResult_backBrush5.CreateSolidBrush(EndResult_backColor5);		//创建画刷
	GetDlgItem(IDC_EDIT5)->Invalidate();
}
void CNetWorkDlg::DisplayResultFinal(CString Result)
{
	if ((Result.Mid(0, 4)) == "pass")
	{
		m_edit6.SetWindowTextW(_T("Pass"));
		EndResult_textColor6 = RGB(0, 0, 0);
		EndResult_backColor6 = RGB(0, 255, 0);
	}
	else if (Result.Mid(0, 4) == "fail")
	{
		m_edit6.SetWindowTextW(_T("Fail"));
		EndResult_textColor6 = RGB(0, 0, 0);
		EndResult_backColor6 = RGB(255, 0, 0);
	}
	EndResult_backBrush6.DeleteObject();
	EndResult_backBrush6.CreateSolidBrush(EndResult_backColor6);		//创建画刷
	GetDlgItem(IDC_EDIT6)->Invalidate();
}

void CNetWorkDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CString TM;
	tm = CTime::GetCurrentTime();
	TM = tm.Format("%Y%m%d");
	CString Network = _T("net\\");
	CString NetworkExe = _T("NetWorkTest.exe");
	CString NetworkPath = PATH + Network + NetworkExe;
	CString NetWorkTest = _T("NetWorkTest.ini");
	CString NetWorkTestPath = PATH + Network + NetWorkTest;
	CString NetWorkLog = _T("log\\");
	CString txt = _T(".txt");
	CString NetWorkLogPath = PATH + Network + NetWorkLog + TM + txt;
	DeleteFile(NetWorkLogPath);
	CString NetworkIP;
	CString Speed;
	GetPrivateProfileString(_T("Setting"), _T("IP"), CString("NULL"), NetworkIP.GetBuffer(MAX_PATH), MAX_PATH, NetWorkTestPath);
	GetPrivateProfileString(_T("Setting"), _T("Speed"), CString("NULL"), Speed.GetBuffer(MAX_PATH), MAX_PATH, NetWorkTestPath);
	NetworkIP.ReleaseBuffer();
	Speed.ReleaseBuffer();
	
	OnRunExe(NetworkPath, NULL);
	
	int line = GetFileLine(NetWorkLogPath);
	CStdioFile file;
	CString sp = L"Speed :";
	CString ip = L"ip ";
	CString logstr;
	CString logip, logip1, logresultip;
	int local_left, local_right;
	CString clientip;
	CString logspeed, logspeed1, logresultspeed;

	file.Open(NetWorkLogPath, CFile::modeRead);
	for (int i = 0; i < line; i++)
	{
		file.ReadString(logstr);
		if (logstr.Find(L"ip") > 0)
		{
			logip = logstr;
		}
		if (logstr.Find(L"Speed") > 0)
		{
			logspeed = logstr;
		}
	}
	file.Close();
	
	logip1 = logip.Left(logip.Find(ip));
	logresultip = logip.Right(logip.GetLength() - logip1.GetLength() - ip.GetLength());
	//提取本地地址
	local_left = logresultip.Find(L"<");
	local_right = logresultip.Find(L">");
	clientip = logresultip.Mid(local_left + 1, local_right - local_left - 1);
	
	logspeed1 = logspeed.Left(logspeed.Find(sp));
	logresultspeed = logspeed.Right(logspeed.GetLength() - logspeed1.GetLength() - sp.GetLength() - 1);


	m_edit1.SetWindowText(clientip);	//本地IP
	m_edit2.SetWindowText(NetworkIP);	//提取Server地址
	m_edit3.SetWindowText(logresultspeed);	//速度结果


	if (logip.Find(_T("success")) > 0)
	{
		DisplayResultIP(_T("pass"));
		if ((logspeed.Find(_T("not")) < 0) && (logresultspeed.GetLength() > 0))
		{
			DisplayResultSpeed(_T("pass"));
			Sleep(300);
			DisplayResultFinal(_T("pass"));
			result_flag = _T("T");
		}
		else if (logspeed.Find(_T("not")) > 0)
		{
			DisplayResultSpeed(_T("fail"));
			DisplayResultFinal(_T("fail"));
			result_flag = _T("F");
			//AfxMessageBox(_T("Speed 错误"));
		}
		else
		{
			DisplayResultSpeed(_T("fail"));
			DisplayResultFinal(_T("fail"));
			result_flag = _T("F");
			//AfxMessageBox(_T("日志异常：Speed行错误"));
		}
	}
	else if (logip.Find(_T("fail")) > 0)
	{
		DisplayResultIP(_T("fail"));
		DisplayResultSpeed(_T("fail"));
		DisplayResultFinal(_T("fail"));
		result_flag = _T("F");
		//AfxMessageBox(_T("Ping 失败"));
	}
	else
	{
		DisplayResultIP(_T("fail"));
		DisplayResultSpeed(_T("fail"));
		DisplayResultFinal(_T("fail"));
		result_flag = _T("F");
		//AfxMessageBox(_T("日志异常：IP行错误"));
	}

	CString AB;
	CFileFind finder;
	BOOL ifFind = finder.FindFile(AB_TXT);
	CString result = PATH + L"result.log";
	if (ifFind)
	{
		finder.Close();
		AB = ReadFileFirstLine(AB_TXT);  //read AB.txt
	}
	else
	{
		AB = L"M";
	}

	if (result_flag == "T")
	{
		OnWriteFileLine(result, L"pass\r\n");
		OnWriteFileLine(result, L"pass," + T + s + AB + s + NET + s + logresultip + s + _T("Speed:") + logresultspeed);
		//DisplayResultFinal(L"pass");
	}
	else
	{
		OnWriteFileLine(result, L"fail\r\n");
		OnWriteFileLine(result, L"fail," + DB1403 + s + AB + s + NET + s + logresultip + s + _T("Speed:") + logresultspeed + s + _T("fail"));
		//DisplayResultFinal(L"fail");
	}

	DeleteFile(NetWorkLogPath);
}

void CNetWorkDlg::AuToFunc()
{
	CString TM;
	tm = CTime::GetCurrentTime();
	TM = tm.Format("%Y%m%d");
	CString Network = _T("net\\");
	CString NetworkExe = _T("NetWorkTest.exe");
	CString NetworkPath = PATH + Network + NetworkExe;
	CString NetWorkTest = _T("NetWorkTest.ini");
	CString NetWorkTestPath = PATH + Network + NetWorkTest;
	CString NetWorkLog = _T("log\\");
	CString txt = _T(".txt");
	CString NetWorkLogPath = PATH + Network + NetWorkLog + TM + txt;
	DeleteFile(NetWorkLogPath);
	CString NetworkIP;
	CString Speed;
	GetPrivateProfileString(_T("Setting"), _T("IP"), CString("NULL"), NetworkIP.GetBuffer(MAX_PATH), MAX_PATH, NetWorkTestPath);
	GetPrivateProfileString(_T("Setting"), _T("Speed"), CString("NULL"), Speed.GetBuffer(MAX_PATH), MAX_PATH, NetWorkTestPath);
	NetworkIP.ReleaseBuffer();
	Speed.ReleaseBuffer();

	OnRunExe(NetworkPath, NULL);

	int line = GetFileLine(NetWorkLogPath);
	CStdioFile file;
	CString sp = L"Speed :";
	CString ip = L"ip ";
	CString logstr;
	CString logip, logip1, logresultip;
	int local_left, local_right;
	CString clientip;
	CString logspeed, logspeed1, logresultspeed;

	file.Open(NetWorkLogPath, CFile::modeRead);
	for (int i = 0; i < line; i++)
	{
		file.ReadString(logstr);
		if (logstr.Find(L"ip") > 0)
		{
			logip = logstr;
		}
		if (logstr.Find(L"Speed") > 0)
		{
			logspeed = logstr;
		}
	}
	file.Close();

	logip1 = logip.Left(logip.Find(ip));
	logresultip = logip.Right(logip.GetLength() - logip1.GetLength() - ip.GetLength());
	//提取本地地址
	local_left = logresultip.Find(L"<");
	local_right = logresultip.Find(L">");
	clientip = logresultip.Mid(local_left + 1, local_right - local_left - 1);

	logspeed1 = logspeed.Left(logspeed.Find(sp));
	logresultspeed = logspeed.Right(logspeed.GetLength() - logspeed1.GetLength() - sp.GetLength() - 1);


	m_edit1.SetWindowText(clientip);	//本地IP
	m_edit2.SetWindowText(NetworkIP);	//提取Server地址
	m_edit3.SetWindowText(logresultspeed);	//速度结果


	if (logip.Find(_T("success")) > 0)
	{
		DisplayResultIP(_T("pass"));
		if ((logspeed.Find(_T("not")) < 0) && (logresultspeed.GetLength() > 0))
		{
			DisplayResultSpeed(_T("pass"));
			Sleep(300);
			DisplayResultFinal(_T("pass"));
			result_flag = _T("T");
		}
		else if (logspeed.Find(_T("not")) > 0)
		{
			DisplayResultSpeed(_T("fail"));
			DisplayResultFinal(_T("fail"));
			result_flag = _T("F");
			//AfxMessageBox(_T("Speed 错误"));
		}
		else
		{
			DisplayResultSpeed(_T("fail"));
			DisplayResultFinal(_T("fail"));
			result_flag = _T("F");
			//AfxMessageBox(_T("日志异常：Speed行错误"));
		}
	}
	else if (logip.Find(_T("fail")) > 0)
	{
		DisplayResultIP(_T("fail"));
		DisplayResultSpeed(_T("fail"));
		DisplayResultFinal(_T("fail"));
		result_flag = _T("F");
		//AfxMessageBox(_T("Ping 失败"));
	}
	else
	{
		DisplayResultIP(_T("fail"));
		DisplayResultSpeed(_T("fail"));
		DisplayResultFinal(_T("fail"));
		result_flag = _T("F");
		//AfxMessageBox(_T("日志异常：IP行错误"));
	}

	CString AB;
	CFileFind finder;
	BOOL ifFind = finder.FindFile(AB_TXT);
	CString result = PATH + L"result.log";
	if (ifFind)
	{
		finder.Close();
		AB = ReadFileFirstLine(AB_TXT);  //read AB.txt
	}
	else
	{
		AB = L"M";
	}

	if (result_flag == "T")
	{
		OnWriteFileLine(result, L"pass\r\n");
		OnWriteFileLine(result, L"pass," + T + s + AB + s + NET + s + logresultip + s + _T("Speed:") + logresultspeed);
		//DisplayResultFinal(L"pass");
	}
	else
	{
		OnWriteFileLine(result, L"fail\r\n");
		OnWriteFileLine(result, L"fail," + DB1403 + s + AB + s + NET + s + logresultip + s + _T("Speed:") + logresultspeed + s + _T("fail"));
		//DisplayResultFinal(L"fail");
	}

	DeleteFile(NetWorkLogPath);
}

void CNetWorkDlg::OnWindowPosChanging(WINDOWPOS* lpwndpos)
{
	CString Config = L"Config.ini";
	CString config = PATH + Config;
	CString autotest;
	GetPrivateProfileString(_T("DisPlay"), _T("AUTOTESTYN"), CString("NULL"), autotest.GetBuffer(MAX_PATH), MAX_PATH, config);
	string at = (LPCSTR)(CStringA)(autotest);

	if (at == "Y")
	{
		SetWindowPos(&CWnd::wndNoTopMost, 0, 0, 0, 0, SWP_HIDEWINDOW);
		ModifyStyleEx(WS_EX_APPWINDOW, WS_EX_TOOLWINDOW);
		AuToFunc();
		exit(0);
	}
	CDialog::OnWindowPosChanging(lpwndpos);
}

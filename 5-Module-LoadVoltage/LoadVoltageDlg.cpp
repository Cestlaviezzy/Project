
// LoadVoltageDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "LoadVoltage.h"
#include "LoadVoltageDlg.h"
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


// CLoadVoltageDlg 对话框



CLoadVoltageDlg::CLoadVoltageDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LOADVOLTAGE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CLoadVoltageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CLoadVoltageDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CLoadVoltageDlg::OnBnClickedButton1)
	ON_WM_WINDOWPOSCHANGING()
END_MESSAGE_MAP()


// CLoadVoltageDlg 消息处理程序

BOOL CLoadVoltageDlg::OnInitDialog()
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

void CLoadVoltageDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CLoadVoltageDlg::OnPaint()
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
HCURSOR CLoadVoltageDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//获取文件行数
int CLoadVoltageDlg::GetFileLine(CString road)
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
CString CLoadVoltageDlg::ReadFileALL(CString path)
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
			//all_result.Replace(L" ", L"");
		}
		file.Close();
		return all_result;
	}
	else
	{
		file.Close();
	//	AfxMessageBox(L"all.文件不存在");
		return L"all.文件不存在";
	}
}

CString CLoadVoltageDlg::ReadFileFirstLine(CString path)
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
		//AfxMessageBox(L"2.文件不存在");
		return ResultNULL;
	}

}

void CLoadVoltageDlg::OnWriteFileLine(CString path, CString str)
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

void CLoadVoltageDlg::OnRunExe(CString path, CString Param)
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

void CLoadVoltageDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	//Config.ini配置文件
	CString ResultLog = _T("result.log");
	CString ResultPath = PATH + ResultLog;

	CString Config = _T("Config.ini");
	CString ConfigPath = PATH + Config;
	
	CString LV = _T("LV\\");
	CString ExeName = _T("PDTester.exe");
	CString PDTesterINI = _T("PDTester.ini");
	CString ExePath = PATH + LV + ExeName;
	CString PDTesteriniPath = PATH + LV + PDTesterINI;
	CString Log = _T("log\\");
	CString LogName = _T(".log");
	CString TM;
	tm = CTime::GetCurrentTime();
	TM = tm.Format("%Y%m%d");
	CString LogPath = PATH + LV + Log + TM + LogName;

	OnRunExe(ExePath,NULL);

	CString ResultTxt = _T("Result.txt");
	CString ResultTxtPath = PATH + LV + ResultTxt;
	CString Resulttxt = ReadFileFirstLine(ResultTxtPath);
	CString ResulttxtALL = ReadFileALL(ResultTxtPath);


	CString res = ReadFileALL(LogPath);
	CString value;
	int nCount = res.Replace(L"Electron Load Command", L"Electron Load Command");
	value.Format(L"%d", nCount);


	CStdioFile file,file1;
	CString arry[100];
	CString result;
	CString des[10];
	CString str[10];

	CString num;
	CString Value = _T("Value");
	CString Val;
	int line = GetFileLine(LogPath);

	if (file.Open(LogPath, CFile::modeRead))
	{
		for (int i = 1; i <= line; i++)
		{
			file.ReadString(arry[i]);
			result += arry[i] + L"\n";
			if (arry[i].Find(_T("Read PD VBus PASS")) > 0)
			{
				n = i;
				break;
			}
		}
		file.Close();
	}
	else
	{
		file.Close();
		AfxMessageBox(L"all.文件不存在");
	}

	CString AB;
	CFileFind finder;
	BOOL ifFind = finder.FindFile(AB_TXT);
	if (ifFind)
	{
		finder.Close();
		AB = ReadFileFirstLine(AB_TXT);  //read AB.txt
	}
	else
	{
		AB = L"M";
	}

	if (Resulttxt.Mid(0, 4) == (_T("PASS")))
	{
		OnWriteFileLine(ResultPath, pass + L"\n");
	}
	else if (Resulttxt.Mid(0, 4) == _T("FAIL"))
	{
		OnWriteFileLine(ResultPath, fail + L"\n");
		if (ResulttxtALL.Find(_T("Electron Load Command")) < 0)
		{
			OnWriteFileLine(ResultPath, fail + s + DH1102 + s + AB + s + Function + s + NoLoadVBus + not + s + LoadVBus + not + _T("\n"));
		}
	}
	else if (line < 5)
	{
		OnWriteFileLine(ResultPath, fail + L"\n");
		OnWriteFileLine(ResultPath, fail + s + DH1102 + s + AB + s + Function + s + ResultNULL);
	}
	else 
	{
		OnWriteFileLine(ResultPath, fail + L"\n");
		OnWriteFileLine(ResultPath, fail + s + DH1102 + s + AB + s + Function + s + ResultNULL);
	}

	int a, b;
	CString Get_VBus;
	CString Get_Current;
	CString No_Load_VBus;
	CString Load_VBus;
	for (int y = 0; y < nCount; y++)
	{
		num.Format(L"%d", y + 1);
		GetPrivateProfileString(_T("PORT1"), Value + num, CString("NULL"), Val.GetBuffer(MAX_PATH), MAX_PATH, PDTesteriniPath);
		Val.ReleaseBuffer();
		Get_VBus = Val.Left(Val.Find(_T(",")));
		Get_Current = Val.Right(Val.GetLength() - Get_VBus.GetLength() - 1);
		Get_Current = Get_Current.Left(Get_Current.Find(_T(",")));
		if (file1.Open(LogPath, CFile::modeRead))
		{
			for (int i = 1; i <= line; i++)
			{
				file1.ReadString(arry[i]);
				if (i == y * 7 + n)
				{
					a = arry[i].Find(L"[");
					b = arry[i].Find(L"]");
					des[y] = arry[i].Mid(a + 1, b - a - 1);

				}
				if (i == y * 7 + n + 2)
				{
					a = arry[i].Find(L"[");
					b = arry[i].Find(L"]");
					str[y] = arry[i].Mid(a + 1, b - a - 1);
				}
			}
			file1.Close();
		}
		else
		{
			file1.Close();
			AfxMessageBox(L"all.文件不存在");
		}

		if (Resulttxt.Mid(0,4) == _TEXT("PASS"))
		{
			OnWriteFileLine(ResultPath, pass + s + T + s + AB + s + Function  + s + NoLoadVBus + des[y] + s + LoadVBus + str[y] + _T("\n"));
		}
		else if (Resulttxt.Mid(0,4) == _TEXT("FAIL"))
		{
			OnWriteFileLine(ResultPath, fail + s + DH1102 + s + AB + s + Function + s + NoLoadVBus + des[y] + s + LoadVBus + str[y] + _T("\n"));
		}
		else
		{
			OnWriteFileLine(ResultPath, fail + s + DH1102 + s + AB + s + Function + s + ResultNULL + _T("\n"));
		}
		
	}

	DeleteFile(LogPath);
}

void CLoadVoltageDlg::AuToFunc()
{
	//Config.ini配置文件
	CString ResultLog = _T("result.log");
	CString ResultPath = PATH + ResultLog;

	CString Config = _T("Config.ini");
	CString ConfigPath = PATH + Config;

	CString LV = _T("LV\\");
	CString ExeName = _T("PDTester.exe");
	CString PDTesterINI = _T("PDTester.ini");
	CString ExePath = PATH + LV + ExeName;
	CString PDTesteriniPath = PATH + LV + PDTesterINI;
	CString Log = _T("log\\");
	CString LogName = _T(".log");
	CString TM;
	tm = CTime::GetCurrentTime();
	TM = tm.Format("%Y%m%d");
	CString LogPath = PATH + LV + Log + TM + LogName;

	OnRunExe(ExePath, NULL);

	CString ResultTxt = _T("Result.txt");
	CString ResultTxtPath = PATH + LV + ResultTxt;
	CString Resulttxt = ReadFileFirstLine(ResultTxtPath);
	CString ResulttxtALL = ReadFileALL(ResultTxtPath);


	CString res = ReadFileALL(LogPath);
	CString value;
	int nCount = res.Replace(L"Electron Load Command", L"Electron Load Command");
	value.Format(L"%d", nCount);


	CStdioFile file, file1;
	CString arry[100];
	CString result;
	CString des[10];
	CString str[10];

	CString num;
	CString Value = _T("Value");
	CString Val;
	int line = GetFileLine(LogPath);

	if (file.Open(LogPath, CFile::modeRead))
	{
		for (int i = 1; i <= line; i++)
		{
			file.ReadString(arry[i]);
			result += arry[i] + L"\n";
			if (arry[i].Find(_T("Read PD VBus PASS")) > 0)
			{
				n = i;
				break;
			}
		}
		file.Close();
	}
	else
	{
		file.Close();
		AfxMessageBox(L"all.文件不存在");
	}

	CString AB;
	CFileFind finder;
	BOOL ifFind = finder.FindFile(AB_TXT);
	if (ifFind)
	{
		finder.Close();
		AB = ReadFileFirstLine(AB_TXT);  //read AB.txt
	}
	else
	{
		AB = L"M";
	}

	if (Resulttxt.Mid(0, 4) == (_T("PASS")))
	{
		OnWriteFileLine(ResultPath, pass + L"\n");
	}
	else if (Resulttxt.Mid(0, 4) == _T("FAIL"))
	{
		OnWriteFileLine(ResultPath, fail + L"\n");
		if (ResulttxtALL.Find(_T("Electron Load Command")) < 0)
		{
			OnWriteFileLine(ResultPath, fail + s + DH1102 + s + AB + s + Function + s + NoLoadVBus + not + s + LoadVBus + not + _T("\n"));
		}
	}
	else if (line < 5)
	{
		OnWriteFileLine(ResultPath, fail + L"\n");
		OnWriteFileLine(ResultPath, fail + s + DH1102 + s + AB + s + Function + s + ResultNULL);
	}
	else
	{
		OnWriteFileLine(ResultPath, fail + L"\n");
		OnWriteFileLine(ResultPath, fail + s + DH1102 + s + AB + s + Function + s + ResultNULL);
	}

	int a, b;
	CString Get_VBus;
	CString Get_Current;
	CString No_Load_VBus;
	CString Load_VBus;
	for (int y = 0; y < nCount; y++)
	{
		num.Format(L"%d", y + 1);
		GetPrivateProfileString(_T("PORT1"), Value + num, CString("NULL"), Val.GetBuffer(MAX_PATH), MAX_PATH, PDTesteriniPath);
		Val.ReleaseBuffer();
		Get_VBus = Val.Left(Val.Find(_T(",")));
		Get_Current = Val.Right(Val.GetLength() - Get_VBus.GetLength() - 1);
		Get_Current = Get_Current.Left(Get_Current.Find(_T(",")));
		if (file1.Open(LogPath, CFile::modeRead))
		{
			for (int i = 1; i <= line; i++)
			{
				file1.ReadString(arry[i]);
				if (i == y * 7 + n)
				{
					a = arry[i].Find(L"[");
					b = arry[i].Find(L"]");
					des[y] = arry[i].Mid(a + 1, b - a - 1);

				}
				if (i == y * 7 + n + 2)
				{
					a = arry[i].Find(L"[");
					b = arry[i].Find(L"]");
					str[y] = arry[i].Mid(a + 1, b - a - 1);
				}
			}
			file1.Close();
		}
		else
		{
			file1.Close();
			AfxMessageBox(L"all.文件不存在");
		}

		if (Resulttxt.Mid(0, 4) == _TEXT("PASS"))
		{
			OnWriteFileLine(ResultPath, pass + s + T + s + AB + s + Function + s + NoLoadVBus + des[y] + s + LoadVBus + str[y] + _T("\n"));
		}
		else if (Resulttxt.Mid(0, 4) == _TEXT("FAIL"))
		{
			OnWriteFileLine(ResultPath, fail + s + DH1102 + s + AB + s + Function + s + NoLoadVBus + des[y] + s + LoadVBus + str[y] + _T("\n"));
		}
		else
		{
			OnWriteFileLine(ResultPath, fail + s + DH1102 + s + AB + s + Function + s + ResultNULL + _T("\n"));
		}

	}

	DeleteFile(LogPath);
}




void CLoadVoltageDlg::OnWindowPosChanging(WINDOWPOS* lpwndpos)
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

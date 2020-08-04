
// VideoDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "Video.h"
#include "VideoDlg.h"
#include "afxdialogex.h"
#include <string>

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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


// CVideoDlg 对话框



CVideoDlg::CVideoDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_VIDEO_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CVideoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CVideoDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CVideoDlg::OnBnClickedButton1)
	ON_WM_WINDOWPOSCHANGING()
END_MESSAGE_MAP()


// CVideoDlg 消息处理程序

BOOL CVideoDlg::OnInitDialog()
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
			//获取当前exe路径
	TCHAR path[MAX_PATH] = { 0 };
	GetModuleFileName(NULL, path, MAX_PATH);
	(_tcsrchr(path, _T('\\')))[1] = 0;
	PATH = path;//此时获得了EXE的目录

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CVideoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CVideoDlg::OnPaint()
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
HCURSOR CVideoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
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
	/////////////////////////////////////等待线程完成函数///////////////////////////////////////////
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
	////////////////////////////////////////////////////////////////////////////////////////////////////

}

void CVideoDlg::OnRunExe(CString path, CString Param)
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
	//WaitForSingleObject(ShExecInfo.hProcess, INFINITE);
	//if (ShExecInfo.hProcess != NULL)
	//{
	//	TerminateProcess(ShExecInfo.hProcess, 0);
	//	ShExecInfo.hProcess = NULL;
	//}
}


//获取文件行数
int CVideoDlg::GetFileLine(CString road)
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


CString CVideoDlg::ReadFileFirstLine(CString path)
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
		AfxMessageBox(L"USB没有获取到AB.TXT文件");
	}

}

void CVideoDlg::OnWriteFileLine(CString path, CString str)
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

void CVideoDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CString Result = _T("Result.txt");
	CString DHVT_R = _T("DHVT_R.ini");
	CString EXE = _T("DHVT_R.exe");
	CString path = PATH + _T("video-new\\") + Result;
	CString config = PATH + _T("video-new\\") + DHVT_R;
	CString exe_path = PATH + _T("video-new\\") + EXE;
	CStdioFile file;
	CString str,dst;
	CString arry[1024];
	CString port_DP, port_HDMI, port_VGA;
	CFileFind finder;
	BOOL ifFind = finder.FindFile(AB_TXT);

	CString PORT_NUMBER;
	CString HDMI, VGA, DP;
	CString hdmi, vga, dp;
	int m_index = 1;
	CString portnum;
	CString portnum_result;
	CString port_num;
	int p_n;
	OnRunExe(exe_path, NULL);

	for (int i = 0; i < 10; i++)
	{
		PORT_NUMBER.Format(_T("PORT%d"), m_index);
		GetPrivateProfileString(PORT_NUMBER, _T("ID"), CString("NULL"), portnum.GetBuffer(MAX_PATH), MAX_PATH, config);
		portnum.ReleaseBuffer();

		if (portnum==_T("NULL"))
		{
			p_n = m_index - 1;
			break;
		}
		m_index++;
	}
	portnum_result.Format(_T("%d"), p_n);
	int index = 1;
	CString PortResult;
	for (int j = 1; j <= p_n; j++)
	{
		port_num.Format(L"%d", j);
		PortResult.Format(_T("PORT%d"), index);
		GetPrivateProfileString(PortResult, _T("HDMI"), CString("NULL"), HDMI.GetBuffer(MAX_PATH), MAX_PATH, config);
		HDMI.ReleaseBuffer();
		GetPrivateProfileString(PortResult, _T("VGA"), CString("NULL"), VGA.GetBuffer(MAX_PATH), MAX_PATH, config);
		VGA.ReleaseBuffer();
		GetPrivateProfileString(PortResult, _T("DP"), CString("NULL"), DP.GetBuffer(MAX_PATH), MAX_PATH, config);
		DP.ReleaseBuffer();
		//HDMI
		if (HDMI.Find(_T("4K"))!=-1)
		{
			hdmi = _T("3840*2160");
		}
		else if (HDMI.Find(_T("2K"))!=-1)
		{
			hdmi = _T("1920*1080");
		}
		else
		{
			hdmi = _T("");
		}
		//VGA 只有2K
		if (VGA.Find(_T("2K"))!=-1)
		{
			vga = _T("1920*1080");
		}
		else
		{
			vga = _T("");
		}
		//DP
		if (DP.Find(_T("4K"))!=-1)
		{
			dp = _T("3840*2160");
		}
		else if (DP.Find(_T("2K"))!=-1)
		{
			dp = _T("1920*1080");
		}
		else
		{
			dp = _T("");
		}
		if (file.Open(path, CFile::modeRead))
		{
			for (int i = 0; i < 1 + 5 * j; i++)
			{
				file.ReadString(arry[i]);
				str += arry[i] + _T("\r\n");
				if (i == 2 + 5 * (j - 1))
				{
					port_DP = arry[i];

				}
				if (i == 3 + 5 * (j - 1))
				{
					port_HDMI = arry[i];

				}
				if (i == 4 + 5 * (j - 1))
				{
					port_VGA = arry[i];

				}
			}
			file.Close();
		}
		//MessageBox(port_DP + _T(",") + port_HDMI + _T(",") + port_VGA);
		//MessageBox(port_HDMI);
		//MessageBox(port_VGA);
		if (ifFind)
		{
			finder.Close();
			AB = ReadFileFirstLine(AB_TXT);  //read AB.txt
		}
		else
		{
			AB = L"NULL";
		}
		CString dest;
		dest = ReadFileFirstLine(path);
		int line;
		line = GetFileLine(path);
		if (line < 4)
		{
			OnWriteFileLine(PATH + L"result.log", FAIL + L"\n");
			FAIL.Empty();
			OnWriteFileLine(PATH + L"result.log", L"fail" + s + DB1500 + s + AB + s + p + port_num + L":" + L"" + L"" + L"");
		}
		else
		{
			if (dest.Find(L"FAIL") == -1)
			{
				OnWriteFileLine(PATH + L"result.log", PASS + L"\n");
				PASS.Empty();
				OnWriteFileLine(PATH + L"result.log", L"pass" + s + L"T" + s + AB + s + p + port_num + L":" + port_DP + left + dp + right + port_HDMI + left + hdmi + right + port_VGA + left + vga + right);
			}
			else
			{
				OnWriteFileLine(PATH + L"result.log", FAIL + L"\n");
				FAIL.Empty();
				if (port_DP.Find(L"Fail") == -1)
				{
					OnWriteFileLine(PATH + L"result.log", L"pass" + s + L"T" + s + AB + s + p + port_num + L":" + port_DP + left + dp + right + port_HDMI + left + hdmi + right + port_VGA + left + vga + right);
				}
				else
				{
					if (port_DP.Find(L"Pass") != -1)
					{
						port_DP = port_DP + left + dp + right;
					}
					if (port_HDMI.Find(L"Pass") != -1)
					{
						port_HDMI = port_HDMI + left + hdmi + right;
					}
					if (port_VGA.Find(L"Pass") != -1)
					{
						port_VGA = port_VGA + left + vga + right;
					}
					OnWriteFileLine(PATH + L"result.log", L"fail" + s + DB1500 + s + AB + s + p + port_num + L":" + port_DP + port_HDMI + port_VGA);
				}
			}
			index++;
		}
	}

}


void CVideoDlg::OnAuToFun()
{
	CString Result = _T("Result.txt");
	CString DHVT_R = _T("DHVT_R.ini");
	CString EXE = _T("DHVT_R.exe");
	CString path = PATH + _T("video-new\\") + Result;
	CString config = PATH + _T("video-new\\") + DHVT_R;
	CString exe_path = PATH + _T("video-new\\") + EXE;
	CStdioFile file;
	CString str, dst;
	CString arry[1024];
	CString port_DP, port_HDMI, port_VGA;
	CFileFind finder;
	BOOL ifFind = finder.FindFile(AB_TXT);

	CString PORT_NUMBER;
	CString HDMI, VGA, DP;
	CString hdmi, vga, dp;
	int m_index = 1;
	CString portnum;
	CString portnum_result;
	CString port_num;
	int p_n;
	OnRunExe(exe_path, NULL);

	for (int i = 0; i < 10; i++)
	{
		PORT_NUMBER.Format(_T("PORT%d"), m_index);
		GetPrivateProfileString(PORT_NUMBER, _T("ID"), CString("NULL"), portnum.GetBuffer(MAX_PATH), MAX_PATH, config);
		portnum.ReleaseBuffer();

		if (portnum == _T("NULL"))
		{
			p_n = m_index - 1;
			break;
		}
		m_index++;
	}
	portnum_result.Format(_T("%d"), p_n);
	int index = 1;
	CString PortResult;
	for (int j = 1; j <= p_n; j++)
	{
		port_num.Format(L"%d", j);
		PortResult.Format(_T("PORT%d"), index);
		GetPrivateProfileString(PortResult, _T("HDMI"), CString("NULL"), HDMI.GetBuffer(MAX_PATH), MAX_PATH, config);
		HDMI.ReleaseBuffer();
		GetPrivateProfileString(PortResult, _T("VGA"), CString("NULL"), VGA.GetBuffer(MAX_PATH), MAX_PATH, config);
		VGA.ReleaseBuffer();
		GetPrivateProfileString(PortResult, _T("DP"), CString("NULL"), DP.GetBuffer(MAX_PATH), MAX_PATH, config);
		DP.ReleaseBuffer();
		//HDMI
		if (HDMI.Find(_T("4K")) != -1)
		{
			hdmi = _T("3840*2160");
		}
		else if (HDMI.Find(_T("2K")) != -1)
		{
			hdmi = _T("1920*1080");
		}
		else
		{
			hdmi = _T("");
		}
		//VGA 只有2K
		if (VGA.Find(_T("2K")) != -1)
		{
			vga = _T("1920*1080");
		}
		else
		{
			vga = _T("");
		}
		//DP
		if (DP.Find(_T("4K")) != -1)
		{
			dp = _T("3840*2160");
		}
		else if (DP.Find(_T("2K")) != -1)
		{
			dp = _T("1920*1080");
		}
		else
		{
			dp = _T("");
		}
		if (file.Open(path, CFile::modeRead))
		{
			for (int i = 0; i < 1 + 5 * j; i++)
			{
				file.ReadString(arry[i]);
				str += arry[i] + _T("\r\n");
				if (i == 2 + 5 * (j - 1))
				{
					port_DP = arry[i];

				}
				if (i == 3 + 5 * (j - 1))
				{
					port_HDMI = arry[i];

				}
				if (i == 4 + 5 * (j - 1))
				{
					port_VGA = arry[i];

				}
			}
			file.Close();
		}
		//MessageBox(port_DP + _T(",") + port_HDMI + _T(",") + port_VGA);
		//MessageBox(port_HDMI);
		//MessageBox(port_VGA);
		if (ifFind)
		{
			finder.Close();
			AB = ReadFileFirstLine(AB_TXT);  //read AB.txt
		}
		else
		{
			AB = L"NULL";
		}
		CString dest;
		dest = ReadFileFirstLine(path);
		int line;
		line = GetFileLine(path);
		if (line < 4)
		{
			OnWriteFileLine(PATH + L"result.log", FAIL + L"\n");
			FAIL.Empty();
			OnWriteFileLine(PATH + L"result.log", L"fail" + s + DB1500 + s + AB + s + p + port_num + L":" + L"" + L"" + L"");
		}
		else
		{
			if (dest.Find(L"FAIL") == -1)
			{
				OnWriteFileLine(PATH + L"result.log", PASS + L"\n");
				PASS.Empty();
				OnWriteFileLine(PATH + L"result.log", L"pass" + s + L"T" + s + AB + s + p + port_num + L":" + port_DP + left + dp + right + port_HDMI + left + hdmi + right + port_VGA + left + vga + right);
			}
			else
			{
				OnWriteFileLine(PATH + L"result.log", FAIL + L"\n");
				FAIL.Empty();
				if (port_DP.Find(L"Fail") == -1)
				{
					OnWriteFileLine(PATH + L"result.log", L"pass" + s + L"T" + s + AB + s + p + port_num + L":" + port_DP + left + dp + right + port_HDMI + left + hdmi + right + port_VGA + left + vga + right);
				}
				else
				{
					if (port_DP.Find(L"Pass") != -1)
					{
						port_DP = port_DP + left + dp + right;
					}
					if (port_HDMI.Find(L"Pass") != -1)
					{
						port_HDMI = port_HDMI + left + hdmi + right;
					}
					if (port_VGA.Find(L"Pass") != -1)
					{
						port_VGA = port_VGA + left + vga + right;
					}
					OnWriteFileLine(PATH + L"result.log", L"fail" + s + DB1500 + s + AB + s + p + port_num + L":" + port_DP + port_HDMI + port_VGA);
				}
			}
			index++;
		}
	}
}

void CVideoDlg::OnWindowPosChanging(WINDOWPOS* lpwndpos)
{
	CString autotest;
	CString Config = _T("VideoConfig.ini");
	CString config = PATH + Config;
	GetPrivateProfileString(_T("AUTO"), _T("AUTOTESTYN"), CString("NULL"), autotest.GetBuffer(MAX_PATH), MAX_PATH, config);
	string at = (LPCSTR)(CStringA)(autotest);

	if (at == "Y")
	{
		SetWindowPos(&CWnd::wndNoTopMost, 0, 0, 0, 0, SWP_HIDEWINDOW);
		ModifyStyleEx(WS_EX_APPWINDOW, WS_EX_TOOLWINDOW);
		OnAuToFun();
		exit(0);
	}
	CDialogEx::OnWindowPosChanging(lpwndpos);
}

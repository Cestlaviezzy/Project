
// USBTypeC-ModuleDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "USBTypeC-Module.h"
#include "USBTypeC-ModuleDlg.h"
#include "afxdialogex.h"
#include <string>

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CString PATH;
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


// CUSBTypeCModuleDlg 对话框



CUSBTypeCModuleDlg::CUSBTypeCModuleDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_USBTYPECMODULE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CUSBTypeCModuleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CUSBTypeCModuleDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CUSBTypeCModuleDlg::OnBnClickedButton1)
	ON_WM_WINDOWPOSCHANGING()
END_MESSAGE_MAP()


// CUSBTypeCModuleDlg 消息处理程序

BOOL CUSBTypeCModuleDlg::OnInitDialog()
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

void CUSBTypeCModuleDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CUSBTypeCModuleDlg::OnPaint()
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
HCURSOR CUSBTypeCModuleDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

CString CUSBTypeCModuleDlg::ReadFirstLine(CString path)
{
	CStdioFile file;
	CString result;
	if (file.Open(path, CFile::modeRead))
	{
		file.ReadString(result);
		file.Close();
		return result;
	}
	else
	{
		return ResultNULL;
	}
}

void CUSBTypeCModuleDlg::OnWriteFileLine(CString path, CString str)
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


//获取文件行数
int CUSBTypeCModuleDlg::GetFileLine(CString road)
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
CString CUSBTypeCModuleDlg::ReadFileALL(CString path)
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
		AfxMessageBox(L"all.文件不存在");
	}
}

CString CUSBTypeCModuleDlg::ReadLastLine(CString path)
{
	CStdioFile file;
	CString result;
	int line = GetFileLine(path);
	if (file.Open(path, CFile::modeRead))
	{
		for (int i = 1; i < line; i++)
		{
			file.ReadString(result);
		}
		file.Close();
		return result;
	}
	else
	{
		file.Close();
		return ResultNULL;
	}
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

void CUSBTypeCModuleDlg::OnRunExe(CString path, CString Param)
{
	SHELLEXECUTEINFO ShExecInfo = { 0 };
	ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
	ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
	ShExecInfo.hwnd = NULL;
	ShExecInfo.lpVerb = NULL;
	ShExecInfo.lpFile = path;
	ShExecInfo.lpParameters = Param;
	ShExecInfo.lpDirectory = NULL;
	ShExecInfo.nShow - SW_HIDE;
	ShExecInfo.hInstApp = NULL;
	ShellExecuteEx(&ShExecInfo);
	TheadWait(ShExecInfo.hProcess);
}

void CUSBTypeCModuleDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CString TypeC = _TEXT("TypeC\\");
	CString TypeCTester = _TEXT("TypeCTester_1605.ini");
	CString TypeC_Path = PATH + TypeC + TypeCTester;
	CString TypeC_EXE = _TEXT("TypeCTester_1605.exe");
	CString TypeC_EXE_Path = PATH + TypeC + TypeC_EXE;
	CString More_Detail_Result = _TEXT("More_Detail_Result.txt");
	CString More_Detail_Result_Path = PATH + TypeC + More_Detail_Result;
	DeleteFile(More_Detail_Result_Path);
	CString edit_number;	//port个数
	int edit_num = 1;
	CString PORT = _TEXT("PORT");
	CString pNum;
	CString PortDate;
	CString result1, result2, result3, result4, result5;
	CString FileData;
	int pos;

	//获取 TypeCTester_1605.ini 里面PORTS数据
	GetPrivateProfileString(_T("TestSetting"), _T("Edit_Numbers"), CString("1"), edit_number.GetBuffer(MAX_PATH), MAX_PATH, TypeC_Path);
	edit_number.ReleaseBuffer();
	edit_num = _ttoi(edit_number);
	for (int i = 1; i <= edit_num; i++)
	{
		pNum.Format(_TEXT("%d"), i);

		GetPrivateProfileString(_T("PORTS"), PORT + pNum, CString("NULL"), PortDate.GetBuffer(MAX_PATH), MAX_PATH, TypeC_Path);
		PortDate.ReleaseBuffer();

		result1 = PortDate.Left(PortDate.Find(_T(",")));			//第一个逗号数据
		result2 = PortDate.Right(PortDate.GetLength() - result1.GetLength() - 1);
		result2 = result2.Left(result2.Find(_T(",")));				//第二个逗号数据
		result3 = PortDate.Right(PortDate.GetLength() - result1.GetLength() - result2.GetLength() - 2);
		result3 = result3.Left(result3.Find(_T(",")));				//第三个逗号数据
		result4 = PortDate.Right(PortDate.GetLength() - result1.GetLength() - result2.GetLength() - result3.GetLength() - 3);
		result4 = result4.Left(result4.Find(_T(",")));				//第四个逗号数据
		result5 = PortDate.Right(PortDate.GetLength() - result1.GetLength() - result2.GetLength() - result3.GetLength() -result4.GetLength() - 4);
		result5 = result5.Left(result5.Find(_T(",")));				//第五个逗号数据

	}
	OnRunExe(TypeC_EXE_Path, NULL);

	//读取 More_Detail_Result.txt 测试结果数据
	CString portNum;
	CString portCount;
	CString resNull;
	CStdioFile file;
	CString res[100], rn[100], sn[100];
	int line = GetFileLine(More_Detail_Result_Path);
	FileData = ReadFileALL(More_Detail_Result_Path);


		//获取正反面文件
	if (ifFindtxt)
	{
		finderTXT.Close();
		AB = ReadFirstLine(AB_TXT);  //read AB.txt
	}
	else
	{
		AB = L"M";
	}

	//获取Type-C 结果
	CString TypeC_Result = ReadLastLine(More_Detail_Result_Path);
	TypeC_Result = TypeC_Result.Right(4);
	CString strNull;
	CString strP = L"P";
	CString strX;

	if (TypeC_Result == _TEXT("PASS"))
	{
		OnWriteFileLine(PATH + L"result.log", PASS + L"\n");
		OnWriteFileLine(PATH + L"result.log", PASS + s + L"T" + s + AB + s + strP + L"1" + s);
	}
	else if (TypeC_Result == _TEXT("FAIL"))
	{
		OnWriteFileLine(PATH + L"result.log", FAIL + L"\n");
		OnWriteFileLine(PATH + L"result.log", FAIL + s + DB1300 + s + AB + s + strP + L"1" + s);
	}
	else
	{
		OnWriteFileLine(PATH + L"result.log", FAIL + L"\n");
		OnWriteFileLine(PATH + L"result.log", FAIL + s + DB1300 + s + AB + s);
	}


	if (file.Open(More_Detail_Result_Path, CFile::modeRead))
	{
		for (int i = 1; i < line; i++)
		{
			if (edit_num >= 2)
			{
				file.ReadString(res[i]);
				res[i].MakeLower();
				rn[i] = res[i].Left(res[i].Find(_T(" ")));
				sn[i] = res[i].Right(res[i].GetLength() - rn[i].GetLength() - 1);

				if (TypeC_Result == _TEXT("PASS"))
				{
					if (i == line / edit_num)
					{
						for (int x = 2; x <= edit_num; x++)
						{
							strX.Format(L"%d", x);
							strNull = L"\n";
							OnWriteFileLine(PATH + L"result.log", strNull + L"pass" + s + L"T" + s + AB + s + strP + strX + sn[i] + s);
							strNull.Empty();
						}
					}
					else
					{
						OnWriteFileLine(PATH + L"result.log", sn[i] + s);
					}
				}
				else if (TypeC_Result == _TEXT("FAIL"))
				{
					if (i == line / edit_num)
					{
						for (int x = 2; x <= edit_num; x++)
						{
							strX.Format(L"%d", x);
							strNull = L"\n";
							OnWriteFileLine(PATH + L"result.log", strNull + L"fail" + s + DB1300 + s + AB + s + strP + strX + sn[i] + s);
							strNull.Empty();
						}
					}
					else
					{
						OnWriteFileLine(PATH + L"result.log", sn[i] + s);
					}
					
				}
				else
				{
					OnWriteFileLine(PATH + L"result.log", ResultNULL);
				}
			}
			else
			{
				file.ReadString(res[i]);
				res[i].MakeLower();
				rn[i] = res[i].Left(res[i].Find(_T(" ")));
				sn[i] = res[i].Right(res[i].GetLength() - rn[i].GetLength() - 1);
				if (TypeC_Result == _TEXT("PASS"))
				{
					OnWriteFileLine(PATH + L"result.log", sn[i] + s);
				}
				else if (TypeC_Result == _TEXT("FAIL"))
				{
					OnWriteFileLine(PATH + L"result.log", sn[i] + s);
				}
				else
				{
					OnWriteFileLine(PATH + L"result.log", ResultNULL);
				}
			}

		}
		file.Close();
	}
	else
	{
		ResultNULL = _TEXT("could not found More_Detail_Result.txt");
	}

}


void CUSBTypeCModuleDlg::OnAuToFunc()
{
	CString TypeC = _TEXT("TypeC\\");
	CString TypeCTester = _TEXT("TypeCTester_1605.ini");
	CString TypeC_Path = PATH + TypeC + TypeCTester;
	CString TypeC_EXE = _TEXT("TypeCTester_1605.exe");
	CString TypeC_EXE_Path = PATH + TypeC + TypeC_EXE;
	CString More_Detail_Result = _TEXT("More_Detail_Result.txt");
	CString More_Detail_Result_Path = PATH + TypeC + More_Detail_Result;
	DeleteFile(More_Detail_Result_Path);
	CString edit_number;	//port个数
	int edit_num = 1;
	CString PORT = _TEXT("PORT");
	CString pNum;
	CString PortDate;
	CString result1, result2, result3, result4, result5;
	CString FileData;
	int pos;

	//获取 TypeCTester_1605.ini 里面PORTS数据
	GetPrivateProfileString(_T("TestSetting"), _T("Edit_Numbers"), CString("1"), edit_number.GetBuffer(MAX_PATH), MAX_PATH, TypeC_Path);
	edit_number.ReleaseBuffer();
	edit_num = _ttoi(edit_number);
	for (int i = 1; i <= edit_num; i++)
	{
		pNum.Format(_TEXT("%d"), i);

		GetPrivateProfileString(_T("PORTS"), PORT + pNum, CString("NULL"), PortDate.GetBuffer(MAX_PATH), MAX_PATH, TypeC_Path);
		PortDate.ReleaseBuffer();

		result1 = PortDate.Left(PortDate.Find(_T(",")));			//第一个逗号数据
		result2 = PortDate.Right(PortDate.GetLength() - result1.GetLength() - 1);
		result2 = result2.Left(result2.Find(_T(",")));				//第二个逗号数据
		result3 = PortDate.Right(PortDate.GetLength() - result1.GetLength() - result2.GetLength() - 2);
		result3 = result3.Left(result3.Find(_T(",")));				//第三个逗号数据
		result4 = PortDate.Right(PortDate.GetLength() - result1.GetLength() - result2.GetLength() - result3.GetLength() - 3);
		result4 = result4.Left(result4.Find(_T(",")));				//第四个逗号数据
		result5 = PortDate.Right(PortDate.GetLength() - result1.GetLength() - result2.GetLength() - result3.GetLength() - result4.GetLength() - 4);
		result5 = result5.Left(result5.Find(_T(",")));				//第五个逗号数据

	}
	OnRunExe(TypeC_EXE_Path, NULL);

	//读取 More_Detail_Result.txt 测试结果数据
	CString portNum;
	CString portCount;
	CString resNull;
	CStdioFile file;
	CString res[100], rn[100], sn[100];
	int line = GetFileLine(More_Detail_Result_Path);
	FileData = ReadFileALL(More_Detail_Result_Path);


	//获取正反面文件
	if (ifFindtxt)
	{
		finderTXT.Close();
		AB = ReadFirstLine(AB_TXT);  //read AB.txt
	}
	else
	{
		AB = L"M";
	}

	//获取Type-C 结果
	CString TypeC_Result = ReadLastLine(More_Detail_Result_Path);
	TypeC_Result = TypeC_Result.Right(4);
	CString strNull;
	CString strP = L"P";
	CString strX;

	if (TypeC_Result == _TEXT("PASS"))
	{
		OnWriteFileLine(PATH + L"result.log", PASS + L"\n");
		OnWriteFileLine(PATH + L"result.log", PASS + s + L"T" + s + AB + s + strP + L"1" + s);
	}
	else if (TypeC_Result == _TEXT("FAIL"))
	{
		OnWriteFileLine(PATH + L"result.log", FAIL + L"\n");
		OnWriteFileLine(PATH + L"result.log", FAIL + s + DB1300 + s + AB + s + strP + L"1" + s);
	}
	else
	{
		OnWriteFileLine(PATH + L"result.log", FAIL + L"\n");
		OnWriteFileLine(PATH + L"result.log", FAIL + s + DB1300 + s + AB + s);
	}


	if (file.Open(More_Detail_Result_Path, CFile::modeRead))
	{
		for (int i = 1; i < line; i++)
		{
			if (edit_num >= 2)
			{
				file.ReadString(res[i]);
				res[i].MakeLower();
				rn[i] = res[i].Left(res[i].Find(_T(" ")));
				sn[i] = res[i].Right(res[i].GetLength() - rn[i].GetLength() - 1);

				if (TypeC_Result == _TEXT("PASS"))
				{
					if (i == line / edit_num)
					{
						for (int x = 2; x <= edit_num; x++)
						{
							strX.Format(L"%d", x);
							strNull = L"\n";
							OnWriteFileLine(PATH + L"result.log", strNull + L"pass" + s + L"T" + s + AB + s + strP + strX + sn[i] + s);
							strNull.Empty();
						}
					}
					else
					{
						OnWriteFileLine(PATH + L"result.log", sn[i] + s);
					}
				}
				else if (TypeC_Result == _TEXT("FAIL"))
				{
					if (i == line / edit_num)
					{
						for (int x = 2; x <= edit_num; x++)
						{
							strX.Format(L"%d", x);
							strNull = L"\n";
							OnWriteFileLine(PATH + L"result.log", strNull + L"fail" + s + DB1300 + s + AB + s + strP + strX + sn[i] + s);
							strNull.Empty();
						}
					}
					else
					{
						OnWriteFileLine(PATH + L"result.log", sn[i] + s);
					}

				}
				else
				{
					OnWriteFileLine(PATH + L"result.log", ResultNULL);
				}
			}
			else
			{
				file.ReadString(res[i]);
				res[i].MakeLower();
				rn[i] = res[i].Left(res[i].Find(_T(" ")));
				sn[i] = res[i].Right(res[i].GetLength() - rn[i].GetLength() - 1);
				if (TypeC_Result == _TEXT("PASS"))
				{
					OnWriteFileLine(PATH + L"result.log", sn[i] + s);
				}
				else if (TypeC_Result == _TEXT("FAIL"))
				{
					OnWriteFileLine(PATH + L"result.log", sn[i] + s);
				}
				else
				{
					OnWriteFileLine(PATH + L"result.log", ResultNULL);
				}
			}

		}
		file.Close();
	}
	else
	{
		ResultNULL = _TEXT("could not found More_Detail_Result.txt");
	}

}


void CUSBTypeCModuleDlg::OnWindowPosChanging(WINDOWPOS* lpwndpos)
{
	CString TypeCConfig = L"TypeCConfig.ini";
	CString config = PATH + TypeCConfig;
	CString autotest;


	GetPrivateProfileString(_T("AUTO"), _T("AUTOTESTYN"), CString("NULL"), autotest.GetBuffer(MAX_PATH), MAX_PATH, config);
	string at = (LPCSTR)(CStringA)(autotest);

	if (at == "Y")
	{
		SetWindowPos(&CWnd::wndNoTopMost, 0, 0, 0, 0, SWP_HIDEWINDOW);
		ModifyStyleEx(WS_EX_APPWINDOW, WS_EX_TOOLWINDOW);
		OnAuToFunc();
		exit(0);
	}

	CDialog::OnWindowPosChanging(lpwndpos);
}

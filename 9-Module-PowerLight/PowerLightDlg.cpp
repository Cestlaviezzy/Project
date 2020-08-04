
// PowerLightDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "PowerLight.h"
#include "PowerLightDlg.h"
#include "afxdialogex.h"

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


// CPowerLightDlg 对话框



CPowerLightDlg::CPowerLightDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_POWERLIGHT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPowerLightDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_POWER, m_static_powerlight);
	DDX_Control(pDX, IDC_BUTTON1, m_buttonYES);
	DDX_Control(pDX, IDC_BUTTON2, m_buttonNO);
}

BEGIN_MESSAGE_MAP(CPowerLightDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CPowerLightDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CPowerLightDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CPowerLightDlg 消息处理程序

BOOL CPowerLightDlg::OnInitDialog()
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
	font.CreatePointFont(200, L"微软雅黑");
	m_static_powerlight.SetFont(&font);
	m_buttonYES.SetFont(&font);
	m_buttonNO.SetFont(&font);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CPowerLightDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	CString result = _T("result.log");
	CString ResultPath = PATH + result;
	// TODO: 在此添加控件通知处理程序代码
	CFileFind finder;
	BOOL ifFind = finder.FindFile(AB_TXT);
	CString AB;
	if (ifFind)
	{
		finder.Close();
		AB = ReadFileFirstLine(AB_TXT);  //read AB.txt
	}
	else
	{
		AB = L"M";
	}

	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else if ((nID & 0xFFF0) == SC_CLOSE)		//右上角X  加入自己的代码*****************************
	{
		OnWriteFileLine(ResultPath, L"fail\r\n");
		OnWriteFileLine(ResultPath, L"fail," + DH1501 + s + AB + s + Function + s + _T("NO"));
		exit(0);
	}

	CDialogEx::OnSysCommand(nID, lParam);
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CPowerLightDlg::OnPaint()
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
HCURSOR CPowerLightDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CPowerLightDlg::OnWriteFileLine(CString path, CString str)
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

CString CPowerLightDlg::ReadFileFirstLine(CString path)
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

void CPowerLightDlg::OnBnClickedButton1()
{
	CString result = _T("result.log");
	CString ResultPath = PATH + result;
	// TODO: 在此添加控件通知处理程序代码
	CFileFind finder;
	BOOL ifFind = finder.FindFile(AB_TXT);
	CString AB;
	if (ifFind)
	{
		finder.Close();
		AB = ReadFileFirstLine(AB_TXT);  //read AB.txt
	}
	else
	{
		AB = L"M";
	}

	OnWriteFileLine(ResultPath, L"pass\r\n");
	OnWriteFileLine(ResultPath, L"pass," + T + s + AB + s + Function + s + _T("YES"));
	CPowerLightDlg::OnOK();
}


void CPowerLightDlg::OnBnClickedButton2()
{
	CString result = _T("result.log");
	CString ResultPath = PATH + result;
	// TODO: 在此添加控件通知处理程序代码
	CFileFind finder;
	BOOL ifFind = finder.FindFile(AB_TXT);
	CString AB;
	if (ifFind)
	{
		finder.Close();
		AB = ReadFileFirstLine(AB_TXT);  //read AB.txt
	}
	else
	{
		AB = L"M";
	}

	OnWriteFileLine(ResultPath, L"fail\r\n");
	OnWriteFileLine(ResultPath, L"fail," + DH1501 + s + AB + s + Function + s + _T("NO"));
	CPowerLightDlg::OnOK();
}


BOOL CPowerLightDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (pMsg->message == WM_KEYDOWN)
	{
		switch (pMsg->wParam)
		{
		//case VK_RETURN:     //屏蔽回车  
		case VK_ESCAPE:     //屏蔽ESC  
			return true;
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}

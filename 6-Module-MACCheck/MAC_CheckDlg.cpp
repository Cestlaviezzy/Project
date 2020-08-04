
// MAC_CheckDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MAC_Check.h"
#include "MAC_CheckDlg.h"
#include "afxdialogex.h"
#include <string>

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CString PATH;
CString TM,TM1; //获取系统时间 　　
CTime tm,tm1;
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


// CMACCheckDlg 对话框



CMACCheckDlg::CMACCheckDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MAC_CHECK_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMACCheckDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT2, m_edit2);
	DDX_Control(pDX, IDC_EDIT1, m_edit1);
	DDX_Control(pDX, IDC_STATIC_LOCALMAC, m_static_localmac);
	DDX_Control(pDX, IDC_STATIC_MACADDR, m_static_macaddr);
	DDX_Control(pDX, IDC_STATIC_MAC, m_static_mac);
	DDX_Control(pDX, IDC_STATIC_NUM, m_static_num);
	DDX_Control(pDX, IDC_STATIC_PCB, m_static_pcb);
	DDX_Control(pDX, IDC_STATIC_RESULT, m_static_result);
	DDX_Control(pDX, IDC_EDIT3, m_edit3);
	DDX_Control(pDX, IDC_EDIT4, m_edit4);
	DDX_Control(pDX, IDC_EDIT5, m_edit5);
	DDX_Control(pDX, IDC_STATIC_SN, m_static_sn);
	DDX_Control(pDX, IDC_EDIT6, m_edit6);
	DDX_Control(pDX, IDC_STATIC_QR, m_static_qr);
	DDX_Control(pDX, IDC_BUTTON1, m_button);
}

BEGIN_MESSAGE_MAP(CMACCheckDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMACCheckDlg::OnBnClickedButton1)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CMACCheckDlg 消息处理程序

BOOL CMACCheckDlg::OnInitDialog()
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



	tm1 = CTime::GetCurrentTime();
	TM1 = tm1.Format("TIME:%Y-%m-%d-%X");
	FILE *f1 = NULL;
	if (_tfopen_s(&f1, PATH + MACdata, _T("a+b")) == 0)		//w write  b bin
	{
		CStringArray sLine;
		sLine.Add(L"测试次数");						//测试次数
		sLine.Add(L"工单");							//工单
		sLine.Add(L"PCB板号");						//PCB
		sLine.Add(L"扫码MAC");						//扫码MAC
		sLine.Add(L"设备MAC");						//设备MAC
		sLine.Add(L"设备路径");						//设备路径
		sLine.Add(L"SN安规码");						//SN
		sLine.Add(L"校验结果");						//结果PASS or FAIL
		sLine.Add(L"时间");							//时间

		PutCSVItemLine(f1, sLine);
		fclose(f1);
	}

	m_font_result.DeleteObject();
	m_font_result.CreatePointFont(300, L"微软雅黑");//代表15号字体，华文行楷
	m_edit1.SetFont(&m_font_result);


	m_font.DeleteObject();
	m_font.CreatePointFont(150, L"微软雅黑");//代表15号字体，华文行楷
	m_static_localmac.SetFont(&m_font);

	m1_font.DeleteObject();
	m1_font.CreatePointFont(100, L"微软雅黑");//代表15号字体，华文行楷
	m_static_macaddr.SetFont(&m1_font);

	m2_font.DeleteObject();
	m2_font.CreatePointFont(100, L"微软雅黑");//代表15号字体，华文行楷
	m_static_mac.SetFont(&m2_font);
	m_static_num.SetFont(&m2_font);
	m_static_pcb.SetFont(&m2_font);
	m_static_sn.SetFont(&m2_font);
	m_static_qr.SetFont(&m2_font);

	m_button_font.DeleteObject();
	m_button_font.CreatePointFont(200, L"微软雅黑");//代表15号字体，华文行楷
	m_button.SetFont(&m_button_font);

	GetDlgItem(IDC_EDIT3)->SetFocus();

	return FALSE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMACCheckDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMACCheckDlg::OnPaint()
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
HCURSOR CMACCheckDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//获取文件行数
int CMACCheckDlg::GetFileLine(CString road)
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

void CMACCheckDlg::CharToUTF8(CString &str)
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

void CMACCheckDlg::OnRunExe(CString path, CString Param, CString DestPath)
{
	SHELLEXECUTEINFO ShExecInfo = { 0 };
	ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
	ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
	ShExecInfo.hwnd = NULL;
	ShExecInfo.lpVerb = NULL;
	ShExecInfo.lpFile = path;
	ShExecInfo.lpParameters = Param;
	ShExecInfo.lpDirectory = DestPath;
	ShExecInfo.nShow - SW_HIDE;
	ShExecInfo.hInstApp = NULL;
	ShellExecuteEx(&ShExecInfo);
	TheadWait(ShExecInfo.hProcess);
}

HBRUSH CMACCheckDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	if (pWnd->GetDlgCtrlID() == IDC_EDIT1)//如果是静态编辑框
	{
		//pDC->SetTextColor(RGB(0, 0, 0));//修改字体的颜色
		//pDC->SetBkMode(TRANSPARENT);//把字体的背景变成透明的
		pDC->SetTextColor(EndResult_textColor);
		pDC->SetBkColor(EndResult_backColor);

		hbr = (HBRUSH)EndResult_backBrush.GetSafeHandle();  //功能：适应static大小的背景颜色
		//return m_brush;//返回背景色
	}
	if (pWnd->GetDlgCtrlID() == IDC_STATIC_LOCALMAC)
	{
		pDC->SetTextColor(RGB(238, 130, 238));
	}
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}

void CMACCheckDlg::DisplayResult(CString Result)
{
	if ((Result.Mid(0, 4)) == "pass")
	{
		m_edit1.SetWindowTextW(_T("Pass"));
		EndResult_textColor = RGB(0, 0, 0);
		EndResult_backColor = RGB(0, 255, 0);
	}
	else if (Result.Mid(0, 4) == "fail")
	{
		m_edit1.SetWindowTextW(_T("Fail"));
		EndResult_textColor = RGB(0, 0, 0);
		EndResult_backColor = RGB(255, 0, 0);
	}
	else //if (Result.Mid(0, 4) == "WAIT")
	{
		m_edit1.SetWindowTextW(_T("Wait"));
		EndResult_textColor = RGB(0, 0, 0);
		EndResult_backColor = RGB(255, 255, 0);
	}
	EndResult_backBrush.DeleteObject();
	EndResult_backBrush.CreateSolidBrush(EndResult_backColor);		//创建画刷
	GetDlgItem(IDC_EDIT1)->Invalidate();
}

//将数据项写入CSV文件
int CMACCheckDlg::PutCSVItemLine(FILE *file, CStringArray &sItemLine)
{
	//准备行数据
	CStringA sLineString;
	//循环取子项
	for (INT_PTR nItem = 0; nItem < sItemLine.GetSize(); nItem++)
	{
		//取子项
		CStringA sItem(sItemLine.GetAt(nItem));

		//查找是否包含引号或逗号
		if (sItem.FindOneOf("\",\r\n") >= 0)
		{
			//单引号替换为双引号
			sItem.Replace("\"", "\"\"");

			//首尾用引号包含
			sItem.Insert(0, "\""); sItem += "\"";
		}
		//添加逗号分隔符
		if (!sLineString.IsEmpty()) sLineString += ",";
		//追加数据
		sLineString += sItem;
	}
	//行尾添加\r\n
	sLineString += "\r\n";
	//写入文件
	return (int)fwrite((LPCSTR)sLineString, 1, sLineString.GetLength(), file);

}

void CMACCheckDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CString MACINI = _TEXT("MAC.ini");
	CString MACINI_PATH = PATH + MACINI;
	CString str, str_D, result, result_D;
	CString ipconfig_txt = _TEXT("ipconfig.txt");
	CString ipconfig_param = _TEXT("/C ipconfig /all > ipconfig.txt");
	CString ipconfig_path = PATH + ipconfig_txt;

	CString log_txt = _TEXT("log.txt");
	CString devcon = _TEXT("devcon\\");
	CString log_txt_path = PATH + devcon + log_txt;
	CString devcon_param = _TEXT("/C devcon.exe find usb\* > log.txt");
	CStdioFile file, file_D;
	DisplayResult(L"wait");



	OnRunExe(_TEXT("cmd.exe"), ipconfig_param, PATH);
	OnRunExe(_TEXT("cmd.exe"), devcon_param, PATH + devcon);
	Sleep(300);

	CString ImageCode;
	CString SN,SN1,SN2;
	CString value;
	CString MacAddress;
	CString sym = L"-";
	int x = 0;
	CString Num, PCB;
	CString PreFix;

	GetPrivateProfileString(_T("PreFix"), _T("Set"), CString("NULL"), PreFix.GetBuffer(MAX_PATH), MAX_PATH, MACINI_PATH);
	PreFix.ReleaseBuffer();
	m_edit3.GetWindowText(Num);//工单
	m_edit4.GetWindowText(PCB);//PCB
	m_edit6.GetWindowText(ImageCode);//二维码

	//MAC
	value = ImageCode.Right(12);	
	//SN
	SN1 = ImageCode.Left(ImageCode.Find(PreFix));
	SN2 = ImageCode.Right(ImageCode.GetLength() - SN1.GetLength());
	SN = SN2.Mid(0, 12);
	
	m_edit5.SetWindowTextW(SN);//SN
	m_edit2.SetWindowTextW(value);//MAC

	GetDlgItem(IDC_EDIT3)->EnableWindow(FALSE);
	for (int i = 0; i < 6; i++)
	{
		MacAddress += value.Mid(x, 2) + sym;
		x += 2;
	}
	MacAddress = MacAddress.Left(MacAddress.GetLength() - 1);


	//read ini
	CString DeviceInstanceID, DeviceVID, DevicePID;
	GetPrivateProfileString(_T("DeviceInstanceID"), _T("VID"), CString("NULL"), DeviceVID.GetBuffer(MAX_PATH), MAX_PATH, MACINI_PATH);
	GetPrivateProfileString(_T("DeviceInstanceID"), _T("PID"), CString("NULL"), DevicePID.GetBuffer(MAX_PATH), MAX_PATH, MACINI_PATH);
	GetPrivateProfileString(_T("DeviceInstanceID"), _T("Set"), CString("NULL"), DeviceInstanceID.GetBuffer(MAX_PATH), MAX_PATH, MACINI_PATH);
	DeviceInstanceID.ReleaseBuffer();
	int D_Line = DeviceInstanceID.GetLength();//MAC.ini DeviceInstanceID数据长度
	int D_fileline = GetFileLine(log_txt_path);//log.txt 文件行数


	//实际输出MAC和本机读取到的做对比
	int line = GetFileLine(ipconfig_path);
	int n = MacAddress.GetLength();
	file.Open(ipconfig_path, CFile::modeRead);
	for (int i = 0; i < line; i++)
	{
		file.ReadString(str);
		result += str;
		//CharToUTF8(result);
	}
	file.Close();

	CString r1,DevicePath;//设备实际路径
	CString res = DeviceInstanceID + value;
	int nn = D_Line + MacAddress.GetLength() - 5;//减5是因为有5个"-"
	file_D.Open(log_txt_path, CFile::modeRead);
	for (int i = 0; i < D_fileline; i++)
	{
		file_D.ReadString(str_D);
		if (str_D.Find(DeviceVID)&& str_D.Find(DevicePID) > 0)
		{
			r1 = str_D.Left(str_D.Find(L" "));
			DevicePath = r1.Right(D_Line+12);
		}
		result_D += str_D;
	}
	file_D.Close();
	//设备实际MAC就是设备路径的后12位
	CString DeviceMAC;
	DeviceMAC = DevicePath.Right(12);
	//此处循环为了IDC_STATIC_LOCALMAC 显示真实MAC地址
	CString DeviceMACDisplay;
	int y = 0;
	for (int i = 0; i < 6; i++)
	{
		DeviceMACDisplay += DeviceMAC.Mid(y, 2) + sym;
		y += 2;
	}
	DeviceMACDisplay = DeviceMACDisplay.Left(DeviceMACDisplay.GetLength() - 1);



	CString final_result;
	if (n == 17)
	{
		if (result.Find(MacAddress) > 0)
		{
			if (nn == D_Line + 12)
			{
				if (result_D.Find(res) > 0)
				{
					//AfxMessageBox(L"OK");
					m_static_localmac.SetWindowTextW(DeviceMACDisplay);
					DisplayResult(L"pass");
					final_result = _TEXT("pass");
				}
				else
				{
					m_static_localmac.SetWindowTextW(DeviceMACDisplay);
					result_D = _TEXT("Device Address Error: Device地址不一致");
					AfxMessageBox(result_D);
					DisplayResult(L"fail");
					final_result = _TEXT("fail");
				}
			}
			else
			{
				m_static_localmac.SetWindowTextW(DeviceMACDisplay);
				result_D = _TEXT("DevicePath Length Error: Device路径长度不一致");
				AfxMessageBox(result_D);
				DisplayResult(L"fail");
				final_result = _TEXT("fail");
			}
		}
		else
		{
			m_static_localmac.SetWindowTextW(DeviceMACDisplay);
			result = _TEXT("MAC address Error: Mac地址不一致");
			AfxMessageBox(result);
			DisplayResult(L"fail");
			final_result = _TEXT("fail");
		}

	}
	else
	{
		m_static_localmac.SetWindowTextW(DeviceMACDisplay);
		result = _TEXT("MAC Address Length Error: Mac长度不一致");
		AfxMessageBox(result);
		DisplayResult(L"fail");
		final_result = _TEXT("fail");
	}

	CString NumberS;
	NumberS.Format(L"%d", Number);
	tm = CTime::GetCurrentTime();
	TM = tm.Format("TIME:%Y-%m-%d-%X");
	FILE *f = NULL;
	if (_tfopen_s(&f, PATH + MACdata, _T("a+b")) == 0)		//w write  b bin
	{
		CStringArray sLine;
		sLine.Add(NumberS);						//测试次数
		sLine.Add(Num);							//工单
		sLine.Add(PCB);							//PCB
		sLine.Add(value);						//扫码MAC
		sLine.Add(DeviceMAC);					//设备MAC
		sLine.Add(DevicePath);					//设备路径
		sLine.Add(SN);							//SN
		sLine.Add(final_result);				//结果PASS or FAIL
		sLine.Add(TM);							//时间

		PutCSVItemLine(f, sLine);
		fclose(f);
	}

	Number += 1;
	DeleteFile(ipconfig_path);
	DeleteFile(log_txt_path);
	m_edit4.SetWindowText(_TEXT(""));//PCB
	m_edit6.SetWindowText(_TEXT(""));//MAC
	GetDlgItem(IDC_EDIT4)->SetFocus();
}

BOOL CMACCheckDlg::PreTranslateMessage(MSG* pMsg)
{
	CString PCB;
	m_edit4.GetWindowText(PCB);
	if (WM_KEYDOWN == pMsg->message && VK_RETURN == pMsg->wParam)
	{
		if (GetFocus() == GetDlgItem(IDC_EDIT3))
		{
			GetDlgItem(IDC_EDIT4)->SetFocus();
		}
		else if (GetFocus() == GetDlgItem(IDC_EDIT4))
		{
			if (PCB.GetLength() == 9)
			{
				GetDlgItem(IDC_EDIT6)->SetFocus();
			}
			else
			{
				AfxMessageBox(L"PCB长度不一致");
				m_edit4.SetWindowText(_TEXT(""));
				GetDlgItem(IDC_EDIT4)->SetFocus();
			}

		}
		return true;
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}

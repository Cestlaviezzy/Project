
// IntegrationDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "Integration.h"
#include "IntegrationDlg.h"
#include "afxdialogex.h"
#include "configpage.h"
#include <string>
#include "ShellExe.h"
#include "fileinfo.h"
#include "login.h"
#include "MESCheck.h"
#include "MESconnect.h"
#include "WindowTips.h"
#include "ChangeWindow.h"
#include "ModelErrorChoose.h"
#include "dbt.h"

using namespace System;
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#define COLOR_DEFAULT 0 //默认颜色 白色
#define COLOR_RED 1		//红色
#define COLOR_GREEN 2	//绿色
#define COLOR_YELLOW 3	//黄色
#endif

ShellExe shellexe;
fileinfo finfo;
login loginDlg;
MESCheck MEScheck;
MESconnect MESconDlg;
CString EXEPATH;
WindowTips WindowTipsDlg;
ChangeWindow ChangeWindowDlg;
ModelErrorChoose ModelErrorChooseDlg;
volatile BOOL m_Flag;



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


// CIntegrationDlg 对话框



CIntegrationDlg::CIntegrationDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_INTEGRATION_DIALOG, pParent)
{
//	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
//	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON2);
//	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON3);
//	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON4);
//	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON5);
//	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON6);
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON7);
}

void CIntegrationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_listA);
	DDX_Control(pDX, IDC_LIST2, m_listB);
	DDX_Control(pDX, IDC_EDIT1, m_edit1);
	DDX_Control(pDX, IDC_STATIC_RESULT, m_MES_result);
	DDX_Control(pDX, IDC_EDIT2, m_edit_site);
	DDX_Control(pDX, IDC_EDIT3, m_edit_user);
	DDX_Control(pDX, IDC_EDIT4, m_edit_equip);
	DDX_Control(pDX, IDC_EDIT5, m_edit_pcb);
	DDX_Control(pDX, IDC_STATIC_PICTURE, m_edit_picture);
	DDX_Control(pDX, IDC_STATIC_A, m_static_test_A);
	DDX_Control(pDX, IDC_STATIC_B, m_static_test_B);
	DDX_Control(pDX, IDC_STATIC_TESTRESULT, m_static_test_result);
	DDX_Control(pDX, IDC_STATIC_USERLOGIN, m_static_user_login);
	DDX_Control(pDX, IDC_STATIC_SETMES, m_static_MES_set);
	DDX_Control(pDX, IDC_STATIC_SITE, m_static_site);
	DDX_Control(pDX, IDC_STATIC_USER, m_static_user);
	DDX_Control(pDX, IDC_STATIC_EQUIP, m_static_equip);
	DDX_Control(pDX, IDC_STATIC_PCB, m_static_pcb);
	DDX_Control(pDX, IDC_STATIC_GOODWAYLOGO, m_static_goodway_logo);
	DDX_Control(pDX, IDC_EDIT6, m_edit_number);
	DDX_Control(pDX, IDC_STATIC_NUMBER, m_static_number);
}

BEGIN_MESSAGE_MAP(CIntegrationDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DEVICECHANGE()//添加消息映射
	ON_COMMAND(ID_32778, &CIntegrationDlg::OnconfigPage)
//	ON_BN_CLICKED(IDC_BUTTON1, &CIntegrationDlg::OnBnClickedButton1)
	ON_WM_CTLCOLOR()
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_LIST1, &CIntegrationDlg::OnNMCustomdrawList1)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_LIST2, &CIntegrationDlg::OnNMCustomdrawList2)
	ON_BN_CLICKED(IDC_RADIO1, &CIntegrationDlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CIntegrationDlg::OnBnClickedRadio2)
	ON_WM_TIMER()
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &CIntegrationDlg::OnNMDblclkList1)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST2, &CIntegrationDlg::OnNMDblclkList2)
END_MESSAGE_MAP()


// CIntegrationDlg 消息处理程序

BOOL CIntegrationDlg::OnInitDialog()
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

	//初始化listA
	//DWORD styles = m_listA.GetExtendedStyle();		//选中
	//m_listA.SetExtendedStyle(styles | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);		//设置网格
	m_listA.SetExtendedStyle(m_listA.GetExtendedStyle() | LVS_EX_FULLROWSELECT);//设置listcontrol report属性也能整行选中
	CRect rect;
	m_listA.GetClientRect(&rect);
	m_listA.InsertColumn(0, _T("项目名称"), LVCFMT_CENTER, rect.Width() / 3);
	m_listA.InsertColumn(1, _T("当前状态"), LVCFMT_CENTER, rect.Width() / 3);
	m_listA.InsertColumn(2, _T("测试结果"), LVCFMT_CENTER, rect.Width() / 3);
	OnReadINIfileA();

	//初始化listB
	m_listB.SetExtendedStyle(m_listB.GetExtendedStyle() | LVS_EX_FULLROWSELECT);//设置listcontrol report属性也能整行选中
	//CRect rectB;
	m_listB.GetClientRect(&rect);
	m_listB.InsertColumn(0, _T("项目名称"), LVCFMT_CENTER, rect.Width() / 3);
	m_listB.InsertColumn(1, _T("当前状态"), LVCFMT_CENTER, rect.Width() / 3);
	m_listB.InsertColumn(2, _T("测试结果"), LVCFMT_CENTER, rect.Width() / 3);
	OnReadINIfileB();

	//设置字体(左下角字体)
	m_font_result.DeleteObject();
	m_font_result.CreatePointFont(900, L"微软雅黑");//代表15号字体，华文行楷
	m_MES_result.SetFont(&m_font_result);
	//页面字体和list字体
	m_font.DeleteObject();
	m_font.CreatePointFont(100, L"微软雅黑");
	m_listA.SetFont(&m_font);
	m_listB.SetFont(&m_font);
	m_static_test_A.SetFont(&m_font);
	m_static_test_B.SetFont(&m_font);
	m_static_test_result.SetFont(&m_font);
	m_static_user_login.SetFont(&m_font);
	m_static_MES_set.SetFont(&m_font);
	m_static_site.SetFont(&m_font);
	m_static_user.SetFont(&m_font);
	m_static_equip.SetFont(&m_font);
	m_static_pcb.SetFont(&m_font);
	m_static_number.SetFont(&m_font);

	//设置radio初始状态
	CButton* radio = (CButton*)GetDlgItem(IDC_RADIO2);
	radio->SetCheck(0);
	//GetDlgItem(IDC_BUTTON1)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT5)->EnableWindow(FALSE);
	SetDlgItemText(IDC_EDIT1, L"请选择MES状态");
	//if (true)
	//{
	//	SelectPic_Logo(GOODWAY_LOGO);
	//}
	OnDelFile(PathA);
	OnDelFile(PathB);
	DeleteFile(log_path_A);		//删除A面结果日志
	DeleteFile(log_path_B);		//删除B面结果日志
	DeleteFile(path_AB);		//删除AB.txt文件

	//设置菜单栏
	CMenu mmenu;
	mmenu.LoadMenu(IDR_MENU1);  //IDR_MENU1为菜单栏ID号
	SetMenu(&mmenu);

	//设置时间
	//CString strTime;
	//CTime tm;
	//tm = CTime::GetCurrentTime();         //获取当前系统时间
	//strTime = tm.Format("%y年%m月%d日 %X");   //格式化系统时间。即使系统时 间按照Format中设置的格式显示
	//SetDlgItemText(IDC_EDIT6, strTime);        //初始化编辑框显示
	DateFont.DeleteObject();
	TimeFont.DeleteObject();
	CountFont.DeleteObject();
	DateFont.CreatePointFont(300, _T("宋体"), NULL);
	TimeFont.CreatePointFont(300, _T("宋体"), NULL);
	CountFont.CreatePointFont(200, _T("宋体"), NULL);
	GetDlgItem(IDC_STATIC_TIME1)->SetFont(&DateFont);
	GetDlgItem(IDC_STATIC_TIME2)->SetFont(&TimeFont);
	GetDlgItem(IDC_STATIC_TIME)->SetFont(&CountFont);
	SetTimer(1, 1000, NULL);         //启动定时器

	//设置焦点
	GetDlgItem(IDC_EDIT5)->SetFocus();
	//return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE

	TCHAR path[MAX_PATH] = { 0 };
	GetModuleFileName(NULL, path, MAX_PATH);
	(_tcsrchr(path, _T('\\')))[1] = 0;
	EXEPATH = path;//此时获得了EXE的目录

	//清除C/GOODWAY下所有result.log
	CString delresult = EXEPATH + L"DelResult.bat";
	ShellExecute(NULL, L"open", delresult, NULL, NULL, SW_HIDE);
	//shellexe.OnOpenFile(delresult, NULL);

	//设备拔插检测
	//DEV_BROADCAST_DEVICEINTERFACE DevBroadcastDeviceInterface;
	//memset(&DevBroadcastDeviceInterface, 0, sizeof(DEV_BROADCAST_DEVICEINTERFACE));
	//DevBroadcastDeviceInterface.dbcc_size = sizeof(DEV_BROADCAST_DEVICEINTERFACE);
	//DevBroadcastDeviceInterface.dbcc_devicetype = DBT_DEVTYP_DEVICEINTERFACE;
	//DevBroadcastDeviceInterface.dbcc_classguid = { 0xA5DCBF10, 0x6530, 0x11D2,{ 0x90, 0x1F, 0x00, 0xC0, 0x4F, 0xB9, 0x51, 0xED } };
	////	DevBroadcastDeviceInterface.dbcc_classguid = { 0xf18a0e88, 0xc30c, 0x11d0, {0x88, 0x15, 0x00, 0xa0, 0xc9, 0x06, 0xbe, 0xd8} };
	//RegisterDeviceNotification(this->GetSafeHwnd(), &DevBroadcastDeviceInterface, DEVICE_NOTIFY_WINDOW_HANDLE);

	//DEV_BROADCAST_DEVICEINTERFACE DevBroadcastDeviceInterfaceHUB;
	//memset(&DevBroadcastDeviceInterfaceHUB, 0, sizeof(DEV_BROADCAST_DEVICEINTERFACE));
	//DevBroadcastDeviceInterfaceHUB.dbcc_size = sizeof(DEV_BROADCAST_DEVICEINTERFACE);
	//DevBroadcastDeviceInterfaceHUB.dbcc_devicetype = DBT_DEVTYP_DEVICEINTERFACE;
	//DevBroadcastDeviceInterfaceHUB.dbcc_classguid = { 0xf18a0e88, 0xc30c, 0x11d0, {0x88, 0x15, 0x00, 0xa0, 0xc9, 0x06, 0xbe, 0xd8} };
	//RegisterDeviceNotification(this->GetSafeHwnd(), &DevBroadcastDeviceInterfaceHUB, DEVICE_NOTIFY_WINDOW_HANDLE);

	return FALSE;
}


void CIntegrationDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else if ((nID & 0xFFF0) == SC_CLOSE)		//右上角X  加入自己的代码*****************************
	{
		//删除意外导致的残留log
		//删除各个exe的残留log

		OnDelFile(PathA);
		OnDelFile(PathB);
		DeleteFile(log_path_A);		//删除A面结果日志
		DeleteFile(log_path_B);		//删除B面结果日志
		DeleteFile(path_AB);		//删除AB.txt文件
		exit(0);
	}
	CDialogEx::OnSysCommand(nID, lParam);
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CIntegrationDlg::OnPaint()
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
		CImage image;
		CRect rect1;
		image.Load(L"..\\Debug\\Icon\\goodway_logo_test.png");
		CWnd *pWnd = GetDlgItem(IDC_STATIC_GOODWAYLOGO);
		pWnd->UpdateWindow();
		CDC *pDC = pWnd->GetDC();
		pWnd->GetClientRect(&rect1);
		pDC->SetStretchBltMode(STRETCH_HALFTONE);
		image.Draw(pDC->m_hDC, rect1);
		ReleaseDC(pDC);
		image.Destroy();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CIntegrationDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//BOOL CIntegrationDlg::OnDeviceChange(UINT nEventType, DWORD dwData)
//{
//	DEV_BROADCAST_DEVICEINTERFACE* dbd = (DEV_BROADCAST_DEVICEINTERFACE*)dwData;
//
//	//这里进行信息匹配,比如guid等
//	//针对各个事件进行处理.
//	switch (nEventType)
//	{
//	case DBT_DEVICEREMOVECOMPLETE://设置移除
//		if (bFindRemovableDevice)
//		{
//			//MessageBox(_T("移除设备"));
//			DeviceRemovable = L"F";
//			bFindRemovableDevice = FALSE;
//		}
//		break;
//	case DBT_DEVICEARRIVAL://设备插入
//
//		if (!bFindRemovableDevice)
//		{
//			DeviceRemovable = L"T";
//			bFindRemovableDevice = TRUE;
//			//MessageBox(_T("发现设备"));
//		}
//		break;
//	default:
//		break;
//	}
//
//	return TRUE;
//}

void CIntegrationDlg::OnconfigPage()
{
	// TODO: 在此添加命令处理程序代码
	configpage  Dlg;
	Dlg.DoModal();
}

//读取INI文件函数
void CIntegrationDlg::OnReadINIfileA() 
{
	//主要每次都读取A面显示在list中

	CString stra;
	int m_indexA = 0;
	CString InformationStrA;
	CString stritema, strsoftwarea;
	GetPrivateProfileStringW(_T("LIST"), _T("Rows"), CString("NULL"), stra.GetBuffer(MAX_PATH), MAX_PATH, PathA);
	rowsA = _ttoi(stra);
	//AfxMessageBox(stra);
	for (int i = 0; i < rowsA; i++)
	{
		m_listA.InsertItem(i, L"");
		InformationStrA.Format(_T("Information_%d"), m_indexA);
		GetPrivateProfileStringW(InformationStrA, L"Item", CString("NULL"), stritema.GetBuffer(MAX_PATH), MAX_PATH, PathA);		//read Item name
		m_listA.SetItemText(i, 0, stritema);
		m_listA.SetItemText(i, 1, L"等待测试");	
		m_indexA++;
	}

}
void CIntegrationDlg::OnReadINIfileB()
{
	//主要每次都读取A面显示在list中
	CString strb;
	int m_indexB = 0;
	CString InformationStrB;
	CString stritemb, strsoftwareb;
	GetPrivateProfileString(_T("LIST"), _T("Rows"), CString("NULL"), strb.GetBuffer(MAX_PATH), MAX_PATH, PathB);
	strb.ReleaseBuffer();
	rowsB = _ttoi(strb);
	for (int i = 0; i < rowsB; i++)
	{
		m_listB.InsertItem(i, L"");
		InformationStrB.Format(_T("Information_%d"), m_indexB);
		GetPrivateProfileString(InformationStrB, L"Item", L"", stritemb.GetBuffer(MAX_PATH), MAX_PATH, PathB);		//read Item name
		stritemb.ReleaseBuffer();
		m_listB.SetItemText(i, 0, stritemb);
		m_listB.SetItemText(i, 1, L"等待测试");
		m_indexB++;
	}

}


void CIntegrationDlg::OnNMCustomdrawList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	//LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	NMLVCUSTOMDRAW* pNMCD = reinterpret_cast<NMLVCUSTOMDRAW*>(pNMHDR);
	NMCUSTOMDRAW nmCustomDraw = pNMCD->nmcd;
	int nItem = static_cast<int>(pNMCD->nmcd.dwItemSpec);
	switch (nmCustomDraw.dwDrawStage){
	case CDDS_ITEMPREPAINT:
	{
		if (COLOR_GREEN == nmCustomDraw.lItemlParam)
		{
			pNMCD->clrTextBk = RGB(192, 255, 62);
			pNMCD->clrText = RGB(0, 0, 0);		//green
		}
		else if (COLOR_RED == nmCustomDraw.lItemlParam)
		{
			pNMCD->clrTextBk = RGB(255, 0, 0);		//背景颜色
			pNMCD->clrText = RGB(0, 0, 0);		//red
		}
		else if (COLOR_YELLOW == nmCustomDraw.lItemlParam)
		{
			pNMCD->clrTextBk = RGB(255, 255, 0);
			pNMCD->clrText = RGB(0, 0, 0);		//yellow
		}
		else if (COLOR_DEFAULT == nmCustomDraw.lItemlParam)
		{
			pNMCD->clrTextBk = RGB(255, 255, 255);	//white
			pNMCD->clrText = RGB(0, 0, 0);		//black
		}
		break;
	}
	default:
	{
		break;
	}
	}
	*pResult = 0;
	*pResult |= CDRF_NOTIFYPOSTPAINT;
	*pResult |= CDRF_NOTIFYITEMDRAW;
	return;
}

void CIntegrationDlg::OnNMCustomdrawList2(NMHDR *pNMHDR, LRESULT *pResult)
{
	//LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	NMLVCUSTOMDRAW* pNMCD = reinterpret_cast<NMLVCUSTOMDRAW*>(pNMHDR);
	NMCUSTOMDRAW nmCustomDraw = pNMCD->nmcd;
	int nItem = static_cast<int>(pNMCD->nmcd.dwItemSpec);
	switch (nmCustomDraw.dwDrawStage){
	case CDDS_ITEMPREPAINT:
	{
		if (COLOR_GREEN == nmCustomDraw.lItemlParam)
		{
			pNMCD->clrTextBk = RGB(192, 255, 62);
			pNMCD->clrText = RGB(0, 0, 0);		//green
		}
		else if (COLOR_RED == nmCustomDraw.lItemlParam)
		{
			pNMCD->clrTextBk = RGB(255, 0, 0);		//背景颜色
			pNMCD->clrText = RGB(0, 0, 0);		//red
		}
		else if (COLOR_YELLOW == nmCustomDraw.lItemlParam)
		{
			pNMCD->clrTextBk = RGB(255, 255, 0);
			pNMCD->clrText = RGB(0, 0, 0);		//yellow
		}
		else if (COLOR_DEFAULT == nmCustomDraw.lItemlParam)
		{
			pNMCD->clrTextBk = RGB(255, 255, 255);	//white
			pNMCD->clrText = RGB(0, 0, 0);		//black
		}
		break;
	}
	default:
	{
		break;
	}
	}
	*pResult = 0;
	*pResult |= CDRF_NOTIFYPOSTPAINT;		//必须有，不然就没有效果
	*pResult |= CDRF_NOTIFYITEMDRAW;		//必须有，不然就没有效果
	return;
}


HBRUSH CIntegrationDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	if (pWnd->GetDlgCtrlID() == IDC_STATIC_RESULT)//如果是静态编辑框
	{
		//pDC->SetTextColor(RGB(0, 0, 0));//修改字体的颜色
		//pDC->SetBkMode(TRANSPARENT);//把字体的背景变成透明的
		pDC->SetTextColor(EndResult_textColor);
		pDC->SetBkColor(EndResult_backColor);

		hbr = (HBRUSH)EndResult_backBrush.GetSafeHandle();  //功能：适应static大小的背景颜色
		//return m_brush;//返回背景色
	}
	if (pWnd->GetDlgCtrlID() == IDC_STATIC_TIME1)
	{
		pDC->SetTextColor(RGB(147, 112, 219));
	}
	if (pWnd->GetDlgCtrlID() == IDC_STATIC_TIME2)
	{
		pDC->SetTextColor(RGB(238, 130, 238));
	}
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}

void CIntegrationDlg::DisplayResult(CString Result)
{
	if ((Result.Mid(0, 4)) == "PASS")
	{
		m_MES_result.SetWindowTextW(_T("PASS"));
		EndResult_textColor = RGB(0, 0, 0);
		EndResult_backColor = RGB(0, 255, 0);
	}
	else if (Result.Mid(0, 4) == "FAIL")
	{
		m_MES_result.SetWindowTextW(_T("FAIL"));
		EndResult_textColor = RGB(0, 0, 0);
		EndResult_backColor = RGB(255, 0, 0);
	}
	else //if (Result.Mid(0, 4) == "WAIT")
	{
		m_MES_result.SetWindowTextW(_T("WAIT"));
		EndResult_textColor = RGB(0, 0, 0);
		EndResult_backColor = RGB(255, 255, 0);
	}
	EndResult_backBrush.DeleteObject();
	EndResult_backBrush.CreateSolidBrush(EndResult_backColor);		//创建画刷
	GetDlgItem(IDC_STATIC_RESULT)->Invalidate();
}

//根据读取ini路径 来查找对应result.log路径并删除
void CIntegrationDlg::OnDelFile(CString path)
{
	CString str;
	CString str_result;
	CString InformationStr;
	int m_idex = 0;
	int rows;
	GetPrivateProfileString(_T("LIST"), _T("Rows"), CString("NULL"), str.GetBuffer(MAX_PATH), MAX_PATH, path);
	str.ReleaseBuffer();
	rows = _ttoi(str);
	for (int i = 0; i < rows; i++)
	{
		InformationStr.Format(_T("Information_%d"), m_idex);
		GetPrivateProfileString(InformationStr, L"Result", L"", str_result.GetBuffer(MAX_PATH), MAX_PATH, path);
		str_result.ReleaseBuffer();
		DeleteFile(str_result);
		m_idex++;
	}	
}

void CIntegrationDlg::ShowPic(CString LED_OriginalPath)//形参可以为所给的图片对象的指针，这里为了通用性省去了形参
{
	float cx, cy, dx, dy, k, t;//跟控件的宽和高以及图片宽和高有关的参数
	CRect   rect;//用于获取图片控件的宽和高
	CImage q;//为cimage图片类创建一个对象
	//CString IniPath = _T("\\Icon\\Ball Green.bmp");
	//CString PathINI = m_IspOriginalPath + IniPath;
	q.Load(LED_OriginalPath);//构造函数的形参是所加载图片的路径 
	cx = q.GetWidth();
	cy = q.GetHeight();//获取图片的宽 高
	k = cy / cx;//获得图片的宽高比

	CWnd *pWnd = NULL;
	pWnd = GetDlgItem(IDC_STATIC_PICTURE);//获取控件句柄
	pWnd->GetClientRect(&rect);//获取Picture Control控件的客户区
	dx = rect.Width();
	dy = rect.Height();//获得控件的宽高比
	t = dy / dx;//获得控件的宽高比
	if (k >= t)
	{
		rect.right = floor(rect.bottom / k);
		rect.left = (dx - rect.right) / 2;
		rect.right = floor(rect.bottom / k) + (dx - rect.right) / 2;
	}
	else
	{
		rect.bottom = floor(k*rect.right);
		rect.top = (dy - rect.bottom) / 2;
		rect.bottom = floor(k*rect.right) + (dy - rect.bottom) / 2;
	}
	//相关的计算为了让图片在绘图区居中按比例显示，原理很好懂，如果图片很宽但是不高，就上下留有空白区；如果图片很高而不宽就左右留有空白区，并且保持两边空白区一样大

	CDC *pDc = NULL;
	pDc = pWnd->GetDC();//获取picture control的DC，
	int ModeOld = SetStretchBltMode(pDc->m_hDC, STRETCH_HALFTONE);//设置指定设备环境中的位图拉伸模式

	//GetDlgItem(IDC_STATIC_PICTURE_SHOW)->ShowWindow(FALSE);
	GetDlgItem(IDC_STATIC_PICTURE)->ShowWindow(TRUE);
	q.StretchBlt(pDc->m_hDC, rect, SRCCOPY);//显示函数
	SetStretchBltMode(pDc->m_hDC, ModeOld);
	ReleaseDC(pDc);//释放指针空间
}
//初始化公司logo
void CIntegrationDlg::ShowPic_Logo(CString LED_OriginalPath)//形参可以为所给的图片对象的指针，这里为了通用性省去了形参
{
	float cx, cy, dx, dy, k, t;//跟控件的宽和高以及图片宽和高有关的参数
	CRect   rect;//用于获取图片控件的宽和高
	CImage q;//为cimage图片类创建一个对象
	//CString IniPath = _T("\\Icon\\Ball Green.bmp");
	//CString PathINI = m_IspOriginalPath + IniPath;
	q.Load(LED_OriginalPath);//构造函数的形参是所加载图片的路径 
	cx = q.GetWidth();
	cy = q.GetHeight();//获取图片的宽 高
	k = cy / cx;//获得图片的宽高比

	CWnd *pWnd = NULL;
	pWnd = GetDlgItem(IDC_STATIC_GOODWAYLOGO);//获取控件句柄
	pWnd->GetClientRect(&rect);//获取Picture Control控件的客户区
	dx = rect.Width();
	dy = rect.Height();//获得控件的宽高比
	t = dy / dx;//获得控件的宽高比
	if (k >= t)
	{
		rect.right = floor(rect.bottom / k);
		rect.left = (dx - rect.right) / 2;
		rect.right = floor(rect.bottom / k) + (dx - rect.right) / 2;
	}
	else
	{
		rect.bottom = floor(k*rect.right);
		rect.top = (dy - rect.bottom) / 2;
		rect.bottom = floor(k*rect.right) + (dy - rect.bottom) / 2;
	}
	//相关的计算为了让图片在绘图区居中按比例显示，原理很好懂，如果图片很宽但是不高，就上下留有空白区；如果图片很高而不宽就左右留有空白区，并且保持两边空白区一样大

	CDC *pDc = NULL;
	pWnd->UpdateWindow();
	pDc = pWnd->GetDC();//获取picture control的DC，
	int ModeOld = SetStretchBltMode(pDc->m_hDC, STRETCH_HALFTONE);//设置指定设备环境中的位图拉伸模式

	//GetDlgItem(IDC_STATIC_PICTURE_SHOW)->ShowWindow(FALSE);
	GetDlgItem(IDC_STATIC_GOODWAYLOGO)->ShowWindow(TRUE);
	q.StretchBlt(pDc->m_hDC, rect, SRCCOPY);//显示函数
	SetStretchBltMode(pDc->m_hDC, ModeOld);
	ReleaseDC(pDc);//释放指针空间
}

//导入MES图片
void CIntegrationDlg::SelectPic(UINT nIDEvent) {
	CString Path;
	switch (nIDEvent) {
	case Green_pic:
		Path = _T("..\\Debug\\Icon\\Green MES LED.bmp");
		ShowPic(Path);
		break;
	case Red_pic:
		Path = _T("..\\Debug\\Icon\\Red MES LED.bmp");
		ShowPic(Path);
		break;
	case Yellow_pic:
		Path = _T("..\\Debug\\Icon\\Yellow MES LED.bmp");
		ShowPic(Path);
	}
}

void CIntegrationDlg::SelectPic_Logo(UINT nIDEvent) {
	CString Path;
	switch (nIDEvent) {
	case GOODWAY_LOGO:
		Path = _T("..\\Debug\\Icon\\goodway_logo.bmp");
		ShowPic_Logo(Path);
	}
}

/******************Check MES Connect**********************/
void CIntegrationDlg::OnBnClickedRadio1()
{
	// TODO: 在此添加控件通知处理程序代码
	CFileFind finder;
	CString IntegraionName = _T("Integraion.ini");
	CString IntegraionPath = _T("C:\\Integraion.ini");
	BOOL ifFind = finder.FindFile(IntegraionPath);

	CString MES_site = _T("A2010A1");
	Genesis::Gtimes::Interface::EquipLinkMes ^site = gcnew Genesis::Gtimes::Interface::EquipLinkMes;
	System::String ^put_site = gcnew String(MES_site);
	CString MES_SITE = site->CheckSite(put_site);
	string login_site = (LPCSTR)(CStringA)(MES_SITE);
	UpdateData(TRUE);
	RadioState_Green = ((CButton *)GetDlgItem(IDC_RADIO1))->GetCheck();
	if ((RadioState_Green == 1) && (MES_SITE == "T"))
	{
		if (ifFind)
		{
			finder.Close();
			loginDlg.DoModal();
			GetPrivateProfileString(_T("LoginInfo"), _T("Site"), CString(""), mes_site.GetBuffer(MAX_PATH), MAX_PATH, IntegraionPath);
			GetPrivateProfileString(_T("LoginInfo"), _T("User"), CString(""), mes_user.GetBuffer(MAX_PATH), MAX_PATH, IntegraionPath);
			GetPrivateProfileString(_T("LoginInfo"), _T("Number"), CString(""), mes_number.GetBuffer(MAX_PATH), MAX_PATH, IntegraionPath);
			GetPrivateProfileString(_T("LoginInfo"), _T("Equip"), CString(""), mes_equip.GetBuffer(MAX_PATH), MAX_PATH, IntegraionPath);
			GetDlgItem(IDC_EDIT5)->EnableWindow(TRUE);
			GetDlgItem(IDC_EDIT5)->SetFocus();
			SetDlgItemText(IDC_EDIT1, L"连接MES成功");
			SelectPic(Green_pic);
			m_edit_site.SetWindowText(mes_site);
			m_edit_user.SetWindowText(mes_user);
			m_edit_equip.SetWindowText(mes_equip);
			m_edit_number.SetWindowText(mes_number);
			SetDlgItemText(IDC_EDIT1, L"登陆成功");
		}
		else
		{
			GetDlgItem(IDC_EDIT5)->EnableWindow(TRUE);
			GetDlgItem(IDC_EDIT5)->SetFocus();
			SetDlgItemText(IDC_EDIT1, L"连接MES成功");
			SelectPic(Green_pic);
			loginDlg.DoModal();
			m_edit_site.SetWindowText(loginDlg.Site);
			m_edit_user.SetWindowText(loginDlg.User);
			m_edit_equip.SetWindowText(loginDlg.Equip1);
			m_edit_number.SetWindowText(loginDlg.Number);
			SetDlgItemText(IDC_EDIT1, L"登陆成功");
		}

		if (loginclose == 0)
		{
			GetDlgItem(IDC_EDIT5)->EnableWindow(FALSE);
			m_edit_site.SetWindowText(_T(""));
			m_edit_user.SetWindowText(_T(""));
			m_edit_equip.SetWindowText(_T(""));
			m_edit_number.SetWindowText(_T(""));
			SetDlgItemText(IDC_EDIT1, L"连接MES失败");
			SelectPic(Red_pic);
			((CButton *)GetDlgItem(IDC_RADIO1))->SetCheck(0);
			SetDlgItemText(IDC_EDIT1, L"登陆失败");
		}

	}
	else if ((RadioState_Green == 1) && (MES_SITE != "T"))
	{
		GetDlgItem(IDC_EDIT5)->EnableWindow(FALSE);
		SetDlgItemText(IDC_EDIT1, L"连接MES失败");
		SelectPic(Red_pic);
		AfxMessageBox(_T("连接失败或者没有连接到MES专用网络"));
		((CButton *)GetDlgItem(IDC_RADIO1))->SetCheck(0);
	}
}




void CIntegrationDlg::OnBnClickedRadio2()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	//RadioState_Yellow = ((CButton *)GetDlgItem(IDC_RADIO2))->GetCheck();
	MESconDlg.DoModal();
	if (mespasswordflag == 1)
	{
		//GetDlgItem(IDC_BUTTON1)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT5)->EnableWindow(TRUE);	
		GetDlgItem(IDC_EDIT5)->SetFocus();
		SetDlgItemText(IDC_EDIT1, L"MES不连接/单机测试");
		SelectPic(Yellow_pic);
	}
	else if (mespasswordflag == 0)
	{
		((CButton *)GetDlgItem(IDC_RADIO2))->SetCheck(FALSE);
		//GetDlgItem(IDC_BUTTON1)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT5)->EnableWindow(FALSE);
		SetDlgItemText(IDC_EDIT1, L"MES解锁失败");
	}
	else if (mespasswordflag == 6)
	{
		SetTimer(3, 1000, NULL);
		GetDlgItem(IDC_EDIT5)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT5)->SetFocus();
		SetDlgItemText(IDC_EDIT1, L"MES不连接/单机测试/计数器");
		SelectPic(Yellow_pic);
		KillTimer(3);
	}
}

//void CIntegrationDlg::OnBnClickedButton1()
//{
//	// TODO: 在此添加控件通知处理程序代码
//
//	OnDelFile(PathA);
//	OnDelFile(PathB);
//	DeleteFile(log_path_A);		//删除A面结果日志
//	DeleteFile(log_path_B);		//删除B面结果日志
//	DeleteFile(path_AB);		//删除AB.txt文件
//}


//LONG WINAPI FreeEIM_UnhandledExceptionFilter(LPEXCEPTION_POINTERS ExceptionInfo)
//{
//	AfxMessageBox(L"Exception");	//调用回调函数成功
//
//	//调用重启/错误提交程序（视情况而定）
//	CString strPath = _T("Integration.exe");
//	USES_CONVERSION;
//	LPCSTR lpcs = NULL;
//	lpcs = T2A(strPath.GetBuffer(strPath.GetLength()));
//	WinExec(lpcs, SW_SHOWNORMAL);
//
//	return EXCEPTION_EXECUTE_HANDLER;	//返回本回调函数的处理结果
//}


void CIntegrationDlg::IntegrationStart(CString PCB)
{
	//SetUnhandledExceptionFilter(FreeEIM_UnhandledExceptionFilter);	//声明调用回调函数

	/**********读取INI文档**********/
	//先INI文件中获取A和B的list行数
	CString stra, strb;
	GetPrivateProfileString(_T("LIST"), _T("Rows"), CString("NULL"), stra.GetBuffer(MAX_PATH), MAX_PATH, PathA);
	GetPrivateProfileString(_T("LIST"), _T("Rows"), CString("NULL"), strb.GetBuffer(MAX_PATH), MAX_PATH, PathB);
	rowsA = _ttoi(stra);
	rowsB = _ttoi(strb);
	for (int i = 0; i < rowsA; i++)
	{
		m_listA.SetItemText(i, 1, L"等待测试");
		m_listA.SetItemText(i, 2, L"");
		m_listA.SetItemData(i, COLOR_DEFAULT);
		//return ;
	}
	for (int i = 0; i < rowsB; i++)
	{
		m_listB.SetItemText(i, 1, L"等待测试");
		m_listB.SetItemText(i, 2, L"");
		m_listB.SetItemData(i, COLOR_DEFAULT);
		//return;
	}
	CString site, user, equip, pcb_r;
	CString result_pass = L"";
	CString result_fail = L"";
	CString upload_pass;
	CString upload_fail;

	CString MES_PCB_RESULT;
	//PCB check
	m_edit_pcb.GetWindowText(PCB);
	m_edit_number.GetWindowText(mes_number);
	m_edit_site.GetWindowText(mes_site);


	SetDlgItemText(IDC_EDIT1, L"s.开始测试中...");


	//程序开始

	//先检测PCB是不是9位
	if (PCB.GetLength() == 9)
	{

		//密码为6启动计数器
		if (mespasswordflag == 6)
		{
			SetTimer(3, 1000, NULL);
		}
		GetDlgItem(IDC_EDIT5)->EnableWindow(FALSE);
		//界面初始化
		pcb_r = PCB;
		//读取特定内容
		CFileFind finder;
		BOOL ifFind = finder.FindFile(PathB);
		CString stritema, strsoftwarea, strresulta;
		CString stritemb, strsoftwareb, strresultb;
		int m_indexA = 0;
		int m_indexB = 0;
		CString InformationStrA;
		CString InformationStrB;
		CString ColorResultA = L"";
		CString ColorResultB = L"";
		CString ColorResultX = L"";
		CString EXE_Name;
		CString PCBdata;

		//检测是不是连接MES状态
		if (((CButton *)GetDlgItem(IDC_RADIO1))->GetCheck())
		{
			//检测PCB是否存在、是不是当前站别等...
			MES_PCB_RESULT = MEScheck.CheckPCB(mes_site, PCB);
			string mes_pcb_result = (LPCSTR)(CStringA)(MES_PCB_RESULT);
			if (mes_pcb_result == "T")
			{
				//工单检测
				PCBdata = MEScheck.GetPCBdata(mes_site, PCB);
				CheckNumberResult = PCBdata.Left(PCBdata.Find(_T(",")));
				if (CheckNumberResult == mes_number)
				{
					//start 生成AB.txt文件
					//A面开始运行
					DisplayResult(L"");
					finfo.WriteFileToPath(path_AB, s_A);
					for (int i = 0; i < rowsA; i++)
					{
						m_listA.SetItemText(i, 1, L"测试中...");
						m_listA.SetItemText(i, 2, wait);
						m_listA.SetItemData(i, COLOR_YELLOW);
						InformationStrA.Format(_T("Information_%d"), m_indexA);
						GetPrivateProfileString(InformationStrA, L"Item", L"", stritema.GetBuffer(MAX_PATH), MAX_PATH, PathA);		//read Item name
						stritema.ReleaseBuffer();
						GetPrivateProfileString(InformationStrA, L"Software", L"", strsoftwarea.GetBuffer(MAX_PATH), MAX_PATH, PathA);		//read Software path 
						strsoftwarea.ReleaseBuffer();
						GetPrivateProfileString(InformationStrA, L"Result", L"", strresulta.GetBuffer(MAX_PATH), MAX_PATH, PathA);		//read Result path 
						strresulta.ReleaseBuffer();

						loop1:
						shellexe.OnOpenFile(strsoftwarea, NULL);
						ColorResultA = finfo.ReadFileFirstLine(strresulta);
						if (ColorResultA.Mid(0, 4) == "pass")
						{
							m_listA.SetItemText(i, 1, L"测试完成");
							m_listA.SetItemText(i, 2, pass);
							m_listA.SetItemData(i, COLOR_GREEN);
						}
						else if (ColorResultA.Mid(0, 4) == "fail")
						{
							m_listA.SetItemText(i, 1, L"测试完成");
							m_listA.SetItemText(i, 2, fail);
							m_listA.SetItemData(i, COLOR_RED);
							ModelErrorChooseDlg.DoModal();
							///*
							//	三种选择
							//	one -> 当前重新测试一次
							//	two -> 退出测试，并将UI界面置为初始，重新输入PCB
							//	three -> 继续往下测试
							//*/
							if (Choose == "one")
							{
								SetDlgItemText(IDC_EDIT1, L"选择重新测试");
								DeleteFile(strresulta);

								m_listA.SetItemText(i, 1, L"测试中...");
								m_listA.SetItemText(i, 2, wait);
								m_listA.SetItemData(i, COLOR_YELLOW);
								goto loop1;
							}
							else if (Choose == "two")
							{
								DeleteFile(strresulta);
								DeleteFile(log_path_A);
								
								for (int j = 0; j < rowsA; j++)
								{
									m_listA.SetItemText(j, 1, L"等待测试");
									m_listA.SetItemText(j, 2, L"");
									m_listA.SetItemData(j, COLOR_DEFAULT);
									//return ;
								}
								goto loop2;
							}
							else if (Choose == "three")
							{
								SetDlgItemText(IDC_EDIT1, L"选择继续测试");
								goto loop3;
							}						
						}
						loop3:
						m_indexA++;
						finfo.OnFileMerge(GOODWAY, log_path_A);		//Param1 在哪个目录下抓取， Param2 抓取结果生成在什么路径上。  
						/****删除A面的result.log***/
						OnDelFile(PathA);
					}
					DeleteFile(path_AB);		//A面全运行完，删除A面文档


					//查找B面ini文件是否存在，存在就运行，不存在跳出结束	
					if (ifFind)
					{
						finder.Close();

						//AfxMessageBox(L"换面");
						ChangeWindowDlg.DoModal();
						//通过检测设备拔插来是否运行反面程序 DeviceRemovable = T 插入
						//BFuncCheck();
						HANDLE hThreadss;
						DWORD ThreadID;
						//读取特定内容
						CString stritemb, strsoftwareb, strresultb;
						int m_indexB = 0;
						CString InformationStrB;
						CString ColorResultB = L"";
						//防止计数器卡死
						hThreadss = CreateThread(0, 0, ThreadProcTime, this, 0, &ThreadID);
						shellexe.TheadWait(hThreadss);

						finfo.WriteFileToPath(path_AB, s_B);
						for (int i = 0; i < rowsB; i++)
						{
							m_listB.SetItemText(i, 1, L"测试中...");
							m_listB.SetItemText(i, 2, wait);
							m_listB.SetItemData(i, COLOR_YELLOW);
							InformationStrB.Format(_T("Information_%d"), m_indexB);
							GetPrivateProfileString(InformationStrB, _T("Item"), CString("NULL"), stritemb.GetBuffer(MAX_PATH), MAX_PATH, PathB);
							stritemb.ReleaseBuffer();
							GetPrivateProfileString(InformationStrB, _T("Software"), CString("NULL"), strsoftwareb.GetBuffer(MAX_PATH), MAX_PATH, PathB);
							strsoftwareb.ReleaseBuffer();
							GetPrivateProfileString(InformationStrB, L"Result", CString("NULL"), strresultb.GetBuffer(MAX_PATH), MAX_PATH, PathB);
							strresultb.ReleaseBuffer();
							//string s = (LPCSTR)(CStringA)(stritemb);

						loop11:
							shellexe.OnOpenFile(strsoftwareb, NULL);
							ColorResultB = finfo.ReadFileFirstLine(strresultb);
							if (ColorResultB.Mid(0, 4) == "pass")
							{
								m_listB.SetItemText(i, 1, L"测试完成");
								m_listB.SetItemText(i, 2, pass);
								m_listB.SetItemData(i, COLOR_GREEN);
							}
							else if (ColorResultB.Mid(0, 4) == "fail")
							{
								m_listB.SetItemText(i, 1, L"测试完成");
								m_listB.SetItemText(i, 2, fail);
								m_listB.SetItemData(i, COLOR_RED);
								ModelErrorChooseDlg.DoModal();
								/*
									三种选择
									one -> 当前重新测试一次
									two -> 退出测试，并将UI界面置为初始，重新输入PCB
									three -> 继续往下测试
								*/
								if (Choose == "one")
								{
									SetDlgItemText(IDC_EDIT1, L"选择重新测试");
									DeleteFile(strresultb);
									m_listB.SetItemText(i, 1, L"测试中...");
									m_listB.SetItemText(i, 2, wait);
									m_listB.SetItemData(i, COLOR_YELLOW);
									goto loop11;
								}
								else if (Choose == "two")
								{
									DeleteFile(strresultb);

									DeleteFile(log_path_A);
									DeleteFile(log_path_B);
									
									for (int j = 0; j < rowsA; j++)
									{
										m_listA.SetItemText(j, 1, L"等待测试");
										m_listA.SetItemText(j, 2, L"");
										m_listA.SetItemData(j, COLOR_DEFAULT);
										//return ;
									}
									for (int j = 0; j < rowsB; j++)
									{
										m_listB.SetItemText(j, 1, L"等待测试");
										m_listB.SetItemText(j, 2, L"");
										m_listB.SetItemData(j, COLOR_DEFAULT);
										//return;
									}
									goto loop22;
								}
								else if (Choose == "three")
								{
									SetDlgItemText(IDC_EDIT1, L"选择继续测试");
									goto loop33;
								}
							}
						loop33:
							m_indexB++;
							finfo.OnFileMerge(GOODWAY, log_path_B);
							OnDelFile(PathB);
						}

						DeleteFile(path_AB);	//删除AB.txt
					}
					Sleep(300);
					MSG	msg;
					if (PeekMessage(&msg, (HWND)NULL, 0, 0, PM_REMOVE))
					{
						::SendMessage(msg.hwnd, msg.message, msg.wParam, msg.lParam);
					}
					UpdateData(FALSE);
					SetDlgItemText(IDC_EDIT1, L"测试已经完成，准备上传资料...");
					//抓取A和B面所有result.log合并成一个Final_Result.log文件
					finfo.OnFileMergeAll(log_path_A, log_path_B, log_path_temp_result);
					;
					DeleteFile(log_path_A);
					DeleteFile(log_path_B);
					finfo.AddFileINI(log_path_temp_result, log_path_result);				//最终结果文件添加PASS/FAIL		
					DeleteFile(log_path_temp_result);
					ColorResultX = finfo.ReadFileFirstLine(log_path_result);
					/*****上传MES*****/
					/*********先获取控件的值*********/
					int line = finfo.Newgetfileline(log_path_result);
					//int SendToMes = finfo.SendToMESWaitTime(Configini);
					CString cc;
					int ccnum;
					GetPrivateProfileStringW(_T("WindowTips"), _T("Set"), CString("NULL"), cc.GetBuffer(MAX_PATH), MAX_PATH, Configini);
					ccnum = _ttoi(cc);

					if (((CButton *)GetDlgItem(IDC_RADIO1))->GetCheck())
					{
						//过站提醒
						if ((ccnum == 1) && ((ColorResultX.Mid(0, 4) == "FAIL")))
						{
							//弹窗提醒
							WindowTipsDlg.DoModal();
							if (TF == 1)
							{
								SetDlgItemText(IDC_EDIT1, L"数据上传MES中...");
								if (ColorResultX.Mid(0, 4) == "PASS")
								{
									DWORD dwIDpass1;
									HANDLE hThreadpass1;
									hThreadpass1 = CreateThread(0, 0, ThreadProcPASS, this, 0, &dwIDpass1);

									while (TRUE)
									{

										DWORD result;
										MSG msg;

										result = MsgWaitForMultipleObjects(1, &hThreadpass1,
											FALSE, INFINITE, QS_ALLINPUT);

										if (result == (WAIT_OBJECT_0))
										{
											break;
										}
										else
										{
											PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);
											DispatchMessage(&msg);
										}
									}
									GetPrivateProfileString(_T("MESRESULT"), _T("result"), CString("null"), upload_pass.GetBuffer(MAX_PATH), MAX_PATH, mes_check_result_ini);

									string up_pass = (LPCSTR)(CStringA)(upload_pass);
									if (up_pass == "T")
									{
										SetDlgItemText(IDC_EDIT1, L"p.上传MES成功");
										DisplayResult(ColorResultX);
									}
									else
									{
										SetDlgItemText(IDC_EDIT1, L"p.上传MES失败");
										DisplayResult(L"FAIL");
									}
									GetDlgItem(IDC_EDIT5)->EnableWindow(TRUE);
									GetDlgItem(IDC_EDIT5)->SetWindowText(L"");
									GetDlgItem(IDC_EDIT5)->SetFocus();
								}
								else if (ColorResultX.Mid(0, 4) == "FAIL")
								{
									DWORD dwIDfail2;
									HANDLE hThreadfail2;
									hThreadfail2 = CreateThread(0, 0, ThreadProcFAIL, this, 0, &dwIDfail2);

									while (TRUE)
									{

										DWORD result;
										MSG msg;

										result = MsgWaitForMultipleObjects(1, &hThreadfail2,
											FALSE, INFINITE, QS_ALLINPUT);

										if (result == (WAIT_OBJECT_0))
										{
											break;
										}
										else
										{
											PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);
											DispatchMessage(&msg);
										}
									}
									GetPrivateProfileString(_T("MESRESULT"), _T("result"), CString("null"), upload_fail.GetBuffer(MAX_PATH), MAX_PATH, mes_check_result_ini);

									string up_fail = (LPCSTR)(CStringA)(upload_fail);
									if (up_fail == "T")
									{
										SetDlgItemText(IDC_EDIT1, L"f.上传MES成功");
										DisplayResult(ColorResultX);
									}
									else
									{
										SetDlgItemText(IDC_EDIT1, L"f.上传MES失败");
										DisplayResult(ColorResultX);
									}
									GetDlgItem(IDC_EDIT5)->EnableWindow(TRUE);
									GetDlgItem(IDC_EDIT5)->SetWindowText(L"");
									GetDlgItem(IDC_EDIT5)->SetFocus();
								}
							}
							else
							{
								if (ColorResultX.Mid(0, 4) == "PASS")
								{
									DisplayResult(ColorResultX);
								}
								else if (ColorResultX.Mid(0, 4) == "FAIL")
								{
									DisplayResult(ColorResultX);
								}
								SetDlgItemText(IDC_EDIT1, L"选择不上传重新测试");
								GetDlgItem(IDC_EDIT5)->EnableWindow(TRUE);
								GetDlgItem(IDC_EDIT5)->SetWindowText(L"");
								GetDlgItem(IDC_EDIT5)->SetFocus();
								DeleteFile(log_path_result);

							}
						}
						else
						{
							SetDlgItemText(IDC_EDIT1, L"数据上传MES中...");
							if (ColorResultX.Mid(0, 4) == "PASS")
							{
								DWORD dwIDpass1;
								HANDLE hThreadpass1;
								hThreadpass1 = CreateThread(0, 0, ThreadProcPASS, this, 0, &dwIDpass1);

								while (TRUE)
								{

									DWORD result;
									MSG msg;

									result = MsgWaitForMultipleObjects(1, &hThreadpass1,
										FALSE, INFINITE, QS_ALLINPUT);

									if (result == (WAIT_OBJECT_0))
									{
										break;
									}
									else
									{
										PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);
										DispatchMessage(&msg);
									}
								}
								GetPrivateProfileString(_T("MESRESULT"), _T("result"), CString("null"), upload_pass.GetBuffer(MAX_PATH), MAX_PATH, mes_check_result_ini);

								string up_pass = (LPCSTR)(CStringA)(upload_pass);
								if (up_pass == "T")
								{
									SetDlgItemText(IDC_EDIT1, L"p.上传MES成功");
									DisplayResult(ColorResultX);
								}
								else
								{
									SetDlgItemText(IDC_EDIT1, L"p.上传MES失败");
									DisplayResult(L"FAIL");
								}
								GetDlgItem(IDC_EDIT5)->EnableWindow(TRUE);
								GetDlgItem(IDC_EDIT5)->SetWindowText(L"");
								GetDlgItem(IDC_EDIT5)->SetFocus();
							}
							else if (ColorResultX.Mid(0, 4) == "FAIL")
							{
								DWORD dwIDfail2;
								HANDLE hThreadfail2;
								hThreadfail2 = CreateThread(0, 0, ThreadProcFAIL, this, 0, &dwIDfail2);

								while (TRUE)
								{

									DWORD result;
									MSG msg;

									result = MsgWaitForMultipleObjects(1, &hThreadfail2,
										FALSE, INFINITE, QS_ALLINPUT);

									if (result == (WAIT_OBJECT_0))
									{
										break;
									}
									else
									{
										PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);
										DispatchMessage(&msg);
									}
								}
								GetPrivateProfileString(_T("MESRESULT"), _T("result"), CString("null"), upload_fail.GetBuffer(MAX_PATH), MAX_PATH, mes_check_result_ini);

								string up_fail = (LPCSTR)(CStringA)(upload_fail);
								if (up_fail == "T")
								{
									SetDlgItemText(IDC_EDIT1, L"f.上传MES成功");
									DisplayResult(ColorResultX);
								}
								else
								{
									SetDlgItemText(IDC_EDIT1, L"f.上传MES失败");
									DisplayResult(ColorResultX);
								}
								GetDlgItem(IDC_EDIT5)->EnableWindow(TRUE);
								GetDlgItem(IDC_EDIT5)->SetWindowText(L"");
								GetDlgItem(IDC_EDIT5)->SetFocus();
							}
						}

					}
					else if (((CButton *)GetDlgItem(IDC_RADIO2))->GetCheck())		//不连接MES测试
					{
						if (ColorResultX.Mid(0, 4) == "PASS")
						{
							DisplayResult(ColorResultX);
						}
						else if (ColorResultX.Mid(0, 4) == "FAIL")
						{
							DisplayResult(ColorResultX);
						}
					}
				}
				else
				{
					//工单不一致 界面控件重置
					AfxMessageBox(L"ERROR\n" + L"工单不一致\n" + L"当前工单：" + mes_number + L"\n" + L"输入PCB工单：" + CheckNumberResult);
					GetDlgItem(IDC_EDIT5)->EnableWindow(TRUE);
					GetDlgItem(IDC_EDIT5)->SetWindowText(L"");
					GetDlgItem(IDC_EDIT5)->SetFocus();
					EndResult_backColor = RGB(255, 255, 255);
					EndResult_backBrush.DeleteObject();
					EndResult_backBrush.CreateSolidBrush(EndResult_backColor);		//创建画刷
					GetDlgItem(IDC_STATIC_RESULT)->Invalidate();
					GetDlgItem(IDC_STATIC_RESULT)->SetWindowText(_T(""));
					SetDlgItemText(IDC_EDIT1, L"N.测试失败");
				}
			}
			else
			{
				//PCB不存在或者不在当站 界面控件重置
				AfxMessageBox(MES_PCB_RESULT);
				GetDlgItem(IDC_EDIT5)->EnableWindow(TRUE);
				GetDlgItem(IDC_EDIT5)->SetWindowText(L"");
				GetDlgItem(IDC_EDIT5)->SetFocus();
				EndResult_backColor = RGB(255, 255, 255);
				EndResult_backBrush.DeleteObject();
				EndResult_backBrush.CreateSolidBrush(EndResult_backColor);		//创建画刷
				GetDlgItem(IDC_STATIC_RESULT)->Invalidate();
				GetDlgItem(IDC_STATIC_RESULT)->SetWindowText(_T(""));
				SetDlgItemText(IDC_EDIT1, L"P.测试失败");
			}
		}
		else
		{
			//单机测试
			DisplayResult(L"");
			finfo.WriteFileToPath(path_AB, s_A);
			for (int i = 0; i < rowsA; i++)
			{
				m_listA.SetItemText(i, 1, L"测试中...");
				m_listA.SetItemText(i, 2, wait);
				m_listA.SetItemData(i, COLOR_YELLOW);
				InformationStrA.Format(_T("Information_%d"), m_indexA);
				GetPrivateProfileString(InformationStrA, L"Item", L"", stritema.GetBuffer(MAX_PATH), MAX_PATH, PathA);		//read Item name
				stritema.ReleaseBuffer();
				GetPrivateProfileString(InformationStrA, L"Software", L"", strsoftwarea.GetBuffer(MAX_PATH), MAX_PATH, PathA);		//read Software path 
				strsoftwarea.ReleaseBuffer();
				GetPrivateProfileString(InformationStrA, L"Result", L"", strresulta.GetBuffer(MAX_PATH), MAX_PATH, PathA);		//read Result path 
				strresulta.ReleaseBuffer();

				shellexe.OnOpenFile(strsoftwarea, NULL);
				ColorResultA = finfo.ReadFileFirstLine(strresulta);
				if (ColorResultA.Mid(0, 4) == "pass")
				{
					m_listA.SetItemText(i, 1, L"测试完成");
					m_listA.SetItemText(i, 2, pass);
					m_listA.SetItemData(i, COLOR_GREEN);
				}
				else if (ColorResultA.Mid(0, 4) == "fail")
				{
					m_listA.SetItemText(i, 1, L"测试完成");
					m_listA.SetItemText(i, 2, fail);
					m_listA.SetItemData(i, COLOR_RED);
				}
				m_indexA++;
				finfo.OnFileMerge(GOODWAY, log_path_A);		//Param1 在哪个目录下抓取， Param2 抓取结果生成在什么路径上。  
				/****删除A面的result.log***/
				OnDelFile(PathA);
			}
			DeleteFile(path_AB);		//A面全运行完，删除A面文档


			//查找B面ini文件是否存在，存在就运行，不存在跳出结束	
			if (ifFind)
			{
				finder.Close();

				//AfxMessageBox(L"换面");
				ChangeWindowDlg.DoModal();
				//通过检测设备拔插来是否运行反面程序 DeviceRemovable = T 插入
				//BFuncCheck();
				HANDLE hThreadss;
				DWORD ThreadID;
				//读取特定内容
				CString stritemb, strsoftwareb, strresultb;
				int m_indexB = 0;
				CString InformationStrB;
				CString ColorResultB = L"";
				//防止计数器卡死
				hThreadss = CreateThread(0, 0, ThreadProcTime, this, 0, &ThreadID);
				shellexe.TheadWait(hThreadss);

				finfo.WriteFileToPath(path_AB, s_B);
				for (int i = 0; i < rowsB; i++)
				{
					m_listB.SetItemText(i, 1, L"测试中...");
					m_listB.SetItemText(i, 2, wait);
					m_listB.SetItemData(i, COLOR_YELLOW);
					InformationStrB.Format(_T("Information_%d"), m_indexB);
					GetPrivateProfileString(InformationStrB, _T("Item"), CString("NULL"), stritemb.GetBuffer(MAX_PATH), MAX_PATH, PathB);
					stritemb.ReleaseBuffer();
					GetPrivateProfileString(InformationStrB, _T("Software"), CString("NULL"), strsoftwareb.GetBuffer(MAX_PATH), MAX_PATH, PathB);
					strsoftwareb.ReleaseBuffer();
					GetPrivateProfileString(InformationStrB, L"Result", CString("NULL"), strresultb.GetBuffer(MAX_PATH), MAX_PATH, PathB);
					strresultb.ReleaseBuffer();

					shellexe.OnOpenFile(strsoftwareb, NULL);
					ColorResultB = finfo.ReadFileFirstLine(strresultb);
					if (ColorResultB.Mid(0, 4) == "pass")
					{
						m_listB.SetItemText(i, 1, L"测试完成");
						m_listB.SetItemText(i, 2, pass);
						m_listB.SetItemData(i, COLOR_GREEN);
					}
					else if (ColorResultB.Mid(0, 4) == "fail")
					{
						m_listB.SetItemText(i, 1, L"测试完成");
						m_listB.SetItemText(i, 2, fail);
						m_listB.SetItemData(i, COLOR_RED);
					}
					m_indexB++;
					finfo.OnFileMerge(GOODWAY, log_path_B);
					OnDelFile(PathB);
				}

				DeleteFile(path_AB);	//删除AB.txt
			}
			Sleep(300);
			MSG	msg;
			if (PeekMessage(&msg, (HWND)NULL, 0, 0, PM_REMOVE))
			{
				::SendMessage(msg.hwnd, msg.message, msg.wParam, msg.lParam);
			}
			UpdateData(FALSE);
			SetDlgItemText(IDC_EDIT1, L"测试已经完成，准备上传资料...");
			//抓取A和B面所有result.log合并成一个Final_Result.log文件
			finfo.OnFileMergeAll(log_path_A, log_path_B, log_path_temp_result);
			;
			DeleteFile(log_path_A);
			DeleteFile(log_path_B);
			finfo.AddFileINI(log_path_temp_result, log_path_result);				//最终结果文件添加PASS/FAIL		
			DeleteFile(log_path_temp_result);
			ColorResultX = finfo.ReadFileFirstLine(log_path_result);

			if (ColorResultX.Mid(0, 4) == "PASS")
			{
				DisplayResult(ColorResultX);
			}
			else if (ColorResultX.Mid(0, 4) == "FAIL")
			{
				DisplayResult(ColorResultX);
			}
			GetDlgItem(IDC_EDIT5)->EnableWindow(TRUE);
			GetDlgItem(IDC_EDIT5)->SetWindowText(L"");
			GetDlgItem(IDC_EDIT5)->SetFocus();
			SetDlgItemText(IDC_EDIT1, L"测试完毕");
		}
	}
	else
	{
		AfxMessageBox(L"PCB必须是9位");
		loop2:
		loop22:

		GetDlgItem(IDC_EDIT5)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT5)->SetWindowText(L"");
		GetDlgItem(IDC_EDIT5)->SetFocus();
		
		EndResult_backColor = RGB(255, 255, 255);
		EndResult_backBrush.DeleteObject();
		EndResult_backBrush.CreateSolidBrush(EndResult_backColor);		//创建画刷
		GetDlgItem(IDC_STATIC_RESULT)->Invalidate();
		GetDlgItem(IDC_STATIC_RESULT)->SetWindowText(_T(""));
		SetDlgItemText(IDC_EDIT1, L"等待测试");
	}

	DeleteFile(log_path_result);//最终结果是否删除
	DeleteFile(mes_check_result_ini);


	SetTimer(4, 1000, NULL);
	GetDlgItem(IDC_EDIT5)->EnableWindow(TRUE);
//	SetTimer(6, 1000, NULL);
}

////B面函数体
//void CIntegrationDlg::BFuncCheck()
//{
//	HANDLE hThreadss;
//	DWORD ThreadID;
//	//读取特定内容
//	CString stritemb, strsoftwareb, strresultb;
//	int m_indexB = 0;
//	CString InformationStrB;
//	CString ColorResultB = L"";
//	//防止计数器卡死
//	hThreadss = CreateThread(0, 0, ThreadProcTime, this, 0, &ThreadID);
//	shellexe.TheadWait(hThreadss);
//
//	finfo.WriteFileToPath(path_AB, s_B);
//	for (int i = 0; i < rowsB; i++)
//	{
//		m_listB.SetItemText(i, 1, L"测试中...");
//		m_listB.SetItemText(i, 2, wait);
//		m_listB.SetItemData(i, COLOR_YELLOW);
//		InformationStrB.Format(_T("Information_%d"), m_indexB);
//		GetPrivateProfileString(InformationStrB, _T("Item"), CString("NULL"), stritemb.GetBuffer(MAX_PATH), MAX_PATH, PathB);
//		stritemb.ReleaseBuffer();
//		GetPrivateProfileString(InformationStrB, _T("Software"), CString("NULL"), strsoftwareb.GetBuffer(MAX_PATH), MAX_PATH, PathB);
//		strsoftwareb.ReleaseBuffer();
//		GetPrivateProfileString(InformationStrB, L"Result", CString("NULL"), strresultb.GetBuffer(MAX_PATH), MAX_PATH, PathB);
//		strresultb.ReleaseBuffer();
//		//string s = (LPCSTR)(CStringA)(stritemb);
//
//		loop11:
//		shellexe.OnOpenFile(strsoftwareb, NULL);	
//		ColorResultB = finfo.ReadFileFirstLine(strresultb);
//		if (ColorResultB.Mid(0, 4) == "pass")
//		{
//			m_listB.SetItemText(i, 1, L"测试完成");
//			m_listB.SetItemText(i, 2, pass);
//			m_listB.SetItemData(i, COLOR_GREEN);
//		}
//		else if (ColorResultB.Mid(0, 4) == "fail")
//		{
//			m_listB.SetItemText(i, 1, L"测试完成");
//			m_listB.SetItemText(i, 2, fail);
//			m_listB.SetItemData(i, COLOR_RED);
//			ModelErrorChooseDlg.DoModal();
//			/*
//				三种选择
//				one -> 当前重新测试一次
//				two -> 退出测试，并将UI界面置为初始，重新输入PCB
//				three -> 继续往下测试
//			*/
//			if (Choose == "one")
//			{
//				SetDlgItemText(IDC_EDIT1, L"选择重新测试");
//				DeleteFile(strresultb);
//				goto loop11;
//			}
//			else if (Choose == "two")
//			{
//				//GetDlgItem(IDC_EDIT5)->EnableWindow(TRUE);
//				//GetDlgItem(IDC_EDIT5)->SetWindowText(L"");
//				//GetDlgItem(IDC_EDIT5)->SetFocus();
//				//EndResult_backColor = RGB(255, 255, 255);
//				//EndResult_backBrush.DeleteObject();
//				//EndResult_backBrush.CreateSolidBrush(EndResult_backColor);		//创建画刷
//				//GetDlgItem(IDC_STATIC_RESULT)->Invalidate();
//				//GetDlgItem(IDC_STATIC_RESULT)->SetWindowText(_T(""));
//				//SetDlgItemText(IDC_EDIT1, L"选择退出测试");
//				DeleteFile(strresultb);
//				DeleteFile(log_path_B);
//				//break;
//				goto loop22;
//			}
//			else if (Choose == "three")
//			{
//				SetDlgItemText(IDC_EDIT1, L"选择继续测试");
//				goto loop33;
//			}
//		}
//		loop33:
//		m_indexB++;
//		finfo.OnFileMerge(GOODWAY, log_path_B);
//		OnDelFile(PathB);
//	}
//}


BOOL CIntegrationDlg::PreTranslateMessage(MSG* pMsg)
{
	CString PCB;
	// TODO: 在此添加专用代码和/或调用基类
	if (WM_KEYDOWN == pMsg->message && VK_RETURN == pMsg->wParam)
	{
		if (GetFocus() == GetDlgItem(IDC_EDIT5))
		{
			UpdateData(TRUE);
			m_edit_pcb.GetWindowText(PCB);
			IntegrationStart(PCB);
			UpdateData(FALSE);
		}
		return true;
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


void CIntegrationDlg::OnTimer(UINT_PTR nIDEvent)
{
	//HANDLE hThreadssCheck, hThreadssBCheckTime;
	//DWORD ThreadIDCheck, ThreadIDBCheckTime;
	//case1
	CString CDate;
	CString CTimers;
	//case2
	CString stra;
	int m_indexA = 0;
	CString InformationStrA;
	CString stritema, strsoftwarea;
	GetPrivateProfileStringW(_T("LIST"), _T("Rows"), CString("NULL"), stra.GetBuffer(MAX_PATH), MAX_PATH, PathA);
	CString strb;
	int m_indexB = 0;
	CString InformationStrB;
	CString stritemb, strsoftwareb;
	GetPrivateProfileString(_T("LIST"), _T("Rows"), CString("NULL"), strb.GetBuffer(MAX_PATH), MAX_PATH, PathB);
	strb.ReleaseBuffer();
	rowsB = _ttoi(strb);
	rowsA = _ttoi(stra);
	//case3

	static int nTimer = 0;
	CString strTmp = _T("");
	switch (nIDEvent)
	{
	case 1:
		CDate = CTime::GetCurrentTime().Format(_T("%Y年%m月%d日"));
		GetDlgItem(IDC_STATIC_TIME1)->SetWindowText(CDate);
		CTimers = CTime::GetCurrentTime().Format(_T("%H:%M:%S"));
		GetDlgItem(IDC_STATIC_TIME2)->SetWindowText(CTimers);
		break;
	case 2:
		EndResult_backColor = RGB(255, 255, 255);
		EndResult_backBrush.DeleteObject();
		EndResult_backBrush.CreateSolidBrush(EndResult_backColor);		//创建画刷
		GetDlgItem(IDC_STATIC_RESULT)->Invalidate();
		GetDlgItem(IDC_STATIC_RESULT)->SetWindowText(_T(""));
		for (int i = 0; i < rowsA; i++)
		{
			m_listA.SetItemData(i, COLOR_DEFAULT);
		}

		for (int i = 0; i < rowsB; i++)
		{
			m_listB.SetItemData(i, COLOR_DEFAULT);
		}
		KillTimer(2);
		break;
	case 3:
		strTmp.Format(_T("Time:%d"), nTimer++);
		GetDlgItem(IDC_STATIC_TIME)->SetWindowText(strTmp);
		break;
	case 4:
		nTimer = 0;
		KillTimer(3);
		KillTimer(4);
		break;
	case 5:
		KillTimer(5);
		keybd_event(13, 0, 0, 0);
		keybd_event(13, 0, KEYEVENTF_KEYUP, 0);
		break;
	case 6:
		if (DeviceRemovable == L"F")
		{
			EndResult_backColor = RGB(255, 255, 255);
			EndResult_backBrush.DeleteObject();
			EndResult_backBrush.CreateSolidBrush(EndResult_backColor);		//创建画刷
			GetDlgItem(IDC_STATIC_RESULT)->Invalidate();
			GetDlgItem(IDC_STATIC_RESULT)->SetWindowText(_T(""));
			for (int i = 0; i < rowsA; i++)
			{
				m_listA.SetItemData(i, COLOR_DEFAULT);
			}

			for (int i = 0; i < rowsB; i++)
			{
				m_listB.SetItemData(i, COLOR_DEFAULT);
			}
			KillTimer(6);
		}
		break;
	case 7:
		casen++;
		if (casen==10)
		{
			KillTimer(7);
		}
		break;
	default:
		break;
	}
	

	CDialogEx::OnTimer(nIDEvent);
}

//DWORD WINAPI ThreadProcCheck(LPVOID lpParameter)
//{
//	CIntegrationDlg *pDlg = (CIntegrationDlg*)lpParameter;
//	while (1)
//	{
//		if (pDlg->DeviceRemovable == L"T")
//		{
//			pDlg->BFuncCheck();
//			break;
//		}
//		if (pDlg->casen==10)
//		{
//			//AfxMessageBox(L"10");
//			pDlg->BFuncCheck();
//			break;
//		}
//
//	}
//	//MSG	msg;
//	//if (PeekMessage(&msg, (HWND)NULL, 0, 0, PM_REMOVE))
//	//{
//	//	::SendMessage(msg.hwnd, msg.message, msg.wParam, msg.lParam);
//	//}
//
//	return true;
//}

//DWORD WINAPI ThreadProcBCheckTime(LPVOID lpParameter)
//{
//	CIntegrationDlg *pDlg = (CIntegrationDlg*)lpParameter;
//	Sleep(15000);
//	MSG	msg;
//	if (PeekMessage(&msg, (HWND)NULL, 0, 0, PM_REMOVE))
//	{
//		::SendMessage(msg.hwnd, msg.message, msg.wParam, msg.lParam);
//	}
//	return true;
//}

DWORD WINAPI ThreadProcTime(LPVOID lpParameter)
{
	CIntegrationDlg *pDlg = (CIntegrationDlg*)lpParameter;
	//int n = finfo.ReadSetINI(pDlg->Configini);
	//Sleep(n);
	MSG	msg;
	if (PeekMessage(&msg, (HWND)NULL, 0, 0, PM_REMOVE))
	{
		::SendMessage(msg.hwnd, msg.message, msg.wParam, msg.lParam);
	}
	return true;
}


DWORD WINAPI ThreadProcPASS(LPVOID lpParameter)
{
	CIntegrationDlg *pDlg = (CIntegrationDlg*)lpParameter;
	CString upload_pass;
	CString strmes_pass;

	CString ss_null = L"";
	pDlg->m_edit_site.GetWindowTextW(pDlg->mes_site);
	pDlg->m_edit_user.GetWindowTextW(pDlg->mes_user);
	pDlg->m_edit_pcb.GetWindowText(pDlg->mes_pcb);
	pDlg->m_edit_equip.GetWindowTextW(pDlg->mes_equip);
	int linee = finfo.GetFileLine(_TEXT("C:\\GOODWAY\\Result.log"));
	CStdioFile file;
	CString szTemp, szA[1024], szB[1024];
	file.Open(L"C:\\GOODWAY\\Result.log", CFile::modeRead);
	file.ReadString(ss_null);

	for (int i = 0; file.ReadString(szTemp); i++)
	{
		szTemp.Delete(0, szTemp.Find(L"\t") + 1);
		szA[i] = szTemp.Mid(0, szTemp.Find(L"\t")).Trim();
		szB[i] = szTemp.Mid(szTemp.Find(L"\t") + 1).Trim();
		pDlg->CharToUTF8(szB[i]);
		if (szB[i] == szB[i + 1])
		{
			break;
		}
		MSG	msg;
		if (PeekMessage(&msg, (HWND)NULL, 0, 0, PM_REMOVE))
		{
			::SendMessage(msg.hwnd, msg.message, msg.wParam, msg.lParam);
		}
	}
	for (int i = 0; i < linee - 1; i++)
	{
		MEScheck.SaveLogToMES(pDlg->mes_site, pDlg->mes_user, pDlg->mes_pcb, pDlg->mes_equip, _TEXT(""), szB[i]);
		MSG	msg;
		if (PeekMessage(&msg, (HWND)NULL, 0, 0, PM_REMOVE))
		{
			::SendMessage(msg.hwnd, msg.message, msg.wParam, msg.lParam);
		}
	}
	file.Close();
	upload_pass = MEScheck.ResultToMES(pDlg->mes_site, pDlg->mes_user, pDlg->mes_pcb, pDlg->mes_equip, _TEXT(""), _TEXT("AutoTest_Pass"));
	WritePrivateProfileString(L"MESRESULT", L"result", upload_pass, pDlg->mes_check_result_ini);

	return 0;
}

DWORD WINAPI ThreadProcFAIL(LPVOID lpParameter)
{
	CIntegrationDlg *pDlg = (CIntegrationDlg*)lpParameter;
	CString upload_fail;
	CString defect_fail;
	defect_fail = finfo.DefectFileRead(pDlg->log_path_result);
	CString ss_null = L"";
	pDlg->m_edit_site.GetWindowTextW(pDlg->mes_site);
	pDlg->m_edit_user.GetWindowTextW(pDlg->mes_user);
	pDlg->m_edit_pcb.GetWindowText(pDlg->mes_pcb);
	pDlg->m_edit_equip.GetWindowTextW(pDlg->mes_equip);
	int linee = finfo.GetFileLine(_TEXT("C:\\GOODWAY\\Result.log"));
	CStdioFile file;
	CString szTemp, szA[1024], szB[1024];
	file.Open(L"C:\\GOODWAY\\Result.log", CFile::modeRead);
	file.ReadString(ss_null);

	for (int i = 0; file.ReadString(szTemp); i++)
	{
		szTemp.Delete(0, szTemp.Find(L"\t") + 1);
		szA[i] = szTemp.Mid(0, szTemp.Find(L"\t")).Trim();
		szB[i] = szTemp.Mid(szTemp.Find(L"\t") + 1).Trim();
		pDlg->CharToUTF8(szB[i]);
		if (szB[i] == szB[i + 1])
		{
			break;
		}
		MSG	msg;
		if (PeekMessage(&msg, (HWND)NULL, 0, 0, PM_REMOVE))
		{
			::SendMessage(msg.hwnd, msg.message, msg.wParam, msg.lParam);
		}
	}
	for (int i = 0; i < linee - 1; i++)
	{
		MEScheck.SaveLogToMES(pDlg->mes_site, pDlg->mes_user, pDlg->mes_pcb, pDlg->mes_equip, defect_fail, szB[i]);
		MSG	msg;
		if (PeekMessage(&msg, (HWND)NULL, 0, 0, PM_REMOVE))
		{
			::SendMessage(msg.hwnd, msg.message, msg.wParam, msg.lParam);
		}
	}
	file.Close();
	upload_fail = MEScheck.ResultToMES(pDlg->mes_site, pDlg->mes_user, pDlg->mes_pcb, pDlg->mes_equip, defect_fail, _TEXT("AutoTest_Fail"));
	WritePrivateProfileString(L"MESRESULT", L"result", upload_fail, pDlg->mes_check_result_ini);
	return 0;
}

void CIntegrationDlg::CharToUTF8(CString &str)
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


void CIntegrationDlg::OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	//LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	NM_LISTVIEW *pNMListView = (NM_LISTVIEW *)pNMHDR;

	//UpdateData(TRUE);
	CString stritema, strsoftwarea, strresulta;
	CString InformationStrA;
	CString ColorResultA = L"";


	int nItem = pNMListView->iItem;
	if (nItem >= 0 && nItem < m_listA.GetItemCount())//判断双击位置是否在有数据的列表项上面
	{
		m_listA.SetItemText(nItem, 1, L"测试中...");
		m_listA.SetItemText(nItem, 2, wait);
		m_listA.SetItemData(nItem, COLOR_YELLOW);
		InformationStrA.Format(_T("Information_%d"), nItem);
		GetPrivateProfileString(InformationStrA, L"Item", L"", stritema.GetBuffer(MAX_PATH), MAX_PATH, PathA);		//read Item name
		stritema.ReleaseBuffer();
		GetPrivateProfileString(InformationStrA, L"Software", L"", strsoftwarea.GetBuffer(MAX_PATH), MAX_PATH, PathA);		//read Software path 
		strsoftwarea.ReleaseBuffer();
		GetPrivateProfileString(InformationStrA, L"Result", L"", strresulta.GetBuffer(MAX_PATH), MAX_PATH, PathA);		//read Result path 
		strresulta.ReleaseBuffer();

		shellexe.OnOpenFile(strsoftwarea, NULL);
		ColorResultA = finfo.ReadFileFirstLine(strresulta);
		if (ColorResultA.Mid(0, 4) == "pass")
		{
			m_listA.SetItemText(nItem, 1, L"测试完成");
			m_listA.SetItemText(nItem, 2, pass);
			m_listA.SetItemData(nItem, COLOR_GREEN);
		}
		else if (ColorResultA.Mid(0, 4) == "fail")
		{
			m_listA.SetItemText(nItem, 1, L"测试完成");
			m_listA.SetItemText(nItem, 2, fail);
			m_listA.SetItemData(nItem, COLOR_RED);
		}
	}
	this->m_listA.SetItemState(nItem, 0, -1);//取消选中（高亮）
	OnDelFile(PathA);
	*pResult = 0;
}


void CIntegrationDlg::OnNMDblclkList2(NMHDR *pNMHDR, LRESULT *pResult)
{
	NM_LISTVIEW *pNMListView = (NM_LISTVIEW *)pNMHDR;

	//UpdateData(TRUE);
	CString stritemb, strsoftwareb, strresultb;
	CString InformationStrB;
	CString ColorResultB = L"";


	int nItem = pNMListView->iItem;
	if (nItem >= 0 && nItem < m_listB.GetItemCount())//判断双击位置是否在有数据的列表项上面
	{
		m_listB.SetItemText(nItem, 1, L"测试中...");
		m_listB.SetItemText(nItem, 2, wait);
		m_listB.SetItemData(nItem, COLOR_YELLOW);
		InformationStrB.Format(_T("Information_%d"), nItem);
		GetPrivateProfileString(InformationStrB, L"Item", L"", stritemb.GetBuffer(MAX_PATH), MAX_PATH, PathB);		//read Item name
		stritemb.ReleaseBuffer();
		GetPrivateProfileString(InformationStrB, L"Software", L"", strsoftwareb.GetBuffer(MAX_PATH), MAX_PATH, PathB);		//read Software path 
		strsoftwareb.ReleaseBuffer();
		GetPrivateProfileString(InformationStrB, L"Result", L"", strresultb.GetBuffer(MAX_PATH), MAX_PATH, PathB);		//read Result path 
		strresultb.ReleaseBuffer();

		shellexe.OnOpenFile(strsoftwareb, NULL);
		ColorResultB = finfo.ReadFileFirstLine(strresultb);
		if (ColorResultB.Mid(0, 4) == "pass")
		{
			m_listB.SetItemText(nItem, 1, L"测试完成");
			m_listB.SetItemText(nItem, 2, pass);
			m_listB.SetItemData(nItem, COLOR_GREEN);
		}
		else if (ColorResultB.Mid(0, 4) == "fail")
		{
			m_listB.SetItemText(nItem, 1, L"测试完成");
			m_listB.SetItemText(nItem, 2, fail);
			m_listB.SetItemData(nItem, COLOR_RED);
		}
	}
	this->m_listB.SetItemState(nItem, 0, -1);//取消选中（高亮）
	OnDelFile(PathB);
	*pResult = 0;
}

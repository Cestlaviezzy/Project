
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
#include "WindowTips.h"


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
//login loginDlg;
//MESCheck MEScheck;
//MESconnect MESconDlg;
CString EXEPATH;
WindowTips WindowTipsDlg;
CWinThread* pWinThread;
CString TM; //获取系统时间 　　
CTime tm; 
CString str;


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
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
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
}

BEGIN_MESSAGE_MAP(CIntegrationDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_32778, &CIntegrationDlg::OnconfigPage)
	ON_BN_CLICKED(IDC_BUTTON1, &CIntegrationDlg::OnBnClickedButton1)
	ON_WM_CTLCOLOR()
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_LIST1, &CIntegrationDlg::OnNMCustomdrawList1)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_LIST2, &CIntegrationDlg::OnNMCustomdrawList2)
//	ON_BN_CLICKED(IDC_RADIO1, &CIntegrationDlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CIntegrationDlg::OnBnClickedRadio2)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON3, &CIntegrationDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON2, &CIntegrationDlg::OnBnClickedButton2)
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
	m_font_result.CreatePointFont(1000, L"微软雅黑");//代表15号字体，华文行楷
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

	//设置radio初始状态
	CButton* radio = (CButton*)GetDlgItem(IDC_RADIO2);
	radio->SetCheck(0);
	GetDlgItem(IDC_BUTTON1)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT5)->EnableWindow(TRUE);
	SetDlgItemText(IDC_EDIT1, L"请选择MES状态");

	//设置菜单栏
	CMenu mmenu;
	mmenu.LoadMenu(IDR_MENU1);  //IDR_MENU1为菜单栏ID号
	SetMenu(&mmenu);

	//设置时间
	CString strTime;
	CTime tm;
	tm = CTime::GetCurrentTime();         //获取当前系统时间
	strTime = tm.Format("%y年%m月%d日 %X");   //格式化系统时间。即使系统时 间按照Format中设置的格式显示
	SetDlgItemText(IDC_EDIT6, strTime);        //初始化编辑框显示
	SetTimer(1, 1000, NULL);         //启动定时器

	//设置焦点
	GetDlgItem(IDC_EDIT5)->SetFocus();
	//return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE

	TCHAR path[MAX_PATH] = { 0 };
	GetModuleFileName(NULL, path, MAX_PATH);
	(_tcsrchr(path, _T('\\')))[1] = 0;
	EXEPATH = path;//此时获得了EXE的目录

	pWinThread = AfxBeginThread((AFX_THREADPROC)MyThread, this, THREAD_PRIORITY_NORMAL, 0, 0);

	return FALSE;
}

void CIntegrationDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else if ((nID & 0xFFF0) == SC_CLOSE)		//右上角X  
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
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
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
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CIntegrationDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



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
	switch (nmCustomDraw.dwDrawStage)
	{
	case CDDS_ITEMPREPAINT:
	{
		if (COLOR_GREEN == nmCustomDraw.lItemlParam)
		{
			pNMCD->clrTextBk = RGB(0, 255, 0);
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

void CIntegrationDlg::OnNMCustomdrawList2(NMHDR *pNMHDR, LRESULT *pResult)
{
	//LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	NMLVCUSTOMDRAW* pNMCD = reinterpret_cast<NMLVCUSTOMDRAW*>(pNMHDR);
	NMCUSTOMDRAW nmCustomDraw = pNMCD->nmcd;
	int nItem = static_cast<int>(pNMCD->nmcd.dwItemSpec);
	switch (nmCustomDraw.dwDrawStage)
	{
	case CDDS_ITEMPREPAINT:
	{
		if (COLOR_GREEN == nmCustomDraw.lItemlParam)
		{
			pNMCD->clrTextBk = RGB(0, 255, 0);
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
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}

void CIntegrationDlg::DisplayResult(CString Result)
{
	if ((Result.Mid(0, 4)) == "PASS")
	{
		m_MES_result.SetWindowTextW(_T("Pass"));
		EndResult_textColor = RGB(0, 0, 0);
		EndResult_backColor = RGB(0, 255, 0);
	}
	else if (Result.Mid(0, 4) == "FAIL")
	{
		m_MES_result.SetWindowTextW(_T("Fail"));
		EndResult_textColor = RGB(0, 0, 0);
		EndResult_backColor = RGB(255, 0, 0);
	}
	else //if (Result.Mid(0, 4) == "WAIT")
	{
		m_MES_result.SetWindowTextW(_T("Wait"));
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

/******************Check MES Connect**********************/
//void CIntegrationDlg::OnBnClickedRadio1()
//{
//	// TODO: 在此添加控件通知处理程序代码
//	CString MES_site = _T("A2010A1");
//	Genesis::Gtimes::Interface::EquipLinkMes ^site = gcnew Genesis::Gtimes::Interface::EquipLinkMes;
//	System::String ^put_site = gcnew String(MES_site);
//	CString MES_SITE = site->CheckSite(put_site);
//	string login_site = (LPCSTR)(CStringA)(MES_SITE);
//	UpdateData(TRUE);
//	RadioState_Green = ((CButton *)GetDlgItem(IDC_RADIO1))->GetCheck();
//	if ((RadioState_Green = 1) && (MES_SITE == "T")) {
//		//GetDlgItem(IDC_BUTTON1)->EnableWindow(TRUE);
//		GetDlgItem(IDC_EDIT5)->EnableWindow(TRUE);
//		GetDlgItem(IDC_EDIT5)->SetFocus();
//		SetDlgItemText(IDC_EDIT1, L"连接MES成功");
//		SelectPic(Green_pic);
//		loginDlg.DoModal();
//		m_edit_site.SetWindowText(loginDlg.Site);
//		m_edit_user.SetWindowText(loginDlg.User);
//		m_edit_equip.SetWindowText(loginDlg.Equip1);
//	}
//	else if ((RadioState_Green = 1) && (MES_SITE != "T"))
//	{
//		//GetDlgItem(IDC_BUTTON1)->EnableWindow(FALSE);
//		GetDlgItem(IDC_EDIT5)->EnableWindow(FALSE);
//		SetDlgItemText(IDC_EDIT1, L"连接MES失败");
//		SelectPic(Red_pic);
//		AfxMessageBox(_T("连接失败或者没有连接到MES专用网络"));
//		((CButton *)GetDlgItem(IDC_RADIO1))->SetCheck(0);
//	}
//}


void CIntegrationDlg::OnBnClickedRadio2()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	//RadioState_Yellow = ((CButton *)GetDlgItem(IDC_RADIO2))->GetCheck();

	//MESconDlg.DoModal();
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

}

int CIntegrationDlg::GetFileLine(CString road)
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
CString CIntegrationDlg::ReadFileALL(CString path)
{
	CStdioFile file;
	CString arry[1000];
	CString all_result;
	int line = GetFileLine(path);
	if (file.Open(path, CFile::modeRead))
	{
		for (int i = 0; i < line; i++)
		{
			file.ReadString(arry[i]);
			all_result += arry[i] + L"\n";
			all_result.Replace(L" ", L"");
		}
		file.Close();
		return all_result;
	}
	else
	{
		AfxMessageBox(L"1.文件不存在");
	}
}

//将数据项写入CSV文件
int CIntegrationDlg::PutCSVItemLine(FILE *file, CStringArray &sItemLine)
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

void CIntegrationDlg::TestCSV(CString Item, CString Result)
{
	tm = CTime::GetCurrentTime();
	//TM = tm.Format("%Y%m%d% X");
	TM = tm.Format("现在时间是%Y年%m月%d日 %X");
	FILE *f = NULL;
	if (_tfopen_s(&f, _T("C:\\test.csv"), _T("a+b")) == 0)		//w write  b bin
	{
		CStringArray sLine;
		sLine.Add(TM);
		sLine.Add(Item);
		sLine.Add(Result);

		PutCSVItemLine(f, sLine);
		fclose(f);
	}
}

UINT CIntegrationDlg::MyThread(LPVOID pParam)
{
	CIntegrationDlg *pDlg = (CIntegrationDlg*)pParam;
	CString cyclenumber;
	CString exewaittime;

	

	GetPrivateProfileString(_T("CysleMunber"), _T("num"), CString("NULL"), cyclenumber.GetBuffer(MAX_PATH), MAX_PATH, pDlg->Configini);
	GetPrivateProfileString(_T("WaitTime"), _T("ExeWaitTime"), CString("NULL"), exewaittime.GetBuffer(MAX_PATH), MAX_PATH, pDlg->Configini);
	CString Item;
	int n;
	int i = 1;
	int num;
	num = _ttoi(cyclenumber);
	n = _ttoi(exewaittime);
	CString Result; 

	while (i != (num+1))
	{
		Sleep(n);
		Item.Format(L"%d", i);
		pDlg->IntegrationStart(L"123456789");					//运行程序
		Result = pDlg->ReadFileALL(pDlg->log_path_result);		//读取日志
		finfo.CharToUTF8(Result);
		pDlg->TestCSV(Item, Result);							//写入CSV
		DeleteFile(pDlg->log_path_result);						//删除日志

		i++;
	}
	return 0;
}

void CIntegrationDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	pWinThread->SuspendThread();		//挂起
}
void CIntegrationDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	OnDelFile(PathA);
	OnDelFile(PathB);
	DeleteFile(log_path_A);		//删除A面结果日志
	DeleteFile(log_path_B);		//删除B面结果日志
	DeleteFile(path_AB);		//删除AB.txt文件
}


void CIntegrationDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码

	pWinThread->ResumeThread();		//继续
}

void CIntegrationDlg::IntegrationStart(CString PCB)
{
	GetDlgItem(IDC_EDIT5)->SetWindowText(L"123456789");
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
	CString defect_pass = L"";
	CString defect_fail;
	CString MES_PCB_RESULT;
	//PCB check
	m_edit_pcb.GetWindowText(PCB);
	//if (((CButton *)GetDlgItem(IDC_RADIO1))->GetCheck())
	//{
	//	Genesis::Gtimes::Interface::EquipLinkMes ^sendresulttomes = gcnew Genesis::Gtimes::Interface::EquipLinkMes;
	//	System::String^ put_site = gcnew String(loginDlg.Site);
	//	System::String^ put_pcb = gcnew String(PCB);
	//	MES_PCB_RESULT = sendresulttomes->CheckPCB(put_site, put_pcb);
	//	string mes_pcb_result = (LPCSTR)(CStringA)(MES_PCB_RESULT);

	//	if (!(mes_pcb_result == "T"))
	//	{
	//		AfxMessageBox(MES_PCB_RESULT);
	//		return;
	//	}
	//}
	//else
	//{
	//	Sleep(1);
	//}
	//程序开始
	if (PCB.GetLength() == 9)
	{
		//界面初始化
		DisplayResult(L"");
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
		//左下角result变化
		//DisplayResult(L"");
		//start 生成AB.txt文件
		//A面全运行一次
		finfo.WriteFileToPath(path_AB, s_A);
		for (int i = 0; i < rowsA; i++)
		{
			m_listA.SetItemText(i, 1, L"测试中...");
			m_listA.SetItemText(i, 2, wait);
			m_listA.SetItemData(i, COLOR_YELLOW);
			InformationStrA.Format(_T("Information_%d"), m_indexA);
			GetPrivateProfileString(InformationStrA, L"Item", L"", stritema.GetBuffer(MAX_PATH), MAX_PATH, PathA);		//read Item name
			GetPrivateProfileString(InformationStrA, L"Software", L"", strsoftwarea.GetBuffer(MAX_PATH), MAX_PATH, PathA);		//read Software path 
			GetPrivateProfileString(InformationStrA, L"Result", L"", strresulta.GetBuffer(MAX_PATH), MAX_PATH, PathA);		//read Result path 
			
			//进程
			shellexe.OnOpenFile(strsoftwarea, NULL);
			//线程
			ColorResultA = finfo.ReadFileFirstLine(strresulta);
			if (ColorResultA.Mid(0, 4) == "PASS")
			{
				m_listA.SetItemText(i, 1, L"测试完成");
				m_listA.SetItemText(i, 2, pass);
				m_listA.SetItemData(i, COLOR_GREEN);
			}
			else if (ColorResultA.Mid(0, 4) == "FAIL")
			{
				m_listA.SetItemText(i, 1, L"测试完成");
				m_listA.SetItemText(i, 2, fail);
				m_listA.SetItemData(i, COLOR_RED);
			}
			m_indexA++;
		}
		DeleteFile(path_AB);		//A面全运行完，删除A面文档
		finfo.OnFileMerge(GOODWAY, log_path_A);		//Param1 在哪个目录下抓取， Param2 抓取结果生成在什么路径上。  
		/****删除A面的result.log***/
		OnDelFile(PathA);
		//查找B面ini文件是否存在，存在就运行，不存在跳出结束

		int n = finfo.ReadSetINI(Configini);
		Sleep(n);

		if (ifFind)
		{
			finder.Close();
			//keybd_event(13, 0, 0, 0);
			//Sleep(200);
			//keybd_event(13, 0, KEYEVENTF_KEYUP, 0);
			//AfxMessageBox(L"换面");


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

				//进程
				shellexe.OnOpenFile(strsoftwareb, NULL);
				//线程
				

				ColorResultB = finfo.ReadFileFirstLine(strresultb);
				if (ColorResultB.Mid(0, 4) == "PASS")
				{
					m_listB.SetItemText(i, 1, L"测试完成");
					m_listB.SetItemText(i, 2, pass);
					m_listB.SetItemData(i, COLOR_GREEN);
				}
				else if (ColorResultB.Mid(0, 4) == "FAIL")
				{
					m_listB.SetItemText(i, 1, L"测试完成");
					m_listB.SetItemText(i, 2, fail);
					m_listB.SetItemData(i, COLOR_RED);
				}
				m_indexB++;
			}
			DeleteFile(path_AB);	//删除AB.txt
			finfo.OnFileMerge(GOODWAY, log_path_B);
			OnDelFile(PathB);
		}
		else
		{
			Sleep(1);
		}
		//抓取A和B面所有result.log合并成一个Final_Result.log文件
		finfo.OnFileMergeAll(log_path_A, log_path_B, log_path_temp_result);

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
		/*****上传MES*****/
		/*********先获取控件的值*********/
		//CString cc;
		//int ccnum;
		//GetPrivateProfileStringW(_T("WindowTips"), _T("Set"), CString("NULL"), cc.GetBuffer(MAX_PATH), MAX_PATH, Configini);
		//ccnum = _ttoi(cc);

		//if (((CButton *)GetDlgItem(IDC_RADIO1))->GetCheck())
		//{
		//	//过站提醒
		//	//if ((ccnum == 1))
		//	if ((ccnum == 1) && ((ColorResultX.Mid(0, 4) == "FAIL")))
		//	{
		//		//弹窗提醒
		//		WindowTipsDlg.DoModal();
		//		if (TF == 1)
		//		{
		//			SetDlgItemText(IDC_EDIT1, L"数据上传MES中...");
		//			if (ColorResultX.Mid(0, 4) == "PASS")
		//			{
		//				result_pass = finfo.ReadFileALL(log_path_result);
		//				upload_pass = MEScheck.ResultToMES(loginDlg.Site, loginDlg.User, pcb_r, loginDlg.Equip1, defect_pass, result_pass);
		//				//AfxMessageBox(upload_pass);
		//				string up_pass = (LPCSTR)(CStringA)(upload_pass);
		//				if (up_pass == "T")
		//				{
		//					SetDlgItemText(IDC_EDIT1, L"p.上传MES成功");
		//					DisplayResult(ColorResultX);
		//				}
		//				else
		//				{
		//					SetDlgItemText(IDC_EDIT1, L"p.上传MES失败");
		//					DisplayResult(L"FAIL");
		//				}
		//			}
		//			else if (ColorResultX.Mid(0, 4) == "FAIL")
		//			{
		//				//需要一个将不良代码合并的函数  返回总的defect
		//				defect_fail = finfo.DefectFileRead(log_path_result);
		//				result_fail = finfo.ReadFileALL(log_path_result);
		//				upload_fail = MEScheck.ResultToMES(loginDlg.Site, loginDlg.User, pcb_r, loginDlg.Equip1, defect_fail, result_fail);
		//				//AfxMessageBox(defect_fail);
		//				string up_fail = (LPCSTR)(CStringA)(upload_fail);
		//				if (up_fail == "T")
		//				{
		//					SetDlgItemText(IDC_EDIT1, L"f.上传MES成功");
		//					DisplayResult(ColorResultX);
		//				}
		//				else
		//				{
		//					SetDlgItemText(IDC_EDIT1, L"f.上传MES失败");
		//					DisplayResult(ColorResultX);
		//				}
		//			}
		//		}
		//		else
		//		{
		//			DeleteFile(log_path_result);
		//			SetDlgItemText(IDC_EDIT1, L"选择不上传重新测试");
		//			GetDlgItem(IDC_EDIT5)->SetWindowText(L"");
		//		}
		//	}
		//	else
		//	{
		//		SetDlgItemText(IDC_EDIT1, L"数据上传MES中...");
		//		if (ColorResultX.Mid(0, 4) == "PASS")
		//		{
		//			result_pass = finfo.ReadFileALL(log_path_result);
		//			upload_pass = MEScheck.ResultToMES(loginDlg.Site, loginDlg.User, pcb_r, loginDlg.Equip1, defect_pass, result_pass);
		//			//AfxMessageBox(upload_pass);
		//			string up_pass = (LPCSTR)(CStringA)(upload_pass);
		//			if (up_pass == "T")
		//			{
		//				SetDlgItemText(IDC_EDIT1, L"p.上传MES成功");
		//				DisplayResult(ColorResultX);
		//			}
		//			else
		//			{
		//				SetDlgItemText(IDC_EDIT1, L"p.上传MES失败");
		//				DisplayResult(L"FAIL");
		//			}
		//		}
		//		else if (ColorResultX.Mid(0, 4) == "FAIL")
		//		{
		//			//需要一个将不良代码合并的函数  返回总的defect
		//			defect_fail = finfo.DefectFileRead(log_path_result);
		//			result_fail = finfo.ReadFileALL(log_path_result);
		//			upload_fail = MEScheck.ResultToMES(loginDlg.Site, loginDlg.User, pcb_r, loginDlg.Equip1, defect_fail, result_fail);
		//			//AfxMessageBox(defect_fail);
		//			string up_fail = (LPCSTR)(CStringA)(upload_fail);
		//			if (up_fail == "T")
		//			{
		//				SetDlgItemText(IDC_EDIT1, L"f.上传MES成功");
		//				DisplayResult(ColorResultX);
		//			}
		//			else
		//			{
		//				SetDlgItemText(IDC_EDIT1, L"f.上传MES失败");
		//				DisplayResult(ColorResultX);
		//			}

		//		}
		//	}

		//}
		//else if (((CButton *)GetDlgItem(IDC_RADIO2))->GetCheck())		//不连接MES测试
		//{
		//	if (ColorResultX.Mid(0, 4) == "PASS")
		//	{
		//		DisplayResult(ColorResultX);
		//	}
		//	else if (ColorResultX.Mid(0, 4) == "FAIL")
		//	{
		//		DisplayResult(ColorResultX);
		//	}
		//}
	}
	else
	{
		AfxMessageBox(L"PCB必须是9位");
	}
	
	//DeleteFile(log_path_result);
	//SetDlgItemText(IDC_EDIT1, L"OK");
	//m_edit_pcb.Clear();
	//GetDlgItem(IDC_EDIT5)->SetWindowText(L"");
}

//BOOL CIntegrationDlg::PreTranslateMessage(MSG* pMsg)
//{
//	CString PCB;
//	// TODO: 在此添加专用代码和/或调用基类
//	if (WM_KEYDOWN == pMsg->message && VK_RETURN == pMsg->wParam)
//	{
//		if (GetFocus() == GetDlgItem(IDC_EDIT5))
//		{
//			UpdateData(TRUE);
//			m_edit_pcb.GetWindowText(PCB);
//			IntegrationStart(PCB);
//			UpdateData(FALSE);
//		}
//		return true;
//	}
//	return CDialogEx::PreTranslateMessage(pMsg);
//}




void CIntegrationDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CString strTime;
	CTime tm;
	tm = CTime::GetCurrentTime();
	strTime = tm.Format("%Y-%m-%d %H:%M:%S:%A");
	SetDlgItemText(IDC_EDIT6, strTime);        //显示系统时间

	CDialogEx::OnTimer(nIDEvent);
}
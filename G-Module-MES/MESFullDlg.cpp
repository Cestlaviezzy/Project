
// MESFullDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MESFull.h"
#include "MESFullDlg.h"
#include "afxdialogex.h"
#include "MesDll.h"
#include <string>
#include "MesFile.h"

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

MesDll MesDLLDlg;
MesFile MesFileDlg;
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


// CMESFullDlg 对话框



CMESFullDlg::CMESFullDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MESFULL_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMESFullDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_edit1);
	DDX_Control(pDX, IDC_EDIT2, m_edit2);
	DDX_Control(pDX, IDC_EDIT3, m_edit3);
	DDX_Control(pDX, IDC_EDIT4, m_edit4);
	DDX_Control(pDX, IDC_EDIT5, m_edit5);
	DDX_Control(pDX, IDC_EDIT6, m_edit6);
	DDX_Control(pDX, IDC_EDIT7, m_edit7);
	DDX_Control(pDX, IDC_EDIT8, m_edit8);
	DDX_Control(pDX, IDC_EDIT9, m_edit9);
	DDX_Control(pDX, IDC_EDIT10, m_edit10);
	DDX_Control(pDX, IDC_EDIT11, m_edit11);
	DDX_Control(pDX, IDC_EDIT12, m_edit12);
	DDX_Control(pDX, IDC_EDIT13, m_edit13);
}

BEGIN_MESSAGE_MAP(CMESFullDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMESFullDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMESFullDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CMESFullDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CMESFullDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON6, &CMESFullDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &CMESFullDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &CMESFullDlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON9, &CMESFullDlg::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON10, &CMESFullDlg::OnBnClickedButton10)
	ON_BN_CLICKED(IDC_BUTTON11, &CMESFullDlg::OnBnClickedButton11)
	ON_BN_CLICKED(IDC_BUTTON5, &CMESFullDlg::OnBnClickedButton5)
END_MESSAGE_MAP()


// CMESFullDlg 消息处理程序

BOOL CMESFullDlg::OnInitDialog()
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
	m_edit1.SetWindowText(_T("A2010A1"));
	m_edit2.SetWindowText(_T("G08694"));
	m_edit4.SetWindowText(_T("200000000116"));
//	m_edit6.SetWindowText(_T(""));
//	m_edit7.SetWindowText(_T("AuToTestPass"));
	
	m_edit8.SetWindowText(_T("A2010A1"));
	m_edit9.SetWindowText(_T("G08694"));

//	GetDlgItem(IDC_BUTTON5)->EnableWindow(FALSE);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMESFullDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMESFullDlg::OnPaint()
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
HCURSOR CMESFullDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMESFullDlg::OnBnClickedButton1()
{
	//site
	CString site;
	CString result;
	m_edit1.GetWindowText(site);
	result = MesDLLDlg.CheckSite(site);
	AfxMessageBox(result);
}


void CMESFullDlg::OnBnClickedButton2()
{
	//user
	CString site, user;
	CString result;
	m_edit1.GetWindowText(site);
	m_edit2.GetWindowText(user);
	result = MesDLLDlg.CheckUser(site, user);
	AfxMessageBox(result);
}


void CMESFullDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	CString site, pcb;
	CString result;
	m_edit1.GetWindowText(site);
	m_edit3.GetWindowText(pcb);
	result = MesDLLDlg.CheckPCB(site, pcb);
	AfxMessageBox(result);
}


void CMESFullDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	CString site, pcb, num;
	CString number, result;
	m_edit1.GetWindowText(site);
	m_edit3.GetWindowText(pcb);
	m_edit5.GetWindowText(num);
	number = MesDLLDlg.CheckNumber(site, pcb);

	result = number.Left(number.Find(_T(",")));

	if (result == num)
	{
		AfxMessageBox(L"工单一致");
	}
	else
	{
		AfxMessageBox(L"工单不一致\n" + L"当前输入工单：" + num + L"\n" + L"输入PCB工单：" + result);
	}
}


void CMESFullDlg::OnBnClickedButton6()
{
	//Save Log
	CString site, user, equip, pcb, defect, result;
	CString res;
	m_edit1.GetWindowText(site);
	m_edit2.GetWindowText(user);
	m_edit3.GetWindowText(pcb);
	m_edit4.GetWindowText(equip);
	m_edit6.GetWindowText(defect);
	m_edit7.GetWindowText(result);
	res = MesDLLDlg.MESToSave(site, user, pcb, equip, defect, result);
	AfxMessageBox(res);
}


void CMESFullDlg::OnBnClickedButton7()
{
	//过站
	CString site, user, equip, pcb, defect, result;
	CString res;
	m_edit1.GetWindowText(site);
	m_edit2.GetWindowText(user);
	m_edit3.GetWindowText(pcb);
	m_edit4.GetWindowText(equip);
	m_edit6.GetWindowText(defect);
	m_edit7.GetWindowText(result);
	res = MesDLLDlg.MESToStation(site, user, pcb, equip, defect, result);
	AfxMessageBox(res);
}


/////////////////////////////////////////////////////////////////////////////////////////////
void CMESFullDlg::OnBnClickedButton8()
{
	// TODO: 在此添加控件通知处理程序代码
	CString site;
	CString result;
	m_edit8.GetWindowText(site);
	result = MesDLLDlg.CheckSite(site);
	AfxMessageBox(result);
}


void CMESFullDlg::OnBnClickedButton9()
{
	// TODO: 在此添加控件通知处理程序代码
	CString site, user;
	CString result;
	m_edit8.GetWindowText(site);
	m_edit9.GetWindowText(user);
	result = MesDLLDlg.CheckUser(site, user);
	AfxMessageBox(result);
}


void CMESFullDlg::OnBnClickedButton10()
{
	// TODO: 在此添加控件通知处理程序代码
	CString pcb;
	CString result;
	m_edit10.GetWindowText(pcb);
	result = MesDLLDlg.CheckPCBisExist(pcb);
	AfxMessageBox(result);
}


void CMESFullDlg::OnBnClickedButton11()
{
	// TODO: 在此添加控件通知处理程序代码
	CString site, user, pcb, SN, MAC, Packageing;
	CString result;
	m_edit8.GetWindowText(site);
	m_edit9.GetWindowText(user);
	m_edit10.GetWindowText(pcb);
	m_edit11.GetWindowText(SN);
	m_edit12.GetWindowText(MAC);
	m_edit13.GetWindowText(Packageing);
	result = MesDLLDlg.MESNewDLL(site, user, pcb, SN, MAC, Packageing);
	AfxMessageBox(result);
}


void CMESFullDlg::OnBnClickedButton5()
{
	//选择结果文件
	CString MesResult;
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("All Files(*.*)|*.*|(*.*)|*.*|"), NULL);
	if (dlg.DoModal())
	{
		CString s = dlg.GetPathName();
		s.Replace(L"\\", L"\\\\");		//	替换
		//s.Replace(L" ", L"");
		MesResult = s;
	}
	SetDlgItemText(IDC_EDIT7, MesResult);
	
	CString result = MesFileDlg.ReadFileALL(MesResult);
	MesFileDlg.CharToUTF8(result);

	SetDlgItemText(IDC_EDIT7, result);
}

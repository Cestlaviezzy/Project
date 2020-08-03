// login.cpp: 实现文件
//

#include "pch.h"
#include "BurnProcess.h"
#include "login.h"
#include "afxdialogex.h"
#include "BurnProcessDlg.h"
#include <string>

#using "..\\Debug\\EquipLinkMes.dll"

using namespace System;
using namespace std;

// login 对话框

IMPLEMENT_DYNAMIC(login, CDialogEx)

login::login(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

login::~login()
{
}

void login::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_edit_site);
	DDX_Control(pDX, IDC_EDIT2, m_edit_user);
	DDX_Control(pDX, IDC_EDIT3, m_edit_number);
	DDX_Control(pDX, IDC_EDIT4, m_edit_equip);
	DDX_Control(pDX, IDC_STATIC_SITE, m_static_site);
	DDX_Control(pDX, IDC_STATIC_USER, m_static_user);
	DDX_Control(pDX, IDC_STATIC_NUMBER, m_static_number);
	DDX_Control(pDX, IDC_STATIC_EQUIP, m_static_equip);
	DDX_Control(pDX, IDC_BUTTON1, m_button1);
	DDX_Control(pDX, IDC_EDIT5, m_edit5);
//	DDX_Control(pDX, IDC_EDIT6, m_edit6);
	DDX_Control(pDX, IDC_STATIC_MACMAX, m_static_macmax);
//	DDX_Control(pDX, IDC_STATIC_DEVMAX, m_static_devmax);
}


BEGIN_MESSAGE_MAP(login, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &login::OnBnClickedButton1)
	ON_WM_SYSCOMMAND()
END_MESSAGE_MAP()


// login 消息处理程序


void login::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CBurnProcessDlg * parent = (CBurnProcessDlg*)GetParent();
	//site验证
	m_edit_site.GetWindowText(Site);
	Genesis::Gtimes::Interface::EquipLinkMes ^site = gcnew Genesis::Gtimes::Interface::EquipLinkMes;
	System::String ^put_site = gcnew String(Site);
	CString lgn_Site = site->CheckSite(put_site);

	//user验证
	m_edit_user.GetWindowText(User);
	Genesis::Gtimes::Interface::EquipLinkMes ^user = gcnew Genesis::Gtimes::Interface::EquipLinkMes;
	System::String ^put_user = gcnew String(User);
	CString lgn_User = user->CheckUser(put_site, put_user);

	//equip验证
	m_edit_equip.GetWindowText(Equip);
	Genesis::Gtimes::Interface::EquipLinkMes ^equip = gcnew Genesis::Gtimes::Interface::EquipLinkMes;
	System::String ^put_equip = gcnew String(Equip);
	CString lgn_Equip1 = equip->CheckEquip(put_equip);

	//工单
	m_edit_number.GetWindowText(Number);
	m_edit5.GetWindowText(MacMax);
//	m_edit6.GetWindowText(DevMax);
	//判断都为"T"  验证通过

	string login_site = (LPCSTR)(CStringA)(lgn_Site);		//CString to string
	string login_user = (LPCSTR)(CStringA)(lgn_User);
	string login_equip = (LPCSTR)(CStringA)(lgn_Equip1);


	if ((login_site == "T") && (login_user == "T") && (login_equip == "T"))
	{
		//AfxMessageBox(_T("登陆成功"));
		parent->loginclose = 1;
		login::OnOK();
	}
	else
	{
		AfxMessageBox(_T("登陆失败"));
	}
}


BOOL login::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (WM_KEYDOWN == pMsg->message&&VK_RETURN == pMsg->wParam)
	{
		TCHAR szClass[MAX_PATH] = { 0 };
		::GetClassName(pMsg->hwnd, szClass, MAX_PATH - 1);
		if (0 == _tcscmp(szClass, _T("Edit")))
		{
			HWND hWnd = pMsg->hwnd;
			while (NULL != (hWnd = ::GetWindow(hWnd, GW_HWNDNEXT)))
			{
				::GetClassName(hWnd, szClass, MAX_PATH - 1);
				if (0 == _tcscmp(szClass, _T("Edit")))
				{
					::SetFocus(hWnd);
					return TRUE;
				}
			}
		}
	}
	return CDialog::PreTranslateMessage(pMsg);
}


void login::OnSysCommand(UINT nID, LPARAM lParam)
{
	CBurnProcessDlg * parent = (CBurnProcessDlg*)GetParent();
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		login dlgAbout;
		dlgAbout.DoModal();
	}
	else if ((nID & 0xFFF0) == SC_CLOSE)		//右上角X  加入自己的代码
	{
		parent->loginclose = 0;
	}


	CDialogEx::OnSysCommand(nID, lParam);
}


BOOL login::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//设置字体
	font.DeleteObject();
	font.CreatePointFont(100, L"微软雅黑");
	m_static_site.SetFont(&font);
	m_static_user.SetFont(&font);
	m_static_number.SetFont(&font);
	m_static_equip.SetFont(&font);
	m_static_macmax.SetFont(&font);
//	m_static_devmax.SetFont(&font);

	font1.DeleteObject();
	font1.CreatePointFont(200, L"微软雅黑");
	m_button1.SetFont(&font1);
	

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

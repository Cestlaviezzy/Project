// login.cpp: 实现文件
//

#include "pch.h"
#include "Integration.h"
#include "login.h"
#include "afxdialogex.h"
#include "IntegrationDlg.h"
#include <string>
using namespace System;
using namespace std;

// login 对话框

IMPLEMENT_DYNAMIC(login, CDialogEx)

login::login(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG4, pParent)
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
	DDX_Control(pDX, IDC_EDIT3, m_edit_equip1);
	DDX_Control(pDX, IDC_EDIT4, m_edit_equip2);
	DDX_Control(pDX, IDC_STATIC_SITE, m_static_site);
	DDX_Control(pDX, IDC_STATIC_USER, m_static_user);
	DDX_Control(pDX, IDC_STATIC_EQUIP, m_static_equip);
	DDX_Control(pDX, IDC_BUTTON1, m_button_login);
	DDX_Control(pDX, IDC_STATIC_NUMBER, m_static_number);
	DDX_Control(pDX, IDC_EDIT5, m_edit_number);
}


BEGIN_MESSAGE_MAP(login, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &login::OnBnClickedButton1)
	ON_WM_SYSCOMMAND()
END_MESSAGE_MAP()


// login 消息处理程序

BOOL login::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	font.DeleteObject();
	font.CreatePointFont(100, _T("微软雅黑"));
	m_static_site.SetFont(&font);
	m_static_user.SetFont(&font);
	m_static_equip.SetFont(&font);
	m_static_number.SetFont(&font);
	m_button_login.SetFont(&font);


	GetPrivateProfileString(_T("LoginInfo"), _T("Site"), CString(""), login_site.GetBuffer(MAX_PATH), MAX_PATH, IntegraionPath);
	GetPrivateProfileString(_T("LoginInfo"), _T("User"), CString(""), login_user.GetBuffer(MAX_PATH), MAX_PATH, IntegraionPath);
	GetPrivateProfileString(_T("LoginInfo"), _T("Number"), CString(""), login_number.GetBuffer(MAX_PATH), MAX_PATH, IntegraionPath);
	GetPrivateProfileString(_T("LoginInfo"), _T("Equip"), CString(""), login_equip.GetBuffer(MAX_PATH), MAX_PATH, IntegraionPath);
	m_edit_site.SetWindowText(login_site);
	m_edit_user.SetWindowText(login_user);
	m_edit_number.SetWindowText(login_number);
	m_edit_equip1.SetWindowText(login_equip);


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void login::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CIntegrationDlg * parent = (CIntegrationDlg*)GetParent();
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
	m_edit_equip1.GetWindowText(Equip1);
	m_edit_equip2.GetWindowText(Equip2);
	Genesis::Gtimes::Interface::EquipLinkMes ^equip = gcnew Genesis::Gtimes::Interface::EquipLinkMes;
	System::String ^put_equip1 = gcnew String(Equip1);
	System::String ^put_equip2 = gcnew String(Equip2);
	CString lgn_Equip1 = equip->CheckEquip(put_equip1);
	CString lgn_Equip2 = equip->CheckEquip(put_equip2);

	//工单
	m_edit_number.GetWindowText(Number);

	//判断都为"T"  验证通过

	string login_site = (LPCSTR)(CStringA)(lgn_Site);		//CString to string
	string login_user = (LPCSTR)(CStringA)(lgn_User);
	string login_equip = (LPCSTR)(CStringA)(lgn_Equip1);

	
	if ((login_site == "T") && (login_user == "T") && (login_equip == "T"))
	{	
		//AfxMessageBox(_T("登陆成功"))
		//CString flag = L"T";
		parent->loginclose = 1;

		//登陆成功后，信息保存在C盘下Integraion.ini里面
		WritePrivateProfileString(L"LoginInfo", L"Site", Site, IntegraionPath);
		WritePrivateProfileString(L"LoginInfo", L"User", User, IntegraionPath);
		WritePrivateProfileString(L"LoginInfo", L"Number", Number, IntegraionPath);
		WritePrivateProfileString(L"LoginInfo", L"Equip", Equip1, IntegraionPath);
		//WritePrivateProfileString(L"LoginFlag", L"Flag", flag, IntegraionPath);

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
		// 修改回车键的操作反应  
	//if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
	//	return  TRUE;

	//return CDialogEx::PreTranslateMessage(pMsg);
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

	if (pMsg->message == WM_KEYDOWN)
	{
		switch (pMsg->wParam)
		{
			//case VK_RETURN:     //屏蔽回车  
		case VK_ESCAPE:     //屏蔽ESC  
			return true;
		}
	}
	return CDialog::PreTranslateMessage(pMsg);
}


void login::OnSysCommand(UINT nID, LPARAM lParam)
{
	CIntegrationDlg * parent = (CIntegrationDlg*)GetParent();
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

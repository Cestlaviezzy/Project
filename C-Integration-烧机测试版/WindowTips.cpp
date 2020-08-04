// WindowTips.cpp: 实现文件
//

#include "pch.h"
#include "Integration.h"
#include "WindowTips.h"
#include "afxdialogex.h"
#include "IntegrationDlg.h"


// WindowTips 对话框

IMPLEMENT_DYNAMIC(WindowTips, CDialogEx)

WindowTips::WindowTips(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG6, pParent)
{

}

WindowTips::~WindowTips()
{
}

void WindowTips::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(WindowTips, CDialogEx)
	ON_BN_CLICKED(IDOK, &WindowTips::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &WindowTips::OnBnClickedCancel)
END_MESSAGE_MAP()


// WindowTips 消息处理程序


void WindowTips::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CIntegrationDlg * parent = (CIntegrationDlg*)GetParent();
	parent->TF = 1;
	CDialogEx::OnOK();
}


void WindowTips::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CIntegrationDlg * parent = (CIntegrationDlg*)GetParent();
	parent->TF = 0;
	CDialogEx::OnCancel();
}

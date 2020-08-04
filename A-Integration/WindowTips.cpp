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
	DDX_Control(pDX, IDC_STATIC_PorF, static_PorF);
	DDX_Control(pDX, IDOK, m_button_Y);
	DDX_Control(pDX, IDCANCEL, m_button_N);
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


BOOL WindowTips::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_font.DeleteObject();
	m_font.CreatePointFont(100, L"微软雅黑");
	static_PorF.SetFont(&m_font);
	m_button_Y.SetFont(&m_font);
	m_button_N.SetFont(&m_font);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

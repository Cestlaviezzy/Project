// WindowPrompts.cpp: 实现文件
//

#include "pch.h"
#include "BurnProcess.h"
#include "WindowPrompts.h"
#include "afxdialogex.h"
#include "BurnProcessDlg.h"


// WindowPrompts 对话框

IMPLEMENT_DYNAMIC(WindowPrompts, CDialogEx)

WindowPrompts::WindowPrompts(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG3, pParent)
{

}

WindowPrompts::~WindowPrompts()
{
}

void WindowPrompts::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_PROMPTS, m_static_prompts);
}


BEGIN_MESSAGE_MAP(WindowPrompts, CDialogEx)
	ON_BN_CLICKED(IDOK, &WindowPrompts::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &WindowPrompts::OnBnClickedCancel)
END_MESSAGE_MAP()


// WindowPrompts 消息处理程序


void WindowPrompts::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CBurnProcessDlg * parent = (CBurnProcessDlg*)GetParent();
	parent->WP = 1;	
	CDialogEx::OnOK();
}


void WindowPrompts::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CBurnProcessDlg * parent = (CBurnProcessDlg*)GetParent();
	parent->WP = 0;
	CDialogEx::OnCancel();
}


BOOL WindowPrompts::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//设置字体
	font.DeleteObject();
	font.CreatePointFont(100, L"微软雅黑");
	m_static_prompts.SetFont(&font);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

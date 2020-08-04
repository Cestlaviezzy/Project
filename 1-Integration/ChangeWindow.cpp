// ChangeWindow.cpp: 实现文件
//

#include "pch.h"
#include "Integration.h"
#include "ChangeWindow.h"
#include "afxdialogex.h"


// ChangeWindow 对话框

IMPLEMENT_DYNAMIC(ChangeWindow, CDialogEx)

ChangeWindow::ChangeWindow(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG7, pParent)
{

}

ChangeWindow::~ChangeWindow()
{
}

void ChangeWindow::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_TEXT, m_static_text);
	DDX_Control(pDX, IDC_BUTTON1, m_button);
}


BEGIN_MESSAGE_MAP(ChangeWindow, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &ChangeWindow::OnBnClickedButton1)
END_MESSAGE_MAP()


// ChangeWindow 消息处理程序


void ChangeWindow::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}


BOOL ChangeWindow::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_font.DeleteObject();
	m_font.CreatePointFont(100, L"微软雅黑");
	m_static_text.SetFont(&m_font);
	m_button.SetFont(&m_font);

	GetDlgItem(IDC_BUTTON1)->SetFocus();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

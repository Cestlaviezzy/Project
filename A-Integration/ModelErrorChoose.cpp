// ModelErrorChoose.cpp: 实现文件
//

#include "pch.h"
#include "Integration.h"
#include "ModelErrorChoose.h"
#include "afxdialogex.h"
#include "IntegrationDlg.h"


// ModelErrorChoose 对话框

IMPLEMENT_DYNAMIC(ModelErrorChoose, CDialogEx)

ModelErrorChoose::ModelErrorChoose(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG8, pParent)
{

}

ModelErrorChoose::~ModelErrorChoose()
{
}

void ModelErrorChoose::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON1, m_button1);
	DDX_Control(pDX, IDC_BUTTON2, m_button2);
	DDX_Control(pDX, IDC_BUTTON3, m_button3);
	DDX_Control(pDX, IDC_STATIC_CHOOSE, m_static_choose);
}


BEGIN_MESSAGE_MAP(ModelErrorChoose, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &ModelErrorChoose::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &ModelErrorChoose::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &ModelErrorChoose::OnBnClickedButton3)
END_MESSAGE_MAP()


// ModelErrorChoose 消息处理程序


void ModelErrorChoose::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CIntegrationDlg * parent = (CIntegrationDlg*)GetParent();
	parent->Choose = "one";
	ModelErrorChoose::OnOK();
}


void ModelErrorChoose::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	CIntegrationDlg * parent = (CIntegrationDlg*)GetParent();
	parent->Choose = "two";
	ModelErrorChoose::OnOK();
}


void ModelErrorChoose::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	CIntegrationDlg * parent = (CIntegrationDlg*)GetParent();
	parent->Choose = "three";
	ModelErrorChoose::OnOK();
}


BOOL ModelErrorChoose::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//设置字体
	font.DeleteObject();
	font.CreatePointFont(150, L"微软雅黑");
	m_button1.SetFont(&font);
	m_button2.SetFont(&font);
	m_button3.SetFont(&font);

	fontstatic.DeleteObject();
	fontstatic.CreatePointFont(200, L"微软雅黑");
	m_static_choose.SetFont(&fontstatic);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

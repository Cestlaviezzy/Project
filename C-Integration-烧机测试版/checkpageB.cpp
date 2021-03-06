﻿// checkpageB.cpp: 实现文件
//

#include "pch.h"
#include "Integration.h"
#include "checkpageB.h"
#include "configpage.h"
#include "afxdialogex.h"


// checkpageB 对话框

IMPLEMENT_DYNAMIC(checkpageB, CDialogEx)

checkpageB::checkpageB(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG3, pParent)
{

}

checkpageB::~checkpageB()
{
}

void checkpageB::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_edit_item);
	DDX_Control(pDX, IDC_EDIT2, m_edit_software);
	DDX_Control(pDX, IDC_EDIT3, m_edit_result);
	DDX_Control(pDX, IDC_STATIC_B, m_static_B);
	DDX_Control(pDX, IDC_STATIC_ITEM, m_static_item);
	DDX_Control(pDX, IDC_STATIC_SOFTWARE, m_static_software);
	DDX_Control(pDX, IDC_STATIC_RESULT, m_static_result);
	DDX_Control(pDX, IDC_BUTTON3, m_button_save);
	DDX_Control(pDX, IDC_BUTTON4, m_button_cancle);
	DDX_Control(pDX, IDC_BUTTON1, m_check_exe);
	DDX_Control(pDX, IDC_BUTTON2, m_check_result);
}


BEGIN_MESSAGE_MAP(checkpageB, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &checkpageB::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &checkpageB::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &checkpageB::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &checkpageB::OnBnClickedButton4)
END_MESSAGE_MAP()


// checkpageB 消息处理程序

/**********B面选择EXE按钮**********/
void checkpageB::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("All Files(*.exe)|*.exe|(*.exe)|*.exe|"), NULL);
	if (dlg.DoModal())
	{
		CString s = dlg.GetPathName();
		s.Replace(L"\\", L"\\\\");		//	替换
		check_exe = s;
	}
	SetDlgItemText(IDC_EDIT2, check_exe);
	CString m_csFileName1;
	m_csFileName1 = check_exe.Right(check_exe.GetLength() - check_exe.ReverseFind('\\') - 1);		//反向截取字符串获取最后一个\\后边字符串
	if (check_exe.Find(m_csFileName1))
	{
		check_exe.Replace(m_csFileName1, L"result.txt");

	}
	SetDlgItemText(IDC_EDIT3, check_exe);
}


void checkpageB::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("All Files(*.log)|*.log|(*.log)|*.log|"), NULL);
	if (dlg.DoModal())
	{
		CString s = dlg.GetPathName();
		s.Replace(L"\\", L"\\\\");		//	替换
		check_result = s;
	}
	SetDlgItemText(IDC_EDIT3, check_result);
}


void checkpageB::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	configpage * parent = (configpage*)GetParent();
	CString tt;
	CString str1, str2, str3;
	this->m_edit_item.GetWindowText(str1);//获取当前子窗口编辑框中的值
	this->m_edit_software.GetWindowText(str2);
	this->m_edit_result.GetWindowText(str3);

	if ((str1 == "") || (str2 == "") || (str3 == ""))
	{
		AfxMessageBox(_T("请填写所有信息"));
	}
	else
	{
		int flag = parent->m_list_B.GetItemCount();  //获取行数
		tt.Format(L"%d", flag);
		parent->m_list_B.InsertItem(flag, tt);
		parent->m_list_B.SetItemText(flag, 0, str1);//把当前编辑框中的值回传给父窗口
		parent->m_list_B.SetItemText(flag, 1, str2);
		parent->m_list_B.SetItemText(flag, 2, str3);
		parent->flag_B = 1;
		CDialogEx::OnOK();
	}
}


void checkpageB::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	configpage * parent = (configpage*)GetParent();
	int pageB = 0;
	parent->flag_B = pageB;
	CDialogEx::OnCancel();
}


BOOL checkpageB::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_font.DeleteObject();
	m_font.CreatePointFont(100, L"微软雅黑");
	m_static_B.SetFont(&m_font);
	m_static_item.SetFont(&m_font);
	m_static_software.SetFont(&m_font);
	m_static_result.SetFont(&m_font);
	m_check_exe.SetFont(&m_font);
	m_check_result.SetFont(&m_font);
	m_button_save.SetFont(&m_font);
	m_button_cancle.SetFont(&m_font);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

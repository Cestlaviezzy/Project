// NoConnectMax.cpp: 实现文件
//

#include "pch.h"
#include "BurnProcess.h"
#include "NoConnectMax.h"
#include "afxdialogex.h"
#include "BurnProcessDlg.h"


// NoConnectMax 对话框

IMPLEMENT_DYNAMIC(NoConnectMax, CDialogEx)

NoConnectMax::NoConnectMax(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG4, pParent)
{

}

NoConnectMax::~NoConnectMax()
{
}

void NoConnectMax::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_edit_macmax);
	//	DDX_Control(pDX, IDC_EDIT2, m_edit_devmax);
	DDX_Control(pDX, IDC_STATIC_MACMAX, m_static_macmax);
}


BEGIN_MESSAGE_MAP(NoConnectMax, CDialogEx)
	ON_WM_SYSCOMMAND()
END_MESSAGE_MAP()


// NoConnectMax 消息处理程序


BOOL NoConnectMax::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	font.DeleteObject();
	font.CreatePointFont(100, _T("微软雅黑"));
	m_static_macmax.SetFont(&font);
	
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


BOOL NoConnectMax::PreTranslateMessage(MSG* pMsg)
{
	CBurnProcessDlg * parent = (CBurnProcessDlg*)GetParent();
	m_edit_macmax.GetWindowText(macmax);
//	m_edit_devmax.GetWindowText(devmax);
	if (WM_KEYDOWN == pMsg->message && VK_RETURN == pMsg->wParam)
	{
		if (GetFocus() == GetDlgItem(IDC_EDIT1))
		{
			if (macmax.GetLength() == 12)
			{
				//GetDlgItem(IDC_EDIT2)->SetFocus();
				parent->loginclose = 1;
				NoConnectMax::OnOK();
			}
			else
			{
				AfxMessageBox(L"MacMax长度不是12位");
				m_edit_macmax.SetWindowText(_TEXT(""));
				GetDlgItem(IDC_EDIT1)->SetFocus();
			}
		}
		//else if (GetFocus() == GetDlgItem(IDC_EDIT2))
		//{
		//	if (devmax.GetLength() == 12)
		//	{
		//		NoConnectMax::OnOK();
		//	}
		//	else
		//	{
		//		AfxMessageBox(L"SNMax长度不是12位");
		//		m_edit_devmax.SetWindowText(_TEXT(""));
		//		GetDlgItem(IDC_EDIT2)->SetFocus();
		//	}
		//}
		return true;
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}


void NoConnectMax::OnSysCommand(UINT nID, LPARAM lParam)
{
	CBurnProcessDlg * parent = (CBurnProcessDlg*)GetParent();
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		NoConnectMax dlgAbout;
		dlgAbout.DoModal();
	}
	else if ((nID & 0xFFF0) == SC_CLOSE)		//右上角X  加入自己的代码
	{
		parent->loginclose = 0;
	}


	CDialogEx::OnSysCommand(nID, lParam);
}

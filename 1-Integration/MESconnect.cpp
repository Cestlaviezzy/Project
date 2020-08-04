// MESconnect.cpp: 实现文件
//

#include "pch.h"
#include "Integration.h"
#include "MESconnect.h"
#include "afxdialogex.h"
#include <string>
#include "IntegrationDlg.h"

using namespace std;


// MESconnect 对话框

IMPLEMENT_DYNAMIC(MESconnect, CDialogEx)

MESconnect::MESconnect(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG5, pParent)
{

}

MESconnect::~MESconnect()
{
}

void MESconnect::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_edit1);
	DDX_Control(pDX, IDC_STATIC_PASSWORD, m_static_password);
}


BEGIN_MESSAGE_MAP(MESconnect, CDialogEx)
END_MESSAGE_MAP()


// MESconnect 消息处理程序
BOOL MESconnect::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_font.DeleteObject();
	m_font.CreatePointFont(100, L"微软雅黑");
	m_static_password.SetFont(&m_font);


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

BOOL MESconnect::PreTranslateMessage(MSG* pMsg)
{
	CString str;
	// TODO: 在此添加专用代码和/或调用基类
	if (WM_KEYDOWN == pMsg->message && VK_RETURN == pMsg->wParam)
	{
		if (GetFocus() == GetDlgItem(IDC_EDIT1))
		{
			UpdateData(TRUE);
			m_edit1.GetWindowText(str);
			//m_edit2.SetWindowText(str);
			//WriteFileToPath(str);
			MESLogin(str);
			UpdateData(FALSE);
		}
		return true;
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}

//flag = 6;  启动定时器密码
void MESconnect::MESLogin(CString password) 
{
	CIntegrationDlg * parent = (CIntegrationDlg*)GetParent();
	string ps = (LPCSTR)(CStringA)(password);
	if (ps == "123456") 
	{
		//AfxMessageBox(_T("解锁成功"));
		flag = 1;
		parent->mespasswordflag = flag;
		MESconnect::OnOK();
	}
	else if (ps == "666666")
	{
		flag = 6;
		parent->mespasswordflag = flag;
		MESconnect::OnOK();
	}
	else
	{
		//AfxMessageBox(_T("解锁失败"));
		flag = 0;
		parent->mespasswordflag = flag;
		MESconnect::OnOK();
	}
}



// password.cpp: 实现文件
//

#include "pch.h"
#include "BurnProcess.h"
#include "password.h"
#include "afxdialogex.h"
#include "BurnProcessDlg.h"
#include <string>


using namespace std;



// password 对话框

IMPLEMENT_DYNAMIC(password, CDialogEx)

password::password(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG2, pParent)
{

}

password::~password()
{
}

void password::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_edit1);
	DDX_Control(pDX, IDC_STATIC_PASSWORD, m_static_password);
}


BEGIN_MESSAGE_MAP(password, CDialogEx)
END_MESSAGE_MAP()


// password 消息处理程序


BOOL password::PreTranslateMessage(MSG* pMsg)
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
			MES_No_Connet_PassWord(str);
			UpdateData(FALSE);
		}
		return true;
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}

void password::MES_No_Connet_PassWord(CString password)
{
	CBurnProcessDlg * parent = (CBurnProcessDlg*)GetParent();
	string ps = (LPCSTR)(CStringA)(password);
	if (ps == "123456")
	{
		//AfxMessageBox(_T("解锁成功"));
		flag = 1;
		parent->mespasswordflag = flag;
		password::OnOK();
	}
	else
	{
		//AfxMessageBox(_T("解锁失败"));
		flag = 0;
		parent->mespasswordflag = flag;
		password::OnOK();
	}
}

BOOL password::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//设置字体
	font.DeleteObject();
	font.CreatePointFont(100, L"微软雅黑");
	m_static_password.SetFont(&font);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

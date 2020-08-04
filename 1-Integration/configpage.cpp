// configpage.cpp: 实现文件
//

#include "pch.h"
#include "Integration.h"
#include "configpage.h"
#include "afxdialogex.h"
#include "checkpageA.h"
#include "checkpageB.h"
#include "IntegrationDlg.h"


// configpage 对话框

IMPLEMENT_DYNAMIC(configpage, CDialogEx)

configpage::configpage(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

configpage::~configpage()
{
}

void configpage::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list_A);
	DDX_Control(pDX, IDC_LIST2, m_list_B);
	DDX_Control(pDX, IDC_CHECK1, m_checkbox);
	DDX_Control(pDX, IDC_STATIC_A, m_static_A);
	DDX_Control(pDX, IDC_STATIC_B, m_static_B);
	DDX_Control(pDX, IDC_BUTTON1, m_button_A_add);
	DDX_Control(pDX, IDC_BUTTON2, m_button_A_del);
	DDX_Control(pDX, IDC_BUTTON3, m_button_B_add);
	DDX_Control(pDX, IDC_BUTTON4, m_button_B_del);
}


BEGIN_MESSAGE_MAP(configpage, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &configpage::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON3, &configpage::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON2, &configpage::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON4, &configpage::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &configpage::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_CHECK1, &configpage::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_BUTTON6, &configpage::OnBnClickedButton6)
END_MESSAGE_MAP()

BOOL configpage::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_list_A.SetExtendedStyle(m_list_A.GetExtendedStyle() | LVS_EX_FULLROWSELECT);//设置listcontrol report属性也能整行选中
	m_list_B.SetExtendedStyle(m_list_B.GetExtendedStyle() | LVS_EX_FULLROWSELECT);//设置listcontrol report属性也能整行选中
	CRect rectA, rectB;
	m_list_A.GetClientRect(&rectA);
	m_list_B.GetClientRect(&rectB);
	/**********初始化AB面三列**********/
	m_list_A.InsertColumn(0, _T("项目名称"), LVCFMT_CENTER, rectA.Width() / 3);
	m_list_A.InsertColumn(1, _T("软件路径"), LVCFMT_CENTER, rectA.Width() / 3);
	m_list_A.InsertColumn(2, _T("结果路径"), LVCFMT_CENTER, rectA.Width() / 3);

	m_list_B.InsertColumn(0, _T("项目名称"), LVCFMT_CENTER, rectB.Width() / 3);
	m_list_B.InsertColumn(1, _T("软件路径"), LVCFMT_CENTER, rectB.Width() / 3);
	m_list_B.InsertColumn(2, _T("结果路径"), LVCFMT_CENTER, rectB.Width() / 3);
	//读取ini文档并现实
	CString stra, strb;
	int m_indexA = 0;
	int m_indexB = 0;
	CString InformationStrA;
	CString InformationStrB;
	GetPrivateProfileString(_T("LIST"), _T("Rows"), CString("NULL"), stra.GetBuffer(MAX_PATH), MAX_PATH, PathA);
	GetPrivateProfileString(_T("LIST"), _T("Rows"), CString("NULL"), strb.GetBuffer(MAX_PATH), MAX_PATH, PathB);
	rowsA = _ttoi(stra);
	rowsB = _ttoi(strb);

	for (int i = 0; i < rowsA; i++)
	{
		int j = 0;
		m_list_A.InsertItem(i, L"");
		InformationStrA.Format(_T("Information_%d"), m_indexA);
		GetPrivateProfileString(InformationStrA, L"Item", L"", stritema.GetBuffer(MAX_PATH), MAX_PATH, PathA);		//read Item name
		stritema.ReleaseBuffer();
		m_list_A.SetItemText(i, j++, stritema);
		GetPrivateProfileString(InformationStrA, L"Software", L"", strsoftwarea.GetBuffer(MAX_PATH), MAX_PATH, PathA);		//read Software path 
		strsoftwarea.ReleaseBuffer();
		m_list_A.SetItemText(i, j++, strsoftwarea);
		GetPrivateProfileString(InformationStrA, L"Result", L"", strresulta.GetBuffer(MAX_PATH), MAX_PATH, PathA);		//read Result path 
		strresulta.ReleaseBuffer();
		m_list_A.SetItemText(i, j++, strresulta);
		m_indexA++;
	}
	for (int i = 0; i < rowsB; i++)
	{
		int j = 0;
		m_list_B.InsertItem(i, L"");
		InformationStrB.Format(_T("Information_%d"), m_indexB);
		GetPrivateProfileString(InformationStrB, _T("Item"), CString("NULL"), stritemb.GetBuffer(MAX_PATH), MAX_PATH, PathB);
		stritemb.ReleaseBuffer();
		m_list_B.SetItemText(i, j++, stritemb);
		GetPrivateProfileString(InformationStrB, _T("Software"), CString("NULL"), strsoftwareb.GetBuffer(MAX_PATH), MAX_PATH, PathB);
		strsoftwareb.ReleaseBuffer();
		m_list_B.SetItemText(i, j++, strsoftwareb);
		GetPrivateProfileString(InformationStrB, L"Result", CString("NULL"), strresultb.GetBuffer(MAX_PATH), MAX_PATH, PathB);
		strresultb.ReleaseBuffer();
		m_list_B.SetItemText(i, j++, strresultb);
		m_indexB++;
	}
	

	int nCheck = 0;
	((CButton *)GetDlgItem(IDC_CHECK1))->SetCheck(nCheck);
	GetDlgItem(IDC_BUTTON3)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON4)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON5)->EnableWindow(FALSE);

	//设置字体
	m_font.DeleteObject();
	m_font.CreatePointFont(100, L"微软雅黑");
	m_static_A.SetFont(&m_font);
	m_static_B.SetFont(&m_font);
	m_list_A.SetFont(&m_font);
	m_list_B.SetFont(&m_font);
	m_checkbox.SetFont(&m_font);
	m_button_A_add.SetFont(&m_font);
	m_button_A_del.SetFont(&m_font);
	m_button_B_add.SetFont(&m_font);
	m_button_B_del.SetFont(&m_font);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

// configpage 消息处理程序

/**********正面添加按钮**********/
void configpage::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	checkpageA Dlg;
	Dlg.DoModal();
	int fg = m_list_A.GetItemCount();  //获取行数
	if (fg > 14)
	{
		//AfxMessageBox(_T("项目数量已经10个，删除后在添加操作"));
		GetDlgItem(IDC_BUTTON1)->EnableWindow(FALSE);
	}
	//判断list数据是否为空，空的话禁止保存，只能取消
	if (flag_A == 0)
	{
		GetDlgItem(IDC_BUTTON5)->EnableWindow(FALSE);
	}
	else
	{
		GetDlgItem(IDC_BUTTON5)->EnableWindow(TRUE);
	}
	
}

/**********正面删除按钮**********/
void configpage::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	int count = m_list_A.GetSelectedCount();	//获取选中行
	int lineA = m_list_A.GetItemCount();	//获取行数
	int sel;
	sel = m_list_A.GetNextItem(-1, LVIS_SELECTED);
	if (count > 0)
	{
		if (lineA == 1)
		{
			POSITION pos = m_list_A.GetFirstSelectedItemPosition();
			while (pos != NULL)
			{
				int delId = m_list_A.GetNextSelectedItem(pos);
				m_list_A.DeleteItem(delId);
			}
			GetDlgItem(IDC_BUTTON5)->EnableWindow(FALSE);
		}
		else if (lineA > 0)
		{
			POSITION pos = m_list_A.GetFirstSelectedItemPosition();
			while (pos != NULL)
			{
				int delId = m_list_A.GetNextSelectedItem(pos);
				m_list_A.DeleteItem(delId);
			}
			GetDlgItem(IDC_BUTTON5)->EnableWindow(TRUE);
		}
		else if (lineA < 1)
		{
			GetDlgItem(IDC_BUTTON5)->EnableWindow(FALSE);
			MessageBoxW(_T("未选中任何行或者当前没有可以删除数据"));
		}
	}
	else
	{
		MessageBoxW(_T("请选中要删除数据"));
	}

}


/**********反面添加按钮**********/
void configpage::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	checkpageB Dlg;
	Dlg.DoModal();
	int flag = m_list_B.GetItemCount();  //获取行数
	if (flag > 14)
	{
		//AfxMessageBox(_T("项目数量已经10个，删除后在添加操作"));
		GetDlgItem(IDC_BUTTON1)->EnableWindow(FALSE);
	}
	//判断list数据是否为空，空的话禁止保存，只能取消
	if (flag_B == 0)
	{
		GetDlgItem(IDC_BUTTON5)->EnableWindow(FALSE);
	}
	else
	{
		GetDlgItem(IDC_BUTTON5)->EnableWindow(TRUE);
	}
}


/**********反面删除按钮**********/
void configpage::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	int count = m_list_B.GetSelectedCount();	//获取选中行
	int lineB = m_list_B.GetItemCount();	//获取行数
	int lineA = m_list_A.GetItemCount();	//获取行数
	int sel;
	sel = m_list_B.GetNextItem(-1, LVIS_SELECTED);
	if (count > 0)
	{
		if (lineB == 1)
		{
			POSITION pos = m_list_B.GetFirstSelectedItemPosition();
			while (pos != NULL)
			{
				int delId = m_list_B.GetNextSelectedItem(pos);
				m_list_B.DeleteItem(delId);
			}
			//GetDlgItem(IDC_BUTTON5)->EnableWindow(FALSE);
			((CButton *)GetDlgItem(IDC_CHECK1))->SetCheck(0);
			GetDlgItem(IDC_BUTTON3)->EnableWindow(FALSE);
			GetDlgItem(IDC_BUTTON4)->EnableWindow(FALSE);
		}
		else if (lineB > 0)
		{
			POSITION pos = m_list_B.GetFirstSelectedItemPosition();
			while (pos != NULL)
			{
				int delId = m_list_B.GetNextSelectedItem(pos);
				m_list_B.DeleteItem(delId);
			}
			if (lineA>0)
			{
				GetDlgItem(IDC_BUTTON5)->EnableWindow(TRUE);
			}
			else
			{
				GetDlgItem(IDC_BUTTON5)->EnableWindow(FALSE);
			}
			
		}
		else if (lineB < 1)
		{
			GetDlgItem(IDC_BUTTON5)->EnableWindow(FALSE);
			MessageBoxW(_T("未选中任何行或者当前没有可以删除数据"));
		}
		else if (lineB == 0)
		{
			GetDlgItem(IDC_BUTTON5)->EnableWindow(FALSE);
		}
	}
	else
	{
		MessageBoxW(_T("请选中要删除数据"));
	}
}


void configpage::OnBnClickedCheck1()
{
	// TODO: 在此添加控件通知处理程序代码
	int state = ((CButton *)GetDlgItem(IDC_CHECK1))->GetCheck();
	int flag_a = m_list_A.GetItemCount();  //获取行数
	int flag_b = m_list_B.GetItemCount();  //获取行数
	if (state == 1)
	{
		if (flag_a < 0)
		{
			MessageBoxW(_T("请添加正面数据后在操作"));
			GetDlgItem(IDC_BUTTON3)->EnableWindow(FALSE);
			GetDlgItem(IDC_BUTTON4)->EnableWindow(FALSE);
			GetDlgItem(IDC_BUTTON5)->EnableWindow(FALSE);
			((CButton *)GetDlgItem(IDC_CHECK1))->SetCheck(0);
			return;
		}
		else
		{
			GetDlgItem(IDC_BUTTON3)->EnableWindow(TRUE);
			GetDlgItem(IDC_BUTTON4)->EnableWindow(TRUE);
		}

		if (flag_b < 0)
		{
			MessageBoxW(_T("请添加反面数据后在操作"));
			GetDlgItem(IDC_BUTTON3)->EnableWindow(FALSE);
			GetDlgItem(IDC_BUTTON4)->EnableWindow(FALSE);
			GetDlgItem(IDC_BUTTON5)->EnableWindow(FALSE);
			((CButton *)GetDlgItem(IDC_CHECK1))->SetCheck(0);
			return;
		}
		else
		{
			GetDlgItem(IDC_BUTTON3)->EnableWindow(TRUE);
			GetDlgItem(IDC_BUTTON4)->EnableWindow(TRUE);
			GetDlgItem(IDC_BUTTON5)->EnableWindow(FALSE);
		}

		//if ((flag_a <= 0) && (flag_b <= 0))
		//{
		//	GetDlgItem(IDC_BUTTON5)->EnableWindow(FALSE);
		//}
	}
	else if (state == 0)
	{
		GetDlgItem(IDC_BUTTON3)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON4)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON5)->EnableWindow(FALSE);
	}
}



/**********list数据保存**********/
void configpage::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	/**********删除临时ini文件**********/
	DeleteFile(PathA);
	DeleteFile(PathB);
	/**********A面list页面数据清空**********/
	CIntegrationDlg * parent = (CIntegrationDlg*)GetParent();
	parent->m_listA.DeleteAllItems(); //清空列表A
	parent->m_listB.DeleteAllItems(); //清空列表B
	/**********A面list数据保存**********/
	n = ((CButton *)GetDlgItem(IDC_CHECK1))->GetCheck();
	int m_indexA = 0;
	int m_indexB = 0;
	CString InformationStrA;
	CString InformationStrB;
	rowsA = m_list_A.GetItemCount();	//行数
	rowsB = m_list_B.GetItemCount();	//行数
	colsA = m_list_A.GetHeaderCtrl()->GetItemCount();	//列数
	colsB = m_list_B.GetHeaderCtrl()->GetItemCount();	//列数
	CString list_Arows;
	CString list_Brows;
	list_Arows.Format(L"%d", rowsA);		//int转CString
	list_Brows.Format(L"%d", rowsB);

	WritePrivateProfileString(L"LIST", L"Rows", list_Arows, PathA);
	for (int i = 0; i < rowsA; i++)
	{
		int j = 0;
		InformationStrA.Format(_T("Information_%d"), m_indexA);
		itemA = m_list_A.GetItemText(i, j++);
		WritePrivateProfileString(InformationStrA, L"Item", itemA, PathA);

		softwareA = m_list_A.GetItemText(i, j++);
		WritePrivateProfileString(InformationStrA, L"Software", softwareA, PathA);

		resultA = m_list_A.GetItemText(i, j++);
		WritePrivateProfileString(InformationStrA, L"Result", resultA, PathA);
		parent->m_listA.InsertItem(i, itemA);
		parent->m_listA.SetItemText(i, 1, L"等待测试");
		m_indexA++;
	}

	/**********B面list数据保存**********/
	if (rowsB != 0)
	{
		WritePrivateProfileString(L"LIST", L"Rows", list_Brows, PathB);
		for (int i = 0; i < rowsB; i++)
		{
			int j = 0;
			InformationStrB.Format(_T("Information_%d"), m_indexB);
			itemB = m_list_B.GetItemText(i, j++);
			WritePrivateProfileString(InformationStrB, L"Item", itemB, PathB);

			softwareB = m_list_B.GetItemText(i, j++);
			WritePrivateProfileString(InformationStrB, L"Software", softwareB, PathB);

			resultB = m_list_B.GetItemText(i, j++);
			WritePrivateProfileString(InformationStrB, L"Result", resultB, PathB);
			parent->m_listB.InsertItem(i, itemB);
			parent->m_listB.SetItemText(i, 1, L"等待测试");
			m_indexB++;
		}
	}
	else
	{
		if (n == 1)
		{
			WritePrivateProfileString(L"LIST", L"Rows", list_Brows, PathB);
			for (int i = 0; i < rowsB; i++)
			{
				int j = 0;
				InformationStrB.Format(_T("Information_%d"), m_indexB);
				itemB = m_list_B.GetItemText(i, j++);
				WritePrivateProfileString(InformationStrB, L"Item", itemB, PathB);

				softwareB = m_list_B.GetItemText(i, j++);
				WritePrivateProfileString(InformationStrB, L"Software", softwareB, PathB);

				resultB = m_list_B.GetItemText(i, j++);
				WritePrivateProfileString(InformationStrB, L"Result", resultB, PathB);
				parent->m_listB.InsertItem(i, itemB);
				parent->m_listB.SetItemText(i, 1, L"等待测试");
				m_indexB++;
			}
		}
	}

	CDialogEx::OnOK();
}





void configpage::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}




#pragma once


// login 对话框

class login : public CDialogEx
{
	DECLARE_DYNAMIC(login)

public:
	login(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~login();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG4 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	CEdit m_edit_site;
	CEdit m_edit_user;
	CEdit m_edit_equip1;
	CEdit m_edit_equip2;
	CString Site;
	CString User;
	CString Equip1, Equip2;
	CString Number;
	virtual BOOL OnInitDialog();
	CFont font;
	CStatic m_static_site;
	CStatic m_static_user;
	CStatic m_static_equip;
	CButton m_button_login;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	CStatic m_static_number;
	CEdit m_edit_number;
	CString IntegraionName = _T("Integraion.ini");
	CString IntegraionPath = _T("C:\\Integraion.ini");
	CString login_site;
	CString login_user;
	CString login_number;
	CString login_equip;
};

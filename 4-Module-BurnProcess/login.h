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
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	CString Site;
	CString User;
	CString Number;
	CString Equip;
	CEdit m_edit_site;
	CEdit m_edit_user;
	CEdit m_edit_number;
	CEdit m_edit_equip;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	virtual BOOL OnInitDialog();
	CFont font,font1;
	CStatic m_static_site;
	CStatic m_static_user;
	CStatic m_static_number;
	CStatic m_static_equip;
	CButton m_button1;
	CEdit m_edit5;
//	CEdit m_edit6;
	CString MacMax;
//	CString DevMax;
	CStatic m_static_macmax;
//	CStatic m_static_devmax;
};

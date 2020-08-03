#pragma once


// password 对话框

class password : public CDialogEx
{
	DECLARE_DYNAMIC(password)

public:
	password(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~password();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CEdit m_edit1;
	void password::MES_No_Connet_PassWord(CString password);
	int flag;
	CStatic m_static_password;
	virtual BOOL OnInitDialog();
	CFont font;
};

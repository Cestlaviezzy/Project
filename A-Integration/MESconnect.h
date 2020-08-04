#pragma once


// MESconnect 对话框

class MESconnect : public CDialogEx
{
	DECLARE_DYNAMIC(MESconnect)

public:
	MESconnect(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~MESconnect();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG5 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CEdit m_edit1;
	void MESLogin(CString password);
	int flag;
	virtual BOOL OnInitDialog();
	CFont m_font;
	CStatic m_static_password;
};

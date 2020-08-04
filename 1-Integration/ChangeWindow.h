#pragma once


// ChangeWindow 对话框

class ChangeWindow : public CDialogEx
{
	DECLARE_DYNAMIC(ChangeWindow)

public:
	ChangeWindow(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~ChangeWindow();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG7 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	CStatic m_static_text;
	virtual BOOL OnInitDialog();
	CFont m_font;
	CButton m_button;
};

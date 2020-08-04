#pragma once


// WindowTips 对话框

class WindowTips : public CDialogEx
{
	DECLARE_DYNAMIC(WindowTips)

public:
	WindowTips(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~WindowTips();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG6 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	CStatic static_PorF;
	virtual BOOL OnInitDialog();
	CFont m_font;
	CButton m_button_Y;
	CButton m_button_N;
};

#pragma once


// WindowPrompts 对话框

class WindowPrompts : public CDialogEx
{
	DECLARE_DYNAMIC(WindowPrompts)

public:
	WindowPrompts(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~WindowPrompts();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	CStatic m_static_prompts;
	virtual BOOL OnInitDialog();
	CFont font;
};

#pragma once


// ModelErrorChoose 对话框

class ModelErrorChoose : public CDialogEx
{
	DECLARE_DYNAMIC(ModelErrorChoose)

public:
	ModelErrorChoose(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~ModelErrorChoose();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG8 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CButton m_button1;
	CButton m_button2;
	CButton m_button3;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	virtual BOOL OnInitDialog();
	CFont font, fontstatic;
	CStatic m_static_choose;
};

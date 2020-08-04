#pragma once


// checkpageA 对话框

class checkpageA : public CDialogEx
{
	DECLARE_DYNAMIC(checkpageA)

public:
	checkpageA(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~checkpageA();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	CString check_exe;
	CString check_result;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	CEdit m_edit_item;
	CEdit m_edit_software;
	CEdit m_edit_result;
	CString result = L"result.log";

	CFont m_font;
	CStatic m_static_A;
	CStatic m_static_item;
	CStatic m_static_software;
	CStatic m_static_result;
	CButton m_check_exe;
	CButton m_check_result;
	CButton m_button_save;
	CButton m_button_cancle;
	virtual BOOL OnInitDialog();
};

#pragma once


// checkpageB 对话框

class checkpageB : public CDialogEx
{
	DECLARE_DYNAMIC(checkpageB)

public:
	checkpageB(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~checkpageB();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_edit_item;
	CEdit m_edit_software;
	CEdit m_edit_result;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	CString check_exe;
	CString check_result;

	CFont m_font;
	CStatic m_static_B;
	CStatic m_static_item;
	CStatic m_static_software;
	CStatic m_static_result;
	CButton m_button_save;
	CButton m_button_cancle;
	CButton m_check_exe;
	CButton m_check_result;
	virtual BOOL OnInitDialog();
};

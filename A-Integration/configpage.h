#pragma once


// configpage 对话框

class configpage : public CDialogEx
{
	DECLARE_DYNAMIC(configpage)

public:
	configpage(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~configpage();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton3();
	CListCtrl m_list_A;
	CListCtrl m_list_B;
	afx_msg void OnBnClickedButton2();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	int rowsA;
	int colsA;
	int rowsB;
	int colsB;
	CString PathA = L"..\\menuA.ini";
	CString PathB = L"..\\menuB.ini";
	CString itemA, softwareA, resultA;
	CString itemB, softwareB, resultB;
	CButton m_checkbox;
	afx_msg void OnBnClickedCheck1();
	int n;
	CStatic m_static_A;
	CStatic m_static_B;
	CFont m_font;
	CButton m_button_A_add;
	CButton m_button_A_del;
	CButton m_button_B_add;
	CButton m_button_B_del;
	afx_msg void OnBnClickedButton6();
	int flag_A;
	int flag_B;
	afx_msg void OnBnClickedCheck2();
	CString stritema, strsoftwarea, strresulta;
	CString stritemb, strsoftwareb, strresultb;
};

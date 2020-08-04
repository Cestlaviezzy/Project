
// PowerLightDlg.h: 头文件
//

#pragma once


// CPowerLightDlg 对话框
class CPowerLightDlg : public CDialogEx
{
// 构造
public:
	CPowerLightDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_POWERLIGHT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	void CPowerLightDlg::OnWriteFileLine(CString path, CString str);
	CString T = _T("T");
	CString s = _T(",");
	CString Function = _T("LED_Test");
	CString DH1501 = _T("DH1501");
	CString AB_TXT = L"C:\\GOODWAY\\AB.txt";
	CString CPowerLightDlg::ReadFileFirstLine(CString path);
	CStatic m_static_powerlight;
	CButton m_buttonYES;
	CButton m_buttonNO;
	CFont font;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};

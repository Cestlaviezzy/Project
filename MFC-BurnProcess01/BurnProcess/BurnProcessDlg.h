
// BurnProcessDlg.h: 头文件
//

#pragma once


// CBurnProcessDlg 对话框
class CBurnProcessDlg : public CDialogEx
{
// 构造
public:
	CBurnProcessDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BURNPROCESS_DIALOG };
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
	void CBurnProcessDlg::CharToUTF8(CString &str);
	void CBurnProcessDlg::OnRunExe(CString path, CString Param, CString dest);
	int CBurnProcessDlg::GetFileLine(CString road);
	void CBurnProcessDlg::ReplaceFuncMAC(CString pszSrc, CString pszDes2);
	void CBurnProcessDlg::ReplaceFuncDEV(CString DeviceSrc, CString Device2);
	void CBurnProcessDlg::ButtonFunc();
	CString CBurnProcessDlg::ReadFileALL(CString path);
	void CBurnProcessDlg::BurnProcess();
	void CBurnProcessDlg::CheckFunc();
	void CBurnProcessDlg::DisplayResult(CString Result);
	COLORREF EndResult_textColor;//to change the color of result
	COLORREF EndResult_backColor;//to change the color of result
	CBrush EndResult_backBrush;//to change the color of result
	COLORREF EndResult_textColor_mes;//to change the color of result
	COLORREF EndResult_backColor_mes;//to change the color of result
	CBrush EndResult_backBrush_mes;//to change the color of result
	CFont font;

	CEdit m_edit1;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CEdit m_edit2;
	CEdit m_edit3;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CString run;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedRadio1();
	CButton m_radio1;
	CButton m_radio2;
	afx_msg void OnBnClickedRadio2();
	int RadioState_Yes;
	int RadioState_Err;
	CEdit m_edit_site;
	CEdit m_edit_user;
	CEdit m_edit_number;
	CEdit m_edit_equip;
	CEdit m_edit_mes;
	int loginclose;
	int mespasswordflag;
	void CBurnProcessDlg::DisplayMESconnet(CString Result);
	CString DB1404 = _T("DB1404");
	CString T = _T("T");
	CString s = _T(",");
	CString Function = _T("Mac Burn");
	void CBurnProcessDlg::OnWriteFileLine(CString path, CString str);
	CString CBurnProcessDlg::ReadFileFirstLine(CString path);
	CString site;
	CString user;
	CString number;
	CString equip;
	//CString pcb;
	int WP;
	void CBurnProcessDlg::ReplaceFuncMACMAX(CString pszSrc, CString pszDes2);
	void CBurnProcessDlg::ReplaceFuncDEVMAX(CString DeviceSrc, CString Device2);
	CEdit m_edit_macmax;
	CEdit m_edit_devmax;
	CString macmax;
	CString devmax;
};
